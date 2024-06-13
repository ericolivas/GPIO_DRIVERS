#include <stdio.h>
#include "GPIO.h"

//DIRECCIONES DE LOS REGISTROS GPIO Y GPI
//******************************************************
const uint32_t _IO_MUX_REGISTERS[] = {
	0x3FF49044, //GPIO0_REG				INICIAN IN/OUT
	0x3FF49088, //GPIO1_REG
	0x3FF49040, //GPIO2_REG
	0x3FF49084, //GPIO3_REG
	0x3FF49048, //GPIO4_REG
	0x3FF4906C, //GPIO5_REG
	0x3FF49060, //GPIO6_REG
	0x3FF49064, //GPIO7_REG
	0x3FF49068, //GPIO8_REG
	0x3FF49054, //GPIO9_REG
	0x3FF49058, //GPIO10_REG
	0x3FF4905C, //GPIO11_REG
	0x3FF49034, //GPIO12_REG
	0x3FF49038, //GPIO13_REG
	0x3FF49030, //GPIO14_REG
	0x3FF4903C, //GPIO15_REG
	0x3FF4904C, //GPIO16_REG
	0x3FF49050, //GPIO17_REG
	0x3FF49070, //GPIO18_REG
	0x3FF49074, //GPIO19_REG
	0x00000000, //20 NOT A GPIO PORT
	0x3FF4907C, //GPIO21_REG
	0x3FF49080, //GPIO22_REG
	0x3FF4908C, //GPIO23_REG
	0x00000000, //24 NOT A GPIO PORT
	0x3FF49024, //GPIO25_REG
	0x3FF49028, //GPIO26_REG
	0x3FF4902C, //GPIO27_REG
	0x00000000, //28 NOT A GPIO PORT
	0x00000000, //29 NOT A GPIO PORT
	0x00000000, //30 NOT A GPIO PORT
	0x00000000, //31 NOT A GPIO PORT
	0x0000001C, //GPIO32_REG
	0x3FF49020, //GPIO33_REG			TERMINAN IN/OUT
	0x3FF49014, //GPIO34_REG			INICIAN IN
	0x3FF49018, //GPIO35_REG
	0x3FF49004, //GPIO36_REG
	0x3FF49008, //GPIO37_REG
	0x3FF4900C, //GPIO38_REG
	0x3FF49010, //GPIO39_REG			TERMINAN IN
};

/**************************************************************************
* Function: ENABLE_PIN_AS_INPUT
* Preconditions: NONE
* Overview: WRITES 1 AT THE 9TH BIT OF THE SPECIFIED REGISTER TO ENABLE IT AS INPUT.
* Input: PIN NUMBER.
* Output: NONE.
*
*****************************************************************************/

;static void ENABLE_PIN_AS_INPUT(uint8_t pin_num){
	(*(volatile uint32_t*)(_IO_MUX_REGISTERS[pin_num])) |= INPUT_ENABLE;
}

/**************************************************************************
* Function: DISABLE_PIN_AS_INPUT
* Preconditions: NONE
* Overview: WRITES 0 AT THE 9TH BIT OF THE SPECIFIED REGISTER TO DISABLE IT AS INPUT.
* Input: PIN NUMBER.
* Output: NONE.
*
*****************************************************************************/
static void DISABLE_PIN_AS_INPUT(uint8_t pin_num){
	(*(volatile uint32_t*)(_IO_MUX_REGISTERS[pin_num])) &= INPUT_DISABLE;
}

/**************************************************************************
* Function: ENABLE_PIN_AS_OUTPUT
* Preconditions: NONE
* Overview: WRITES 1 AT THE SPECIFIED BIT OF THE OUTPUT ENABLE REGISTER TO TURN THAT PIN INTO AN OUTPUT PIN
* Input: PIN NUMBER.
* Output: NONE.
*
*****************************************************************************/
static void ENABLE_PIN_AS_OUTPUT(uint8_t pin_num){
	if(pin_num < 32)
		OUTPUT_ENABLE_REG_0_31 |= (1 << pin_num);
	if(pin_num > 31)
		OUTPUT_ENABLE_REG_32_33 |= (1 << (pin_num - 32));
}

