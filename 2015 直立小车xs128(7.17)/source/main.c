/******************************************************************************
 ******************************************************************************
  文 件 名   : main.c
  版 本 号   : v1.0
  作    者   : Guokaiyi
  生成日期   : 2012-11-10
  最近修改   : 
  功能描述   : OLED演示例程
               说明: 
               ----------------------------------------------------------------
               G    电源地
               VCC  接5V或3.3v电源
               D0   PORTA_PA0 宏为 LED_SCL
               D1   PORTA_PA1 宏为 LED_SDA
               RST  PORTA_PA2 宏为 LED_RST
               DC   PORTA_PA3 宏为 LED_DC 
               CS   可以不接，已经默认选中                     
               ----------------------------------------------------------------
  修改历史   :
  1.日    期   : 2012-11-10
    作    者   : Guokaiyi
    修改内容   : 创建文件
    
    


******************************************************************************/

/*----------------------------------------------------------------------------*
 * 包含头文件                                                                 *
 *----------------------------------------------------------------------------*/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include<string.h>
#include"common.h"
#include"system_funtion.h"
#include"oled.h"
#include"control.h"
#include "anglecontrol.h"

/*----------------------------------------------------------------------------*
 * 宏定义                                                                     *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * 全局变量                                                                   *
 *----------------------------------------------------------------------------*/
 

//此部分内存很大，使用时请按需要调整
//UCHAR8 g_aucImageBuf[8][LED_MAX_COLUMN_NUM];


/*----------------------------------------------------------------------------*
 * 内部函数原型                                                               *
 *----------------------------------------------------------------------------*/
VOID MAIN_Init(VOID);
VOID MAIN_OLED_Display(VOID);

/*----------------------------------------------------------------------------*
 * 外部函数原型                                                               *
 *----------------------------------------------------------------------------*/



extern unsigned char STOP;                  //停车标记



void main(void) 
{
    unsigned char TimeFlag20ms_A=1;
    unsigned char TimeFlag20ms_B=1;
    int run_delays=50;
    int go=0;
    int light_off=0;
    int wait=1;
    int stophere=0;
    int go_delay=-10;
    int start_speed=0;
    float maxra=0;
    int ra_delay=50;
    DisableInterrupts;
    MAIN_Init();
    
    PORTK_PK7 = 1;   //蜂鸣器
    MAIN_OLED_Display();

    EnableInterrupts;
    
    Switch_Choose();
    
    start_speed = Speed_Want;
    Speed_Want=0;
        
    for (;;)
    {
         /* */if(STOP!=0)
        {
          DisableInterrupts;
          LED0=1;
          LED1=1;
          LED2=1;
          LED3=0; 
          MORTOR_OUTA=gPWMMid;
          MORTOR_OUTB=gPWMMid;
          break;
         }  
      
       if(t==0 && TimeFlag20ms_A == 1)
       {
        TimeFlag20ms_A =0;
        
        if(go_delay>0) go_delay--;
        
        if(Startline1 == 1 && Startline2 == 1){            //起始线
         
           light_off=1;
           if( run_delays==0 && wait==1){
               go=1;
               go_delay=100;
               wait=0;  
               
             if(go==1){
               Speed_Want=  start_speed;
               
             }    
           }
        }else{
           light_off=0;
          }
        
        if(Startline1 == 0 && Startline2 == 0 && go_delay==0 ){            //起始线
            stophere = 3;
             PORTK_PK7 = 0;

        } else
               PORTK_PK7 = 1;
        

      
      
        DisableInterrupts; 
        ImageCapture(CCD_AD);
        EnableInterrupts; 
        
      //  Calculate_Exposure_Time();
               
        Get_Position();
        Show_load();
        
        LED3= ~LED3;
        Timeflag40MS++;
        if(go==1 && ra_delay!=0){
          
          ra_delay--;
        }
        
        if(ra_delay==0){
          
         if( maxra<gRealAngle){
          
          maxra= gRealAngle;
         }
        }
       
       }
       if(t==18 && TimeFlag20ms_B == 1)
       {
        TimeFlag20ms_B=0;

          if(run_dalay==0) {
          
            if(run_delays==0&&speed_s==1){
               if((stophere-light_off)==2){
                  Speed_Want=0;
                }
               SpeedControl();                 //速度控制
              // PORTK_PK7 = 0;
            }
             else
            {
              if(run_delays!=0)
                 run_delays--;
            }
          }
      
           if(run_delays==0&&direction_s==1) {
              Direction_Control();            //方向控制
            }
          
       }
       
        if(Timeflag40MS >=3)
        {
          LED1= ~LED1;
      //  SendImageData(CCD_AD);
          LED_PrintImage((UCHAR8*)g_aucImageBuf,0,8, LED_MAX_COLUMN_NUM);
          LED_PrintShort(80,3,(SHORT16) lGv);
          LED_PrintShort(80,5,(SHORT16) lZv);
         LED_PrintShort(80,7,(SHORT16) maxra);
      //    LED_PrintShort(80,7,(SHORT16) Speed_PWM);  

          Timeflag40MS = 0;
        } 
               
       if(t>=20)
       {
        TimeFlag20ms_A = 1;
        TimeFlag20ms_B = 1;
        t=0;
       }
      
    } 
    for(;;);  
    
}

VOID MAIN_Init(VOID)
{
    SYSTEM_PLL_Init();
    Init_POTH_Int();
    INT_PORT();
    INIT_AD();              // 0 CCD_AD2 1 CCD_AD1 2 ACCE加速度计 3-5 陀螺仪
    LED_Init();
    Init_RTI();
    Init_PulseACC();
    init_pwm();
    INIT_SCI0();
    Get_Switch_Key();
}

VOID MAIN_OLED_Display(VOID)
{
    

    LED_P14x16Str(3, 0, (UCHAR8*)"周仕扬陈涛刘剑峰");
    SYSTEM_TIME_Delay(2000);
    LED_Fill(0x00); 
    //清空图片缓存
   // (VOID)memset(g_aucImageBuf, 0x00, 32 * LED_MAX_COLUMN_NUM);  
    LED_Fill(0x00); //黑屏
    SYSTEM_TIME_Delay(1000);
    Show_Welcome_Picture();
    SYSTEM_TIME_Delay(2000);
    LED_Fill(0x00); 
    LED_P14x16Str(0, 1, (UCHAR8*)"左边");    
    LED_P14x16Str(0, 2, (UCHAR8*)"右边");
    LED_P14x16Str(0, 3, (UCHAR8*)"中线");   
    LED_P8x16Str(60, 1,(UCHAR8*)"lG") ;
    LED_P8x16Str(60, 2,(UCHAR8*)"lZ") ;
    LED_P8x16Str(60, 3,(UCHAR8*)"RA") ;
}


