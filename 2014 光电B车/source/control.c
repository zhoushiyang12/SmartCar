/*----------------------------------------------------------------------------*
 * °üº¬Í·ÎÄ¼þ                         
 
 
 
 225   2.2  10 
                                         *
 *----------------------------------------------------------------------------*/
#include<string.h>
#include"common.h"
#include"system_funtion.h"
#include"oled.h"
#include"control.h"
/*----------------------------------------------------------------------------*
 * ºê¶¨Òå                                                                     *
 *----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*
 * È«¾Ö±äÁ¿                                                                   *
 *----------------------------------------------------------------------------*/

int t = 0;
int n = 31;                //rigtt-left
int n0 = 31;                //rigtt-left
int s1 = 0;              //    Startline1;
int s2 = 0;             //    Startline2;
int k = 3;              //ÈË×ÖÌø±äÑØ¸öÊý
int T1 = 0;             //Í£³µ ÆðÊ¼Ïß
int T2 = 1000;             //Í£³µ ³ö½ç
int d = 1;             //µ¹³µÅÐ¶Ï±êÖ¾ 1ÕýÅÜ
int q = 0;             //ccdÇÐ»»±êÖ¾
int shangpo = 0;             //ÉÏÆÂ±êÖ¾
int w=0;                       //Ö±µÀºÍÍäµÀÅÐ¶Ï±êÖ¾w=direction_Erro[2]+direction_Erro[0]-2*direction_Erro[0]
int zhidao=1;                  //Ö±µÀ±êÖ¾
int wd=0;                  //ÍäµÀËÙ¶È±äÁ¿
int wd1=0;                  //ÍäµÀËÙ¶È±äÁ¿
int qianzhan=1;                       //Ç°Õ°ÊÇ·ñ¶ªÏß
int panduandaochequ=0;    //  ´«µÝ
int panduantingche=0;    //  ´«µÝ
int dp=0;    //  ´«µÝ
int shizi=0;    //   Ê®×Ö
int zhangai=0;    //   ÕÏ°­
int yanshi=0;       // WANDAOÑÓÊ±
int bian=0;           // 678±àÂë
int changzhidao=0;           // 678±àÂë
int xs=200;           // ¶þ´ÎÏ¸Êý


int po_c=0;           // po
unsigned char po_old=0;           // po
unsigned char po=0;           // po
unsigned char po1=0;           // po



int s_po_za =0;     //ÕÏ°­ ÆÂµÀ ¿ª¹Ø
int s_shizi =0;     //Ê®×Ö ¿ª¹Ø


int j = 0;              //¼ÆÊý
int f = 0;              //¼ÆÊý
int j1 = 0;              //¼ÆÊý
int j2 = 0;              //¼ÆÊý
int j3 = 0;              //¼ÆÊý
int j4 = 0;              //¼ÆÊý
int t2 = 0;              //¼ÆÊ±
int t3 = 63;              //¼ÆÊ±  shangpo

int m = 0;               //Ç°Ò»¸öqÖµ

int Location_Erro=0;
int Location_Erro1=0;

int SPEED = 0;

int Speed_Want = 0;
int Speed_jichu =  450;          //Ö±µÀ²âÊÔËÙ¶È
int Speed_jichu1_min = 450;          //ÍäµÀ²âÊÔËÙ¶È
int Speed_jichu1_max = 450;          //ÍäµÀ²âÊÔËÙ¶È
int Speed_jichu0 = 450;          //ËÙ¶È
int Speed_min = 450;          //Ö±µÀ²âÊÔËÙ¶È
int Speed_Want_Old=0;
int Speed_Erro[3]={0};
int direction_Erro[5]={0};
int Num=200;
int yuzhi= 27;       //ccdãÐÖµ
int yuzhi1= 100;              //Ç°ccdãÐÖµ
int js=500;           //¾ùËÙ


int renzi= 45;              //ÈË×ÖãÐÖµ
int renzi_s= 0;              //ÈË×ÖÊý
int t_min=20;                //ÈË×Ö×î¶ÌÊ±¼ä
int t_max=40;                //ÈË×Ö×î³¤Ê±¼ä
int wandao1=0;             //ÍäµÀÆ«ÒÆÁ¿
int wandao=0;  //ÍäµÀÆ«ÒÆÁ¿
int rg=0;      //
int jiajiao=0;        

/*float qzsz[64]={0,1,2,3,4,5,6.2,7.5,8.8,9.9,11,
12.3,13.8,15.7,17.7,18.8,20.9,23,25.3,27.6,30,
33,36,39,42,45,49,53,57,61,65,
69,73,77,81,85,89,93,97,101,105,
110,115,125,130,135,140,145,150,155,160,
165,170,175                     
};             */                  //Æ«²îÈ¨Öµ
float qzsz[64]={0,1,2.5,4,5.5,7,8.5,10,11.5,12,13.5,
15,17,18.5,20,21.4,23.4,25.4,27.4,29.4,31.4,
33,36,39,42,45,49,53,57,61,65,
69,73,77,81,85,89,93,97,101,105,
110,115,125,130,135,140,145,150,155,160,
165,170,175,180,185,190,195,200,205,210,
215,220,225,                     
};                               //Æ«²îÈ¨Öµ
  


float Speed_PWM= 0;

float Kp_Speed = 2.3;             //   800   1.7    600  1.55      700   2       1.97     2        2.3
float Ki_Speed = 0.54;              //       0.48          0.45        0.35       0.43      0.44  0.55
float Kd_Speed = 1.8;               //       1.6         1.7           1.8       1.75      1.75   1.8



float Kp_Direction = 2.3;         //ÍäµÀ
float Kd_Direction = 10;
float Kp_Direction1 = 2.3;      //Ö±µÀ
float Kd_Direction1 = 10;

float MORTOR_PWM=2000;

