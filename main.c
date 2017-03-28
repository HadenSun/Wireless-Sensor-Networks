#include "delay.h"
#include <ioCC2530.h>
#include <string.h>
#include "opt3001.h"


#define LED P2_0



void LED_Init(void)
{
  P2DIR |= 0x01;
  LED = 0;
}

void Uart1_Init(void)
{
    CLKCONCMD &= ~0x40;
    while(CLKCONSTA & 0x40);
    CLKCONCMD &= ~0x47;

    PERCFG = 0x00;
    P0SEL = 0x30;
    P2DIR |= 0x40;

    U1CSR |= 0x80;
    U1GCR |= 11;
    U1BAUD |= 216;
    UTX1IF = 0;
}

void Uart1_SendString(char *Date,int len)
{
    int j;
    for(j = 0; j < len;j++)
    {
        U1DBUF = *Date++;
        while(!UTX1IF);
        UTX1IF = 0;
    }
}
void Uart1_SendByte(uchar n)
{
  U1DBUF = n;
  while(!UTX1IF);
  UTX1IF = 0;
}

void main(void)
{
  u8 error = 0;
  u16 MID,DID;
  

  LED_Init();
  Uart1_Init();
  IIC_Init();
  
  delay_ms(2000);
  error = OPT3001_ReadManufactureerID(&MID);
  Uart1_SendString("Error:",6);
  Uart1_SendByte(error);
  Uart1_SendString("  MID:",6);
  Uart1_SendByte((uchar)(MID>>8));
  Uart1_SendByte(MID & 0xFF);
  
  while(1)
  {
      LED = !LED;
      delay_ms(3000);
  }
}
