
#include "MAX17262/MAX17262.h"




	
void MAX17262_GetData(uint16_t MAX17262_target, int16_t* getDataPointer)	//
{
	uint8_t myBuffer[2];
	
	while(HAL_I2C_Mem_Read(&MAX17262_I2C_PORT, MAX17262_DIVECE_ADDR, MAX17262_target, 1, myBuffer, 2, 10)!=HAL_OK){return;}
	int16_t output = (int16_t)myBuffer[0] | (int16_t)(myBuffer[1] << 8);
	*getDataPointer = output;
}

void MAX17262_SetData(uint16_t MAX17262_target, uint16_t MAX17262_target_data, int16_t* getDataPointer)	//
{
	uint8_t myBuffer[2];
	myBuffer[1] = MAX17262_target_data>>8;
	myBuffer[0] = MAX17262_target_data;
	while(HAL_I2C_Mem_Write(&MAX17262_I2C_PORT, MAX17262_DIVECE_ADDR, MAX17262_target, 1, myBuffer, 2, 1000)!=HAL_OK){return;}
	
	while(HAL_I2C_Mem_Read(&MAX17262_I2C_PORT, MAX17262_DIVECE_ADDR, MAX17262_target, 1, myBuffer, 2, 10)!=HAL_OK){return;}
	int16_t output = (int16_t)myBuffer[0] | (int16_t)(myBuffer[1] << 8);
	*getDataPointer = output;
}

void MAX17262_init(void)
{
	int16_t I2C_value[1]={0,};
	int8_t setting_flag=0;
	
	
	//���� ������� Ȯ��
	
	MAX17262_GetData(MAX17262_DESIGN_CAP, I2C_value);
	if(I2C_value[0] != 0x01F4){setting_flag=1;}
	MAX17262_GetData(MAX17262_V_EMPTY, I2C_value);
	if((uint16_t)I2C_value[0] != 0xA561){setting_flag=1;}
	MAX17262_GetData(MAX17262_ICHG_TERM, I2C_value);
	if(I2C_value[0]!=0x0080){setting_flag=1;}
	

	//�����¸�� ��������
	
	MAX17262_SetData(MAX17262_SOFT_WAKEUP, 0x0090, I2C_value); 		 // ����ũ��

	MAX17262_SetData(MAX17262_HIB_CFG, 0x0000, I2C_value);  					// ������ ��� ���� ����

	MAX17262_SetData(MAX17262_SOFT_WAKEUP, 0x0000, I2C_value); 		 // ����ũ�� �÷��� �ʱ�ȭ

	//���͸� �� ����
	MAX17262_SetData(MAX17262_DESIGN_CAP, 0x01F4, I2C_value);  //������� ���͸� �뷮 ���� 250mA

	MAX17262_SetData(MAX17262_V_EMPTY, 0xA561, I2C_value);  //3V

	MAX17262_SetData(MAX17262_ICHG_TERM, 0x0080, I2C_value);  //���� ���� �������� 20mA

	//���� �� �Ϸ���
	MAX17262_SetData(MAX17262_MODEL_CFG, 0x8000, I2C_value);  //�� ����

	MAX17262_GetData(MAX17262_MODEL_CFG, I2C_value);

	while(I2C_value[0]!=0x0000){			//���¿Ϸ���� ���
		MAX17262_GetData(MAX17262_MODEL_CFG, I2C_value);
	}
	
	MAX17262_SetData(MAX17262_HIB_CFG, 0x870C, I2C_value);  					// ������ ��� �����
	MAX17262_SetData(0x00, 0x00, I2C_value);												// ���� �������� �ʱ�ȭ

}


uint8_t MAX17262_Get_BatPercent(void)
{
	int16_t I2C_value[1];
	float bat_percent=0;
	MAX17262_GetData(MAX17262_ATAVSOC ,I2C_value);
	bat_percent = I2C_value[0]/256;
	return bat_percent;
}





