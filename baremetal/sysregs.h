/**
 * Bao, a Lightweight Static Partitioning Hypervisor
 *
 * Copyright (c) Bao Project (www.bao-project.org), 2019-
 *
 * Authors:
 *      Jose Martins <jose.martins@bao-project.org>
 *
 * Bao is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation, with a special exception exempting guest code from such
 * license. See the COPYING file in the top-level directory for details.
 *
 */

#ifndef __ARCH_SYSREGS_H__
#define __ARCH_SYSREGS_H__

/* ID_AA64MMFR0_EL1, AArch64 Memory Model Feature Register 0 */
#define ID_AA64MMFR0_PAR_OFF 0
#define ID_AA64MMFR0_PAR_LEN 4
#define ID_AA64MMFR0_PAR_MSK \
    BIT_MASK(ID_AA64MMFR0_PAR_OFF, ID_AA64MMFR0_PAR_LEN)

#define SPSel_SP (1 << 0)

/* PSTATE */

#define PSTATE_DAIF_I_BIT (1UL << 1)

/* MPIDR_EL1, Multiprocessor Affinity Register */

#define MPIDR_RES1 (0x80000000)
#define MPIDR_CPU_MASK MPIDR_AFFLVL_MASK
#define MPIDR_CLUSTER_MASK (MPIDR_AFFLVL_MASK << MPIDR_AFFINITY_BITS)
#define MPIDR_AFFINITY_BITS (8)
#define MPIDR_AFFLVL_MASK (0xff)
#define MPIDR_U_BIT (1UL << 30)

/* SPSR - Saved Program Status Register */

#define SPSR_EL_MSK (0x0f)
#define SPSR_EL0t (0x0)
#define SPSR_EL1t (0x4)
#define SPSR_EL1h (0x5)
#define SPSR_EL2t (0x8)
#define SPSR_EL2h (0x9)
#define SPSR_EL3t (0xc)
#define SPSR_EL3h (0xd)

#define SPSR_F (1 << 6)
#define SPSR_I (1 << 7)
#define SPSR_A (1 << 8)
#define SPSR_D (1 << 9)
#define SPSR_IL (1 << 20)
#define SPSR_SS (1 << 21)

/* SCR - Secure Configuration Register */

#define SCR_NS (1 << 0)
#define SCR_IRQ (1 << 1)
#define SCR_FIQ (1 << 2)
#define SCR_EA (1 << 3)
#define SCR_SMD (1 << 7)
#define SCR_HCE (1 << 8)
#define SCR_SIF (1 << 9)
#define SCR_RW (1 << 10)
#define SCR_ST (1 << 11)
#define SCR_TWI (1 << 12)
#define SCR_TWE (1 << 13)
#define SCR_TLOR (1 << 14)
#define SCR_TERR (1 << 15)
#define SCR_APK (1 << 16)
#define SCR_API (1 << 17)

/* TCR - Translation Control Register */

#define TCR_RES1 ((1 << 23) | (1 << 31))
#define TCR_T0SZ_MSK (0x1f << 0)
#define TCR_T0SZ_OFF (0)
#define TCR_T0SZ(SZ) ((SZ << TCR_T0SZ_OFF) & TCR_T0SZ_MSK)
#define TCR_IRGN0_MSK (0x3 << 8)
#define TCR_IRGN0_NC (0 << 8)
#define TCR_IRGN0_WB_RA_WA (1 << 8)
#define TCR_IRGN0_WT_RA_NWA (2 << 8)
#define TCR_IRGN0_WB_RA_NWA (3 << 8)
#define TCR_ORGN0_MSK (0x3 << 10)
#define TCR_ORGN0_NC (0 << 10)
#define TCR_ORGN0_WB_RA_WA (1 << 10)
#define TCR_ORGN0_WT_RA_NWA (2 << 10)
#define TCR_ORGN0_WB_RA_NWA (3 << 10)
#define TCR_SH0_MSK (0x3 << 12)
#define TCR_SH0_NS (0 << 12)
#define TCR_SH0_IS (2 << 12)
#define TCR_SH0_OS (3 << 12)
#define TCR_TG0_MSK (0x3 << 14)
#define TCR_TG0_4K (0 << 14)
#define TCR_TG0_16K (2 << 14)
#define TCR_TG0_64K (1 << 14)
#define TCR_PS_OFF (16)
#define TCR_PS_MSK (0x7 << TCR_PS_OFF)
#define TCR_PS_32B (0 << 16)
#define TCR_PS_36B (1 << 16)
#define TCR_PS_40B (2 << 16)
#define TCR_PS_42B (3 << 16)
#define TCR_PS_44B (4 << 16)
#define TCR_PS_48B (5 << 16)
#define TCR_PS_52B (6 << 16)
#define TCR_TBI (1 << 20)

