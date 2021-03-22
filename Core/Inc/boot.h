#ifndef __BOOT_H
#define __BOOT_H

#include "main.h"

void GoToUserApp(void);
void firmware_write(void);

void FLASH_Erase(uint32_t, uint32_t);
void FLASH_Program(uint32_t, uint32_t, uint16_t);

void led_update(void);
void brightness_IND(uint8_t);
void LED_TLC59116IR_config(void);

#define FLASH_BASE_ADDR      (uint32_t)(FLASH_BASE)
#define FLASH_END_ADDR       (uint32_t)(0x081FFFFF)

//Base address of the Flash sectors Bank 1
#define ADDR_FLASH_SECTOR_0_BANK1     ((uint32_t)0x08000000) //Base @ of Sector 0, 0   Kbytes
#define ADDR_FLASH_SECTOR_1_BANK1     ((uint32_t)0x08020000) //Base @ of Sector 1, 128 Kbytes
#define ADDR_FLASH_SECTOR_2_BANK1     ((uint32_t)0x08040000) //Base @ of Sector 2, 256 Kbytes
#define ADDR_FLASH_SECTOR_3_BANK1     ((uint32_t)0x08060000) //Base @ of Sector 3, 384 Kbytes
#define ADDR_FLASH_SECTOR_4_BANK1     ((uint32_t)0x08080000) //Base @ of Sector 4, 512 Kbytes
#define ADDR_FLASH_SECTOR_5_BANK1     ((uint32_t)0x080A0000) //Base @ of Sector 5, 640 Kbytes
#define ADDR_FLASH_SECTOR_6_BANK1     ((uint32_t)0x080C0000) //Base @ of Sector 6, 768 Kbytes
#define ADDR_FLASH_SECTOR_7_BANK1     ((uint32_t)0x080E0000) //Base @ of Sector 7, 896 Kbytes

//Base address of the Flash sectors Bank 2
#define ADDR_FLASH_SECTOR_0_BANK2     ((uint32_t)0x08100000) //Base @ of Sector 0, 1024 Kbytes
#define ADDR_FLASH_SECTOR_1_BANK2     ((uint32_t)0x08120000) //Base @ of Sector 1, 1152 Kbytes
#define ADDR_FLASH_SECTOR_2_BANK2     ((uint32_t)0x08140000) //Base @ of Sector 2, 1280 Kbytes
#define ADDR_FLASH_SECTOR_3_BANK2     ((uint32_t)0x08160000) //Base @ of Sector 3, 1408 Kbytes
#define ADDR_FLASH_SECTOR_4_BANK2     ((uint32_t)0x08180000) //Base @ of Sector 4, 1536 Kbytes
#define ADDR_FLASH_SECTOR_5_BANK2     ((uint32_t)0x081A0000) //Base @ of Sector 5, 1664 Kbytes
#define ADDR_FLASH_SECTOR_6_BANK2     ((uint32_t)0x081C0000) //Base @ of Sector 6, 1792 Kbytes
#define ADDR_FLASH_SECTOR_7_BANK2     ((uint32_t)0x081E0000) //Base @ of Sector 7, 1920 Kbytes

#endif // __BOOT_H