/**************************************************************************
* Function: DISABLE_PIN_AS_OUTPUT
* Preconditions: NONE
* Overview: WRITES 0 AT THE SPECIFIED BIT OF THE OUTPUT ENABLE REGISTER TO DISABLE THAT PIN AS AN OUTPUT PIN
* Input: PIN NUMBER.
* Output: NONE.
*
*****************************************************************************/
static void DISABLE_PIN_AS_OUTPUT(uint8_t pin_num){
	if(pin_num < 32)
		OUTPUT_ENABLE_REG_0_31 &= (~(1 << pin_num));
	if(pin_num > 31)
		OUTPUT_ENABLE_REG_32_33 &= (~(1 << (pin_num - 32)));
}

/**************************************************************************
* Function: MODO
*****************************************************************************/
void MODO(uint8_t pin_num, MODO_GPIO MODO){

	(*(volatile uint32_t*)(_IO_MUX_REGISTERS[pin_num])) |= HABILITAR;
	//DISPONIBLE PARA REGISTROS GPIO Y GPI
	if (MODO == ENTRADA){
		DISABLE_PIN_AS_OUTPUT(pin_num);
		ENABLE_PIN_AS_INPUT(pin_num);
	}
	//DISPONIBLE PARA REGISTROS GPIO
	if (MODO == SALIDA){
		DISABLE_PIN_AS_INPUT(pin_num);
		ENABLE_PIN_AS_OUTPUT(pin_num);
	}
}

/**************************************************************************
* Function: RESISTENCIAS
*****************************************************************************/
void RESISTENCIAS(uint8_t pin_num, MODO_RESISTENCIAS MODO){
	if (MODO == RES_PULLUP){
		(*(volatile uint32_t*)(_IO_MUX_REGISTERS[pin_num])) &= PULLDOWN_DISABLE;
		(*(volatile uint32_t*)(_IO_MUX_REGISTERS[pin_num])) |= PULLUP_ENABLE;
	}

	if (MODO == RES_PULLDOWN){
		(*(volatile uint32_t*)(_IO_MUX_REGISTERS[pin_num])) &= PULLUP_DISABLE;
		(*(volatile uint32_t*)(_IO_MUX_REGISTERS[pin_num])) |= PULLDOWN_ENABLE;
	}

}

/**************************************************************************
* Function: LEER
*****************************************************************************/
int LEER(uint8_t pin_num){
	int LECTURA;
	if(pin_num < 32){
		if(((INPUT_STATUS_REG_0_31 >> pin_num) & 0x1) == 1)
			LECTURA = 1;
		else
			LECTURA = 0;
	}
	if(pin_num > 31){
		if(((INPUT_STATUS_REG_32_39 >> (pin_num - 32)) & 0x1) == 1)
			LECTURA = 1;
		else
			LECTURA = 0;
	}
	return LECTURA;
}

/**************************************************************************
* Function: ESCRIBIR
*****************************************************************************/
void ESCRIBIR(uint8_t pin_num, ESTADO EDO){
	if(pin_num < 32){
		if(EDO == ALTO)
			SET_OUTPUT_PIN_REG_0_31 |= (1 << pin_num);
		if(EDO == BAJO)
			CLEAR_OUTPUT_PIN_REG_0_31 |= (1 << pin_num);
	}
	if(pin_num > 31){
		if(EDO == ALTO)
			SET_OUTPUT_PIN_REG_32_33 |= (1 << (pin_num - 32));
		if(EDO == BAJO)
			CLEAR_OUTPUT_PIN_REG_32_33 |= (1 << (pin_num - 32));
	}
}



