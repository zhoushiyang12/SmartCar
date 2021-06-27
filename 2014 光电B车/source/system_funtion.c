/******************************************************************************

          版权所有 (C), 2011-2012, 信意电子科技(http://xydz123.taobao.com/)

 ******************************************************************************
  文 件 名   : system_funtion.c
  版 本 号   : v2.0
  作    者   : Guokaiyi
  生成日期   : 2012-12-1
  最近修改   : 
  功能描述   : 芯片内部功能函数
  修改历史   :
  1.日    期   : 2012-11-12
    作    者   : Guokaiyi
    修改内容   : 创建文件
    
  2.日    期   : 2012-12-1
    作    者   : Guokaiyi
    修改内容   : 增加DFLASH功能函数

******************************************************************************/

/*----------------------------------------------------------------------------*
 * 包含头文件                                                                 *
 *----------------------------------------------------------------------------*/
#include "system_funtion.h"

/*----------------------------------------------------------------------------*
 * 宏定义                                                                     *
 *----------------------------------------------------------------------------*/
#define FLASH_DFLASH_GLOBAL_ADDR_BASE   0x0010
#define FLASH_DFLASH_LOCAL_ADDR_BASE    0x0800
#define FLASH_DFLASH_PAGE_SIZE          0x0400  // 1Kbytes
/*----------------------------------------------------------------------------*
 * 枚举定义                                                                     *
 *----------------------------------------------------------------------------*/
enum tagSystemFlashCmd
{
    FLASH_ERASE_VERIFY_ALL_BLOCKS     = 0x01,
    FLASH_ERASE_VERIFY_BLOCK          = 0x02,
    FLASH_ERASE_VERIFY_PFLASH_SECTION = 0x03,
    FLASH_READ_ONCE                   = 0x04,
    FLASH_PROGRAM_PFLASH              = 0x06,
    FLASH_PROGRAM_ONCE                = 0x07,
    FLASH_ERASE_ALL_BLOCKS            = 0x08,
    FLASH_ERASE_FLASH_BLOCK           = 0x09,
    FLASH_ERASE_PFLASH_SECTOR         = 0x0A,
    FLASH_UNSECURE_FLASH              = 0x0B,
    FLASH_VERIFY_BACKDOOR_ACCESS_KEY  = 0x0C,
    FLASH_SET_USER_MARGIN_LEVEL       = 0x0D,
    FLASH_SET_FIELD_MARGIN_LEVEL      = 0x0E,
    FLASH_ERASE_VERIFY_DFLASH_SECTION = 0x10,
    FLASH_PROGRAM_DFLASH              = 0x11,
    FLASH_ERASE_DFLASH_SECTOR         = 0x12,
}SystemFlashCmd_E;

/*----------------------------------------------------------------------------*
 * 全局变量                                                                   *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * 内部函数原型                                                               *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * 外部函数原型                                                               *
 *----------------------------------------------------------------------------*/


/*****************************************************************************
 函 数 名  : PLL_Init
 功能描述  : 初始化锁相环
 输入参数  : NONE  
 输出参数  : NONE
 返 回 值  : NONE
*****************************************************************************/
VOID SYSTEM_PLL_Init(VOID) 
{
    CLKSEL &= 0x7f;       //set OSCCLK as sysclk
    PLLCTL &= 0x8F;       //Disable PLL circuit
    CRGINT &= 0xDF;

    #if  (SYSTEM_BUS_CLOCK == 120000000) 
      SYNR = 0xcd;
    #elif(SYSTEM_BUS_CLOCK == 104000000) 
      SYNR = 0xcc;
    #elif(SYSTEM_BUS_CLOCK == 96000000) 
      SYNR = 0xcb;
    #elif(SYSTEM_BUS_CLOCK == 88000000) 
      SYNR = 0xca;
    #elif(SYSTEM_BUS_CLOCK == 80000000) 
      SYNR = 0xc9;
    #elif(SYSTEM_BUS_CLOCK == 72000000) 
      SYNR = 0xc8;
    #elif(SYSTEM_BUS_CLOCK == 64000000)
      SYNR = 0xc7;     
    #elif(SYSTEM_BUS_CLOCK == 40000000) 
      SYNR = 0x44;
    #elif(SYSTEM_BUS_CLOCK == 24000000)
      SYNR = 0x42;
    #endif 

    REFDV  = 0xC1;            //PLLCLK=2×OSCCLK×(SYNR+1)/(REFDV+1)＝128MHz ,fbus=32M
    PLLCTL = PLLCTL | 0x70;   //Enable PLL circuit
    
    asm NOP;
    asm NOP;
    
    while (!(CRGFLG & 0x08)); //PLLCLK is Locked already
    CLKSEL |= 0x80;           //set PLLCLK as sysclk

    return;
}