float Control_PWM=0,Control_PWM_old=0,value=0;//·Ö¶ÎÌí¼Ó20


unsigned char CCD_AD[128]={0};
unsigned char CCD_AD1[128]={0};
unsigned char Exposure_Time =10; 
unsigned char Exposure_Time1 =6; 
unsigned char Switch_Key_Value[8]={0};
SHORT16  Average_CCDVoltage =0;
SHORT16  Expect_Average_CCDVoltage =28;
SHORT16  Expect_Average_CCDVoltage1 =25;
int      Average_CCDVoltage_Erro = 0;

UCHAR8   g_aucImageBuf[8][LED_MAX_COLUMN_NUM];


unsigned char Timeflag20MS=0;
unsigned char Timeflag40MS=0;
int black_line_old = 64,black_line = 64;
unsigned char black_line_old0 = 64,black_line0 = 64;
int left = 0,right = 0,left1 = 0,right1 = 0,left_old = 0,right_old = 0,Left_Lose_old=0,Right_Lose_old=0;
unsigned char leftchu = 0,rightchu = 0;


unsigned char s,z=127,zr=0,yr=0,zr1=0,yr1=0,r=0;     //Ìø±äÑØ
 
 /*----------------------------------------------------------------------------*
 * ÄÚ²¿º¯ÊýÔ­ÐÍ                                                               *
 *----------------------------------------------------------------------------*/
int  ReadSpeed();
void delay(void);
 
 /*----------------------------------------------------------------------------*
 * Íâ²¿º¯ÊýÔ­ÐÍ                                                               *
 *----------------------------------------------------------------------------*/


/*****************************************/
/*            ¶Ë¿Ú³õÊ¼»¯                 */
/*****************************************/
void INT_PORT(void)
{
  Switch_Key_DDR = 0x00;
  Switch_Key_PLUS = 1;//A¿ÚÄÚÖÃÉÏÀ­  8Î»²¦Âë
  
  Startline1_DDR = 0;
  Startline2_DDR = 0;
  
  DIR_DDR  = 0;
  LED1_DDR = 1;
  LED2_DDR = 1;
  LED3_DDR = 1;
  LED1 = LED_OFF;
  LED2 = LED_OFF;
  LED3 = LED_OFF;
  
  Light_Key1_DDR = 0;
  Light_Key2_DDR = 0;
  
  BUZZER_DDR = 1;
  BUZZER = BUZZER_OFF;
  
  CCD_CLK2_DDR = 1;
  CCD_SI2_DDR  = 1;
  CCD_CLK2 = 1;
  CCD_SI2  = 1;
  
  CCD_CLK1_DDR = 1;
  CCD_SI1_DDR  = 1;
  CCD_CLK1 = 1;
  CCD_SI1  = 1;
}
 

/*****************************************/
/*            ËÙ¶È¶ÁÈ¡                   */
/*****************************************/
int ReadSpeed()
{
   int Speed;
   Speed = PACNT;
   PACNT = 0;
   if(DIR == 0)  //·½ÏòÅÐ¶Ï
     return Speed;
   else
     return -Speed;
}

/*************************************************************/
/*                        ·¢ËÍËÙ¶È                          */
/*************************************************************/
void Send_Speed(int speed)
{
   int speed_high,speed_low;
   if(speed>=0)
   {
      SCI0_send('#');
      speed_low=speed%127;
      speed_high=speed/127;
      SCI0_send((unsigned char)speed_low);
      SCI0_send((unsigned char)speed_high);
   }
   if(speed<0)
   {
    
   }
  
}
/*****************************************/
/*            »ñÈ¡Ìø±äÑØ                 */
/*****************************************/


void tiaobian_z(void)
{
  unsigned char i;
  s=0;
  z=0;
  for(i=0;i<=70;i++)
  {
    if((CCD_AD[i]-CCD_AD[i+2])>renzi||(CCD_AD[i]-CCD_AD[i+2])<-renzi)
    {
      s++;
      z=z+i;
      i=i+5;
    }
  }
}

void tiaobian_y(void)
{
  unsigned char i;
  s=0;
  z=0;
  for(i=128;i>=55;i--)
  {
    if((CCD_AD[i]-CCD_AD[i+2])>renzi||(CCD_AD[i]-CCD_AD[i+2])<-renzi)
    {
      s++;
      z=z+i;
      i=i-5;
    }
  }
} 
void tiaobian_r(void)
{
  unsigned char i;
  int o=0;
  s=0;
  z=100;
  for(i=28;i<=z;i++)
  {
    if((CCD_AD[i]-CCD_AD[i+3])>renzi||(CCD_AD[i]-CCD_AD[i+3])<-renzi)
    {
      s++;
      if(o==0){
      z=i+60;                                                
      o++;
      }
      i=i+4;
    }
  }
} 
void jiajiao_z(void)
{
  unsigned char i;                                                    
  for(i=right;i<=124;i++)
  {
    if((CCD_AD[i]-CCD_AD[i+4])<-50)
    {
      jiajiao=i-right;
      break;
    }
  }
} 
void jiajiao_y(void)
{
  unsigned char i;
  for(i=left;i>=4;i--)
  {
    if((CCD_AD[i]-CCD_AD[i-4])<-50)
    {
      jiajiao=left-i;
      break;
    }
  }
} 
/*****************************************/
/*            Æ«²î»ñÈ¡º¯Êý               */
/*****************************************/


