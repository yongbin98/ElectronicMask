
#include "LPS22HH.h"

void LPS22HH_setup()
{	
	uint8_t TxBuffer[2];
	
	uint8_t who_am_i = LPS22HH_readMsg(LPS_WHO_AM_I);
	
	if(who_am_i != 0xB3){Error_Handler();}	
	
	// reboot	
	LPS22HH_reboot();
	
	// Set Interface control
	TxBuffer[0] = LPS_IF_CTRL;
	TxBuffer[1] = LPS22HH_SDA_PU_EN | LPS22HH_SDO_PU_EN | LPS22HH_PD_DIS_INT1 | LPS22HH_I3C_DISABLE | LPS22HH_I2C_DISABLE;
	LPS22HH_sendMsg(TxBuffer[0], TxBuffer[1]);
	memset(TxBuffer,0,sizeof(TxBuffer));
		
	// Set control register 1
	TxBuffer[0] = LPS_CTRL_REG1;
	TxBuffer[1] = LPS22HH_ODR2 | LPS22HH_ODR1 | LPS22HH_ODR0 | LPS22HH_EN_LPFP | LPS22HH_LPFP_CFG;
	LPS22HH_sendMsg(TxBuffer[0], TxBuffer[1]);
	memset(TxBuffer,0,sizeof(TxBuffer));
		
}

void LPS22HH_sendMsg(uint8_t address, uint8_t msg)
{
	uint8_t TxBuffer[2];
	TxBuffer[0] = address | WRITE_EN;	
	TxBuffer[1] = msg;
	
	LPS22HH_Select();
	while(HAL_SPI_GetState(&LPS22HH_SPI_PORT) != HAL_SPI_STATE_READY){}
	
	if(HAL_SPI_Transmit_DMA(&LPS22HH_SPI_PORT, (uint8_t*)TxBuffer, 2) != HAL_OK){Error_Handler();}
		
	while(HAL_SPI_GetState(&LPS22HH_SPI_PORT) != HAL_SPI_STATE_READY){}
	LPS22HH_Deselect();
	
}

uint8_t LPS22HH_readMsg(uint8_t address)
{
	uint8_t TxBuffer[2];
	uint8_t RxBuffer[2];
	uint8_t spiStatus = 0x00;
	TxBuffer[0] = address | READ_EN;	
	TxBuffer[1] = 0x00;	
	
	LPS22HH_Select();
	while(HAL_SPI_GetState(&LPS22HH_SPI_PORT) != HAL_SPI_STATE_READY){}
	
//	spiStatus = HAL_SPI_TransmitReceive(&LPS22HH_SPI_PORT, TxBuffer, RxBuffer, 2, HAL_MAX_DELAY);
	spiStatus = HAL_SPI_TransmitReceive_DMA(&LPS22HH_SPI_PORT, TxBuffer, RxBuffer, 2);
	if(spiStatus != HAL_OK){Error_Handler();}
		
	while(HAL_SPI_GetState(&LPS22HH_SPI_PORT) != HAL_SPI_STATE_READY){}
	LPS22HH_Deselect();
	
	return RxBuffer[1];
}

float LPS22HH_readTemperature()
{
	uint8_t temperature_data[2];
	int16_t rawTemperature;
	float celData;
	
	temperature_data[0] = LPS22HH_readMsg(LPS_TEMP_OUT_L);
	temperature_data[1] = LPS22HH_readMsg(LPS_TEMP_OUT_H);
	
	rawTemperature = temperature_data[1] << 8 | temperature_data[0];
	celData = rawTemperature/100.f;
	
	return celData;
} 

float LPS22HH_readPressure()
{
	uint8_t pressure_data[3];
	int32_t rawPressure;
	float hPaData;
	
	pressure_data[0] = LPS22HH_readMsg(LPS_PRESS_OUT_XL);
	pressure_data[1] = LPS22HH_readMsg(LPS_PRESS_OUT_L);
	pressure_data[2] = LPS22HH_readMsg(LPS_PRESS_OUT_H);
	
	rawPressure = pressure_data[2] << 16 | pressure_data[1] << 8 | pressure_data[0];
	hPaData = rawPressure/4096.f;
	
	return hPaData;
} 

float LPS22HH_calAltitude(float pressure, float temperature)
{
	return (1.0f - powf((pressure / SEA_PRESSURE), 0.1902226f)) * (temperature + 273.15f) / 0.0065f;
}

void LPS22HH_reboot()
{
	uint8_t TxBuffer[2];
	
	TxBuffer[0] = LPS_CTRL_REG2;
	TxBuffer[1] = LPS22HH_SWRESET;
	LPS22HH_sendMsg(TxBuffer[0], TxBuffer[1]);
	memset(TxBuffer,0,sizeof(TxBuffer));
	
	while((LPS22HH_readMsg(LPS_CTRL_REG2) & 0x04) != 0x00);
}
