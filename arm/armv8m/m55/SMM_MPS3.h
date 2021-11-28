/*
 * Copyright:
 * ----------------------------------------------------------------
 // The confidential and proprietary information contained in this file may
// only be used by a person authorised under and to the extent permitted
// by a subsisting licensing agreement from Arm Limited or its affiliates.
//
//        (C) COPYRIGHT 2016-2021 Arm Limited or its affiliates.
//            ALL RIGHTS RESERVED
//
// This entire notice must be reproduced on all copies of this file
// and copies of this file may only be made by a person if such person is
// permitted to do so under the terms of a subsisting license agreement
// from Arm Limited or its affiliates.
 * ----------------------------------------------------------------
 * File:     smm_mps3.h
 * Release:  Version 1.0
 * ----------------------------------------------------------------
 */

#ifndef __SMM_MPS3_H
#define __SMM_MPS3_H

//#include "cmsis.h"
#define __IO volatile
#define __I volatile const
#define __O volatile

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/******************************************************************************/
/*                          FPGA System Register declaration                  */
/******************************************************************************/

typedef struct                   
{
  __IO uint32_t LED;             // Offset: 0x000 (R/W)  LED connections
                                 //                         [31:2] : Reserved
                                 //                          [1:0] : LEDs
       uint32_t RESERVED1[1];
  __IO uint32_t BUTTON;          // Offset: 0x008 (R/W)  Buttons
                                 //                         [31:2] : Reserved
                                 //                          [1:0] : Buttons
       uint32_t RESERVED2[1];
  __IO uint32_t CLK1HZ;          // Offset: 0x010 (R/W)  1Hz up counter
  __IO uint32_t CLK100HZ;        // Offset: 0x014 (R/W)  100Hz up counter
  __IO uint32_t COUNTER;         // Offset: 0x018 (R/W)  Cycle Up Counter
                                 //                         Increments when 32-bit prescale counter reach zero
  __IO uint32_t PRESCALE;        // Offset: 0x01C (R/W)  Prescaler
                                 //                         Bit[31:0] : reload value for prescale counter
  __IO uint32_t PSCNTR;          // Offset: 0x020 (R/W)  32-bit Prescale counter
                                 //                         current value of the pre-scaler counter
                                 //                         The Cycle Up Counter increment when the prescale down counter reach 0
                                 //                         The pre-scaler counter is reloaded with PRESCALE after reaching 0.
       uint32_t RESERVED3[1];
  __IO uint32_t SWITCHES;        // Offset: 0x028 (R/W)  Switches
                                 //                         [31:8] : Reserved
                                 //                          [7:0] : Switches
       uint32_t RESERVED4[8];
  __IO uint32_t MISC;            // Offset: 0x04C (R/W)  Misc control */
                                 //                         [31:10] : Reserved
                                 //                            [9] : SHIELD_1_SPI_nCS
                                 //                            [8] : SHIELD_0_SPI_nCS
                                 //                            [7] : ADC_SPI_nCS
                                 //                            [6] : CLCD_BL_CTRL
                                 //                            [5] : CLCD_RD
                                 //                            [4] : CLCD_RS
                                 //                            [3] : CLCD_RESET
                                 //                            [2] : RESERVED
                                 //                            [1] : SPI_nSS
                                 //                            [0] : CLCD_CS
} MPS3_FPGAIO_TypeDef;

// MISC register bit definitions

#define CLCD_CS_Pos        0
#define CLCD_CS_Msk        (1UL<<CLCD_CS_Pos)
#define CLCD_WR_Pos        1
#define CLCD_WR_Msk        (1UL<<CLCD_WR_Pos)
#define CLCD_RESET_Pos     3
#define CLCD_RESET_Msk     (1UL<<CLCD_RESET_Pos)
#define CLCD_RS_Pos        4
#define CLCD_RS_Msk        (1UL<<CLCD_RS_Pos)
#define CLCD_RD_Pos        5
#define CLCD_RD_Msk        (1UL<<CLCD_RD_Pos)
#define CLCD_BL_Pos        6
#define CLCD_BL_Msk        (1UL<<CLCD_BL_Pos)
#define ADC_nCS_Pos        7
#define ADC_nCS_Msk        (1UL<<ADC_nCS_Pos)
#define SHIELD_0_nCS_Pos        8
#define SHIELD_0_nCS_Msk        (1UL<<SHIELD_0_nCS_Pos)
#define SHIELD_1_nCS_Pos        9
#define SHIELD_1_nCS_Msk        (1UL<<SHIELD_1_nCS_Pos)

/******************************************************************************/
/*                        SCC Register declaration                            */
/******************************************************************************/

typedef struct                   // 
{
  __IO uint32_t CFG_REG0;        // Offset: 0x000 (R/W)  Remaps block RAM to ZBT
                                 //                         [31:1] : Reserved
                                 //                            [0] 1 : REMAP BlockRam to ZBT
  __IO uint32_t LEDS;            // Offset: 0x004 (R/W)  Controls the MCC user LEDs
                                 //                         [31:8] : Reserved
                                 //                          [7:0] : MCC LEDs
       uint32_t RESERVED0[1];
  __I  uint32_t SWITCHES;        // Offset: 0x00C (R/ )  Denotes the state of the MCC user switches
                                 //                         [31:8] : Reserved
                                 //                          [7:0] : These bits indicate state of the MCC switches
  __I  uint32_t CFG_REG4;        // Offset: 0x010 (R/ )  Denotes the board revision
                                 //                         [31:4] : Reserved
                                 //                          [3:0] : Used by the MCC to pass PCB revision. 0 = A 1 = B
  __I  uint32_t CFG_ACLK;        // Offset: 0x014 (R/ )  System Clock
       uint32_t RESERVED1[34];
  __IO uint32_t SYS_CFGDATA_RTN; // Offset: 0x0A0 (R/W)  User data register
                                 //                         [31:0] : Data
  __IO uint32_t SYS_CFGDATA_OUT; // Offset: 0x0A4 (R/W)  User data register
                                 //                         [31:0] : Data
  __IO uint32_t SYS_CFGCTRL;     // Offset: 0x0A8 (R/W)  Control register
                                 //                           [31] : Start (generates interrupt on write to this bit)
                                 //                           [30] : R/W access
                                 //                        [29:26] : Reserved
                                 //                        [25:20] : Function value
                                 //                        [19:12] : Reserved
                                 //                         [11:0] : Device (value of 0/1/2 for supported clocks)
  __IO uint32_t SYS_CFGSTAT;     // Offset: 0x0AC (R/W)  Contains status information
                                 //                         [31:2] : Reserved
                                 //                            [1] : Error
                                 //                            [0] : Complete
  __IO uint32_t RESERVED2[20];
  __IO uint32_t SCC_DLL;         // Offset: 0x100 (R/W)  DLL Lock Register
                                 //                        [31:24] : DLL LOCK MASK[7:0] - Indicate if the DLL locked is masked
                                 //                        [23:16] : DLL LOCK MASK[7:0] - Indicate if the DLLs are locked or unlocked
                                 //                         [15:1] : Reserved
                                 //                            [0] : This bit indicates if all enabled DLLs are locked
       uint32_t RESERVED3[957];
  __I  uint32_t SCC_AID;         // Offset: 0xFF8 (R/ )  SCC AID Register
                                 //                        [31:24] : FPGA build number
                                 //                        [23:20] : V2M-MPS3 target board revision (A = 0, B = 1)
                                 //                        [19:11] : Reserved
                                 //                           [10] : if “1” SCC_SW register has been implemented
                                 //                            [9] : if “1” SCC_LED register has been implemented
                                 //                            [8] : if “1” DLL lock register has been implemented
                                 //                          [7:0] : number of SCC configuration register
  __I  uint32_t SCC_ID;          // Offset: 0xFFC (R/ )  Contains information about the FPGA image
                                 //                        [31:24] : Implementer ID: 0x41 = ARM
                                 //                        [23:20] : Application note IP variant number
                                 //                        [19:16] : IP Architecture: 0x4 =AHB
                                 //                         [15:4] : Primary part number: 386 = AN386
                                 //                          [3:0] : Application note IP revision number
} MPS3_SCC_TypeDef;


/******************************************************************************/
/*                            ARM SYSCounter (COUNTER)                            */
/******************************************************************************/
typedef struct
{
  __IO  uint32_t  CNTCR;                    /* Offset: 0x000 (R/W) Counter Control Register */
                                            /* [31:6] : Reserved */
                                            /*    [5] : INTRCLR - Interrupt clear bit, only */
                                            /*          writes of 0 are allowed, write of 1 is ignored */
                                            /*    [4] : PSLVERRDIS - PSLVERR output disable: */
                                            /*    [3] : INTRMASK - Interrupt mask */
                                            /*    [2] : SCEN – scale enable:  */
                                            /*    [1] : HDBG - Halt On Debug   */
                                            /*    [0] : EN   - Enable Counter 0=Disabled, 1=Enabled */
  __O   uint32_t  CNTSR;                    /* Offset: 0x004 (R/W) Counter Status Register */
                                            /* [31:2] : Reserved */
                                            /*    [1] : DBGH - Indicates whether the counter is halted */
                                            /*    [0] : Reserved */
  __IO  uint32_t  CNTCV_L;                  /* Offset: 0x008 (R/W) Counter Count Value register Lower */
  __IO  uint32_t  CNTCV_H;                  /* Offset: 0x00c (R/W) Counter Count Value register Upper*/
  __IO  uint32_t  CNTSCR;                   /* Offset: 0x010 (R/W) Counter Scale Register */
        uint32_t  RESERVED1[2];             /* Offset: 0x014-0x018 Reserved */
  __IO  uint32_t  CNTID;                    /* Offset: 0x01C (R/ ) Counter ID register */
        uint32_t  RESERVED2[5];             /* Offset: 0x020-0x0CC Reserved */
  __IO  uint32_t  CNTSCR0;                  /* Offset: 0x0D0 (R/W) Counter Scale Register 0 */
  __IO  uint32_t  CNTSCR1;                  /* Offset: 0x0D4 (R/W) Counter Scale Register 1 */
        uint32_t  RESERVED4[123];           /* Offset: 0x054-0xFCC Reserved */
  __IO  uint32_t  CNTPIDR4;                 /* Offset: 0xFD0 (R/ ) Peripheral ID4 register */
        uint32_t  RESERVED5[3];             /* Offset: 0xFD4-0xFDC Reserved */
  __IO  uint32_t  CNTPIDR0;                 /* Offset: 0xFE0 (R/ ) Peripheral ID0 register */
  __IO  uint32_t  CNTPIDR1;                 /* Offset: 0xFE4 (R/ ) Peripheral ID1 register */
  __IO  uint32_t  CNTPIDR2;                 /* Offset: 0xFE8 (R/ ) Peripheral ID2 register */
  __IO  uint32_t  CNTPIDR3;                 /* Offset: 0xFEC (R/ ) Peripheral ID3 register */
  __IO  uint32_t  CNTCIDR0;                 /* Offset: 0xFF0 (R/ ) Component ID0 register */
  __IO  uint32_t  CNTCIDR1;                 /* Offset: 0xFF4 (R/ ) Component ID1 register */
  __IO  uint32_t  CNTCIDR2;                 /* Offset: 0xFF8 (R/ ) Component ID2 register */
  __IO  uint32_t  CNTCIDR3;                 /* Offset: 0xFFC (R/ ) Component ID3 register */

} ARM_SYSCNT_CTRL_TypeDef;

/******************************************************************************/
/*                            ARM SYSTimer (TIMER)                            */
/******************************************************************************/
typedef struct
{
  __O   uint32_t  CNTPCT_L;                 /* Offset: 0x000 (R/ ) Count Register Lower */
  __O   uint32_t  CNTPCT_H;                 /* Offset: 0x004 (R/ ) Count Register Upper*/
        uint32_t RESERVED1[2];              /* Offset: 0x008 - 0x00C Reserved */
  __IO  uint32_t  CNTFRQ;                   /* Offset: 0x010 (R/W) Counter Frequency register */
        uint32_t RESERVED2[3];              /* Offset: 0x014 - 0x01C Reserved */
  __IO  uint32_t  CNTP_CVAL_L;              /* Offset: 0x020 (R/W) Timer CompareValue register Lower */
  __IO  uint32_t  CNTP_CVAL_H;              /* Offset: 0x024 (R/W) Timer CompareValue register Upper */
  __IO  uint32_t  CNTP_TVAL;                /* Offset: 0x028 (R/W) TimerValue register */
  __IO  uint32_t  CNTP_CTL;                 /* Offset: 0x02C (R/W) Timer Control register */
                                            /* [31:3] : Reserved */
                                            /*    [2] : ISTATUS  */
                                            /*    [1] : IMASK    */
                                            /*    [0] : ENABLE   */
        uint32_t RESERVED3[4];              /* Offset: 0x030 - 0x03C Reserved */
  __O   uint64_t  CNTP_AIVAL;               /* Offset: 0x040 (R/ ) AutoIncrValue register Lower */
                                            /* Offset: 0x044 (R/ ) AutoIncrValue register Upper */
  __IO  uint32_t  CNTP_AIVAL_RELOAD;        /* Offset: 0x048 (R/W) AutoIncrValue Reload register */
  __IO  uint32_t  CNTP_AIVAL_CTL;           /* Offset: 0x04C (R/W) AutoIncrValue Control register */
                                            /* [31:2] : Reserved */
                                            /*    [1] : CLR      */
                                            /*    [0] : EN       */
  __O   uint32_t  CNTP_CFG;                 /* Offset: 0x050 (R/ ) Timer Configuration register */
                                            /* [31:4] : Reserved */
                                            /*  [3:0] : AIVAL : 0000 autoincrement not implemented */
                                            /*        :         0001 autoincrement implemented */
        uint32_t RESERVED4[123];            /* Offset: 0x054 - 0xFCC Reserved */
  __O   uint32_t  CNTP_PID4;                /* Offset: 0xFD0 (R/ ) Peripheral ID4 register */
        uint32_t RESERVED5[3];              /* Offset: 0xFD4 - 0xFDC Reserved */
  __O   uint32_t  CNTP_PID0;                /* Offset: 0xFE0 (R/ ) Peripheral ID0 register */
  __O   uint32_t  CNTP_PID1;                /* Offset: 0xFE4 (R/ ) Peripheral ID1 register */
  __O   uint32_t  CNTP_PID2;                /* Offset: 0xFE8 (R/ ) Peripheral ID2 register */
  __O   uint32_t  CNTP_PID3;                /* Offset: 0xFEC (R/ ) Peripheral ID3 register */
  __O   uint32_t  CNTP_CID0;                /* Offset: 0xFF0 (R/ ) Component ID0 register */
  __O   uint32_t  CNTP_CID1;                /* Offset: 0xFF4 (R/ ) Component ID1 register */
  __O   uint32_t  CNTP_CID2;                /* Offset: 0xFF8 (R/ ) Component ID2 register */
  __O   uint32_t  CNTP_CID3;                /* Offset: 0xFFC (R/ ) Component ID3 register */

} ARM_SYSTIMER_TypeDef;