void Get_Position(void)                     //Ô¶
{
  unsigned char i;
  unsigned char Left_Lose=0;
  unsigned char Right_Lose=0;
  unsigned char right_q=0,left_q=0;
  for(i=black_line_old0;i>=2;i--)
  {
    if((CCD_AD[i]-CCD_AD[i-2])>yuzhi1)
    {
      left1 = i-1;
      break;
    }
    if(i==27)
    Left_Lose=1;  //×ó±ß¶ªÏß
  }
  
  for(i=black_line_old0;i<=125;i++)
  {
    if((CCD_AD[i]-CCD_AD[i+2])>yuzhi1)
    {
      right1 = i+1;
      break; 
    }
    if(i==100)
    Right_Lose=1;  //ÓÒ±ß¶ªÏß
  }
 
  
  if(Left_Lose==0 && Right_Lose==0){
    
    black_line0 =(unsigned char) (left1+right1)/2;  //¶¼Ã»¶ªÏß
    qianzhan = 1;
    wandao=0;
   // q = 0;
  }
  if(Right_Lose == 1){
  black_line0=black_line;
  
    qianzhan = 0;   
    q = 10;
    j4=0;                   //¿¿ÓÒ
  }
  if(Left_Lose == 1) {
    black_line0=black_line;

    qianzhan = 0;           
    q = -1;                  //¿¿×ó
    j4=0;
  }
  if(j<255)
  j++;                //ÈË×Ö¸öÊý
  if(f<255)
  f++;
  if(panduandaochequ==1&&shangpo==0&&zhidao==1){//
  tiaobian_r();                  //µ½³µÇø  
  }
    if(s>k)
   {
   renzi_s++;
   j=0; 
   }
   if(j>5)
   renzi_s=0;
   if(renzi_s>=1){
    
   r=1;
   f=0; 
   }
   if(f>5)
   r=0;
   
   
  if((m-q)==-10)   //×óÍä
    wandao= wandao1;
  if((m-q)==1)    //ÓÒÍä
    wandao= -wandao1;
        
   m=q;

   black_line_old0=black_line0;
    
    
         
      Location_Erro1 = black_line0-64;
    if(Location_Erro1<0)
      Location_Erro1 = -Location_Erro1;
 

  }

  




void Get_Position1(void)                     //½ü
{
  int g=64;       //Ñ°ÏßÎ»ÖÃ
  int shizi_1=0;
  unsigned char i;
  unsigned char Left_Lose=0;
  unsigned char Right_Lose=0;
  if(shizi==0){
    
         if(black_line_old>=125){
            g=125;
           }
          if(black_line_old<=2){    
            g=2;
           }
            if(black_line_old>2&&black_line_old<125){
             g=black_line_old;
           }
  }
  else{
        if(shizi==15) g=15;
          if(shizi==110) g=110;
 
  }
     for(i=g;i>=2;i--)
  {
    if((CCD_AD1[i]-CCD_AD1[i-2])>yuzhi)
    {
      left = i-1;
      break;
    }
    if(i==2)
    Left_Lose=1;  //×ó±ß¶ªÏß
  }
  
  for(i=g;i<=125;i++)
  {
    if((CCD_AD1[i]-CCD_AD1[i+2])>yuzhi)
    {
      right = i+1;
      break; 
    }
    if(i==125)
    Right_Lose=1;  //ÓÒ±ß¶ªÏß
  }   
 


  n=right-left;

  
  LED_PrintShort(65,3,(SHORT16) left);
  LED_PrintShort(65,5,(SHORT16) right);
  LED_PrintShort(95,3,(SHORT16) Exposure_Time);
  LED_PrintShort(95,5,(SHORT16) Exposure_Time1);
 /* if(Left_Lose==0 && Right_Lose==0)
    black_line =(unsigned char) (left+right)/2;  //¶¼Ã»¶ªÏß
  if(Left_Lose==0 && Right_Lose==1)
    black_line =  left+22;
  if(Left_Lose==1 && Right_Lose==0)
    black_line =  right-22;
  if(Left_Lose==1 && Right_Lose==1)
    black_line =  black_line_old;  */
    
    
  if(Left_Lose==0 && Right_Lose==0) {
  

    if(n>12&&n<55) {
    
    Left_Lose_old = 0;
    Right_Lose_old = 0;
    shizi_1=0;
    
    
    
    black_line =(unsigned char) (left+right)/2+wandao;  //¶¼Ã»¶ªÏß
    if(j4<255)
    j4++;
    if(qianzhan==1&&j4>5){
    q=0 ;
    }
    if(yr==1&&black_line>58&&black_line<70&&n>25&n<45&&j2>t_min) 
    {
    r=0;
    yr=0;
    zr=0;
    yr1=0;
    zr1=0;
    black_line=5;
    }
    if(zr==1&&black_line>58&&black_line<70&&n>25&&n<45&&j2>t_min)
    {
    r=0;
    yr=0;
    zr=0;
    yr1=0;
    zr1=0;
    black_line=123;
    }
    }
  }
  
  
  
  
   if((j2>t_max)&&yr==1) {
     r=0;
    yr=0;
    zr=0;
    yr1=0;
    zr1=0;
    black_line=5;

   }
   if((j2>t_max)&&zr==1) {
     r=0;
    yr=0;
    zr=0;
    yr1=0;
    zr1=0;
    black_line=123;

   }
  if(j1<100)
  j1++;
  
  
  
  
  if(Right_Lose == 1&& Left_Lose==0) {
    black_line =  left+17;
    right=left+32;
    Right_Lose_old = Right_Lose; 
        Left_Lose_old = 0;
    shizi_1=0;
    if(left<=56&&r == 1&&j3>150) {
    r=0;
     zr=1;
     j2=0;
         j3=0;
         }
  }
  if(Left_Lose == 1&& Right_Lose==0) {
    black_line =  right-17;
    left=right-32;
    Left_Lose_old = Left_Lose;
    Right_Lose_old = 0;
    shizi_1=0;
   if(right>=73&& r == 1&&j3>150) {
    r=0;
     yr=1;
     j2=0;
     j3=0;
    }
  } 
  if(Left_Lose == 1&& Right_Lose==1) {
     if(Left_Lose_old==1){
     shizi_1=15;
        }
     if(Right_Lose_old==1){
     shizi_1=110;
     }
     
  
   if(s_shizi==1){
    black_line = black_line0; 
   }
  j1=0;
  
  }
 
  if(n>26&&n<50){//ÕÏ°­¼ì²â
      zhangai=0; 
  }
  if(n>18&&n<26&&black_line<=60&&shangpo==0&&zhidao==1&&s_po_za==1){//ÕÏ°­¼ì²â
      black_line =  right-27;
      zhangai=1; 
  }
  if(n>18&&n<26&&black_line>=68&&shangpo==0&&zhidao==1&&s_po_za==1){
    
      black_line =  left+27;      
      zhangai=1; 
  }
 if((n<28)&&(black_line>60&&black_line<68)&&zhidao==1&&zhangai==0&&right1>right&&left1<left&&s_po_za==1){      //ÉÏÆÂ¼ì²â
       shangpo=1;
       t3=0;

 }
  if(t3>10){
  shangpo=0;
  }
 
  left_old=left;
  right_old=right;
  if(j3>150&&zhangai==0&&shizi==0){
  if((black_line-black_line_old>20)||(black_line-black_line_old<-20))
  black_line = black_line_old;
  }
  if(shangpo==1){
    black_line=black_line_old;
  }
  black_line_old = black_line;
   
      Location_Erro = black_line-64;
    if(Location_Erro<0)
      Location_Erro = -Location_Erro;
  if(s_shizi==1){
    shizi=shizi_1; 
  }
    n0=n;
    
    
    
   //if(po1<po)
  //  po1=po;
    
  LED_PrintShort(95,7,(SHORT16) bian);
 
 LED_PrintShort(65,7,(SHORT16) black_line);
    
    
}
 