/**
 * Default hypervisor translation control
 * The PS field must be filled at runtime by first reading parange
 */
#define TCR_EL2_DFLT                                           \
    (TCR_RES1 | TCR_TG0_4K | TCR_PS_48B | TCR_ORGN0_WB_RA_WA | \
     TCR_IRGN0_WB_RA_WA | TCR_T0SZ(16) | TCR_SH0_IS)

/* TCR - Translation Control Register */

#define VTCR_RES1 (1UL << 31)
#define VTCR_T0SZ_MSK (0x1f << 0)
#define VTCR_T0SZ_OFF (0)
#define VTCR_T0SZ(SZ) (((SZ) << TCR_T0SZ_OFF) & TCR_T0SZ_MSK)
#define VTCR_SL0_OFF (6)
#define VTCR_SL0_MSK (0xc0)
#define VTCR_SL0_01 ((0x2UL << VTCR_SL0_OFF) & VTCR_SL0_MSK)
#define VTCR_SL0_12 ((0x1UL << VTCR_SL0_OFF) & VTCR_SL0_MSK)
#define VTCR_SL0_23 (0)
#define VTCR_IRGN0_MSK (0x3 << 8)
#define VTCR_IRGN0_NC (0 << 8)
#define VTCR_IRGN0_WB_RA_WA (1 << 8)
#define VTCR_IRGN0_WT_RA_NWA (2 << 8)
#define VTCR_IRGN0_WB_RA_NWA (3 << 8)
#define VTCR_ORGN0_MSK (0x3 << 10)
#define VTCR_ORGN0_NC (0 << 10)
#define VTCR_ORGN0_WB_RA_WA (1 << 10)
#define VTCR_ORGN0_WT_RA_NWA (2 << 10)
#define VTCR_ORGN0_WB_RA_NWA (3 << 10)
#define VTCR_SH0_MSK (0x3 << 12)
#define VTCR_SH0_NS (0 << 12)
#define VTCR_SH0_IS (2 << 12)
#define VTCR_SH0_OS (3 << 12)
#define VTCR_TG0_MSK (0x3 << 14)
#define VTCR_TG0_4K (0 << 14)
#define VTCR_TG0_16K (2 << 14)
#define VTCR_TG0_64K (1 << 14)
#define VTCR_PS_OFF (16)
#define VTCR_PS_MSK (0x7 << VTCR_PS_OFF)
#define VTCR_PS_32B (0 << 16)
#define VTCR_PS_36B (1 << 16)
#define VTCR_PS_40B (2 << 16)
#define VTCR_PS_42B (3 << 16)
#define VTCR_PS_44B (4 << 16)
#define VTCR_PS_48B (5 << 16)
#define VTCR_PS_52B (6 << 16)
#define VTCR_TBI (1 << 20)

/**
 * Default stage-2 translation control
 * ...
 */
#define VTCR_DFLT                                                  \
    (VTCR_RES1 | VTCR_PS_40B | VTCR_TG0_4K | VTCR_ORGN0_WB_RA_WA | \
     VTCR_IRGN0_WB_RA_WA | VTCR_T0SZ(24) | VTCR_SLO_12 | VTCR_SH0_IS)

