/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : LPF.c
  * @brief          : lowpass filter 
  * @author         : GrassFan Wang
  * @date           : 2025/12/28
  * @version        : v1.0
  ******************************************************************************
  * @attention      : To be perfected
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "LPF.h"
#include "string.h"
#include "user_lib.h"

/**
  * @brief ��ʼ��һ�׵�ͨ�˲���.
  * @param LPF: һ�׵�ͨ�˲����ṹ��.
  * @param Alpha: �˲���ϵ��.
  * @param Frame_Period: ��������.
  * @retval ��.
  */
void LowPassFilter1p_Init(LowPassFilter1p_Info_TypeDef *LPF,float Alpha)
{
  LPF->Alpha = Alpha;
  LPF->Input = 0;
  LPF->Output = 0;
}

/**
  * @brief ����һ�׵�ͨ�˲�������.
  * @param Input: ��ǰ����.
  * @retval �˲����ֵ.
  */
float LowPassFilter1p_Update(LowPassFilter1p_Info_TypeDef *LPF,float Input)
{
  LPF->Input = Input;

  if(LPF->Initialized == false)
  {
    LPF->Output = LPF->Input;//��һ�ν�����º��� ��������������
    LPF->Initialized = true;
  }

	/*�˲���ϵ�� = Alhpa 0< Alhpa <1 ���˲�ϵ��ԽС���˲�����Խƽ�ȣ������ͺ��Ը���
                                   ���˲�ϵ��Խ���˲�����Խ�ӽ�ʵ��ֵ���ͺ���С�������˲����߸��� */
	
	//�˲�ֵ = Alhpa * ��һ����� + ��1 - Alhpa)*�������	
  LPF->Output = LPF->Alpha * LPF->Output +(1.f - LPF->Alpha) * LPF->Input;
	
  return LPF->Output;
}

/**
  * @brief ��ʼ�����׵�ͨ�˲���.
  * @param Alpha[3]: �˲���ϵ��[3].
  * @retval ��.
  */
void LowPassFilter2p_Init(LowPassFilter2p_Info_TypeDef *LPF,float Alpha[3])
{
  memcpy(LPF->Alpha,Alpha,sizeof(LPF->Alpha));
  LPF->Input = 0;
  memset(LPF->Output,0,sizeof(LPF->Output));
}

/**
  * @brief ���¶��׵�ͨ�˲�������.
  * @param Input: ��ǰ����.
  * @retval �˲����ֵ.
  */
float LowPassFilter2p_Update(LowPassFilter2p_Info_TypeDef *LPF,float Input)
{
	LPF->Input = Input;
  
  if(LPF->Initialized == false)
  {
    LPF->Output[0] = LPF->Input;
    LPF->Output[1] = LPF->Input;
    LPF->Output[2] = LPF->Input;
    LPF->Initialized = true;
  }
  
	LPF->Output[0] = LPF->Output[1];
	LPF->Output[1] = LPF->Output[2];
  LPF->Output[2] = LPF->Alpha[0] * LPF->Output[1] + LPF->Alpha[1] * LPF->Output[0] + LPF->Alpha[2] * LPF->Input;

	return LPF->Output[2];
}
//------------------------------------------------------------------------------