/* ARM_SYSTIMER CTRL Register Definitions */
#define ARM_SYSTIMER_CNTP_CTL_ISTATUS_Pos    2                                              /* ARM_SYSTIMER CTRL: STATUS Position */
#define ARM_SYSTIMER_CNTP_CTL_ISTATUS_Msk    (0x01ul << ARM_SYSTIMER_CNTP_CTL_ISTATUS_Pos)         /* ARM_SYSTIMER CTRL: STATUS Mask */

#define ARM_SYSTIMER_CNTP_CTL_IMASK_Pos      1                                              /* ARM_SYSTIMER CTRL: IRQEN Position */
#define ARM_SYSTIMER_CNTP_CTL_IMASK_Msk      (0x01ul << ARM_SYSTIMER_CNTP_CTL_IMASK_Pos)         /* ARM_SYSTIMER CTRL: IRQEN Mask */

#define ARM_SYSTIMER_CNTP_CTL_ENABLE_Pos     0                                              /* ARM_SYSTIMER CTRL: SELEXTCLK Position */
#define ARM_SYSTIMER_CNTP_CTL_ENABLE_Msk     (0x01ul << ARM_SYSTIMER_CNTP_CTL_ENABLE_Pos)     /* ARM_SYSTIMER CTRL: SELEXTCLK Mask */

#define ARM_SYSTIMER_CNTP_AIVAL_CTL_CLR_Pos  1                                              /* ARM_SYSTIMER CTRL: SELEXTEN Position */
#define ARM_SYSTIMER_CNTP_AIVAL_CTL_CLR_Msk  (0x01ul << ARM_SYSTIMER_CNTP_AIVAL_CTL_CLR_Pos)      /* ARM_SYSTIMER CTRL: SELEXTEN Mask */

#define ARM_SYSTIMER_CNTP_AIVAL_CTL_EN_Pos   0                                              /* ARM_SYSTIMER CTRL: EN Position */
#define ARM_SYSTIMER_CNTP_AIVAL_CTL_EN_Msk   (0x01ul << ARM_SYSTIMER_CNTP_AIVAL_CTL_EN_Pos)            /* ARM_SYSTIMER CTRL: EN Mask */


/******************************************************************************/
/*                        SSP Peripheral declaration                          */
/******************************************************************************/

typedef struct                   // Document DDI0194G_ssp_pl022_r1p3_trm.pdf
{
  __IO uint32_t CR0;             // Offset: 0x000 (R/W)  Control register 0
                                 //                        [31:16] : Reserved
                                 //                         [15:8] : Serial clock rate
                                 //                            [7] : SSPCLKOUT phase,    applicable to Motorola SPI frame format only
                                 //                            [6] : SSPCLKOUT polarity, applicable to Motorola SPI frame format only
                                 //                          [5:4] : Frame format
                                 //                          [3:0] : Data Size Select
  __IO uint32_t CR1;             // Offset: 0x004 (R/W)  Control register 1
                                 //                         [31:4] : Reserved
                                 //                            [3] : Slave-mode output disable
                                 //                            [2] : Master or slave mode select
                                 //                            [1] : Synchronous serial port enable
                                 //                            [0] : Loop back mode
  __IO uint32_t DR;              // Offset: 0x008 (R/W)  Data register
                                 //                        [31:16] : Reserved
                                 //                         [15:0] : Transmit/Receive FIFO
  __I  uint32_t SR;              // Offset: 0x00C (R/ )  Status register
                                 //                         [31:5] : Reserved
                                 //                            [4] : PrimeCell SSP busy flag
                                 //                            [3] : Receive FIFO full
                                 //                            [2] : Receive FIFO not empty
                                 //                            [1] : Transmit FIFO not full
                                 //                            [0] : Transmit FIFO empty
  __IO uint32_t CPSR;            // Offset: 0x010 (R/W)  Clock prescale register
                                 //                         [31:8] : Reserved
                                 //                          [8:0] : Clock prescale divisor
  __IO uint32_t IMSC;            // Offset: 0x014 (R/W)  Interrupt mask set or clear register
                                 //                         [31:4] : Reserved
                                 //                            [3] : Transmit FIFO interrupt mask
                                 //                            [2] : Receive FIFO interrupt mask
                                 //                            [1] : Receive timeout interrupt mask
                                 //                            [0] : Receive overrun interrupt mask
  __I  uint32_t RIS;             // Offset: 0x018 (R/ )  Raw interrupt status register
                                 //                         [31:4] : Reserved
                                 //                            [3] : raw interrupt state, prior to masking, of the SSPTXINTR interrupt
                                 //                            [2] : raw interrupt state, prior to masking, of the SSPRXINTR interrupt
                                 //                            [1] : raw interrupt state, prior to masking, of the SSPRTINTR interrupt
                                 //                            [0] : raw interrupt state, prior to masking, of the SSPRORINTR interrupt
  __I  uint32_t MIS;             // Offset: 0x01C (R/ )  Masked interrupt status register
                                 //                         [31:4] : Reserved
                                 //                            [3] : transmit FIFO masked interrupt state, after masking, of the SSPTXINTR interrupt
                                 //                            [2] : receive FIFO masked interrupt state, after masking, of the SSPRXINTR interrupt
                                 //                            [1] : receive timeout masked interrupt state, after masking, of the SSPRTINTR interrupt
                                 //                            [0] : receive over run masked interrupt status, after masking, of the SSPRORINTR interrupt
  __O  uint32_t ICR;             // Offset: 0x020 ( /W)  Interrupt clear register
                                 //                         [31:2] : Reserved
                                 //                            [1] : Clears the SSPRTINTR interrupt
                                 //                            [0] : Clears the SSPRORINTR interrupt
  __IO uint32_t DMACR;           // Offset: 0x024 (R/W)  DMA control register
                                 //                         [31:2] : Reserved
                                 //                            [1] : Transmit DMA Enable
                                 //                            [0] : Receive DMA Enable
} MPS3_SSP_TypeDef;


// SSP_CR0 Control register 0
#define SSP_CR0_DSS_Pos         0           // Data Size Select
#define SSP_CR0_DSS_Msk         (0xF<<SSP_CR0_DSS_Pos)
#define SSP_CR0_FRF_Pos         4           // Frame Format Select
#define SSP_CR0_FRF_Msk         (3UL<<SSP_CR0_FRM_Pos)
#define SSP_CR0_SPO_Pos         6           // SSPCLKOUT polarity
#define SSP_CR0_SPO_Msk         (1UL<<SSP_CR0_SPO_Pos)
#define SSP_CR0_SPH_Pos         7           // SSPCLKOUT phase
#define SSP_CR0_SPH_Msk         (1UL<<SSP_CR0_SPH_Pos)
#define SSP_CR0_SCR_Pos         8           // Serial Clock Rate (divide)
#define SSP_CR0_SCR_Msk         (0xFF<<SSP_CR0_SCR_Pos)

#define SSP_CR0_SCR_DFLT        0x0300      // Serial Clock Rate (divide), default set at 3
#define SSP_CR0_FRF_MOT         0x0000      // Frame format, Motorola
#define SSP_CR0_DSS_8           0x0007      // Data packet size, 8bits
#define SSP_CR0_DSS_16          0x000F      // Data packet size, 16bits

// SSP_CR1 Control register 1
#define SSP_CR1_LBM_Pos         0           // Loop Back Mode
#define SSP_CR1_LBM_Msk         (1UL<<SSP_CR1_LBM_Pos)
#define SSP_CR1_SSE_Pos         1           // Serial port enable
#define SSP_CR1_SSE_Msk         (1UL<<SSP_CR1_SSE_Pos)
#define SSP_CR1_MS_Pos          2           // Master or Slave mode
#define SSP_CR1_MS_Msk          (1UL<<SSP_CR1_MS_Pos)
#define SSP_CR1_SOD_Pos         3           // Slave Output mode Disable
#define SSP_CR1_SOD_Msk         (1UL<<SSP_CR1_SOD_Pos)

// SSP_SR Status register
#define SSP_SR_TFE_Pos          0           // Transmit FIFO empty
#define SSP_SR_TFE_Msk          (1UL<<SSP_SR_TFE_Pos)
#define SSP_SR_TNF_Pos          1           // Transmit FIFO not full
#define SSP_SR_TNF_Msk          (1UL<<SSP_SR_TNF_Pos)
#define SSP_SR_RNE_Pos          2           // Receive  FIFO not empty
#define SSP_SR_RNE_Msk          (1UL<<SSP_SR_RNE_Pos)
#define SSP_SR_RFF_Pos          3           // Receive  FIFO full
#define SSP_SR_RFF_Msk          (1UL<<SSP_SR_RFF_Pos)
#define SSP_SR_BSY_Pos          4           // Busy
#define SSP_SR_BSY_Msk          (1UL<<SSP_SR_BSY_Pos)

// SSP_CPSR Clock prescale register
#define SSP_CPSR_CPD_Pos        0           // Clock prescale divisor
#define SSP_CPSR_CPD_Msk        (0xFF<<SSP_CPSR_CDP_Pos)

#define SSP_CPSR_DFLT        0x0008      // Clock prescale (use with SCR), default set at 8

// SSPIMSC Interrupt mask set and clear register
#define SSP_IMSC_RORIM_Pos         0           // Receive overrun not Masked
#define SSP_IMSC_RORIM_Msk         (1UL<<SSP_IMSC_RORIM_Pos)
#define SSP_IMSC_RTIM_Pos          1           // Receive timeout not Masked
#define SSP_IMSC_RTIM_Msk          (1UL<<SSP_IMSC_RTIM_Pos)
#define SSP_IMSC_RXIM_Pos          2           // Receive  FIFO not Masked
#define SSP_IMSC_RXIM_Msk          (1UL<<SSP_IMSC_RXIM_Pos)
#define SSP_IMSC_TXIM_Pos          3           // Transmit FIFO not Masked
#define SSP_IMSC_TXIM_Msk          (1UL<<SSP_IMSC_TXIM_Pos)

// SSPRIS Raw interrupt status register
#define SSP_RIS_RORRIS_Pos         0           // Raw Overrun  interrupt flag
#define SSP_RIS_RORRIS_Msk         (1UL<<SSP_RIS_RORRIS_Pos)
#define SSP_RIS_RTRIS_Pos          1           // Raw Timemout interrupt flag
#define SSP_RIS_RTRIS_Msk          (1UL<<SSP_RIS_RTRIS_Pos)
#define SSP_RIS_RXRIS_Pos          2           // Raw Receive  interrupt flag
#define SSP_RIS_RXRIS_Msk          (1UL<<SSP_RIS_RXRIS_Pos)
#define SSP_RIS_TXRIS_Pos          3           // Raw Transmit interrupt flag
#define SSP_RIS_TXRIS_Msk          (1UL<<SSP_RIS_TXRIS_Pos)

// SSPMIS Masked interrupt status register
#define SSP_MIS_RORMIS_Pos         0           // Masked Overrun  interrupt flag
#define SSP_MIS_RORMIS_Msk         (1UL<<SSP_MIS_RORMIS_Pos)
#define SSP_MIS_RTMIS_Pos          1           // Masked Timemout interrupt flag
#define SSP_MIS_RTMIS_Msk          (1UL<<SSP_MIS_RTMIS_Pos)
#define SSP_MIS_RXMIS_Pos          2           // Masked Receive  interrupt flag
#define SSP_MIS_RXMIS_Msk          (1UL<<SSP_MIS_RXMIS_Pos)
#define SSP_MIS_TXMIS_Pos          3           // Masked Transmit interrupt flag
#define SSP_MIS_TXMIS_Msk          (1UL<<SSP_MIS_TXMIS_Pos)

