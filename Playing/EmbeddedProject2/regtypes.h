#pragma once

#define BITS volatile unsigned int
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
		BITS SW : 2;
		BITS SWS : 2;
		BITS HPRE : 4;
		BITS UNUSED2 : 2;
		BITS PPRE1 : 3;
		BITS PPRE2 : 3;
		BITS RTCPRE : 5;
		BITS MCO1 : 2;
		BITS I2SSC : 1;
		BITS MCO1_PRE : 3;
		BITS MCO2_PRE : 3;
		BITS MCO2 : 2;
	};
	uint32_t ALLBITS;
} RCC_CFGR_Reg, * RCC_CFGR_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BITS GPIOA_EN : 1;
		BITS GPIOB_EN : 1;
		BITS GPIOC_EN : 1;
		BITS GPIOD_EN : 1;
		BITS GPIOE_EN : 1;
		BITS GPIOF_EN : 1;
		BITS GPIOG_EN : 1;
		BITS GPIOH_EN : 1;
		BITS GPIOI_EN : 1;
		BITS GPIOJ_EN : 1;
		BITS GPIOK_EN : 1;
		BITS UNUSED1 : 1;
		BITS CRC_EN : 1;
		BITS UNUSED2 : 5;
		BITS BKPSRAM_EN : 1;
		BITS UNUSED3 : 1;
		BITS CCMDATARAM_EN : 1;
		BITS DMA1_EN : 1;
		BITS DMA2_EN : 1;
		BITS DMA2D_EN : 1;
		BITS UNUSED4 : 1;
		BITS ETHMAC_EN : 1;
		BITS ETHMACTX_EN : 1;
		BITS ETHMACRX_EN : 1;
		BITS ETHMACPTP_EN : 1;
		BITS OTGHS_EN : 1;
		BITS OTGHSULPI_EN : 1;
		BITS UNUSED5 : 1;
	};
	uint32_t ALLBITS;
} RCC_AHB1ENR_Reg, * RCC_AHB1ENR_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BITS DCMI_EN : 1;
		BITS UNUSED1 : 3;
		BITS CRYP_EN : 1;
		BITS HASH_EN : 1;
		BITS RNG_EN : 1;
		BITS OTGFS_EN : 1;
		BITS UNUSED2: 8;
		BITS UNUSED3 : 16;
	};
	uint32_t ALLBITS;
} RCC_AHB2ENR_Reg, * RCC_AHB2ENR_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BITS FSMC_EN : 1;
		BITS UNUSED1 : 31;
	};
	uint32_t ALLBITS;
} RCC_AHB3ENR_Reg, * RCC_AHB3ENR_Reg_ptr;

typedef union
{
	struct // STM32F407
	{
		// LSB at top, MSB at bottom
		BITS HSI_ON : 1;
		BITS HSI_RDY : 1;
		BITS UNUSED1 : 1;
		BITS HSI_TRIM : 5;
		BITS HSI_CAL : 8;
		BITS HSE_ON : 1;
		BITS HSE_RDY : 1;
		BITS HSE_BYP : 1;
		BITS CSS_ON : 1;
		BITS UNUSED2 : 4;
		BITS PLL_ON : 1;
		BITS PLL_RDY : 1;
		BITS PLL_I2S_ON : 1;
		BITS PLL_I2S_RDY: 1;
		BITS UNUSED3 : 4;
	};
	uint32_t ALLBITS;
} RCC_CR_Reg, * RCC_CR_Reg_ptr;

typedef union
{
	struct // STM32F407
	{
		// LSB at top, MSB at bottom
		BITS LSI_RDY_F : 1;
		BITS LSE_RDY_F : 1;
		BITS HSI_RDY_F : 1;
		BITS HSE_RDY_F : 1;
		BITS PLL_RDY_F : 1;
		BITS PLL_I2S_RDY_F : 1;
		BITS UNUSED : 1;
		BITS CSS_F : 1;
		BITS LSI_RDY_E : 1;
		BITS LSE_RDY_E : 1;
		BITS HSI_RDY_E : 1;
		BITS HSE_RDY_E : 1;
		BITS PLL_RDY_E : 1;
		BITS PLL_I2S_RDY_E : 1;
		BITS UNUSED2 : 2;
		BITS LSI_RDY_C : 1;
		BITS LSE_RDY_C : 1;
		BITS HSI_RDY_C : 1;
		BITS HSE_RDY_C : 1;
		BITS PLL_RDY_C : 1;
		BITS PLL_I2S_RDY_C : 1;
		BITS UNUSED3 : 1;
		BITS CSS_C : 1;
		BITS UNUSED4 : 8;
	};
	uint32_t ALLBITS;
} RCC_CIR_Reg, * RCC_CIR_Reg_ptr;

