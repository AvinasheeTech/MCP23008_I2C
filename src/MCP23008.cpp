#include  "MCP23008_I2C.h"



/*@brief initialize i2c 
  @param sda and scl pin number
*/
MCP23008_I2C::MCP23008_I2C(uint8_t sda,uint8_t scl){
	Wire.begin(sda,scl);
}



/*@brief  read the register value 
  @param  register address to read,and i2c address of the device
  @retval current register data
*/
uint8_t MCP23008_I2C::read(uint16_t reg, uint8_t address){
	uint8_t c;
    Wire.beginTransmission(address);    //send start bit
    Wire.write(reg);                    //send write bit with i2c slave address
    Wire.endTransmission();             //send stop bit 

    Wire.requestFrom(address, 1);       

    while (Wire.available()) { // slave may send less than requested
      c = Wire.read();         // receive a byte as character
      Serial.print(c);         // print the character
    }

    return c;
}



/*@brief  write data to register 
  @param  register address to write to,data to be written
          and i2c address of the device
  @retval None
*/
void MCP23008_I2C::write(uint16_t reg, uint8_t data, uint8_t address){
	Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
}

/*@brief  set i/o direction of port
  @param  i/o direction port data and i2c address of the device
  @retval None
*/
void MCP23008_I2C::iodir_port(uint8_t iodir, uint8_t address){
	write(REGISTER_IODIR,iodir,address);
}

/*@brief  set i/o direction of individual pins
  @param  i/o direction pin data, configuration format(i.e input or output) and i2c address of the device
  @retval None
*/
void MCP23008_I2C::iodir_pin(uint8_t pin_data, uint8_t gpio_config, uint8_t address){
	/*read existing port data*/
    uint8_t reg_data = read(REGISTER_IODIR,address);

    if(gpio_config==GPIO_INPUT){
        reg_data = reg_data | pin_data;
        write(REGISTER_IODIR,reg_data,address);
    }
    else if(gpio_config==GPIO_OUTPUT){
    	reg_data = reg_data & pin_data;
        write(REGISTER_IODIR,reg_data,address);
    }
    else{
    }
    
}

/*@brief  configure the polarity of I/O port at once
  @param  i/o polarity port data and i2c address of the device
  @retval None
  @note 1 = GPIO register bit reflects the opposite logic state of the input pin.
        0 = GPIO register bit reflects the same logic state of the input pin.
*/
void MCP23008_I2C::ipol_port(uint8_t ipol, uint8_t address){
	write(REGISTER_IOPOL,ipol,address);
}

/*@brief  set polarity of individual pins
  @param  polarity pin data, configuration format(i.e inverted or same) and i2c address of the device
  @retval None
*/
void MCP23008_I2C::ipol_pin(uint8_t pin_data, uint8_t polarity_config,uint8_t address){
	/*read existing port data*/
    uint8_t reg_data = read(REGISTER_IOPOL,address);

    if(polarity_config==GPIO_POLARITY_INVERTED){
        reg_data = reg_data | pin_data;
        write(REGISTER_IOPOL,reg_data,address);
    }
    else if(polarity_config==GPIO_POLARITY_NONINVERTED){
    	reg_data = reg_data & pin_data;
        write(REGISTER_IOPOL,reg_data,address);
    }
    else{
    }
}

/*@brief  set input pullup value for the port at once 
  @param  pullup port data and i2c address of the device
  @retval None
*/
void MCP23008_I2C::gppu_port(uint8_t pu, uint8_t address){
	write(REGISTER_GPPU,pu,address);
}

/*@brief  set pullup resistor for individual pins
  @param  pullup pin data, configuration format(i.e enabled or disabled) and i2c address of the device
  @retval None
*/
void MCP23008_I2C::gppu_pin(uint8_t pin_data, uint8_t pullup_config, uint8_t address){
	/*read existing port data*/
    uint8_t reg_data = read(REGISTER_GPPU,address);

    if(pullup_config==GPPU_ENABLED){
      reg_data = reg_data | pin_data;
      write(REGISTER_GPPU,reg_data,address);
    }
    else if(pullup_config==GPPU_DISABLED){
    	reg_data = reg_data & pin_data;
      write(REGISTER_GPPU,reg_data,address);
    }
    else{
    	
    }
}

/*@brief  read current gpio port status
  @param  i2c address of the device
  @retval gpio data
*/
uint8_t  MCP23008_I2C::read_gpio(uint8_t address){
	uint8_t c;
  c = read(REGISTER_GPIO,address);

  return c;
}

/*@brief  write gpio port data
  @param  data to be written and i2c address of the device
  @retval None
*/
void MCP23008_I2C::write_gpio(uint8_t data, uint8_t address)
{
  write(REGISTER_GPIO,data,address);
}

/*@brief  read gpio port pin data
  @param  i/o pin to be read and i2c address of the device
  @retval current gpio pin state
*/
uint8_t  MCP23008_I2C::read_gpio_pin(uint8_t pin_pos, uint8_t address)
{
  /*read existing port data*/
  uint8_t reg_data = read_gpio(address);

  reg_data = reg_data & (1<<pin_pos);
  return (reg_data>>pin_pos);
}

/*@brief  set selected gpio port pin
  @param  i/o pin data and i2c address of the device
  @retval None
*/
void MCP23008_I2C::set_gpio_pin(uint8_t pin_data, uint8_t address)
{
  /*read existing port data*/
  uint8_t reg_data = read_gpio(address);
  reg_data = reg_data | pin_data;

  /*write updated data*/
  write_gpio(reg_data,address);
}

/*@brief  clear selected gpio port pin
  @param  i/o pin clear data and i2c address of the device
  @retval None
*/
void MCP23008_I2C::clear_gpio_pin(uint8_t pin_data, uint8_t address)
{
  /*read existing port data*/
  uint8_t reg_data = read_gpio(address);

  pin_data ^= 0xFF;
  reg_data = reg_data & pin_data;

  /*write updated data*/
  write_gpio(reg_data,address);

}
