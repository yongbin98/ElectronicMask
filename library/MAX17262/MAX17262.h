#ifndef __MAX17262_H
#define __MAX17262_H

#include "main.h"

#define MAX17262_I2C_PORT hi2c1
extern I2C_HandleTypeDef MAX17262_I2C_PORT;


#define MAX17262_DIVECE_ADDR		0x6C			//0x36  //0x6C


#define MAX17262_REPCAP					0x05				//
#define MAX17262_ATAVCAP				0xDF
#define MAX17262_REPSOC					0x06				//�ܷ� ����� �ۼ�Ʈ
#define MAX17262_ATAVSOC				0xDE
#define MAX17262_FULLCAPREP			0x10
#define MAX17262_CURRENT				0x0A				//���� ����� ����

//�𵨼��ð���
#define MAX17262_DESIGN_CAP			0x18 			//���͸� �뷮 ����
#define MAX17262_V_EMPTY				0x3A				//���͸� �ּ����� �� ȸ������ ����
#define MAX17262_ICHG_TERM			0x1E				//���͸� ���� ���� ���� ����
#define MAX17262_MODEL_CFG			0xDB			//�� ���ð���, �𵨸���

//�����¸�����
#define MAX17262_SOFT_WAKEUP		0x60			//����ũ��
#define MAX17262_HIB_CFG					0xBA		//�����¸�� ���� ����(�ʱⰪ 0x8400)

//���͸� ���� Ȯ�� ��������


#define MAX17043_COMMAND				0xfe




void MAX17262_GetData(uint16_t MAX17262_target, int16_t* getDataPointer);
void MAX17262_SetData(uint16_t MAX17262_target, uint16_t MAX17262_target_data, int16_t* getDataPointer);
void MAX17262_init(void);
uint8_t MAX17262_Get_BatPercent(void);



#endif
