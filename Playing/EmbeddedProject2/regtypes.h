#pragma once
// Undefine stuff defined by STM32 HAL/LL support headers.
#undef TIM2
#undef TIM3
#undef TIM4
#undef TIM5
#undef RCC
#undef CRC

#define bit volatile uint32_t

//#define RCC_CFGR ((RCC_CFGR_Reg_ptr)&(RCC->CFGR)) 
//#define RCC_AHB1ENR ((RCC_AHB1ENR_Reg_ptr)&(RCC->AHB1ENR)) 
//#define RCC_CR ((RCC_CR_Reg_ptr)&(RCC->CR)) 
//#define RCC_PLLCFGR ((RCC_PLLCFGR_Reg_ptr)&(RCC->PLLCFGR)) 
//#define GPIO_MODER(BASE) ((GPIO_MODER_Reg_ptr)&((BASE)->MODER)) 
//#define GPIO_OTYPER(BASE) ((GPIO_OTYPER_Reg_ptr)&((BASE)->OTYPER)) 
//#define GPIO_OSPEEDR(BASE) ((GPIO_OSPEEDR_Reg_ptr)&((BASE)->OSPEEDR)) 
#define PADTO(NAME,BYTES,TYPE) char NAME[BYTES-sizeof(TYPE)]
#define PADBY(NAME,BYTES) char NAME[BYTES]
// RCC Registers

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		bit SW : 2;
		bit SWS : 2;
		bit HPRE : 4;
		bit UNUSED2 : 2;
		bit PPRE1 : 3;
		bit PPRE2 : 3;
		bit RTCPRE : 5;
		bit MCO1 : 2;
		bit I2SSC : 1;
		bit MCO1_PRE : 3;
		bit MCO2_PRE : 3;
		bit MCO2 : 2;
	};
	uint32_t ALLBITS;
} RCC_CFGR_Reg, * RCC_CFGR_Reg_ptr;
typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		bit GPIOA_EN : 1;
		bit GPIOB_EN : 1;
		bit GPIOC_EN : 1;
		bit GPIOD_EN : 1;
		bit GPIOE_EN : 1;
		bit GPIOF_EN : 1;
		bit GPIOG_EN : 1;
		bit GPIOH_EN : 1;
		bit GPIOI_EN : 1;
		bit GPIOJ_EN : 1;
		bit GPIOK_EN : 1;
		bit UNUSED1 : 1;
		bit CRC_EN : 1;
		bit UNUSED2 : 5;
		bit BKPSRAM_EN : 1;
		bit UNUSED3 : 1;
		bit CCMDATARAM_EN : 1;
		bit DMA1_EN : 1;
		bit DMA2_EN : 1;
		bit DMA2D_EN : 1;
		bit UNUSED4 : 1;
		bit ETHMAC_EN : 1;
		bit ETHMACTX_EN : 1;
		bit ETHMACRX_EN : 1;
		bit ETHMACPTP_EN : 1;
		bit OTGHS_EN : 1;
		bit OTGHSULPI_EN : 1;
		bit UNUSED5 : 1;
	};
	uint32_t ALLBITS;
} RCC_AHB1ENR_Reg, * RCC_AHB1ENR_Reg_ptr;
typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		bit TIM2_EN : 1;
		bit TIM3_EN : 1;
		bit TIM4_EN : 1;
		bit TIM5_EN : 1;
		bit TIM6_EN : 1;
		bit TIM7_EN : 1;
		bit TIM12_EN : 1;
		bit TIM13_EN : 1;
		bit TIM14_EN : 1;
		bit RESERVED1 : 2;
		bit WWDG_EN : 1;
		bit RESERVED2 : 2;
		bit SPI2_EN : 1;
		bit SPI3_EN : 1;
		bit RESERVED3 : 1;
		bit USART2_EN : 1;
		bit USART3_EN : 1;
		bit UART4_EN : 1;
		bit UART5_EN : 1;
		bit I2C1_EN : 1;
		bit I2C2_EN : 1;
		bit I2C3_EN : 1;
		bit RESEEVED4 : 1;
		bit CAN1_EN : 1;
		bit CAN2_EN : 1;
		bit RESERVED5 : 1;
		bit PWR_EN : 1;
		bit DAC_EN : 1;
		bit RESERVED6 : 2;
		uint32_t ALLBITS;
	};
} RCC_APB1ENR_Reg, *RCC_APB1ENR_Reg_ptr;
typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		bit DCMI_EN : 1;
		bit UNUSED1 : 3;
		bit CRYP_EN : 1;
		bit HASH_EN : 1;
		bit RNG_EN : 1;
		bit OTGFS_EN : 1;
		bit UNUSED2: 8;
		bit UNUSED3 : 16;
	};
	uint32_t ALLBITS;
} RCC_AHB2ENR_Reg, * RCC_AHB2ENR_Reg_ptr;
typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		bit FSMC_EN : 1;
		bit UNUSED1 : 15;
		bit UNUSED2 : 16;
	};
	uint32_t ALLBITS;
} RCC_AHB3ENR_Reg, * RCC_AHB3ENR_Reg_ptr;
typedef union
{
	struct // STM32F407
	{
		// LSB at top, MSB at bottom
		bit HSI_ON : 1;
		bit HSI_RDY : 1;
		bit UNUSED1 : 1;
		bit HSI_TRIM : 5;
		bit HSI_CAL : 8;
		bit HSE_ON : 1;
		bit HSE_RDY : 1;
		bit HSE_BYP : 1;
		bit CSS_ON : 1;
		bit UNUSED2 : 4;
		bit PLL_ON : 1;
		bit PLL_RDY : 1;
		bit PLL_I2S_ON : 1;
		bit PLL_I2S_RDY: 1;
		bit UNUSED3 : 4;
	};
	uint32_t ALLBITS;
} RCC_CR_Reg, * RCC_CR_Reg_ptr;
typedef union
{
	struct // STM32F407
	{
		// LSB at top, MSB at bottom
		bit LSI_RDY_F : 1;
		bit LSE_RDY_F : 1;
		bit HSI_RDY_F : 1;
		bit HSE_RDY_F : 1;
		bit PLL_RDY_F : 1;
		bit PLL_I2S_RDY_F : 1;
		bit UNUSED : 1;
		bit CSS_F : 1;
		bit LSI_RDY_E : 1;
		bit LSE_RDY_E : 1;
		bit HSI_RDY_E : 1;
		bit HSE_RDY_E : 1;
		bit PLL_RDY_E : 1;
		bit PLL_I2S_RDY_E : 1;
		bit UNUSED2 : 2;
		bit LSI_RDY_C : 1;
		bit LSE_RDY_C : 1;
		bit HSI_RDY_C : 1;
		bit HSE_RDY_C : 1;
		bit PLL_RDY_C : 1;
		bit PLL_I2S_RDY_C : 1;
		bit UNUSED3 : 1;
		bit CSS_C : 1;
		bit UNUSED4 : 8;
	};
	uint32_t ALLBITS;
} RCC_CIR_Reg, * RCC_CIR_Reg_ptr;
typedef union
{
	struct 
	{
		// LSB at top, MSB at bottom
		bit PLL_M : 6;
		bit PLL_N : 9;
		bit UNUSED1 : 1;
		bit PLL_P : 2;
		bit UNUSED2 : 4;
		bit PLL_SRC : 1;
		bit UNUSED3 : 1;
		bit PLL_Q : 4;
		bit UNUSED4 : 4;
	};
	uint32_t ALLBITS;

} RCC_PLLCFGR_Reg, * RCC_PLLCFGR_Reg_ptr;