/*****************************************/
/*            ËÙ¶È¶ÁÈ¡                   */
/*****************************************/
void chushihua(){

     if(PORTA_PA0==1)
     {
     panduandaochequ =1;     //µ½³µÇø

     }
         
    if(PORTA_PA1==1)
     {
      panduantingche=1;    //Í£³µ
     //T2=0;              //µ÷ÊÔµµ
     }  
     if(PORTA_PA2==1)
    { 
     s_po_za=1; 
    }  
     
      if(PORTA_PA3==1)
     {
       s_shizi=1;
     }
         
     if(PORTA_PA4==1)
     {
      Kp_Direction = 2.55;                        //Í
      Kp_Direction1 = 2.55;                        //Í

     }
         
   
   if(bian==1){
   
       xs=200;  

     Speed_jichu =  550;          //Ö±µÀ²âÊÔËÙ¶È
     Speed_jichu1_min = 450;          //ÍäµÀ²âÊÔËÙ¶È
     Speed_jichu1_max = 500;          //ÍäµÀ²âÊÔËÙ¶È
      Speed_jichu0 = 450;          //ËÙ¶È
      Speed_min = 400;          //Ö±µÀ²âÊÔËÙ¶È

     t_min=20;
     t_max=40;
     
      Kp_Direction = 2.45;         //ÍäµÀ
       Kd_Direction = 10;
      Kp_Direction1 = 2.45;      //Ö±µÀ
      Kd_Direction1 = 10;

   }
    if(bian==2){
    
    xs=200;  
    Exposure_Time1 = 16;
    Speed_jichu = 650;                     //Ö±µÀ
    Speed_jichu1_max = 550;                    //ÍäµÀ
    Speed_jichu1_min = 500;                    //ÍäµÀ
    Speed_min = 500;                       //×îÐ¡ËÙ¶È
     Kp_Direction = 2.5;         //ÍäµÀ
     Kd_Direction = 10;
     Kp_Direction1 = 2.5;      //Ö±µÀ
     Kd_Direction1 = 10;

     t_min=15;
     t_max=35;
     
    }
    if(bian==3){
     xs=220; //225
    Exposure_Time1 = 11;
     Speed_jichu = 650;
    Speed_jichu1_max = 600;                    //ÍäµÀ
    Speed_jichu1_min = 550;                    //ÍäµÀ
    Speed_min = 550; 
     Kp_Direction = 2.45;         //ÍäµÀ
     Kd_Direction = 10;
     Kp_Direction1 = 2.45;      //Ö±µÀ
     Kd_Direction1 =10;
     t_min=17;
     t_max=35
     ;

    }
    if(bian==4){
     xs=220; //225
   Exposure_Time1 = 5; 
     Speed_jichu =700;
    Speed_jichu1_max = 600;                    //ÍäµÀ
    Speed_jichu1_min = 550;                    //ÍäµÀ
     Speed_min = 550;  
     Kp_Direction = 2.4;         //ÍäµÀ
     Kd_Direction =10 ;
     Kp_Direction1 = 2.4;      //Ö±µÀ
     Kd_Direction1 = 10;
     t_min=17;
     t_max=35;

    }
      if(bian==5){    //¸Ä
      
        xs=150;
     Speed_jichu = 750;
    Speed_jichu1_max = 650;                    //ÍäµÀ
    Speed_jichu1_min = 600;                    //ÍäµÀ
     Speed_min = 600;  
     Kp_Direction = 3;         //ÍäµÀ            //2.8
     Kd_Direction =14;                            //20
     Kp_Direction1 = 2.8;      //Ö±µÀ            //2.8
     Kd_Direction1 =11;                          //15
     t_min=15;
     t_max=35;

   
    }
    if(bian==6){//¸Ä
      
    xs=140;
     Speed_jichu = 800;
    Speed_jichu1_max = 650;                    //ÍäµÀ
    Speed_jichu1_min = 600;                    //ÍäµÀ
     Speed_min = 600;  
     Kp_Direction = 3;         //ÍäµÀ            //2.8
     Kd_Direction =14;                            //20
     Kp_Direction1 = 2.8;      //Ö±µÀ            //2.8
     Kd_Direction1 =11;                          //15
     t_min=15;
     t_max=35;
   
   
    }
    if(bian==7){///¸Ä
      
    xs=135;
     Speed_jichu = 900;
    Speed_jichu1_max = 700;                    //ÍäµÀ
    Speed_jichu1_min = 600;                    //ÍäµÀ
     Speed_min = 600;  
     Kp_Direction = 3.1;         //ÍäµÀ            //2.8
     Kd_Direction =17;                            //20
     Kp_Direction1 = 2.9;      //Ö±µÀ            //2.8
     Kd_Direction1 =15;                          //15
     t_min=15;
     t_max=35;
   
   
    }


}

