/*
 * can2_com_manager.c
 *
 *  Created on: Jan 27, 2022
 *      Author: shin
 */
#include "main.h"
#include "uart.h"
#include "can2_com_manager.h"


uint8_t rxID;
uint16_t rxPosi;


void UART_App_JMM_LCD_Setting_Polling_RxReq(UART_JMM_LCD_SettingTypeDef *pData)
{


}


void CAN_App_JMS_POSI_DATA_RxReq(uint8_t canid, uint16_t posi)
{
	rxID = canid;
	rxPosi = posi;


}