// SSPICR Interrupt clear register
#define SSP_ICR_RORIC_Pos           0           // Clears Overrun  interrupt flag
#define SSP_ICR_RORIC_Msk           (1UL<<SSP_ICR_RORIC_Pos)
#define SSP_ICR_RTIC_Pos            1           // Clears Timemout interrupt flag
#define SSP_ICR_RTIC_Msk            (1UL<<SSP_ICR_RTIC_Pos)

// SSPDMACR DMA control register
#define SSP_DMACR_RXDMAE_Pos        0           // Enable Receive  FIFO DMA
#define SSP_DMACR_RXDMAE_Msk        (1UL<<SSP_DMACR_RXDMAE_Pos)
#define SSP_DMACR_TXDMAE_Pos        1           // Enable Transmit FIFO DMA
#define SSP_DMACR_TXDMAE_Msk        (1UL<<SSP_DMACR_TXDMAE_Pos)

/******************************************************************************/
/*               Audio and Touch Screen (I2C) Peripheral declaration          */
/******************************************************************************/

typedef struct
{
  union {
  __O   uint32_t  CONTROLS;     // Offset: 0x000 CONTROL Set Register     ( /W) 
  __I   uint32_t  CONTROL;      // Offset: 0x000 CONTROL Status Register  (R/ ) 
  };
  __O    uint32_t  CONTROLC;     // Offset: 0x004 CONTROL Clear Register    ( /W)  
} MPS3_I2C_TypeDef;

#define SDA                1 << 1
#define SCL                1 << 0


/******************************************************************************/
/*               Audio I2S Peripheral declaration                             */
/******************************************************************************/

typedef struct
{
  /*!< Offset: 0x000 CONTROL Register    (R/W) */
  __IO   uint32_t  CONTROL; // <h> CONTROL </h>
                              //   <o.0> TX Enable
                              //     <0=> TX disabled
                              //     <1=> TX enabled
                              //   <o.1> TX IRQ Enable
                              //     <0=> TX IRQ disabled
                              //     <1=> TX IRQ enabled
                              //   <o.2> RX Enable
                              //     <0=> RX disabled
                              //     <1=> RX enabled
                              //   <o.3> RX IRQ Enable
                              //     <0=> RX IRQ disabled
                              //     <1=> RX IRQ enabled
                              //   <o.10..8> TX Buffer Water Level
                              //     <0=> / IRQ triggers when any space available
                              //     <1=> / IRQ triggers when more than 1 space available
                              //     <2=> / IRQ triggers when more than 2 space available
                              //     <3=> / IRQ triggers when more than 3 space available
                              //     <4=> Undefined!
                              //     <5=> Undefined!
                              //     <6=> Undefined!
                              //     <7=> Undefined!  
                              //   <o.14..12> RX Buffer Water Level
                              //     <0=> Undefined!
                              //     <1=> / IRQ triggers when less than 1 space available
                              //     <2=> / IRQ triggers when less than 2 space available
                              //     <3=> / IRQ triggers when less than 3 space available
                              //     <4=> / IRQ triggers when less than 4 space available
                              //     <5=> Undefined!
                              //     <6=> Undefined!
                              //     <7=> Undefined!  
                              //   <o.16> FIFO reset
                              //     <0=> Normal operation
                              //     <1=> FIFO reset
                              //   <o.17> Audio Codec reset
                              //     <0=> Normal operation
                              //     <1=> Assert audio Codec reset
  /*!< Offset: 0x004 STATUS Register     (R/ ) */
  __I    uint32_t  STATUS;  // <h> STATUS </h> 
                              //   <o.0> TX Buffer alert
                              //     <0=> TX buffer don't need service yet
                              //     <1=> TX buffer need service
                              //   <o.1> RX Buffer alert
                              //     <0=> RX buffer don't need service yet 
                              //     <1=> RX buffer need service
                              //   <o.2> TX Buffer Empty
                              //     <0=> TX buffer have data
                              //     <1=> TX buffer empty
                              //   <o.3> TX Buffer Full
                              //     <0=> TX buffer not full
                              //     <1=> TX buffer full
                              //   <o.4> RX Buffer Empty
                              //     <0=> RX buffer have data
                              //     <1=> RX buffer empty
                              //   <o.5> RX Buffer Full
                              //     <0=> RX buffer not full
                              //     <1=> RX buffer full
  union {
   /*!< Offset: 0x008 Error Status Register (R/ ) */  
    __I    uint32_t  ERROR;  // <h> ERROR </h> 
                              //   <o.0> TX error
                              //     <0=> Okay
                              //     <1=> TX overrun/underrun
                              //   <o.1> RX error
                              //     <0=> Okay 
                              //     <1=> RX overrun/underrun
   /*!< Offset: 0x008 Error Clear Register  ( /W) */    
    __O    uint32_t  ERRORCLR;  // <h> ERRORCLR </h> 
                              //   <o.0> TX error
                              //     <0=> Okay
                              //     <1=> Clear TX error
                              //   <o.1> RX error
                              //     <0=> Okay 
                              //     <1=> Clear RX error
    };
   /*!< Offset: 0x00C Divide ratio Register (R/W) */  
  __IO   uint32_t  DIVIDE;  // <h> Divide ratio for Left/Right clock </h> 
                              //   <o.9..0> TX error (default 0x80)                  
   /*!< Offset: 0x010 Transmit Buffer       ( /W) */
  __O    uint32_t  TXBUF;  // <h> Transmit buffer </h> 
                              //   <o.15..0> Right channel                  
                              //   <o.31..16> Left channel
   /*!< Offset: 0x014 Receive Buffer        (R/ ) */
  __I    uint32_t  RXBUF;  // <h> Receive buffer </h> 
                              //   <o.15..0> Right channel                  
                              //   <o.31..16> Left channel
         uint32_t  RESERVED1[186];
  __IO uint32_t ITCR;         // <h> Integration Test Control Register </h>
                              //   <o.0> ITEN
                              //     <0=> Normal operation
                              //     <1=> Integration Test mode enable
  __O  uint32_t ITIP1;        // <h> Integration Test Input Register 1</h>
                              //   <o.0> SDIN
  __O  uint32_t ITOP1;        // <h> Integration Test Output Register 1</h>
                              //   <o.0> SDOUT
                              //   <o.1> SCLK
                              //   <o.2> LRCK
                              //   <o.3> IRQOUT
} MPS3_I2S_TypeDef;

#define I2S_CONTROL_TXEN_Pos        0
#define I2S_CONTROL_TXEN_Msk        (1UL<<I2S_CONTROL_TXEN_Pos)

#define I2S_CONTROL_TXIRQEN_Pos     1
#define I2S_CONTROL_TXIRQEN_Msk     (1UL<<I2S_CONTROL_TXIRQEN_Pos)

#define I2S_CONTROL_RXEN_Pos        2
#define I2S_CONTROL_RXEN_Msk        (1UL<<I2S_CONTROL_RXEN_Pos)

#define I2S_CONTROL_RXIRQEN_Pos     3
#define I2S_CONTROL_RXIRQEN_Msk     (1UL<<I2S_CONTROL_RXIRQEN_Pos)

#define I2S_CONTROL_TXWLVL_Pos      8
#define I2S_CONTROL_TXWLVL_Msk      (7UL<<I2S_CONTROL_TXWLVL_Pos)

#define I2S_CONTROL_RXWLVL_Pos      12
#define I2S_CONTROL_RXWLVL_Msk      (7UL<<I2S_CONTROL_RXWLVL_Pos)
/* FIFO reset*/
#define I2S_CONTROL_FIFORST_Pos     16
#define I2S_CONTROL_FIFORST_Msk     (1UL<<I2S_CONTROL_FIFORST_Pos)
/* Codec reset*/
#define I2S_CONTROL_CODECRST_Pos    17
#define I2S_CONTROL_CODECRST_Msk    (1UL<<I2S_CONTROL_CODECRST_Pos)

#define I2S_STATUS_TXIRQ_Pos        0
#define I2S_STATUS_TXIRQ_Msk        (1UL<<I2S_STATUS_TXIRQ_Pos)

#define I2S_STATUS_RXIRQ_Pos        1
#define I2S_STATUS_RXIRQ_Msk        (1UL<<I2S_STATUS_RXIRQ_Pos)

#define I2S_STATUS_TXEmpty_Pos      2
#define I2S_STATUS_TXEmpty_Msk      (1UL<<I2S_STATUS_TXEmpty_Pos)

#define I2S_STATUS_TXFull_Pos       3
#define I2S_STATUS_TXFull_Msk       (1UL<<I2S_STATUS_TXFull_Pos)

#define I2S_STATUS_RXEmpty_Pos      4
#define I2S_STATUS_RXEmpty_Msk      (1UL<<I2S_STATUS_RXEmpty_Pos)

#define I2S_STATUS_RXFull_Pos       5
#define I2S_STATUS_RXFull_Msk       (1UL<<I2S_STATUS_RXFull_Pos)

#define I2S_ERROR_TXERR_Pos         0
#define I2S_ERROR_TXERR_Msk         (1UL<<I2S_ERROR_TXERR_Pos)

#define I2S_ERROR_RXERR_Pos         1
#define I2S_ERROR_RXERR_Msk         (1UL<<I2S_ERROR_RXERR_Pos)

/******************************************************************************/
/*                       SMSC9220 Register Definitions                        */
/******************************************************************************/

typedef struct                   // SMSC LAN9220
{
__I   uint32_t  RX_DATA_PORT;          //   Receive FIFO Ports (offset 0x0)
      uint32_t  RESERVED1[0x7];
__O   uint32_t  TX_DATA_PORT;          //   Transmit FIFO Ports (offset 0x20)
      uint32_t  RESERVED2[0x7];

__I   uint32_t  RX_STAT_PORT;          //   Receive FIFO status port (offset 0x40)
__I   uint32_t  RX_STAT_PEEK;          //   Receive FIFO status peek (offset 0x44)
__I   uint32_t  TX_STAT_PORT;          //   Transmit FIFO status port (offset 0x48)
__I   uint32_t  TX_STAT_PEEK;          //   Transmit FIFO status peek (offset 0x4C)

__I   uint32_t  ID_REV;                //   Chip ID and Revision (offset 0x50)
__IO  uint32_t  IRQ_CFG;               //   Main Interrupt Configuration (offset 0x54)
__IO  uint32_t  INT_STS;               //   Interrupt Status (offset 0x58)
__IO  uint32_t  INT_EN;                //   Interrupt Enable Register (offset 0x5C)
      uint32_t  RESERVED3;             //   Reserved for future use (offset 0x60)
__I   uint32_t  BYTE_TEST;             //   Read-only byte order testing register 87654321h (offset 0x64)
__IO  uint32_t  FIFO_INT;              //   FIFO Level Interrupts (offset 0x68)
__IO  uint32_t  RX_CFG;                //   Receive Configuration (offset 0x6C)
__IO  uint32_t  TX_CFG;                //   Transmit Configuration (offset 0x70)
__IO  uint32_t  HW_CFG;                //   Hardware Configuration (offset 0x74)
__IO  uint32_t  RX_DP_CTL;             //   RX Datapath Control (offset 0x78)
__I   uint32_t  RX_FIFO_INF;           //   Receive FIFO Information (offset 0x7C)
__I   uint32_t  TX_FIFO_INF;           //   Transmit FIFO Information (offset 0x80)
__IO  uint32_t  PMT_CTRL;              //   Power Management Control (offset 0x84)
__IO  uint32_t  GPIO_CFG;              //   General Purpose IO Configuration (offset 0x88)
__IO  uint32_t  GPT_CFG;               //   General Purpose Timer Configuration (offset 0x8C)
__I   uint32_t  GPT_CNT;               //   General Purpose Timer Count (offset 0x90)
      uint32_t  RESERVED4;             //   Reserved for future use (offset 0x94)
__IO  uint32_t  ENDIAN;                //   WORD SWAP Register (offset 0x98)
__I   uint32_t  FREE_RUN;              //   Free Run Counter (offset 0x9C)
__I   uint32_t  RX_DROP;               //   RX Dropped Frames Counter (offset 0xA0)
__IO  uint32_t  MAC_CSR_CMD;           //   MAC CSR Synchronizer Command (offset 0xA4)
__IO  uint32_t  MAC_CSR_DATA;          //   MAC CSR Synchronizer Data (offset 0xA8)
__IO  uint32_t  AFC_CFG;               //   Automatic Flow Control Configuration (offset 0xAC)
__IO  uint32_t  E2P_CMD;               //   EEPROM Command (offset 0xB0)
__IO  uint32_t  E2P_DATA;              //   EEPROM Data (offset 0xB4)

} SMSC9220_TypeDef;

// SMSC9220 MAC Registers       Indices
#define SMSC9220_MAC_CR         0x1
#define SMSC9220_MAC_ADDRH      0x2
#define SMSC9220_MAC_ADDRL      0x3
#define SMSC9220_MAC_HASHH      0x4
#define SMSC9220_MAC_HASHL      0x5
#define SMSC9220_MAC_MII_ACC    0x6
#define SMSC9220_MAC_MII_DATA   0x7
#define SMSC9220_MAC_FLOW       0x8
#define SMSC9220_MAC_VLAN1      0x9
#define SMSC9220_MAC_VLAN2      0xA
#define SMSC9220_MAC_WUFF       0xB
#define SMSC9220_MAC_WUCSR      0xC

