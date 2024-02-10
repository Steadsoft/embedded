#pragma once
// Undefine stuff defined by STM32 HAL/LL support headers.
#undef TIM2
#undef TIM3
#undef TIM4
#undef TIM5

#define BIT08 volatile uint8_t
#define BIT16 volatile uint16_t

#define RCC_CFGR ((RCC_CFGR_Reg_ptr)&(RCC->CFGR)) 
#define RCC_AHB1ENR ((RCC_AHB1ENR_Reg_ptr)&(RCC->AHB1ENR)) 
#define RCC_CR ((RCC_CR_Reg_ptr)&(RCC->CR)) 
#define RCC_PLLCFGR ((RCC_PLLCFGR_Reg_ptr)&(RCC->PLLCFGR)) 
#define GPIO_MODER(BASE) ((GPIO_MODER_Reg_ptr)&((BASE)->MODER)) 
#define GPIO_OTYPER(BASE) ((GPIO_OTYPER_Reg_ptr)&((BASE)->OTYPER)) 
#define GPIO_OSPEEDR(BASE) ((GPIO_OSPEEDR_Reg_ptr)&((BASE)->OSPEEDR)) 
#define PADTO(NAME,BYTES,TYPE) char NAME[BYTES-sizeof(TYPE)]

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BIT16 SW : 2;
		BIT16 SWS : 2;
		BIT16 HPRE : 4;
		BIT16 UNUSED2 : 2;
		BIT16 PPRE1 : 3;
		BIT16 PPRE2 : 3;
		BIT16 RTCPRE : 5;
		BIT16 MCO1 : 2;
		BIT16 I2SSC : 1;
		BIT16 MCO1_PRE : 3;
		BIT16 MCO2_PRE : 3;
		BIT16 MCO2 : 2;
	};
	uint32_t ALLBITS;
} RCC_CFGR_Reg, * RCC_CFGR_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BIT16 GPIOA_EN : 1;
		BIT16 GPIOB_EN : 1;
		BIT16 GPIOC_EN : 1;
		BIT16 GPIOD_EN : 1;
		BIT16 GPIOE_EN : 1;
		BIT16 GPIOF_EN : 1;
		BIT16 GPIOG_EN : 1;
		BIT16 GPIOH_EN : 1;
		BIT16 GPIOI_EN : 1;
		BIT16 GPIOJ_EN : 1;
		BIT16 GPIOK_EN : 1;
		BIT16 UNUSED1 : 1;
		BIT16 CRC_EN : 1;
		BIT16 UNUSED2 : 5;
		BIT16 BKPSRAM_EN : 1;
		BIT16 UNUSED3 : 1;
		BIT16 CCMDATARAM_EN : 1;
		BIT16 DMA1_EN : 1;
		BIT16 DMA2_EN : 1;
		BIT16 DMA2D_EN : 1;
		BIT16 UNUSED4 : 1;
		BIT16 ETHMAC_EN : 1;
		BIT16 ETHMACTX_EN : 1;
		BIT16 ETHMACRX_EN : 1;
		BIT16 ETHMACPTP_EN : 1;
		BIT16 OTGHS_EN : 1;
		BIT16 OTGHSULPI_EN : 1;
		BIT16 UNUSED5 : 1;
	};
	uint32_t ALLBITS;
} RCC_AHB1ENR_Reg, * RCC_AHB1ENR_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BIT16 DCMI_EN : 1;
		BIT16 UNUSED1 : 3;
		BIT16 CRYP_EN : 1;
		BIT16 HASH_EN : 1;
		BIT16 RNG_EN : 1;
		BIT16 OTGFS_EN : 1;
		BIT16 UNUSED2: 8;
		BIT16 UNUSED3 : 16;
	};
	uint32_t ALLBITS;
} RCC_AHB2ENR_Reg, * RCC_AHB2ENR_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BIT08 FSMC_EN : 1;
		BIT16 UNUSED1 : 15;
		BIT16 UNUSED2 : 16;
	};
	uint32_t ALLBITS;
} RCC_AHB3ENR_Reg, * RCC_AHB3ENR_Reg_ptr;

