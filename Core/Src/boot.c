#include "boot.h"
#include "fatfs.h"
#include "usb_host.h"

#define SIZE_DATA 128

FRESULT res;        //FatFs function common result code
uint32_t bytesread; //File read counts
uint8_t file_name[] = "bik.bin";
uint8_t usb_data[SIZE_DATA];

#define FLASH_DISK_START_ADDRESS ((uint32_t)0x08020000) //адрес начала программы ADDR_FLASH_SECTOR_1
#define FLASH_USER_START_ADDR   ADDR_FLASH_SECTOR_1_BANK1      //Start of user Flash area Bank1

//__attribute__((optimize("O0")))
void GoToUserApp()
{
  uint32_t appJumpAddress;
  void (*GoToApp)(void);  //объявляем пользовательский тип

  HAL_RCC_DeInit();
  HAL_DeInit();
  HAL_SuspendTick();

  appJumpAddress = *((volatile uint32_t*)(FLASH_DISK_START_ADDRESS + 4)); //извлекаем адрес перехода из вектора Reset  (PC – регистр, который указывает на текущую инструкцию + 4 байта). 
  GoToApp = (void (*)(void))appJumpAddress; //приводим его к пользовательскому типу

  //SCB->VTOR = FLASH_DISK_START_ADDRESS; //перенос вектора прерываний в основной программе
  //устанавливаем SP приложения (SP – регистр, который указывает на вершину стека
  __set_MSP(*((__IO uint32_t*) FLASH_DISK_START_ADDRESS)); //stack pointer (to RAM) for USER app in this address  

  GoToApp();  //запускаем приложение  

}

void firmware_write(void) {

  if (FATFS_LinkDriver(&USBH_Driver, USBHPath) == 0)
  {
    if (f_mount(&USBHFatFS, (TCHAR const*)USBHPath, 1) != FR_OK)
    {
      USBH_UsrLog("ERROR : Cannot Initialize FatFs! \n");
    }
    else
    {
      if(f_open(&USBHFile, (TCHAR const*)file_name, FA_READ) == FR_OK)  //Create and Open a new text file object with read access
      {
        uint32_t NbOfSectors = FLASH_SECTOR_5 - FLASH_SECTOR_1 + 1; //Number of sector to erase from 1st sector

        HAL_FLASH_Unlock();                       //Unlock the Flash to enable the flash control register access
        FLASH_Erase(FLASH_SECTOR_1, NbOfSectors); //(128 * 5) KB

        static uint32_t addr_flash = FLASH_USER_START_ADDR;
        while(1) {
          res = f_read(&USBHFile, usb_data, SIZE_DATA, (void *)&bytesread);//Read data from the text file_name
          if(bytesread == 0) 
            break;
          FLASH_Program(addr_flash, (uint32_t)usb_data, bytesread / 32);

          addr_flash += bytesread;
        } 
        HAL_FLASH_Lock(); 
        f_close(&USBHFile); //Close the open text file
      }
      if (f_mount(NULL, "", 0) != FR_OK)
      {
        USBH_UsrLog("ERROR : Cannot DeInitialize FatFs! \n");
      }
    }
    MX_FATFS_DeInit();
  }
}