// GPIO Registers

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		bit MODER_0 : 2;
		bit MODER_1 : 2;
		bit MODER_2 : 2;
		bit MODER_3 : 2;
		bit MODER_4 : 2;
		bit MODER_5 : 2;
		bit MODER_6 : 2;
		bit MODER_7 : 2;
		bit MODER_8 : 2;
		bit MODER_9 : 2;
		bit MODER_10 : 2;
		bit MODER_11 : 2;
		bit MODER_12 : 2;
		bit MODER_13 : 2;
		bit MODER_14 : 2;
		bit MODER_15 : 2;
	};
	uint32_t ALLBITS;

} GPIO_MODER_Reg, * GPIO_MODER_Reg_ptr;
typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		bit OT_0 : 1;
		bit OT_1 : 1;
		bit OT_2 : 1;
		bit OT_3 : 1;
		bit OT_4 : 1;
		bit OT_5 : 1;
		bit OT_6 : 1;
		bit OT_7 : 1;
		bit OT_8 : 1;
		bit OT_9 : 1;
		bit OT_10 : 1;
		bit OT_11 : 1;
		bit OT_12 : 1;
		bit OT_13 : 1;
		bit OT_14 : 1;
		bit OT_15 : 1;
		bit UNUSED1 : 16;
	};
	uint32_t ALLBITS;

} GPIO_OTYPER_Reg, * GPIO_OTYPER_Reg_ptr;
typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		bit SPEED_0 : 2;
		bit SPEED_1 : 2;
		bit SPEED_2 : 2;
		bit SPEED_3 : 2;
		bit SPEED_4 : 2;
		bit SPEED_5 : 2;
		bit SPEED_6 : 2;
		bit SPEED_7 : 2;
		bit SPEED_8 : 2;
		bit SPEED_9 : 2;
		bit SPEED_10 : 2;
		bit SPEED_11 : 2;
		bit SPEED_12 : 2;
		bit SPEED_13 : 2;
		bit SPEED_14 : 2;
		bit SPEED_15 : 2;
	};
	uint32_t ALLBITS;

} GPIO_OSPEEDR_Reg, * GPIO_OSPEEDR_Reg_ptr;
typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		bit PUPDR_0 : 2;
		bit PUPDR_1 : 2;
		bit PUPDR_2 : 2;
		bit PUPDR_3 : 2;
		bit PUPDR_4 : 2;
		bit PUPDR_5 : 2;
		bit PUPDR_6 : 2;
		bit PUPDR_7 : 2;
		bit PUPDR_8 : 2;
		bit PUPDR_9 : 2;
		bit PUPDR_10 : 2;
		bit PUPDR_11 : 2;
		bit PUPDR_12 : 2;
		bit PUPDR_13 : 2;
		bit PUPDR_14 : 2;
		bit PUPDR_15 : 2;
	};
	uint32_t ALLBITS;

} GPIO_PUPDR_Reg, * GPIO_PUPDR_Reg_ptr;
typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		bit IDR_0 : 1;
		bit IDR_1 : 1;
		bit IDR_2 : 1;
		bit IDR_3 : 1;
		bit IDR_4 : 1;
		bit IDR_5 : 1;
		bit IDR_6 : 1;
		bit IDR_7 : 1;
		bit IDR_8 : 1;
		bit IDR_9 : 1;
		bit IDR_10 : 1;
		bit IDR_11 : 1;
		bit IDR_12 : 1;
		bit IDR_13 : 1;
		bit IDR_14 : 1;
		bit IDR_15 : 1;
		bit UNUSED : 16;
	};
	uint32_t ALLBITS;

} GPIO_IDR_Reg, * GPIO_IDR_Reg_ptr;
typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		bit ODR_0 : 1;
		bit ODR_1 : 1;
		bit ODR_2 : 1;
		bit ODR_3 : 1;
		bit ODR_4 : 1;
		bit ODR_5 : 1;
		bit ODR_6 : 1;
		bit ODR_7 : 1;
		bit ODR_8 : 1;
		bit ODR_9 : 1;
		bit ODR_10 : 1;
		bit ODR_11 : 1;
		bit ODR_12 : 1;
		bit ODR_13 : 1;
		bit ODR_14 : 1;
		bit ODR_15 : 1;
		bit UNUSED : 16;
	};
	uint32_t ALLBITS;

} GPIO_ODR_Reg, * GPIO_ODR_Reg_ptr;
typedef union
{
	struct
	{
		// All bits here are write only.
		// LSB at top, MSB at bottom
		bit BS_0 : 1;
		bit BS_1 : 1;
		bit BS_2 : 1;
		bit BS_3 : 1;
		bit BS_4 : 1;
		bit BS_5 : 1;
		bit BS_6 : 1;
		bit BS_7 : 1;
		bit BS_8 : 1;
		bit BS_9 : 1;
		bit BS_10 : 1;
		bit BS_11 : 1;
		bit BS_12 : 1;
		bit BS_13 : 1;
		bit BS_14 : 1;
		bit BS_15 : 1;
		bit BR_0 : 1;
		bit BR_1 : 1;
		bit BR_2 : 1;
		bit BR_3 : 1;
		bit BR_4 : 1;
		bit BR_5 : 1;
		bit BR_6 : 1;
		bit BR_7 : 1;
		bit BR_8 : 1;
		bit BR_9 : 1;
		bit BR_10 : 1;
		bit BR_11 : 1;
		bit BR_12 : 1;
		bit BR_13 : 1;
		bit BR_14 : 1;
		bit BR_15 : 1;
	};
	uint32_t ALLBITS;

} GPIO_BSRR_Reg, * GPIO_BSRR_Reg_ptr;
typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		bit LCK_0 : 1;
		bit LCK_1 : 1;
		bit LCK_2 : 1;
		bit LCK_3 : 1;
		bit LCK_4 : 1;
		bit LCK_5 : 1;
		bit LCK_6 : 1;
		bit LCK_7 : 1;
		bit LCK_8 : 1;
		bit LCK_9 : 1;
		bit LCK_10 : 1;
		bit LCK_11 : 1;
		bit LCK_12 : 1;
		bit LCK_13 : 1;
		bit LCK_14 : 1;
		bit LCK_15 : 1;
		bit LCK_K : 1;
		bit UNUSED : 15;
	};
	uint32_t ALLBITS;

} GPIO_LCKR_Reg, * GPIO_LCKR_Reg_ptr;
typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		bit AFRL_0 : 4;
		bit AFRL_1 : 4;
		bit AFRL_2 : 4;
		bit AFRL_3 : 4;
		bit AFRL_4 : 4;
		bit AFRL_5 : 4;
		bit AFRL_6 : 4;
		bit AFRL_7 : 4;
	};
	uint32_t ALLBITS;

} GPIO_AFRL_Reg, * GPIO_AFRL_Reg_ptr;
typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		bit AFRH_8 : 4;
		bit AFRH_9 : 4;
		bit AFRH_10 : 4;
		bit AFRH_11 : 4;
		bit AFRH_12 : 4;
		bit AFRH_13 : 4;
		bit AFRH_14 : 4;
		bit AFRH_15 : 4;
	};
	uint32_t ALLBITS;

} GPIO_AFRH_Reg, * GPIO_AFRH_Reg_ptr;
typedef struct
{
	GPIO_MODER_Reg MODER;
	GPIO_OTYPER_Reg OTYPER;
	GPIO_OSPEEDR_Reg SPEEDR;
	GPIO_PUPDR_Reg PUPDR;
	GPIO_IDR_Reg IDR;
	GPIO_ODR_Reg ODR;
	GPIO_BSRR_Reg BSRR;
	GPIO_LCKR_Reg LCKR;
	GPIO_AFRL_Reg AFRL;
	GPIO_AFRH_Reg AFRH;

} GPIO_Registers, * GPIO_Registers_ptr;
typedef struct
{
	GPIO_Registers Registers;
	PADTO(RESERVED, 1024, GPIO_Registers);
} GPIO_Device, GPIO_ptr;

