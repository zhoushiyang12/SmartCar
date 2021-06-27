/*----------------------------------------------------------------------------*
 * 包含头文件                                                                 *
 *----------------------------------------------------------------------------*/
#include<string.h>
#include"common.h"
#include"system_funtion.h"
#include"oled.h"
#include"control.h"

#include "anglecontrol.h"
//#include "communication.h"
/*----------------------------------------------------------------------------*
 * 宏定义                                                                     *
 *----------------------------------------------------------------------------*/

#define  Left_Limit   700 
#define  Right_Limit   460 
/*----------------------------------------------------------------------------*
 * 全局变量                                                                   *
 *----------------------------------------------------------------------------*/

int t = 0;


int ft = 0;                        //分次叠加标志
int start_sud = 500;                        //分次叠加标志

int direction_s=0;                 //方向开关
int speed_s = 0;                   //速度开关

int Speed_Want = 0;
int Speed_Wanted = 0;
int Speed_Want_Old=0;
int Speed_Erro[3]={0};
int Speed_Err=0;
int direction_Erro[5]={0};
int Num=200;
//电机输出

//速度定义
int SPEED_A = 0;
int SPEED_B = 0;
int SPEED_Aa = 0;
int SPEED_Bb = 0;
int SPEED = 0;                        // SPEED = (SPEED_A+SPEED_B)/2
float Speed_PWM= 0;                //速度输出PWM
float Speed_PWM_old= 0;                //上次速度输出PWM
float Speed_PWM_inc= 0;                //增加速度输出PWM



float Kp_Speed = 35;             //  7           2          7   15
float Ki_Speed = 4;              //  2.5         0.6     1.9     3
float Kd_Speed = 0;               //  3.5       0.8       2.3   10


float Kp_Direction = 7.5;
float Ki_Direction = 0;
//float Kp_Direction_jc = 9.5;
float Kd_Direction = 130;          //180
float lSpeedOut=0;
float lIntegral=0;
float lLimitUH=1500;                  
float lLimitUL=-1500; 

float lLimitIH=1000;                  
float lLimitIL=-1000;

float MORTOR_PWM=0;
//方向定义
float Direction_PWM=0;                  //总方向
float Direction_PWM_old=0;                  //上次总方向
float Direction_PWM_inc=0;                  //总方向
float Direction_PWM_A=0;                //左电机方向
float Direction_PWM_B=0;                //右电机方向
unsigned char black_line_old = 64,black_line_old1 = 64,black_line = 64,black_line1 = 64,centre_lined=0,centre_lineu=0,rock_up=0,rock_down=0;
int left = 0,right = 0,left1 = 0,right1 = 0,left_old = 0,right_old = 0,Left_Lose_old=0,Right_Lose_old=0;
   unsigned char Left_Lose=0;
  unsigned char Right_Lose=0;

//CCD定义
int yuzhi= 40;       //ccd阈值
int yuzhi1= 30;              //前ccd阈值
unsigned char CCD_AD[128]={0};
unsigned char CCD_AD1[128]={0};
unsigned char Exposure_Time =5; 
unsigned char Exposure_Time1 =3; 
unsigned char Switch_Key_Value[8]={0};
SHORT16  Average_CCDVoltage =0;
SHORT16  Expect_Average_CCDVoltage =30;
int      Average_CCDVoltage_Erro = 0;

//OLED定义
UCHAR8   g_aucImageBuf[8][LED_MAX_COLUMN_NUM];

//FLAG标志
unsigned char COUNT = 0;                //停车标记
unsigned char STOP = 0;                //停车标记
unsigned char STOP_s = 0;                //停车标记
unsigned char black_l = 0;                //停车标记
unsigned char black_r = 0;                //停车标记
unsigned char black_l_old = 0;                //停车标记
unsigned char black_r_old = 0;                //停车标记
unsigned char Timeflag20MS=0;
unsigned char Timeflag40MS=0;
unsigned char qianzhan=1;
//十字 
int shizi=0;    //   十字
int s_shizi =0;     //十字 开关 1开
int loseswitch=0;

