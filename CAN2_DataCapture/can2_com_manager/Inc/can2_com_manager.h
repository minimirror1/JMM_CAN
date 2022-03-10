/*
 * can2_com_manager.h
 *
 *  Created on: Jan 27, 2022
 *      Author: shin
 */

#ifndef CAN2_COM_MANAGER_INC_CAN2_COM_MANAGER_H_
#define CAN2_COM_MANAGER_INC_CAN2_COM_MANAGER_H_

#include "main.h"
#include "uart.h"
#include "uart_datalink_parsing.h"

#pragma pack(1)
typedef struct{
	int rawData;
	int filterData;
	int oldData;
}ControlData_TypeDef;

typedef struct{
	UART_JMM_LCD_SettingData_TypeDef setting[SLIDE_CNT];
	ControlData_TypeDef data[SLIDE_CNT];
}MotionData_TypeDef;
#pragma pack()

void newDataProcess(void);

#endif /* CAN2_COM_MANAGER_INC_CAN2_COM_MANAGER_H_ */