// SMSC9220 PHY Registers       Indices
#define SMSC9220_PHY_BCONTROL   0x0
#define SMSC9220_PHY_BSTATUS    0x1
#define SMSC9220_PHY_ID1        0x2
#define SMSC9220_PHY_ID2        0x3
#define SMSC9220_PHY_ANEG_ADV   0x4
#define SMSC9220_PHY_ANEG_LPA   0x5
#define SMSC9220_PHY_ANEG_EXP   0x6
#define SMSC9220_PHY_MCONTROL   0x17
#define SMSC9220_PHY_MSTATUS    0x18
#define SMSC9220_PHY_CSINDICATE 0x27
#define SMSC9220_PHY_INTSRC     0x29
#define SMSC9220_PHY_INTMASK    0x30
#define SMSC9220_PHY_CS         0x31

/*------------- Universal Asynchronous Receiver Transmitter (UART) -----------*/
typedef struct
{
  __IO   uint32_t  DATA;                     /* Offset: 0x000 (R/W) Data Register    */
  __IO   uint32_t  STATE;                    /* Offset: 0x004 (R/W) Status Register  */
  __IO   uint32_t  CTRL;                     /* Offset: 0x008 (R/W) Control Register */
  union {
    __I    uint32_t  INTSTATUS;              /* Offset: 0x00C (R/ ) Interrupt Status Register */
    __O    uint32_t  INTCLEAR;               /* Offset: 0x00C ( /W) Interrupt Clear Register  */
    };
  __IO   uint32_t  BAUDDIV;                  /* Offset: 0x010 (R/W) Baudrate Divider Register */

} CMSDK_UART_TypeDef;

/* CMSDK_UART DATA Register Definitions */
#define CMSDK_UART_DATA_Pos               0                                             /* CMSDK_UART_DATA_Pos: DATA Position */
#define CMSDK_UART_DATA_Msk              (0xFFul << CMSDK_UART_DATA_Pos)                /* CMSDK_UART DATA: DATA Mask */

/* CMSDK_UART STATE Register Definitions */
#define CMSDK_UART_STATE_RXOR_Pos         3                                             /* CMSDK_UART STATE: RXOR Position */
#define CMSDK_UART_STATE_RXOR_Msk         (0x1ul << CMSDK_UART_STATE_RXOR_Pos)          /* CMSDK_UART STATE: RXOR Mask */

#define CMSDK_UART_STATE_TXOR_Pos         2                                             /* CMSDK_UART STATE: TXOR Position */
#define CMSDK_UART_STATE_TXOR_Msk         (0x1ul << CMSDK_UART_STATE_TXOR_Pos)          /* CMSDK_UART STATE: TXOR Mask */

#define CMSDK_UART_STATE_RXBF_Pos         1                                             /* CMSDK_UART STATE: RXBF Position */
#define CMSDK_UART_STATE_RXBF_Msk         (0x1ul << CMSDK_UART_STATE_RXBF_Pos)          /* CMSDK_UART STATE: RXBF Mask */

#define CMSDK_UART_STATE_TXBF_Pos         0                                             /* CMSDK_UART STATE: TXBF Position */
#define CMSDK_UART_STATE_TXBF_Msk         (0x1ul << CMSDK_UART_STATE_TXBF_Pos )         /* CMSDK_UART STATE: TXBF Mask */

/* CMSDK_UART CTRL Register Definitions */
#define CMSDK_UART_CTRL_HSTM_Pos          6                                             /* CMSDK_UART CTRL: HSTM Position */
#define CMSDK_UART_CTRL_HSTM_Msk          (0x01ul << CMSDK_UART_CTRL_HSTM_Pos)          /* CMSDK_UART CTRL: HSTM Mask */

#define CMSDK_UART_CTRL_RXORIRQEN_Pos     5                                             /* CMSDK_UART CTRL: RXORIRQEN Position */
#define CMSDK_UART_CTRL_RXORIRQEN_Msk     (0x01ul << CMSDK_UART_CTRL_RXORIRQEN_Pos)     /* CMSDK_UART CTRL: RXORIRQEN Mask */

#define CMSDK_UART_CTRL_TXORIRQEN_Pos     4                                             /* CMSDK_UART CTRL: TXORIRQEN Position */
#define CMSDK_UART_CTRL_TXORIRQEN_Msk     (0x01ul << CMSDK_UART_CTRL_TXORIRQEN_Pos)     /* CMSDK_UART CTRL: TXORIRQEN Mask */

#define CMSDK_UART_CTRL_RXIRQEN_Pos       3                                             /* CMSDK_UART CTRL: RXIRQEN Position */
#define CMSDK_UART_CTRL_RXIRQEN_Msk       (0x01ul << CMSDK_UART_CTRL_RXIRQEN_Pos)       /* CMSDK_UART CTRL: RXIRQEN Mask */

#define CMSDK_UART_CTRL_TXIRQEN_Pos       2                                             /* CMSDK_UART CTRL: TXIRQEN Position */
#define CMSDK_UART_CTRL_TXIRQEN_Msk       (0x01ul << CMSDK_UART_CTRL_TXIRQEN_Pos)       /* CMSDK_UART CTRL: TXIRQEN Mask */

#define CMSDK_UART_CTRL_RXEN_Pos          1                                             /* CMSDK_UART CTRL: RXEN Position */
#define CMSDK_UART_CTRL_RXEN_Msk          (0x01ul << CMSDK_UART_CTRL_RXEN_Pos)          /* CMSDK_UART CTRL: RXEN Mask */

#define CMSDK_UART_CTRL_TXEN_Pos          0                                             /* CMSDK_UART CTRL: TXEN Position */
#define CMSDK_UART_CTRL_TXEN_Msk          (0x01ul << CMSDK_UART_CTRL_TXEN_Pos)          /* CMSDK_UART CTRL: TXEN Mask */

/* CMSDK_UART INTSTATUS\INTCLEAR Register Definitions */
#define CMSDK_UART_INT_RXORIRQ_Pos        3                                             /* CMSDK_UART INT: RXORIRQ Position */
#define CMSDK_UART_INT_RXORIRQ_Msk        (0x01ul << CMSDK_UART_INT_RXORIRQ_Pos)        /* CMSDK_UART INT: RXORIRQ Mask */

#define CMSDK_UART_INT_TXORIRQ_Pos        2                                             /* CMSDK_UART INT: TXORIRQ Position */
#define CMSDK_UART_INT_TXORIRQ_Msk        (0x01ul << CMSDK_UART_INT_TXORIRQ_Pos)        /* CMSDK_UART INT: TXORIRQ Mask */

#define CMSDK_UART_INT_RXIRQ_Pos          1                                             /* CMSDK_UART INT: RXIRQ Position */
#define CMSDK_UART_INT_RXIRQ_Msk          (0x01ul << CMSDK_UART_INT_RXIRQ_Pos)          /* CMSDK_UART INT: RXIRQ Mask */

#define CMSDK_UART_INT_TXIRQ_Pos          0                                             /* CMSDK_UART INT: TXIRQ Position */
#define CMSDK_UART_INT_TXIRQ_Msk          (0x01ul << CMSDK_UART_INT_TXIRQ_Pos)          /* CMSDK_UART INT: TXIRQ Mask */

/* CMSDK_UART BAUDDIV Register Definitions */
#define CMSDK_UART_BAUDDIV_Pos            0                                             /* CMSDK_UART BAUDDIV: BAUDDIV Position */
#define CMSDK_UART_BAUDDIV_Msk           (0xFFFFFul << CMSDK_UART_BAUDDIV_Pos)          /* CMSDK_UART BAUDDIV: BAUDDIV Mask */


/*----------------------------- Timer (TIMER) -------------------------------*/
typedef struct
{
  __IO   uint32_t  CTRL;                     /* Offset: 0x000 (R/W) Control Register */
  __IO   uint32_t  VALUE;                    /* Offset: 0x004 (R/W) Current Value Register */
  __IO   uint32_t  RELOAD;                   /* Offset: 0x008 (R/W) Reload Value Register */
  union {
    __I    uint32_t  INTSTATUS;              /* Offset: 0x00C (R/ ) Interrupt Status Register */
    __O    uint32_t  INTCLEAR;               /* Offset: 0x00C ( /W) Interrupt Clear Register */
    };

} CMSDK_TIMER_TypeDef;

/* CMSDK_TIMER CTRL Register Definitions */
#define CMSDK_TIMER_CTRL_IRQEN_Pos          3                                              /* CMSDK_TIMER CTRL: IRQEN Position */
#define CMSDK_TIMER_CTRL_IRQEN_Msk          (0x01ul << CMSDK_TIMER_CTRL_IRQEN_Pos)         /* CMSDK_TIMER CTRL: IRQEN Mask */

#define CMSDK_TIMER_CTRL_SELEXTCLK_Pos      2                                              /* CMSDK_TIMER CTRL: SELEXTCLK Position */
#define CMSDK_TIMER_CTRL_SELEXTCLK_Msk      (0x01ul << CMSDK_TIMER_CTRL_SELEXTCLK_Pos)     /* CMSDK_TIMER CTRL: SELEXTCLK Mask */

#define CMSDK_TIMER_CTRL_SELEXTEN_Pos       1                                              /* CMSDK_TIMER CTRL: SELEXTEN Position */
#define CMSDK_TIMER_CTRL_SELEXTEN_Msk       (0x01ul << CMSDK_TIMER_CTRL_SELEXTEN_Pos)      /* CMSDK_TIMER CTRL: SELEXTEN Mask */

#define CMSDK_TIMER_CTRL_EN_Pos             0                                              /* CMSDK_TIMER CTRL: EN Position */
#define CMSDK_TIMER_CTRL_EN_Msk             (0x01ul << CMSDK_TIMER_CTRL_EN_Pos)            /* CMSDK_TIMER CTRL: EN Mask */

/* CMSDK_TIMER VAL Register Definitions */
#define CMSDK_TIMER_VAL_CURRENT_Pos         0                                              /* CMSDK_TIMER VALUE: CURRENT Position */
#define CMSDK_TIMER_VAL_CURRENT_Msk         (0xFFFFFFFFul << CMSDK_TIMER_VAL_CURRENT_Pos)  /* CMSDK_TIMER VALUE: CURRENT Mask */

/* CMSDK_TIMER RELOAD Register Definitions */
#define CMSDK_TIMER_RELOAD_VAL_Pos          0                                              /* CMSDK_TIMER RELOAD: RELOAD Position */
#define CMSDK_TIMER_RELOAD_VAL_Msk          (0xFFFFFFFFul << CMSDK_TIMER_RELOAD_VAL_Pos)   /* CMSDK_TIMER RELOAD: RELOAD Mask */

/* CMSDK_TIMER INTSTATUS Register Definitions */
#define CMSDK_TIMER_INTSTATUS_Pos           0                                              /* CMSDK_TIMER INTSTATUS: INTSTATUSPosition */
#define CMSDK_TIMER_INTSTATUS_Msk           (0x01ul << CMSDK_TIMER_INTSTATUS_Pos)          /* CMSDK_TIMER INTSTATUS: INTSTATUSMask */

/* CMSDK_TIMER INTCLEAR Register Definitions */
#define CMSDK_TIMER_INTCLEAR_Pos            0                                              /* CMSDK_TIMER INTCLEAR: INTCLEAR Position */
#define CMSDK_TIMER_INTCLEAR_Msk            (0x01ul << CMSDK_TIMER_INTCLEAR_Pos)           /* CMSDK_TIMER INTCLEAR: INTCLEAR Mask */


/*------------- Timer (TIM) --------------------------------------------------*/
typedef struct
{
  __IO uint32_t Timer1Load;                  /* Offset: 0x000 (R/W) Timer 1 Load */
  __I  uint32_t Timer1Value;                 /* Offset: 0x004 (R/ ) Timer 1 Counter Current Value */
  __IO uint32_t Timer1Control;               /* Offset: 0x008 (R/W) Timer 1 Control */
  __O  uint32_t Timer1IntClr;                /* Offset: 0x00C ( /W) Timer 1 Interrupt Clear */
  __I  uint32_t Timer1RIS;                   /* Offset: 0x010 (R/ ) Timer 1 Raw Interrupt Status */
  __I  uint32_t Timer1MIS;                   /* Offset: 0x014 (R/ ) Timer 1 Masked Interrupt Status */
  __IO uint32_t Timer1BGLoad;                /* Offset: 0x018 (R/W) Background Load Register */
       uint32_t RESERVED0;
  __IO uint32_t Timer2Load;                  /* Offset: 0x020 (R/W) Timer 2 Load */
  __I  uint32_t Timer2Value;                 /* Offset: 0x024 (R/ ) Timer 2 Counter Current Value */
  __IO uint32_t Timer2Control;               /* Offset: 0x028 (R/W) Timer 2 Control */
  __O  uint32_t Timer2IntClr;                /* Offset: 0x02C ( /W) Timer 2 Interrupt Clear */
  __I  uint32_t Timer2RIS;                   /* Offset: 0x030 (R/ ) Timer 2 Raw Interrupt Status */
  __I  uint32_t Timer2MIS;                   /* Offset: 0x034 (R/ ) Timer 2 Masked Interrupt Status */
  __IO uint32_t Timer2BGLoad;                /* Offset: 0x038 (R/W) Background Load Register */
       uint32_t RESERVED1[945];
  __IO uint32_t ITCR;                        /* Offset: 0xF00 (R/W) Integration Test Control Register */
  __O  uint32_t ITOP;                        /* Offset: 0xF04 ( /W) Integration Test Output Set Register */
} CMSDK_DUALTIMER_BOTH_TypeDef;