/*****************************************/
/*            678±àÂë                    */
/****************************************/
void bianma()
{
 if(PORTA_PA5==1&&PORTA_PA6==1&&PORTA_PA7==1)
 {
 bian=7;
 }
  if(PORTA_PA5==0&&PORTA_PA6==1&&PORTA_PA7==1) {
    
 bian=6;
  }
 if(PORTA_PA5==1&&PORTA_PA6==0&&PORTA_PA7==1) {
  
 bian=5;
 }

if(PORTA_PA5==0&&PORTA_PA6==0&&PORTA_PA7==1) {
  bian=4;
}
 if(PORTA_PA5==1&&PORTA_PA6==1&&PORTA_PA7==0){
  
 bian=3; 
 }
 if(PORTA_PA5==0&&PORTA_PA6==1&&PORTA_PA7==0) {
  bian=2;
 }
 if(PORTA_PA5==1&&PORTA_PA6==0&&PORTA_PA7==0) {
  bian=1;
 }
 if(PORTA_PA5==0&&PORTA_PA6==0&&PORTA_PA7==0) {
  bian=0;
 }
}

/*****************************************/
/*            µÀÂ·ÅÐ¶Ïº¯Êý               */
/****************************************
void Road_Judge(void)
 { int i=0; 
         
 
   
 if(TimeflagS>=1) {
 TimeflagS++;}

 
   
    
    if(Man_TimeFlags==1){
    Man_Times++;   
    }
    if((Man_Times>Man_Time  && Man_Right==1) || (Man_Times>Man_Time2  && Man_Left==1) ){               //1s
    Man_Left=0;
    Man_Right=0;
    Man_TimeFlags=0;
    Man_Times=0;
     }                                                                               //ÈË×Ö¶¨Ê±
   
   
                                                        
   
    if(Location_Erro<9 && Location_Erro1<15 && Width<105 && Width1<105)       //Ö±µÀ±êÊ¾
    {
     
      Speed_Max=680;
      Speed_Min=640; 
                             
     
     
                        
       
      
      
      Kp_Speed = 1.65;
      Ki_Speed = 0.25; 

   }
   
   if(Location_Erro1>8 &&  Location_Erro<9) {
     
      Speed_Max=500;
      Speed_Min=470;  
       
                                                                         //Ö±ÈëÍä
      Kp_Speed = 2.2;
      Ki_Speed = 0.8;
   }       
  

    
   
   
    if( Location_Erro>=9 )                                             //Íä±êÊ¾
    {
      
      Speed_Max=700;
      Speed_Min=500;
      
     
      
      
      Kp_Speed = 2.2;
      Ki_Speed = 0.8;
    }
    
    
 
       
       
         Kp_Direction=0.002*Location_Erro*Location_Erro+0.6;   //KP    
       if(Kp_Direction<0.8)
       {
         Kp_Direction=0.8;                                 
       }  

         if(PORTA_PA0==1)
         {
            
         Kp_Direction=0.002*Location_Erro*Location_Erro+0.4;   //KP    
       if(Kp_Direction<0.6)
       {
         Kp_Direction=0.6;                                 
       }  
         }
   
        
        
         if(PORTA_PA1==1)
         {
            
         Kp_Direction=0.002*Location_Erro*Location_Erro+1;   //KP    
       if(Kp_Direction<1.2)
       {
         Kp_Direction=1.2;                                 
       }  
         }
         
         
         if(PORTA_PA2==1)
         {
            
         Kp_Direction=0.003*Location_Erro*Location_Erro+1.2;   //KP    
       if(Kp_Direction<1.4)
       {
         Kp_Direction=1.4;                                 
       }  
         }
       
        if(Location_Erro<8)
       {
         Kd_Direction=1;         
       }                                                          
        if(Location_Erro>=8)
       {
         Kd_Direction=2;
       }
       if(Location_Erro>=12)
       {
         Kd_Direction=3;
       }
       if(Location_Erro>=16)
       {
         Kd_Direction=4;
       }
              if(Location_Erro>=20)
       {
         Kd_Direction=5;
       }
              if(Location_Erro>=24)
       {
         Kd_Direction=7;
       }
       if(Location_Erro>=28)
       {
         Kd_Direction=10;
       }
       if(Location_Erro>=32)
       {
        Kd_Direction=15;
       } 
       
      
      if(PORTA_PA3==1)
      {
           if(Location_Erro<8)
       {
         Kd_Direction=2;         
       }                                                          
        if(Location_Erro>=8)
       {
         Kd_Direction=3;
       }
       if(Location_Erro>=12)
       {
         Kd_Direction=4;
       }
       if(Location_Erro>=16)
       {
         Kd_Direction=5;
       }
              if(Location_Erro>=20)
       {
         Kd_Direction=6;
       }
              if(Location_Erro>=24)
       {
         Kd_Direction=8;
       }
       if(Location_Erro>=28)
       {
         Kd_Direction=11;
       }
       if(Location_Erro>=32)
       {
        Kd_Direction=16;
       } 
      }

     black_line_old2 = black_line_old;
     black_line_old = black_line;

        
}

*/

