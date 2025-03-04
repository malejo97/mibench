/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <stdio.h>
#include "pmu.h"

#define QSORT_SMALL 10000
#define QSORT_LARGE 1024		// TBD

// extern int qsort_small(const char *file);//, size_t size);
// extern int qsort_large(struct my3DVertexStruct *array, size_t size);
extern int bitcnts(int iterations);


// struct myStringStruct {		// QSORT_SMALL
//   char qstring[25];
// };


// struct my3DVertexStruct {	// QSORT_LARGE
//   int x, y, z;
//   double distance;
// };

// void clear_pmu(){
// 	unsigned long _temp = 0;
// 	__asm__ volatile ("mrc p15, 0, %0, c9, c12, 0\n\r": "=r"(_temp));
// 	_temp |= 0x4;
// 	__asm__ volatile ("mcr p15, 0, %0, c9, c12, 0\n\r": :"r"(_temp));
// }

// void set_pmu_clk_counter(){
// 	unsigned long _temp=0;
// 	__asm__ volatile ("mrc p15, 0, %0, c9, c12, 0\n\r": "=r"(_temp));	// PMCR.E = 1
// 	_temp |= 1;
// 	__asm__ volatile ("mcr p15, 0, %0, c9, c12, 0\n\r": :"r"(_temp));

// 	__asm__ volatile ("mrc p15, 0, %0, c9, c12, 1\n\r": "=r"(_temp));	// PMCNTENSET = 0x80000000
// 	_temp |= 0x80000000;
// 	__asm__ volatile ("mcr p15, 0, %0, c9, c12, 1\n\r": :"r"(_temp));
// }

// unsigned long getclk(){
// 	unsigned long _temp=0;
// 	__asm__ volatile ("mrc p15, 0, %0, c9, c13, 0\n\r": "=r"(_temp));
// 	printf("Clock cycles: %d\n", _temp);
// 	return _temp;
// }



#define SAMPLE_FORMAT   "%" XSTR(COL_SIZE) "lu"//"d"
#define HEADER_FORMAT   "%" XSTR(COL_SIZE) "s"

#define NUM_SAMPLES  (35)
#define NUM_WARMUPS  (10)
#define COL_SIZE      20
volatile size_t sample_count;

/*const size_t sample_events[] = {
    L1I_CACHE_REFILL ,
    L1I_CACHE_REFILL | EL2_ONLY,
    L1D_CACHE_REFILL,
    L1D_CACHE_REFILL | EL2_ONLY,
    L2D_CACHE_REFILL,
    L2D_CACHE_REFILL | EL2_ONLY,
    L1I_TLB_REFILL ,
    L1I_TLB_REFILL | EL2_ONLY,
    L1D_TLB_REFILL,
    L1D_TLB_REFILL | EL2_ONLY,
    MEM_ACCESS,
    MEM_ACCESS | EL2_ONLY,
    BUS_ACCESS,
    BUS_ACCESS | EL2_ONLY,
    EXC_TAKEN,
    EXC_TAKEN | EL2_ONLY,
    EXC_IRQ,
    EXC_IRQ | EL2_ONLY,
    INST_RETIRED,
    INST_RETIRED | EL2_ONLY,
};*/

const size_t sample_events[] = {
    L1I_CACHE_REFILL,
	KITE_I_UMPU_HIT,
    INST_RETIRED,
    BUS_ACCESS,
    // L1D_CACHE_REFILL,
	// KITE_D_UMPU_HIT,
    // MEM_ACCESS,
    // EXC_TAKEN,
    // EXC_IRQ,
    // EXC_TRAP_IRQ,
    // EXC_TRAP_FIQ,
    // KITE_EL2_ENTERED,
};

const size_t sample_events_size = sizeof(sample_events)/sizeof(size_t);
unsigned long pmu_samples[sizeof(sample_events)/sizeof(size_t)][NUM_SAMPLES];
unsigned long pmu_overflow[sizeof(sample_events)/sizeof(size_t)][NUM_SAMPLES];
unsigned long cycle_samples[sizeof(sample_events)/sizeof(size_t)][NUM_SAMPLES];
unsigned long long cycle_overflow[sizeof(sample_events)/sizeof(size_t)][NUM_SAMPLES];
// unsigned long pmu_dst_samples[sizeof(sample_events)/sizeof(size_t)][NUM_SAMPLES];
// unsigned long cycle_dst_samples[sizeof(sample_events)/sizeof(size_t)][NUM_SAMPLES];
volatile size_t pmu_used_counters = 0;

