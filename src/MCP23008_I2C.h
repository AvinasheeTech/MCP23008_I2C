/*@brief  library for interacting with  MCP23008 I/O expander 
          over i2c communication
  @pinout

         .---------.
   SCK-->|1  \_/ 18|<--VDD
    SI-->|    M    |<->GPA7
    SO<--|    C    |<->GPA6
    A1-->|    P    |<->GPA5
    A0-->|    2    |<->GPA4
~RESET-->|    3    |<->GPA3
   ~CS-->|    0    |<->GPA2
   INT<--|    0    |<->GPA1
   VSS-->!    8    |<->GPA0
         '---------'
*/

#ifndef _MCP23008_I2C_H_
#define _MCP23008_I2C_H_

#include <Wire.h> 
#include "Arduino.h"
#include <stdint.h> 

/* Register Definitions*/
#define REGISTER_IODIR		0x00
#define REGISTER_IOPOL		0x01
#define REGISTER_GPINTEN    0x02
#define REGISTER_DEFVAL		0x03
#define REGISTER_INTCON 	0x04
#define REGISTER_IOCON	    0x05
#define REGISTER_GPPU   	0x06
#define REGISTER_INTF   	0x07
#define REGISTER_INTCAP 	0x08
#define REGISTER_GPIO   	0x09
#define REGISTER_OLAT       0x0A

/* Hardware Address Pins(A0-A2) 
       A2    A1    A0        7-bit slave address
      GND   GND   GND              0x20
      GND   GND   VCC              0x21
      GND   VCC   GND              0x22
      GND   VCC   VCC              0x23
      VCC   GND   GND              0x24
      VCC   GND   VCC              0x25
      VCC   VCC   GND              0x26
      VCC   VCC   VCC              0x27
*/
#define MCP23008_ADDRESS_20   0x20
#define MCP23008_ADDRESS_21   0x21
#define MCP23008_ADDRESS_22   0x22
#define MCP23008_ADDRESS_23   0x23
#define MCP23008_ADDRESS_24   0x24
#define MCP23008_ADDRESS_25   0x25
#define MCP23008_ADDRESS_26   0x26
#define MCP23008_ADDRESS_27   0x27

/* I/O Direction
 Default state: MCP23008_IODIR_ALL_INPUT
 */
#define GPIO_INPUT   1    /*configure pin as gpio input*/
#define GPIO_OUTPUT  0    /*configure pin as gpio output*/

#define MCP23008_IODIR_ALL_OUTPUT 0x00
#define MCP23008_IODIR_ALL_INPUT  0xFF


#define MCP23008_IODIR_IO0_POS      0
#define MCP23008_IODIR_IO0_MSK      (1<<MCP23008_IODIR_IO0_POS)
#define MCP23008_IODIR_IO0_INPUT    MCP23008_IODIR_IO0_MSK
#define MCP23008_IODIR_IO0_OUTPUT   ~(MCP23008_IODIR_IO0_MSK)

#define MCP23008_IODIR_IO1_POS      1
#define MCP23008_IODIR_IO1_MSK      (1<<MCP23008_IODIR_IO1_POS)
#define MCP23008_IODIR_IO1_INPUT    MCP23008_IODIR_IO1_MSK
#define MCP23008_IODIR_IO1_OUTPUT   ~(MCP23008_IODIR_IO1_MSK)

#define MCP23008_IODIR_IO2_POS      2
#define MCP23008_IODIR_IO2_MSK      (1<<MCP23008_IODIR_IO2_POS)
#define MCP23008_IODIR_IO2_INPUT    MCP23008_IODIR_IO2_MSK
#define MCP23008_IODIR_IO2_OUTPUT   ~(MCP23008_IODIR_IO2_MSK)

#define MCP23008_IODIR_IO3_POS      3
#define MCP23008_IODIR_IO3_MSK      (1<<MCP23008_IODIR_IO3_POS)
#define MCP23008_IODIR_IO3_INPUT    MCP23008_IODIR_IO3_MSK
#define MCP23008_IODIR_IO3_OUTPUT   ~(MCP23008_IODIR_IO3_MSK)

