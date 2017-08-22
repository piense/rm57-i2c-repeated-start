/** @file HL_sys_main.c 
*   @brief Application main file
*   @date 02-Mar-2016
*   @version 04.05.02
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "HL_sys_common.h"

/* USER CODE BEGIN (1) */

#include "HL_i2c.h"

/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */


#define DATA_COUNT  10

#define Master_Address 0x26
#define Slave_Address  0x1D

//For mma8451. Demo of repeated start condition.
uint8_t readReg(i2cBASE_t *i2c, uint8_t reg)
{
	/* Configure address of Slave to talk to */
	i2cSetSlaveAdd(i2c, Slave_Address);

	/* Set direction to Transmitter */
	/* Note: Optional - It is done in Init */
	i2cSetDirection(i2c, I2C_TRANSMITTER);

	//Transmitting 1 data byte
	i2cSetCount(i2c,1);

	//Clear STP bit
	i2c->MDR &= 0xF7FF;

	/* Set mode as Master */
	i2cSetMode(i2c, I2C_MASTER);

	/* Transmit Start Condition */
	i2cSetStart(i2c);

	//Transmit the register to read
	i2cSendByte(i2c, 0x14);

    while ((i2c->STR & (uint32)I2C_ARDY) == 0U  )
    {
    } /* Wait */

	// Set direction to receiver
	i2cSetDirection(i2c, I2C_RECEIVER);

	/* Set mode as Master */
	i2cSetMode(i2c, I2C_MASTER);

	// Transmit Repeat Start Condition
	i2cSetStart(i2c);

	i2cSetCount(i2c,1);

	i2cSetStop(i2c);

	// Get the register data
	return i2cReceiveByte(i2c);

}

/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */

	i2cInit();

	uint8_t WHO_AM_I1 = readReg(i2cREG1,0x0D);
	uint8_t WHO_AM_I2 = readReg(i2cREG2,0x0D);

	uint8_t PL_BF_ZCOMP1 = readReg(i2cREG1,0x13);
	uint8_t PL_BF_ZCOMP2 = readReg(i2cREG2,0x13);


	asm(" nop");
	asm(" nop");
	asm(" nop");
	while(1);


/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */
