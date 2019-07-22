#include "io_pin.h"
#include "stm32f2xx_hal.h"
#include "main.h"


extern "C"
{

using blue_led = stm32f2xx::Output<stm32f2xx::GpioBaseAddress::B, stm32f2xx::Pin::_7>;

void user_main()
{

	uint8_t data[] = "Hallo Welt\n";


	while (1)
	{
		// HAL_GPIO_TogglePin(LedRed_GPIO_Port, LedRed_Pin);
		// HAL_GPIO_TogglePin(LedBlue_GPIO_Port, LedBlue_Pin);
		HAL_GPIO_TogglePin(LedGreen_GPIO_Port, LedGreen_Pin);

		blue_led::toggle();

		HAL_Delay(1000);
		printf("%s", data);
	}

}

//#define LedBlue_Pin                 GPIO_PIN_7
//#define LedBlue_GPIO_Port           GPIOB

}