/*  MAIR - Memory Attribute Indirection Register */

#define MAIR_ATTR_WIDTH (8)
#define MAIT_ATTR_NUM (8)

#define MAIR_DEV_nGnRnE (0x0 << 2)
#define MAIR_DEV_nGnRE (0x1 << 2)
#define MAIR_DEV_nGRE (0x2 << 2)
#define MAIR_DEV_GRE (0x3 << 2)

#define MAIR_OWTT (0x0 << 6)
#define MAIR_ONC (0x1 << 6)
#define MAIR_OWBT (0x1 << 6)
#define MAIR_OWTNT (0x2 << 6)
#define MAIR_OWBNT (0x3 << 6)
#define MAIR_ORA (0x1 << 5)
#define MAIR_OWA (0x1 << 4)

#define MAIR_IWTT (0x0 << 2)
#define MAIR_INC (0x1 << 2)
#define MAIR_IWBT (0x1 << 2)
#define MAIR_IWTNT (0x2 << 2)
#define MAIR_IWBNT (0x3 << 2)
#define MAIR_IRA (0x1 << 1)
#define MAIR_IWA (0x1 << 0)

/**
* Default hypervisor memory attributes
* 0 -> Device-nGnRnE
* 1 -> Normal, Inner/Outer  WB/WA/RA
* 2 -> Device-nGnRE
*/
#define MAIR_EL1_DFLT    (\
    ((MAIR_OWBNT | MAIR_ORA | MAIR_OWA | MAIR_IWBNT | MAIR_IRA | MAIR_IWA)\
        << MAIR_ATTR_WIDTH) |\
    ((MAIR_DEV_nGnRE) << (MAIR_ATTR_WIDTH*2))\
)

/**
 * Default hypervisor memory attributes
 * 0 -> Device-nGnRnE
 * 1 -> Normal, Inner/Outer  WB/WA/RA
 * 2 -> Device-nGnRE
 */
#define MAIR_EL2_DFLT                                                       \
    (((MAIR_OWBNT | MAIR_ORA | MAIR_OWA | MAIR_IWBNT | MAIR_IRA | MAIR_IWA) \
      << MAIR_ATTR_WIDTH) |                                                 \
     ((MAIR_DEV_nGnRE) << (MAIR_ATTR_WIDTH * 2)))

/* PAR -  Physical Address Register */

#define PAR_ATTR_OFF (56)
#define PAR_ATTR_MSK (0xffUL << PAR_ATTR_OFF)
#define PAR_PA_OFF (12)
#define PAR_PA_MSK (0x3ffffffUL << PAR_PA_OFF)
#define PAR_RES1 (0x1UL << 11)
#define PAR_IMPDEF (0x1UL << 10)
#define PAR_NS (0x1UL << 9)
#define PAR_SH_OFF (7)
#define PAR_SH_MSK (0x3UL << PAR_SH_OFF)
#define PAR_F (0x1UL << 0)

/* SCTLR - System Control Register */

#define SCTLR_RES1 (0x30C50830)
#define SCTLR_M (1 << 0)
#define SCTLR_A (1 << 1)
#define SCTLR_C (1 << 2)
#define SCTLR_SA (1 << 3)
#define SCTLR_I (1 << 12)
#define SCTLR_WXN (1 << 19)
#define SCTLR_EE (1 << 25)

/* CLIDR - Cache Level ID Register */

#define CLIDR_CTYPE_LEN (0x03)
#define CLIDR_CTYPE_NUM (0x07)
#define CLIDR_CTYPE_NO 0
#define CLIDR_CTYPE_IO 1
#define CLIDR_CTYPE_DO 2
#define CLIDR_CTYPE_SP 3
#define CLIDR_CTYPE_UN 4

/* CTR_EL0 - Cache Type Register */

