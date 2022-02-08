/*
 * can2_com_manager.c
 *
 *  Created on: Jan 27, 2022
 *      Author: shin
 */
#include "main.h"
#include "uart.h"
#include "uart_datalink_parsing.h"
#include "can2_com_manager.h"


extern uint8_t my_can_id;
uint8_t rxID;
uint16_t rxPosi;

#include "app_pid_midi_cmd.h"

void UART_App_JMM_LCD_Setting_Polling_RxReq(UART_JMM_LCD_SettingTypeDef *pData)
{


}


void CAN_App_JMS_POSI_DATA_RxReq(uint8_t canid, uint16_t posi)
{
	rxID = canid;
	rxPosi = posi;
	app_tx_midi_sub_pid_adc_ctl(0, 0, my_can_id, MASTER_CAN_ID, 0, 0,
										(rxID&0xF0)>>4,
										rxID&0x0F,
										rxPosi);
}


