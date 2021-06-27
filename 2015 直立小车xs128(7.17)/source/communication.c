/**********************************************************
 * 文件名       ：communication.c
 * 描述         ：上位机通信函数
 * 备注         ：
 * 库版本       ：
 * 作者         ：hfh
**********************************************************/	
#include "communication.h"

/**********************************************************


/*************************************************************************
*
*  函数名称：SendDataVisual
*  功能说明：发送数据到上位机VisualScope
*  参数说明：
*  函数返回：
*  修改时间：
*  备    注：最多发送四组数据，用于动态显示数据关系及变化规律
/*************************************************************************/
void SendDataVisual(void)
{
  unsigned char DataArray[10];
  int temp[4]={0};
  unsigned int temp1[4]={0};
  unsigned char i;
  unsigned short CRC16=0;
  
  //摄像头调试
  /*temp[0]=(int)line_count;
  temp[1]=(int)line_get_count;
  temp[2]=(int)line_process_count;
  temp[3]=(int)line_count; */  
  
  //直立控制调试
  temp[0]=(int)gyro1_ave;//;angle_control,gyro2_ave
  temp[1]=(int)car_angle;//gyro2_value;Speed_Left
  temp[2]=(int)acc_value;//MOTORA_PWM
  temp[3]=(int)acc_ave; //  
  
  //速度控制调试
  /*temp[0]=(int)Speed_Left;
  temp[1]=(int)Speed_Right;
  temp[2]=(int)car_angle;//angle_control;Speed_Left_Old，MOTORA_PWM
  temp[3]=(int)acc_ave;//MOTORB_PWM;Speed_Right_Oldy*/

  
  //直立速度控制
  /*temp[0]=speed_control;//gyro1_value;
  temp[1]=(int)angle_control;//gyro2_value;
  temp[2]=(int)car_angle;
  temp[3]=MOTORB_PWM;// LastSpeed*/
  //方向控制调试
  
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
*  函数名称：CRC_CHECK
*  功能说明：计算CRC校验码函数
*  参数说明：
*  函数返回：
*  修改时间：
*  备    注：用于与上位机通讯，在SendDataVisual函数中调用
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