#define CTR_IMINLINE_OFF 0
#define CTR_IMINLINE_LEN 4
#define CTR_L1LP_OFF 14
#define CTR_L1LP_LEN 2
#define CTR_L1LP_AIVIVT (0x1UL << CTR_L1LP_OFF)
#define CTR_L1LP_VIPT (0x2UL << CTR_L1LP_OFF)
#define CTR_L1LP_PIPT (0x3UL << CTR_L1LP_OFF)
#define CTR_DMINLINE_OFF 16
#define CTR_DMINLINE_LEN 4
#define CTR_ERG_OFF 20
#define CTR_ERG_LEN 4
#define CTR_CEG_OFF 24
#define CTR_CEG_LEN 4
#define CTR_RES1 (1UL << 31)

/* CSSELR_EL1 - Cache Size Selection Register */

#define CSSELR_IND_BIT 0
#define CSSELR_LVL_OFF 1
#define CSSELR_LVL_LEN 3

/* CCSIDR_EL1 - Current Cache Size ID Register */

#define CCSIDR_LINESIZE_OFF 0
#define CCSIDR_LINESIZE_LEN 3
#define CCSIDR_ASSOCIATIVITY_OFF 3
#define CCSIDR_ASSOCIATIVITY_LEN 10
#define CCSIDR_NUMSETS_OFF 13
#define CCSIDR_NUMSETS_LEN 15

/**
 * Below are platform implementation registers related to a53.
 * TODO: move them to a a53 specific file.
 */

/* CPUECTLR_EL1 - CPU Extended Control Register  */

#define CPUECTLR_EL1 S3_1_c15_c2_1
#define CPUECTLR_SPEN_BIT (1UL << 6)

/* ACTLR - Auxiliary Control Register */

#define ACTLR_CPUACTLR_BIT (1UL << 0)
#define ACTLR_CPUECTLR_BIT (1UL << 1)
#define ACTLR_L2CTLR_BIT (1UL << 4)
#define ACTLR_L2ECTLR_BIT (1UL << 5)
#define ACTLR_L2ACTLR_BIT (1UL << 6)

/* HCR_EL2 - Hypervisor Configuration Register */

#define HCR_VM_BIT (1UL << 0)
#define HCR_SWIO_BIT (1UL << 1)
#define HCR_PTW_BIT (1UL << 2)
#define HCR_FMO_BIT (1UL << 3)
#define HCR_IMO_BIT (1UL << 4)
#define HCR_AMO_BIT (1UL << 5)
#define HCR_VF_BIT (1UL << 6)
#define HCR_VI_BIT (1UL << 7)
#define HCR_VSE_BIT (1UL << 8)
#define HCR_FB_BIT (1UL << 9)
#define HCR_BSU_BIT (1UL << 10)
#define HCR_DC_BIT (1UL << 12)
#define HCR_TWI_BIT (1UL << 13)
#define HCR_TWE_BIT (1UL << 14)
#define HCR_TID0_BIT (1UL << 15)
#define HCR_TID1_BIT (1UL << 16)
#define HCR_TID2_BIT (1UL << 17)
#define HCR_TID3_BIT (1UL << 18)
#define HCR_TSC_BIT (1UL << 19)
#define HCR_TIDCP_BIT (1UL << 20)
#define HCR_TACR_BIT (1UL << 21)
#define HCR_TSW_BIT (1UL << 22)
#define HCR_TPC_BIT (1UL << 23)
#define HCR_TPU_BIT (1UL << 24)
#define HCR_TTLB_BIT (1UL << 25)
#define HCR_TVM_BIT (1UL << 26)
#define HCR_TGE_BIT (1UL << 27)
#define HCR_TDZ_BIT (1UL << 28)
#define HCR_HCD_BIT (1UL << 29)
#define HCR_TRVM_BIT (1UL << 30)
#define HCR_RW_BIT (1UL << 31)
#define HCR_CD_BIT (1UL << 32)
#define HCR_ID_BIT (1UL << 33)
#define HCR_TERR_BIT (1UL << 36)
#define HCR_TEA_BIT (1UL << 37)
#define HCR_MIOCNCE_BIT (1UL << 38)

/* ESR_ELx, Exception Syndrome Register (ELx) */