typedef union
{
	struct // STM32F407
	{
		// LSB at top, MSB at bottom
		BIT16 HSI_ON : 1;
		BIT16 HSI_RDY : 1;
		BIT16 UNUSED1 : 1;
		BIT16 HSI_TRIM : 5;
		BIT16 HSI_CAL : 8;
		BIT16 HSE_ON : 1;
		BIT16 HSE_RDY : 1;
		BIT16 HSE_BYP : 1;
		BIT16 CSS_ON : 1;
		BIT16 UNUSED2 : 4;
		BIT16 PLL_ON : 1;
		BIT16 PLL_RDY : 1;
		BIT16 PLL_I2S_ON : 1;
		BIT16 PLL_I2S_RDY: 1;
		BIT16 UNUSED3 : 4;
	};
	uint32_t ALLBITS;
} RCC_CR_Reg, * RCC_CR_Reg_ptr;

typedef union
{
	struct // STM32F407
	{
		// LSB at top, MSB at bottom
		BIT16 LSI_RDY_F : 1;
		BIT16 LSE_RDY_F : 1;
		BIT16 HSI_RDY_F : 1;
		BIT16 HSE_RDY_F : 1;
		BIT16 PLL_RDY_F : 1;
		BIT16 PLL_I2S_RDY_F : 1;
		BIT16 UNUSED : 1;
		BIT16 CSS_F : 1;
		BIT16 LSI_RDY_E : 1;
		BIT16 LSE_RDY_E : 1;
		BIT16 HSI_RDY_E : 1;
		BIT16 HSE_RDY_E : 1;
		BIT16 PLL_RDY_E : 1;
		BIT16 PLL_I2S_RDY_E : 1;
		BIT16 UNUSED2 : 2;
		BIT16 LSI_RDY_C : 1;
		BIT16 LSE_RDY_C : 1;
		BIT16 HSI_RDY_C : 1;
		BIT16 HSE_RDY_C : 1;
		BIT16 PLL_RDY_C : 1;
		BIT16 PLL_I2S_RDY_C : 1;
		BIT16 UNUSED3 : 1;
		BIT16 CSS_C : 1;
		BIT16 UNUSED4 : 8;
	};
	uint32_t ALLBITS;
} RCC_CIR_Reg, * RCC_CIR_Reg_ptr;