typedef union
{
	struct 
	{
		// LSB at top, MSB at bottom
		BITS PLL_M : 6;
		BITS PLL_N : 9;
		BITS UNUSED1 : 1;
		BITS PLL_P : 2;
		BITS UNUSED2 : 4;
		BITS PLL_SRC : 1;
		BITS UNUSED3 : 1;
		BITS PLL_Q : 4;
		BITS UNUSED4 : 4;
	};
	uint32_t ALLBITS;

} RCC_PLLCFGR_Reg, * RCC_PLLCFGR_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BITS MODER_0 : 2;
		BITS MODER_1 : 2;
		BITS MODER_2 : 2;
		BITS MODER_3 : 2;
		BITS MODER_4 : 2;
		BITS MODER_5 : 2;
		BITS MODER_6 : 2;
		BITS MODER_7 : 2;
		BITS MODER_8 : 2;
		BITS MODER_9 : 2;
		BITS MODER_10 : 2;
		BITS MODER_11 : 2;
		BITS MODER_12 : 2;
		BITS MODER_13 : 2;
		BITS MODER_14 : 2;
		BITS MODER_15 : 2;
	};
	uint32_t ALLBITS;

} GPIO_MODER_Reg, * GPIO_MODER_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BITS OT_0 : 1;
		BITS OT_1 : 1;
		BITS OT_2 : 1;
		BITS OT_3 : 1;
		BITS OT_4 : 1;
		BITS OT_5 : 1;
		BITS OT_6 : 1;
		BITS OT_7 : 1;
		BITS OT_8 : 1;
		BITS OT_9 : 1;
		BITS OT_10 : 1;
		BITS OT_11 : 1;
		BITS OT_12 : 1;
		BITS OT_13 : 1;
		BITS OT_14 : 1;
		BITS OT_15 : 1;
		BITS UNUSED1 : 16;
	};
	uint32_t ALLBITS;

} GPIO_OTYPER_Reg, * GPIO_OTYPER_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BITS SPEED_0 : 2;
		BITS SPEED_1 : 2;
		BITS SPEED_2 : 2;
		BITS SPEED_3 : 2;
		BITS SPEED_4 : 2;
		BITS SPEED_5 : 2;
		BITS SPEED_6 : 2;
		BITS SPEED_7 : 2;
		BITS SPEED_8 : 2;
		BITS SPEED_9 : 2;
		BITS SPEED_10 : 2;
		BITS SPEED_11 : 2;
		BITS SPEED_12 : 2;
		BITS SPEED_13 : 2;
		BITS SPEED_14 : 2;
		BITS SPEED_15 : 2;
	};
	uint32_t ALLBITS;

} GPIO_OSPEEDR_Reg, * GPIO_OSPEEDR_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BITS PUPDR_0 : 2;
		BITS PUPDR_1 : 2;
		BITS PUPDR_2 : 2;
		BITS PUPDR_3 : 2;
		BITS PUPDR_4 : 2;
		BITS PUPDR_5 : 2;
		BITS PUPDR_6 : 2;
		BITS PUPDR_7 : 2;
		BITS PUPDR_8 : 2;
		BITS PUPDR_9 : 2;
		BITS PUPDR_10 : 2;
		BITS PUPDR_11 : 2;
		BITS PUPDR_12 : 2;
		BITS PUPDR_13 : 2;
		BITS PUPDR_14 : 2;
		BITS PUPDR_15 : 2;
	};
	uint32_t ALLBITS;

} GPIO_PUPDR_Reg, * GPIO_PUPDR_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BITS IDR_0 : 1;
		BITS IDR_1 : 1;
		BITS IDR_2 : 1;
		BITS IDR_3 : 1;
		BITS IDR_4 : 1;
		BITS IDR_5 : 1;
		BITS IDR_6 : 1;
		BITS IDR_7 : 1;
		BITS IDR_8 : 1;
		BITS IDR_9 : 1;
		BITS IDR_10 : 1;
		BITS IDR_11 : 1;
		BITS IDR_12 : 1;
		BITS IDR_13 : 1;
		BITS IDR_14 : 1;
		BITS IDR_15 : 1;
		BITS UNUSED : 16;
	};
	uint32_t ALLBITS;

} GPIO_IDR_Reg, * GPIO_IDR_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BITS ODR_0 : 1;
		BITS ODR_1 : 1;
		BITS ODR_2 : 1;
		BITS ODR_3 : 1;
		BITS ODR_4 : 1;
		BITS ODR_5 : 1;
		BITS ODR_6 : 1;
		BITS ODR_7 : 1;
		BITS ODR_8 : 1;
		BITS ODR_9 : 1;
		BITS ODR_10 : 1;
		BITS ODR_11 : 1;
		BITS ODR_12 : 1;
		BITS ODR_13 : 1;
		BITS ODR_14 : 1;
		BITS ODR_15 : 1;
		BITS UNUSED : 16;
	};
	uint32_t ALLBITS;

} GPIO_ODR_Reg, * GPIO_ODR_Reg_ptr;