#define ESR_ISS_OFF (0)
#define ESR_ISS_LEN (25)
#define ESR_IL_OFF (25)
#define ESR_IL_LEN (1)
#define ESR_EC_OFF (26)
#define ESR_EC_LEN (6)

#define ESR_EC_UNKWN (0x00)
#define ESR_EC_WFIE (0x01)
#define ESR_EC_SVC32 (0x11)
#define ESR_EC_HVC32 (0x12)
#define ESR_EC_SMC32 (0x13)
#define ESR_EC_SVC64 (0x15)
#define ESR_EC_HVC64 (0x16)
#define ESR_EC_SMC64 (0x17)
#define ESR_EC_IALEL (0x20)
#define ESR_EC_IASEL (0x21)
#define ESR_EC_PCALG (0x22)
#define ESR_EC_DALEL (0x24)
#define ESR_EC_DASEL (0x25)
#define ESR_EC_SPALG (0x26)

#define ESR_ISS_DA_DSFC_OFF (0)
#define ESR_ISS_DA_DSFC_LEN (6)
#define ESR_ISS_DA_WnR_OFF (6)
#define ESR_ISS_DA_WnR_LEN (1)
#define ESR_ISS_DA_WnR_BIT (1 << 6)
#define ESR_ISS_DA_S1PTW_OFF (7)
#define ESR_ISS_DA_S1PTW_LEN (1)
#define ESR_ISS_DA_CM_OFF (8)
#define ESR_ISS_DA_CM_LEN (1)
#define ESR_ISS_DA_EA_OFF (9)
#define ESR_ISS_DA_EA_LEN (1)
#define ESR_ISS_DA_FnV_OFF (10)
#define ESR_ISS_DA_FnV_LEN (1)
#define ESR_ISS_DA_FnV_BIT (1UL << 10)
#define ESR_ISS_DA_SET_OFF (11)
#define ESR_ISS_DA_SET_LEN (2)
#define ESR_ISS_DA_AR_OFF (14)
#define ESR_ISS_DA_AR_LEN (1)
#define ESR_ISS_DA_SF_OFF (15)
#define ESR_ISS_DA_SF_LEN (1)
#define ESR_ISS_DA_SRT_OFF (16)
#define ESR_ISS_DA_SRT_LEN (5)
#define ESR_ISS_DA_SSE_OFF (21)
#define ESR_ISS_DA_SSE_LEN (1)
#define ESR_ISS_DA_SAS_OFF (22)
#define ESR_ISS_DA_SAS_LEN (2)
#define ESR_ISS_DA_ISV_OFF (24)
#define ESR_ISS_DA_ISV_LEN (1)
#define ESR_ISS_DA_ISV_BIT (1UL << 24)

#define ESR_ISS_DA_DSFC_CODE (0xf << 2)
#define ESR_ISS_DA_DSFC_ADDRSZ (0x0)
#define ESR_ISS_DA_DSFC_TRNSLT (0x4)
#define ESR_ISS_DA_DSFC_ACCESS (0x8)
#define ESR_ISS_DA_DSFC_PERMIS (0xC)

/* VTTBR_EL2, Virtualization Translation Table Base Register */

#define VTTBR_VMID_OFF 48
#define VTTBR_VMID_LEN 8
#define VTTBR_VMID_MSK BIT_MASK(VTTBR_VMID_OFF, VTTBR_VMID_LEN)

#define CPUACTLR_EL1 S3_1_C15_C2_0

/* GICC System Register Interface Definitions */

