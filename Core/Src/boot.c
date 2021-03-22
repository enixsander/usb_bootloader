#include "boot.h"
#include "fatfs.h"
#include "usb_host.h"

#define SIZE_DATA 224 //256-32 bytes

FRESULT res;        //FatFs function common result code
uint32_t bytesread; //File read counts
uint8_t file_name[] = "bik.bin";
uint8_t usb_data[SIZE_DATA];

#define FLASH_DISK_START_ADDRESS ((uint32_t)0x08020000) //����� ������ ��������� ADDR_FLASH_SECTOR_1
#define FLASH_USER_START_ADDR   ADDR_FLASH_SECTOR_1_BANK1      //Start of user Flash area Bank1

//__attribute__((optimize("O0")))
void GoToUserApp()
{
  uint32_t appJumpAddress;
  void (*GoToApp)(void);  //��������� ���������������� ���

  //red LEDs turn off
  brightness_IND(0);
  led_update();

  HAL_RCC_DeInit();
  HAL_DeInit();
  HAL_SuspendTick();

  appJumpAddress = *((volatile uint32_t*)(FLASH_DISK_START_ADDRESS + 4)); //��������� ����� �������� �� ������� Reset  (PC � �������, ������� ��������� �� ������� ���������� + 4 �����). 
  GoToApp = (void (*)(void))appJumpAddress; //�������� ��� � ����������������� ����

  //SCB->VTOR = FLASH_DISK_START_ADDRESS; //������� ������� ���������� � �������� ���������
  //������������� SP ���������� (SP � �������, ������� ��������� �� ������� �����
  __set_MSP(*((__IO uint32_t*) FLASH_DISK_START_ADDRESS)); //stack pointer (to RAM) for USER app in this address  

  GoToApp();  //��������� ����������  

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
        FSIZE_t file_size = USBHFile.obj.objsize; // - USBHFile.fptr -- File read/write pointer (Zeroed on file open)
        uint32_t NbOfSectors = (file_size + 0x1FFFF) / 0x20000;  //0x20000 - 128KB, 0x1FFFF ��� ���������� � ������� �������
        static uint32_t addr_flash = FLASH_USER_START_ADDR;

        if(NbOfSectors > 0 && NbOfSectors < 8) { //size firmwire < 896 Kbytes
            HAL_FLASH_Unlock();                       //Unlock the Flash to enable the flash control register access
            FLASH_Erase(FLASH_SECTOR_1, NbOfSectors); //(128 * NbOfSectors) KB

            while(1) {
              res = f_read(&USBHFile, usb_data, SIZE_DATA, (void *)&bytesread);//Read data from the text file_name
              if(bytesread == 0) 
                break;
              FLASH_Program(addr_flash, (uint32_t)usb_data, (bytesread + 31) / 32);  //program 32 Bytes
              addr_flash += bytesread;
            } 
            HAL_FLASH_Lock();
        }

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