// TIM2 - TIM5 Registers

typedef struct
{
	bit CEN : 1;
	bit UDIS : 1;
	bit URS : 1;
	bit OPM : 1;
	bit DIR : 1;
	bit CMS : 2;
	bit ARPE : 1;
	bit CKD : 2;
	bit RESERVED1 : 6;
	bit RESERVED2 : 16;
} TIM_CR1, *TIM_CR1_ptr;
typedef struct
{
	bit UNUSED1 : 3;
	bit CCDS : 1;
	bit MMS : 3;
	bit TI1 : 1;
	bit RESERVED1 : 8;
	bit RESERVED2 : 16;
} TIM_CR2, *TIM_CR2_ptr;
typedef struct
{
	bit SMS : 3;
	bit UNUSED1 : 1;
	bit TS : 3;
	bit MSM : 1;
	bit ETF : 4;
	bit ETPS : 2;
	bit ECE : 1;
	bit ETP : 1;
	bit UNUSED2 : 16;
} TIM_SMCR, *TIM_SMCR_ptr;
typedef struct
{
	bit UIE : 1;
	bit CC1IE : 1;
	bit CC2IE : 1;
	bit CC3IE : 1;
	bit CC4IE : 1;
	bit UNUSED1 : 1;
	bit TIE : 1;
	bit UNUSED2 : 1;
	bit UDE : 1;
	bit CC1DE : 1;
	bit CC2DE : 1;
	bit CC3DE : 1;
	bit CC4DE : 1;
	bit UNUSED3 : 1;
	bit TDE : 1;
	bit UNUSED4 : 1;
	bit UNUSED5 : 16;
} TIM_DIER, *TIM_DIER_ptr;
typedef struct
{
	bit UIF : 1;
	bit CC1IF : 1;
	bit CC2IF : 1;
	bit CC3IF : 1;
	bit CC4IF : 1;
	bit RESERVED1 : 1;
	bit TIF : 1;
	bit RESERVED2 : 2;
	bit CC1OF : 1;
	bit CC2OF : 1;
	bit CC3OF : 1;
	bit CC4OF : 1;
	bit RESERVED3 : 3;
	bit RESERVED4 : 16;
} TIM_SR, *TIM_SR_ptr;
typedef struct
{
	bit UG : 1;
	bit CC1G :1;
	bit CC2G : 1;
	bit CC3G : 1;
	bit CC4G : 1;
	bit RESERVED1 : 1;
	bit TG : 1;
	bit RESERVED : 25;
} TIM_EGR, *TIM_EGR_ptr;
// CCMR1 register when in output capture mode
typedef struct
{
	bit CC1S : 2;
	bit OC1FE : 1;
	bit OC1PE : 1;
	bit OC1M : 3;
	bit OC1CE : 1;
	bit CC2S : 2;
	bit OC2FE : 1;
	bit OC2PE : 1;
	bit OC2M : 3;
	bit OC2CE : 1;
	bit RESERVED : 16;
} TIM_CCMR1_OCM, *TIM_CCMR1_OCM_ptr;
// CCMR1 register when in input compare mode
typedef struct
{
	bit CC1S : 2;
	bit IC1PSC : 2;
	bit IC1F : 4;
	bit CC2S : 2;
	bit IC2PSC : 2;
	bit IC2F : 4;
	bit RESERVED : 16;
} TIM_CCMR1_ICM, *TIM_CCMR1_ICM_ptr;
// CCMR2 register when in output capture mode
typedef struct
{
	bit CC3S : 2;
	bit OC3FE : 1;
	bit OC3PE : 1;
	bit OC3M : 3;
	bit OC3CE : 1;
	bit CC4S : 2;
	bit OC4FE : 1;
	bit OC4PE : 1;
	bit OC4M : 3;
	bit OC4CE : 1;
	bit RESERVED : 16;
	
} TIM_CCMR2_OCM, *TIM_CCMR2_OCM_ptr;
// CCMR2 register when in input compare mode
typedef struct
{
	bit CC3S : 2;
	bit IC3PSC : 2;
	bit IC3F : 4;
	bit CC4S : 2;
	bit IC4PSC : 2;
	bit IC4F : 4;
	bit RESERVED : 16;
	
} TIM_CCMR2_ICM, *TIM_CCMR2_ICM_ptr;
typedef struct
{
	bit CC1E : 1;
	bit CC1P : 1;
	bit RESERVED1 : 1;
	bit CC1NP : 1;
	bit CC2E : 1;
	bit CC2P : 1;
	bit RESERVED2 : 1;
	bit CC2NP : 1;
	bit CC3E : 1;
	bit CC3P : 1;
    bit RESERVED3:1;
	bit CC3NP : 1;
	bit CC4E : 1;
	bit CC4P : 1;
	bit RESERVED4 : 1;
	bit CC4NP : 1;
	bit RESERVED5 : 16;
	
} TIM_CCER, *TIM_CCER_ptr;
typedef struct
{
	bit CNT : 16;
	bit RESERVED : 16;
	
} TIM_CNT, *TIM_CNT_ptr;
typedef struct
{
	bit PSC : 16;
	bit RESERVED : 16;
} TIM_PSC, *TIM_PSC_ptr;
typedef struct
{
	
} TIM_ARR, *TIM_ARR_ptr;
typedef struct
{
	
} TIM_CCR1, *TIM_CCR1_ptr;
typedef struct
{
	
} TIM_CCR2, *TIM_CCR2_ptr;
typedef struct
{
	
} TIM_CCR3, *TIM_CCR3_ptr;
typedef struct
{
	
} TIM_CCR4, *TIM_CCR4_ptr;
typedef struct
{
	
} TIM_DCR, *TIM_DCR_ptr;
typedef struct
{
	
} TIM_DMAR, *TIM_DMAR_ptr;
typedef struct
{
	
} TIM2_OR, *TIM2_OR_ptr;
typedef struct
{
	
} TIM5_OR, *TIM5_OR_ptr;

