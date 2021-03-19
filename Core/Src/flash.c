#include "boot.h"
#include "fatfs.h"
#include "usb_host.h"

#define FLASH_USER_START_ADDR   ADDR_FLASH_SECTOR_1_BANK1      //Start of user Flash area Bank1
#define FLASH_USER_END_ADDR     (ADDR_FLASH_SECTOR_6_BANK1 - 1)  //End of user Flash area Bank1

uint32_t Address = 0, SECTORError = 0;
static FLASH_EraseInitTypeDef EraseInitStruct;

//HAL_FLASH_Unlock(); //Unlock the Flash to enable the flash control register access
//HAL_FLASH_Lock();   //Lock the Flash to disable the flash control register access

void FLASH_Erase(uint32_t FirstSector, uint32_t NbOfSectors) 
{
  //Fill EraseInit structure
  EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORS;  //Sectors erase only
  EraseInitStruct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;    //Flash program/erase by 32 bits
  EraseInitStruct.Banks         = FLASH_BANK_1;             //Bank 1
  EraseInitStruct.Sector        = FirstSector;              //Initial FLASH sector to erase when Mass erase is disabled
  EraseInitStruct.NbSectors     = NbOfSectors;              //Number of sectors to be erased
  
  if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)
  {

  }
}

void FLASH_Program(uint32_t flashAddress, uint32_t DataAddress, uint16_t size)
{
  for(uint16_t i = 0; i < size; i++)
  {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, flashAddress, DataAddress) == HAL_OK)
    {
      flashAddress = flashAddress + 32; //increment for the next Flash word
      DataAddress  = DataAddress  + 32;
    }
    else
    {
      //Error occurred while writing data in Flash memory.
    }
  }
}