/*****************************************/
/*            ·½Ïò¿ØÖÆº¯Êý               */
/*****************************************/
void Direction_Control(void)
{
   float Direction_PWM=0;
   int o;
   direction_Erro[4]=direction_Erro[3];
   direction_Erro[3]=direction_Erro[2];
   direction_Erro[2]=direction_Erro[1];
   direction_Erro[1]=direction_Erro[0];
   direction_Erro[0]=(black_line-64);
  /*       if(direction_Erro[0]>0) {
        direction_Erro[0]=(int)direction_Erro[0]*4/5;
        } 
 */
                               
  if(direction_Erro[0]>0)
    direction_Erro[0]=(black_line-64)+(black_line-64)*(black_line-64)/xs;
    if(direction_Erro[0]<0)
    direction_Erro[0]=(black_line-64)-(black_line-64)*(black_line-64)/xs;
 /*    if(dp==0) {
      
 if(direction_Erro[0]<0){
    
  Kp_Direction=Kp_Direction1-direction_Erro[0]*0.02; 
  Kd_Direction=Kd_Direction1-direction_Erro[0]*0.35; 
 }
   else {
    
  Kp_Direction=Kp_Direction1+direction_Erro[0]*0.02;
  Kd_Direction=Kd_Direction1+direction_Erro[0]*0.35; 
   }
  
   if(Kp_Direction>3){
   Kp_Direction=3;
   } 
   
    } */
   w=direction_Erro[2]+direction_Erro[0]-2*direction_Erro[1]+direction_Erro[2]+direction_Erro[4]-2*direction_Erro[3];

   Control_PWM_old=Control_PWM;

     if(q==0){                                  //Ö±µÀ
      Direction_PWM =(int)(Kp_Direction1*direction_Erro[0] + Kd_Direction1 * (direction_Erro[0]-direction_Erro[1]));
     }
     
    if(q!=0){
      //ÍäµÀ
    Direction_PWM =(int)(Kp_Direction*direction_Erro[0] + Kd_Direction * (direction_Erro[0]-direction_Erro[1]));
    }
    Control_PWM =((615 - Direction_PWM)+Control_PWM_old)/2;  //ÕýÅÜ
  

   if(Control_PWM>Left_Limit)
     Control_PWM=Left_Limit;
   if(Control_PWM<Right_Limit)
     Control_PWM=Right_Limit;
    // PWMDTY45 = (int)Control_PWM;
    
     
    if((w==0||w==-1||w==1)&&direction_Erro[0]<8&&direction_Erro[0]>-8){
    if(direction_Erro[0]+direction_Erro[1]+direction_Erro[2]+direction_Erro[3]+direction_Erro[4]<3){ 
    }
    //q=0;
    zhidao=1;
    } else{    
    zhidao=0;
    }
    
   /* wd = wd + (Direction_PWM/5);
    if(wd<0){
    wd=-wd;
    }
    if(wd>0){
    wd--;
    wd--;
    }  */
        wd = wd + (Direction_PWM/5);
    if(wd>100){
    wd=100;
    }
    if(wd<-100){
    wd=-100;
    }
    if(wd<0){
    wd1=-wd;
    }
    if( Location_Erro>-9&& Location_Erro<9){
       if(wd<0){
       wd=wd+10;
       }
       if(wd>0){
       wd=wd-10;
       }
    }

}

/*****************************************/
/*            Âí´ï¿ØÖÆº¯Êý               */
/*****************************************/
void MortorControl(void)
{
  //  int Location_Erro=0;
    
    
    SPEED=  ReadSpeed();
       
 /*        
if(Speed_Want_Old !=Speed_Want)
    {
      Speed_Want_Old = Speed_Want;
      Num=55; 
    }
    if(Num>0)
    {
      Num--;
      Send_Speed(SPEED);
    }*/  
   if(SPEED>350){
    
   js= (SPEED+js)/2;
   }
   
   
  Location_Erro = black_line-64;
    if(Location_Erro<0)
      Location_Erro = -Location_Erro;
    
    if(q==0){
       yanshi=8;
       if(Speed_jichu0 < Speed_jichu)
       Speed_jichu0 = Speed_jichu0 + 20;
       Speed_Want = Speed_jichu0- Location_Erro*3;   //Ö±µÀ
    }
    if(q!=0){
       if(yanshi!=0){
       Speed_jichu0=Speed_jichu1_min;
       yanshi--;
       }else{
        
       if(Speed_jichu0 < Speed_jichu1_max)
       Speed_jichu0 = Speed_jichu0 + 3; 
       }
       Speed_Want = Speed_jichu0 - Location_Erro*5;      //ÍäµÀ
    }
   
    //Speed_Want =Speed_Want+rg;
    Speed_Want =Speed_Want-wd1;
    
     if(Speed_Want<Speed_min)
      Speed_Want = Speed_min;
    if(d==0)    //·´ÅÜ
      Speed_Want = -Speed_Want;
    
    if(zr==1||yr==1){
      
    Speed_Want= 400;
    rg=100; 
    }
     if(shangpo==1) {
      Speed_Want=400;
     }
 if(T1==1&& panduantingche==1&&shangpo==0){
Speed_Want=0;
}
    
    Speed_Erro[2] = Speed_Erro[1];                    //ÉÏÉÏ´ÎÆ«²î
    Speed_Erro[1] = Speed_Erro[0];                     //ÉÏ´ÎÆ«²î
    Speed_Erro[0] = Speed_Want - SPEED;              //±¾´ÎÆ«²î
    Speed_PWM += Ki_Speed*Speed_Erro[0] + Kp_Speed*(Speed_Erro[1]-Speed_Erro[2]) + Kd_Speed*(Speed_Erro[0]-2*Speed_Erro[1]+Speed_Erro[2]);
    if(Speed_PWM >1000)
       Speed_PWM = 1000;
    if(Speed_PWM <-1000)
       Speed_PWM = -1000; 
    
    MORTOR_PWM = 2000-Speed_PWM;
    PWMDTY01 = (int)MORTOR_PWM;
}


