#ifndef ANGLECONTROL_H
#define ANGLECONTROL_H

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

/*----------------------------------------------------------------------------*
 * 宏定义                                                                     *
 *----------------------------------------------------------------------------*/
#define  Switch_Key_DDR     DDRE
#define  Switch_Key         PORTE
#define  Switch_Key_PLUS    PUCR_PUPEE       // 拨码开关
#define  gPWMMid            2000             //电机中值
#define  gPWMOffset         2000             //比例放大

/*----------------------------------------------------------------------------*
 * 外部函数原型                                                               *
 *----------------------------------------------------------------------------*/
 
extern int   lCg;            //陀螺仪零偏
extern int   lCz;            //加速度传感器零偏

extern float gPWMOutA;                       //直立输出
extern float gRealAngle;                     //陀螺仪计算得到的角度
extern float lZangle;                        //Z轴计算的角度

extern float lGoValue[3];                    //陀螺仪历史值
extern float lAzValue[3];                    //加速度Z历史值

extern float lGv;                            //采集到的陀螺仪均值量
extern float lZv;                            //采集到的加速度Z均值量

extern int gKpa;             //   直立p   
extern int gKda;            //    直立d
extern int gKia;            //    直立i


extern unsigned char STOP;                  //停车标记
extern int run_dalay ;

 

extern void GetAngleFun(void);
extern void AngleControlFun(void);
extern void DirectionControlFun(void);
extern void PWMOutputFun(void);

#endif //ANGLECONTROL_H