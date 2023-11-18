#include "fifo.h"

bool sd_init(){
	if(!(HAL_GPIO_ReadPin(SD_SW_GPIO_Port,SD_SW_Pin)))
	{
		HAL_Delay(100);
		
		//SD카드 초기화
		res = BSP_SD_Init();
		if(res != FR_OK)
				return true;
		
		//SD 마운트
		res = f_mount(&SDFatFs,"", 0);
		if(res != FR_OK)
				return true;
		
		return false;
	}
	return true;
}


void fifo_lps(float tmp, float press, float alti, uintmax_t timeT){
	sprintf(SD_msg,"%f,%f,%f,%f\n",(float)timeT/(float)1000,press,tmp,alti);
	f_puts(SD_msg,&LPS_fp);	
	memset(SD_msg,0,sizeof(SD_msg));
}

void fifo_i2s(uint8_t *data, uint16_t data_size){
	uint16_t temp_number;
	if(first_time == 0){
		for(int i = 0; i < 44; i++){
			*(data + i) = wav_file_header[i];
		}
		first_time = 1;		
	}
	res = f_write(&I2S_fp,(void *)data, data_size,(UINT*)&temp_number);
	
	wav_file_size += data_size;
}

void fifo_spo2(uint32_t IR, uint32_t red, uintmax_t timeT){
	float newTime = (float)timeT/50;
	sprintf(SD_msg,"%f,%d,%d\n",newTime,IR,red);
	f_puts(SD_msg,&PPG_fp);	
	memset(SD_msg,0,sizeof(SD_msg));	
}

bool start_recording_lps(void){
	while(1){
		sprintf(SD_msg,"LPS22HH_%d.csv",file_counter_lps);
		res = f_open(&LPS_fp, SD_msg, FA_CREATE_ALWAYS | FA_WRITE);
		if(res == FR_EXIST){			
			memset(SD_msg,0,sizeof(SD_msg));
			file_counter_lps++;
		}
		else if(res == FR_OK){
			memset(SD_msg,0,sizeof(SD_msg));
			break;
		}else{
			return true;	
		}		
	}	
	f_puts("Time,Pressure,Temperature,Altitude\n",&LPS_fp);	
	file_counter_lps++;
	return false;
}


bool start_recording_i2s(uint32_t frequency)
{	
	static char file_name[] = "w_000.wav";
	
	while(1){
		int file_number_digits = file_counter_i2s;	
		uint32_t byte_rate = frequency * 2 * 2;	
		wav_file_header[24] = (uint8_t)frequency;
		wav_file_header[25] = (uint8_t)(frequency >> 8);
		wav_file_header[26] = (uint8_t)(frequency >> 16);
		wav_file_header[27] = (uint8_t)(frequency >> 24);
		wav_file_header[28] = (uint8_t)byte_rate;
		wav_file_header[29] = (uint8_t)(byte_rate >> 8);
		wav_file_header[30] = (uint8_t)(byte_rate >> 16);
		wav_file_header[31] = (uint8_t)(byte_rate >> 24);
		
		// defining a wave file name
		file_name[4] = file_number_digits%10 + 48;
		file_number_digits /= 10;
		file_name[3] = file_number_digits%10 + 48;
		file_number_digits /= 10;
		file_name[2] = file_number_digits%10 + 48;
			
		res = f_open(&I2S_fp, file_name, FA_CREATE_ALWAYS | FA_WRITE);	
		if(res == FR_EXIST){			
			memset(SD_msg,0,sizeof(SD_msg));
			file_counter_i2s++;
		}
		else if(res == FR_OK){
			memset(SD_msg,0,sizeof(SD_msg));
			break;
		}else{
			return true;	
		}		
	}
	file_counter_i2s++;
	wav_file_size = 0;	
	return false;
}

bool start_recording_spo2(void){
	while(1){
		sprintf(SD_msg,"SpO2_%d.csv",file_counter_spo2);
		res = f_open(&PPG_fp, SD_msg, FA_CREATE_ALWAYS | FA_WRITE);
		if(res == FR_EXIST){			
			memset(SD_msg,0,sizeof(SD_msg));
			file_counter_spo2++;
		}
		else if(res == FR_OK){
			memset(SD_msg,0,sizeof(SD_msg));
			break;
		}else{
			return true;	
		}
	}
	f_puts("Time,IR,RED\n",&PPG_fp);	
	return false;
}
void stop_recording_lps(void){	
	
	res = f_close(&LPS_fp);
	if(res != FR_OK){  }
}
void stop_recording_i2s(void){
	
	uint16_t temp_number;
	
	wav_file_size -= 8;
	wav_file_header[4] = (uint8_t)wav_file_size;
	wav_file_header[5] = (uint8_t)(wav_file_size >> 8);
	wav_file_header[6] = (uint8_t)(wav_file_size >> 16);
	wav_file_header[7] = (uint8_t)(wav_file_size >> 24);
	
	wav_file_size -= 36;
	wav_file_header[40] = (uint8_t)wav_file_size;
	wav_file_header[41] = (uint8_t)(wav_file_size >> 8);
	wav_file_header[42] = (uint8_t)(wav_file_size >> 16);
	wav_file_header[43] = (uint8_t)(wav_file_size >> 24);
	
	f_lseek(&I2S_fp,0);
	res = f_write(&I2S_fp,(void *)wav_file_header, sizeof(wav_file_header),(UINT*)&temp_number);
	if(res != FR_OK){
		//error
	}	
	res = f_close(&I2S_fp);
	first_time = 0;
	if(res != FR_OK){ 
		//error
	}
}

bool stop_recording_spo2(void){
	res = f_close(&PPG_fp);
	if(res != FR_OK){  }
}