typedef struct
{
	TIM_CR1 CR1;
	TIM_CR2 CR2;
	TIM_SMCR SMCR;
	TIM_DIER DIER;
	TIM_SR SR;
	TIM_EGR EGR;
	union
	{
		TIM_CCMR1_OCM CCMR1_OCR;
		TIM_CCMR1_ICM CCMR1_ICM;
	};
	union
	{
		TIM_CCMR2_OCM CCMR2_OCR;
		TIM_CCMR2_ICM CCMR2_ICM;
	};
	TIM_CCER CCER;
	TIM_CNT CNT;
	TIM_PSC PSC;
	TIM_ARR ARR;
	TIM_CCR1 CCR1;
	TIM_CCR2 CCR2;
	TIM_CCR3 CCR3;
	TIM_CCR4 CCR4;
	TIM_DCR DCR;
	TIM_DMAR DMAR;
	TIM2_OR OR2;
	TIM5_OR OR5;

} TIM_BASIC_Registers, *TIM_BASIC_Registers_ptr;


typedef struct
{
	TIM_BASIC_Registers Registers;
	PADTO(RESERVED, 1024, TIM_BASIC_Registers);
} TIM_Basic, * TIM_Basic_ptr;
typedef struct
{
	TIM_Basic TIM2;
	TIM_Basic TIM3;
	TIM_Basic TIM4;
	TIM_Basic TIM5;

} APB1, *APB1_ptr;

