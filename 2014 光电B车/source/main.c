/******************************************************************************

    if(Switch_Key_Value[7]==1){
     xs=200; 
    Exposure_Time1 = 16;
    Speed_jichu = 650;                     //ֱ��
    Speed_jichu1_max = 550;                    //���
    Speed_jichu1_min = 500;                    //���
    Speed_min = 450;                       //��С�ٶ�
     Kp_Direction = 2.3;         //���
     Kd_Direction = 10;
     Kp_Direction1 = 2.3;      //ֱ��
     Kd_Direction1 = 10;

     t_min=12;
     t_max=35;
    }


 ******************************************************************************
  �� �� ��   : main.c
  �� �� ��   : v1.0
  ��    ��   : Guokaiyi
  ��������   : 2012-11-10
  ����޸�   : 
  ��������   : OLED��ʾ����
               ˵��: 
               ----------------------------------------------------------------
               G    ��Դ��
               VCC  ��5V��3.3v��Դ
               D0   PORTA_PA0 ��Ϊ LED_SCL
               D1   PORTA_PA1 ��Ϊ LED_SDA
               RST  PORTA_PA2 ��Ϊ LED_RST
               DC   PORTA_PA3 ��Ϊ LED_DC 
               CS   ���Բ��ӣ��Ѿ�Ĭ��ѡ��                     
               ----------------------------------------------------------------
  �޸���ʷ   :
  1.��    ��   : 2012-11-10
    ��    ��   : Guokaiyi
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------------------------------------*
 * ����ͷ�ļ�                                                                 *
 *----------------------------------------------------------------------------*/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include<string.h>
#include"common.h"
#include"system_funtion.h"
#include"oled.h"
#include"control.h"

/*----------------------------------------------------------------------------*
 * �궨��                                                                     *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * ȫ�ֱ���                                                                   *
 *----------------------------------------------------------------------------*/
 

//�˲����ڴ�ܴ�ʹ��ʱ�밴��Ҫ����
//UCHAR8 g_aucImageBuf[8][LED_MAX_COLUMN_NUM];
int b=0;    //  ����
int p=0;    //  ����
int a=3000;    //  ����
int x=0;    //  ����
int jishu=100;    //  ����
int jishu1=100;    //  ����


/*----------------------------------------------------------------------------*
 * �ڲ�����ԭ��                                                               *
 *----------------------------------------------------------------------------*/
VOID MAIN_Init(VOID);
VOID MAIN_OLED_Display(VOID);


/*----------------------------------------------------------------------------*
 * �ⲿ����ԭ��                                                               *
 *----------------------------------------------------------------------------*/


void main(void) 
{
    unsigned char TimeFlag20ms_A=0;
    unsigned char TimeFlag20ms_B=0;
    DisableInterrupts;
    MAIN_Init();
  
    MAIN_OLED_Display();
    EnableInterrupts;
        

    Get_Switch_Key();
    bianma();
    
    chushihua();
    

    for (;;)
    { 
       if(t==0 && TimeFlag20ms_A == 1)
       {
        
        ImageCapture(CCD_AD);
        ImageCapture1(CCD_AD1);
        Calculate_Exposure_Time(CCD_AD);
        Calculate_Exposure_Time1(CCD_AD1);
        Get_Position();
        LED3= 1;
        Get_Position1();
        
        Show_load();
        Show_load1();
        Timeflag40MS++;     


       if(jishu<100)
       jishu++;
       if(jishu1<100)
       jishu1++;
       if(t2<1000)
       t2++;
       if(t3<64)
       t3++;
         if(j2<200)
        j2++;
       if(j3<255)
        j3++;
       if(T2<1000){
        T2++;
        }
       if(T2==250){
        T1=1;
        }


       if(s1==1&&s2==1){T1=1;}    //��ʼ��
       if(s1==1){
         jishu=0;
       }
       if(jishu<5&&s2==1){
     
         T1=1;
        }
       if(s2==1){
         jishu1=0;
       }
       if(jishu1<5&&s1==1){
         T1=1;
        }
        
        
        TimeFlag20ms_A =0;
       }
       if(t==12 && TimeFlag20ms_B == 1)
       {
        TimeFlag20ms_B=0;
        
        MortorControl();
       if(panduandaochequ==1){
          
        if(zr==1) { PWMDTY45 = Right_Limit-10;} 
        if(yr==1) { PWMDTY45 = Left_Limit+10; }
        if(zr==0&&yr==0) {
        Direction_Control();
        }
        } 
        else{
         Direction_Control();
        }      
        
       } 
        if(Timeflag40MS >=3)                    //60ms????
        {
          LED1= ~LED1;
        if(b==1) 
        SendImageData(CCD_AD1);
        if(p==1) 
        SendImageData(CCD_AD);
          
          LED_PrintImage((UCHAR8*)g_aucImageBuf,0,10, LED_MAX_COLUMN_NUM);
          Timeflag40MS = 0;
        }
               
       if(t>=15)
       {
        TimeFlag20ms_A = 1;
        TimeFlag20ms_B = 1;
        t=0;
       }
      
    }
    for(;;) {
    }
}

VOID MAIN_Init(VOID)
{
    SYSTEM_PLL_Init();
    Init_POTJ_Int();
    INT_PORT();
    LED_Init();
    Init_RTI();
    Init_PulseACC();
    init_pwm();
    INIT_SCI0();
    INIT_AD();
    
}

VOID MAIN_OLED_Display(VOID)
{
    

    LED_P14x16Str(15, 0, (UCHAR8*)"������ ����");
    SYSTEM_TIME_Delay(2000);
   // LED_Fill(0x00); 
    //���ͼƬ����
    
   // (VOID)memset(g_aucImageBuf, 0x00, 32 * LED_MAX_COLUMN_NUM);  
  // LED_Fill(0x00); //����
   // SYSTEM_TIME_Delay(1000);
  //  Show_Welcome_Picture();
    SYSTEM_TIME_Delay(2000);
    LED_Fill(0x00); 
    LED_P14x16Str(0, 1, (UCHAR8*)"���Ե");    
    LED_P14x16Str(0, 2, (UCHAR8*)"�ұ�Ե");
    LED_P14x16Str(0, 3, (UCHAR8*)"����λ��");   
    //LED_P14x16Str(0, 3, (UCHAR8*)"��ǰλ��");   
   
}

