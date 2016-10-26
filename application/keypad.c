/**
  ******************************************************************************
  ******************************************************************************
  *
  * @file	keypad.c
  * @author	R. Bush
  * @email	bush@krtkl.com
  * @version	v1.0
  * @date	2016 October 22
  * @brief	Keypad Reading Test Program
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

#define GPIO_JA1P5		(8)
#define GPIO_JA1P6		(11)
#define GPIO_JA1P7		(9)
#define GPIO_JA1P8		(10)
#define GPIO_JA1P11		(12)
#define GPIO_JA1P12		(15)
#define GPIO_JA1P13		(13)
#define GPIO_JA1P14		(14)

/* Keypad definitions */
#define KEYPAD_COL_1		(GPIO_BASE + GPIO_JA1P13)
#define KEYPAD_COL_2		(GPIO_BASE + GPIO_JA1P11)
#define KEYPAD_COL_3		(GPIO_BASE + GPIO_JA1P7)
#define KEYPAD_COL_4		(GPIO_BASE + GPIO_JA1P5)

#define KEYPAD_ROW_1		(GPIO_BASE + GPIO_JA1P14)
#define KEYPAD_ROW_2		(GPIO_BASE + GPIO_JA1P12)
#define KEYPAD_ROW_3		(GPIO_BASE + GPIO_JA1P8)
#define KEYPAD_ROW_4		(GPIO_BASE + GPIO_JA1P6)

#define BUFFER_LENGTH		(256)

#define GPIO_OUT		(1)
#define GPIO_IN			(0)

#define GPIO_HIGH		(1)
#define GPIO_LOW		(0)


static const char key_tab[] = {
	'1',
	'4',
	'7',
	'0',
	'2',
	'5',
	'8',
	'F',
	'3',
	'6',
	'9',
	'E',
	'A',
	'B',
	'C',
	'D'
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
  * @brief	Get GPIO Value
  *
  * @param  pin:	Pin ID to read value
  * @retval Value of pin state if successful, error status otherwise
  */
int gpio_read(int pin)
{
	int len, fid, status, retval;
	char pin_path[BUFFER_LENGTH];
	char pin_val[4];

	len = snprintf(pin_path, BUFFER_LENGTH, "/sys/class/gpio/gpio%d/value", pin);

	fid = open(pin_path, O_RDONLY);

	if (fid < 0) {
		fprintf(stderr, "Failed to open GPIO %d value for reading\n", pin);
		return -1;
	}

	status = read(fid, pin_val, 4);

	if (status < 0) {
		fprintf(stderr, "Failed to read GPIO %d value\n", pin);
		return -2;
	}

	close(fid);

	return atoi(pin_val);
}


/**
  * @brief	Initialize GPIO Pins
  *
  */
void gpio_init(void)
{
	gpio_export(KEYPAD_ROW_1);
	gpio_export(KEYPAD_ROW_2);
	gpio_export(KEYPAD_ROW_3);
	gpio_export(KEYPAD_ROW_4);

	sleep(1);
	gpio_direction(KEYPAD_ROW_1, GPIO_IN);
	gpio_direction(KEYPAD_ROW_2, GPIO_IN);
	gpio_direction(KEYPAD_ROW_3, GPIO_IN);
	gpio_direction(KEYPAD_ROW_4, GPIO_IN);

	gpio_export(KEYPAD_COL_1);
	gpio_export(KEYPAD_COL_2);
	gpio_export(KEYPAD_COL_3);
	gpio_export(KEYPAD_COL_4);

	sleep(1);
	gpio_direction(KEYPAD_COL_1, GPIO_OUT);
	gpio_direction(KEYPAD_COL_2, GPIO_OUT);
	gpio_direction(KEYPAD_COL_3, GPIO_OUT);
	gpio_direction(KEYPAD_COL_4, GPIO_OUT);

	gpio_write(KEYPAD_COL_1, GPIO_HIGH);
	gpio_write(KEYPAD_COL_2, GPIO_HIGH);
	gpio_write(KEYPAD_COL_3, GPIO_HIGH);
	gpio_write(KEYPAD_COL_4, GPIO_HIGH);
}


/**
  * @brief	Scan Keypad Column
  *
  * @param  col:	The column to scan
  * @retval 4 LSBs representing the column GPIO state
  */
uint16_t keypad_col_scan(int col)
{
	uint16_t col_state;

	gpio_write(col, GPIO_LOW);

	usleep(5 * 1000);

	col_state = !gpio_read(KEYPAD_ROW_1);
	col_state |= (!gpio_read(KEYPAD_ROW_2)) << 1;
	col_state |= (!gpio_read(KEYPAD_ROW_3)) << 2;
	col_state |= (!gpio_read(KEYPAD_ROW_4)) << 3;

	gpio_write(col, GPIO_HIGH);

	usleep(5 * 1000);

	return col_state;
}


/**
  * @brief	Scan Keypad
  *
  * @retval 16-bit field representing the keypad button states
  */
uint16_t keypad_scan(void)
{
	uint16_t kypd_state;

	kypd_state = keypad_col_scan(KEYPAD_COL_1);
	kypd_state |= keypad_col_scan(KEYPAD_COL_2) << 4;
	kypd_state |= keypad_col_scan(KEYPAD_COL_3) << 8;
	kypd_state |= keypad_col_scan(KEYPAD_COL_4) << 12;

	return kypd_state;
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
	int i;
	uint16_t scan_val, prev_val;
	char buf[BUFFER_LENGTH];

	if (argc > 1) {
		if (strcmp(argv[1], "init") == 0) {
			gpio_init();			/* Initialize GPIOs */
			return EXIT_SUCCESS;
		} else {
			printf("Invalid argument\n");
			return EXIT_FAILURE;
		}
	}

	while (1) {
		scan_val = keypad_scan();
		if (scan_val && (scan_val != prev_val)) {

			for (i = 0; i < 16; i++) {
				if (scan_val & (1 << i)) {
					snprintf(buf, BUFFER_LENGTH, "%c", key_tab[i]);

					if (execl("./display", "./display", buf, NULL) < 0) {
						printf("Error occurred executing display program: %d\n", errno);
					}
				}
			}
		}
		prev_val = scan_val;
	}
}