typedef union
{
	struct 
	{
		// LSB at top, MSB at bottom
		BIT16 PLL_M : 6;
		BIT16 PLL_N : 9;
		BIT16 UNUSED1 : 1;
		BIT16 PLL_P : 2;
		BIT16 UNUSED2 : 4;
		BIT16 PLL_SRC : 1;
		BIT16 UNUSED3 : 1;
		BIT16 PLL_Q : 4;
		BIT16 UNUSED4 : 4;
	};
	uint32_t ALLBITS;

} RCC_PLLCFGR_Reg, * RCC_PLLCFGR_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BIT16 MODER_0 : 2;
		BIT16 MODER_1 : 2;
		BIT16 MODER_2 : 2;
		BIT16 MODER_3 : 2;
		BIT16 MODER_4 : 2;
		BIT16 MODER_5 : 2;
		BIT16 MODER_6 : 2;
		BIT16 MODER_7 : 2;
		BIT16 MODER_8 : 2;
		BIT16 MODER_9 : 2;
		BIT16 MODER_10 : 2;
		BIT16 MODER_11 : 2;
		BIT16 MODER_12 : 2;
		BIT16 MODER_13 : 2;
		BIT16 MODER_14 : 2;
		BIT16 MODER_15 : 2;
	};
	uint32_t ALLBITS;

} GPIO_MODER_Reg, * GPIO_MODER_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BIT16 OT_0 : 1;
		BIT16 OT_1 : 1;
		BIT16 OT_2 : 1;
		BIT16 OT_3 : 1;
		BIT16 OT_4 : 1;
		BIT16 OT_5 : 1;
		BIT16 OT_6 : 1;
		BIT16 OT_7 : 1;
		BIT16 OT_8 : 1;
		BIT16 OT_9 : 1;
		BIT16 OT_10 : 1;
		BIT16 OT_11 : 1;
		BIT16 OT_12 : 1;
		BIT16 OT_13 : 1;
		BIT16 OT_14 : 1;
		BIT16 OT_15 : 1;
		BIT16 UNUSED1 : 16;
	};
	uint32_t ALLBITS;

} GPIO_OTYPER_Reg, * GPIO_OTYPER_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BIT16 SPEED_0 : 2;
		BIT16 SPEED_1 : 2;
		BIT16 SPEED_2 : 2;
		BIT16 SPEED_3 : 2;
		BIT16 SPEED_4 : 2;
		BIT16 SPEED_5 : 2;
		BIT16 SPEED_6 : 2;
		BIT16 SPEED_7 : 2;
		BIT16 SPEED_8 : 2;
		BIT16 SPEED_9 : 2;
		BIT16 SPEED_10 : 2;
		BIT16 SPEED_11 : 2;
		BIT16 SPEED_12 : 2;
		BIT16 SPEED_13 : 2;
		BIT16 SPEED_14 : 2;
		BIT16 SPEED_15 : 2;
	};
	uint32_t ALLBITS;

} GPIO_OSPEEDR_Reg, * GPIO_OSPEEDR_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BIT16 PUPDR_0 : 2;
		BIT16 PUPDR_1 : 2;
		BIT16 PUPDR_2 : 2;
		BIT16 PUPDR_3 : 2;
		BIT16 PUPDR_4 : 2;
		BIT16 PUPDR_5 : 2;
		BIT16 PUPDR_6 : 2;
		BIT16 PUPDR_7 : 2;
		BIT16 PUPDR_8 : 2;
		BIT16 PUPDR_9 : 2;
		BIT16 PUPDR_10 : 2;
		BIT16 PUPDR_11 : 2;
		BIT16 PUPDR_12 : 2;
		BIT16 PUPDR_13 : 2;
		BIT16 PUPDR_14 : 2;
		BIT16 PUPDR_15 : 2;
	};
	uint32_t ALLBITS;

} GPIO_PUPDR_Reg, * GPIO_PUPDR_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BIT16 IDR_0 : 1;
		BIT16 IDR_1 : 1;
		BIT16 IDR_2 : 1;
		BIT16 IDR_3 : 1;
		BIT16 IDR_4 : 1;
		BIT16 IDR_5 : 1;
		BIT16 IDR_6 : 1;
		BIT16 IDR_7 : 1;
		BIT16 IDR_8 : 1;
		BIT16 IDR_9 : 1;
		BIT16 IDR_10 : 1;
		BIT16 IDR_11 : 1;
		BIT16 IDR_12 : 1;
		BIT16 IDR_13 : 1;
		BIT16 IDR_14 : 1;
		BIT16 IDR_15 : 1;
		BIT16 UNUSED : 16;
	};
	uint32_t ALLBITS;

} GPIO_IDR_Reg, * GPIO_IDR_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BIT16 ODR_0 : 1;
		BIT16 ODR_1 : 1;
		BIT16 ODR_2 : 1;
		BIT16 ODR_3 : 1;
		BIT16 ODR_4 : 1;
		BIT16 ODR_5 : 1;
		BIT16 ODR_6 : 1;
		BIT16 ODR_7 : 1;
		BIT16 ODR_8 : 1;
		BIT16 ODR_9 : 1;
		BIT16 ODR_10 : 1;
		BIT16 ODR_11 : 1;
		BIT16 ODR_12 : 1;
		BIT16 ODR_13 : 1;
		BIT16 ODR_14 : 1;
		BIT16 ODR_15 : 1;
		BIT16 UNUSED : 16;
	};
	uint32_t ALLBITS;

} GPIO_ODR_Reg, * GPIO_ODR_Reg_ptr;

