/**
  ******************************************************************************
  ******************************************************************************
  *
  * @file	display.c
  * @author	R. Bush
  * @email	bush@krtkl.com
  * @version	v1.0
  * @date	2016 October 24
  * @brief	7-Segment Display Output Test Program
  * @license	FreeBSD
  *
  ******************************************************************************
  *
  * Copyright (c) 2016, krtkl inc.
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted provided that the following conditions are met:
  *
  * 1.	Redistribution of source code must retain the above copyright notice,
  *	this list of conditions and the following disclaimer.
  * 2.	Redistributions in binary form must reproduce the above copyright notice,
  *	this list of conditions and the following disclaimer in the documentation
  *	and/or other materials provided with the distribution.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVICED OF THE
  * POSSIBILITY OF SUCH DAMAGE.
  *
  * The views and conclusions contained in the software and documentation are
  * those of the authors and should not be interpreted as representing official
  * policies, either expressed or implied, of the FreeBSD Project.
  *
  ******************************************************************************
  */

/*---------------------------------- Includes --------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/types.h>


/*----------------------------------- Defines --------------------------------*/
#define ASCII_ESC		(0x1B)

#define GPIO_BASE		(881)		/**< GPIO block base chip */

#define GPIO_JA1P36		(23)
#define GPIO_JA1P37		(7)
#define GPIO_JA1P38		(22)

/* Display definitions */
#define DISPLAY_DATA		(GPIO_BASE + GPIO_JA1P38)
#define DISPLAY_CLK		(GPIO_BASE + GPIO_JA1P37)
#define DISPLAY_LATCH		(GPIO_BASE + GPIO_JA1P36)

#define BUFFER_LENGTH		(256)

#define GPIO_OUT		(1)
#define GPIO_IN			(0)

#define GPIO_HIGH		(1)
#define GPIO_LOW		(0)


static const uint8_t disp_data_tab[] = {
	0xC0,					/* 0 */
	0xF9,					/* 1 */
	0xA4,					/* 2 */
	0xB0,					/* 3 */
	0x99,					/* 4 */
	0x92,					/* 5 */
	0x82,					/* 6 */
	0xF8,					/* 7 */
	0x80,					/* 8 */
	0x90,					/* 9 */
	0x88,					/* A */
	0x83,					/* b */
	0xC6,					/* C */
	0xA1,					/* d */
	0x86,					/* E */
	0x8E,					/* F */
	0xFF,					/* OFF */
};


/**
  * @brief	Export GPIO Pin
  *
  * @param  pin:	Pin ID to export
  * @retval 0 on success, error status otherwise
  */
int gpio_export(int pin)
{
	int len, fid;
	char buf[BUFFER_LENGTH];

	fid = open("/sys/class/gpio/export", O_WRONLY);

	if (fid < 0) {
		fprintf(stderr, "Failed to open export pin %d for writing\n", pin);
		return -1;
	}

	len = snprintf(buf, BUFFER_LENGTH, "%d", pin);

	write(fid, buf, len);
	close(fid);

	return 0;
}


/**
  * @brief	Set GPIO Direction
  *
  * @param  pin:	Pin ID to set direction
  * @param  dir:	Pin direction to set
  *			This parameter can have the following values:
  *			@arg GPIO_IN: Set the direction as input
  *			@arg GPIO_OUT: Set the direction as output
  * @retval 0 on success, error status otherwise
  */
int gpio_direction(int pin, int dir)
{
	int len, fid, status;
	char pin_path[BUFFER_LENGTH];
	char pin_dir[4];

	len = snprintf(pin_path, BUFFER_LENGTH, "/sys/class/gpio/gpio%d/direction", pin);

	fid = open(pin_path, O_WRONLY);

	if (fid < 0) {
		fprintf(stderr, "Failed to open GPIO %d direction for writing\n", pin);
		return -1;
	}

	len = snprintf(pin_dir, 4, (dir ? "out" : "in"));

	status = write(fid, pin_dir, len);

	if (status < 0) {
		fprintf(stderr, "Failed to set direction for GPIO\n");
		return -2;
	}

	close(fid);

	return 0;
}


/**
  * @brief	Set GPIO Value
  *
  * @param  pin:	Pin ID to write value
  * @param  val:	Value to write to the output pin
  *			This parameter can have the following values:
  *			@arg GPIO_HIGH: Set the gpio output high
  *			@arg GPIO_LOW: Set the gpio output low
  * @retval 0 on success, error status otherwise
  */
