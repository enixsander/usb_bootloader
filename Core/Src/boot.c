#include "boot.h"
#include "fatfs.h"
#include "usb_host.h"

FRESULT res;        //FatFs function common result code
uint32_t bytesread; //File read counts
uint8_t file_name[] = "bik.bin";
uint8_t rtext[100];

#define FLASH_DISK_START_ADDRESS ((uint32_t)0x08020000) //адрес начала программы ADDR_FLASH_SECTOR_1

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
      if(f_open(&USBHFile, (TCHAR const*)file_name, FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)  //Create and Open a new text file object with write access
      {

        /*for(uint32_t i = 0; i < ALL_LOG_SIZE; i += PAGE_SIZE) {
          SPI3_ReadData(FLASH_LOGS_ADDR + i, PAGE_SIZE, (uint8_t*)&operative_data);
          res = f_write(&USBHFile, operative_data, PAGE_SIZE, (void *)&byteswritten); //Write data to the text file 
        }
        if((byteswritten > 0) && (res == FR_OK))*/
        {
          //res = f_read(&USBHFile, rtext, sizeof(rtext), (void *)&bytesread);//Read data from the text file_name
          f_close(&USBHFile); //Close the open text file
        }
      }
      if (f_mount(NULL, "", 0) != FR_OK)
      {
        USBH_UsrLog("ERROR : Cannot DeInitialize FatFs! \n");
      }
    }
    MX_FATFS_DeInit();
  }
}
