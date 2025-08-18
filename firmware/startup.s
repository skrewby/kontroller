.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

.global reset_handler
.global vtab

/* Addresses defined in the linker script */
.word _sidata
.word _sdata
.word _edata
.word _sbss
.word _ebss

/*
    ARM Instructions Used
    movs r, #val        ; Write immediate value #val to register r
    add r1, r2, val     ; Perform r1 = r2 + val where val can be register or value
    ldr r, =var         ; Loads the address of var into register r
    ldr r1, [r2, r3]    ; Load value from address r2+r3 into register r1
    str r1, [r2, r3]    ; Store value of register r1 into address r2+r3
    str r1, [r2], #val  ; Store value of register r1 into address r2 then increement r2 by val
    cmp r1, r2          ; Sets flag registers depending on the result of r1-r2
                        ; N if (r1 < r2), Z if (r1 == r2), C if (r1 >= r2)
    bcc func            ; Jumps to func if C flag is equal 0
    b func              ; Jumps to func
    bl func             ; Copies address of next instruction to LR (register R14)
                        ; then jumps to func. Necessary to call into C code
*/

.section .text.reset_handler
.type reset_handler,%function
reset_handler:
    ldr sp, =_estack

/* We want to copy from _sidata to the region bounded by _sdata <= RAM < _edata */
data_copy:
    ldr r0, =_sdata
    ldr r1, =_edata
    ldr r2, =_sidata        /* Load address (LMA) of the start of .data */
    movs r3, #0             /* Used for offset access into flash memory */
    b data_copy_check_done

data_copy_loop:
    ldr r4, [r2, r3]        /* Value at location currently indexed in flash memory */
    str r4, [r0, r3]        /* Move 4 bytes from flash to sram */
    add r3, r3, #4          /* offset += 4 */

data_copy_check_done:
    add r5, r0, r3          /* Contains the address in RAM we're currently indexing */
    cmp r5, r1              /* while ((addr + offset) < _edata) */
    bcc data_copy_loop      /*   loop                           */

/* Set the .bss section bounded by _sbss <= RAM < _ebss to 0 in sram */
bss_zero:
    ldr r0, =_sbss          /* Current address in RAM we're indexing */
    ldr r1, =_ebss
    movs r2, #0             /* The value we will set the section to */
    b bss_zero_check_done

bss_zero_loop:
    str r2, [r0], #4        /* Set 4 bytes at addr to 0 then addr += 4 */

bss_zero_check_done:
    cmp r0, r1              /* while (addr < _ebss) */
    bcc bss_zero_loop       /*   loop               */
    bl main                 /* Everything now set up, let's move to a nice and comforting */
                            /* high level langauge like C by calling main() */

loop_infinite:
    b loop_infinite

.size reset_handler, .-reset_handler

/* Function called by default from the vector table if user does not provide one */
.section .text.default_handler,"ax",%progbits
default_handler:
    b default_handler

.size default_handler, .-default_handler

.section .vector_table,"a",%progbits
.type vtab, %object

vtab:
    .word _estack
    .word reset_handler
	.word	NMI_Handler
	.word	HardFault_Handler
	.word	MemManage_Handler
	.word	BusFault_Handler
	.word	UsageFault_Handler
	.word	0
	.word	0
	.word	0
	.word	0
	.word	SVC_Handler
	.word	DebugMon_Handler
	.word	0
	.word	PendSV_Handler
	.word	SysTick_Handler
	.word	WWDG_IRQHandler
	.word	PVD_PVM_IRQHandler
	.word	TAMP_STAMP_IRQHandler
	.word	RTC_WKUP_IRQHandler
	.word	FLASH_IRQHandler
	.word	RCC_IRQHandler
	.word	EXTI0_IRQHandler
	.word	EXTI1_IRQHandler
	.word	EXTI2_IRQHandler
	.word	EXTI3_IRQHandler
	.word	EXTI4_IRQHandler
	.word	DMA1_Channel1_IRQHandler
	.word	DMA1_Channel2_IRQHandler
	.word	DMA1_Channel3_IRQHandler
	.word	DMA1_Channel4_IRQHandler
	.word	DMA1_Channel5_IRQHandler
	.word	DMA1_Channel6_IRQHandler
	.word	DMA1_Channel7_IRQHandler
	.word	ADC1_IRQHandler
	.word	CAN1_TX_IRQHandler
	.word	CAN1_RX0_IRQHandler
	.word	CAN1_RX1_IRQHandler
	.word	CAN1_SCE_IRQHandler
	.word	EXTI9_5_IRQHandler
	.word	TIM1_BRK_TIM15_IRQHandler
	.word	TIM1_UP_TIM16_IRQHandler
	.word	TIM1_TRG_COM_IRQHandler
	.word	TIM1_CC_IRQHandler
	.word	TIM2_IRQHandler
	.word	0
	.word	0
	.word	I2C1_EV_IRQHandler
	.word	I2C1_ER_IRQHandler
	.word	I2C2_EV_IRQHandler
	.word	I2C2_ER_IRQHandler
	.word	SPI1_IRQHandler
	.word	SPI2_IRQHandler
	.word	USART1_IRQHandler
	.word	USART2_IRQHandler
	.word	USART3_IRQHandler
	.word	EXTI15_10_IRQHandler
	.word	RTC_Alarm_IRQHandler
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	SDMMC1_IRQHandler
	.word	0
	.word	SPI3_IRQHandler
	.word	0
	.word	0
	.word	TIM6_DAC_IRQHandler
	.word	TIM7_IRQHandler
	.word	DMA2_Channel1_IRQHandler
	.word	DMA2_Channel2_IRQHandler
	.word	DMA2_Channel3_IRQHandler
	.word	DMA2_Channel4_IRQHandler
	.word	DMA2_Channel5_IRQHandler
	.word	0
	.word	0
	.word	0
	.word	COMP_IRQHandler
	.word	LPTIM1_IRQHandler
	.word	LPTIM2_IRQHandler
	.word	USB_IRQHandler
	.word	DMA2_Channel6_IRQHandler
	.word	DMA2_Channel7_IRQHandler
	.word	LPUART1_IRQHandler
	.word	QUADSPI_IRQHandler
	.word	I2C3_EV_IRQHandler
	.word	I2C3_ER_IRQHandler
	.word	SAI1_IRQHandler
	.word	0
	.word	SWPMI1_IRQHandler
	.word	TSC_IRQHandler
	.word	LCD_IRQHandler
	.word	0
	.word	RNG_IRQHandler
	.word	FPU_IRQHandler
	.word	CRS_IRQHandler