#define CMSDK_DUALTIMER1_LOAD_Pos            0                                                /* CMSDK_DUALTIMER1 LOAD: LOAD Position */
#define CMSDK_DUALTIMER1_LOAD_Msk            (0xFFFFFFFFul << CMSDK_DUALTIMER1_LOAD_Pos)      /* CMSDK_DUALTIMER1 LOAD: LOAD Mask */

#define CMSDK_DUALTIMER1_VALUE_Pos           0                                                /* CMSDK_DUALTIMER1 VALUE: VALUE Position */
#define CMSDK_DUALTIMER1_VALUE_Msk           (0xFFFFFFFFul << CMSDK_DUALTIMER1_VALUE_Pos)     /* CMSDK_DUALTIMER1 VALUE: VALUE Mask */

#define CMSDK_DUALTIMER1_CTRL_EN_Pos         7                                                /* CMSDK_DUALTIMER1 CTRL_EN: CTRL Enable Position */
#define CMSDK_DUALTIMER1_CTRL_EN_Msk         (0x1ul << CMSDK_DUALTIMER1_CTRL_EN_Pos)          /* CMSDK_DUALTIMER1 CTRL_EN: CTRL Enable Mask */

#define CMSDK_DUALTIMER1_CTRL_MODE_Pos       6                                                /* CMSDK_DUALTIMER1 CTRL_MODE: CTRL MODE Position */
#define CMSDK_DUALTIMER1_CTRL_MODE_Msk       (0x1ul << CMSDK_DUALTIMER1_CTRL_MODE_Pos)        /* CMSDK_DUALTIMER1 CTRL_MODE: CTRL MODE Mask */

#define CMSDK_DUALTIMER1_CTRL_INTEN_Pos      5                                                /* CMSDK_DUALTIMER1 CTRL_INTEN: CTRL Int Enable Position */
#define CMSDK_DUALTIMER1_CTRL_INTEN_Msk      (0x1ul << CMSDK_DUALTIMER1_CTRL_INTEN_Pos)       /* CMSDK_DUALTIMER1 CTRL_INTEN: CTRL Int Enable Mask */

#define CMSDK_DUALTIMER1_CTRL_PRESCALE_Pos   2                                                /* CMSDK_DUALTIMER1 CTRL_PRESCALE: CTRL PRESCALE Position */
#define CMSDK_DUALTIMER1_CTRL_PRESCALE_Msk   (0x3ul << CMSDK_DUALTIMER1_CTRL_PRESCALE_Pos)    /* CMSDK_DUALTIMER1 CTRL_PRESCALE: CTRL PRESCALE Mask */

#define CMSDK_DUALTIMER1_CTRL_SIZE_Pos       1                                                /* CMSDK_DUALTIMER1 CTRL_SIZE: CTRL SIZE Position */
#define CMSDK_DUALTIMER1_CTRL_SIZE_Msk       (0x1ul << CMSDK_DUALTIMER1_CTRL_SIZE_Pos)        /* CMSDK_DUALTIMER1 CTRL_SIZE: CTRL SIZE Mask */

#define CMSDK_DUALTIMER1_CTRL_ONESHOOT_Pos   0                                                /* CMSDK_DUALTIMER1 CTRL_ONESHOOT: CTRL ONESHOOT Position */
#define CMSDK_DUALTIMER1_CTRL_ONESHOOT_Msk   (0x1ul << CMSDK_DUALTIMER1_CTRL_ONESHOOT_Pos)    /* CMSDK_DUALTIMER1 CTRL_ONESHOOT: CTRL ONESHOOT Mask */

#define CMSDK_DUALTIMER1_INTCLR_Pos          0                                                /* CMSDK_DUALTIMER1 INTCLR: INT Clear Position */
#define CMSDK_DUALTIMER1_INTCLR_Msk          (0x1ul << CMSDK_DUALTIMER1_INTCLR_Pos)           /* CMSDK_DUALTIMER1 INTCLR: INT Clear  Mask */

#define CMSDK_DUALTIMER1_RAWINTSTAT_Pos      0                                                /* CMSDK_DUALTIMER1 RAWINTSTAT: Raw Int Status Position */
#define CMSDK_DUALTIMER1_RAWINTSTAT_Msk      (0x1ul << CMSDK_DUALTIMER1_RAWINTSTAT_Pos)       /* CMSDK_DUALTIMER1 RAWINTSTAT: Raw Int Status Mask */

#define CMSDK_DUALTIMER1_MASKINTSTAT_Pos     0                                                /* CMSDK_DUALTIMER1 MASKINTSTAT: Mask Int Status Position */
#define CMSDK_DUALTIMER1_MASKINTSTAT_Msk     (0x1ul << CMSDK_DUALTIMER1_MASKINTSTAT_Pos)      /* CMSDK_DUALTIMER1 MASKINTSTAT: Mask Int Status Mask */

#define CMSDK_DUALTIMER1_BGLOAD_Pos          0                                                /* CMSDK_DUALTIMER1 BGLOAD: Background Load Position */
#define CMSDK_DUALTIMER1_BGLOAD_Msk          (0xFFFFFFFFul << CMSDK_DUALTIMER1_BGLOAD_Pos)    /* CMSDK_DUALTIMER1 BGLOAD: Background Load Mask */

#define CMSDK_DUALTIMER2_LOAD_Pos            0                                                /* CMSDK_DUALTIMER2 LOAD: LOAD Position */
#define CMSDK_DUALTIMER2_LOAD_Msk            (0xFFFFFFFFul << CMSDK_DUALTIMER2_LOAD_Pos)      /* CMSDK_DUALTIMER2 LOAD: LOAD Mask */

#define CMSDK_DUALTIMER2_VALUE_Pos           0                                                /* CMSDK_DUALTIMER2 VALUE: VALUE Position */
#define CMSDK_DUALTIMER2_VALUE_Msk           (0xFFFFFFFFul << CMSDK_DUALTIMER2_VALUE_Pos)     /* CMSDK_DUALTIMER2 VALUE: VALUE Mask */

#define CMSDK_DUALTIMER2_CTRL_EN_Pos         7                                                /* CMSDK_DUALTIMER2 CTRL_EN: CTRL Enable Position */
#define CMSDK_DUALTIMER2_CTRL_EN_Msk         (0x1ul << CMSDK_DUALTIMER2_CTRL_EN_Pos)          /* CMSDK_DUALTIMER2 CTRL_EN: CTRL Enable Mask */

#define CMSDK_DUALTIMER2_CTRL_MODE_Pos       6                                                /* CMSDK_DUALTIMER2 CTRL_MODE: CTRL MODE Position */
#define CMSDK_DUALTIMER2_CTRL_MODE_Msk       (0x1ul << CMSDK_DUALTIMER2_CTRL_MODE_Pos)        /* CMSDK_DUALTIMER2 CTRL_MODE: CTRL MODE Mask */

#define CMSDK_DUALTIMER2_CTRL_INTEN_Pos      5                                                /* CMSDK_DUALTIMER2 CTRL_INTEN: CTRL Int Enable Position */
#define CMSDK_DUALTIMER2_CTRL_INTEN_Msk      (0x1ul << CMSDK_DUALTIMER2_CTRL_INTEN_Pos)       /* CMSDK_DUALTIMER2 CTRL_INTEN: CTRL Int Enable Mask */

#define CMSDK_DUALTIMER2_CTRL_PRESCALE_Pos   2                                                /* CMSDK_DUALTIMER2 CTRL_PRESCALE: CTRL PRESCALE Position */
#define CMSDK_DUALTIMER2_CTRL_PRESCALE_Msk   (0x3ul << CMSDK_DUALTIMER2_CTRL_PRESCALE_Pos)    /* CMSDK_DUALTIMER2 CTRL_PRESCALE: CTRL PRESCALE Mask */

#define CMSDK_DUALTIMER2_CTRL_SIZE_Pos       1                                                /* CMSDK_DUALTIMER2 CTRL_SIZE: CTRL SIZE Position */
#define CMSDK_DUALTIMER2_CTRL_SIZE_Msk       (0x1ul << CMSDK_DUALTIMER2_CTRL_SIZE_Pos)        /* CMSDK_DUALTIMER2 CTRL_SIZE: CTRL SIZE Mask */

#define CMSDK_DUALTIMER2_CTRL_ONESHOOT_Pos   0                                                /* CMSDK_DUALTIMER2 CTRL_ONESHOOT: CTRL ONESHOOT Position */
#define CMSDK_DUALTIMER2_CTRL_ONESHOOT_Msk   (0x1ul << CMSDK_DUALTIMER2_CTRL_ONESHOOT_Pos)    /* CMSDK_DUALTIMER2 CTRL_ONESHOOT: CTRL ONESHOOT Mask */

#define CMSDK_DUALTIMER2_INTCLR_Pos          0                                                /* CMSDK_DUALTIMER2 INTCLR: INT Clear Position */
#define CMSDK_DUALTIMER2_INTCLR_Msk          (0x1ul << CMSDK_DUALTIMER2_INTCLR_Pos)           /* CMSDK_DUALTIMER2 INTCLR: INT Clear  Mask */

#define CMSDK_DUALTIMER2_RAWINTSTAT_Pos      0                                                /* CMSDK_DUALTIMER2 RAWINTSTAT: Raw Int Status Position */
#define CMSDK_DUALTIMER2_RAWINTSTAT_Msk      (0x1ul << CMSDK_DUALTIMER2_RAWINTSTAT_Pos)       /* CMSDK_DUALTIMER2 RAWINTSTAT: Raw Int Status Mask */

#define CMSDK_DUALTIMER2_MASKINTSTAT_Pos     0                                                /* CMSDK_DUALTIMER2 MASKINTSTAT: Mask Int Status Position */
#define CMSDK_DUALTIMER2_MASKINTSTAT_Msk     (0x1ul << CMSDK_DUALTIMER2_MASKINTSTAT_Pos)      /* CMSDK_DUALTIMER2 MASKINTSTAT: Mask Int Status Mask */

#define CMSDK_DUALTIMER2_BGLOAD_Pos          0                                                /* CMSDK_DUALTIMER2 BGLOAD: Background Load Position */
#define CMSDK_DUALTIMER2_BGLOAD_Msk          (0xFFFFFFFFul << CMSDK_DUALTIMER2_BGLOAD_Pos)    /* CMSDK_DUALTIMER2 BGLOAD: Background Load Mask */


typedef struct
{
  __IO uint32_t TimerLoad;                   /* Offset: 0x000 (R/W) Timer Load */
  __I  uint32_t TimerValue;                  /* Offset: 0x000 (R/W) Timer Counter Current Value */
  __IO uint32_t TimerControl;                /* Offset: 0x000 (R/W) Timer Control */
  __O  uint32_t TimerIntClr;                 /* Offset: 0x000 (R/W) Timer Interrupt Clear */
  __I  uint32_t TimerRIS;                    /* Offset: 0x000 (R/W) Timer Raw Interrupt Status */
  __I  uint32_t TimerMIS;                    /* Offset: 0x000 (R/W) Timer Masked Interrupt Status */
  __IO uint32_t TimerBGLoad;                 /* Offset: 0x000 (R/W) Background Load Register */
} CMSDK_DUALTIMER_SINGLE_TypeDef;

/* CMSDK_DUALTIMER_SINGLE LOAD Register Definitions */
#define CMSDK_DUALTIMER_LOAD_Pos             0                                               /* CMSDK_DUALTIMER LOAD: LOAD Position */
#define CMSDK_DUALTIMER_LOAD_Msk             (0xFFFFFFFFul << CMSDK_DUALTIMER_LOAD_Pos)      /* CMSDK_DUALTIMER LOAD: LOAD Mask */

/* CMSDK_DUALTIMER_SINGLE VALUE Register Definitions */
#define CMSDK_DUALTIMER_VALUE_Pos            0                                               /* CMSDK_DUALTIMER VALUE: VALUE Position */
#define CMSDK_DUALTIMER_VALUE_Msk            (0xFFFFFFFFul << CMSDK_DUALTIMER_VALUE_Pos)     /* CMSDK_DUALTIMER VALUE: VALUE Mask */

/* CMSDK_DUALTIMER_SINGLE CTRL Register Definitions */
#define CMSDK_DUALTIMER_CTRL_EN_Pos          7                                               /* CMSDK_DUALTIMER CTRL_EN: CTRL Enable Position */
#define CMSDK_DUALTIMER_CTRL_EN_Msk          (0x1ul << CMSDK_DUALTIMER_CTRL_EN_Pos)          /* CMSDK_DUALTIMER CTRL_EN: CTRL Enable Mask */

#define CMSDK_DUALTIMER_CTRL_MODE_Pos        6                                               /* CMSDK_DUALTIMER CTRL_MODE: CTRL MODE Position */
#define CMSDK_DUALTIMER_CTRL_MODE_Msk        (0x1ul << CMSDK_DUALTIMER_CTRL_MODE_Pos)        /* CMSDK_DUALTIMER CTRL_MODE: CTRL MODE Mask */

#define CMSDK_DUALTIMER_CTRL_INTEN_Pos       5                                               /* CMSDK_DUALTIMER CTRL_INTEN: CTRL Int Enable Position */
#define CMSDK_DUALTIMER_CTRL_INTEN_Msk       (0x1ul << CMSDK_DUALTIMER_CTRL_INTEN_Pos)       /* CMSDK_DUALTIMER CTRL_INTEN: CTRL Int Enable Mask */