//障碍
int rock_delay=0;
int S_rock=0;
//单线
int S_single_line=0;
//直角
int quanhei = 0;
int zhijiao_j=0;
int zhijiao = 0;
int zhijiao_tmin=20 ;
int zhijiao_delay=30 ;              //两次间隔
int k=0,sum=0,ave=0;                   //宽
int zhijiao_dl=0;                               //延时

 /*----------------------------------------------------------------------------*
 * 内部函数原型                                                               *
 *----------------------------------------------------------------------------*/
void ReadSpeed();
void delay(void);

void SendDataVisual(void);               //发送直立参数


 /*----------------------------------------------------------------------------*
 * 外部函数原型                                                               *
 *----------------------------------------------------------------------------*/
 
 
 
 
 
/*****************************************/
/*            按键控制函数               */
/*****************************************/


void Get_Switch_Key(void)
{
   Switch_Key_Value[0] = Switch_Key_1;
   Switch_Key_Value[1] = Switch_Key_2;
   Switch_Key_Value[2] = Switch_Key_3;
   Switch_Key_Value[3] = Switch_Key_4;
   Switch_Key_Value[4] = Switch_Key_5;
   Switch_Key_Value[5] = Switch_Key_6;
   Switch_Key_Value[6] = Switch_Key_7;
   Switch_Key_Value[7] = Switch_Key_8;
}

void Switch_Choose(void)
{
   if(Switch_Key_Value[0]==1){      //1500
      // lCz=1415;
     // gKia = 400;
     PORTK_PK7 = 0;
     lCz= 1275;
      //   Speed_Want = 100;
     // Ki_Speed =14;
   }
   if(Switch_Key_Value[1]==1){
     //lCz=1410;
      lCz = 1245;
    // gKia = 1200;
       //Speed_Want = -50;
        PORTK_PK7 = 0;
       // Kp_Speed =10;
   }
   if(Switch_Key_Value[2]==1){
  
   //      gKpa = 450;
     // gKia = 1600;
       PORTK_PK7 = 0;
     // gKpa = 700;
       //    Speed_Want = 150;
     //       Kp_Direction = 2;
     // Kd_Direction = 0;
    // Ki_Speed =18;
       //  gKpa = 900;
    //    gKia = 400;
  // gKda = 3000;
      Speed_Want = 300;
      direction_s = 1;
     speed_s = 1;
     //  Kp_Direction = 3;
    //  Kd_Direction = 15;
   }
   if(Switch_Key_Value[3]==1){
        //  gKda = 200 ;
     gKpa = 1300;
      //    gKda = 600;
          Speed_Want = 400;
       Kp_Direction = 9;
     Kd_Direction = 150;

      PORTK_PK7 = 0;
   }
   if(Switch_Key_Value[4]==1){
            gKpa = 1400;
     //gKia = 600;
   //  gKda =40 ;                             400/ dir6.5  150 /angle 1400 /speed 35 2
          Kp_Direction = 14.5;
         Kd_Direction = 180;
         Speed_Want = 500;

  // Kp_Speed =8 ;
       PORTK_PK7 = 0;
    //   direction_s = 1;

   }
 if(Switch_Key_Value[5]==1){
         S_single_line=1;
 
     //Kp_Speed =25 ;
     PORTK_PK7 = 0;
   }
   if(Switch_Key_Value[6]==1){
   //Kd_Speed =20 ;
       // gKpa = 1000;
       S_rock=1;
   PORTK_PK7 = 0;
   }

   if(Switch_Key_Value[7]==1){
        //Kp_Direction = 6;
      //  Kp_Speed = 40;              
        loseswitch=1;              //丢线延时开关
        s_shizi =1;                  //十字开关
        STOP_s =1 ; 
        PORTK_PK7 = 0;                  //停车开关
     }   
                         
}




