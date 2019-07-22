#pragma once
#include "stm32f2xx_hal.h"
#include <stdint.h>

namespace stm32f2xx
{

struct BaseAddress
{
	enum Value : uint32_t
	{
		Flash            = 0x08000000U,
		FlashEnd         = 0x080FFFFFU,
		Sram1            = 0x20000000U,
		Sram2            = 0x2001C000U,
		Peripheral       = 0x40000000U,
		BackupRam        = 0x40024000U,
		Fsmc             = 0xA0000000U,
		Sram1BitBand     = 0x22000000U,
		Sram2BitBand     = 0x22380000U,
		PeriphBitBand    = 0x42000000U,
		BackupRamBitBand = 0x42480000U,
		FlashOtp         = 0x1FFF7800U,
		FlashOtpEnd      = 0x1FFF7A0FU
	};
};

struct ApbBaseAddress
{
	enum Value : uint32_t
	{
		Apb1 = static_cast<uint32_t>(BaseAddress::Peripheral),
		Apb2 = (BaseAddress::Peripheral + 0x00010000U)
	};
};

struct AhbBaseAddress
{
	enum Value : uint32_t
	{
		Ahb1 = BaseAddress::Peripheral + 0x00020000U,
		Ahb2 = BaseAddress::Peripheral + 0x10000000U
	};
};

struct GpioBaseAddress
{
	enum Value : uint32_t
	{
		A = AhbBaseAddress::Ahb1 + 0x0000U,
		B = AhbBaseAddress::Ahb1 + 0x0400U,
		C = AhbBaseAddress::Ahb1 + 0x0800U,
		D = AhbBaseAddress::Ahb1 + 0x0C00U,
		E = AhbBaseAddress::Ahb1 + 0x1000U,
		F = AhbBaseAddress::Ahb1 + 0x1400U,
		G = AhbBaseAddress::Ahb1 + 0x1800U,
		H = AhbBaseAddress::Ahb1 + 0x1C00U,
		I = AhbBaseAddress::Ahb1 + 0x2000U
	};
};

struct Pin
{
	enum Value : uint16_t
	{
		_0  =0x0001,
		_1  =0x0002,
		_2  =0x0004,
		_3  =0x0008,
		_4  =0x0010,
		_5  =0x0020,
		_6  =0x0040,
		_7  =0x0080,
		_8  =0x0100,
		_9  =0x0200,
		_10 =0x0400,
		_11 =0x0800,
		_12 =0x1000,
		_13 =0x2000,
		_14 =0x4000,
		_15 =0x8000
	};
};

template<GpioBaseAddress::Value ADDRESS, Pin::Value PIN>
struct Output
{
	static GPIO_TypeDef * reg()
	{
		return ((GPIO_TypeDef *)ADDRESS);
	}

	static void toggle()
	{
		reg()->ODR ^= PIN;
	}

	static void on()
	{
		reg()->BSRR = PIN;
	}

	static void off()
	{
		reg()->BSRR = static_cast<uint32_t>(PIN) << 16U;
	}
};

}
