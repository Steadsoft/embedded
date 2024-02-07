#pragma once

#define BIT unsigned int
#define RCC_CFGR ((RCC_CFGR_Type_ptr)&(RCC->CFGR)) 
#define RCC_AHB1ENR ((RCC_AHB1ENR_Type_ptr)&(RCC->AHB1ENR)) 
#define RCC_CR ((RCC_CR_Type_ptr)&(RCC->CR)) 

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
		__IO BIT UNUSED1 : 1;
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
		__IO BIT PLL_SAI_ON : 1;
		__IO BIT PLL_SAI_RDY : 1;
		__IO BIT UNUSED3 : 2;
	};
	uint32_t ALLBITS;
} RCC_CR_Type, * RCC_CR_Type_ptr;
