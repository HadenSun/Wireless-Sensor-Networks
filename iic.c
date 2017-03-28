
#include "iic.h"


//IIC��ʼ��
void IIC_Init(void)
{
  P1SEL &= ~0x06;     //P1.2 P1.3 ͨ��IO��Ĭ�ϣ�
  P1DIR |= 0x0C;      //P1.2 P1.3 ���
  P1INP &= ~0x06;     //P1.2 P1.3 ������Ĭ�ϣ�

  IIC_SDA = 1;
  IIC_SCL = 1;
}

//P1.2 ���
void SDA_OUT()
{
  P1DIR |= 0x02;
}

//P1.2 ����
void SDA_IN()
{
  P1DIR &= ~0x02;
}

//����IIC��ʼ�ź�
void IIC_Start()
{
  SDA_OUT();
  IIC_SDA=1;
  IIC_SCL=1;
  delay_us(4);
  IIC_SDA=0;
  delay_us(4);
  IIC_SCL=0;
}

//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();     //sda�����
	IIC_SCL=0;
	IIC_SDA=0;     //STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1;
	delay_us(1);
	IIC_SDA=1;     //����IIC���߽����ź�
	delay_us(4);
}

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//       0������Ӧ��ɹ�
uchar IIC_Wait_Ack(void)
{
	uchar ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����
	IIC_SDA=1;delay_us(1);
	IIC_SCL=1;delay_us(1);
	while(IIC_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;      //ʱ�����0
	return 0;
}
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//������ACKӦ��
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
void IIC_Send_Byte(uchar txd)
{
    uchar t;
		SDA_OUT();
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1;
        delay_us(2);   
        IIC_SCL=1;
        delay_us(2);
        IIC_SCL=0;
        delay_us(2);
    }
}
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
uchar IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
    {
      IIC_SCL=0;
      delay_us(2);
				IIC_SCL=1;
      receive<<=1;
      if(IIC_SDA)receive++;
	delay_us(1);
    }
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK
    return receive;
}
