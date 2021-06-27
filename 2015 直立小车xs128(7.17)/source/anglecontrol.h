#ifndef ANGLECONTROL_H
#define ANGLECONTROL_H

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

/*----------------------------------------------------------------------------*
 * �궨��                                                                     *
 *----------------------------------------------------------------------------*/
#define  Switch_Key_DDR     DDRE
#define  Switch_Key         PORTE
#define  Switch_Key_PLUS    PUCR_PUPEE       // ���뿪��
#define  gPWMMid            2000             //�����ֵ
#define  gPWMOffset         2000             //�����Ŵ�

/*----------------------------------------------------------------------------*
 * �ⲿ����ԭ��                                                               *
 *----------------------------------------------------------------------------*/
 
extern int   lCg;            //��������ƫ
extern int   lCz;            //���ٶȴ�������ƫ

extern float gPWMOutA;                       //ֱ�����
extern float gRealAngle;                     //�����Ǽ���õ��ĽǶ�
extern float lZangle;                        //Z�����ĽǶ�

extern float lGoValue[3];                    //��������ʷֵ
extern float lAzValue[3];                    //���ٶ�Z��ʷֵ

extern float lGv;                            //�ɼ����������Ǿ�ֵ��
extern float lZv;                            //�ɼ����ļ��ٶ�Z��ֵ��

extern int gKpa;             //   ֱ��p   
extern int gKda;            //    ֱ��d
extern int gKia;            //    ֱ��i


extern unsigned char STOP;                  //ͣ�����
extern int run_dalay ;

 

extern void GetAngleFun(void);
extern void AngleControlFun(void);
extern void DirectionControlFun(void);
extern void PWMOutputFun(void);

#endif //ANGLECONTROL_H