/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  -
 *
 *        Version:  1.0
 *        Created:  28.03.2019 22:08:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Patrick Erdmann
 *   Organization:  -
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdbool.h>
#include <unistd.h>

// local includes
#include "config.h"
#include "register_names.h"

int twi_file;

bool check_chip();
uint16_t read_twi(uint8_t reg);
void write_twi(uint8_t reg, uint16_t value);
void get_measurement(uint16_t *ret_temp, uint16_t *ret_humid);

int main()
{
	uint16_t humidity, temp;

    if ((twi_file = open(TWI_BUS, O_RDWR)) < 0)
    {
        perror("Failed to open the TWI bus");
        return 1;
    }

	if (ioctl(twi_file, I2C_SLAVE, HDC_ADDR) < 0) 
	{
		perror("TWI address failed");
		return 1;
	}

	if (!check_chip())
	{
		perror("wrong HDC1080");
		return 1;
	}
	
	// configure HDC1080 to measure humidity and temperature at once and 14 bit resolution
	// additionally enable heating for humidity measurement
	write_twi(CONFIG_REG, DEFAULT_CONFIG | CONFIG_HEATING); 
	get_measurement(&temp, &humidity);	
	
	// calculate temperature and humidity values
	temp = temp * (160.0/65536.0) - 40.0;
	humidity = humidity * (100.0/65536.9);
	
	//disable heating
	write_twi(CONFIG_REG, DEFAULT_CONFIG);

	printf("Temperatur: %d, Humidity: %d \n", temp, humidity);
	return 0;
}

uint16_t read_twi(uint8_t reg)
{
	uint8_t buf[2];
	buf[0] = reg;
	buf[1] = 0;

	write(twi_file, buf, 1);
	read(twi_file, buf, 2);

	return ((uint16_t)(buf[0] << 8 | buf[1]));
}

void get_measurement(uint16_t *ret_temp, uint16_t *ret_humid)
{
	ssize_t r_size;
	uint8_t buf[4];
	*ret_temp = 0;
	*ret_humid = 0;
	
	buf[0] = TEMP_REG;

	write(twi_file, buf, 1);
	
	// read the measured values
	// sensor returns NACK until the measurement is ready
	while(r_size != 4)
	{
		r_size = read(twi_file, buf, 4);
	}

	*ret_temp = (uint16_t)(buf[0] << 8 | buf[1]);
	*ret_humid = (uint16_t)(buf[2] << 8 | buf[3]);
}

void write_twi(uint8_t reg, uint16_t value)
{
	uint8_t buf[3];

	buf[0] = reg;
	buf[1] = value >> 8;
	buf[2] = value & 0xff;

	write(twi_file, buf, 3);
}

bool check_chip()
{
	uint16_t manufactor_id, device_id;

	manufactor_id = read_twi(MANUFACTOR_ID_REG);
	device_id = read_twi(DEVICE_ID_REG);

	if (manufactor_id == DEFAULT_MAN_ID &&
		device_id == DEFAULT_DEV_ID )
	{
		return true;
	}
	return false;
}


