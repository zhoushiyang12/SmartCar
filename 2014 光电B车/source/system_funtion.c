/******************************************************************************

          ��Ȩ���� (C), 2011-2012, ������ӿƼ�(http://xydz123.taobao.com/)

 ******************************************************************************
  �� �� ��   : system_funtion.c
  �� �� ��   : v2.0
  ��    ��   : Guokaiyi
  ��������   : 2012-12-1
  ����޸�   : 
  ��������   : оƬ�ڲ����ܺ���
  �޸���ʷ   :
  1.��    ��   : 2012-11-12
    ��    ��   : Guokaiyi
    �޸�����   : �����ļ�
    
  2.��    ��   : 2012-12-1
    ��    ��   : Guokaiyi
    �޸�����   : ����DFLASH���ܺ���

******************************************************************************/

/*----------------------------------------------------------------------------*
 * ����ͷ�ļ�                                                                 *
 *----------------------------------------------------------------------------*/
#include "system_funtion.h"

/*----------------------------------------------------------------------------*
 * �궨��                                                                     *
 *----------------------------------------------------------------------------*/
#define FLASH_DFLASH_GLOBAL_ADDR_BASE   0x0010
#define FLASH_DFLASH_LOCAL_ADDR_BASE    0x0800
#define FLASH_DFLASH_PAGE_SIZE          0x0400  // 1Kbytes
/*----------------------------------------------------------------------------*
 * ö�ٶ���                                                                     *
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
 * ȫ�ֱ���                                                                   *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * �ڲ�����ԭ��                                                               *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
 * �ⲿ����ԭ��                                                               *
 *----------------------------------------------------------------------------*/


/*****************************************************************************
 �� �� ��  : PLL_Init
 ��������  : ��ʼ�����໷
 �������  : NONE  
 �������  : NONE
 �� �� ֵ  : NONE
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

    REFDV  = 0xC1;            //PLLCLK=2��OSCCLK��(SYNR+1)/(REFDV+1)��128MHz ,fbus=32M
    PLLCTL = PLLCTL | 0x70;   //Enable PLL circuit
    
    asm NOP;
    asm NOP;
    
    while (!(CRGFLG & 0x08)); //PLLCLK is Locked already
    CLKSEL |= 0x80;           //set PLLCLK as sysclk

    return;
}

/*************************************************************/
/*                        �ж϶�ʱ                           */
/*************************************************************/
void Init_RTI(void)         //����5ms (10ms)�ж�     �ж�Ƶ��=16MHz/(RTICTL��Ӧ�ı���ֵ)
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
                         //RTIʹ��
}



/************************************************************/
/*                   ��ʼ���ⲿ�ж�                         */
/************************************************************/
void Init_POTJ_Int(void)
{
    PPSJ_PPSJ0 = 0;  //�½��ش����ж�
    PIEJ_PIEJ0 = 1;  //�����ж�
    
}


/*************************************************************/
/*                      �ⲿ�������                         */
/*************************************************************/
void Init_PulseACC(void)  
{
    TSCR1_TFFCA=1;      //��TSCR1_TFFCA=1�����PACNT��ʹPAFLG_PAOVF����
    PACTL_PAEN=0;       //�ر������ۼ���A
    PACNT=0X00;         //�����ۼ���A����
    PACTL=0X50;         //�����ۼ�ʹ�ܣ��¼������������ش�����ʹ������ʱ�ӣ������ж�
}

/*************************************************************/
/*                        ��ʼ��PWM                          */
/*************************************************************/
void init_pwm(void) 
{
  PWME=0x00; 

                     //2367 B SB   0145 A SA
                     // 1 3 MORTOR   5 7 ���
  PWMCLK   = 0xb0;   //45��SAʱ����Ϊʱ��Դ��01��23��A,Bʱ�� 67��SBʱ��
  PWMPRCLK = 0x00;   //Aʱ�ӵķ�Ƶϵ��Ϊ0,Ƶ��Ϊ80MHz   Bʱ�ӷ�Ƶϵ��Ϊ0��Ƶ��Ϊ80MHZ
  
  PWMPOL_PPOL1= 1;   //ͨ���ļ���Ϊ�ߵ�ƽ��Ч
  PWMPOL_PPOL3= 1;   //ͨ���ļ���Ϊ�ߵ�ƽ��Ч
  PWMPOL_PPOL5= 1;   //ͨ���ļ���Ϊ�ߵ�ƽ��Ч
  PWMPOL_PPOL7= 1;   //ͨ���ļ���Ϊ�ߵ�ƽ��Ч
  
  PWMCAE   = 0x00;   //����ģʽΪ�����ģʽ
  
  PWMCTL_CON01= 1;   //ͨ��01Ϊ16λ��PWM
  PWMCTL_CON23= 1;   //ͨ��23Ϊ16λ��PWM
  PWMCTL_CON45= 1;   //ͨ��45Ϊ16λ��PWM
  PWMCTL_CON67= 1;   //ͨ��67Ϊ16λ��PWM
  
  PWMSCLA  =    100;   //SAʱ��Ƶ��Ϊ400kHz  SA=A/(2*PWMSCLA)
  PWMSCLB  =    100;   //SBʱ��Ƶ��Ϊ400kHz  SB=B/(2*PWMSCLB)
  
  PWMPER01  =  4000;   //ͨ��1��Ƶ��Ϊ20KHz,���ڵ�������� 
  PWMPER23  =  4000;   //ͨ��3��Ƶ��Ϊ20KHz,���ڵ�������� 
  PWMPER45  =  4000;   //Ƶ��100Hz������ת����������
  PWMPER67  =  4000;   //Ƶ��100Hz������ҡͷ���������
  
  
  PWMDTY01  = 2000;    //ͨ��01��ռ�ձ�����  
  PWMDTY23  = 2000;    //ͨ��23��ռ�ձ�����
  PWMDTY45  = 615;     //ͨ��45��ռ�ձ�����
  PWMDTY67  = 645;     //ͨ��67��ռ�ձ�����    ����
// if(PORTA_PA0 == 0)
 // PWMDTY67  = 250;     //ͨ��67��ռ�ձ�����   ����
  PWME=0xff ;         //PWMʹ��
}


