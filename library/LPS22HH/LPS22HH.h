#ifndef __LPS22HH_H
#define __LPS22HH_H

#include "main.h"

//USER SETTING START***********************************************************************
//============================================================================================================================
#define LPS22HH_SPI_PORT  			hspi2
extern SPI_HandleTypeDef 				LPS22HH_SPI_PORT;
#define LPS22HH_CS_GPIO_Port		LPS_CS_GPIO_Port
#define LPS22HH_CS_Pin				 	LPS_CS_Pin

//#define FIFO_SAMPLES						128
//============================================================================================================================
//USER SETTING END***********************************************************************

#define LPS22HH_Select()    HAL_GPIO_WritePin(LPS22HH_CS_GPIO_Port, LPS22HH_CS_Pin, GPIO_PIN_RESET)
#define LPS22HH_Deselect()  HAL_GPIO_WritePin(LPS22HH_CS_GPIO_Port, LPS22HH_CS_Pin, GPIO_PIN_SET)

//LPS22HH Registry addresses

#define READ_EN 0x80
#define WRITE_EN 0x00

// Interface Register
#define LPS_INTERRUPT_CFG								(0x0B)      
#define LPS_THS_P_L											(0x0C)      
#define LPS_THS_P_H											(0x0D)     
#define LPS_IF_CTRL											(0x0E)     
#define LPS_WHO_AM_I										(0x0F)     

// Control Register
#define LPS_CTRL_REG1										(0x10)   
#define LPS_CTRL_REG2										(0x11)   
#define LPS_CTRL_REG3										(0x12)   
#define LPS_FIFO_CTRL										(0x13)   
#define LPS_FIFO_WTM										(0x14)   
#define LPS_REF_P_L											(0x15)   
#define LPS_REF_P_H											(0x16)   
#define LPS_RPDS_L											(0x18)   
#define LPS_RPDS_H											(0x19)   

// Interrupt source
#define LPS_INT_SOURCE									(0x24)   
#define LPS_FIFO_STATUS1								(0x25)   
#define LPS_FIFO_STATUS2								(0x26)   
#define LPS_STATUS											(0x27)   

// FIFO
#define LPS_PRESS_OUT_XL								(0x28)     
#define LPS_PRESS_OUT_L									(0x29)     
#define LPS_PRESS_OUT_H									(0x2A)  

#define LPS_TEMP_OUT_L									(0x2B)     
#define LPS_TEMP_OUT_H									(0x2C)  

#define LPS_FIFO_DATA_OUT_PRESS_XL			(0x78)     
#define LPS_FIFO_DATA_OUT_PRESS_L				(0x79)     
#define LPS_FIFO_DATA_OUT_PRESS_H				(0x7A)  

#define LPS_FIFO_DATA_OUT_TEMP_L				(0x7B)     
#define LPS_FIFO_DATA_OUT_TEMP_H				(0x7C)  

#define SEA_PRESSURE 1013.25f

typedef enum
{
	LPS22HH_INT_EN_I3C	= 0x80,
	LPS22HH_SDA_PU_EN		= 0x10,
	LPS22HH_SDO_PU_EN		= 0x08,
	LPS22HH_PD_DIS_INT1	= 0x04,
	LPS22HH_I3C_DISABLE	= 0x02,
	LPS22HH_I2C_DISABLE	= 0x01
}LPS22HH_IF_CTRL;

typedef enum
{
	LPS22HH_ODR2				= 0x40,	
	LPS22HH_ODR1				= 0x20,	
	LPS22HH_ODR0				= 0x10,
	LPS22HH_EN_LPFP			= 0x08,
	LPS22HH_LPFP_CFG		= 0x04,
	LPS22HH_BDU					= 0x02,
	LPS22HH_SIM					= 0x01
}LPS22HH_CTRL_REG1;

typedef enum
{
	LPS22HH_BOOT					= 0x80,	
	LPS22HH_INT_H_L				= 0x40,	
	LPS22HH_PP_OD					= 0x20,
	LPS22HH_IF_ADD_INC		= 0x10,
	LPS22HH_SWRESET				= 0x04,
	LPS22HH_LOW_NOISE_EN	= 0x02,
	LPS22HH_ONE_SHOT			= 0x01
}LPS22HH_CTRL_REG2;

typedef enum
{
	LPS22HH_INT_F_FULL		= 0x40,	
	LPS22HH_INT_F_WTM			= 0x20,	
	LPS22HH_INT_F_OVR			= 0x08,
	LPS22HH_DRDY					= 0x04,
	LPS22HH_INT_S1				= 0x02,
	LPS22HH_INT_S0				= 0x01
}LPS22HH_CTRL_REG3;

typedef enum
{
	LPS22HH_STOP_ON_WTM		= 0x08,
	LPS22HH_TRIG_MODES		= 0x04,
	LPS22HH_F_MODE1				= 0x02,
	LPS22HH_F_MODE0				= 0x01
}LPS22HH_FIFO_CTRL;


void LPS22HH_setup(void);
float LPS22HH_readPressure(void);
float LPS22HH_readTemperature(void);
float LPS22HH_calAltitude(float pressure, float temperature);
void LPS22HH_sendMsg(uint8_t address, uint8_t msg);
uint8_t LPS22HH_readMsg(uint8_t msg);
void LPS22HH_reboot(void);
#endif