/*****************************************/
/*            端口初始化                 */
/*****************************************/
void INT_PORT(void)
{
   Switch_Key_DDR = 0x00;
  Switch_Key_PLUS = 1;        //E口内置上拉  8位拨码
  Switch_Key_PLUS_A = 1;        //E口内置上拉  8位拨码
  ECLKCTL_NECLK= 1;
  IRQCR_IRQEN = 0;
  
  Startline1_DDR = 0;         //0为输入
  Startline2_DDR = 0;
  
  DIRA_DDR  = 0;
  DIRB_DDR  = 0;
  REAB_DDR  = 1;
  REAB = 0;              //置0开始工作

  LED3_DDR = 1;
  LED3 = LED_OFF;
  
  Light_Key1_DDR = 0;
  Light_Key2_DDR = 0;
  
  BUZZER_DDR = 1;
  BUZZER = BUZZER_OFF;
  
  CCD_CLK1_DDR = 1;
  CCD_SI1_DDR  = 1;
  CCD_CLK1 = 1;
  CCD_SI1  = 1;
  CCD_CLK2_DDR = 1;
  CCD_SI2_DDR  = 1;
  CCD_CLK2 = 1;
  CCD_SI2  = 1;
  
  Black_Check1_DDR = 0;
  Black_Check2_DDR = 0;
}
 

/*****************************************/
/*            速度读取                   */
/*****************************************/
void ReadSpeed()
{
   SPEED_A = PACNT;
   SPEED_B = SUDB;
   
   if(DIRA == 1)  //方向判断
     SPEED_A = -SPEED_A;
   else
     SPEED_A = SPEED_A;
   
   if(DIRB == 0)  //方向判断
     SPEED_B = -SPEED_B ;
   else
     SPEED_B = SPEED_B ;
   
   REAB = 1;             //清零置1  置0开始工作
   Delay250ns();
   PACNT = 0;
   REAB = 0;              //置0开始工作
}




/*************************************************************/
/*                        发送速度                          */
/*************************************************************/
void Send_Speed(int speed)
{
   int speed_high,speed_low;
   if(speed>=0)
   {
     // SCI0_send('#');
      speed_low=speed%127;
      speed_high=speed/127;
      SCI0_send((unsigned char)speed_low);
      SCI0_send((unsigned char)speed_high);
   }
   if(speed<0)
   {
    
   }
  
}
 


/*************************************************************/
/*                        延时函数                           */
/*************************************************************/
void delay(void) 
{
      asm("nop"); asm("nop"); asm("nop"); asm("nop");
      asm("nop"); asm("nop"); asm("nop"); asm("nop");
      asm("nop"); asm("nop"); asm("nop"); asm("nop");
}

/*************************************************************/
void delay_1s(int i)
{
  int p;
  for(;i>=0;i--)
    for(p=1000;p>0;p--){
    }
}

/*****************************************/
/*            曝光控制函数               */
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
     
     
void StartIntegration1(void)          //反向
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
/*            读取一帧图像               */
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
    
    for(i = 0; i < 125; i++) {                //更改25*5，让CCD的图像看上去比较平滑，
        delay();                      //把该值改大或者改小达到自己满意的结果。
    }  
      /*  SamplingDelay();
        SamplingDelay();*/

    //Sampling Pixel 1
 
    temp_int =(unsigned char)(AD_capture(1)>>4);
    *ImageData++ = temp_int;
    CCD_CLK2 = 0;        /* CLK = 0 */

    for(i=0; i<127; i++) {
        delay();
        CCD_CLK2 = 1;    /* CLK = 1 */
        delay();
        //Sampling Pixel 2~128
    
        temp_int =(unsigned char)( AD_capture(1)>>4);
        *ImageData++ = temp_int;
        CCD_CLK2 = 0;    /* CLK = 0 */
    }
    delay();
    CCD_CLK2 = 1;        /* CLK = 1 */
    delay();
    CCD_CLK2 = 0;        /* CLK = 0 */
}


void ImageCapture1(unsigned char * ImageData) {             //反向ccd

    unsigned char i;
    unsigned char  temp_int;

    CCD_SI1 = 1;         /* SI  = 1 */
    delay();
    CCD_CLK1 = 1;        /* CLK = 1 */
    delay();
    CCD_SI1 = 0;         /* SI  = 0 */
    delay();

    //Delay 20us for sample the first pixel
    
    for(i = 0; i < 125; i++) {                //更改25*5，让CCD的图像看上去比较平滑，
        delay();                      //把该值改大或者改小达到自己满意的结果。
    }  
      /*  SamplingDelay();
        SamplingDelay();*/

    //Sampling Pixel 1
    // while(ATD0STAT0_SCF==0);
    temp_int =(unsigned char)( AD_capture(0)>>4);
    *ImageData++ = temp_int;
    CCD_CLK1 = 0;        /* CLK = 0 */

    for(i=0; i<127; i++) {
        delay();
        CCD_CLK1 = 1;    /* CLK = 1 */
        delay();
        //Sampling Pixel 2~128
     //while(ATD0STAT0_SCF==0);
        temp_int =(unsigned char)( AD_capture(0)>>4);
        *ImageData++ = temp_int;
        CCD_CLK1 = 0;    /* CLK = 0 */
    }
    delay();
    CCD_CLK1 = 1;        /* CLK = 1 */
    delay();
    CCD_CLK1 = 0;        /* CLK = 0 */
}



