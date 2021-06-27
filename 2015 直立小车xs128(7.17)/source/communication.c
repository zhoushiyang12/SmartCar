/**********************************************************
 * �ļ���       ��communication.c
 * ����         ����λ��ͨ�ź���
 * ��ע         ��
 * ��汾       ��
 * ����         ��hfh
**********************************************************/	
#include "communication.h"

/**********************************************************


/*************************************************************************
*
*  �������ƣ�SendDataVisual
*  ����˵�����������ݵ���λ��VisualScope
*  ����˵����
*  �������أ�
*  �޸�ʱ�䣺
*  ��    ע����෢���������ݣ����ڶ�̬��ʾ���ݹ�ϵ���仯����
/*************************************************************************/
void SendDataVisual(void)
{
  unsigned char DataArray[10];
  int temp[4]={0};
  unsigned int temp1[4]={0};
  unsigned char i;
  unsigned short CRC16=0;
  
  //����ͷ����
  /*temp[0]=(int)line_count;
  temp[1]=(int)line_get_count;
  temp[2]=(int)line_process_count;
  temp[3]=(int)line_count; */  
  
  //ֱ�����Ƶ���
  temp[0]=(int)gyro1_ave;//;angle_control,gyro2_ave
  temp[1]=(int)car_angle;//gyro2_value;Speed_Left
  temp[2]=(int)acc_value;//MOTORA_PWM
  temp[3]=(int)acc_ave; //  
  
  //�ٶȿ��Ƶ���
  /*temp[0]=(int)Speed_Left;
  temp[1]=(int)Speed_Right;
  temp[2]=(int)car_angle;//angle_control;Speed_Left_Old��MOTORA_PWM
  temp[3]=(int)acc_ave;//MOTORB_PWM;Speed_Right_Oldy*/

  
  //ֱ���ٶȿ���
  /*temp[0]=speed_control;//gyro1_value;
  temp[1]=(int)angle_control;//gyro2_value;
  temp[2]=(int)car_angle;
  temp[3]=MOTORB_PWM;// LastSpeed*/
  //������Ƶ���
  
  for(i=0;i<4;i++)
    temp1[i]=(unsigned int)temp[i];
  
  for(i=0;i<4;i++)
  {
    DataArray[i*2]=(unsigned char)(temp1[i]%256);
    DataArray[i*2+1]=(unsigned char)(temp1[i]/256);
  }
  
  CRC16=CRC_CHECK(DataArray,8);
  DataArray[8]=CRC16%256;
  DataArray[9]=CRC16/256;
  
  for(i=0;i<10;i++)
    uart_putchar(UART_CH,DataArray[i]);
}

/*************************************************************************
*
*  �������ƣ�CRC_CHECK
*  ����˵��������CRCУ���뺯��
*  ����˵����
*  �������أ�
*  �޸�ʱ�䣺
*  ��    ע����������λ��ͨѶ����SendDataVisual�����е���
*************************************************************************/
unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i,j;
    CRC_Temp = 0xffff;

    for (i=0;i<CRC_CNT; i++){      
        CRC_Temp ^= Buf[i];
        for (j=0;j<8;j++) {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
}