typedef struct
{
	bit DRLOW : 16;
	bit DRHIGH : 16;
} CRC_DR, *CRC_DR_ptr;

typedef struct
{
	bit IDR : 8;
	bit RESERVED1 : 8;
	bit RESERVED2 : 16;
} CRC_IDR, *CRC_IDR_ptr;

typedef struct
{
	bit RESET : 1;
	bit RESERVED1 : 15;
	bit RESERVED2 : 16;
} CRC_CR, *CRC_CR_ptr;

typedef struct
{
	CRC_DR DR;
	CRC_IDR IDR;
	CRC_CR CR;
} CRC_Registers, CRC_Registers_ptr;

typedef struct
{
	RCC_CR_Reg CR; /*!< RCC clock control register,                                  Address offset: 0x00 */
	RCC_PLLCFGR_Reg PLLCFGR; /*!< RCC PLL configuration register,                              Address offset: 0x04 */
	RCC_CFGR_Reg CFGR; /*!< RCC clock configuration register,                            Address offset: 0x08 */
	RCC_CIR_Reg CIR; /*!< RCC clock interrupt register,                                Address offset: 0x0C */
	uint32_t AHB1RSTR; /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
	uint32_t AHB2RSTR; /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
	uint32_t AHB3RSTR; /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
	uint32_t      RESERVED0; /*!< Reserved, 0x1C                                                                    */
	uint32_t APB1RSTR; /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
	uint32_t APB2RSTR; /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
	uint32_t      RESERVED1[2]; /*!< Reserved, 0x28-0x2C                                                               */
	RCC_AHB1ENR_Reg AHB1ENR; /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
	RCC_AHB2ENR_Reg AHB2ENR; /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
	RCC_AHB3ENR_Reg AHB3ENR; /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
	uint32_t      RESERVED2; /*!< Reserved, 0x3C                                                                    */
	RCC_APB1ENR_Reg APB1ENR; /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
	uint32_t APB2ENR; /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
	uint32_t      RESERVED3[2]; /*!< Reserved, 0x48-0x4C                                                               */
	uint32_t AHB1LPENR; /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
	uint32_t AHB2LPENR; /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
	uint32_t AHB3LPENR; /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
	uint32_t      RESERVED4; /*!< Reserved, 0x5C                                                                    */
	uint32_t APB1LPENR; /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
	uint32_t APB2LPENR; /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
	uint32_t      RESERVED5[2]; /*!< Reserved, 0x68-0x6C                                                               */
	uint32_t BDCR; /*!< RCC Backup domain control register,                          Address offset: 0x70 */
	uint32_t CSR; /*!< RCC clock control & status register,                         Address offset: 0x74 */
	uint32_t      RESERVED6[2]; /*!< Reserved, 0x78-0x7C                                                               */
	uint32_t SSCGR; /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
	uint32_t PLLI2SCFGR; /*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */
} RCC_Registers, *RCC_Registers_ptr;