#define CMSDK_DUALTIMER_CTRL_PRESCALE_Pos    2                                               /* CMSDK_DUALTIMER CTRL_PRESCALE: CTRL PRESCALE Position */
#define CMSDK_DUALTIMER_CTRL_PRESCALE_Msk    (0x3ul << CMSDK_DUALTIMER_CTRL_PRESCALE_Pos)    /* CMSDK_DUALTIMER CTRL_PRESCALE: CTRL PRESCALE Mask */

#define CMSDK_DUALTIMER_CTRL_SIZE_Pos        1                                               /* CMSDK_DUALTIMER CTRL_SIZE: CTRL SIZE Position */
#define CMSDK_DUALTIMER_CTRL_SIZE_Msk        (0x1ul << CMSDK_DUALTIMER_CTRL_SIZE_Pos)        /* CMSDK_DUALTIMER CTRL_SIZE: CTRL SIZE Mask */

#define CMSDK_DUALTIMER_CTRL_ONESHOOT_Pos    0                                               /* CMSDK_DUALTIMER CTRL_ONESHOOT: CTRL ONESHOOT Position */
#define CMSDK_DUALTIMER_CTRL_ONESHOOT_Msk    (0x1ul << CMSDK_DUALTIMER_CTRL_ONESHOOT_Pos)    /* CMSDK_DUALTIMER CTRL_ONESHOOT: CTRL ONESHOOT Mask */

/* CMSDK_DUALTIMER_SINGLE INTCLR Register Definitions */
#define CMSDK_DUALTIMER_INTCLR_Pos           0                                               /* CMSDK_DUALTIMER INTCLR: INT Clear Position */
#define CMSDK_DUALTIMER_INTCLR_Msk           (0x1ul << CMSDK_DUALTIMER_INTCLR_Pos)           /* CMSDK_DUALTIMER INTCLR: INT Clear  Mask */

/* CMSDK_DUALTIMER_SINGLE RIS Register Definitions */
#define CMSDK_DUALTIMER_RAWINTSTAT_Pos       0                                               /* CMSDK_DUALTIMER RAWINTSTAT: Raw Int Status Position */
#define CMSDK_DUALTIMER_RAWINTSTAT_Msk       (0x1ul << CMSDK_DUALTIMER_RAWINTSTAT_Pos)       /* CMSDK_DUALTIMER RAWINTSTAT: Raw Int Status Mask */

/* CMSDK_DUALTIMER_SINGLE MIS Register Definitions */
#define CMSDK_DUALTIMER_MASKINTSTAT_Pos      0                                               /* CMSDK_DUALTIMER MASKINTSTAT: Mask Int Status Position */
#define CMSDK_DUALTIMER_MASKINTSTAT_Msk      (0x1ul << CMSDK_DUALTIMER_MASKINTSTAT_Pos)      /* CMSDK_DUALTIMER MASKINTSTAT: Mask Int Status Mask */

/* CMSDK_DUALTIMER_SINGLE BGLOAD Register Definitions */
#define CMSDK_DUALTIMER_BGLOAD_Pos           0                                               /* CMSDK_DUALTIMER BGLOAD: Background Load Position */
#define CMSDK_DUALTIMER_BGLOAD_Msk           (0xFFFFFFFFul << CMSDK_DUALTIMER_BGLOAD_Pos)    /* CMSDK_DUALTIMER BGLOAD: Background Load Mask */


/*-------------------- General Purpose Input Output (GPIO) -------------------*/
typedef struct
{
  __IO   uint32_t  DATA;                     /* Offset: 0x000 (R/W) DATA Register */
  __IO   uint32_t  DATAOUT;                  /* Offset: 0x004 (R/W) Data Output Latch Register */
         uint32_t  RESERVED0[2];
  __IO   uint32_t  OUTENABLESET;             /* Offset: 0x010 (R/W) Output Enable Set Register */
  __IO   uint32_t  OUTENABLECLR;             /* Offset: 0x014 (R/W) Output Enable Clear Register */
  __IO   uint32_t  ALTFUNCSET;               /* Offset: 0x018 (R/W) Alternate Function Set Register */
  __IO   uint32_t  ALTFUNCCLR;               /* Offset: 0x01C (R/W) Alternate Function Clear Register */
  __IO   uint32_t  INTENSET;                 /* Offset: 0x020 (R/W) Interrupt Enable Set Register */
  __IO   uint32_t  INTENCLR;                 /* Offset: 0x024 (R/W) Interrupt Enable Clear Register */
  __IO   uint32_t  INTTYPESET;               /* Offset: 0x028 (R/W) Interrupt Type Set Register */
  __IO   uint32_t  INTTYPECLR;               /* Offset: 0x02C (R/W) Interrupt Type Clear Register */
  __IO   uint32_t  INTPOLSET;                /* Offset: 0x030 (R/W) Interrupt Polarity Set Register */
  __IO   uint32_t  INTPOLCLR;                /* Offset: 0x034 (R/W) Interrupt Polarity Clear Register */
  union {
    __I    uint32_t  INTSTATUS;              /* Offset: 0x038 (R/ ) Interrupt Status Register */
    __O    uint32_t  INTCLEAR;               /* Offset: 0x038 ( /W) Interrupt Clear Register */
    };
         uint32_t RESERVED1[241];
  __IO   uint32_t LB_MASKED[256];            /* Offset: 0x400 - 0x7FC Lower byte Masked Access Register (R/W) */
  __IO   uint32_t UB_MASKED[256];            /* Offset: 0x800 - 0xBFC Upper byte Masked Access Register (R/W) */
} CMSDK_GPIO_TypeDef;

/* CMSDK_GPIO DATA Register Definitions */
#define CMSDK_GPIO_DATA_Pos            0                                          /* CMSDK_GPIO DATA: DATA Position */
#define CMSDK_GPIO_DATA_Msk            (0xFFFFul << CMSDK_GPIO_DATA_Pos)          /* CMSDK_GPIO DATA: DATA Mask */

/* CMSDK_GPIO DATAOUT Register Definitions */
#define CMSDK_GPIO_DATAOUT_Pos         0                                          /* CMSDK_GPIO DATAOUT: DATAOUT Position */
#define CMSDK_GPIO_DATAOUT_Msk         (0xFFFFul << CMSDK_GPIO_DATAOUT_Pos)       /* CMSDK_GPIO DATAOUT: DATAOUT Mask */

/* CMSDK_GPIO OUTENSET Register Definitions */
#define CMSDK_GPIO_OUTENSET_Pos        0                                          /* CMSDK_GPIO OUTEN: OUTEN Position */
#define CMSDK_GPIO_OUTENSET_Msk        (0xFFFFul << CMSDK_GPIO_OUTEN_Pos)         /* CMSDK_GPIO OUTEN: OUTEN Mask */

/* CMSDK_GPIO OUTENCLR Register Definitions */
#define CMSDK_GPIO_OUTENCLR_Pos        0                                          /* CMSDK_GPIO OUTEN: OUTEN Position */
#define CMSDK_GPIO_OUTENCLR_Msk        (0xFFFFul << CMSDK_GPIO_OUTEN_Pos)         /* CMSDK_GPIO OUTEN: OUTEN Mask */

/* CMSDK_GPIO ALTFUNCSET Register Definitions */
#define CMSDK_GPIO_ALTFUNCSET_Pos      0                                          /* CMSDK_GPIO ALTFUNC: ALTFUNC Position */
#define CMSDK_GPIO_ALTFUNCSET_Msk      (0xFFFFul << CMSDK_GPIO_ALTFUNC_Pos)       /* CMSDK_GPIO ALTFUNC: ALTFUNC Mask */

/* CMSDK_GPIO ALTFUNCCLR Register Definitions */
#define CMSDK_GPIO_ALTFUNCCLR_Pos      0                                          /* CMSDK_GPIO ALTFUNC: ALTFUNC Position */
#define CMSDK_GPIO_ALTFUNCCLR_Msk      (0xFFFFul << CMSDK_GPIO_ALTFUNC_Pos)       /* CMSDK_GPIO ALTFUNC: ALTFUNC Mask */

/* CMSDK_GPIO INTENSET Register Definitions */
#define CMSDK_GPIO_INTENSET_Pos        0                                          /* CMSDK_GPIO INTEN: INTEN Position */
#define CMSDK_GPIO_INTENSET_Msk        (0xFFFFul << CMSDK_GPIO_INTEN_Pos)         /* CMSDK_GPIO INTEN: INTEN Mask */

/* CMSDK_GPIO INTENCLR Register Definitions */
#define CMSDK_GPIO_INTENCLR_Pos        0                                          /* CMSDK_GPIO INTEN: INTEN Position */
#define CMSDK_GPIO_INTENCLR_Msk        (0xFFFFul << CMSDK_GPIO_INTEN_Pos)         /* CMSDK_GPIO INTEN: INTEN Mask */

/* CMSDK_GPIO INTTYPESET Register Definitions */
#define CMSDK_GPIO_INTTYPESET_Pos      0                                          /* CMSDK_GPIO INTTYPE: INTTYPE Position */
#define CMSDK_GPIO_INTTYPESET_Msk      (0xFFFFul << CMSDK_GPIO_INTTYPE_Pos)       /* CMSDK_GPIO INTTYPE: INTTYPE Mask */

/* CMSDK_GPIO INTTYPECLR Register Definitions */
#define CMSDK_GPIO_INTTYPECLR_Pos      0                                          /* CMSDK_GPIO INTTYPE: INTTYPE Position */
#define CMSDK_GPIO_INTTYPECLR_Msk      (0xFFFFul << CMSDK_GPIO_INTTYPE_Pos)       /* CMSDK_GPIO INTTYPE: INTTYPE Mask */

/* CMSDK_GPIO INTPOLSET Register Definitions */
#define CMSDK_GPIO_INTPOLSET_Pos       0                                          /* CMSDK_GPIO INTPOL: INTPOL Position */
#define CMSDK_GPIO_INTPOLSET_Msk       (0xFFFFul << CMSDK_GPIO_INTPOL_Pos)        /* CMSDK_GPIO INTPOL: INTPOL Mask */

/* CMSDK_GPIO INTPOLCLR Register Definitions */
#define CMSDK_GPIO_INTPOLCLR_Pos       0                                          /* CMSDK_GPIO INTPOL: INTPOL Position */
#define CMSDK_GPIO_INTPOLCLR_Msk       (0xFFFFul << CMSDK_GPIO_INTPOL_Pos)        /* CMSDK_GPIO INTPOL: INTPOL Mask */

/* CMSDK_GPIO INTSTATUS Register Definitions */
#define CMSDK_GPIO_INTSTATUS_Pos       0                                          /* CMSDK_GPIO INTSTATUS: INTSTATUS Position */
#define CMSDK_GPIO_INTSTATUS_Msk       (0xFFul << CMSDK_GPIO_INTSTATUS_Pos)       /* CMSDK_GPIO INTSTATUS: INTSTATUS Mask */

/* CMSDK_GPIO INTCLEAR Register Definitions */
#define CMSDK_GPIO_INTCLEAR_Pos        0                                          /* CMSDK_GPIO INTCLEAR: INTCLEAR Position */
#define CMSDK_GPIO_INTCLEAR_Msk        (0xFFul << CMSDK_GPIO_INTCLEAR_Pos)        /* CMSDK_GPIO INTCLEAR: INTCLEAR Mask */

/* CMSDK_GPIO MASKLOWBYTE Register Definitions */
#define CMSDK_GPIO_MASKLOWBYTE_Pos     0                                          /* CMSDK_GPIO MASKLOWBYTE: MASKLOWBYTE Position */
#define CMSDK_GPIO_MASKLOWBYTE_Msk     (0x00FFul << CMSDK_GPIO_MASKLOWBYTE_Pos)   /* CMSDK_GPIO MASKLOWBYTE: MASKLOWBYTE Mask */

/* CMSDK_GPIO MASKHIGHBYTE Register Definitions */
#define CMSDK_GPIO_MASKHIGHBYTE_Pos    0                                          /* CMSDK_GPIO MASKHIGHBYTE: MASKHIGHBYTE Position */
#define CMSDK_GPIO_MASKHIGHBYTE_Msk    (0xFF00ul << CMSDK_GPIO_MASKHIGHBYTE_Pos)  /* CMSDK_GPIO MASKHIGHBYTE: MASKHIGHBYTE Mask */


/*------------- System Control (SYSCON) --------------------------------------*/
typedef struct
{
  __IO   uint32_t  REMAP;                    /* Offset: 0x000 (R/W) Remap Control Register */
  __IO   uint32_t  PMUCTRL;                  /* Offset: 0x004 (R/W) PMU Control Register */
  __IO   uint32_t  RESETOP;                  /* Offset: 0x008 (R/W) Reset Option Register */
  __IO   uint32_t  EMICTRL;                  /* Offset: 0x00C (R/W) EMI Control Register */
  __IO   uint32_t  RSTINFO;                  /* Offset: 0x010 (R/W) Reset Information Register */
} CMSDK_SYSCON_TypeDef;

/* CMSDK_SYSCON REMAP Register Definitions */
#define CMSDK_SYSCON_REMAP_Pos                 0
#define CMSDK_SYSCON_REMAP_Msk                 (0x01ul << CMSDK_SYSCON_REMAP_Pos)               /* CMSDK_SYSCON MEME_CTRL: REMAP Mask */

/* CMSDK_SYSCON PMUCTRL Register Definitions */
#define CMSDK_SYSCON_PMUCTRL_EN_Pos            0
#define CMSDK_SYSCON_PMUCTRL_EN_Msk            (0x01ul << CMSDK_SYSCON_PMUCTRL_EN_Pos)          /* CMSDK_SYSCON PMUCTRL: PMUCTRL ENABLE Mask */

