/*
 * can2_com_manager.c
 *
 *  Created on: Jan 27, 2022
 *      Author: shin
 */
#include "main.h"
#include "string.h"
#include "uart.h"
#include "uart_datalink_parsing.h"
#include "can2_com_manager.h"
#include "app_pid_midi_cmd.h"
#include "filter_manager.h"

extern uint8_t my_can_id;

extern filter_TypeDef filter[FILTER_NUM];

MotionData_TypeDef motion;

void UART_App_JMM_LCD_Setting_Polling_RxReq(UART_JMM_LCD_SettingTypeDef *pData)
{
	memcpy((uint8_t *)&motion.setting,(uint8_t *)pData,sizeof(UART_JMM_LCD_SettingTypeDef));
}
//==============================================================================
uint8_t rxGid;
uint8_t rxSid;
uint16_t rxPosi;

void newDataProcess(void)
{

	UART_JMM_LCD_MotionOut_Data_TypeDef newData = {0,};
	for(int i = 0; i < 10; i++)
	{
		if(motion.data[i].oldData != motion.data[i].filterData)
		{
			motion.data[i].oldData = motion.data[i].filterData;

			 app_tx_midi_sub_pid_adc_ctl(0, 0, my_can_id, MASTER_CAN_ID, 0, 0,
					 motion.setting[i].gid,
					 motion.setting[i].sid,
					 motion.data[i].filterData);

			 newData.gid = motion.setting[i].gid;
			 newData.sid = motion.setting[i].sid;
			 newData.posi = motion.data[i].filterData;

			 UART_App_JMM_LCD_MotionOut_Data_TxReq(&newData);
		}
	}
}

uint8_t findIDtoIndex(uint8_t gid, uint8_t sid)
{
	int i = 0;
	for( i = 0; i < 10; i++)
	{
		if((motion.setting[i].gid == gid)&&(motion.setting[i].sid == sid))
		{
			return i;
		}
	}
	return i;
}

void CAN_App_JMS_POSI_DATA_RxReq(uint8_t canid, uint16_t posi)
{
	rxGid = (canid&0xF0)>>4;
	rxSid = canid&0x0F;
	rxPosi = posi;
	uint8_t index = 0;
	if( (index = findIDtoIndex(rxGid, rxSid)) != 10)
	{
		motion.data[index].rawData = rxPosi;


	}
}


