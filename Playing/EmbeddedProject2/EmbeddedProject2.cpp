#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_ll_gpio.h>
#include <stm32f4xx_ll_utils.h>

int main(void)
{
	LL_InitTick(16000000, 1000);

	//Warning: if the line below triggers an error, GPIOD is not connected to a AHB1 (Group 1) on this device.
	//In this case, please search the stm32xxxx_ll_bus.h file for 'PERIPH_GPIOD' to find out the correct
	//macro name and use it to replace LL_AHB1_GRP1_PERIPH_$$com.sysprogs.examples.lBedblink.LEDPORT$$ and LL_AHB1_GRP1_EnableClock() below. 
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
	
	LL_GPIO_SetPinMode(GPIOD, LL_GPIO_PIN_12, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(GPIOD, LL_GPIO_PIN_12, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinSpeed(GPIOD, LL_GPIO_PIN_12, LL_GPIO_SPEED_FREQ_LOW);

	LL_GPIO_SetPinMode(GPIOD, LL_GPIO_PIN_11, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(GPIOD, LL_GPIO_PIN_11, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinSpeed(GPIOD, LL_GPIO_PIN_11, LL_GPIO_SPEED_FREQ_LOW);

	for (;;)
	{
		//LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_12);
		//LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_11);
		WRITE_REG(GPIOD->BSRR, LL_GPIO_PIN_11);
		//LL_mDelay(5);
		//LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_12);
		//LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_11);
		WRITE_REG(GPIOD->BSRR, (LL_GPIO_PIN_11 << 16));
		//LL_mDelay(5);
	}
}