/* CMSDK_SYSCON LOCKUPRST Register Definitions */
#define CMSDK_SYSCON_LOCKUPRST_RESETOP_Pos     0
#define CMSDK_SYSCON_LOCKUPRST_RESETOP_Msk     (0x01ul << CMSDK_SYSCON_LOCKUPRST_RESETOP_Pos)   /* CMSDK_SYSCON SYS_CTRL: LOCKUP RESET ENABLE Mask */

/* CMSDK_SYSCON EMICTRL Register Definitions */
#define CMSDK_SYSCON_EMICTRL_SIZE_Pos          24
#define CMSDK_SYSCON_EMICTRL_SIZE_Msk          (0x00001ul << CMSDK_SYSCON_EMICTRL_SIZE_Pos)     /* CMSDK_SYSCON EMICTRL: SIZE Mask */

#define CMSDK_SYSCON_EMICTRL_TACYC_Pos         16
#define CMSDK_SYSCON_EMICTRL_TACYC_Msk         (0x00007ul << CMSDK_SYSCON_EMICTRL_TACYC_Pos)    /* CMSDK_SYSCON EMICTRL: TURNAROUNDCYCLE Mask */

#define CMSDK_SYSCON_EMICTRL_WCYC_Pos          8
#define CMSDK_SYSCON_EMICTRL_WCYC_Msk          (0x00003ul << CMSDK_SYSCON_EMICTRL_WCYC_Pos)     /* CMSDK_SYSCON EMICTRL: WRITECYCLE Mask */

#define CMSDK_SYSCON_EMICTRL_RCYC_Pos          0
#define CMSDK_SYSCON_EMICTRL_RCYC_Msk          (0x00007ul << CMSDK_SYSCON_EMICTRL_RCYC_Pos)     /* CMSDK_SYSCON EMICTRL: READCYCLE Mask */

/* CMSDK_SYSCON RSTINFO Register Definitions */
#define CMSDK_SYSCON_RSTINFO_SYSRESETREQ_Pos   0
#define CMSDK_SYSCON_RSTINFO_SYSRESETREQ_Msk   (0x00001ul << CMSDK_SYSCON_RSTINFO_SYSRESETREQ_Pos) /* CMSDK_SYSCON RSTINFO: SYSRESETREQ Mask */

#define CMSDK_SYSCON_RSTINFO_WDOGRESETREQ_Pos  1
#define CMSDK_SYSCON_RSTINFO_WDOGRESETREQ_Msk  (0x00001ul << CMSDK_SYSCON_RSTINFO_WDOGRESETREQ_Pos) /* CMSDK_SYSCON RSTINFO: WDOGRESETREQ Mask */

#define CMSDK_SYSCON_RSTINFO_LOCKUPRESET_Pos   2
#define CMSDK_SYSCON_RSTINFO_LOCKUPRESET_Msk   (0x00001ul << CMSDK_SYSCON_RSTINFO_LOCKUPRESET_Pos) /* CMSDK_SYSCON RSTINFO: LOCKUPRESET Mask */




/*------------------- Watchdog ----------------------------------------------*/
typedef struct
{

  __IO    uint32_t  LOAD;                   /* Offset: 0x000 (R/W) Watchdog Load Register */
  __I     uint32_t  VALUE;                  /* Offset: 0x004 (R/ ) Watchdog Value Register */
  __IO    uint32_t  CTRL;                   /* Offset: 0x008 (R/W) Watchdog Control Register */
  __O     uint32_t  INTCLR;                 /* Offset: 0x00C ( /W) Watchdog Clear Interrupt Register */
  __I     uint32_t  RAWINTSTAT;             /* Offset: 0x010 (R/ ) Watchdog Raw Interrupt Status Register */
  __I     uint32_t  MASKINTSTAT;            /* Offset: 0x014 (R/ ) Watchdog Interrupt Status Register */
        uint32_t  RESERVED0[762];
  __IO    uint32_t  LOCK;                   /* Offset: 0xC00 (R/W) Watchdog Lock Register */
        uint32_t  RESERVED1[191];
  __IO    uint32_t  ITCR;                   /* Offset: 0xF00 (R/W) Watchdog Integration Test Control Register */
  __O     uint32_t  ITOP;                   /* Offset: 0xF04 ( /W) Watchdog Integration Test Output Set Register */
}CMSDK_WATCHDOG_TypeDef;

/* CMSDK_WATCHDOG LOAD Register Definitions */
#define CMSDK_Watchdog_LOAD_Pos               0                                              /* CMSDK_Watchdog LOAD: LOAD Position */
#define CMSDK_Watchdog_LOAD_Msk              (0xFFFFFFFFul << CMSDK_Watchdog_LOAD_Pos)       /* CMSDK_Watchdog LOAD: LOAD Mask */

/* CMSDK_WATCHDOG VALUE Register Definitions */
#define CMSDK_Watchdog_VALUE_Pos              0                                              /* CMSDK_Watchdog VALUE: VALUE Position */
#define CMSDK_Watchdog_VALUE_Msk             (0xFFFFFFFFul << CMSDK_Watchdog_VALUE_Pos)      /* CMSDK_Watchdog VALUE: VALUE Mask */

/* CMSDK_WATCHDOG CTRL Register Definitions */
#define CMSDK_Watchdog_CTRL_RESEN_Pos         1                                              /* CMSDK_Watchdog CTRL_RESEN: Enable Reset Output Position */
#define CMSDK_Watchdog_CTRL_RESEN_Msk        (0x1ul << CMSDK_Watchdog_CTRL_RESEN_Pos)        /* CMSDK_Watchdog CTRL_RESEN: Enable Reset Output Mask */

#define CMSDK_Watchdog_CTRL_INTEN_Pos         0                                              /* CMSDK_Watchdog CTRL_INTEN: Int Enable Position */
#define CMSDK_Watchdog_CTRL_INTEN_Msk        (0x1ul << CMSDK_Watchdog_CTRL_INTEN_Pos)        /* CMSDK_Watchdog CTRL_INTEN: Int Enable Mask */

/* CMSDK_WATCHDOG INTCLR Register Definitions */
#define CMSDK_Watchdog_INTCLR_Pos             0                                              /* CMSDK_Watchdog INTCLR: Int Clear Position */
#define CMSDK_Watchdog_INTCLR_Msk            (0x1ul << CMSDK_Watchdog_INTCLR_Pos)            /* CMSDK_Watchdog INTCLR: Int Clear Mask */

/* CMSDK_WATCHDOG RAWINTSTAT Register Definitions */
#define CMSDK_Watchdog_RAWINTSTAT_Pos         0                                              /* CMSDK_Watchdog RAWINTSTAT: Raw Int Status Position */
#define CMSDK_Watchdog_RAWINTSTAT_Msk        (0x1ul << CMSDK_Watchdog_RAWINTSTAT_Pos)        /* CMSDK_Watchdog RAWINTSTAT: Raw Int Status Mask */

/* CMSDK_WATCHDOG MASKINTSTAT Register Definitions */
#define CMSDK_Watchdog_MASKINTSTAT_Pos        0                                              /* CMSDK_Watchdog MASKINTSTAT: Mask Int Status Position */
#define CMSDK_Watchdog_MASKINTSTAT_Msk       (0x1ul << CMSDK_Watchdog_MASKINTSTAT_Pos)       /* CMSDK_Watchdog MASKINTSTAT: Mask Int Status Mask */

/* CMSDK_WATCHDOG LOCK Register Definitions */
#define CMSDK_Watchdog_LOCK_Pos               0                                              /* CMSDK_Watchdog LOCK: LOCK Position */
#define CMSDK_Watchdog_LOCK_Msk              (0x1ul << CMSDK_Watchdog_LOCK_Pos)              /* CMSDK_Watchdog LOCK: LOCK Mask */

/* CMSDK_WATCHDOG INTEGTESTEN Register Definitions */
#define CMSDK_Watchdog_INTEGTESTEN_Pos        0                                              /* CMSDK_Watchdog INTEGTESTEN: Integration Test Enable Position */
#define CMSDK_Watchdog_INTEGTESTEN_Msk       (0x1ul << CMSDK_Watchdog_INTEGTESTEN_Pos)       /* CMSDK_Watchdog INTEGTESTEN: Integration Test Enable Mask */

/* CMSDK_WATCHDOG INTEGTESTOUTSET Register Definitions */
#define CMSDK_Watchdog_INTEGTESTOUTSET_Pos    1                                              /* CMSDK_Watchdog INTEGTESTOUTSET: Integration Test Output Set Position */
#define CMSDK_Watchdog_INTEGTESTOUTSET_Msk   (0x1ul << CMSDK_Watchdog_INTEGTESTOUTSET_Pos)   /* CMSDK_Watchdog INTEGTESTOUTSET: Integration Test Output Set Mask */



/* --------------------  End of section using anonymous unions  ------------------- */
#if defined ( __CC_ARM   )
  #pragma pop
#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) // armclang
  /* anonymous unions are enabled by default */
  //#pragma clang diagnostic pop
#elif defined(__ICCARM__)
  /* leave anonymous unions enabled */
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif




/* ================================================================================ */
/* ================              Peripheral memory map             ================ */
/* ================================================================================ */

/* Non Secure IoT Kit peripherals                                                                  */
#define CMSDK_TIMER0_BASE       (0x40000000UL)
#define CMSDK_TIMER1_BASE       (0x40001000UL)
#define CMSDK_DUALTIMER_BASE    (0x40002000UL)
#define CMSDK_DUALTIMER_1_BASE  (CMSDK_DUALTIMER_BASE)
#define CMSDK_DUALTIMER_2_BASE  (CMSDK_DUALTIMER_BASE + 0x20UL)
#define CMSDK_WATCHDOG_BASE     (0x40081000UL)

#define CMSDK_SYSCTRL_BASE      (0x40116000UL)

/* ================================================================================ */
/* ================          Secure Peripheral memory map          ================ */
/* ================================================================================ */

/* Secure IoT Kit peripherals */
#define SEC_TIMER0_BASE       (0x50000000UL)
#define SEC_TIMER1_BASE       (0x50001000UL)
#define SEC_DUALTIMER_BASE    (0x50002000UL)
#define SEC_DUALTIMER_1_BASE  (SEC_DUALTIMER_BASE)
#define SEC_DUALTIMER_2_BASE  (SEC_DUALTIMER_BASE + 0x20UL)

#define SEC_SYSCTRL_BASE      (0x50116000UL)

/* ================================================================================ */
/* ================             Peripheral declaration             ================ */
/* ================================================================================ */

#define CMSDK_UART0             ((CMSDK_UART_TypeDef   *) CMSDK_UART0_BASE   )
#define CMSDK_UART1             ((CMSDK_UART_TypeDef   *) CMSDK_UART1_BASE   )
#define CMSDK_UART2             ((CMSDK_UART_TypeDef   *) CMSDK_UART2_BASE   )
#define CMSDK_UART3             ((CMSDK_UART_TypeDef   *) CMSDK_UART3_BASE   )
#define CMSDK_UART4             ((CMSDK_UART_TypeDef   *) CMSDK_UART4_BASE   )
#define CMSDK_UART5             ((CMSDK_UART_TypeDef   *) CMSDK_UART5_BASE   )
#define CMSDK_TIMER0            ((CMSDK_TIMER_TypeDef  *) CMSDK_TIMER0_BASE  )
#define CMSDK_TIMER1            ((CMSDK_TIMER_TypeDef  *) CMSDK_TIMER1_BASE  )
#define CMSDK_DUALTIMER         ((CMSDK_DUALTIMER_BOTH_TypeDef  *) CMSDK_DUALTIMER_BASE )
#define CMSDK_DUALTIMER1        ((CMSDK_DUALTIMER_SINGLE_TypeDef  *) CMSDK_DUALTIMER_1_BASE )
#define CMSDK_DUALTIMER2        ((CMSDK_DUALTIMER_SINGLE_TypeDef  *) CMSDK_DUALTIMER_2_BASE )
#define CMSDK_WATCHDOG          ((CMSDK_WATCHDOG_TypeDef  *) CMSDK_WATCHDOG_BASE   )
#define CMSDK_GPIO0             ((CMSDK_GPIO_TypeDef   *) CMSDK_GPIO0_BASE   )
#define CMSDK_GPIO1             ((CMSDK_GPIO_TypeDef   *) CMSDK_GPIO1_BASE   )
#define CMSDK_GPIO2             ((CMSDK_GPIO_TypeDef   *) CMSDK_GPIO2_BASE )
#define CMSDK_GPIO3             ((CMSDK_GPIO_TypeDef   *) CMSDK_GPIO3_BASE )
#define CMSDK_SYSCON            ((CMSDK_SYSCON_TypeDef *) CMSDK_SYSCTRL_BASE )

