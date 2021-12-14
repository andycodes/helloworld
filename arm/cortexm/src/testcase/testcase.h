#ifndef _COMMON_H_
#define _COMMON_H_

// Types
#undef FALSE
#undef TRUE
#define FALSE   0
#define TRUE    1

/*
 * Description:
 * Error codes - each module is assigned space for error codes from apERR_XXXX_START to apERR_XXXX_START+255.
 *
 * Implementation:
 * Define an enumerated type apError.  By using this it is possible to avoid the
 * need to specify individual values for the error constants, but can simply append
 * new constants to the list below.
 *
 * Code numbers with the top bit clear are generic errors.
 * Those with the top bit set (negative) are module-specific errors
 */
#ifndef _EXTN_ERROR_H
#define _EXTN_ERROR_H

typedef enum
{
/*---------------Generic errors---------------*/
apERR_NONE          =0,

apERR_BAD_PARAMETER =1,    // Call failed due to a parameter out of range.
apERR_UNSUPPORTED   =2,    // Call failed due to a parameter which was in range,
                           // but unsupported for this variant of the hardware.
apERR_BUSY          =3,    // Resource is already in use

/*--------------Specific errors---------------*/
/* Returns errors of the form 0xFFFFxxxx */
apERR_BUZZER_START  =  apERR_NONE         - 0x100,    /*Module apBUZZER*/
apERR_MMC_START     =  apERR_BUZZER_START - 0x100,    /*Module apMMC*/
apERR_SCI_START     =  apERR_MMC_START    - 0x100,    /*Module apSCI*/
apERR_UART0_START   =  apERR_SCI_START    - 0x100,    /*Module apUART0*/
apERR_UART1_START   =  apERR_UART0_START  - 0x100,    /*Module apUART1*/
apERR_IRDA_START    =  apERR_UART1_START  - 0x100,    /*Module apIRDA*/
apERR_LCD_START     =  apERR_IRDA_START   - 0x100,    /*Module apLCD*/
apERR_TSCI_START    =  apERR_LCD_START    - 0x100,    /*Module apTSCI*/
apERR_LCDBIAS_START =  apERR_TSCI_START   - 0x100,    /*Module apLCDBIAS*/
apERR_AACI_START    =  apERR_LCDBIAS_START- 0x100,    /*Module apAACI*/
apERR_LEDS_START    =  apERR_AACI_START   - 0x100,    /*Module apLEDS*/
apERR_SPI_START     =  apERR_LEDS_START   - 0x100,    /*Module apSPI*/
apERR_GPIO_START    =  apERR_SPI_START    - 0x100,    /*Module apGPIO*/
apERR_KYBD_START    =  apERR_GPIO_START   - 0x100,    /*Module apKYBD*/
apERR_MOUSE_START   =  apERR_KYBD_START   - 0x100,    /*Module apMOUSE*/
apERR_LANI_START    =  apERR_MOUSE_START  - 0x100,    /*Module apLANI*/
apERR_CLOCK_START   =  apERR_LANI_START   - 0x100,    /*Module apCLOCK*/
apERR_USB_START     =  apERR_CLOCK_START  - 0x100,    /*Module apUSB*/
apERR_MEM_START     =  apERR_USB_START    - 0x100,    /*Module apMEM*/
apERR_RTC_START     =  apERR_MEM_START    - 0x100,    /*Module apI2C_RTC*/
apERR_CHARLCD_START =  apERR_RTC_START    - 0x100,    /*Module apCharLCD*/
apERR_SSP_START     =  apERR_CHARLCD_START- 0x100,    /*Module SSP*/
apERR_DMA_START     =  apERR_SSP_START    - 0x100,    /*Module DMA*/
apERR_PCI_START     =  apERR_DMA_START    - 0x100,    /*Module PCI*/
apERR_TIMER_START   =  apERR_PCI_START    - 0x100,    /*Module Timer*/
apERR_SWITCH_START  =  apERR_TIMER_START  - 0x100,    /*Module apSWITCHES*/
apERR_HDLCD_START   =  apERR_SWITCH_START - 0x100,    /*Module apHDLCD*/
apERR_QSPI_START    =  apERR_HDLCD_START  - 0x100,    /*Module apQSPI*/
/*============================================*/

apERR_END                  // Dummy terminator
} apError;

#endif

// Bit control macros
#define HW_REG(base,offset) *((volatile unsigned int *)((base) + (offset)))

#define CREATE_MASK(msb, lsb)               (((1U << ((msb) - (lsb) + 1)) - 1) << (lsb))
#define MASK_BITS(arg, msb, lsb)            ((arg) & CREATE_MASK(msb, lsb))
#define EXTRACT_BITS(arg, msb, lsb)         (MASK_BITS(arg, msb, lsb) >> (lsb))
#define INSERT_BITS(arg, msb, lsb, value) \
    ((arg) = ((arg) & ~CREATE_MASK(msb, lsb)) | (((value) << (lsb)) & CREATE_MASK(msb, lsb)))

#define MASK_FIELD(arg, field)              MASK_BITS(arg, field##_MSB, field##_LSB)
#define EXTRACT_FIELD(arg, field)           EXTRACT_BITS(arg, field##_MSB, field##_LSB)
#define INSERT_FIELD(arg, field, value)     INSERT_BITS(arg, field##_MSB, field##_LSB, value)

#define SET_BIT(arg, bit)                   ((arg) |= (1 << (bit)))
#define CLEAR_BIT(arg, bit)                 ((arg) &= ~(1 << (bit)))
#define TEST_BIT(arg, bit)                  ((arg) & (1 << (bit)))

typedef enum sts
{
    TEST_S_UNKNOWN,
    TEST_S_NOTRUN,
    TEST_S_SUCCESS,
    TEST_S_FAILURE,
    MAX_STATUS
} Status_t;

typedef struct test
{
    apError     (*test)(void);
    int         auto_run;
    Status_t    status;
}Test_t;


#endif // _COMMON_H_
