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
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <i2c-dev.h>
// local includes
#include "config.h"

int twi_file;

static void startup_sequence();
static void start_conversation();
static void read_output();
static void decode_output();

int main()
{
    if ((twi_file = open(TWI_BUS, O_RDWR)) < 0)
    {
        perror("Failed to open the twi bus");
        return 1;
    }


    return 0;
}

static void startup_sequence()
{
    write(twi_file,     );

}