/*****************************************/
/*            发送十六进制数             */
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
/*            发送一帧图像               */
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
/*            计算曝光时间               */
/*****************************************/

void Calculate_Exposure_Time(void)
{
  Average_CCDVoltage = Average_CCDVoltage/128;
  Average_CCDVoltage = Average_CCDVoltage*25/128;
  
  Average_CCDVoltage_Erro = Expect_Average_CCDVoltage - Average_CCDVoltage;
  if(Average_CCDVoltage_Erro>2)
  Exposure_Time++;
  if(Average_CCDVoltage_Erro<-2)
    Exposure_Time--;
  if(Exposure_Time<1)
    Exposure_Time=1;
  if(Exposure_Time>20)
    Exposure_Time=20;
  
}



/*****************************************/
/*            赛道显示函数               */
/*****************************************/

void Show_load(void)
{
  int i=0,j=0,i1=0;
  
 /* for(i=0;i<128;i++)
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
    
    
    
    if((i>left)&&(i<right))
      for(i1=5;i1<10;i1++)
        g_aucImageBuf[i1][i]=1;


    else
    {
      for(i1=5;i1<8;i1++)
        g_aucImageBuf[i1][i]=0;          
        g_aucImageBuf[8][i]=1;
    }
    
  }*/
  
  
  
        //  LED_PrintShort(20,0,(SHORT16) left);
        //  LED_PrintShort(20,1,(SHORT16) right);
          
          LED_PrintShort(5,0,(SHORT16) left1);
          LED_PrintShort(5,1,(SHORT16) right1);
  
        
}




/*****************************************/
/*            偏差获取函数               */
/*****************************************/


void Get_Position1(void)                     //远
{
  unsigned char i,kd;
  unsigned char Left_Lose1=0;
  unsigned char Right_Lose1=0;
  unsigned char right_q=0,left_q=0;
  for(i=black_line_old1;i>=2;i--)
  {
    if((CCD_AD1[i]-CCD_AD1[i-2])>yuzhi1)
    {
      left1 = i-1;
      break;
    }
    if(i==27)
    Left_Lose1=1;  //左边丢线
    else
    Left_Lose1=0;  //右边丢线
  }
  
  for(i=black_line_old1;i<=125;i++)
  {
    if((CCD_AD1[i]-CCD_AD1[i+2])>yuzhi1)
    {
      right1 = i+1;
      break; 
    }
    if(i==100)
    Right_Lose1=1;  //右边丢线
    else
    Right_Lose1=0;  //右边丢线
  }
 
  
  if(Left_Lose1==0 && Right_Lose1==0){
    
    black_line1 =(unsigned char) (left1+right1)/2;  //都没丢线
    qianzhan = 1;
   // q = 0;
  }
  if(Right_Lose1 == 1&& Left_Lose1==0){
      black_line1=left1+25;
          right = left+45 ;

    qianzhan = 2;   
  }
  if(Left_Lose1 == 1&& Right_Lose1==0) {
       black_line1=right1-25;
      left =right +45 ;

    qianzhan = -2;           
  }
  if(Left_Lose1 == 1&& Right_Lose1==1) {

       kd=left1;
      for(kd;kd<=right1;kd++){
         if(CCD_AD[kd]>180) 
          ave++;
      } 
      if(ave>(right1-left1-8))
           qianzhan = 0;           
  }
    
    
    
    black_line_old1=black_line1 ;

    LED_PrintShort(50,0,(SHORT16) black_line1);

  }