#define ICC_PMR_EL1         S3_0_C4_C6_0           
#define ICC_IAR0_EL1        S3_0_C12_C8_0        
#define ICC_EOIR0_EL1       S3_0_C12_C8_1        
#define ICC_HPPIR0_EL1      S3_0_C12_C8_2        
#define ICC_BPR0_EL1        S3_0_C12_C8_3        
// #define ICC_AP0R<n>_EL1     S3_0_C12_C8_        
// #define ICC_AP1R<n>_EL1     S3_0_C12_C9_        
#define ICC_DIR_EL1         S3_0_C12_C11_1    
#define ICC_RPR_EL1         S3_0_C12_C11_3    
#define ICC_SGI1R_EL1       S3_0_C12_C11_5        
#define ICC_ASGI1R_EL1      S3_0_C12_C11_6        
#define ICC_SGI0R_EL1       S3_0_C12_C11_7        
#define ICC_IAR1_EL1        S3_0_C12_C12_0        
#define ICC_EOIR1_EL1       S3_0_C12_C12_1        
#define ICC_HPPIR1_EL1      S3_0_C12_C12_2        
#define ICC_BPR1_EL1        S3_0_C12_C12_3        
#define ICC_CTLR_EL1        S3_0_C12_C12_4        
#define ICC_SRE_EL1         S3_0_C12_C12_5    
#define ICC_IGRPEN0_EL1     S3_0_C12_C12_6        
#define ICC_IGRPEN1_EL1     S3_0_C12_C12_7        
#define ICC_SRE_EL2         S3_4_C12_C9_5    
#define ICC_CTLR_EL3        S3_6_C12_C12_4 
#define ICC_SRE_EL3         S3_6_C12_C12_5
#define ICC_IGRPEN1_EL3     S3_6_C12_C12_7

// #define ICH_AP0R<n>_EL2     S3_4_C12_C8 _0-3
// #define ICH_AP1R<n>_EL2     S3_4_C12_C9 _0-3
#define ICH_HCR_EL2         S3_4_C12_C11_0
#define ICH_VTR_EL2         S3_4_C12_C11_1
#define ICH_MISR_EL2        S3_4_C12_C11_2
#define ICH_EISR_EL2        S3_4_C12_C11_3
#define ICH_ELRSR_EL2       S3_4_C12_C11_5
#define ICH_VMCR_EL2        S3_4_C12_C11_7
#define ICH_LR0_EL2         S3_4_C12_C12_0
#define ICH_LR1_EL2         S3_4_C12_C12_1
#define ICH_LR2_EL2         S3_4_C12_C12_2
#define ICH_LR3_EL2         S3_4_C12_C12_3
#define ICH_LR4_EL2         S3_4_C12_C12_4
#define ICH_LR5_EL2         S3_4_C12_C12_5
#define ICH_LR6_EL2         S3_4_C12_C12_6
#define ICH_LR7_EL2         S3_4_C12_C12_7
#define ICH_LR8_EL2         S3_4_C12_C13_0
#define ICH_LR9_EL2         S3_4_C12_C13_1
#define ICH_LR10_EL2        S3_4_C12_C13_2
#define ICH_LR11_EL2        S3_4_C12_C13_3
#define ICH_LR12_EL2        S3_4_C12_C13_4
#define ICH_LR13_EL2        S3_4_C12_C13_5
#define ICH_LR14_EL2        S3_4_C12_C13_6
#define ICH_LR15_EL2        S3_4_C12_C13_7

#define ICC_SRE_ENB_BIT  (0x8)
#define ICC_SRE_DIB_BIT  (0x4)
#define ICC_SRE_DFB_BIT  (0x2)
#define ICC_SRE_SRE_BIT  (0x1)

#define ICC_IGRPEN_EL1_ENB_BIT (0x1)

//#ifndef __ASSEMBLER__

#define STR(str) #str
#define XSTR(S) STR(S)

#define SYSREG_GEN_ACCESSORS(name, op1, crn, crm, op2) \
    static inline unsigned long sysreg_##name##_read() {\
        unsigned long _temp;\
        __asm__ volatile("mrc p15, "#op1", %0, "#crn", "#crm", %1\n\r": "=r"(_temp): "i"(op2));\
        return _temp;\
    } \
    static inline void sysreg_##name##_write(unsigned long val) {\
        __asm__ volatile("mcr p15, "#op1", %0, "#crn", "#crm", "#op2"\n\r": :"r"((val)));\
    }


