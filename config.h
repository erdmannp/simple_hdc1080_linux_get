/*
 * =====================================================================================
 *
 *       Filename:  config.h
 *
 *    Description:  Configuration file for the driver
 *
 *        Version:  1.0
 *        Created:  28.03.2019 22:07:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Patrick Erdmann
 *   Organization:  -
 *
 * =====================================================================================
 */

#define TWI_BUS    "/dev/i2c-0"
#define HDC_ADDR    0x40

#define DEFAULT_MAN_ID		0x5449
#define DEFAULT_DEV_ID		0x1050
#define DEFAULT_CONFIG		0b0000100000000000
#define CONFIG_HEATING		0b0001000000000000

#define SLEEP_TIME			1000
