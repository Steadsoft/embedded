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