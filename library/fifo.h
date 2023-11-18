#ifndef __FIFO_H
#define __FIFO_H

#include "fatfs.h"
#include "stdbool.h"

static FRESULT res;	
static FATFS SDFatFs;
static FIL I2S_fp;
static FIL LPS_fp;
static FIL PPG_fp;
static uint32_t wav_file_size;
static DIR dir;
static FILINFO fno;
static char SD_msg[100];
static uint8_t first_time = 0;
static uint8_t file_counter_lps = 1;
static uint8_t file_counter_i2s = 1;
static uint8_t file_counter_spo2 = 1;

static uint8_t wav_file_header[44] = {
    0x52, 0x49, 0x46, 0x46, // Chunk ID: "RIFF" (in ASCII)
    0xa4, 0xa9, 0x03, 0x00, // Chunk Size (file size - 8 bytes)
    0x57, 0x41, 0x56, 0x45, // Format: "WAVE" (in ASCII)
    0x66, 0x6d, 0x74, 0x20, // Subchunk 1 ID: "fmt " (in ASCII)
    0x10, 0x00, 0x00, 0x00, // Subchunk 1 Size (16 for PCM)
    0x01, 0x00,             // Audio Format (PCM: 1)
    0x02, 0x00,             // Number of Channels (2 for stereo)
    0x80, 0x7d, 0x00, 0x00, // Sample Rate: 32000 kHz
    0x00, 0xf4, 0x01, 0x00, // Byte Rate: SampleRate * NumChannels * BitsPerSample / 8 -> 19200
    0x04, 0x00,             // Block Align: NumChannels * BitsPerSample / 8
    0x10, 0x00,             // Bits Per Sample: 16 bits
    0x64, 0x61, 0x74, 0x61, // Subchunk 2 ID: "data" (in ASCII)
    0x80, 0xa9, 0x03, 0x00  // Subchunk 2 Size (data size)
};

#define WAV_WRITE_SAMPLE_COUNT 2048

bool sd_init(void);
void fifo_lps(float tmp, float press, float alti, uintmax_t timeT);
void fifo_i2s(uint8_t *data, uint16_t data_size);
void fifo_spo2(uint32_t IR, uint32_t red, uintmax_t timeT);
bool start_recording_i2s(uint32_t frequency);
bool start_recording_lps(void);
bool start_recording_spo2(void);
void stop_recording_lps(void);
void stop_recording_i2s(void);
bool stop_recording_spo2(void);

#endif
