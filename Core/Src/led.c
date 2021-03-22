#include "boot.h"

#define SB_CNT 24
#define GLOBAL_BRIGHTNESS 0xFF

enum {OFF = 0x00, UNUSED = 0x0F, ON = 0xFF};

extern I2C_HandleTypeDef hi2c4;
tlc59116_control_type dd7 = {0};
tlc59116_control_type dd8 = {0};
tlc59116_control_type dd9 = {0};
tlc59116_control_type dd10 = {0};

//uint8_t green_light = 0xFF;
//uint8_t red_light   = 0xFF;
uint8_t IND_light   = 0xFF;

//IND1 - IND12, Подсветка индикаторов над кнопками - красная 
uint8_t *red_leds[12]  = {&dd10.PWM12, &dd10.PWM13, &dd10.PWM14, &dd7.PWM12, &dd7.PWM13, &dd7.PWM14, 
                          &dd9.PWM1,   &dd9.PWM2,   &dd9.PWM3,   &dd8.PWM1,  &dd8.PWM2,  &dd8.PWM3};

void led_update(void) {
  HAL_I2C_Master_Transmit(&hi2c4, DD7_ADDR << 1,  (uint8_t *) &dd7,  sizeof(dd7),  10);
  HAL_I2C_Master_Transmit(&hi2c4, DD8_ADDR << 1,  (uint8_t *) &dd8,  sizeof(dd8),  10);
  HAL_I2C_Master_Transmit(&hi2c4, DD9_ADDR << 1,  (uint8_t *) &dd9,  sizeof(dd9),  10);
  HAL_I2C_Master_Transmit(&hi2c4, DD10_ADDR << 1, (uint8_t *) &dd10, sizeof(dd10), 10);
}

void brightness_IND(uint8_t set_light) {
  for(uint8_t i = 0; i < 12; i++)
    *red_leds[i] = set_light;
}

void red_indicators(uint8_t led, uint8_t state) {
  if(led < 12)
    *red_leds[led] = IND_light & state;
}

void LED_TLC59116IR_config(void) {
  uint8_t led_conf[5] = {0};

  dd7.reg_address =  0x02 | 0x80; // global autoincrement and PWM0 address
  dd8.reg_address =  0x02 | 0x80;
  dd9.reg_address =  0x02 | 0x80;
  dd10.reg_address = 0x02 | 0x80;

  led_conf[0] = 0;
  led_conf[1] = 0; // normal mode
  HAL_I2C_Master_Transmit(&hi2c4, DD7_ADDR << 1,  led_conf, 2, 50);
  HAL_I2C_Master_Transmit(&hi2c4, DD8_ADDR << 1,  led_conf, 2, 50);
  HAL_I2C_Master_Transmit(&hi2c4, DD9_ADDR << 1,  led_conf, 2, 50);
  HAL_I2C_Master_Transmit(&hi2c4, DD10_ADDR << 1, led_conf, 2, 50);

  led_conf[0] = 0x80 | 0x14;  // global autoincrement and LEDOUT0 address
  led_conf[1] = 0xFF;         // individual brightness and group dimming/blinking can be
  led_conf[2] = 0xFF;         // controlled through its PWMx register and the GRPPWM registers
  led_conf[3] = 0xFF;
  led_conf[4] = 0xFF;
  HAL_I2C_Master_Transmit(&hi2c4, DD7_ADDR << 1,  led_conf, 5, 100);
  HAL_I2C_Master_Transmit(&hi2c4, DD8_ADDR << 1,  led_conf, 5, 100);
  HAL_I2C_Master_Transmit(&hi2c4, DD9_ADDR << 1,  led_conf, 5, 100);
  HAL_I2C_Master_Transmit(&hi2c4, DD10_ADDR << 1, led_conf, 5, 100);
  dd7.GLOBAL_PWM  = GLOBAL_BRIGHTNESS;
  dd8.GLOBAL_PWM  = GLOBAL_BRIGHTNESS;
  dd9.GLOBAL_PWM  = GLOBAL_BRIGHTNESS;
  dd10.GLOBAL_PWM = GLOBAL_BRIGHTNESS;

  brightness_IND(0xFF);
  led_update();
}