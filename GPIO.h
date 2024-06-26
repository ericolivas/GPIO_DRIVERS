#ifndef INCLUDE_GPIO_H
#define INCLUDE_GPIO_H

#include <stdio.h>
#define OUTPUT_ENABLE_REG_0_31     (*(volatile uint32_t*)(0x3FF44020)) // REGISTER TO ENABLE GPIO PINS 0-31 AS OUTPUTS
#define OUTPUT_ENABLE_REG_32_33    (*(volatile uint32_t*)(0x3FF4402C)) // REGISTER TO ENABLE GPIO PINS 32-39 AS OUTPUTS
#define SET_OUTPUT_PIN_REG_0_31    (*(volatile uint32_t*)(0x3FF44008)) // REGISTER TO SET AN OUTPUT PIN HIGH
#define CLEAR_OUTPUT_PIN_REG_0_31  (*(volatile uint32_t*)(0x3FF4400C)) // REGISTER TO SET AN OUTPUT PIN LOW
#define SET_OUTPUT_PIN_REG_32_33   (*(volatile uint32_t*)(0x3FF44014)) // REGISTER TO SET AN OUTPUT PIN HIGH
#define CLEAR_OUTPUT_PIN_REG_32_33 (*(volatile uint32_t*)(0x3FF44018)) // REGISTER TO SET AN OUTPUT PIN LOW

//REGISTROS DE ENTRADA: DISPONIBLES DEL 0 AL 39 [MENOS 20,24,28-31]
//******************************************************
#define INPUT_STATUS_REG_0_31 	 (*(volatile uint32_t*)(0x3FF4403C)) // REGISTER TO READ THE INPUTS 0-31 STATUS
#define INPUT_STATUS_REG_32_39   (*(volatile uint32_t*)(0x3FF44040)) // REGISTER TO READ THE INPUTS 32-39 STATUS


//MASCARAS PARA RESISTRO IO_MUX_x_REG donde x: pin_num
 // 1 Y 0 en bit 7 del registro [FUN-WPD]
#define PULLDOWN_ENABLE   (1UL<<7) 
#define PULLDOWN_DISABLE  (~(1UL<<7))
// 1 Y 0 en bit 8 del registro [FUN-WPU]
#define PULLUP_ENABLE     (1UL<<8)
#define PULLUP_DISABLE    (~(1UL<<8))
// 1 Y 0 en bit 9 del registro [FUN-IE]
#define INPUT_ENABLE      (1UL<<9)
#define INPUT_DISABLE     (~(1UL<<9))
// 1 en bit 13 del registro [MCU_SEL]
#define HABILITAR         (1UL<<13) 

typedef enum{
	BAJO = 1,
	ALTO = 2,
}ESTADO;

typedef enum {
	ENTRADA	= 1,
	SALIDA = 2,
}MODO_GPIO;

typedef enum {
	RES_PULLUP = 1,
	RES_PULLDOWN = 2,
}MODO_RESISTENCIAS;

extern int LEER(uint8_t pin_num);	//LEER PIN: SOLO PIDE EL PIN DEL CUAL SE TOMA LA LECTURA
extern void ESCRIBIR(uint8_t pin_num, ESTADO EDO);	//ESCRIBIR A PIN: PIDE EL PIN Y EL ESTADO A ESCRIBIR
extern void MODO (uint8_t pin_num, MODO_GPIO MODO);	//MODO DEL PIN: PIDE EL PIN Y SI VA A SER ENTRADA O SALIDA
extern void RESISTENCIAS(uint8_t pin_num, MODO_RESISTENCIAS MODO);	//HABILITAR RESISTENCIAS: PIDE EL PIN Y SI VA A SER PULLUP O PULLDOWN

#endif