#define SEC_UART0               ((CMSDK_UART_TypeDef   *) SEC_UART0_BASE   )
#define SEC_UART1               ((CMSDK_UART_TypeDef   *) SEC_UART1_BASE   )
#define SEC_UART2               ((CMSDK_UART_TypeDef   *) SEC_UART2_BASE   )
#define SEC_UART3               ((CMSDK_UART_TypeDef   *) SEC_UART3_BASE   )
#define SEC_UART4               ((CMSDK_UART_TypeDef   *) SEC_UART4_BASE   )
#define SEC_UART5               ((CMSDK_UART_TypeDef   *) SEC_UART5_BASE   )
#define SEC_TIMER0              ((CMSDK_TIMER_TypeDef  *) SEC_TIMER0_BASE  )
#define SEC_TIMER1              ((CMSDK_TIMER_TypeDef  *) SEC_TIMER1_BASE  )
#define SEC_DUALTIMER           ((CMSDK_DUALTIMER_BOTH_TypeDef  *) SEC_DUALTIMER_BASE )
#define SEC_DUALTIMER1          ((CMSDK_DUALTIMER_SINGLE_TypeDef  *) SEC_DUALTIMER_1_BASE )
#define SEC_DUALTIMER2          ((CMSDK_DUALTIMER_SINGLE_TypeDef  *) SEC_DUALTIMER_2_BASE )
#define SEC_WATCHDOG            ((CMSDK_WATCHDOG_TypeDef  *) SEC_WATCHDOG_BASE   )
#define SEC_GPIO0               ((CMSDK_GPIO_TypeDef   *) SEC_GPIO0_BASE   )
#define SEC_GPIO1               ((CMSDK_GPIO_TypeDef   *) SEC_GPIO1_BASE   )
#define SEC_GPIO2               ((CMSDK_GPIO_TypeDef   *) SEC_GPIO2_BASE )
#define SEC_GPIO3               ((CMSDK_GPIO_TypeDef   *) SEC_GPIO3_BASE )
#define SEC_SYSCON              ((CMSDK_SYSCON_TypeDef *) SEC_SYSCTRL_BASE )

/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/

#define CMSDK_GPIO0_BASE         (0x41100000ul)       /* User GPIO 0 Base Address   */
#define CMSDK_GPIO1_BASE         (0x41101000ul)       /* User GPIO 0 Base Address   */
#define CMSDK_GPIO2_BASE         (0x41102000ul)       /* User GPIO 0 Base Address   */
#define CMSDK_GPIO3_BASE         (0x41103000ul)       /* User GPIO 0 Base Address   */

#define MPS3_I2C0_BASE           (0x49200000ul)       /* Touch Screen I2C Base Address */
#define MPS3_I2C1_BASE           (0x49201000ul)       /* Audio Interface I2C Base Address */
#define MPS3_SSP2_BASE           (0x49202000ul)       /* ADC SPI PL022 Base Address   */
#define MPS3_SSP3_BASE           (0x49203000ul)       /* Shield 0 SPI PL022 Base Address   */

#define MPS3_SSP4_BASE           (0x49204000ul)       /* Shield 1 SPI PL022 Base Address   */
#define MPS3_I2C2_BASE           (0x49205000ul)       /* Shield 0 SBCon Base Address */
#define MPS3_I2C3_BASE           (0x49206000ul)       /* Shield 1 SBCon Base Address */

#define MPS3_I2C4_BASE           (0x49207000ul)       /* HDMI I2C SBCon Base Address */
#define MPS3_I2C5_BASE           (0x49208000ul)       /* DDR EPROM I2C SBCon Base Address */

#define MPS3_SCC_BASE            (0x49300000ul)       /* SCC Base Address    */
#define MPS3_AAIC_I2S_BASE       (0x49301000ul)       /* Audio Interface I2S Base Address */
#define MPS3_FPGAIO_BASE         (0x49302000ul)       /* FPGA IO Base Address */
#define CMSDK_UART0_BASE         (0x49303000ul)       /* UART 0 Base Address */
#define CMSDK_UART1_BASE         (0x49304000ul)       /* UART 1 Base Address */
#define CMSDK_UART2_BASE         (0x49305000ul)       /* UART 2 Base Address */
#define CMSDK_UART3_BASE         (0x49306000ul)       /* UART 3 Base Address Shield 0*/
#define CMSDK_UART4_BASE         (0x49307000ul)       /* UART 4 Base Address Shield 1*/
#define CMSDK_UART5_BASE         (0x49308000ul)       /* UART 5 Base Address */
#define HDMI_AUDIO_BASE          (0x49309000ul)       /* HDMI AUDIO Base Address */
#define CLCD_CONFIG_BASE         (0x4930A000ul)       /* CLCD CONFIG Base Address */
#define RTC_BASE                 (0x4930B000ul)       /* RTC Base address */

#define SMSC9220_BASE            (0x41400000ul)       /* Ethernet SMSC9220 Base Address */
#define USB_BASE                 (0x41500000ul)       /* USB Base Address */
#define CMSDK_SDIO_BASE          (0x41700000ul)       /* User SDIO Base Address   */
#define CHARLCD_BASE             (0x4930A000ul)       /* HDLCD Base Address   */
#define MPS3_eMMC_BASE           (0x41702000ul)       /* User eMMC Base Address   */
#define USER_BASE                (0x41703000ul)       /* User ? Base Address */

#define QSPI_XIP_BASE            (0x41800000ul)       /* QSPI XIP config Base Address */
#define QSPI_WRITE_BASE          (0x41801000ul)       /* QSPI write config Base Address */

#define ARM_SYSTIMER0_BASE       (0x48000000ul)       /* Non-secure timer 0 peripheral */
#define ARM_SYSTIMER1_BASE       (0x48001000ul)       /* Non-secure timer 1 peripheral */
#define ARM_SYSTIMER2_BASE       (0x48002000ul)       /* Non-secure timer 2 peripheral */
#define ARM_SYSTIMER3_BASE       (0x48003000ul)       /* Non-secure timer 3 peripheral */

/******************************************************************************/
/*                      Secure Peripheral memory map                          */
/******************************************************************************/

#define SEC_GPIO0_BASE           (0x51100000ul)       /* User GPIO 0 Base Address   */
#define SEC_GPIO1_BASE           (0x51101000ul)       /* User GPIO 0 Base Address   */
#define SEC_GPIO2_BASE           (0x51102000ul)       /* User GPIO 0 Base Address   */
#define SEC_GPIO3_BASE           (0x51103000ul)       /* User GPIO 0 Base Address   */

#define SEC_I2C0_BASE            (0x59200000ul)       /* Touch Screen I2C Base Address */
#define SEC_I2C1_BASE            (0x59201000ul)       /* Audio Interface I2C Base Address */
#define SEC_SSP2_BASE            (0x59202000ul)       /* ADC SPI PL022 Base Address   */
#define SEC_SSP3_BASE            (0x59203000ul)       /* Shield 0 SPI PL022 Base Address   */
#define SEC_SSP4_BASE            (0x59204000ul)       /* Shield 1 SPI PL022 Base Address   */
#define SEC_I2C2_BASE            (0x59205000ul)       /* Shield 0 SBCon Base Address */
#define SEC_I2C3_BASE            (0x59206000ul)       /* Shield 1 SBCon Base Address */
#define SEC_I2C4_BASE            (0x59207000ul)       /* HDMI I2C SBCon Base Address */
#define SEC_I2C5_BASE            (0x59208000ul)       /* DDR EPROM I2C SBCon Base Address */

#define SEC_SCC_BASE             (0x59300000ul)       /* SCC Base Address    */
#define SEC_AAIC_I2S_BASE        (0x59301000ul)       /* Audio Interface I2S Base Address */
#define SEC_FPGAIO_BASE          (0x59302000ul)       /* FPGA IO Base Address */
#define SEC_UART0_BASE           (0x59303000ul)       /* UART 0 Base Address */
#define SEC_UART1_BASE           (0x59304000ul)       /* UART 1 Base Address */
#define SEC_UART2_BASE           (0x59305000ul)       /* UART 2 Base Address */
#define SEC_UART3_BASE           (0x59306000ul)       /* UART 3 Base Address Shield 0*/
#define SEC_UART4_BASE           (0x59307000ul)       /* UART 4 Base Address Shield 1*/
#define SEC_UART5_BASE           (0x59308000ul)       /* UART 5 Base Address */
#define SEC_HDMI_AUDIO_BASE      (0x59309000ul)       /* HDMI AUDIO Base Address */
#define SEC_CLCD_CONFIG_BASE     (0x5930A000ul)       /* CLCD CONFIG Base Address */
#define SEC_RTC_BASE             (0x5930B000ul)       /* RTC Base address */

#define SEC_SMSC9220_BASE        (0x51400000ul)       /* Ethernet SMSC9220 Base Address */
#define SEC_USB_BASE             (0x51500000ul)       /* USB Base Address */
#define SEC_SDIO_BASE            (0x51700000ul)       /* User SDIO Base Address   */
#define SEC_CLCD_BASE            (0x51701000ul)       /* HDLCD Base Address   */
#define SEC_MMC_BASE             (0x51702000ul)       /* User eMMC Base Address   */
#define SEC_USER_BASE            (0x51703000ul)       /* User ? Base Address */

#define SEC_QSPI_XIP_BASE        (0x51800000ul)       /* QSPI XIP config Base Address */
#define SEC_QSPI_WRITE_BASE      (0x51801000ul)       /* QSPI write config Base Address */

#define SEC_ARM_SYSTIMER0_BASE   (0x58000000ul)       /* Secure Timer 0 Alias */
#define SEC_ARM_SYSTIMER1_BASE   (0x58001000ul)       /* Secure Timer 1 Alias */
#define SEC_ARM_SYSTIMER2_BASE   (0x58002000ul)       /* Secure Timer 2 Alias */
#define SEC_ARM_SYSTIMER3_BASE   (0x58003000ul)       /* Secure Timer 2 Alias */

#define ARM_SYSCNT_CTRL_BASE     (0x58100000ul)
                                    
/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/

#define MPS3_TS_I2C             ((MPS3_I2C_TypeDef      *) MPS3_I2C0_BASE )
#define MPS3_AAIC_I2C           ((MPS3_I2C_TypeDef      *) MPS3_I2C1_BASE )
#define MPS3_AAIC_I2S           ((MPS3_I2S_TypeDef      *) MPS3_AAIC_I2S_BASE )
#define MPS3_FPGAIO             ((MPS3_FPGAIO_TypeDef   *) MPS3_FPGAIO_BASE )
#define MPS3_SCC                ((MPS3_SCC_TypeDef      *) MPS3_SCC_BASE )
#define MPS3_SSP0               ((MPS3_SSP_TypeDef      *) MPS3_SSP0_BASE )
#define MPS3_SSP1               ((MPS3_SSP_TypeDef      *) MPS3_SSP1_BASE )
#define MPS3_SSP2               ((MPS3_SSP_TypeDef      *) MPS3_SSP2_BASE )
#define SMSC9220                ((SMSC9220_TypeDef      *) SMSC9220_BASE)

#define ARM_SYSTIMER0           ((ARM_SYSTIMER_TypeDef  *) ARM_SYSTIMER0_BASE  )
#define ARM_SYSTIMER1           ((ARM_SYSTIMER_TypeDef  *) ARM_SYSTIMER1_BASE  )
#define ARM_SYSTIMER2           ((ARM_SYSTIMER_TypeDef  *) ARM_SYSTIMER2_BASE  )
#define ARM_SYSTIMER3           ((ARM_SYSTIMER_TypeDef  *) ARM_SYSTIMER3_BASE  )

/******************************************************************************/
/*                      Secure Peripheral declaration                         */
/******************************************************************************/

#define SEC_TS_I2C             ((MPS3_I2C_TypeDef      *) SEC_I2C0_BASE )
#define SEC_AAIC_I2C           ((MPS3_I2C_TypeDef      *) SEC_I2C1_BASE )
#define SEC_AAIC_I2S           ((MPS3_I2S_TypeDef      *) SEC_AAIC_I2S_BASE )
#define SEC_FPGAIO             ((MPS3_FPGAIO_TypeDef   *) SEC_FPGAIO_BASE )
#define SEC_SCC                ((MPS3_SCC_TypeDef      *) SEC_SCC_BASE )
#define SEC_SSP0               ((MPS3_SSP_TypeDef      *) SEC_SSP0_BASE )
#define SEC_SSP1               ((MPS3_SSP_TypeDef      *) SEC_SSP1_BASE )
#define SEC_SSP2               ((MPS3_SSP_TypeDef      *) SEC_SSP2_BASE )
#define SEC_SMSC9220           ((SMSC9220_TypeDef      *) SEC_SMSC9220_BASE)

#define SEC_ARM_SYSTIMER0      ((ARM_SYSTIMER_TypeDef  *) SEC_ARM_SYSTIMER0_BASE  )
#define SEC_ARM_SYSTIMER1      ((ARM_SYSTIMER_TypeDef  *) SEC_ARM_SYSTIMER1_BASE  )
#define SEC_ARM_SYSTIMER2      ((ARM_SYSTIMER_TypeDef  *) SEC_ARM_SYSTIMER2_BASE  )
#define SEC_ARM_SYSTIMER3      ((ARM_SYSTIMER_TypeDef  *) SEC_ARM_SYSTIMER3_BASE  )
#define SEC_ARM_SYSCOUNTER     ((ARM_SYSCNT_CTRL_TypeDef  *) ARM_SYSCNT_CTRL_BASE  )

/******************************************************************************/
/*                     General Function Definitions                           */
/******************************************************************************/

extern void i2c_delay(unsigned int tick);
extern void Sleepms(unsigned int msec);
extern void Sleepus(unsigned int usec);

/******************************************************************************/
/*                     General MACRO Definitions                              */
/******************************************************************************/

//#define DEBUG
#ifdef DEBUG
    #define debug(...)      printf(__VA_ARGS__)
#else
    #define debug(...)
#endif  // ifdef DEBUG


#endif /* __SMM_MPS3_H */
