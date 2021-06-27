#include "anglecontrol.h"
#include "system_funtion.h"
#include "math.h"


//#include "main.h"

//����������
int lCg=915;            //��������ƫ
int lCz=1260;            //���ٶȴ�������ƫ

int run_dalay = 300;

float lGv_0[30] = {930}  ;

float lRg=0.3;          //�����Ǳ���
int lZdelta=900;//660;        //���ٶȴ��������ƫб
float lTz=4.5;             //�������ٶȲ���ʱ��ϵ��
float lZangle=0;         //Z�����ĽǶ�
float lGaspeed=0;        //�Ǽ��ٶ�
float lDeltaT=0.001;     //���ּ��ʱ��

uchar lFirstFlagA=1;      //��¼�Ƿ��һ�β���
float lGoValue[3];       //��������ʷֵ
float lAzValue[3];       //���ٶ�Z��ʷֵ



float lGv=0;             //�ɼ����������Ǿ�ֵ��
float lZv=0;             //�ɼ����ļ��ٶ�Z��ֵ��

//ֱ����������
float gStaticAngle=0;
float gRealAngle=0;

int gKpa=1200;             //350 ��ѹ7.47 600      500           650                            300     400   750       400      300   1200
int gKia=1200;            // 425         1350     100         1250        1550    1650    700    600    900       400      425
int gKda=100;            //   30         100      60         120         90              40/20    30   30        50       25            1600
//�����������
                                                                                                                                       
float gPWMOutA=0;
float gPWMOutA2=0;


//���Ʋ���
float lAngleError[3]={0,0,0};

//��־
int lDangerCount=0;





void GetAngleFun(void)
{  
    int i=0;
    float sume=0,avee=0;
    float deltav=0;
    float Kg = 0,NowData = 0,NowData_P = 0;

    
    //������������80us����1�δ�ԼΪ12us
    if(lFirstFlagA==1)
    {
        lFirstFlagA=0;
      //  while(ATD0STAT0_SCF==0);
        lGoValue[0]=AD_capture(5);           //������
        lAzValue[0]=AD_capture(4);
        lGoValue[1]=lGoValue[0];
        lAzValue[1]=lAzValue[0];  
        lGoValue[2]=lGoValue[0];
        lAzValue[2]=lAzValue[0];  
    } 
    else
    {
        lGoValue[2]=lGoValue[1];
        lAzValue[2]=lAzValue[1];
        lGoValue[1]=lGoValue[0];
        lAzValue[1]=lAzValue[0];
        //�ɼ�����������ٶȴ�������ӦADͨ��������ֵ�˲�
       // while(ATD0STAT0_SCF==0);
        lGoValue[0]=AD_capture(5);
        lAzValue[0]=AD_capture(4);  
    }
    
    lGv=(lGoValue[0]+lGoValue[1]+lGoValue[2])/3;
    lZv=(lAzValue[0]+lAzValue[1]+lAzValue[2])/3;
    
     if(run_dalay<1){
        
   //����ٶȴ������ĽǶ�
    lZangle=(lCz-lZv)/lZdelta;
    if(lZangle>1)
        lZangle=1;
    else if (lZangle<-1)
        lZangle=-1;
    lZangle=60*(0.95*lZangle+0.25*lZangle*lZangle*lZangle);
    
     //�Ƕȷ�����
    deltav=(lZangle-gRealAngle)*lTz;
       
    //��Ǽ��ٶ�
    lGaspeed=lRg*(lCg-lGv);
    
    //��ʵ�ʽǶ�
    gRealAngle=(lGaspeed+deltav)*lDeltaT+gRealAngle; 
 
    
    if(gRealAngle>18 || gRealAngle<-17)     //�Ӵ�һ�㣡����
    {
        lDangerCount++;
        if(lDangerCount>300)
        {
            STOP=4;
            lDangerCount=300;  
        }
    } 
    else
        lDangerCount=0;
    
    } 
    else{
      run_dalay--;
    
     lGv_0[0]=lGv;
     for(i=28;i>=0;i--){
    
      lGv_0[i+1]=lGv_0[i];
     }
      if(run_dalay==1){ 
     for(i=0;i<=29;i++) {
     sume+=lGv_0[i]; 
     }
     avee=sume/30;
      
      lCg =  avee+1 ;
       }
    }
   
}



void AngleControlFun(void)
{
    lAngleError[2]=lAngleError[1];
    lAngleError[1]=lAngleError[0];
    lAngleError[0]=gRealAngle-gStaticAngle;
    
    gPWMOutA2 =gKpa*lAngleError[0] + gKda*(lAngleError[0]-lAngleError[1]) + gKia*(lAngleError[0] - 2*lAngleError[1] + lAngleError[2]);
    
     gPWMOutA = gPWMOutA2;
 /*    
       if(gPWMOutA >2000)
         gPWMOutA = 2000;
       if(gPWMOutA <-2000)
         gPWMOutA = -2000;
    */          
   

}