typedef union
{
	struct
	{
		// All bits here are write only.
		// LSB at top, MSB at bottom
		BIT16 BS_0 : 1;
		BIT16 BS_1 : 1;
		BIT16 BS_2 : 1;
		BIT16 BS_3 : 1;
		BIT16 BS_4 : 1;
		BIT16 BS_5 : 1;
		BIT16 BS_6 : 1;
		BIT16 BS_7 : 1;
		BIT16 BS_8 : 1;
		BIT16 BS_9 : 1;
		BIT16 BS_10 : 1;
		BIT16 BS_11 : 1;
		BIT16 BS_12 : 1;
		BIT16 BS_13 : 1;
		BIT16 BS_14 : 1;
		BIT16 BS_15 : 1;
		BIT16 BR_0 : 1;
		BIT16 BR_1 : 1;
		BIT16 BR_2 : 1;
		BIT16 BR_3 : 1;
		BIT16 BR_4 : 1;
		BIT16 BR_5 : 1;
		BIT16 BR_6 : 1;
		BIT16 BR_7 : 1;
		BIT16 BR_8 : 1;
		BIT16 BR_9 : 1;
		BIT16 BR_10 : 1;
		BIT16 BR_11 : 1;
		BIT16 BR_12 : 1;
		BIT16 BR_13 : 1;
		BIT16 BR_14 : 1;
		BIT16 BR_15 : 1;
	};
	uint32_t ALLBITS;

} GPIO_BSRR_Reg, * GPIO_BSRR_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BIT16 LCK_0 : 1;
		BIT16 LCK_1 : 1;
		BIT16 LCK_2 : 1;
		BIT16 LCK_3 : 1;
		BIT16 LCK_4 : 1;
		BIT16 LCK_5 : 1;
		BIT16 LCK_6 : 1;
		BIT16 LCK_7 : 1;
		BIT16 LCK_8 : 1;
		BIT16 LCK_9 : 1;
		BIT16 LCK_10 : 1;
		BIT16 LCK_11 : 1;
		BIT16 LCK_12 : 1;
		BIT16 LCK_13 : 1;
		BIT16 LCK_14 : 1;
		BIT16 LCK_15 : 1;
		BIT16 LCK_K : 1;
		BIT16 UNUSED : 15;
	};
	uint32_t ALLBITS;

} GPIO_LCKR_Reg, * GPIO_LCKR_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BIT16 AFRL_0 : 4;
		BIT16 AFRL_1 : 4;
		BIT16 AFRL_2 : 4;
		BIT16 AFRL_3 : 4;
		BIT16 AFRL_4 : 4;
		BIT16 AFRL_5 : 4;
		BIT16 AFRL_6 : 4;
		BIT16 AFRL_7 : 4;
	};
	uint32_t ALLBITS;

} GPIO_AFRL_Reg, * GPIO_AFRL_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BIT16 AFRH_8 : 4;
		BIT16 AFRH_9 : 4;
		BIT16 AFRH_10 : 4;
		BIT16 AFRH_11 : 4;
		BIT16 AFRH_12 : 4;
		BIT16 AFRH_13 : 4;
		BIT16 AFRH_14 : 4;
		BIT16 AFRH_15 : 4;
	};
	uint32_t ALLBITS;

} GPIO_AFRH_Reg, * GPIO_AFRH_Reg_ptr;

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
	uint32_t APB1ENR; /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
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
} ResetAndClockControl, *ResetAndClockControl_ptr;

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
} GPIO, GPIO_ptr;