int gpio_write(int pin, int val)
{
	int len, fid, status;
	char pin_path[BUFFER_LENGTH];
	char pin_val[4];

	len = snprintf(pin_path, BUFFER_LENGTH, "/sys/class/gpio/gpio%d/value", pin);

	fid = open(pin_path, O_WRONLY);

	if (fid < 0) {
		fprintf(stderr, "Failed to open GPIO %d value for writing\n", pin);
		return -1;
	}

	len = snprintf(pin_val, 4, "%d", val);

	status = write(fid, pin_val, len);

	if (status < 0) {
		fprintf(stderr, "Failed to set value for GPIO %d\n", pin);
		return -2;
	}

	close(fid);

	return 0;
}


/**
  * @brief	Initialize GPIO Pins
  *
  */
void gpio_init(void)
{
	gpio_export(DISPLAY_CLK);
	gpio_export(DISPLAY_DATA);
	gpio_export(DISPLAY_LATCH);

	sleep(1);
	gpio_direction(DISPLAY_CLK, GPIO_OUT);
	gpio_direction(DISPLAY_DATA, GPIO_OUT);
	gpio_direction(DISPLAY_LATCH, GPIO_OUT);

	gpio_write(DISPLAY_CLK, GPIO_LOW);
	gpio_write(DISPLAY_DATA, GPIO_LOW);
	gpio_write(DISPLAY_LATCH, GPIO_LOW);
}



/**
  * @brief	Clear Display
  *
  */
void display_clear(void)
{
	int i;

	gpio_write(DISPLAY_DATA, GPIO_HIGH);
	for (i = 0; i < 64; i++) {
		gpio_write(DISPLAY_CLK, GPIO_LOW);
		gpio_write(DISPLAY_CLK, GPIO_HIGH);
	}

	gpio_write(DISPLAY_DATA, GPIO_LOW);
	gpio_write(DISPLAY_CLK, GPIO_LOW);
	gpio_write(DISPLAY_LATCH, GPIO_HIGH);
	gpio_write(DISPLAY_LATCH, GPIO_LOW);
}


/**
  * @brief	Write 8-bit Value to Display
  *
  */
void display_write(uint8_t val)
{
	int i, data;

	/* The data is input most significant bit first (MSB first) */

	data = val;
	for (i = 0; i < 8; i++) {
		data = (val >> (7 - i)) & 0x01;
		gpio_write(DISPLAY_CLK, GPIO_LOW);

		/* Set the value of the data pin */
		gpio_write(DISPLAY_DATA, data);

		gpio_write(DISPLAY_CLK, GPIO_HIGH);
	}
}


/**
  ******************************************************************************
  *
  * @mainpage
  *
  *
  */
int main(int argc, char *argv[])
{
	int i, status, index, len;
	unsigned int val;
	uint8_t disp_out[8];
	char tmp[2];

        if (argc != 2) {
                printf("Invalid number of arguments\n");
		return EXIT_FAILURE;
	}

	/* Handle initialization of the GPIOs and display */
	if (strcmp(argv[1], "init") == 0) {
		gpio_init();			/* Initialize GPIOs */
		display_clear();		/* Reset the display */
		return EXIT_SUCCESS;
	}

	memset(disp_out, 0xFF, sizeof(disp_out));

	len = strlen(argv[1]);
	while (len--) {
		/* Iterate over each character */
		if (isxdigit(*argv[1])) {
			/* The character is a hexidecimal number */
			tmp[0] = *argv[1];
			if (len < 8) {
				/* Put the character in the display output */
				disp_out[len] = disp_data_tab[atoi(tmp)];
			}
		} else if (*argv[1] == '.') {
			if (len == 7) {
				disp_out[len] = 0x40;
			} else if (len < 7) {
				disp_out[len + 1] &= 0x7F;
			}
		} else {
			printf("Invalid digit %c at index %d\n", *argv[1], len);
			return EXIT_FAILURE;
		}

		argv[1]++;		/* Go to next character */
	}

	display_clear();
	for (i = 0; i < 8; i++) {
		display_write(disp_out[i]);
	}
		gpio_write(DISPLAY_LATCH, GPIO_HIGH);
		gpio_write(DISPLAY_LATCH, GPIO_LOW);
}
