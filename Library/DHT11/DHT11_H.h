#ifndef __DHT11_H
#define __DHT11_H
/*-------------------------------------------
  edit by NHAT HOANG
-------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h" //BOARD f4

//#include "stm32f1xx_hal.h" //BOARD F1

/**************************** KHAI BAO BIEN ****************************/
typedef struct
{
	uint8_t temp_int ;  //so nguyen nhiet do
	uint8_t temp_deci ; //so thap phan nhiet do 
	uint8_t humi_int ; 	//So nguyen cua do am
	uint8_t humi_deci ;	//So thap phan do am 
	uint8_t check_sum ; //sum tong
} DHT11_DATA_TypeDef ;
/********************************* DHT11 Define Port ket noi DHT11 ********************************/
#define			GPIO_DHT11_CLK			__HAL_RCC_GPIOB_CLK_ENABLE();
#define			GPIO_DHT11_PORT			GPIOB						
#define			GPIO_DHT11_PIN			GPIO_PIN_5 

/********************************* DHT11 define GPIO loai vao ra**************************************/
#define			DHT11_DOUT_0			HAL_GPIO_WritePin( GPIO_DHT11_PORT , GPIO_DHT11_PIN,GPIO_PIN_RESET)
#define 		DHT11_DOUT_1			HAL_GPIO_WritePin( GPIO_DHT11_PORT , GPIO_DHT11_PIN,GPIO_PIN_SET)
#define 		DHT11_DATA_IN()		    HAL_GPIO_ReadPin( GPIO_DHT11_PORT , GPIO_DHT11_PIN) 

/*********************************KHAI BAO HAM CON *************************************/
void DHT11_Init(void) ;
void delay_ms(uint16_t au16_ms);// delay ms
void delay_us(uint16_t au16_us);//delay us
uint8_t Read_TempAndHumidity (DHT11_DATA_TypeDef *DHT11_DATA) ;
#endif 						
