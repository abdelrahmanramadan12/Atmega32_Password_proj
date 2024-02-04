/*
 *      @file PASSWORD.c
 *
 *      Created on: Jan 20, 2023
 *      @author: Abdelrahman Ramadan 
 *      @brief PASSWORD source file ,including functions for set and check password  
 *
 */


#include "StdTypes.h"
#include "NVM.h"
#include "LCD.h"
#include "KeyPad_interface.h"
#include "PASSWORD.h"

 #define F_CPU 8000000
 #include <util/delay.h>

 #include <avr/io.h>
 
 

u8 flagPass = 0;

/** Global variables to store password **/
u8 var1, var2, var3, var4;


/**************************************************************************
*   @fn SET_voidPASSWORD
*   @brief Function to set the password 
*/

void SET_voidPASSWORD(void)
{
	u8 key_pressed = NO_KEY; // Variable to store the pressed key

	/* Check if password is already set */
	if (NVM_READ(status_address) != pass_done)
	{
		LCD_Clear();
		LCD_WriteString("Set pass");
		LCD_GoTo(1, 0);
		LCD_WriteString("pass:");

		u8 passCounter = 0;
		u8 pass[Psize] = {NOT_STORED, NOT_STORED, NOT_STORED, NOT_STORED}; // Array to store the password

		LCD_GoTo(1, 7);

		/* Loop to read user input for password */
		while (passCounter < Psize)
		{
			key_pressed = NO_KEY;

			/* Wait until a key is pressed */
			while (key_pressed == NO_KEY)
			{
				key_pressed = KEYPAD_GetKey();
			}

			pass[passCounter] = key_pressed;

			/* Display the pressed key on the LCD */
			LCD_WriteChar(key_pressed);
			_delay_ms(200);

			/* Display a symbol to hide the entered key */
			LCD_GoTo(1, 7 + passCounter);
			LCD_WriteChar(PASS_SYMBOL);
			_delay_ms(100);

			passCounter++;
		}

		/* Mark password as set in the non-volatile memory (NVM) */
		NVM_Write(status_address, pass_done);

		/* Store the password in NVM */
		u8 i, j = Pass_start;
		for (i = 0; i < Psize; i++)
		{
			NVM_Write(j, pass[i]);
			j++;
		}
	}

	/* Read the password from NVM and store in global variables */
	var1 = NVM_READ(Pass_start);
	var2 = NVM_READ(Pass_start + 1);
	var3 = NVM_READ(Pass_start + 2);
	var4 = NVM_READ(Pass_start + 3);
}




/**************************************************************************
*   @fn check_PASSWORD
*   @brief Function to check the entered password
***************************************************************************/
 
u8 check_u8PASSWORD()
{
	u8 key_pressed = NO_KEY; /** Variable to store the pressed key **/

	/** Clear the LCD and display prompt **/
	LCD_Clear();
	LCD_WriteString("Enter the pass");
	LCD_GoTo(1, 0);
	LCD_WriteString("pass:");
	LCD_GoTo(1, 10);

	/* Loop until the flag is set */
	while (flagPass == 0)
	{
		u8 arrCounter = 0;
		u8 checkArr[Psize] = {NOT_STORED, NOT_STORED, NOT_STORED, NOT_STORED}; // Array to store the entered password

		LCD_GoTo(1, 7);

		/* Loop to read user input for password */
		while (arrCounter < Psize)
		{
			key_pressed = NO_KEY;

			/* Wait until a key is pressed */
			while (key_pressed == NO_KEY)
			{
				key_pressed = KEYPAD_GetKey();
			}

			checkArr[arrCounter] = key_pressed;

			/* Display the pressed key on the LCD */
			LCD_WriteChar(key_pressed);
			_delay_ms(200);

			/* Display a symbol to hide the entered key */
			LCD_GoTo(1, 7 + arrCounter);
			LCD_WriteChar(PASS_SYMBOL);
			_delay_ms(100);

			arrCounter++;
		}

		/* Check if the entered password matches the stored password */
		if (checkArr[0] == var1 && checkArr[1] == var2 && checkArr[2] == var3 && checkArr[3] == var4)
		{
			/* If password matches, clear the LCD and return 1 (success) */
			LCD_Clear();
			return 1;
		}
		else
		{
			/* If password does not match, clear the LCD and return 0 (failure) */
			LCD_Clear();
			return 0;
		}
	}
}
