#ifndef __OPT3001_H
#define __OPT3001_H
#include "iic.h"


typedef enum{
	OPT3001_REG_ADD_RST = 0, 					//ת�����
	OPT3001_REG_ADD_COF = 1,					//����
	OPT3001_REG_ADD_LL = 2,						//����
	OPT3001_REG_ADD_HL = 3,						//����
	OPT3001_REG_ADD_MID = 126,					//������ID
	OPT3001_REG_ADD_DID = 127					//�豸ID
}optRegAdd;								//���ܼĴ�����ַ


typedef enum{
	OPT3001_ADD_W = 0x8A, 						//д���ַ
	OPT3001_ADD_R = 0x8B,						//��ȡ��ַ
}optSlaveAdd;								//�豸��ַ��ADD��VCC


typedef enum{
	OPT3001_NAck = 0x01, 						//д���޷�Ӧ
}optErr;								//�������


u8 OPT3001_ReadManufactureerID(u16 *MID);
u8 OPT3001_ReadDeviceID(u16 *DID);
u8 OPT3001_WriteRegister(u8 add,u16 reg);
u8 OPT3001_ReadResult(float *rst);


#endif