void Get_Position(void)
{
  unsigned char g=64;       //寻线位置
  static int rigt;
  static int lef;
  unsigned char i,j,kd,b=0;
  
  
  left_old=left;
  right_old=right;
  
  if(shizi==0||s_shizi==0){
    
         if(black_line_old>=30){
            g=30;
           }
          if(black_line_old<=97){    
            g=97;
           }
            if(black_line_old>30&&black_line_old<97){
             g=black_line_old;
           }
  }
  else{
        if(shizi==15) g=20;
          if(shizi==110) g=107;
 
  }
  for(i=g+8;i>=20;i--)
  {
    if((CCD_AD[i]-CCD_AD[i-2])>yuzhi)
    {
      left = i-1;
      break;
    }
    if(i==20)
    Left_Lose=1;  //左边丢线
    else
    Left_Lose=0;  //右边丢线
  }
  
  for(i=g-8;i<=107;i++)
  {
    if((CCD_AD[i]-CCD_AD[i+2])>yuzhi)
    {
      right = i+1;
      break; 
    }
    if(i==107)
    Right_Lose=1;  //右边丢线
    else
    Right_Lose=0;  //右边丢线
  }   

  k= right- left;
  
  
  if(Left_Lose==0 && Right_Lose==0){
      if((k>-9)){  
          black_line =(unsigned char) (left+right)/2;  //都没丢线
      }
      zhijiao=0;
      shizi  =0;
    
         if(quanhei ==1){
               if( zhijiao_delay==0){  
                  zhijiao_j=35;

               }
               zhijiao_delay=0;
      }
  }
  
  if(Left_Lose == 0&& Right_Lose==1){
       if(rigt==1||loseswitch==1) {
        if(left_old-left>3){
          black_line=black_line_old;
        } else{ 
          
             black_line =  left+21;  
       }
    right = left+40 ;
    shizi=0;
    
    Right_Lose_old = Right_Lose; 
    Left_Lose_old = 0;
       }
       rigt=1;
      if(zhijiao_j!=0){
        //直角
          zhijiao=1;
          zhijiao_j=0; 
         
          zhijiao_dl=-0.08*SPEED +25;
          if(zhijiao_dl<0) zhijiao_dl=0;
 
      }
      
        /*   if(qianzhan==0) {
         black_line = black_line_old+1;
     }  */

  } else {
   rigt=0;
  }
  if(Left_Lose == 1&& Right_Lose==0){
    if(lef==1||loseswitch==1){
        if(right-right_old>3){
        
                  black_line=black_line_old;
         }
         else{
               
             black_line =  right-21; 
        }
    left = right-40 ; 
    shizi=0;
    
    Left_Lose_old = Left_Lose;
    Right_Lose_old = 0;
    
  /*     if(qianzhan==0) {
         black_line = black_line_old-1;
     }  */

   }
    lef=1;
       if(zhijiao_j!=0){
        //直角
          zhijiao=-1;
          zhijiao_j=0; 
          
          zhijiao_dl=-0.08*SPEED +25;
         if(zhijiao_dl<0) zhijiao_dl=0;

       }
  } else{
    lef=0;
  }
  if(Left_Lose == 1&& Right_Lose==1) {
     
      
     if(Left_Lose_old==1){
       shizi=15;
     }
     if(Right_Lose_old==1){
       shizi=110;
     }

  }
  
  
        
  
  LED_PrintShort(30,7,(SHORT16) black_line);
  LED_PrintShort(30,3,(SHORT16) left);
  LED_PrintShort(30,5,(SHORT16) right);
  
  black_line_old = black_line; 

  
  if(zhijiao_j!=0)
     zhijiao_j--; 
  if(zhijiao_delay!=0)
     zhijiao_delay--; 
  if(zhijiao!=0) {
     zhijiao_delay=70;
     zhijiao_tmin=20; 
  }
  if(zhijiao_tmin!=0)
     zhijiao_tmin--;
  if(zhijiao_tmin==0){
     zhijiao =0;
  }
  

   quanhei=0;
  
   if(zhijiao_j!=0){
     PORTK_PK7 = 0;
   } else{
     PORTK_PK7 = 1;
   }
   

}