typedef struct
{
	GPIO GPIO_A;
	GPIO GPIO_B;
	GPIO GPIO_C;
	GPIO GPIO_D;
	GPIO GPIO_E;
	GPIO GPIO_F;
	GPIO GPIO_G;
	GPIO GPIO_H;
	GPIO GPIO_I;
	GPIO GPIO_J;
	GPIO GPIO_K;

} AHB1, *AHB1_ptr;

// TIM2 - TIM5 Registers

typedef struct
{
	BIT08 CEN : 1;
	BIT08 UDIS : 1;
	BIT08 URS : 1;
	BIT08 OPM : 1;
	BIT08 DIR : 1;
	BIT08 CMS : 2;
	BIT08 ARPE : 1;
	BIT08 CKD : 2;
	BIT08 UNUSED : 6;
} TIM_CR1, *TIM_CR1_ptr;
typedef struct
{
	BIT16 UNUSED1 : 3;
	BIT16 CCDS : 1;
	BIT16 MMS : 3;
	BIT16 TI1 : 1;
	BIT16 UNUSED2 : 8;
} TIM_CR2, *TIM_CR2_ptr;
typedef struct
{
	BIT16 SMS : 3;
	BIT16 UNUSED1 : 1;
	BIT16 TS : 3;
	BIT16 MSM : 1;
	BIT16 ETF : 4;
	BIT16 ETPS : 2;
	BIT16 ECE : 1;
	BIT16 ETP : 1;
	BIT16 UNUSED2 : 16;
} TIM_SMCR, *TIM_SMCR_ptr;
typedef struct
{
	BIT16 UIE : 1;
	BIT16 CC1IE : 1;
	BIT16 CC2IE : 1;
	BIT16 CC3IE : 1;
	BIT16 CC4IE : 1;
	BIT16 UNUSED1 : 1;
	BIT16 TIE : 1;
	BIT16 UNUSED2 : 1;
	BIT16 UDE : 1;
	BIT16 CC1DE : 1;
	BIT16 CC2DE : 1;
	BIT16 CC3DE : 1;
	BIT16 CC4DE : 1;
	BIT16 UNUSED3 : 1;
	BIT16 TDE : 1;
	BIT16 UNUSED4 : 1;
	BIT16 UNUSED5 : 16;
} TIM_DIER, *TIM_DIER_ptr;
typedef struct
{
	BIT16 UIF : 1;
	BIT16 CC1IF : 1;
	BIT16 CC2IF : 1;
	BIT16 CC3IF : 1;
	BIT16 CC4IF : 1;
	BIT16 RESERVED1 : 1;
	BIT16 TIF : 1;
	BIT16 RESERVED2 : 2;
	BIT16 CC1OF : 1;
	BIT16 CC2OF : 1;
	BIT16 CC3OF : 1;
	BIT16 CC4OF : 1;
	BIT16 RESERVED3 : 3;
	BIT16 RESERVED4 : 16;
} TIM_SR, *TIM_SR_ptr;
typedef struct
{
	
} TIM_EGR, *TIM_EGR_ptr;
// CCMR1 register when in output capture mode
typedef struct
{
	
} TIM_CCMR1_OCM, *TIM_CCMR1_OCM_ptr;
// CCMR1 register when in input compare mode
typedef struct
{
	
} TIM_CCMR1_ICM, *TIM_CCMR1_ICM_ptr;
// CCMR2 register when in output capture mode
typedef struct
{
	
} TIM_CCMR2_OCM, *TIM_CCMR2_OCM_ptr;
// CCMR2 register when in input compare mode
typedef struct
{
	
} TIM_CCMR2_ICM, *TIM_CCMR2_ICM_ptr;
typedef struct
{
	
} TIM_CCER, *TIM_CCER_ptr;
typedef struct
{
	
} TIM_CNT, *TIM_CNT_ptr;
typedef struct
{
	
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