/*************************************************************/
/*                        ÑÓÊ±º¯Êý                           */
/*************************************************************/
void delay(void) 
{
      asm("nop"); asm("nop"); asm("nop"); asm("nop");
      asm("nop"); asm("nop"); asm("nop"); asm("nop");
      asm("nop"); asm("nop"); asm("nop"); asm("nop");
}

/*****************************************/
/*            ÆØ¹â¿ØÖÆº¯Êý               */
/*****************************************/
void StartIntegration(void) 
{

    unsigned char i;

    CCD_SI2 = 1;         /* SI  = 1 */
    delay();
    CCD_CLK2 = 1;        /* CLK = 1 */
    delay();
    CCD_SI2 = 0;         /* SI  = 0 */
    delay();
    CCD_CLK2 = 0;        /* CLK = 0 */

    for(i=0; i<127; i++) 
    {
        delay();
        CCD_CLK2 = 1;    /* CLK = 1 */
        delay();
        CCD_CLK2 = 0;    /* CLK = 0 */
    }
    delay();
    CCD_CLK2 = 1;        /* CLK = 1 */
    delay();
    CCD_CLK2 = 0;        /* CLK = 0 */
}


void StartIntegration1(void)          //·´Ïò
{

    unsigned char i;

    CCD_SI1 = 1;         /* SI  = 1 */
    delay();
    CCD_CLK1 = 1;        /* CLK = 1 */
    delay();
    CCD_SI1 = 0;         /* SI  = 0 */
    delay();
    CCD_CLK1 = 0;        /* CLK = 0 */

    for(i=0; i<127; i++) 
    {
        delay();
        CCD_CLK1 = 1;    /* CLK = 1 */
        delay();
        CCD_CLK1 = 0;    /* CLK = 0 */
    }
    delay();
    CCD_CLK1 = 1;        /* CLK = 1 */
    delay();
    CCD_CLK1 = 0;        /* CLK = 0 */
}

/*****************************************/
/*            ¶ÁÈ¡Ò»Ö¡Í¼Ïñ               */
/*****************************************/
void ImageCapture(unsigned char * ImageData) {

    unsigned char i;
    unsigned char  temp_int;

    CCD_SI2 = 1;         /* SI  = 1 */
    delay();
    CCD_CLK2 = 1;        /* CLK = 1 */
    delay();
    CCD_SI2 = 0;         /* SI  = 0 */
    delay();

    //Delay 20us for sample the first pixel
    
    for(i = 0; i < 125; i++) {                //¸ü¸Ä25*5£¬ÈÃCCDµÄÍ¼Ïñ¿´ÉÏÈ¥±È½ÏÆ½»¬£¬
        delay();                      //°Ñ¸ÃÖµ¸Ä´ó»òÕß¸ÄÐ¡´ïµ½×Ô¼ºÂúÒâµÄ½á¹û¡£
    }  
      /*  SamplingDelay();
        SamplingDelay();*/

    //Sampling Pixel 1
    temp_int =(unsigned char) AD_capture(1);
    *ImageData++ = temp_int;
    CCD_CLK2 = 0;        /* CLK = 0 */

    for(i=0; i<127; i++) {
        delay();
        CCD_CLK2 = 1;    /* CLK = 1 */
        delay();
        //Sampling Pixel 2~128
        temp_int =(unsigned char) AD_capture(1);
        *ImageData++ = temp_int;
        CCD_CLK2 = 0;    /* CLK = 0 */
    }
    delay();
    CCD_CLK2 = 1;        /* CLK = 1 */
    delay();
    CCD_CLK2 = 0;        /* CLK = 0 */
}
void ImageCapture1(unsigned char * ImageData) {             //·´Ïòccd

    unsigned char i;
    unsigned char  temp_int;

    CCD_SI1 = 1;         /* SI  = 1 */
    delay();
    CCD_CLK1 = 1;        /* CLK = 1 */
    delay();
    CCD_SI1 = 0;         /* SI  = 0 */
    delay();

    //Delay 20us for sample the first pixel
    
    for(i = 0; i < 125; i++) {                //¸ü¸Ä25*5£¬ÈÃCCDµÄÍ¼Ïñ¿´ÉÏÈ¥±È½ÏÆ½»¬£¬
        delay();                      //°Ñ¸ÃÖµ¸Ä´ó»òÕß¸ÄÐ¡´ïµ½×Ô¼ºÂúÒâµÄ½á¹û¡£
    }  
      /*  SamplingDelay();
        SamplingDelay();*/

    //Sampling Pixel 1
    temp_int =(unsigned char) AD_capture(0);
    *ImageData++ = temp_int;
    CCD_CLK1 = 0;        /* CLK = 0 */

    for(i=0; i<127; i++) {
        delay();
        CCD_CLK1 = 1;    /* CLK = 1 */
        delay();
        //Sampling Pixel 2~128
        temp_int =(unsigned char) AD_capture(0);
        *ImageData++ = temp_int;
        CCD_CLK1 = 0;    /* CLK = 0 */
    }
    delay();
    CCD_CLK1 = 1;        /* CLK = 1 */
    delay();
    CCD_CLK1 = 0;        /* CLK = 0 */
}

/*****************************************/
/*            ·¢ËÍÊ®Áù½øÖÆÊý             */
/*****************************************/
void SendHex(unsigned char hex) {
  unsigned char temp;
  temp = hex >> 4;
  if(temp < 10) {
    SCI0_send(temp + '0');
  } else {
    SCI0_send(temp - 10 + 'A');
  }
  temp = hex & 0x0F;
  if(temp < 10) {
    SCI0_send(temp + '0');
  } else {
    SCI0_send(temp - 10 + 'A');
  }
}