typedef union
{
	struct
	{
		// All bits here are write only.
		// LSB at top, MSB at bottom
		BITS BS_0 : 1;
		BITS BS_1 : 1;
		BITS BS_2 : 1;
		BITS BS_3 : 1;
		BITS BS_4 : 1;
		BITS BS_5 : 1;
		BITS BS_6 : 1;
		BITS BS_7 : 1;
		BITS BS_8 : 1;
		BITS BS_9 : 1;
		BITS BS_10 : 1;
		BITS BS_11 : 1;
		BITS BS_12 : 1;
		BITS BS_13 : 1;
		BITS BS_14 : 1;
		BITS BS_15 : 1;
		BITS BR_0 : 1;
		BITS BR_1 : 1;
		BITS BR_2 : 1;
		BITS BR_3 : 1;
		BITS BR_4 : 1;
		BITS BR_5 : 1;
		BITS BR_6 : 1;
		BITS BR_7 : 1;
		BITS BR_8 : 1;
		BITS BR_9 : 1;
		BITS BR_10 : 1;
		BITS BR_11 : 1;
		BITS BR_12 : 1;
		BITS BR_13 : 1;
		BITS BR_14 : 1;
		BITS BR_15 : 1;
	};
	uint32_t ALLBITS;

} GPIO_BSRR_Reg, * GPIO_BSRR_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BITS LCK_0 : 1;
		BITS LCK_1 : 1;
		BITS LCK_2 : 1;
		BITS LCK_3 : 1;
		BITS LCK_4 : 1;
		BITS LCK_5 : 1;
		BITS LCK_6 : 1;
		BITS LCK_7 : 1;
		BITS LCK_8 : 1;
		BITS LCK_9 : 1;
		BITS LCK_10 : 1;
		BITS LCK_11 : 1;
		BITS LCK_12 : 1;
		BITS LCK_13 : 1;
		BITS LCK_14 : 1;
		BITS LCK_15 : 1;
		BITS LCK_K : 1;
		BITS UNUSED : 15;
	};
	uint32_t ALLBITS;

} GPIO_LCKR_Reg, * GPIO_LCKR_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BITS AFRL_0 : 4;
		BITS AFRL_1 : 4;
		BITS AFRL_2 : 4;
		BITS AFRL_3 : 4;
		BITS AFRL_4 : 4;
		BITS AFRL_5 : 4;
		BITS AFRL_6 : 4;
		BITS AFRL_7 : 4;
	};
	uint32_t ALLBITS;

} GPIO_AFRL_Reg, * GPIO_AFRL_Reg_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		BITS AFRH_8 : 4;
		BITS AFRH_9 : 4;
		BITS AFRH_10 : 4;
		BITS AFRH_11 : 4;
		BITS AFRH_12 : 4;
		BITS AFRH_13 : 4;
		BITS AFRH_14 : 4;
		BITS AFRH_15 : 4;
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



typedef struct
{
	
} TIM_Basic, * TIM_Basic_ptr;

typedef struct
{
	
} APB1, *APB1_ptr;