typedef struct
{
	// There is padding between peripherals that forces
	// each one to be at a particular offset from the
	// preceding peripheral.
	GPIO_Registers GPIO_A;
	PADTO(RESERVED1, 1024, GPIO_Registers);
	GPIO_Registers GPIO_B;
	PADTO(RESERVED2, 1024, GPIO_Registers);
	GPIO_Registers GPIO_C;
	PADTO(RESERVED3, 1024, GPIO_Registers);
	GPIO_Registers GPIO_D;
	PADTO(RESERVED4, 1024, GPIO_Registers);
	GPIO_Registers GPIO_E;
	PADTO(RESERVED5, 1024, GPIO_Registers);
	GPIO_Registers GPIO_F;
	PADTO(RESERVED6, 1024, GPIO_Registers);
	GPIO_Registers GPIO_G;
	PADTO(RESERVED7, 1024, GPIO_Registers);
	GPIO_Registers GPIO_H;
	PADTO(RESERVED8, 1024, GPIO_Registers);
	GPIO_Registers GPIO_I;
	PADTO(RESERVED9, 1024, GPIO_Registers);
	GPIO_Registers GPIO_J;
	PADTO(RESERVED10, 1024, GPIO_Registers);
	GPIO_Registers GPIO_K;
	PADTO(RESERVED11, 2048, GPIO_Registers);
	CRC_Registers CRC; 
	PADTO(RESERVED12, 2048, CRC_Registers);
	RCC_Registers RCC;
	PADTO(RESERVED13, 1024, RCC_Registers);

} AHB1, *AHB1_ptr;
