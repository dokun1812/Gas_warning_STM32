
#include "DHT11_H.h"
static void     GPIO_DHT11_OUT(void) ;
static void     GPIO_DHT11_IN(void)  ;
static uint8_t  READ_DATA_8BIT(void) ;

/***************************** DHT11 khoi tao***********************/
void DHT11_Init(void)
{
	//GPIO che dau dau ra
	GPIO_DHT11_OUT() ;	
	//Khoi tao pin DHT11
	DHT11_DOUT_1 ;
	delay_ms(1000);
}
/********************************Khoi tao GPIO Output***************************/
static void GPIO_DHT11_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStruct ;
    // cho phep port
	GPIO_DHT11_CLK;
	GPIO_InitStruct.Pin = GPIO_DHT11_PIN ; 
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP ;//output
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH ;
	HAL_GPIO_Init( GPIO_DHT11_PORT , &GPIO_InitStruct ) ;	
}
/********************************Khoi tao GPIO Input***************************/
static void GPIO_DHT11_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStruct ;
	GPIO_InitStruct.Pin	= GPIO_DHT11_PIN ; 
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT ;//input
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH ;
	HAL_GPIO_Init( GPIO_DHT11_PORT	, &GPIO_InitStruct ) ;
}

/**********************************Doc 8 bit dau vao DHT11**********************************/
static uint8_t  READ_DATA_8BIT(void)
{
	uint8_t  i , data=0;
	//Doc 8bit
	for(i=0;i<8;i++)
	{	
		// 50us moi lan gui du lieu
		while( DHT11_DATA_IN()==0) ;	
		//thoi gian kiem tra = 1 or 0
		delay_us(50);
		//Neu bang 1 thi da truyen di
		if( DHT11_DATA_IN() == 1 )
		{
			//cho cho truyen du lieu ket thuc
			while( DHT11_DATA_IN() == 1 );
			//chuyen du lieu tiep theo vao data
			data |= (uint8_t)(0x01 << (7-i)) ;
		}
		else 
			//Du lieu 0 duoc truyen toi bit cao
			data &= (uint8_t)~(0x01 << (7-i)) ;//co the thay doi data &= (uint8_t)(0x00 << (7-i)) cung duoc
	}
	//Truyen 1 byte du lieu di
	return data ;
}

/****************************Doc Dât DHT11*************************************/
uint8_t Read_TempAndHumidity (DHT11_DATA_TypeDef *DHT11_DATA)
{
	/*	Che do dau ra	*/
	GPIO_DHT11_OUT() ;
	/*	Cho pin =0	*/
	DHT11_DOUT_0 ;
	/*	Delay 18ms	*/
	delay_ms(20) ;
	/*	delay pin len 1 trong 30us	*/
	DHT11_DOUT_1 ;
	delay_us(30) ;
	/*	Chuyen sang che do input	*/
	GPIO_DHT11_IN() ;
	//Kiem tra nhan duoc tin hieu tu DHT11 ko , neu ko nhan duoc bao error
	if(DHT11_DATA_IN() == 0)
	{
          //Cho ket thuc tin lieu =0 
          while(DHT11_DATA_IN() == 0) ;
          //Cho cho ket thuc muc cao
          while(DHT11_DATA_IN() == 1) ;
          //bat dau chuyen du lieu
          DHT11_DATA->humi_int  = READ_DATA_8BIT() ; 
          DHT11_DATA->humi_deci = READ_DATA_8BIT() ; 
          DHT11_DATA->temp_int  = READ_DATA_8BIT() ; 
          DHT11_DATA->temp_deci = READ_DATA_8BIT() ;
          DHT11_DATA->check_sum = READ_DATA_8BIT() ;
          //Ket thuc qua trinh nhan du lieu thay doi dau sensor la dau ra
          GPIO_DHT11_OUT();
          //Dong pin lai
          DHT11_DOUT_1 ;
          //Kiem tra sum truyen dung tra lai SUCCESS, neu sai tra lai ERROR ;
          if(DHT11_DATA->check_sum == DHT11_DATA->humi_int + DHT11_DATA->humi_deci + DHT11_DATA->temp_int + DHT11_DATA->temp_deci)return SUCCESS ;
          else return ERROR ;
	}		
	else return ERROR ;	
}
//--------------------------------------------------TIMER_DELAY---------------------------------------
//void delay_us(uint16_t au16_us)
//	{
//		htim6.Instance->CNT = 0;
//		while(htim6.Instance->CNT < au16_us);
// void delay_ms(uintt16_t au16 ms)
//{
//		while(au16_ms > 0)
//		{
//			htim6.Instance->CNT = 0;
//				au16_ms--;
//		while (htim6.Instance->CNT<1000);
//		}
//}
//-------------------------------------------khoi tao HTIM4 de tao ham delay dung tim4---------------------
//static void MX_TIM4_Init(void)
//{

//  /* USER CODE BEGIN TIM4_Init 0 */
//gu32_ticks = (HAL_RCC_GetHCLKFreq() / 2000000);
//	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
//  /* USER CODE END TIM4_Init 0 */
//TIM_MasterConfigTypeDef sMasterConfig = {0};
//  /* USER CODE BEGIN TIM4_Init 1 */

//  /* USER CODE END TIM4_Init 1 */
//  htim4.Instance = TIM4;
//  htim4.Init.Prescaler = gu32_ticks-1;
//  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
//  htim4.Init.Period = 65535;
//  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
//  if (HAL_TIM_OnePulse_Init(&htim4, TIM_OPMODE_SINGLE) != HAL_OK)
//  {
//    Error_Handler();
//  }
//	sMasterConfig.MasterOutputTrigger =TIM_TRGO_RESET;
//	sMasterConfig.MasterSlaveMode= TIM_MASTERSLAVEMODE_DISABLE;	
//	if (HAL_TIMEx_MasterConfigSynchronization (&htim4, &sMasterConfig) != HAL_OK)
//	{
//		Error_Handler();
//	}	
