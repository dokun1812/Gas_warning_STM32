/** 
Edit by NHAT HOANG 
**/

#include "LCD_I2C_H.h"
extern I2C_HandleTypeDef hi2c1;  //i2c

#define SLAVE_ADDRESS_LCD 0x4E // dia chi lcd
// void delay_us(uint16_t au16_us)
// {
    // HTIM_INSTANCE.Instance->CNT = 0;
    // while (HTIM_INSTANCE.Instance->CNT < au16_us);
// }

// void delay_ms(uint16_t au16_ms)
// {
    // while(au16_ms > 0)
    // {
	// HTIM_INSTANCE.Instance->CNT = 0;
	// au16_ms--;
	// while (HTIM_INSTANCE.Instance->CNT < 1000);
    // }
// }

void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (I2C_INSTANCE, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
	//HAL_I2C_Master_Transmit_IT(I2C_INSTANCE, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4);
}

void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit (I2C_INSTANCE, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100); // khong ngat co anh huonng boi HAL_tick
	//HAL_I2C_Master_Transmit_IT(I2C_INSTANCE, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4);  //co ngat 
}

void lcd_init (void)
{
	lcd_send_cmd (0x33); /* set 4-bits interface */
	lcd_send_cmd (0x32);
	HAL_Delay(50);
	lcd_send_cmd (0x28); /* start to set LCD function */
	HAL_Delay(50);
	lcd_send_cmd (0x01); /* clear display */
	HAL_Delay(50);
	lcd_send_cmd (0x06); /* set entry mode */
	HAL_Delay(50);
	lcd_send_cmd (0x0c); /* set display to on */	
	HAL_Delay(50);
	lcd_send_cmd (0x02); /* move cursor to home and set data address to 0 */
	HAL_Delay(50);
	lcd_send_cmd (0x80);
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

void lcd_clear_display (void)
{
	lcd_send_cmd (0x01); //clear display
}

void lcd_goto_XY (int row, int col)
{
	uint8_t pos_Addr;
        switch(row)
             {
                case 0: //Row 0
                   pos_Addr=(0x80+0x00+col);
                   break;
                case 1: //Row 1
                   pos_Addr=(0x80+0x40+col);
                   break;
                case 2: //Row 2
                   pos_Addr=(0x80+0x14+col);
                   break;
                case 3: //Row 3
                   pos_Addr=(0x80+0x54+col);
                   break;
              }    
	lcd_send_cmd(pos_Addr);
}
//-------------------------------------khoi tao HTIM6 de tao ham delay dung tim6-------------------------------------------------------------------
//volatile uint32_t gu32_ticks =0;
// void MX_TIM6_Init(void)
// {
  
  // /* USER CODE BEGIN TIM6_Init 0 */
  // gu32_ticks = (HAL_RCC_GetHCLKFreq() / 2000000);
  // TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  // /* USER CODE END TIM6_Init 0 */

  // TIM_MasterConfigTypeDef sMasterConfig = {0};

  // /* USER CODE BEGIN TIM6_Init 1 */
  
  // /* USER CODE END TIM6_Init 1 */
  // htim6.Instance = TIM6;
  // htim6.Init.Prescaler = gu32_ticks-1;
  // htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  // htim6.Init.Period = 65535;
  // htim6.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  // htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  // if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  // {
    // Error_Handler();
  // }
  // sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  // if (HAL_TIM_ConfigClockSource(&htim6, &sClockSourceConfig) != HAL_OK)
  // {
    // Error_Handler(
	
	);
  // }
  // sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  // sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  // if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  // {
    // Error_Handler();
  // }
  // /* USER CODE BEGIN TIM6_Init 2 */
  // HAL_TIM_Base_Start(&htim6);
  // /* USER CODE END TIM6_Init 2 */
// }


