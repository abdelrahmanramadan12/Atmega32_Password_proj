/*
 *      @file PASSWORD..h
 *
 *      Created on: Jan 20, 2023
 *      @author: Abdelrahman Ramadan 
 *      @brief PASSWORD header file 
 *
 */
#ifndef PASSWORD_H_
#define PASSWORD_H_
  
//101
  #define status_address 0x102
  
  #define pass_done 0x11
  #define pass_reset 0xff
  #define Psize 4
  #define NOT_STORED   0xFF
  #define PASS_SYMBOL (u8)'*'
  #define Pass_start 0x02
  
  
  /********************************************************/
  
  
 
  
  /*********************************************************/

 void SET_voidPASSWORD (void );

 u8 check_u8PASSWORD(void);
 
/** static u8 arrCompare (u8*arr1,u8*arr2,u8 size1,u8 size2); **/




#endif /* PASSWORD_H_ */