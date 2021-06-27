/******************************************************************************

          ��Ȩ���� (C), 2011-2012, ������ӿƼ�(http://xydz123.taobao.com/)

 ******************************************************************************
  �� �� ��   : system_funtion.h
  �� �� ��   : v1.0
  ��    ��   : Guokaiyi
  ��������   : 2012-11-12
  ����޸�   : 
  ��������   : system_funtion.c ��ͷ�ļ�

  �޸���ʷ   :
  1.��    ��   : 2012-11-12
    ��    ��   : Guokaiyi
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef  __SYSTEM_FUNTION_H__
#define  __SYSTEM_FUNTION_H__

/*----------------------------------------------------------------------------*
 * ����ͷ�ļ�                                                                 *
 *----------------------------------------------------------------------------*/
#include "common.h"

/*----------------------------------------------------------------------------*
 * �궨��                                                                     *
 *----------------------------------------------------------------------------*/
#define SYSTEM_BUS_CLOCK        80000000    //����Ƶ��
#define SYSTEM_OSC_CLOCK        16000000    //����Ƶ��
#define INTERRUPT_TIME          1          //PIT�ж�ʱ��  ����
#define SYSTEM_BAUD               115200    //������

/*----------------------------------------------------------------------------*
 * ȫ�ֱ���                                                                   *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * �ڲ�����ԭ��                                                               *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * �ⲿ����ԭ��                                                               *
 *----------------------------------------------------------------------------*/
extern VOID     SYSTEM_PLL_Init(VOID);
extern void     Init_RTI(void);
extern void     Init_PulseACC(void);
extern void     init_pwm(void);
extern void     INT_PORT(void);
extern void     INIT_SCI0(void);
extern void     SCI0_send(unsigned char data);  
extern VOID     INIT_AD(VOID);
extern unsigned int   AD_capture(UCHAR8);
extern VOID     SYSTEM_DFLASH_Init(void);
extern VOID     SYSTEM_DFLASH_Erase(USHORT16 usAddress);
extern VOID     SYSTEM_DFLASH_Write(USHORT16 usAddress, USHORT16 *pusDataBuf);
extern VOID     SYSTEM_DFLASH_Read(USHORT16 usAddress, USHORT16 *pusDataBuf); 
extern VOID     SYSTEM_TIME_Delay(USHORT16 usTime);

extern void     Init_POTH_Int(void);


#endif

