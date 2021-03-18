#ifndef __CONFIG_BIK_H
#define __CONFIG_BIK_H

//SDRAM - 32MB		0xC0000000 - 0xC1E84800
//FLASH - 16MB	(SPI3)
//FLASH - 64MB	(QSPI)
//MT48LC16M16A2P-6A    4 Meg x 16 x 4 banks - 256Mb = 32MB
//MT25QL128ABB8ESF-0AAT - SPI3     - 16 MB
//MT25QL512ABB8ESF-0AAT - QUAD SPI - 64 MB

enum {NOTCONNECTED, GROUND, POWER};
enum {OFF = 0x00, UNUSED = 0x0F, ON = 0xFF};
//enum {OUTPUT = 0x00, INPUT = 0xFF, WAIT = 0x0F};

#define PIC_COUNT 4	//количество картинок с кранами в памяти

//config.c
#define FLASH_LOGS_ADDR    ((uint32_t)0x00000000)
#define FLASH_CONFIG_ADDR  ((uint32_t)0x00100000)	//~1MB (all - 16 MB)

#define CONFIG_SIZE 	5
#define CRANES_COUNT 	4		//всего моделей крана
#define LOG_TIMER		5000	//запись логов раз в 5 сек
#define ALL_LOG_SIZE 	(4096 * 5)

//ADC - 16 bits
//границы срабатывания на GND или 24V (на входах половина питания)
#define LOWER_LIMIT  0x0100 //GND (adc data) < 0x003C
#define UPPER_LIMIT  0x5CE0 //24V (adc data) 24V - ~0x7000, 20V - ~0x5CE0
#define LIMIT_31V  	 0xA550 //28V ~ 0xA550, 24V ~ 0x8d20, 20V ~ 0x7520

#define ICON_WIDTH  48
#define ICON_HEIGHT 48
#define ICON_SIZE 	(ICON_WIDTH * ICON_HEIGHT * 3)

#define BIK_ID 0x00
#define BVV_ID 0x01
#define BPK_ID 0x02
#define LEP_ID 0x03
#define DDS_ID 0x04

#define BVV_INPUT_ID (0x18FEF000 | BVV_ID)
#define ACCELEROM_ID (0x08F02D00 | BVV_ID)
#define BVV_BAR_ID 	 (0x08FF0400 | BVV_ID)
#define BVV_I1_ID 	 (0x08357000 | BVV_ID)
#define BVV_I2_ID 	 (0x08357100 | BVV_ID)
#define BVV_I3_ID 	 (0x08357200 | BVV_ID)
#define BVV_U_ID 	 (0x08357300 | BVV_ID)

#define BUTTONS_ID   (0x18FED900 | BIK_ID)
#define PEDAL_ID     (0x0CF00300 | BIK_ID) //PGN 61443 - Identifies electronic engine control related parameters.
#define PEDAL_SWITCH_ID (0x0CF00100 | BIK_ID) //PGN 61441 - Electronic brake controller

//BPK through BVV
#define BPK_I1_ID    (0x08357900 | BPK_ID)
#define BPK_I2_ID    (0x08357A00 | BPK_ID)
#define BPK_U_ID     (0x08357B00 | BPK_ID)
#define BPK_Input_ID (0x08357C00 | BPK_ID)
#define BPK_Fault_ID (0x08357D00 | BPK_ID)

//датчик ЛЭП
#define LEP_ACCEL_ID  (0x08F02E00 | LEP_ID)
#define POWER_LINE_ID (0x08F1F100 | LEP_ID)
//датчик длины стрелы
#define DDS_ACC_ID    (0x08F02E00 | DDS_ID)
#define BOSCH_ID      (0x08F02F00 | DDS_ID)

//SDRAM - 32MB	0xC0000000 - 0xC1E84800
#define SDRAM_MAIN_ADDR       ((uint32_t)0xC0000000)
#define SDRAM_LOGO_ADDR       ((uint32_t)0xC0000000 + 1*(800*480*3))
#define SDRAM_TEMP_ADDR       ((uint32_t)0xC0000000 + 20*(800*480*3))	//0xC15F9000
#define SDRAM_MENU_ADDR		  ((uint32_t)0xC0000000 + 3*(800*480*3))
#define SDRAM_CURR_ADDR       ((uint32_t)0xC0000000 + 4*(800*480*3))
#define SDRAM_ICON_ADDR       ((uint32_t)0xC0000000 + 5*(800*480*3))
#define SDRAM_AUDIO_ADDR       ((uint32_t)0xC1000000)
#define SDRAM_AUDIO1_ADDR      ((uint32_t)0xC1600000)
/*#define SDRAM_GIF0_ADDR        ((uint32_t)0xC0000000 + 2*(800*480*3))
#define SDRAM_GIF1_ADDR        ((uint32_t)0xC0000000 + 3*(800*480*3))
#define SDRAM_GIF2_ADDR        ((uint32_t)0xC0000000 + 4*(800*480*3))
#define SDRAM_GIF3_ADDR        ((uint32_t)0xC0000000 + 5*(800*480*3))
#define SDRAM_GIF4_ADDR        ((uint32_t)0xC0000000 + 6*(800*480*3))
#define SDRAM_GIF5_ADDR        ((uint32_t)0xC0000000 + 7*(800*480*3))
#define SDRAM_GIF6_ADDR        ((uint32_t)0xC0000000 + 8*(800*480*3))
#define SDRAM_GIF7_ADDR        ((uint32_t)0xC0000000 + 9*(800*480*3))
#define SDRAM_GIF8_ADDR        ((uint32_t)0xC0000000 + 10*(800*480*3))  // + 0xAFC800*/

extern uint8_t SCREEN_BRIGHTNESS;
extern uint8_t GLOBAL_BRIGHTNESS;
#define GREEN_BRIGHTNESS  0xFF
#define RED_BRIGHTNESS    0x60
#define IND_BRIGHTNESS    0xFF

#endif /* __CONFIG_BIK_H */
