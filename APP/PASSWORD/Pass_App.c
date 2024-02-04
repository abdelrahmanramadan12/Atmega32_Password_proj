/*
 *      @file Pass_App.c
 *
 *      Created on: Jan 20, 2023
 *      @author: Abdelrahman Ramadan 
 *      @brief Application source file ,including Pass selection function for select setting new pass or enter the old pass
                                       ,NumOfTries  runnable func to count the number of wrong pass entered   
 *
 */

#include "StdTypes.h"
#include "DIO_interface.h"
#include "KeyPad_interface.h"
#include "NVM.h"
#include "PASSWORD.h"
#include "Pass_App.h"

 #define F_CPU 8000000
 #include <util/delay.h>

 #include <avr/io.h>


/** Variables to store the number of failed password attempts*/
u8 Tries_Flag = 0;
u8 locFlag = 0,NewPass_Flag=0;

/*
 * Function to perform password-related selections
 */
void pass_voidSelections(void)
{
	
    u8 key_pressed = NO_KEY;
	
	
		SET_voidPASSWORD();
	
	
    /*
     * Check if password is already set
     */
    if (NVM_READ(status_address) == pass_done)
    {
        /*
         * Display options to reset or check password
         */
		LCD_Clear();
        LCD_WriteString("0: Reset pass");
        LCD_GoTo(1, 0);
        LCD_WriteString("1: Check pass");

        /*
         * Wait for a key press
         */
        key_pressed = NO_KEY;
        while (key_pressed == NO_KEY)
        {
            key_pressed = KEYPAD_GetKey();
        }

        /*
         * If '0' is pressed, reset the password
         */
        if (key_pressed == '0')
        {
			while(1)
			{
				LCD_Clear();
				LCD_WriteString("Enter the old pass");
				_delay_ms(1000);
				LCD_Clear();
				if (check_u8PASSWORD())
				{
					 NVM_Write(status_address, pass_reset);
					 break;
				}
				else 
				{
				    NewPass_Flag++;
				}
				
				if (NewPass_Flag>3)
				{
					while(1)
					{
						                DIO_Writepin(PINA7, HIGH);
						                LCD_Clear();
						                LCD_WriteString("Warning.");
						                _delay_ms(300);
						                
						                LCD_Clear();
						                LCD_WriteString("Warning..");
						                _delay_ms(300);
						                
						                LCD_Clear();
						                LCD_WriteString("Warning...");
						                _delay_ms(300);
					                
					}
				}
				
			}
            NVM_Write(status_address, pass_reset);
			 /**reset the password*/
			
        }
		
		SET_voidPASSWORD();
    }

  
}

/*
 * Function to handle the number of password attempts
 */
void Pass_voidNumOfTries(void)
{
    /*
     * If the password is correct
     */
    if (check_u8PASSWORD())
    {
        /*
         * Display success message
         */
        LCD_Clear();
        LCD_WriteString("Correct pass");
        DIO_Writepin(PIND0, HIGH);
        Tries_Flag = 0;
        _delay_ms(1000);
    }
    else
    {
        /*
         * If the password is incorrect
         */
        LCD_Clear();
        LCD_WriteString("Wrong pass");
        Tries_Flag++;
        _delay_ms(500);

        /*
         * Check the number of attempts
         */
        if (Tries_Flag < NUM_OF_VALID_TRIES)
        {
            /*
             * If attempts are within valid range, prompt to try again
             */
            LCD_GoTo(1, 0);
            LCD_WriteString("Try Again....");
            _delay_ms(1000);
        }
        else if (Tries_Flag >= NUM_OF_VALID_TRIES && Tries_Flag < NUM_OF_UNVALID_TRIES)
        {
            /*
             * If attempts exceed valid range but are within the threshold, wait for 15 seconds
             */
            LCD_Clear();
            LCD_WriteString("Wait for 15 Sec...");
            if (locFlag == 0)
            {
                /*
                 * Countdown for 15 seconds
                 */
                for (int i = 1; i <= 15; i++)
                {
                    LCD_GoTo(1, 0);
                    LCD_WriteNumber(i);
                    _delay_ms(1000);
                }
                locFlag++;
            }
        }
        else if (Tries_Flag >= NUM_OF_UNVALID_TRIES)
        {
            /*
             * If attempts exceed threshold, activate warning
             */
            while (Tries_Flag >= NUM_OF_UNVALID_TRIES)
            {
                DIO_Writepin(PINA7, HIGH);
                LCD_Clear();
                LCD_WriteString("Warning.");
                _delay_ms(300);
                
                LCD_Clear();
                LCD_WriteString("Warning..");
                _delay_ms(300);
                
                LCD_Clear();
                LCD_WriteString("Warning...");
                _delay_ms(300);
            }
        }
    }
}