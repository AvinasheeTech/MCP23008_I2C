*****************MCP23008 library for arduino based environment.******************

example is based on ESP-32 board.

*choose mcp23008 address based on logic levels of your hardware addressable pins.


<img width="288" alt="Capture_1" src="https://user-images.githubusercontent.com/101040017/157226627-4e5a319b-acb2-408d-a0d8-2d7488a84df4.PNG">
#define MCP23008_ADDRESS_20   0x20

#define MCP23008_ADDRESS_21   0x21

#define MCP23008_ADDRESS_22   0x22

#define MCP23008_ADDRESS_23   0x23

#define MCP23008_ADDRESS_24   0x24

#define MCP23008_ADDRESS_25   0x25

#define MCP23008_ADDRESS_26   0x26

#define MCP23008_ADDRESS_27   0x27


*select sda and scl pin number based on the board you choose. (Default SDA-21, SCL-22 for esp32).
#define SDA_PIN 21
#define SCL_PIN 22


*choose configurations as per below:
gpio_config -  GPIO_INPUT  ->  1
               GPIO_OUTPUT ->  0

polarity_config - GPIO_POLARITY_INVERTED    ->    1
                  GPIO_POLARITY_NONINVERTED ->    0

pullup_config - GPPU_ENABLED  1 
                GPPU_DISABLED 0 


         functions available :

uint8_t read(uint16_t reg, uint8_t address);            //read register
 
void write(uint16_t reg, uint8_t data, uint8_t address); //write register

void iodir_port(uint8_t iodir, uint8_t address);         //set i/o direction for the port at once
 
void iodir_pin(uint8_t pin_data, uint8_t gpio_config, uint8_t address);      //set i/o direction for individual pin

void ipol_port(uint8_t ipol, uint8_t address);           //set polarity for the port at once

void ipol_pin(uint8_t pin_data, uint8_t polarity_config,uint8_t address);    //set individual pin polarity

void gppu_port(uint8_t pu, uint8_t address);             //set internal pullup for the port 

void gppu_pin(uint8_t pin_data, uint8_t pullup_config, uint8_t address);     //set pullup for individual pins

uint8_t  read_gpio(uint8_t address);                    //read gpio port data

void write_gpio(uint8_t data, uint8_t address);         //write data to gpio port
        
uint8_t read_gpio_pin(uint8_t pin_pos, uint8_t address);     //read gpio pin 
        
void set_gpio_pin(uint8_t pin_data, uint8_t address);        //set gpio pin logic high
        
void clear_gpio_pin(uint8_t pin_data, uint8_t address);      //set gpio pin logic low
