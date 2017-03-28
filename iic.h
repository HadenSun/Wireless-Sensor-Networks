#ifndef _IIC_H
#define _IIC_H

#include <ioCC2530.h>
#include "delay.h"


#define IIC_SCL P1_3
#define IIC_SDA P1_2


void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
uchar IIC_Wait_Ack(void);
uchar IIC_Read_Byte(unsigned char ack);
void IIC_Send_Byte(uchar txd);



#endif
