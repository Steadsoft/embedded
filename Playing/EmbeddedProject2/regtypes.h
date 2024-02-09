#pragma once

#define BIT unsigned int
#define RCC_CFGR ((RCC_CFGR_Type_ptr)&(RCC->CFGR)) 
#define RCC_AHB1ENR ((RCC_AHB1ENR_Type_ptr)&(RCC->AHB1ENR)) 
#define RCC_CR ((RCC_CR_Type_ptr)&(RCC->CR)) 
#define RCC_PLLCFGR ((RCC_PLLCFGR_Type_ptr)&(RCC->PLLCFGR)) 
#define GPIO_MODER(BASE) ((GPIO_MODER_Type_ptr)&((BASE)->MODER)) 
#define GPIO_OTYPER(BASE) ((GPIO_OTYPER_Type_ptr)&((BASE)->OTYPER)) 
#define GPIO_OSPEEDR(BASE) ((GPIO_OSPEEDR_Type_ptr)&((BASE)->OSPEEDR)) 

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		__IO BIT SW : 2;
		__IO BIT SWS : 2;
		__IO BIT HPRE : 4;
		__IO BIT UNUSED2 : 2;
		__IO BIT PPRE1 : 3;
		__IO BIT PPRE2 : 3;
		__IO BIT RTCPRE : 5;
		__IO BIT MCO1 : 2;
		__IO BIT I2SSC : 1;
		__IO BIT MCO1_PRE : 3;
		__IO BIT MCO2_PRE : 3;
		__IO BIT MCO2 : 2;
	};
	uint32_t ALLBITS;
} RCC_CFGR_Type, * RCC_CFGR_Type_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		__IO BIT GPIOA_EN : 1;
		__IO BIT GPIOB_EN : 1;
		__IO BIT GPIOC_EN : 1;
		__IO BIT GPIOD_EN : 1;
		__IO BIT GPIOE_EN : 1;
		__IO BIT GPIOF_EN : 1;
		__IO BIT GPIOG_EN : 1;
		__IO BIT GPIOH_EN : 1;
		__IO BIT GPIOI_EN : 1;
		__IO BIT GPIOJ_EN : 1;
		__IO BIT GPIOK_EN : 1;
		__IO BIT UNUSED1 : 1;
		__IO BIT CRC_EN : 1;
		__IO BIT UNUSED2 : 5;
		__IO BIT BKPSRAM_EN : 1;
		__IO BIT UNUSED3 : 1;
		__IO BIT CCMDATARAM_EN : 1;
		__IO BIT DMA1_EN : 1;
		__IO BIT DMA2_EN : 1;
		__IO BIT DMA2D_EN : 1;
		__IO BIT UNUSED4 : 1;
		__IO BIT ETHMAC_EN : 1;
		__IO BIT ETHMACTX_EN : 1;
		__IO BIT ETHMACRX_EN : 1;
		__IO BIT ETHMACPTP_EN : 1;
		__IO BIT OTGHS_EN : 1;
		__IO BIT OTGHSULPI_EN : 1;
		__IO BIT UNUSED5 : 1;
	};
	uint32_t ALLBITS;
} RCC_AHB1ENR_Type, * RCC_AHB1ENR_Type_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		__IO BIT DCMI_EN : 1;
		__IO BIT UNUSED1 : 3;
		__IO BIT CRYP_EN : 1;
		__IO BIT HASH_EN : 1;
		__IO BIT RNG_EN : 1;
		__IO BIT OTGFS_EN : 1;
		__IO BIT UNUSED2: 8;
		__IO BIT UNUSED3 : 16;
	};
	uint32_t ALLBITS;
} RCC_AHB2ENR_Type, * RCC_AHB2ENR_Type_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		__IO BIT FSMC_EN : 1;
		__IO BIT UNUSED1 : 31;
	};
	uint32_t ALLBITS;
} RCC_AHB3ENR_Type, * RCC_AHB3ENR_Type_ptr;

typedef union
{
	struct // STM32F407
	{
		// LSB at top, MSB at bottom
		__IO BIT HSI_ON : 1;
		__IO BIT HSI_RDY : 1;
		__IO BIT UNUSED1 : 1;
		__IO BIT HSI_TRIM : 5;
		__IO BIT HSI_CAL : 8;
		__IO BIT HSE_ON : 1;
		__IO BIT HSE_RDY : 1;
		__IO BIT HSE_BYP : 1;
		__IO BIT CSS_ON : 1;
		__IO BIT UNUSED2 : 4;
		__IO BIT PLL_ON : 1;
		__IO BIT PLL_RDY : 1;
		__IO BIT PLL_I2S_ON : 1;
		__IO BIT PLL_I2S_RDY: 1;
		__IO BIT UNUSED3 : 4;
	};
	uint32_t ALLBITS;
} RCC_CR_Type, * RCC_CR_Type_ptr;

