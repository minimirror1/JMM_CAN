/*
 * filter_manager.c
 *
 *  Created on: Feb 8, 2022
 *      Author: shin
 */


#include "main.h"
#include "math.h"
#include "filter_manager.h"

#include "non_stop_delay_main.h"
#include "can2_com_manager.h"

float filterMap[15] = {
		1.0f,
		1.0f,
		0.95f,
		0.9f,
		0.85f,
		0.8f,
		0.7f,
		0.6f,
		0.32f,
		0.16,
		0.08f,
		0.04f,
		0.02f,
		0.01f,
		0.005f
};

filter_TypeDef filter[FILTER_NUM] = {0,};



void filter_data_reg(MotionData_TypeDef* pMotion)
{
	for (int i = 0; i < FILTER_NUM; i++) {
		filter[i].LPF_Beta = 1;
		filter[i].SmoothData = 0;
		filter[i].inData = &pMotion->data[i].rawData;
		filter[i].outData = &pMotion->data[i].filterData;

		filter[i].limitMin = &pMotion->setting[i].limitMin;
		filter[i].limitMax= &pMotion->setting[i].limitMax;

		filter[i].mapLow = &pMotion->setting[i].limitMin;
		filter[i].mapHigh= &pMotion->setting[i].limitMax;
		filter[i].reverse= &pMotion->setting[i].reverse;

		filter[i].filterVar =&pMotion->setting[i].filter;


	}
}


void filter_init(void)
{
/*	for(int i = 0; i < 8; i++)
	{
		filter[i].LPF_Beta = 1;
		filter[i].SmoothData = 0;
		filter[i].RawData = &extenderPacket.adc[i];
	}

	for(int i = 0; i < MAX_AXLE_INFO;i++)
	{
		com_axle.axleInfo[i].setPage.max = 4095;
		com_axle.axleInfo[i].setPage.min = 0;
		com_axle.axleInfo[i].setPage.range = 4095;
	}*/
}


int64_t map(int64_t x, int64_t in_min, int64_t in_max, int64_t out_min, int64_t out_max)
{
//	if(in_min <= in_max)
//	{
//		if((x < in_min)||( in_max < x))
//		{
//			x = (in_min+in_max) /2;
//		}
//	}
//	else
//	{
//		if((x < in_max)||( in_min < x))
//		{
//			x = (in_min+in_max) /2;
//		}
//	}
	int64_t temp = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
//	if(temp > 0)
//		temp--;
	 return temp;
}


void filter_calc(int i, float *SmoothData, int *filterData, int RawData, float LPF_Beta)
{

	if (RawData >= 4095)
	{
		RawData = 4095;
	}

	//mapping
	if (*filter[i].reverse == 1) {
		RawData = map(RawData,
			0,
			4095,
			4095,
			0);
	}

	//Limitations of data cut
	if (RawData <= *filter[i].limitMin)
		RawData = *filter[i].limitMin;
	else if (RawData >= *filter[i].limitMax)
		RawData = *filter[i].limitMax;




	RawData = map(RawData,
					*filter[i].limitMin,
					*filter[i].limitMax,
					0,
					4095);
#if 0
	//Limitations of data cut
	if(RawData <=*filter[i].limitMin)
		RawData =*filter[i].limitMin;
	else if(RawData >=*filter[i].limitMax)
		RawData =*filter[i].limitMax;

	//mapping
	if(*filter[i].reverse == 0)
		RawData = map(
			RawData,
			*filter[i].limitMin,
			*filter[i].limitMax,
			0,
			4095);
	else
		RawData = map(
					RawData,
					*filter[i].limitMin,
					*filter[i].limitMax,
					4095,
					0);
#endif


	int32_t errorVal = *SmoothData - RawData;

	float reflection = errorVal * LPF_Beta;

	*SmoothData = *SmoothData - reflection;

	if (*SmoothData >= 4095)
		*SmoothData = 4095;

	*filterData =(int)*SmoothData;

/*
	if(*filter[i].reverse == 0)
	*filterData = map(
			*SmoothData,
			0,
			4095,
			0,
			4095);
	else
		*filterData = map(
					*SmoothData,
					0,
					4095,
					4095,
					0);
*/


/*	*SmoothData = *SmoothData - (LPF_Beta * (*SmoothData - RawData));
	*filterData = round(*SmoothData);*/
}

#ifdef FIXED_POINT
void filter_calc_p()
{
	int RawData;
	signed long SmoothDataINT;
	signed long SmoothDataFP;
	int Beta = 4; // Length of the filter < 16

	void main (void){
	    while(1){
	       // Function that brings Fresh Data into RawData
	       RawData = GetRawData();
	       RawData <<= FP_Shift; // Shift to fixed point
	       SmoothDataFP = (SmoothDataFP<< Beta)-SmoothDataFP;
	       SmoothDataFP += RawData;
	       SmoothDataFP >>= Beta;
	       // Don't do the fllowing shift if you want to do further
	       // calculations in fixed-point using SmoothData
	       SmoothDataINT = SmoothDataFP>> FP_Shift;
	    }
	}
}
#endif

void filter_manager(void)
{
	static uint32_t t_filter = 0;

	if (MAL_NonStopDelay(&t_filter, 20) == 1)
	{
		for (int i = 0; i < FILTER_NUM; i++)
		{
			filter_calc(i,
					&filter[i].SmoothData,
					filter[i].outData,
					*filter[i].inData,
					filterMap[*filter[i].filterVar]);
					//filterMap[10]);
		}
	}

}