#define MCP23008_IODIR_IO4_POS      4
#define MCP23008_IODIR_IO4_MSK      (1<<MCP23008_IODIR_IO4_POS)
#define MCP23008_IODIR_IO4_INPUT    MCP23008_IODIR_IO4_MSK
#define MCP23008_IODIR_IO4_OUTPUT   ~(MCP23008_IODIR_IO4_MSK)

#define MCP23008_IODIR_IO5_POS      5
#define MCP23008_IODIR_IO5_MSK      (1<<MCP23008_IODIR_IO5_POS)
#define MCP23008_IODIR_IO5_INPUT    MCP23008_IODIR_IO5_MSK
#define MCP23008_IODIR_IO5_OUTPUT   ~(MCP23008_IODIR_IO5_MSK)

#define MCP23008_IODIR_IO6_POS      6
#define MCP23008_IODIR_IO6_MSK      (1<<MCP23008_IODIR_IO6_POS)
#define MCP23008_IODIR_IO6_INPUT    MCP23008_IODIR_IO6_MSK
#define MCP23008_IODIR_IO6_OUTPUT   ~(MCP23008_IODIR_IO6_MSK)

#define MCP23008_IODIR_IO7_POS      7
#define MCP23008_IODIR_IO7_MSK      (1<<MCP23008_IODIR_IO7_POS)
#define MCP23008_IODIR_IO7_INPUT    MCP23008_IODIR_IO7_MSK
#define MCP23008_IODIR_IO7_OUTPUT   ~(MCP23008_IODIR_IO7_MSK)

/*Input Polarity
  Default state: MCP23008_IPOL_ALL_NORMAL
*/
#define GPIO_POLARITY_INVERTED   1      /*configure pin polarity as inverted*/
#define GPIO_POLARITY_NONINVERTED  0    /*configure pin polarity as non-inverted*/

#define MCP23008_IPOL_ALL_NORMAL    0x00
#define MCP23008_IPOL_ALL_INVERTED  0xFF

#define MCP23008_IPOL_IO0_POS         0
#define MCP23008_IPOL_IO0_MSK         (1<<MCP23008_IPOL_IO0_POS)
#define MCP23008_IPOL_IO0_INVERTED    MCP23008_IPOL_IO0_MSK
#define MCP23008_IPOL_IO0_NONINVERTED ~(MCP23008_IPOL_IO0_MSK)

#define MCP23008_IPOL_IO1_POS         1
#define MCP23008_IPOL_IO1_MSK         (1<<MCP23008_IPOL_IO1_POS)
#define MCP23008_IPOL_IO1_INVERTED    MCP23008_IPOL_IO1_MSK
#define MCP23008_IPOL_IO1_NONINVERTED ~(MCP23008_IPOL_IO1_MSK)

#define MCP23008_IPOL_IO2_POS         2
#define MCP23008_IPOL_IO2_MSK         (1<<MCP23008_IPOL_IO2_POS)
#define MCP23008_IPOL_IO2_INVERTED    MCP23008_IPOL_IO2_MSK
#define MCP23008_IPOL_IO2_NONINVERTED ~(MCP23008_IPOL_IO2_MSK)

#define MCP23008_IPOL_IO3_POS         3
#define MCP23008_IPOL_IO3_MSK         (1<<MCP23008_IPOL_IO3_POS)
#define MCP23008_IPOL_IO3_INVERTED    MCP23008_IPOL_IO3_MSK
#define MCP23008_IPOL_IO3_NONINVERTED ~(MCP23008_IPOL_IO3_MSK)

#define MCP23008_IPOL_IO4_POS         4
#define MCP23008_IPOL_IO4_MSK         (1<<MCP23008_IPOL_IO4_POS)
#define MCP23008_IPOL_IO4_INVERTED    MCP23008_IPOL_IO4_MSK
#define MCP23008_IPOL_IO4_NONINVERTED ~(MCP23008_IPOL_IO4_MSK)

