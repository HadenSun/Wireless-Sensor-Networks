#ifndef __OPT3001_H
#define __OPT3001_H
#include "iic.h"


typedef enum{
	OPT3001_REG_ADD_RST = 0, 					//转换结果
	OPT3001_REG_ADD_COF = 1,					//配置
	OPT3001_REG_ADD_LL = 2,						//下限
	OPT3001_REG_ADD_HL = 3,						//上限
	OPT3001_REG_ADD_MID = 126,					//制造商ID
	OPT3001_REG_ADD_DID = 127					//设备ID
}optRegAdd;								//功能寄存器地址


typedef enum{
	OPT3001_ADD_W = 0x8A, 						//写入地址
	OPT3001_ADD_R = 0x8B,						//读取地址
}optSlaveAdd;								//设备地址，ADD接VCC


typedef enum{
	OPT3001_NAck = 0x01, 						//写入无反应
}optErr;								//错误代码


u8 OPT3001_ReadManufactureerID(u16 *MID);
u8 OPT3001_ReadDeviceID(u16 *DID);
u8 OPT3001_WriteRegister(u8 add,u16 reg);
u8 OPT3001_ReadResult(float *rst);


#endif