/*************************************************************/
/*                        中断定时                           */
/*************************************************************/
void Init_RTI(void)         //产生5ms (10ms)中断     中断频率=16MHz/(RTICTL对应的表格的值)
{
   
   
    #if(INTERRUPT_TIME == 20) 
      RTICTL = 0xCF;
    #elif(INTERRUPT_TIME == 12.5) 
      RTICTL = 0xC9;
    #elif(INTERRUPT_TIME == 10) 
      RTICTL = 0xC7;
    #elif(INTERRUPT_TIME == 5) 
      RTICTL = 0xB7;
    #elif(INTERRUPT_TIME == 2.5)
      RTICTL = 0xB3;     
    #elif(INTERRUPT_TIME == 2) 
      RTICTL = 0x9F;
    #elif(INTERRUPT_TIME == 1)
      RTICTL = 0x97;
    #endif 
    
                         //1011 0111   200HZ,5ms   /////// 16M/(80*10~3)
                         //1001 0111   1000Hz,1ms   0x97
                         //1011 0011   400Hz,2.5ms  0xB3
                         //1100 0111   100HZ,10ms   0xC7                    
   CRGINT|= 0x80;       //0:interrupt disable
                         //1:interrupt enable 26 
                         //RTI使能
}



/************************************************************/
/*                   初始化外部中断                         */
/************************************************************/
void Init_POTJ_Int(void)
{
    PPSJ_PPSJ0 = 0;  //下降沿触发中断
    PIEJ_PIEJ0 = 1;  //允许中断
    
}


/*************************************************************/
/*                      外部脉冲计数                         */
/*************************************************************/
void Init_PulseACC(void)  
{
    TSCR1_TFFCA=1;      //若TSCR1_TFFCA=1，则读PACNT会使PAFLG_PAOVF清零
    PACTL_PAEN=0;       //关闭脉冲累加器A
    PACNT=0X00;         //脉冲累加器A清零
    PACTL=0X50;         //脉冲累加使能，事件计数，上升沿触发，使用总线时钟，禁用中断
}

/*************************************************************/
/*                        初始化PWM                          */
/*************************************************************/
void init_pwm(void) 
{
  PWME=0x00; 

                     //2367 B SB   0145 A SA
                     // 1 3 MORTOR   5 7 舵机
  PWMCLK   = 0xb0;   //45用SA时钟作为时钟源，01、23用A,B时钟 67用SB时钟
  PWMPRCLK = 0x00;   //A时钟的分频系数为0,频率为80MHz   B时钟分频系数为0，频率为80MHZ
  
  PWMPOL_PPOL1= 1;   //通道的极性为高电平有效
  PWMPOL_PPOL3= 1;   //通道的极性为高电平有效
  PWMPOL_PPOL5= 1;   //通道的极性为高电平有效
  PWMPOL_PPOL7= 1;   //通道的极性为高电平有效
  
  PWMCAE   = 0x00;   //脉冲模式为左对齐模式
  
  PWMCTL_CON01= 1;   //通道01为16位的PWM
  PWMCTL_CON23= 1;   //通道23为16位的PWM
  PWMCTL_CON45= 1;   //通道45为16位的PWM
  PWMCTL_CON67= 1;   //通道67为16位的PWM
  
  PWMSCLA  =    100;   //SA时钟频率为400kHz  SA=A/(2*PWMSCLA)
  PWMSCLB  =    100;   //SB时钟频率为400kHz  SB=B/(2*PWMSCLB)
  
  PWMPER01  =  4000;   //通道1的频率为20KHz,用于电机的驱动 
  PWMPER23  =  4000;   //通道3的频率为20KHz,用于电机的驱动 
  PWMPER45  =  4000;   //频率100Hz，用于转向舵机的驱动
  PWMPER67  =  4000;   //频率100Hz，用于摇头舵机的驱动
  
  
  PWMDTY01  = 2000;    //通道01的占空比设置  
  PWMDTY23  = 2000;    //通道23的占空比设置
  PWMDTY45  = 615;     //通道45的占空比设置
  PWMDTY67  = 645;     //通道67的占空比设置    正向
// if(PORTA_PA0 == 0)
 // PWMDTY67  = 250;     //通道67的占空比设置   反向
  PWME=0xff ;         //PWM使能
}