typedef union
{
	struct // STM32F407
	{
		// LSB at top, MSB at bottom
		__IO BIT LSI_RDY_F : 1;
		__IO BIT LSE_RDY_F : 1;
		__IO BIT HSI_RDY_F : 1;
		__IO BIT HSE_RDY_F : 1;
		__IO BIT PLL_RDY_F : 1;
		__IO BIT PLL_I2S_RDY_F : 1;
		__IO BIT UNUSED : 1;
		__IO BIT CSS_F : 1;
		__IO BIT LSI_RDY_E : 1;
		__IO BIT LSE_RDY_E : 1;
		__IO BIT HSI_RDY_E : 1;
		__IO BIT HSE_RDY_E : 1;
		__IO BIT PLL_RDY_E : 1;
		__IO BIT PLL_I2S_RDY_E : 1;
		__IO BIT UNUSED2 : 2;
		__IO BIT LSI_RDY_C : 1;
		__IO BIT LSE_RDY_C : 1;
		__IO BIT HSI_RDY_C : 1;
		__IO BIT HSE_RDY_C : 1;
		__IO BIT PLL_RDY_C : 1;
		__IO BIT PLL_I2S_RDY_C : 1;
		__IO BIT UNUSED3 : 1;
		__IO BIT CSS_C : 1;
		__IO BIT UNUSED4 : 8;
	};
	uint32_t ALLBITS;
} RCC_CIR_Type, * RCC_CIR_Type_ptr;

typedef union
{
	struct 
	{
		// LSB at top, MSB at bottom
		__IO BIT PLL_M : 6;
		__IO BIT PLL_N : 9;
		__IO BIT UNUSED1 : 1;
		__IO BIT PLL_P : 2;
		__IO BIT UNUSED2 : 4;
		__IO BIT PLL_SRC : 1;
		__IO BIT UNUSED3 : 1;
		__IO BIT PLL_Q : 4;
		__IO BIT UNUSED4 : 4;
	};
	uint32_t ALLBITS;

} RCC_PLLCFGR_Type, * RCC_PLLCFGR_Type_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		__IO BIT MODER_0 : 2;
		__IO BIT MODER_1 : 2;
		__IO BIT MODER_2 : 2;
		__IO BIT MODER_3 : 2;
		__IO BIT MODER_4 : 2;
		__IO BIT MODER_5 : 2;
		__IO BIT MODER_6 : 2;
		__IO BIT MODER_7 : 2;
		__IO BIT MODER_8 : 2;
		__IO BIT MODER_9 : 2;
		__IO BIT MODER_10 : 2;
		__IO BIT MODER_11 : 2;
		__IO BIT MODER_12 : 2;
		__IO BIT MODER_13 : 2;
		__IO BIT MODER_14 : 2;
		__IO BIT MODER_15 : 2;
	};
	uint32_t ALLBITS;

} GPIO_MODER_Type, * GPIO_MODER_Type_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		__IO BIT OT_0 : 1;
		__IO BIT OT_1 : 1;
		__IO BIT OT_2 : 1;
		__IO BIT OT_3 : 1;
		__IO BIT OT_4 : 1;
		__IO BIT OT_5 : 1;
		__IO BIT OT_6 : 1;
		__IO BIT OT_7 : 1;
		__IO BIT OT_8 : 1;
		__IO BIT OT_9 : 1;
		__IO BIT OT_10 : 1;
		__IO BIT OT_11 : 1;
		__IO BIT OT_12 : 1;
		__IO BIT OT_13 : 1;
		__IO BIT OT_14 : 1;
		__IO BIT OT_15 : 1;
		__IO BIT UNUSED1 : 16;
	};
	uint32_t ALLBITS;

} GPIO_OTYPER_Type, * GPIO_OTYPER_Type_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		__IO BIT SPEED_0 : 2;
		__IO BIT SPEED_1 : 2;
		__IO BIT SPEED_2 : 2;
		__IO BIT SPEED_3 : 2;
		__IO BIT SPEED_4 : 2;
		__IO BIT SPEED_5 : 2;
		__IO BIT SPEED_6 : 2;
		__IO BIT SPEED_7 : 2;
		__IO BIT SPEED_8 : 2;
		__IO BIT SPEED_9 : 2;
		__IO BIT SPEED_10 : 2;
		__IO BIT SPEED_11 : 2;
		__IO BIT SPEED_12 : 2;
		__IO BIT SPEED_13 : 2;
		__IO BIT SPEED_14 : 2;
		__IO BIT SPEED_15 : 2;
	};
	uint32_t ALLBITS;

} GPIO_OSPEEDR_Type, * GPIO_OSPEEDR_Type_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		__IO BIT PUPDR_0 : 2;
		__IO BIT PUPDR_1 : 2;
		__IO BIT PUPDR_2 : 2;
		__IO BIT PUPDR_3 : 2;
		__IO BIT PUPDR_4 : 2;
		__IO BIT PUPDR_5 : 2;
		__IO BIT PUPDR_6 : 2;
		__IO BIT PUPDR_7 : 2;
		__IO BIT PUPDR_8 : 2;
		__IO BIT PUPDR_9 : 2;
		__IO BIT PUPDR_10 : 2;
		__IO BIT PUPDR_11 : 2;
		__IO BIT PUPDR_12 : 2;
		__IO BIT PUPDR_13 : 2;
		__IO BIT PUPDR_14 : 2;
		__IO BIT PUPDR_15 : 2;
	};
	uint32_t ALLBITS;

} GPIO_PUPDR_Type, * GPIO_PUPDR_Type_ptr;

