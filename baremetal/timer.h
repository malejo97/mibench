#ifndef ARCH_TIMER_H
#define ARCH_TIMER_H

#include <stdint.h>
#include <sysregs.h>

extern uint64_t TIMER_FREQ;

static inline void timer_disable()
{
    //MSR(CNTV_CTL_EL0, 0);
    sysreg_cntv_ctl_el0_write(0);
}


static inline uint64_t timer_set(uint64_t n)
{
    //MSR(CNTV_TVAL_EL0, n);
    //MSR(CNTV_CTL_EL0, 1);
    //return MRS(CNTV_CVAL_EL0);
    sysreg_cntv_tval_el0_write(n);
    sysreg_cntv_ctl_el0_write(1);
    return sysreg_cntv_cval_read();
}

static inline  uint64_t timer_get()
{
    //uint64_t time = MRS(CNTPCT_EL0);
    uint64_t time = sysreg_cntpct_el0_read();
    return time; // assumes plat_freq = 100MHz
}

static inline  uint64_t timer_busy_wait(uint64_t n)
{
    //uint64_t time = MRS(CNTVCT_EL0) + n;
    uint64_t time = sysreg_cntvct_el0_read() + n;
    while (sysreg_cntvct_el0_read() < time);
}


#endif