/*************************************************************/
/*                        初始化SCI0                         */
/*************************************************************/
void INIT_SCI0(void) 
{
  SCI0BD = SYSTEM_BUS_CLOCK/16/SYSTEM_BAUD;   //设置SCI0波特率为115200
  SCI0CR1 = 0x00;        //设置SCI0为正常模式，八位数据位，无奇偶校验
  SCI0CR2 = 0x0c;        //允许接收和发送数据
}
/*************************************************************/
/*                       串口发送函数                        */
/*************************************************************/
void SCI0_send(unsigned char data) 
{
  while(!SCI0SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空
  SCI0DRL = data;
}


/*************************************************************/
/*                      初始化AD模块                         */
/*************************************************************/
void INIT_AD(void) 
{
    ATD0CTL4 = 0x04;                    /* AD模块时钟频率为8MHz */
    ATD0CTL3 = 0x88;                    /* 数据右对齐,转换序列长度为 1 */
    ATD0CTL0 = 0x0F;                    /* Set wrap around 所有通道 */
    ATD0CTL1 = 0x0F;                    /* 8-bit data */
    ATD0CTL2 = 0x40;                    /* 快速清除所有标志位 */
}

/*************************************************************/
/*                        起动AD转换                         */
/*************************************************************/
unsigned char AD_capture(unsigned char chanel) 
{
    ATD0CTL5_Cx= chanel;
    while(ATD0STAT0_SCF == 0);
    return ATD0DR0L;
 
}

/*****************************************************************************
 函 数 名  : SYSTEM_TIME_Delay
 功能描述  : 延时函数 
 输入参数  : USHORT16 usTime
 输出参数  : NONE
 返 回 值  : NONE
*****************************************************************************/
VOID SYSTEM_TIME_Delay(USHORT16 usTime)
{
    ULONG32 i;
    USHORT16 j;
    
    for (i = (ULONG32)100 * usTime; i > 0; i--)
    {
        for(j = 210; j > 0; j--)
        {
        }
    }
    
    return;
}
  
/*****************************************************************************
 函 数 名  : SYSTEM_DFLASH_Init
 功能描述  : 芯片内部DFlash初始化
 输入参数  : NONE  
 输出参数  : NONE
 返 回 值  : NONE
*****************************************************************************/
VOID SYSTEM_DFLASH_Init(VOID)  
{    
    while (!FSTAT_CCIF);      //向任意FLASH寄存器写入前都需保证CCIF不为0即上次命令完成
    FCLKDIV = 0x0F;           //外部晶振为16M.FLASH时钟不超过1M，具体参照手册  
    FCNFG   = 0x00;           //禁止中断  
    while (!FCLKDIV_FDIVLD);  //等待时钟设置成功

    return;
}  

/*****************************************************************************
 函 数 名  : SYSTEM_DFLASH_Erase
 功能描述  : 擦除DFLASH的一个扇区
             S12XS128的DFLASH共有32个扇区，每扇区265 bytes，共8Kbytes
             扇区  起始地址的低16位
               0:  0x0000     1:  0x0100     2:  0x0200     3:  0x0300
               4:  0x0400     5:  0x0500     6:  0x0600     7:  0x0700
               8:  0x0800     9:  0x0900    10:  0x0A00    11:  0x0B00
              12:  0x0C00    13:  0x0D00    14:  0x0E00    15:  0x0F00
              16:  0x1000    17:  0x1100    18:  0x1200    19:  0x1300
              20:  0x1400    21:  0x1500    22:  0x1600    23:  0x1700
              24:  0x1800    25:  0x1900    26:  0x1A00    27:  0x1B00
              28:  0x1C00    29:  0x1D00    30:  0x1E00    31:  0x1F00

 输入参数  : USHORT16 usAddress 所选扇区的起始地址的低16位
 输出参数  : NONE
 返 回 值  : NONE
*****************************************************************************/
VOID SYSTEM_DFLASH_Erase(USHORT16 usAddress)
{
    while (!FSTAT_CCIF);     //向任意FLASH寄存器写入前都需保证CCIF不为0即上次命令完成
    if (1 == FSTAT_ACCERR)   //判断读写错误标志
    {
        FSTAT_ACCERR = 1;    //清除标志位
    }
    if (1 == FSTAT_FPVIOL)   //判断保护违反标志
    {
        FSTAT_FPVIOL = 1;    //清除标志位
    }
    
    FCCOBIX_CCOBIX = 0x00; 
    FCCOB = ((USHORT16)FLASH_ERASE_DFLASH_SECTOR << 8) | FLASH_DFLASH_GLOBAL_ADDR_BASE; //写入命令和高位地址  
    FCCOBIX_CCOBIX = 0x01;   
    FCCOB = usAddress;       //写入低16位地址 
    
    FSTAT_CCIF=1;            //启动执行命令  
    while (!FSTAT_CCIF);     //等待执行完成  

    return;
}  

/*****************************************************************************
 函 数 名  : SYSTEM_DFLASH_Write
 功能描述  : 向芯片内部DFlash写入数据，向已写入数据的空间写入前需擦除，否则写入失败
 输入参数  : USHORT16 usAddress   0x0000 - 0x1FF8
             USHORT16 *pusDataBuf 大于4words(8bytes)的缓存地址
 输出参数  : NONE
 返 回 值  : NONE
*****************************************************************************/
VOID SYSTEM_DFLASH_Write(USHORT16 usAddress, USHORT16 *pusDataBuf)  
{  
    while (!FSTAT_CCIF);     //向任意FLASH寄存器写入前都需保证CCIF不为0即上次命令完成
    if(1 == FSTAT_ACCERR)    //判断读写错误标志
    {
        FSTAT_ACCERR = 1;    //清除标志位
    }
    if(1 == FSTAT_FPVIOL)    //判断保护违反标志
    {
        FSTAT_FPVIOL = 1;    //清除标志位
    }

    FCCOBIX_CCOBIX = 0x00;   
    FCCOB = ((USHORT16)FLASH_PROGRAM_DFLASH << 8) | FLASH_DFLASH_GLOBAL_ADDR_BASE; //写入命令和高位地址 
    FCCOBIX_CCOBIX = 0x01;   
    FCCOB = usAddress;       //写入低16位地址  
    FCCOBIX_CCOBIX = 0x02;   
    FCCOB = pusDataBuf[0];   //写入第一个数据  
    FCCOBIX_CCOBIX = 0x03;   
    FCCOB = pusDataBuf[1];   //写入第二个数据  
    FCCOBIX_CCOBIX = 0x04;   
    FCCOB = pusDataBuf[2];   //写入第三个数据  
    FCCOBIX_CCOBIX = 0x05;   
    FCCOB = pusDataBuf[3];   //写入第四个数据  

    FSTAT_CCIF = 1;          //写入执行命令  
    while (!FSTAT_CCIF);     //等待执行完毕  

    return;
}  
  
/*****************************************************************************
 函 数 名  : SYSTEM_DFLASH_Read
 功能描述  : 从芯片内部DFlash读出数据
 输入参数  : USHORT16 usAddress   0x0000 - 0x1FF8 
             USHORT16 *pusDataBuf 大于4words(8bytes)的缓存地址
 输出参数  : NONE
 返 回 值  : NONE
*****************************************************************************/
VOID SYSTEM_DFLASH_Read(USHORT16 usAddress, USHORT16 *pusDataBuf)  
{  
    UCHAR8 ucLastEpage;
    USHORT16 *pusMapAddr;

    ucLastEpage = EPAGE;     //保存EPAGE的值  

    EPAGE = (UCHAR8)(usAddress >> 10); //计算EPAGE  

    //计算usAddress映射到CPU内存的地址
    pusMapAddr = (USHORT16*)(FLASH_DFLASH_LOCAL_ADDR_BASE + (usAddress & (FLASH_DFLASH_PAGE_SIZE - 1))); 

    pusDataBuf[0] = *pusMapAddr;
    pusDataBuf[1] = *(pusMapAddr + 1);
    pusDataBuf[2] = *(pusMapAddr + 2);
    pusDataBuf[3] = *(pusMapAddr + 3);

    EPAGE = ucLastEpage;      //恢复EPAGE的值  

    return;
}  

