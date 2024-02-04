#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"

#include "DIO_interface.h"
#include "LCD.h"
#include "KeyPad_interface.h"
#include "NVM.h"
#include "PASSWORD/PASSWORD.h"
#include "PASSWORD/Pass_App.h"

#define F_CPU 8000000
#include <util/delay.h>

#include <avr/io.h>



int main(void)
{
	
	DIO_init();
	
	LCD_Init();
	
	KEYPAD_Init();
	
	pass_voidSelections();
	
	while (1)	
{   
	
	 Pass_voidNumOfTries();

	
}

}