typedef union
{
	struct
	{
		// LSB at top, MSB at bottom
		__IO BIT IDR_0 : 1;
		__IO BIT IDR_1 : 1;
		__IO BIT IDR_2 : 1;
		__IO BIT IDR_3 : 1;
		__IO BIT IDR_4 : 1;
		__IO BIT IDR_5 : 1;
		__IO BIT IDR_6 : 1;
		__IO BIT IDR_7 : 1;
		__IO BIT IDR_8 : 1;
		__IO BIT IDR_9 : 1;
		__IO BIT IDR_10 : 1;
		__IO BIT IDR_11 : 1;
		__IO BIT IDR_12 : 1;
		__IO BIT IDR_13 : 1;
		__IO BIT IDR_14 : 1;
		__IO BIT IDR_15 : 1;
		__IO BIT UNUSED : 16;
	};
	uint32_t ALLBITS;

} GPIO_IDR_Type, * GPIO_IDR_Type_ptr;


typedef struct
{
	__IO RCC_CR_Type CR; /*!< RCC clock control register,                                  Address offset: 0x00 */
	__IO RCC_PLLCFGR_Type PLLCFGR; /*!< RCC PLL configuration register,                              Address offset: 0x04 */
	__IO RCC_CFGR_Type CFGR; /*!< RCC clock configuration register,                            Address offset: 0x08 */
	__IO RCC_CIR_Type CIR; /*!< RCC clock interrupt register,                                Address offset: 0x0C */
	__IO uint32_t AHB1RSTR; /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
	__IO uint32_t AHB2RSTR; /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
	__IO uint32_t AHB3RSTR; /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
	uint32_t      RESERVED0; /*!< Reserved, 0x1C                                                                    */
	__IO uint32_t APB1RSTR; /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
	__IO uint32_t APB2RSTR; /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
	uint32_t      RESERVED1[2]; /*!< Reserved, 0x28-0x2C                                                               */
	__IO RCC_AHB1ENR_Type AHB1ENR; /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
	__IO RCC_AHB2ENR_Type AHB2ENR; /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
	__IO RCC_AHB3ENR_Type AHB3ENR; /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
	uint32_t      RESERVED2; /*!< Reserved, 0x3C                                                                    */
	__IO uint32_t APB1ENR; /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
	__IO uint32_t APB2ENR; /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
	uint32_t      RESERVED3[2]; /*!< Reserved, 0x48-0x4C                                                               */
	__IO uint32_t AHB1LPENR; /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
	__IO uint32_t AHB2LPENR; /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
	__IO uint32_t AHB3LPENR; /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
	uint32_t      RESERVED4; /*!< Reserved, 0x5C                                                                    */
	__IO uint32_t APB1LPENR; /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
	__IO uint32_t APB2LPENR; /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
	uint32_t      RESERVED5[2]; /*!< Reserved, 0x68-0x6C                                                               */
	__IO uint32_t BDCR; /*!< RCC Backup domain control register,                          Address offset: 0x70 */
	__IO uint32_t CSR; /*!< RCC clock control & status register,                         Address offset: 0x74 */
	uint32_t      RESERVED6[2]; /*!< Reserved, 0x78-0x7C                                                               */
	__IO uint32_t SSCGR; /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
	__IO uint32_t PLLI2SCFGR; /*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */
} ResetAndClockControl, *ResetAndClockControl_ptr;

typedef struct
{
	__IO GPIO_MODER_Type MODER;
	__IO GPIO_OTYPER_Type OTYPER;
	__IO GPIO_OSPEEDR_Type SPEEDR;
	
} GeneralPurposeIO_A, * GeneralPurposeIO_A_ptr;

typedef struct
{
	
} AHB1, *AHB1_ptr;
