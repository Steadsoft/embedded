#pragma once
#define SPEEDR_LOW 0
#define SPEEDR_MEDIUM 1
#define SPEEDR_HIGH 2
#define SPEEDR_VERY_HIGH = 3

#define SPEEDR(X) SPEEDR_ ## X

#define MCOPRE_NONE 0
#define MCOPRE_2 4
#define MCOPRE_3 5
#define MCOPRE_4 6
#define MCOPRE_5 7

#define MCOPRE(X) MCOPRE_ ## X

#define MCO1_HSI 0
#define MCO1_LSE 1
#define MCO1_HSE 2
#define MCO1_PLL 3

#define MCO1(X) MCO1_ ## X

#define I2SSRC_PLLI2S 0
#define I2SSRC_EXTERNAL 1

#define I2SSRC(X) I2SSRC_ ## X

#define SW_HSI 0
#define SW_HSE 1
#define SW_PLL 2

#define SW(X) SW_ ## X

#define SWS_HSI 0
#define SWS_HSE 1
#define SWS_PLL 2

#define SWS(X) SWS_ ## X


#define MODER(X) MODER_ ## X

#define MODER_INPUT 0
#define MODER_GENERAL 1
#define MODER_ALTERNATE 2
#define MODER_ANALOG 3


// This is helpful but only useable of the X is constant.
#define MODERBIT(Y) MODER_ ## Y
// e.g. 	ahb1_ptr->GPIO_D.MODER.MODERBIT(12)  = MODER(GENERAL);