/*************************************************************/
/*                        ��ʼ��SCI0                         */
/*************************************************************/
void INIT_SCI0(void) 
{
  SCI0BD = SYSTEM_BUS_CLOCK/16/SYSTEM_BAUD;   //����SCI0������Ϊ115200
  SCI0CR1 = 0x00;        //����SCI0Ϊ����ģʽ����λ����λ������żУ��
  SCI0CR2 = 0x0c;        //������պͷ�������
}
/*************************************************************/
/*                       ���ڷ��ͺ���                        */
/*************************************************************/
void SCI0_send(unsigned char data) 
{
  while(!SCI0SR1_TDRE);         //�ȴ��������ݼĴ�������������Ϊ��
  SCI0DRL = data;
}


/*************************************************************/
/*                      ��ʼ��ADģ��                         */
/*************************************************************/
void INIT_AD(void) 
{
    ATD0CTL4 = 0x04;                    /* ADģ��ʱ��Ƶ��Ϊ8MHz */
    ATD0CTL3 = 0x88;                    /* �����Ҷ���,ת�����г���Ϊ 1 */
    ATD0CTL0 = 0x0F;                    /* Set wrap around ����ͨ�� */
    ATD0CTL1 = 0x0F;                    /* 8-bit data */
    ATD0CTL2 = 0x40;                    /* ����������б�־λ */
}

/*************************************************************/
/*                        ��ADת��                         */
/*************************************************************/
unsigned char AD_capture(unsigned char chanel) 
{
    ATD0CTL5_Cx= chanel;
    while(ATD0STAT0_SCF == 0);
    return ATD0DR0L;
 
}

/*****************************************************************************
 �� �� ��  : SYSTEM_TIME_Delay
 ��������  : ��ʱ���� 
 �������  : USHORT16 usTime
 �������  : NONE
 �� �� ֵ  : NONE
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
 �� �� ��  : SYSTEM_DFLASH_Init
 ��������  : оƬ�ڲ�DFlash��ʼ��
 �������  : NONE  
 �������  : NONE
 �� �� ֵ  : NONE
*****************************************************************************/
VOID SYSTEM_DFLASH_Init(VOID)  
{    
    while (!FSTAT_CCIF);      //������FLASH�Ĵ���д��ǰ���豣֤CCIF��Ϊ0���ϴ��������
    FCLKDIV = 0x0F;           //�ⲿ����Ϊ16M.FLASHʱ�Ӳ�����1M����������ֲ�  
    FCNFG   = 0x00;           //��ֹ�ж�  
    while (!FCLKDIV_FDIVLD);  //�ȴ�ʱ�����óɹ�

    return;
}  

