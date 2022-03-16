/*
 * filter_manager.h
 *
 *  Created on: Feb 8, 2022
 *      Author: shin
 */

#ifndef FILTER_MANAGER_INC_FILTER_MANAGER_H_
#define FILTER_MANAGER_INC_FILTER_MANAGER_H_

#include "can2_com_manager.h"

#define FILTER_NUM	SLIDE_CNT



//#define FIXED_POINT
#define FLOATING_POINT

#ifdef FLOATING_POINT
typedef struct{
		int *inData;
		int *outData;
		float SmoothData;
		uint32_t filterData;


		uint16_t *mapLow;
		uint16_t *mapHigh;
		uint16_t *limitMin;
		uint16_t *limitMax;

		uint8_t *reverse;

		uint16_t *filterVar;
		float LPF_Beta; // 0<ß<1
}filter_TypeDef;
#endif

void filter_calc(int i, float *SmoothData, int *filterData, int RawData, float LPF_Beta);
void filter_data_reg(MotionData_TypeDef* pMotion);
void filter_manager(void);
void filter_init(void);
int64_t map(int64_t x, int64_t in_min, int64_t in_max, int64_t out_min, int64_t out_max);

#endif /* FILTER_MANAGER_INC_FILTER_MANAGER_H_ */
