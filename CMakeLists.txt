cmake_minimum_required (VERSION 2.6)

project(usb_device C CXX ASM)

add_executable(${PROJECT_NAME}
	Core/Src/main.c
	Core/Src/stm32f2xx_it.c
	Core/Src/stm32f2xx_hal_msp.c
	Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_eth.c
	Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim.c
	Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim_ex.c
	Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_uart.c
	Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pcd_ex.c
	Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pcd.c
	Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_ll_usb.c
	Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal.c
	Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc.c
	Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc_ex.c
	Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_cortex.c
	Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash.c
	Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash_ex.c
	Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr.c
	Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr_ex.c
	Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_gpio.c
	Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma.c
	Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma_ex.c
	Core/Src/syscalls.c
	Core/Src/system_stm32f2xx.c
	Core/Src/stm32f2xx_hal_timebase_tim.c
	USB_DEVICE/App/usb_device.c
	USB_DEVICE/App/usbd_desc.c
	USB_DEVICE/App/usbd_cdc_if.c
	USB_DEVICE/Target/usbd_conf.c
	Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c
	Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c
	Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c
	Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c
	startup_stm32f207xx.s
	src/user_main.cc
	)

target_include_directories(${PROJECT_NAME}
	PRIVATE Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc
	PRIVATE Middlewares/ST/STM32_USB_Device_Library/Core/Inc
	PRIVATE USB_DEVICE/App
	PRIVATE USB_DEVICE/Target
	PRIVATE Drivers/CMSIS/Include
	PRIVATE Drivers/CMSIS/Device/ST/STM32F2xx/Include
	PRIVATE Drivers/STM32F2xx_HAL_Driver/Inc
	PRIVATE Drivers/STM32F2xx_HAL_Driver/Inc/Legacy
	PRIVATE Core/Inc
	PRIVATE src)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	-DSTM32F207xx
	-DUSE_HAL_DRIVER)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${SIZE_TOOL} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_compile_options(${PROJECT_NAME} PRIVATE
	-mcpu=cortex-m3
	-mthumb
	-mfloat-abi=soft
	-Os
	-Wall
	-g
	-gdwarf-2
	-MMD
	-MP
	-ffunction-sections
	-fdata-sections
)

set(CMAKE_CXX_FLAGS "-fno-rtti -fno-exceptions")

target_link_options(${PROJECT_NAME} PRIVATE
	-mcpu=cortex-m3
	-mthumb
	--specs=nano.specs
	-T${CMAKE_SOURCE_DIR}/STM32F207ZGTx_FLASH.ld
	-lc
	-lm
	-lnosys
	-Wl,--gc-sections
	-Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.map,--cref
)