/*****************************************************************************
 �� �� ��  : SYSTEM_DFLASH_Erase
 ��������  : ����DFLASH��һ������
             S12XS128��DFLASH����32��������ÿ����265 bytes����8Kbytes
             ����  ��ʼ��ַ�ĵ�16λ
               0:  0x0000     1:  0x0100     2:  0x0200     3:  0x0300
               4:  0x0400     5:  0x0500     6:  0x0600     7:  0x0700
               8:  0x0800     9:  0x0900    10:  0x0A00    11:  0x0B00
              12:  0x0C00    13:  0x0D00    14:  0x0E00    15:  0x0F00
              16:  0x1000    17:  0x1100    18:  0x1200    19:  0x1300
              20:  0x1400    21:  0x1500    22:  0x1600    23:  0x1700
              24:  0x1800    25:  0x1900    26:  0x1A00    27:  0x1B00
              28:  0x1C00    29:  0x1D00    30:  0x1E00    31:  0x1F00

 �������  : USHORT16 usAddress ��ѡ��������ʼ��ַ�ĵ�16λ
 �������  : NONE
 �� �� ֵ  : NONE
*****************************************************************************/
VOID SYSTEM_DFLASH_Erase(USHORT16 usAddress)
{
    while (!FSTAT_CCIF);     //������FLASH�Ĵ���д��ǰ���豣֤CCIF��Ϊ0���ϴ��������
    if (1 == FSTAT_ACCERR)   //�ж϶�д�����־
    {
        FSTAT_ACCERR = 1;    //�����־λ
    }
    if (1 == FSTAT_FPVIOL)   //�жϱ���Υ����־
    {
        FSTAT_FPVIOL = 1;    //�����־λ
    }
    
    FCCOBIX_CCOBIX = 0x00; 
    FCCOB = ((USHORT16)FLASH_ERASE_DFLASH_SECTOR << 8) | FLASH_DFLASH_GLOBAL_ADDR_BASE; //д������͸�λ��ַ  
    FCCOBIX_CCOBIX = 0x01;   
    FCCOB = usAddress;       //д���16λ��ַ 
    
    FSTAT_CCIF=1;            //����ִ������  
    while (!FSTAT_CCIF);     //�ȴ�ִ�����  

    return;
}  

/*****************************************************************************
 �� �� ��  : SYSTEM_DFLASH_Write
 ��������  : ��оƬ�ڲ�DFlashд�����ݣ�����д�����ݵĿռ�д��ǰ�����������д��ʧ��
 �������  : USHORT16 usAddress   0x0000 - 0x1FF8
             USHORT16 *pusDataBuf ����4words(8bytes)�Ļ����ַ
 �������  : NONE
 �� �� ֵ  : NONE
*****************************************************************************/
VOID SYSTEM_DFLASH_Write(USHORT16 usAddress, USHORT16 *pusDataBuf)  
{  
    while (!FSTAT_CCIF);     //������FLASH�Ĵ���д��ǰ���豣֤CCIF��Ϊ0���ϴ��������
    if(1 == FSTAT_ACCERR)    //�ж϶�д�����־
    {
        FSTAT_ACCERR = 1;    //�����־λ
    }
    if(1 == FSTAT_FPVIOL)    //�жϱ���Υ����־
    {
        FSTAT_FPVIOL = 1;    //�����־λ
    }

    FCCOBIX_CCOBIX = 0x00;   
    FCCOB = ((USHORT16)FLASH_PROGRAM_DFLASH << 8) | FLASH_DFLASH_GLOBAL_ADDR_BASE; //д������͸�λ��ַ 
    FCCOBIX_CCOBIX = 0x01;   
    FCCOB = usAddress;       //д���16λ��ַ  
    FCCOBIX_CCOBIX = 0x02;   
    FCCOB = pusDataBuf[0];   //д���һ������  
    FCCOBIX_CCOBIX = 0x03;   
    FCCOB = pusDataBuf[1];   //д��ڶ�������  
    FCCOBIX_CCOBIX = 0x04;   
    FCCOB = pusDataBuf[2];   //д�����������  
    FCCOBIX_CCOBIX = 0x05;   
    FCCOB = pusDataBuf[3];   //д����ĸ�����  

    FSTAT_CCIF = 1;          //д��ִ������  
    while (!FSTAT_CCIF);     //�ȴ�ִ�����  

    return;
}  
  
/*****************************************************************************
 �� �� ��  : SYSTEM_DFLASH_Read
 ��������  : ��оƬ�ڲ�DFlash��������
 �������  : USHORT16 usAddress   0x0000 - 0x1FF8 
             USHORT16 *pusDataBuf ����4words(8bytes)�Ļ����ַ
 �������  : NONE
 �� �� ֵ  : NONE
*****************************************************************************/
VOID SYSTEM_DFLASH_Read(USHORT16 usAddress, USHORT16 *pusDataBuf)  
{  
    UCHAR8 ucLastEpage;
    USHORT16 *pusMapAddr;

    ucLastEpage = EPAGE;     //����EPAGE��ֵ  

    EPAGE = (UCHAR8)(usAddress >> 10); //����EPAGE  

    //����usAddressӳ�䵽CPU�ڴ�ĵ�ַ
    pusMapAddr = (USHORT16*)(FLASH_DFLASH_LOCAL_ADDR_BASE + (usAddress & (FLASH_DFLASH_PAGE_SIZE - 1))); 

    pusDataBuf[0] = *pusMapAddr;
    pusDataBuf[1] = *(pusMapAddr + 1);
    pusDataBuf[2] = *(pusMapAddr + 2);
    pusDataBuf[3] = *(pusMapAddr + 3);

    EPAGE = ucLastEpage;      //�ָ�EPAGE��ֵ  

    return;
}  