.size vtab, .-vtab

.weak	NMI_Handler
.thumb_set NMI_Handler,default_handler

.weak	HardFault_Handler
.thumb_set HardFault_Handler,default_handler

.weak	MemManage_Handler
.thumb_set MemManage_Handler,default_handler

.weak	BusFault_Handler
.thumb_set BusFault_Handler,default_handler

.weak	UsageFault_Handler
.thumb_set UsageFault_Handler,default_handler

.weak	SVC_Handler
.thumb_set SVC_Handler,default_handler

.weak	DebugMon_Handler
.thumb_set DebugMon_Handler,default_handler

.weak	PendSV_Handler
.thumb_set PendSV_Handler,default_handler

.weak	SysTick_Handler
.thumb_set SysTick_Handler,default_handler

.weak	WWDG_IRQHandler
.thumb_set WWDG_IRQHandler,default_handler

.weak	PVD_PVM_IRQHandler
.thumb_set PVD_PVM_IRQHandler,default_handler

.weak	TAMP_STAMP_IRQHandler
.thumb_set TAMP_STAMP_IRQHandler,default_handler

.weak	RTC_WKUP_IRQHandler
.thumb_set RTC_WKUP_IRQHandler,default_handler

.weak	FLASH_IRQHandler
.thumb_set FLASH_IRQHandler,default_handler

.weak	RCC_IRQHandler
.thumb_set RCC_IRQHandler,default_handler

.weak	EXTI0_IRQHandler
.thumb_set EXTI0_IRQHandler,default_handler

.weak	EXTI1_IRQHandler
.thumb_set EXTI1_IRQHandler,default_handler

.weak	EXTI2_IRQHandler
.thumb_set EXTI2_IRQHandler,default_handler

.weak	EXTI3_IRQHandler
.thumb_set EXTI3_IRQHandler,default_handler

.weak	EXTI4_IRQHandler
.thumb_set EXTI4_IRQHandler,default_handler

.weak	DMA1_Channel1_IRQHandler
.thumb_set DMA1_Channel1_IRQHandler,default_handler

.weak	DMA1_Channel2_IRQHandler
.thumb_set DMA1_Channel2_IRQHandler,default_handler

.weak	DMA1_Channel3_IRQHandler
.thumb_set DMA1_Channel3_IRQHandler,default_handler

.weak	DMA1_Channel4_IRQHandler
.thumb_set DMA1_Channel4_IRQHandler,default_handler

.weak	DMA1_Channel5_IRQHandler
.thumb_set DMA1_Channel5_IRQHandler,default_handler

.weak	DMA1_Channel6_IRQHandler
.thumb_set DMA1_Channel6_IRQHandler,default_handler

.weak	DMA1_Channel7_IRQHandler
.thumb_set DMA1_Channel7_IRQHandler,default_handler

.weak	ADC1_IRQHandler
.thumb_set ADC1_IRQHandler,default_handler

.weak	CAN1_TX_IRQHandler
.thumb_set CAN1_TX_IRQHandler,default_handler

.weak	CAN1_RX0_IRQHandler
.thumb_set CAN1_RX0_IRQHandler,default_handler

