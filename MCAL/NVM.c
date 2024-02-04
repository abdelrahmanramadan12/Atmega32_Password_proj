
#include "StdTypes.h"
#include "MemMap.h"
#include "NVM.h"

u8 NVM_READ(u16 adress){
	
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	;
	/* Set up address register */
	EEAR = adress;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
	
	
}

void  NVM_Write (u16 address ,u8 data){
	
	
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	;
	/* Set up address and data registers */
	EEAR = address;
	EEDR = data;
	/* Write logical one to EEMWE */
	EECR |= (1<<EEMWE);
	/* Start EEProm write by setting EEWE */
	EECR |= (1<<EEWE);
	
}