#define MCP23008_IPOL_IO5_POS         5
#define MCP23008_IPOL_IO5_MSK         (1<<MCP23008_IPOL_IO5_POS)
#define MCP23008_IPOL_IO5_INVERTED    MCP23008_IPOL_IO5_MSK
#define MCP23008_IPOL_IO5_NONINVERTED ~(MCP23008_IPOL_IO5_MSK)

#define MCP23008_IPOL_IO6_POS         6
#define MCP23008_IPOL_IO6_MSK         (1<<MCP23008_IPOL_IO6_POS)
#define MCP23008_IPOL_IO6_INVERTED    MCP23008_IPOL_IO6_MSK
#define MCP23008_IPOL_IO6_NONINVERTED ~(MCP23008_IPOL_IO6_MSK)

#define MCP23008_IPOL_IO7_POS         7
#define MCP23008_IPOL_IO7_MSK         (1<<MCP23008_IPOL_IO7_POS)
#define MCP23008_IPOL_IO7_INVERTED    MCP23008_IPOL_IO7_MSK
#define MCP23008_IPOL_IO7_NONINVERTED ~(MCP23008_IPOL_IO7_MSK)

/*Input Pull-Up Resistor
  Default state: MCP23008_GPPU_ALL_DISABLED
*/
#define GPPU_ENABLED  1               /*configure internal pullup for pin*/
#define GPPU_DISABLED 0               /*disable pullup for pin*/

#define MCP23008_GPPU_ALL_DISABLED  0x00
#define MCP23008_GPPU_ALL_ENABLED   0xFF

#define MCP23008_GPPU_IO0_POS         0
#define MCP23008_GPPU_IO0_MSK         (1<<MCP23008_GPPU_IO0_POS)
#define MCP23008_GPPU_IO0_ENABLED     MCP23008_GPPU_IO0_MSK
#define MCP23008_GPPU_IO0_DISABLED    ~(MCP23008_GPPU_IO0_MSK)

#define MCP23008_GPPU_IO1_POS         1
#define MCP23008_GPPU_IO1_MSK         (1<<MCP23008_GPPU_IO1_POS)
#define MCP23008_GPPU_IO1_ENABLED     MCP23008_GPPU_IO1_MSK
#define MCP23008_GPPU_IO1_DISABLED    ~(MCP23008_GPPU_IO1_MSK)

#define MCP23008_GPPU_IO2_POS         2
#define MCP23008_GPPU_IO2_MSK         (1<<MCP23008_GPPU_IO2_POS)
#define MCP23008_GPPU_IO2_ENABLED     MCP23008_GPPU_IO2_MSK
#define MCP23008_GPPU_IO2_DISABLED    ~(MCP23008_GPPU_IO2_MSK)

#define MCP23008_GPPU_IO3_POS         3
#define MCP23008_GPPU_IO3_MSK         (1<<MCP23008_GPPU_IO3_POS)
#define MCP23008_GPPU_IO3_ENABLED     MCP23008_GPPU_IO3_MSK
#define MCP23008_GPPU_IO3_DISABLED    ~(MCP23008_GPPU_IO3_MSK)

#define MCP23008_GPPU_IO4_POS         4
#define MCP23008_GPPU_IO4_MSK         (1<<MCP23008_GPPU_IO4_POS)
#define MCP23008_GPPU_IO4_ENABLED     MCP23008_GPPU_IO4_MSK
#define MCP23008_GPPU_IO4_DISABLED    ~(MCP23008_GPPU_IO4_MSK)

#define MCP23008_GPPU_IO5_POS         5
#define MCP23008_GPPU_IO5_MSK         (1<<MCP23008_GPPU_IO5_POS)
#define MCP23008_GPPU_IO5_ENABLED     MCP23008_GPPU_IO5_MSK
#define MCP23008_GPPU_IO5_DISABLED    ~(MCP23008_GPPU_IO5_MSK)