.weak	CAN1_RX1_IRQHandler
.thumb_set CAN1_RX1_IRQHandler,default_handler

.weak	CAN1_SCE_IRQHandler
.thumb_set CAN1_SCE_IRQHandler,default_handler

.weak	EXTI9_5_IRQHandler
.thumb_set EXTI9_5_IRQHandler,default_handler

.weak	TIM1_BRK_TIM15_IRQHandler
.thumb_set TIM1_BRK_TIM15_IRQHandler,default_handler

.weak	TIM1_UP_TIM16_IRQHandler
.thumb_set TIM1_UP_TIM16_IRQHandler,default_handler

.weak	TIM1_TRG_COM_IRQHandler
.thumb_set TIM1_TRG_COM_IRQHandler,default_handler

.weak	TIM1_CC_IRQHandler
.thumb_set TIM1_CC_IRQHandler,default_handler

.weak	TIM2_IRQHandler
.thumb_set TIM2_IRQHandler,default_handler

.weak	I2C1_EV_IRQHandler
.thumb_set I2C1_EV_IRQHandler,default_handler

.weak	I2C1_ER_IRQHandler
.thumb_set I2C1_ER_IRQHandler,default_handler

.weak	I2C2_EV_IRQHandler
.thumb_set I2C2_EV_IRQHandler,default_handler

.weak	I2C2_ER_IRQHandler
.thumb_set I2C2_ER_IRQHandler,default_handler

.weak	SPI1_IRQHandler
.thumb_set SPI1_IRQHandler,default_handler

.weak	SPI2_IRQHandler
.thumb_set SPI2_IRQHandler,default_handler

.weak	USART1_IRQHandler
.thumb_set USART1_IRQHandler,default_handler

.weak	USART2_IRQHandler
.thumb_set USART2_IRQHandler,default_handler

.weak	USART3_IRQHandler
.thumb_set USART3_IRQHandler,default_handler

.weak	EXTI15_10_IRQHandler
.thumb_set EXTI15_10_IRQHandler,default_handler

.weak	RTC_Alarm_IRQHandler
.thumb_set RTC_Alarm_IRQHandler,default_handler

.weak	SDMMC1_IRQHandler
.thumb_set SDMMC1_IRQHandler,default_handler

.weak	SPI3_IRQHandler
.thumb_set SPI3_IRQHandler,default_handler

.weak	TIM6_DAC_IRQHandler
.thumb_set TIM6_DAC_IRQHandler,default_handler

.weak	TIM7_IRQHandler
.thumb_set TIM7_IRQHandler,default_handler

.weak	DMA2_Channel1_IRQHandler
.thumb_set DMA2_Channel1_IRQHandler,default_handler

.weak	DMA2_Channel2_IRQHandler
.thumb_set DMA2_Channel2_IRQHandler,default_handler

.weak	DMA2_Channel3_IRQHandler
.thumb_set DMA2_Channel3_IRQHandler,default_handler

.weak	DMA2_Channel4_IRQHandler
.thumb_set DMA2_Channel4_IRQHandler,default_handler

.weak	DMA2_Channel5_IRQHandler
.thumb_set DMA2_Channel5_IRQHandler,default_handler

.weak	COMP_IRQHandler
.thumb_set COMP_IRQHandler,default_handler

.weak	LPTIM1_IRQHandler
.thumb_set LPTIM1_IRQHandler,default_handler

.weak	LPTIM2_IRQHandler
.thumb_set LPTIM2_IRQHandler,default_handler

.weak	USB_IRQHandler
.thumb_set USB_IRQHandler,default_handler

.weak	DMA2_Channel6_IRQHandler
.thumb_set DMA2_Channel6_IRQHandler,default_handler

.weak	DMA2_Channel7_IRQHandler
.thumb_set DMA2_Channel7_IRQHandler,default_handler

.weak	LPUART1_IRQHandler
.thumb_set LPUART1_IRQHandler,default_handler

.weak	QUADSPI_IRQHandler
.thumb_set QUADSPI_IRQHandler,default_handler

.weak	I2C3_EV_IRQHandler
.thumb_set I2C3_EV_IRQHandler,default_handler

.weak	I2C3_ER_IRQHandler
.thumb_set I2C3_ER_IRQHandler,default_handler

.weak	SAI1_IRQHandler
.thumb_set SAI1_IRQHandler,default_handler

.weak	SWPMI1_IRQHandler
.thumb_set SWPMI1_IRQHandler,default_handler

.weak	TSC_IRQHandler
.thumb_set TSC_IRQHandler,default_handler

.weak	LCD_IRQHandler
.thumb_set LCD_IRQHandler,default_handler

.weak	RNG_IRQHandler
.thumb_set RNG_IRQHandler,default_handler

.weak	FPU_IRQHandler
.thumb_set FPU_IRQHandler,default_handler

.weak	CRS_IRQHandler
.thumb_set CRS_IRQHandler,default_handler
