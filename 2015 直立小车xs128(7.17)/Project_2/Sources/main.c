/******************************************************************************
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
#include "anglecontrol.h"

/*----------------------------------------------------------------------------*
 * �궨��                                                                     *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * ȫ�ֱ���                                                                   *
 *----------------------------------------------------------------------------*/
 

//�˲����ڴ�ܴ�ʹ��ʱ�밴��Ҫ����
//UCHAR8 g_aucImageBuf[8][LED_MAX_COLUMN_NUM];


/*----------------------------------------------------------------------------*
 * �ڲ�����ԭ��                                                               *
 *----------------------------------------------------------------------------*/
VOID MAIN_Init(VOID);
VOID MAIN_OLED_Display(VOID);

/*----------------------------------------------------------------------------*
 * �ⲿ����ԭ��                                                               *
 *----------------------------------------------------------------------------*/



extern unsigned char STOP;                  //ͣ�����
extern unsigned char STOP_s;                  //ͣ����� ����



void main(void) 
{
    unsigned char TimeFlag20ms_A=1;
    unsigned char TimeFlag20ms_B=1;
    unsigned char TimeFlag20ms_C=1;
    unsigned char TimeFlag20ms_D=1;
    unsigned char TimeFlag20ms_E=1;
    int run_delays=50;
    int go=0;
    int light_off=0;
    int light_count=-1;
    int wait=1;
    int stophere=0;
    int go_delay=-10;        // ͣ����ʱ
    int start_speed=0;                //����
    float maxra=0;
    int ra_delay=50;
    int j=0;                 //ͣ������
    
    DisableInterrupts;
    MAIN_Init();
    
    PORTK_PK7 = 1;   //������
    MAIN_OLED_Display();

    Switch_Choose();
    
    start_speed = Speed_Want;
    Speed_Want=0;
    
    EnableInterrupts;
   
    for (;;)
    {
       if(t==0 && TimeFlag20ms_A == 1)
       {
        TimeFlag20ms_A =0;
        DisableInterrupts; 
        ImageCapture(CCD_AD);
        EnableInterrupts; 
        
      //  Calculate_Exposure_Time();
        
        LED3= ~LED3;
        Timeflag40MS++;
       }
       
       if(t==2 && TimeFlag20ms_D == 1)
       {
       TimeFlag20ms_D = 0 ;
       
        DisableInterrupts; 
        ImageCapture1(CCD_AD1);
        EnableInterrupts; 
       
       

       }
       
       if(t==4 && TimeFlag20ms_C == 1)
       {
       TimeFlag20ms_C = 0;
        Get_Position();
       // Get_Position1();

          
       }
       
       if(t==6 && TimeFlag20ms_E == 1)
       {
         TimeFlag20ms_E = 0;
         Show_load();       
       }

       if(t==17 && TimeFlag20ms_B == 1)
       {
        TimeFlag20ms_B=0;
              
        if(go_delay>0) go_delay--;
        
        if(Startline1 == 1 && Startline2 == 1){            //��ʼ��
         

           if( run_delays==0 && wait==1&&light_off==50){
               go=1;
               go_delay=100;
               wait=0;  
               
             
               Speed_Want=  start_speed;
               
           
               } 
              if(light_off<50) 
                   light_off++; 
              
        }else{
           light_off=0;
          }
        
        if(Startline1 == 0 && Startline2 == 0 && go_delay==0){            //��ʼ��
            
             if(j>=7) {             
               light_count=17;
               PORTK_PK7 = 0;   
                       }

             if(j<17)   j++;
        } 
        else 
        {  
           if(j!=0)
             j-- ;
           
             PORTK_PK7 = 1;  
        }
        
        if(light_count>0) {
           light_count--;
        }
        if(light_count==0)    stophere = 3;
        
        
    
          if(run_dalay==0) {
          
            if(run_delays==0&&speed_s==1){
               if(stophere==3&&light_off!=0&&STOP_s==1){
                  Speed_Want=0;
                  STOP=1;
                }
                   SpeedControl();                 //�ٶȿ���
              // PORTK_PK7 = 0;
            }
             else
            {
              if(run_delays!=0)
                 run_delays--;
            }
          }
      
           if(run_delays==0&&direction_s==1) {
              Direction_Control();            //�������
            }
            
            
            
          
       }
       
        if(Timeflag40MS >=3)
        {

               //  SendImageData(CCD_AD);
          LED_PrintImage((UCHAR8*)g_aucImageBuf,0,8, LED_MAX_COLUMN_NUM);
          LED_PrintShort(80,3,(SHORT16) lGv);
          LED_PrintShort(80,5,(SHORT16) lZv);
          LED_PrintShort(80,7,(SHORT16) gRealAngle);
      //    LED_PrintShort(80,7,(SHORT16) Speed_PWM);  


          Timeflag40MS = 0;
        } 
               
       if(t>=20)
       {
        TimeFlag20ms_A = 1;
        TimeFlag20ms_B = 1;
        TimeFlag20ms_C = 1;
        TimeFlag20ms_D = 1;
        TimeFlag20ms_E = 1;
        t=0;
       }
       
           


         /* */if(STOP!=0)                  // ͣ��
        {
          DisableInterrupts;
          PORTK_PK7 = 0;
          LED3=0; 
          MORTOR_OUTA=gPWMMid-2000;
          MORTOR_OUTB=gPWMMid-2000;
          
          for(j=1200;j>0;j--)
           for(wait=1000;wait>0;wait--);
          
          MORTOR_OUTA=gPWMMid;
          MORTOR_OUTB=gPWMMid;
          PORTK_PK7 = 1;
          break;
         }   
     
      

      
    } 
    for(;;);  
    
}

VOID MAIN_Init(VOID)
{
    SYSTEM_PLL_Init();
   // Init_POTH_Int();
    INT_PORT();
    INIT_AD();              // 0 CCD_AD2 1 CCD_AD1 2 ACCE���ٶȼ� 3-5 ������
    LED_Init();
    Init_RTI();
    Init_PulseACC();
    init_pwm();
    INIT_SCI0();
    Get_Switch_Key();
}

VOID MAIN_OLED_Display(VOID)
{
  int i=0,j=0,i1=0;

    

    LED_P14x16Str(3, 0, (UCHAR8*)"���������������");
    SYSTEM_TIME_Delay(2000);
    LED_Fill(0x00); 
    //���ͼƬ����
   // (VOID)memset(g_aucImageBuf, 0x00, 32 * LED_MAX_COLUMN_NUM);  
    LED_Fill(0x00); //����
    SYSTEM_TIME_Delay(1000);
    Show_Welcome_Picture();
    SYSTEM_TIME_Delay(2000);
    LED_Fill(0x00); 
    LED_P14x16Str(0, 1, (UCHAR8*)"���");    
    LED_P14x16Str(0, 2, (UCHAR8*)"�ұ�");
    LED_P14x16Str(0, 3, (UCHAR8*)"����");   
    LED_P8x16Str(60, 1,(UCHAR8*)"lG") ;
    LED_P8x16Str(60, 2,(UCHAR8*)"lZ") ;
    LED_P8x16Str(60, 3,(UCHAR8*)"RA") ;
    
    


     /*   */ 
}                                            