/*****************************************/
/*            方向控制函数               */
/*****************************************/
void Direction_Control(void)
{

   int i=0,j=0,b=0,bk=0;
   
   Direction_PWM_old =Direction_PWM;
   
   
   if(zhijiao==1&&zhijiao_dl==0) {
        if(SPEED>=250&&SPEED<=350){
          
          black_line=92;
        }
        if(SPEED>350){
          
          black_line=102;
        }
        if(SPEED>=200&&SPEED<250){
          
          black_line=90;
        }
        if(SPEED>=150&&SPEED<200){
          black_line=84;
        }
        if(SPEED>=100&&SPEED<150) {
           // if(zhijiao==2)
              black_line=82; 
        }
        if(SPEED<100) {
           // if(zhijiao==2)
            
              black_line=90;
         
        }
         // zhijiao--;
   }
   if(zhijiao==-1&&zhijiao_dl==0) {
        if(SPEED>=250&&SPEED<=350){
          
          black_line=40;
        }
        if(SPEED>350){
          
          black_line=30;
        }
        if(SPEED>=200&&SPEED<250){
          
          black_line=42;
        }
        if(SPEED>=150&&SPEED<200){        
          black_line=48;
        }
        if(SPEED>=100&&SPEED<150) {
           // if(zhijiao==-2)
               black_line=50;
        }
        if(SPEED<100) {
           // if(zhijiao==-2)
            
              black_line=42;
           
        }
       //   zhijiao++;
        
   }
   
      if(zhijiao_dl!=0)
       zhijiao_dl--;
      
      
    Kp_Direction=0.016*SPEED+6;                     ///速度关联p           0.015低速ok
    
    
      if(S_single_line==1) {
  
        /*   单线   */
      
   LED_P8x16Str(60, 1,(UCHAR8*)"nn") ;  
  for(i=107;i>=20;i--)
  {
    if((CCD_AD[i]-CCD_AD[i-2])>yuzhi-10)
    {   //PORTK_PK7 = 0;
      centre_lined =i-1;
         for(j=centre_lined;j>=centre_lined-10;j--)
           {
             if((CCD_AD[j-2]-CCD_AD[j])>yuzhi-7)
                 {
                      PORTK_PK7 = 0;
                  centre_lineu = (centre_lined+j+1)/2;
                  LED_P8x16Str(60, 0,(UCHAR8*)centre_lineu) ;
                         
               //   Kp_Direction=Kp_Direction*0.9;
      
                   black_line=centre_lineu;

                    b=1;
                   break; 
                 }
          }   

     if(b==1) break;  
    }
  }
  
  }
          /*   障碍  */
      if(Left_Lose == 0&&Right_Lose==0&&S_rock==1) {
      
 
  for(i=right_old+2;i>=left_old;i--)
  {
    if((CCD_AD[i-2]-CCD_AD[i])>yuzhi)
    {   //PORTK_PK7 = 0;
      rock_down =i-1;
         for(j=rock_down;j>=rock_down-13;j--)
           {
             if((CCD_AD[j]-CCD_AD[j-2])>yuzhi)
                 {
                      PORTK_PK7 = 0;
                  rock_up = (rock_down+j+1)/2;
                  LED_P8x16Str(60, 0,(UCHAR8*)centre_lineu) ;
                         
               //   Kp_Direction=Kp_Direction*0.9;
                 if(rock_up<66){
                  
                     rock_delay=-20;
                 }
                 if(rock_up>66){
                    
                   rock_delay=20;
                 }

                    bk=1;
                   break; 
                 }
          }   

     if(bk==1) break;  
    } else{
      rock_up=66;
    }
  }
      }
  
  if(rock_delay>0) {
    
   Kp_Direction=Kp_Direction*1.3;
     black_line=black_line-15;
   rock_delay--;
  }
  if(rock_delay<0) {
   Kp_Direction=Kp_Direction*1.3;

  black_line=black_line+15;
   rock_delay++;
  }

   
   direction_Erro[4]=direction_Erro[3];
   direction_Erro[3]=direction_Erro[2];
   direction_Erro[2]=direction_Erro[1];
   direction_Erro[1]=direction_Erro[0];
   direction_Erro[0]=(black_line-66);
   
  //  if(direction_Erro[0]>0)
 //    Kp_Direction =Kp_Direction_jc*(direction_Erro[0]*direction_Erro[0]/50);
  //  if(direction_Erro[0]<0)
  //   Kp_Direction= Kp_Direction*(1+direction_Erro[0]*direction_Erro[0]/10);


 /* */

    if(direction_Erro[0]>0)                      //////曲率偏差
    direction_Erro[0]=0.8*(black_line-66)+(black_line-66)*(black_line-66)/100;
    if(direction_Erro[0]<0)
    direction_Erro[0]=0.8*(black_line-66)-(black_line-66)*(black_line-66)/100;
    
  

   
      
   Direction_PWM =(int)(Kp_Direction*direction_Erro[0] + Kd_Direction * (direction_Erro[0]-direction_Erro[1])+Ki_Direction * (direction_Erro[0]-2*direction_Erro[1]+direction_Erro[2]));
/*  
   if(Direction_PWM>2000)
     Direction_PWM=2000;
   if(Direction_PWM<-2000)
     Direction_PWM=-2000;  
 */  
  
   Direction_PWM_inc =(Direction_PWM-Direction_PWM_old)/20;
   
   
       right_old=right;
    left_old=left;
}


