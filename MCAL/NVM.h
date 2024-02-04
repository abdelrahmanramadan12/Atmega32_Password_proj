/*
 * NVM.h
 *
 * Created: 2/25/2023 6:25:52 AM
 *  Author: abdelrahman ramadan 
 */ 


#ifndef NVM_H_
#define NVM_H_


u8 NVM_READ(u16 adress);

void  NVM_Write (u16 address ,u8 data);



#endif /* NVM_H_ */