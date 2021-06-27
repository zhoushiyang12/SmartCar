#ifndef __CONTROL_H__
#define __CONTROL_H__

/*----------------------------------------------------------------------------*
 * 包含头文件                                                                 *
 *----------------------------------------------------------------------------*/
#include "common.h"

/*----------------------------------------------------------------------------*
 * 宏定义                                                                     *
 *----------------------------------------------------------------------------*/
#define  Switch_Key_DDR     DDRE
#define  Switch_Key_1       PORTE_PE0
#define  Switch_Key_2       PORTE_PE1
#define  Switch_Key_3       PORTE_PE2
#define  Switch_Key_4       PORTE_PE3
#define  Switch_Key_5       PORTA_PA0
#define  Switch_Key_6       PORTA_PA1
#define  Switch_Key_7       PORTA_PA2
#define  Switch_Key_8       PORTA_PA3
#define  Switch_Key         PORTE
#define  Switch_Key_PLUS    PUCR_PUPEE       // 拨码开关
#define  Switch_Key_PLUS_A    PUCR_PUPAE       // 拨码开关

#define  CCD_CLK2_DDR       DDRA_DDRA7        //  CCD
#define  CCD_CLK2           PORTA_PA7        //
#define  CCD_SI2_DDR        DDRA_DDRA6        //
#define  CCD_SI2            PORTA_PA6        //
#define  CCD_CLK1_DDR       DDRA_DDRA5        //  CCD
#define  CCD_CLK1           PORTA_PA5        //
#define  CCD_SI1_DDR        DDRA_DDRA4        //
#define  CCD_SI1            PORTA_PA4        //
#define  Black_Check1_DDR        DDRK_DDRK0        //
#define  Black_Check1            PORTK_PK0        //
#define  Black_Check2_DDR        DDRK_DDRK1        //
#define  Black_Check2            PORTK_PK1        //

#define  Startline1_DDR     DDRM_DDRM6        //扩展接口 起始线
#define  Startline1         PTM_PTM6        //
#define  Startline2_DDR     DDRM_DDRM7        //
#define  Startline2         PTM_PTM7        //

#define  DIRA_DDR            DDRT_DDRT0       //电机A方向信号
#define  DIRA                PTT_PTT0 
#define  DIRB_DDR            DDRT_DDRT1       //电机B方向信号
#define  DIRB                PTT_PTT1 
#define  REAB_DDR            DDRT_DDRT2       //REAB信号
#define  REAB                PTT_PTT2 

#define  SUDB_DDR            DDRB        // PB口做电机B的计数
#define  SUDB                PORTB        //


#define  LED3_DDR           DDRK_DDRK3        //
#define  LED3               PORTK_PK3         //
#define  LED_ON             1 
#define  LED_OFF            0 

#define  Light_Key1_DDR     DDRH_DDRH2      //光电开关
#define  Light_Key1         PTH_PTH2
#define  Light_Key2_DDR     DDRH_DDRH3
#define  Light_Key2         PTH_PTH3

#define  BUZZER_DDR         DDRK_DDRK7      //蜂鸣器
#define  BUZZER             PORTK_PK7
#define  BUZZER_ON          0
#define  BUZZER_OFF         1

#define  MORTOR_OUTA        PWMDTY01         //电机A
#define  MORTOR_OUTB        PWMDTY23         //电机B


#define  Steer_Right   455      
#define  Steer_Left    685    


/*----------------------------------------------------------------------------*
 * 全局变量                                                                   *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * 内部函数原型                                                               *
 *----------------------------------------------------------------------------*/
 
 
 
 #define Delay250ns() \
    { __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
    }
#define Delay1us() \
    { __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
    }
    
    
    
    

/*----------------------------------------------------------------------------*
 * 外部函数原型                                                               *
 *----------------------------------------------------------------------------*/
extern void             SendImageData(unsigned char * ImageData);
extern void             StartIntegration(void);
extern void             INT_PORT(void);
extern void             ImageCapture(unsigned char * ImageData); 
extern void             ImageCapture1(unsigned char * ImageData); 
extern void             SpeedControl(void);
extern void             MortorControl(void);
extern void             Show_load(void);
extern void             Calculate_Exposure_Time(void);
extern void             Get_Position(void);
extern void             Get_Position1(void);
extern void             Direction_Control(void);
extern void             Get_Switch_Key(void);
extern void             Switch_Choose(void);
extern void             ReadSpeed(void);
extern void             delay_1s(int i);


extern unsigned char    CCD_AD[128];
extern unsigned char    CCD_AD1[128];
extern SHORT16          Average_CCDVoltage;
extern SHORT16          Expect_Average_CCDVoltage;
extern int              Average_CCDVoltage_Erro;
extern unsigned char    Exposure_Time;
extern int              t;


extern int              direction_s;                 //方向开关
extern int              speed_s;                   //速度开关
extern unsigned char           black_l;                //停车标记
extern unsigned char           black_r;                //停车标记
extern unsigned char           black_l_old;                //停车标记
extern unsigned char           black_r_old;                //停车标记

extern int              zhijiao;
extern int              quanhei;


extern int              Speed_Want ;

extern UCHAR8           g_aucImageBuf[8][LED_MAX_COLUMN_NUM];
extern unsigned char    Timeflag40MS;
extern unsigned char    Timeflag20MS;
extern float            Speed_PWM;                //速度输出PWM
#pragma CODE_SEG __NEAR_SEG NON_BANKED 
void interrupt 7 RTI_ISR(void);		  //函数映射关系
#pragma CODE_SEG DEFAULT



#endif

