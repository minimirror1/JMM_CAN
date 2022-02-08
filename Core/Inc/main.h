/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
extern uint8_t my_can_id;
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_1_Pin GPIO_PIN_3
#define LED_1_GPIO_Port GPIOE
#define LED_2_Pin GPIO_PIN_4
#define LED_2_GPIO_Port GPIOE
#define LED_RUN_Pin GPIO_PIN_5
#define LED_RUN_GPIO_Port GPIOE
#define LED_4_Pin GPIO_PIN_14
#define LED_4_GPIO_Port GPIOC
#define LED_5_Pin GPIO_PIN_15
#define LED_5_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */
#define PROTOCOL_DEF //protocol module enable

#define FW_VER_STR "0.0.1v"	//최초?��?��

#define BOARD_TYPE	2//JMM

#define CAN1_ENABLE
#define CAN2_ENABLE

/* CAN QUEUE MEM SIZE --------------------------------------------------------*/
#define CAN_QUEUE_SIZE_CUSTOM
#ifdef CAN_QUEUE_SIZE_CUSTOM
#define MAL_CAN_QUEUE_SIZE	32
#endif

/* UART MODULE Selection------------------------------------------------------*/
#define MAL_UART7_MODULE_ENABLED

/* UART QUEUE MEM SIZE -------------------------------------------------------*/
#define MAL_UART_MEM_CUSTOM
#ifdef MAL_UART_MEM_CUSTOM
#define MAL_UART_QUEUE_SIZE	1024
#define UART_ADDR_REGIST_SIZE  1
#endif



//MASTER CAN ID
#define MASTER_CAN_ID 0

/*************?��?��?�� RAM버퍼?�� ?��?�� ?��?��******************/

#define CAN_Q_BUFF_SIZE 	512   //  ((?��?�� 4 Byte + ?��?��?�� 8 Byte) x 512(CAN_Q_BUFF_SIZE)) x 2(rx,tx) = 12,288 Byte
// CAN 1개일 경우
#define CAN_1	0 // ?��?���? ?��?��?�� define
#define CAN_CNT 1

void HAL_CAN_RxFifo0MsgPendingCallback1(CAN_HandleTypeDef *hcan);

#include "dl_can.h"
#include "net_phd_pid.h"

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