#define SYSREG_GEN_ACCESSORS_64(reg, op1, crm) \
    static inline unsigned long long sysreg_##reg##_read() {\
        unsigned long long _temp, _tempH;\
        __asm__ volatile("mrrc p15, "#op1", %0, %1, "#crm"\n\r": "=r"(_temp), "=r"(_tempH));\
        return ((_tempH << 32) | _temp);\
    } \
    static inline void sysreg_##reg##_write(unsigned long long val) {\
        unsigned long long _tempH = (val>>32);\
        __asm__ volatile("mcrr p15, "#op1", %0, %1, "#crm"\n\r": :"r"(val), "r"(_tempH));\
    }

#define SYSREG_GEN_ACCESSORS_MERGE(reg, reg1, reg2) \
    static inline unsigned long long sysreg_##reg##_read() {\
        return ((unsigned long long)sysreg_##reg2##_read() << 32) |\
            sysreg_##reg1##_read();\
    }\
    static inline void sysreg_##reg##_write(unsigned long long val) {\
        sysreg_##reg1##_write(val);\
        sysreg_##reg2##_write(val >> 32);\
    }


/**
 * We give aarch32 registers the same name as aarch64's to which they are 
 * architecturally mapped to, so that we can use the same name in common code.
 */
SYSREG_GEN_ACCESSORS(esr_el2, 4, c5, c2, 0); // hsr
//SYSREG_GEN_ACCESSORS_BANKED(elr_el2, elr_hyp);
SYSREG_GEN_ACCESSORS(far_el2, 4, c6, c0, 0); // hdfar
SYSREG_GEN_ACCESSORS(hpfar_el2, 4, c6, c0, 4);
SYSREG_GEN_ACCESSORS(clidr_el1, 1, c0, c0, 1);
SYSREG_GEN_ACCESSORS(csselr_el1, 2, c0, c0, 0);
SYSREG_GEN_ACCESSORS(ctr_el0, 0, c0, c0, 1);
SYSREG_GEN_ACCESSORS(mpidr_el1, 0, c0, c0, 5);
SYSREG_GEN_ACCESSORS(vmpidr_el2, 4, c0, c0, 5);
SYSREG_GEN_ACCESSORS_64(cntvoff_el2, 4, c14);
SYSREG_GEN_ACCESSORS(sctlr_el1, 0, c1, c0, 0); 
SYSREG_GEN_ACCESSORS(cntkctl_el1, 0, c14, c1, 0);
//SYSREG_GEN_ACCESSORS(pmcr_el0, 0, c9, c12, 0);
SYSREG_GEN_ACCESSORS_64(par_el1, 0, c7);
SYSREG_GEN_ACCESSORS(tcr_el2, 4, c2, c0, 2); // htcr
SYSREG_GEN_ACCESSORS_64(ttbr0_el2, 4, c2); // httbr
SYSREG_GEN_ACCESSORS(cptr_el2, 4, c1, c1, 2); // hcptr
SYSREG_GEN_ACCESSORS(vtcr_el2, 4, c2, c1, 2);
SYSREG_GEN_ACCESSORS_64(vttbr_el2, 6, c2);
SYSREG_GEN_ACCESSORS(tpidr_el2, 4, c13, c0, 2); // htpidr
SYSREG_GEN_ACCESSORS(ccsidr_el1, 1, c0, c0, 0);
SYSREG_GEN_ACCESSORS(ccsidr2, 1, c0, c0, 2);
SYSREG_GEN_ACCESSORS(hmair0, 4, c10, c2, 0);
SYSREG_GEN_ACCESSORS(hmair1, 4, c10, c2, 1);
SYSREG_GEN_ACCESSORS_MERGE(mair_el2, hmair0, hmair1);
SYSREG_GEN_ACCESSORS(hcr, 4, c1, c1, 0);
SYSREG_GEN_ACCESSORS(hcr2, 4, c6, c0, 0);
SYSREG_GEN_ACCESSORS_MERGE(hcr_el2, hcr, hcr2);
SYSREG_GEN_ACCESSORS(cntfrq_el0, 0, c14, c0, 0);
SYSREG_GEN_ACCESSORS(actlr_el2, 4, c1, c0, 1); // hactlr

