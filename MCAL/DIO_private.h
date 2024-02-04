/*
 * DIO_private.h
 *
 * Created: 11/5/2022 4:34:35 PM
 *  Author: abdel
 */ 


#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

extern const DIO_Pinstatus_type PinStatusArray[TOTAL_PINS];

static void DIO_initPin(DIO_pin_type pin,DIO_Pinstatus_type status);

#endif /* DIO_PRIVATE_H_ */