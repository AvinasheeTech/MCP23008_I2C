#include  "MCP23008_I2C.h"

/*i2c pin definition*/
#define SDA_PIN 21
#define SCL_PIN 22

MCP23008_I2C hmcp1(SDA_PIN,SCL_PIN);    //create object 

void setup() {
  // put your setup code here, to run once:

  /*set pin number 2 and 3 as o/p*/
  hmcp1.iodir_pin(MCP23008_IODIR_IO2_OUTPUT , GPIO_OUTPUT , MCP23008_ADDRESS_20);
  hmcp1.iodir_pin(MCP23008_IODIR_IO3_OUTPUT , GPIO_OUTPUT , MCP23008_ADDRESS_20);

  /*set pin number 6 and 7 as i/p*/
  hmcp1.iodir_pin(MCP23008_IODIR_IO6_INPUT , GPIO_INPUT  , MCP23008_ADDRESS_20);
  hmcp1.iodir_pin(MCP23008_IODIR_IO7_INPUT , GPIO_INPUT  , MCP23008_ADDRESS_20);

  /*configure pin number 7 as input pullup*/
  hmcp1.gppu_pin(MCP23008_GPPU_IO7_ENABLED , GPPU_ENABLED , MCP23008_ADDRESS_20);
}

void loop() {
  // put your main code here, to run repeatedly:

  /**/
  if((hmcp1.read_gpio_pin(MCP23008_GPIO_IO6_POS, MCP23008_ADDRESS_20)==1) || (hmcp1.read_gpio_pin(MCP23008_GPIO_IO7_POS, MCP23008_ADDRESS_20)==1)){
    hmcp1.set_gpio_pin(MCP23008_GPIO_IO2 , MCP23008_ADDRESS_20);
    hmcp1.set_gpio_pin(MCP23008_GPIO_IO3 , MCP23008_ADDRESS_20);
  }
  else{
    hmcp1.clear_gpio_pin(MCP23008_GPIO_IO2 , MCP23008_ADDRESS_20);
    hmcp1.clear_gpio_pin(MCP23008_GPIO_IO3 , MCP23008_ADDRESS_20);
  }
  
}