/*************************************************************/
/*                        速度控制                          */
/*************************************************************/
void SpeedControl(void)
{
    int Location_Erro=0;
    Speed_PWM_old = Speed_PWM;

 
   //   Send_Speed(SPEED);

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
    } 
*/
/*    Location_Erro = black_line-64;
    if(Location_Erro<0)
      Location_Erro = -Location_Erro;
    
    Speed_Want = 200- Location_Erro*2;
    if(Speed_Want<170)
      Speed_Want = 170;
*/  
 /* Speed_Wanted*/ 
 

     SPEED = (SPEED_Aa+SPEED_Bb)/2;
 
    Speed_Erro[2] = Speed_Erro[1];
    Speed_Erro[1] = Speed_Erro[0];
    Speed_Wanted = Speed_Want - SPEED;
    
    SPEED_Aa = 0;
    SPEED_Bb = 0;

   /* if(Speed_Wanted>300 ){
       Speed_Wanted=300;
    }
    if(Speed_Wanted<-300 ){
       Speed_Wanted= -300;
    } */  
    Speed_Erro[0]=Speed_Wanted;  
   
  /*   */       if(lSpeedOut>=lLimitUH)
    {
        if( Speed_Erro[0]<0)
            lIntegral=lIntegral+Ki_Speed*(Speed_Erro[0]-2*Speed_Erro[1]+Speed_Erro[2]);       
    } 
    else {
      if(lSpeedOut<=lLimitUL)
    {
        if( Speed_Erro[0]>0)
            lIntegral=lIntegral+Ki_Speed* (Speed_Erro[0]-2*Speed_Erro[1]+Speed_Erro[2]);
    } 
    else
    {
        if( Speed_Erro[0]<400 &&  Speed_Erro[0]>-400)
            lIntegral=lIntegral+Ki_Speed* (Speed_Erro[0]-2*Speed_Erro[1]+Speed_Erro[2]);  
    }
    
     }
    
    if(lIntegral>lLimitIH)
        lIntegral=lLimitIH;
    else if(lIntegral<lLimitIL)
        lIntegral=lLimitIL;
  
    
    MORTOR_PWM = Kp_Speed*Speed_Erro[0] + Kd_Speed*(Speed_Erro[0]-Speed_Erro[1]) +lIntegral;
  

 /*   if(MORTOR_PWM >4000)
       MORTOR_PWM = 4000;
    if(MORTOR_PWM <-4000)
       MORTOR_PWM = -4000;
  */
    
    Speed_PWM= MORTOR_PWM;
    
    Speed_PWM_inc = (Speed_PWM - Speed_PWM_old)/20;
    ft=0;
  
    
}