/*****************************************/
/*            ·¢ËÍÒ»Ö¡Í¼Ïñ               */
/*****************************************/
void SendImageData(unsigned char * ImageData) {

    unsigned char i;
    unsigned char crc = 0;

    /* Send Data */
    SCI0_send('*');
    SCI0_send('L');
    SCI0_send('D');

    SendHex(0);
    SendHex(0);
    SendHex(0);
    SendHex(0);

    for(i=0; i<128; i++) {
      SendHex(*ImageData++);
    }

    SendHex(crc);
    SCI0_send('#');
}

/*****************************************/
/*            ¼ÆËãÆØ¹âÊ±¼ä               */
/*****************************************/

void Calculate_Exposure_Time(unsigned char * ccd)
{

  Average_CCDVoltage = PixelAverage(128,ccd);
  Average_CCDVoltage = Average_CCDVoltage*25/128;
  
  Average_CCDVoltage_Erro = Expect_Average_CCDVoltage - Average_CCDVoltage;
  if(Average_CCDVoltage_Erro>2)
  Exposure_Time++;
  if(Average_CCDVoltage_Erro<-2)
    Exposure_Time--;
  if(Exposure_Time<1)
    Exposure_Time=1;
  if(Exposure_Time>15)
    Exposure_Time=15;
  
}
void Calculate_Exposure_Time1(unsigned char * ccd)
{

  Average_CCDVoltage = PixelAverage(128,ccd);
  Average_CCDVoltage = Average_CCDVoltage*25/128;
  
  Average_CCDVoltage_Erro = Expect_Average_CCDVoltage1 - Average_CCDVoltage;
  if(Average_CCDVoltage_Erro>2)
  Exposure_Time1++;
  if(Average_CCDVoltage_Erro<-2)
    Exposure_Time1--;
  if(Exposure_Time1<1)
    Exposure_Time1=1;
  if(Exposure_Time1>15)
    Exposure_Time1=15;
  
}

unsigned char PixelAverage(unsigned char len, unsigned char *data) {
  unsigned char i;
  unsigned int sum = 0;
  for(i = 0; i<len; i++) {
    sum = sum + *data++;
  } ;
  return ((unsigned char)(sum/len));
}


/*****************************************/
/*            ÈüµÀÏÔÊ¾º¯Êý               */
/*****************************************/

/*void Show_load(void)
{
  int i=0,j=0;
  
  for(i=0;i<128;i++)
    Average_CCDVoltage +=CCD_AD[i];
 
       
  for(i=0;i<128;i++)
  {
    if((i>left)&&(i<right))
      for(j=0;j<8;j++)
        g_aucImageBuf[j][i]=1;
    else
    {
      for(j=0;j<6;j++)
        g_aucImageBuf[j][i]=0;          
        g_aucImageBuf[6][i]=1;
        g_aucImageBuf[7][i]=1;
    }
  }
        
}*/
 void Show_load1(void)
{

  int i=0,i1=0;


  for(i=0;i<128;i++)
  {
    if((i>left1)&&(i<right1))
      for(i1=0;i1<5;i1++)
        g_aucImageBuf[i1][i]=1;
    else
    {
      for(i1=0;i1<4;i1++)
        g_aucImageBuf[i1][i]=0;          
        g_aucImageBuf[4][i]=1;
    }
  }
        
}
void Show_load(void)
{
  int i=0,i1=0;
  

 
       
  for(i=0;i<128;i++)
  {
    if((i>left)&&(i<right))
      for(i1=5;i1<10;i1++)
        g_aucImageBuf[i1][i]=1;


    else
    {
      for(i1=5;i1<8;i1++)
        g_aucImageBuf[i1][i]=0;          
        g_aucImageBuf[8][i]=1;
    }
  }
 }


/*****************************************/
/*            ²¦Âë                       */
/*****************************************/

void Get_Switch_Key(void)
{
   Switch_Key_Value[0] = PORTA_PA0;
   Switch_Key_Value[1] = PORTA_PA1;
   Switch_Key_Value[2] = PORTA_PA2;
   Switch_Key_Value[3] = PORTA_PA3;
   Switch_Key_Value[4] = PORTA_PA4;
   Switch_Key_Value[5] = PORTA_PA5;
   Switch_Key_Value[6] = PORTA_PA6;
   Switch_Key_Value[7] = PORTA_PA7;
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED 
void interrupt 7 RTI_ISR(void)		  //º¯ÊýÓ³Éä¹ØÏµ
{ 
    t++;
    
    
    if(t2>200){
    s1=Startline1;
    s2=Startline2;
    }
    
    
    
    if((15-Exposure_Time)>=3) 
    {
      if((15-Exposure_Time) == t)
      {
        StartIntegration();
      }
    }
    
    if((15-Exposure_Time1)>=3) 
    {
      if((15-Exposure_Time1) == t)
      {
        StartIntegration1();
      }
    }
     if(zr==0&&yr==0){
      
     PWMDTY45 = (int)Control_PWM;
     }


    CRGFLG_RTIF = 1;   //ÇåÖÐ¶Ï±êÖ¾
  
   //CRGFLG|=0X80;//Write 1 to clear RTIF bit   
}

#pragma CODE_SEG DEFAULT





#pragma CODE_SEG __NEAR_SEG NON_BANKED 

void interrupt 24 POTJ_INT(void)		  //Íâ²¿ÖÐ¶Ï
{   int xxx;
    
     yuzhi= yuzhi+2;              //ccdãÐÖµ
 /*      renzi +=2;
       Kp_Direction= Kp_Direction+0.1;
       Kp_Direction1= Kp_Direction;*/
    for( xxx=0;xxx<1000;xxx++) {
      BUZZER= ~BUZZER;  
    PIFJ_PIFJ0 = 1;//ÇåÖÐ¶Ï±êÖ¾
    }
}
#pragma CODE_SEG DEFAULT