SYSREG_GEN_ACCESSORS(mpuir_el2, 4, c0, c0, 4);
SYSREG_GEN_ACCESSORS(prselr_el2, 4, c6, c2, 1);
SYSREG_GEN_ACCESSORS(prbar_el2, 4, c6, c3, 0);
SYSREG_GEN_ACCESSORS(prlar_el2, 4, c6, c3, 1);
SYSREG_GEN_ACCESSORS(prenr_el2, 4, c6, c1, 1);

/*  PMU  */
SYSREG_GEN_ACCESSORS(pmcr_el0, 0, C9, C12, 0);
SYSREG_GEN_ACCESSORS(pmselr_el0, 0, C9, C12, 5);
SYSREG_GEN_ACCESSORS(pmxevtyper_el0, 0, C9, C13, 1);
SYSREG_GEN_ACCESSORS(pmxevcntr_el0, 0, C9, C13, 2);
SYSREG_GEN_ACCESSORS(pmcntenset_el0, 0, C9, C12, 1);
SYSREG_GEN_ACCESSORS(pmcntenclr_el0, 0, C9, C12, 2);
SYSREG_GEN_ACCESSORS(pmccntr_el0, 0, C9, C13, 0);
SYSREG_GEN_ACCESSORS(pmintenset, 0, c9, c14, 1);
SYSREG_GEN_ACCESSORS(pmovsr, 0, c9, c12, 3);

SYSREG_GEN_ACCESSORS(ich_misr_el2, 4, c12, c11, 2);
SYSREG_GEN_ACCESSORS(ich_eisr_el2, 4, c12, c11, 3);
SYSREG_GEN_ACCESSORS(ich_elrsr_el2, 4, c12, c11, 5);
SYSREG_GEN_ACCESSORS(icc_iar1_el1, 0, c12, c12, 0);
SYSREG_GEN_ACCESSORS(icc_eoir1_el1, 0, c12, c12, 1);
SYSREG_GEN_ACCESSORS(icc_dir_el1, 0, c12, c11, 1);
SYSREG_GEN_ACCESSORS(ich_vtr_el2, 4, c12, c11, 1);
SYSREG_GEN_ACCESSORS(icc_sre_el2, 4, c12, c9, 5);
SYSREG_GEN_ACCESSORS(icc_pmr_el1, 0, c4, c6, 0);
SYSREG_GEN_ACCESSORS(icc_bpr1_el1, 0, c12, c12, 3);
SYSREG_GEN_ACCESSORS(icc_ctlr_el1, 0, c12, c12, 4);
SYSREG_GEN_ACCESSORS(icc_igrpen1_el1, 0, c12, c12, 7);
SYSREG_GEN_ACCESSORS(ich_hcr_el2, 4, c12, c11, 0);
SYSREG_GEN_ACCESSORS_64(icc_sgi1r_el1, 0, c12);

SYSREG_GEN_ACCESSORS(vsctlr_el2, 4, c2, c0, 0);
SYSREG_GEN_ACCESSORS(iciallu, 0, c7, c5, 0);
SYSREG_GEN_ACCESSORS(dcimvac, 0, c7, c6, 1);
//mcr p15, 0, r10, c7, c5, 0 // invalidate ICache

/*   Timer   */
SYSREG_GEN_ACCESSORS(cntv_ctl_el0, 0, c14, c3, 1);
SYSREG_GEN_ACCESSORS(cntv_tval_el0, 0, c14, c3, 0);
SYSREG_GEN_ACCESSORS_64(cntpct_el0, 0, c14);
SYSREG_GEN_ACCESSORS_64(cntv_cval, 3, c14);
SYSREG_GEN_ACCESSORS_64(cntvct_el0, 1, c14);

//#endif /* |__ASSEMBLER__ */

#endif /* __ARCH_SYSREGS_H__ */