/*************************************************************/
/*                        电机控制                          */
/*************************************************************/
void MortorControl(void)
{
   int MORTOR_A,MORTOR_B; 
    COUNT++;
   
   if(ft<=20){
   
     ft++;
     Speed_PWM_old += Speed_PWM_inc;
     
      Direction_PWM_old += Direction_PWM_inc;
      Direction_PWM_A =  Direction_PWM_old;                //左电机方向
      Direction_PWM_B = - Direction_PWM_old;                //右电机方向

   }
     

       MORTOR_A=(int)(gPWMMid+gPWMOutA-Speed_PWM_old+Direction_PWM_A);     //累加用old
       MORTOR_B=(int)(gPWMMid+gPWMOutA-Speed_PWM_old+Direction_PWM_B);
       
 /*    if(MORTOR_A >2000)
         MORTOR_A += 60;
       if(MORTOR_A <2000)
         MORTOR_A -= 60;
   */       
       if(MORTOR_B >2000)
         MORTOR_B += 40;
       if(MORTOR_B <2000)
         MORTOR_B -= 40;
      
       if(MORTOR_A >3800)
         MORTOR_A = 3800;
       if(MORTOR_A <200)
         MORTOR_A = 200;
      
       if(MORTOR_B >3800)
         MORTOR_B= 3800;
       if(MORTOR_B <200)
         MORTOR_B = 200;
       
     MORTOR_OUTA=MORTOR_A;
     MORTOR_OUTB=MORTOR_B;
   

    if(COUNT==5){
      
      COUNT=0;
      
      
      
    }
    
}




/*************************************************************************
*
*  函数名称：SendDataVisual
*  功能说明：发送数据到上位机VisualScope
*  参数说明：
*  函数返回：
*  修改时间：
*  备    注：最多发送四组数据，用于动态显示数据关系及变化规律
*************************************************************************/
void SendDataVisual(void)
{
  unsigned char DataArray[10],Buf[10];
  int temp[4]={0};
  unsigned int temp1[4]={0};
  unsigned char i;
  unsigned short CRC16=0;
  
      unsigned short CRC_Temp=0xffff;
          unsigned char o,j;


  
  //摄像头调试
  
  //直立控制调试
  temp[0]=(int)gRealAngle;//;angle_control,gyro2_ave
  temp[1]=(int)lZangle;//gyro2_value;Speed_Left
  temp[2]=(int)lGv;//MOTORA_PWM
  temp[3]=(int)lZv; //  
  
  //速度控制调试

  
  //直立速度控制
  
  for(i=0;i<4;i++)
    temp1[i]=(unsigned int)temp[i];
  
  for(i=0;i<4;i++)
  {
    DataArray[i*2]=(unsigned char)(temp1[i]%256);
    DataArray[i*2+1]=(unsigned char)(temp1[i]/256);
  }
  
 // CRC16=CRC_CHECK(DataArray,8);
  
      
      for(i=0;i<10;i++)
      Buf[i]= DataArray[i];
      
      
          for (o=0;o<8; o++){      
        CRC_Temp ^= Buf[o];
        for (j=0;j<8;j++) {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    CRC16=CRC_Temp;


  
  
  
  DataArray[8]=CRC16%256;
  DataArray[9]=CRC16/256;
  
  for(i=0;i<10;i++)
    SCI0_send(DataArray[i]);
}










/*****************************************/
/*            中断服务函数               */
/*****************************************/


#pragma CODE_SEG __NEAR_SEG NON_BANKED 
void interrupt 7 RTI_ISR(void)		  //函数映射关系
{  
   
    t++;
    

    if((20-Exposure_Time)>=2) 
    {
      if((20-Exposure_Time) == t)
      StartIntegration();
    }
    
    
   /* */ if((15-Exposure_Time1)>=3) 
    {
      if((15-Exposure_Time1) == t)
      {
        StartIntegration1();      
      }
    }
        
    
    if(t%5==5||t%5==0) {
      
         ReadSpeed();
         SPEED_Aa += SPEED_A;
         SPEED_Bb += SPEED_B;
    }
    
  /* */  GetAngleFun();                 //角度控制
     AngleControlFun();
    
     
     MortorControl(); 
   
    
//  SendDataVisual();              //直立调试
     
      
         
          black_l = Black_Check1;
          black_r = Black_Check2;
          
          if(black_l_old==1&&black_r_old==1){
            
          if(((black_l_old-black_l)==1)||((black_r_old-black_r)==1)) {
             
             quanhei=1;
          }
          }
          
          black_l_old = black_l;
          black_r_old = black_r;

    
    CRGFLG_RTIF = 1;               //清中断标志
  
}

#pragma CODE_SEG DEFAULT




#pragma CODE_SEG __NEAR_SEG NON_BANKED 

void interrupt 24 POTH_INT(void)		  //外部中断
{
  
    lCg =lGv;
  
  //  lCz =lZv;

}
#pragma CODE_SEG DEFAULT