#define PMU_DEV_IRQ  23       /* device uses IRQ 23 */
#define PMU_DEV_PRIO 0 //2    /* device uses interrupt priority 2 */
/* argument passed to my_isr(), in this case a pointer to the device */
#define MY_ISR_ARG  DEVICE_GET(my_device)
#define MY_IRQ_FLAGS 0       /* IRQ flags */

/** @brief Cast @p x, an unsigned integer, to a <tt>void*</tt>. */
#define UINT_TO_POINTER(x) ((void *) (uintptr_t) (x))

// struct isr_counter{
//     unsigned long counter_overflow[4];
//     unsigned long cycle;
// } track;

// static void pmu_isr(void *arg)
// {
//     /* ISR code */
//     unsigned long isr = sysreg_pmovsr_read();
//     switch(isr)
//     {
//         case 1: track.counter_overflow[0] += 1; break;
//         case 2: track.counter_overflow[1] += 1; break;
//         case 4: track.counter_overflow[2] += 1; break;
//         case 8: track.counter_overflow[3] += 1; break;
//         case 0x80000000: track.cycle ++; break;
//         default:
//             break;
//     }
//     sysreg_pmovsr_write(0x8000000F);       // clear isr
// }


void pmu_setup_counters(size_t n, const size_t events[]){
    pmu_used_counters = n < pmu_num_counters()? n : pmu_num_counters();
    for(size_t i = 0; i < pmu_used_counters; i++){
        pmu_counter_set_event(i, events[i]);
        pmu_counter_enable(i);
    }
    pmu_cycle_enable(true);
}


void pmu_sample(size_t start) {
    size_t n = pmu_used_counters;
    for(int i = 0; i < pmu_used_counters; i++){
        pmu_samples[start+i][sample_count] = pmu_counter_get(i); 
//        pmu_overflow[start+i][sample_count] = track.counter_overflow[i];
    }
    cycle_samples[start/pmu_num_counters()][sample_count] = pmu_cycle_get();
/*  with ISR
    cycle_overflow[start/pmu_num_counters()][sample_count] = track.cycle;

    track.counter_overflow[0] = 0;
    track.counter_overflow[1] = 0;
    track.counter_overflow[2] = 0;
    track.counter_overflow[3] = 0;
    track.cycle = 0;
*/
}

/*void pmu_dst_sample(size_t start) {
    size_t n = pmu_used_counters;
    for(int i = 0; i < pmu_used_counters; i++){
        pmu_dst_samples[start+i][sample_count] = pmu_counter_get(i);
    }
     cycle_dst_samples[start/pmu_num_counters()][sample_count] = pmu_cycle_get();
}*/

void pmu_setup(size_t start, size_t n) {
    pmu_setup_counters(n, &sample_events[start]);

    // unsigned long pmu_temp= sysreg_pmcr_el0_read();     // long counter
    // pmu_temp = pmu_temp | 0x40;
    // sysreg_pmcr_el0_write(pmu_temp);

    pmu_reset();
    pmu_start();
}


static inline void pmu_print_header(size_t start) {
    size_t left_counters = sample_events_size - start;
    size_t n = left_counters < pmu_num_counters() ? left_counters : pmu_num_counters();
    for (size_t i = 0; i < n; i++) {
        uint32_t event = sample_events[start + i];
        char const * descr =  pmu_event_descr[event & 0xffff]; 
        descr = descr ? descr : "";
        uint32_t priv_code = (event >> 24) & 0xc8;
        const char * priv = priv_code == 0xc8 ? "_el2" : 
                            priv_code == 0x08 ? "_el1+2" :
                            "_el1";
        char buf[COL_SIZE];
        snprintf(buf, COL_SIZE-1, "%s%s", descr, priv);
        printf(HEADER_FORMAT, buf);
    }
    printf(HEADER_FORMAT, "cycles");
}