#define MCP23008_GPPU_IO6_POS         6
#define MCP23008_GPPU_IO6_MSK         (1<<MCP23008_GPPU_IO6_POS)
#define MCP23008_GPPU_IO6_ENABLED     MCP23008_GPPU_IO6_MSK
#define MCP23008_GPPU_IO6_DISABLED    ~(MCP23008_GPPU_IO6_MSK)

#define MCP23008_GPPU_IO7_POS         7
#define MCP23008_GPPU_IO7_MSK         (1<<MCP23008_GPPU_IO7_POS)
#define MCP23008_GPPU_IO7_ENABLED     MCP23008_GPPU_IO7_MSK
#define MCP23008_GPPU_IO7_DISABLED    ~(MCP23008_GPPU_IO7_MSK)

/*GPIO Data 
*/
#define MCP23008_GPIO_ALL_HIGH    0xFF
#define MCP23008_GPIO_ALL_LOW     0x00

#define MCP23008_GPIO_IO0_POS         0
#define MCP23008_GPIO_IO0_MSK         (1<<MCP23008_GPIO_IO0_POS)
#define MCP23008_GPIO_IO0             MCP23008_GPIO_IO0_MSK

#define MCP23008_GPIO_IO1_POS         1
#define MCP23008_GPIO_IO1_MSK         (1<<MCP23008_GPIO_IO1_POS)
#define MCP23008_GPIO_IO1             MCP23008_GPIO_IO1_MSK

#define MCP23008_GPIO_IO2_POS         2
#define MCP23008_GPIO_IO2_MSK         (1<<MCP23008_GPIO_IO2_POS)
#define MCP23008_GPIO_IO2             MCP23008_GPIO_IO2_MSK

#define MCP23008_GPIO_IO3_POS         3
#define MCP23008_GPIO_IO3_MSK         (1<<MCP23008_GPIO_IO3_POS)
#define MCP23008_GPIO_IO3             MCP23008_GPIO_IO3_MSK

#define MCP23008_GPIO_IO4_POS         4
#define MCP23008_GPIO_IO4_MSK         (1<<MCP23008_GPIO_IO4_POS)
#define MCP23008_GPIO_IO4             MCP23008_GPIO_IO4_MSK

#define MCP23008_GPIO_IO5_POS         5
#define MCP23008_GPIO_IO5_MSK         (1<<MCP23008_GPIO_IO5_POS)
#define MCP23008_GPIO_IO5             MCP23008_GPIO_IO5_MSK

#define MCP23008_GPIO_IO6_POS         6
#define MCP23008_GPIO_IO6_MSK         (1<<MCP23008_GPIO_IO6_POS)
#define MCP23008_GPIO_IO6             MCP23008_GPIO_IO6_MSK

#define MCP23008_GPIO_IO7_POS         7
#define MCP23008_GPIO_IO7_MSK         (1<<MCP23008_GPIO_IO7_POS)
#define MCP23008_GPIO_IO7             MCP23008_GPIO_IO7_MSK


class MCP23008_I2C{
      public:

      	MCP23008_I2C(uint8_t sda=21,uint8_t scl=22);    //constructor with default sda and scl pin definition

      	/*functions for operations*/
        uint8_t read(uint16_t reg, uint8_t address);
        void write(uint16_t reg, uint8_t data, uint8_t address);
        void iodir_port(uint8_t iodir, uint8_t address);
        void iodir_pin(uint8_t pin_data, uint8_t gpio_config, uint8_t address);
        void ipol_port(uint8_t ipol, uint8_t address);
        void ipol_pin(uint8_t pin_data, uint8_t polarity_config,uint8_t address);
        void gppu_port(uint8_t pu, uint8_t address);
        void gppu_pin(uint8_t pin_data, uint8_t pullup_config, uint8_t address);
        uint8_t  read_gpio(uint8_t address);
        void write_gpio(uint8_t data, uint8_t address);
        uint8_t read_gpio_pin(uint8_t pin_pos, uint8_t address);
        void set_gpio_pin(uint8_t pin_data, uint8_t address);
        void clear_gpio_pin(uint8_t pin_data, uint8_t address);

};


#endif
