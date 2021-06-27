#ifndef __CONTROL_H__
#define __CONTROL_H__

/*----------------------------------------------------------------------------*
 * ����ͷ�ļ�                                                                 *
 *----------------------------------------------------------------------------*/
#include "common.h"

/*----------------------------------------------------------------------------*
 * �궨��                                                                     *
 *----------------------------------------------------------------------------*/
 
#define  Left_Limit   715 
#define  Right_Limit   515 

#define  Switch_Key_DDR     DDRA
#define  Switch_Key         PORTA
#define  Switch_Key_PLUS    PUCR_PUPAE       // ���뿪��

#define  CCD_CLK1_DDR       DDRB_DDRB0        //  CCD1..H3
#define  CCD_CLK1           PORTB_PB0        //PB0ΪCCD_CLK1 PB1ΪCCD_SI1 
#define  CCD_SI1_DDR        DDRB_DDRB1        //
#define  CCD_SI1            PORTB_PB1        //

#define  CCD_CLK2_DDR       DDRB_DDRB2        //  CCD2..H4
#define  CCD_CLK2           PORTB_PB2        //PB2ΪCCD_CLK2 PB3ΪCCD_SI2  PB67Ϊ��ʼ�߼��
#define  CCD_SI2_DDR        DDRB_DDRB3        //
#define  CCD_SI2            PORTB_PB3        //



#define  Startline1_DDR     DDRB_DDRB7        //��ʼ��
#define  Startline1         PORTB_PB7        //
#define  Startline2_DDR     DDRB_DDRB6        //
#define  Startline2         PORTB_PB6        //

#define  DIR_DDR            DDRK_DDRK0       //�����ź�
#define  DIR                PORTK_PK0 
#define  LED1_DDR           DDRK_DDRK1 
#define  LED1               PORTK_PK1 
#define  LED2_DDR           DDRK_DDRK2         // LEDָʾ��
#define  LED2               PORTK_PK2  
#define  LED3_DDR           DDRK_DDRK3        //
#define  LED3               PORTK_PK3         //
#define  LED_ON     1 
#define  LED_OFF    0 

#define  Light_Key1_DDR     DDRH_DDRH2      //��翪��
#define  Light_Key1         PTH_PTH2
#define  Light_Key2_DDR     DDRH_DDRH3
#define  Light_Key2         PTH_PTH3

#define  BUZZER_DDR         DDRM_DDRM0      //������
#define  BUZZER             PTM_PTM0
#define  BUZZER_ON     0
#define  BUZZER_OFF    1

#define  Steer_Right   455      
#define  Steer_Left    685    


/*----------------------------------------------------------------------------*
 * ȫ�ֱ���                                                                   *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * �ڲ�����ԭ��                                                               *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * �ⲿ����ԭ��                                                               *
 *----------------------------------------------------------------------------*/
extern void             SendImageData(unsigned char * ImageData);
extern void             StartIntegration(void);
extern void             StartIntegration1(void);
extern void             INT_PORT(void);
extern void             ImageCapture(unsigned char * ImageData); 
extern void             ImageCapture1(unsigned char * ImageData); 
extern void             MortorControl(void);
extern void             Show_load(void);
extern void             Show_load1(void);
extern void             Calculate_Exposure_Time(unsigned char * ccd);
extern void             Calculate_Exposure_Time1(unsigned char * ccd);
extern void             Get_Position(void);
extern void             Get_Position1(void);
extern void             Direction_Control(void);
extern void             Get_Switch_Key(void);

extern void             bianma(void);
extern void             chushihua(void);


extern unsigned char             po;
extern int             po_c;
extern unsigned char             po_old;
extern unsigned char             po1;


extern unsigned char    CCD_AD[128];
extern unsigned char    CCD_AD1[128];
extern SHORT16          Average_CCDVoltage;
extern SHORT16          Expect_Average_CCDVoltage;
extern int              Average_CCDVoltage_Erro;
extern unsigned char    Exposure_Time;
extern unsigned char    Exposure_Time1;
extern int              t;
extern int              T1;
extern int              T2;
extern int              d;
extern int              q;
extern int              k;               //����
extern int              t_min;                //�������ʱ��
extern int              t_max;                //�����ʱ��
extern int              t2;                //��ʱ
extern int              t3;                //��ʱ
extern int              s1;              //    Startline1;
extern int              s2;             //    Startline2;
extern int              panduandaochequ;
extern int               panduantingche;
extern int              j;              //����
extern int              f;              //����
extern int              j1;              //����
extern int             j2;              //����
extern int              j3;              //����
extern int              j4;              //����
extern int              dp;              //����
extern int              xs;              //����



extern UCHAR8           g_aucImageBuf[8][LED_MAX_COLUMN_NUM];
extern unsigned char    Timeflag40MS;
extern unsigned char    Timeflag20MS;
extern unsigned char Switch_Key_Value[8];
extern unsigned char    zr,yr;     //������

extern int              Speed_jichu;          //�����ٶ�
extern int              Speed_jichu1_min;          //�����ٶ�
extern int              Speed_jichu1_max;          //�����ٶ�
extern int              Speed_jichu0;          //�����ٶ�
extern int              Speed_min;          //�����ٶ�
extern float            Kp_Direction;
extern float            Kd_Direction;
extern float            Kp_Direction1;
extern float            Kd_Direction1;
unsigned char PixelAverage(unsigned char len, unsigned char *data);


#pragma CODE_SEG __NEAR_SEG NON_BANKED 
void interrupt 7 RTI_ISR(void);		  //����ӳ���ϵ
#pragma CODE_SEG DEFAULT



#endif