static inline void pmu_print_samples(size_t start, size_t i) {
    size_t left_counters = sample_events_size - start;
    size_t n = left_counters < pmu_num_counters() ? left_counters : pmu_num_counters();
    for (size_t j = 0; j < n; j++) {
        printf(SAMPLE_FORMAT, pmu_samples[start+j][i]);
    }
    printf(SAMPLE_FORMAT, cycle_samples[start/pmu_num_counters()][i]);

    // for (size_t j = 0; j < n; j++) {
    //     printf(SAMPLE_FORMAT, pmu_overflow[start+j][i]);
    // }
    // printf(SAMPLE_FORMAT, cycle_overflow[start/pmu_num_counters()][i]);
}

void print_samples() {

    for(size_t i = 0; i < sample_events_size; i+= pmu_num_counters()) {
        printf("--------------------------------\n");
        //printf(HEADER_FORMAT, "trap-lat");
        //printf(HEADER_FORMAT, "sgi-lat");
        pmu_print_header(i);
        printf("\n");
        for (size_t j = 0; j < NUM_SAMPLES; j++) {
            //printf(SAMPLE_FORMAT, ipi_lat_samples[i/pmu_num_counters()][j]);
            //printf(SAMPLE_FORMAT, sgi_lat_time[i/pmu_num_counters()][j]);
            pmu_print_samples(i, j);
            printf("\n");
        }
    }
    
}

int main(void)
{
    /************************ ISR ************************/
    // IRQ_CONNECT(PMU_DEV_IRQ, 0, pmu_isr, UINT_TO_POINTER(1), 0);
    // irq_enable(PMU_DEV_IRQ);
    // sysreg_pmintenset_write(0x8000000F);   //  Enable ISRs
    /******************************************************/

    pmu_setup(0, sample_events_size);

    for (size_t loop = 0; loop < (NUM_WARMUPS + NUM_SAMPLES); loop++)
    {
        /*********************************************************************/
        /*                               Bitcount                            */
        /*********************************************************************/

        bitcnts(75000); 	    //small
        // bitcnts(1125000);	//large


        /*********************************************************************/
        /*                              BasicMath                            */
        /*********************************************************************/

        // basicmath_small();
        // basicmath_large();       // Counter overflow

        /*********************************************************************/
        /*                                Susan                              */
        /*********************************************************************/

        unsigned char* var = 0x32400000;
        unsigned char* var = 0x32500000;
        unsigned char* var = 0x32600000;
        susan('c', var);
        susan('e', var);
        susan('s', var);

        /*********************************************************************/
        /*                             QSort Large                           */
        /*********************************************************************/

        struct my3DVertexStruct *data = 0x31830000;
        struct myStringStruct temp;
        char *ptr;
        ptr = (char*) 0x31845000;
        int j=0, stage = 0;

        while (*ptr != '\n' && j < QSORT_LARGE) {
            int i = 0;

            // Copy characters from ptr to temp[j].qstring
            while (*ptr != '\n' && *ptr != '\0' && i < 24 ) {
                if (*ptr == 0x9) {ptr++; break;}
                temp.qstring[i++] = *ptr++;
            }

            temp.qstring[i] = '\0'; // Terminate the string with the null character
            switch (stage){
                case 0: 
                    data[j].x = atoi(temp.qstring);
                    printf ("x = %d\n", data[j].x);
                    break;
                case 1:
                    data[j].y = atoi(temp.qstring);
                    printf ("y = %d\n", data[j].y);
                    break;
                case 2:
                    data[j].z = atoi(temp.qstring);
                    data[j].distance = sqrt(pow(data[j].x, 2) + pow(data[j].y, 2) + pow(data[j].z, 2));
                    stage = -1;
                    printf ("z = %d\n", data[j].z);
                    printf ("dist = %ld\n", data[j].distance);
                    break;
            }

            j++; stage++;
            if (j==10000) break;		// TBD
            if (*ptr == '\n') {
                ptr++; // Move past the newline character
            }
        }

	    qsort_large();


        /*********************************************************************/
        /*                             QSort Small                           */
        /*********************************************************************/	       
        
        qsort_small();

        sample_count = loop - NUM_WARMUPS;
        if(loop >= NUM_WARMUPS) {
            pmu_sample(0);
        }
        printf("\n\n\ntLOOP: %d\n\n", loop);
        pmu_reset();
        for (size_t i=0; i<pmu_num_counters(); i++)
            pmu_sample(i);
        print_samples();
        print_dst_samples();
	}

    // pmu_stop();
    // print_samples();

	return 0;
}
