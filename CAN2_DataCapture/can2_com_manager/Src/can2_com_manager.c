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

#include "app_pid_edit_cmd.h"



extern uint8_t my_can_id;

extern filter_TypeDef filter[FILTER_NUM];

MotionData_TypeDef motion;

uint8_t settingFirst = 0;
void UART_App_JMM_LCD_Setting_Polling_RxReq(UART_JMM_LCD_SettingTypeDef *pData)
{
	settingFirst = 1;
	memcpy((uint8_t *)&motion.setting,(uint8_t *)pData,sizeof(UART_JMM_LCD_SettingTypeDef));
}

void UART_App_JMM_On_Setting_View_RxReq(void)
{
	app_tx_edit_sub_pid_action_ctl(0, 0, my_can_id, MASTER_CAN_ID, 0, 0,
			EDIT_ACTION_KEY_POSITION_START);
}
//==============================================================================
uint8_t rxGid;
uint8_t rxSid;
uint16_t rxPosi;

uint8_t monitor = 0;

void newDataProcess(void)
{
	UART_JMM_LCD_MotionOut_Data_TypeDef newData = {0,};

	if(settingFirst == 0)
		return;

	for(int i = 0; i < SLIDE_CNT; i++)
	{

		if (motion.data[i].oldData != motion.data[i].filterData) {
			motion.data[i].oldData = motion.data[i].filterData;

			if((motion.setting[i].gid == 0)||(motion.setting[i].gid == 0)||(motion.setting[i].slideid == 0)||(motion.data[i].f_first == 0))
			{
				return;
			}

			monitor = motion.setting[i].slideid;

			app_tx_midi_sub_pid_adc_ctl(0, 0, my_can_id, MASTER_CAN_ID, 0, 0,
					motion.setting[i].gid, motion.setting[i].sid,
					motion.data[i].filterData);

			newData.gid = motion.setting[i].gid;
			newData.sid = motion.setting[i].sid;
			newData.posi = motion.data[i].filterData;

			UART_App_JMM_LCD_MotionOut_Data_TxReq(&newData);
		}
	}
}

#if 0
uint8_t findIDtoIndex(uint8_t gid, uint8_t sid)
{
	int i = 0;
	for( i = 0; i < SLIDE_CNT; i++)
	{
		if((motion.setting[i].gid == gid)&&(motion.setting[i].sid == sid))
		{
			return i;
		}
	}
	return i;
}
#endif

uint8_t findIDtoIndex(uint8_t id)
{
	int i = 0;
	for( i = 0; i < SLIDE_CNT; i++)
	{
		if(motion.setting[i].slideid == id)
		{
			return i;
		}
	}
	return i;
}

uint8_t firstData[255] = {0,};


void CAN_App_JMS_POSI_DATA_RxReq(uint8_t canid, uint16_t posi)
{
	rxGid = (canid&0xF0)>>4;
	rxSid = canid&0x0F;
	rxPosi = posi;
	uint8_t index = 0;
	//if( (index = findIDtoIndex(rxGid, rxSid)) != SLIDE_CNT)
	if( (index = findIDtoIndex(canid)) != SLIDE_CNT)
	{

		motion.data[index].rawData = rxPosi;
		motion.data[index].f_first = 1;
		if (firstData[canid] == 0) {

			firstData[canid] = 1;
			filter_calc(index,
					&filter[index].SmoothData,
					filter[index].outData,
					*filter[index].inData,
					1.0f);
		}
	}
}


