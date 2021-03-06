/******************************************************************************

          版权所有 (C), 2011-2012, 信意电子科技(http://xydz123.taobao.com/)

 ******************************************************************************
  文 件 名   : system_funtion.h
  版 本 号   : v1.0
  作    者   : Guokaiyi
  生成日期   : 2012-11-12
  最近修改   : 
  功能描述   : system_funtion.c 的头文件

  修改历史   :
  1.日    期   : 2012-11-12
    作    者   : Guokaiyi
    修改内容   : 创建文件

******************************************************************************/
#ifndef  __SYSTEM_FUNTION_H__
#define  __SYSTEM_FUNTION_H__

/*----------------------------------------------------------------------------*
 * 包含头文件                                                                 *
 *----------------------------------------------------------------------------*/
#include "common.h"

/*----------------------------------------------------------------------------*
 * 宏定义                                                                     *
 *----------------------------------------------------------------------------*/
#define SYSTEM_BUS_CLOCK        80000000    //总线频率
#define SYSTEM_OSC_CLOCK        16000000    //晶振频率
#define INTERRUPT_TIME          1          //PIT中断时间  毫秒
#define SYSTEM_BAUD               115200    //波特率

/*----------------------------------------------------------------------------*
 * 全局变量                                                                   *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * 内部函数原型                                                               *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * 外部函数原型                                                               *
 *----------------------------------------------------------------------------*/
extern VOID     SYSTEM_PLL_Init(VOID);
extern void     Init_RTI(void);
extern void     Init_PulseACC(void);
extern void     init_pwm(void);
extern void     INT_PORT(void);
extern void     INIT_SCI0(void);
extern void     SCI0_send(unsigned char data);  
extern VOID     INIT_AD(VOID);
extern VOID     Init_POTJ_Int(void);
extern UCHAR8   AD_capture(UCHAR8);
extern VOID     SYSTEM_DFLASH_Init(void);
extern VOID     SYSTEM_DFLASH_Erase(USHORT16 usAddress);
extern VOID     SYSTEM_DFLASH_Write(USHORT16 usAddress, USHORT16 *pusDataBuf);
extern VOID     SYSTEM_DFLASH_Read(USHORT16 usAddress, USHORT16 *pusDataBuf); 
extern VOID     SYSTEM_TIME_Delay(USHORT16 usTime);

#endif

