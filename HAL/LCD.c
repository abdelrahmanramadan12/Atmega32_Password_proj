
#include "StdTypes.h"
#include "DIO_interface.h"
#include "LCD.h"
#include "Utils.h"

#define  F_CPU 8000000
#include <util/delay.h>

/******************************8BIT_MODE***************************/
#if LCD_Mode==_8_BIT
static void WriteIns(u8 ins)
{
	
	DIO_Writepin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_Writepin(EN,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN,LOW);
	_delay_ms(1);
}


static void WriteData(u8 data)
{
	
	DIO_Writepin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_Writepin(EN,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN,LOW);
	_delay_ms(1);
}


void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0X38);
	
	WriteIns(0X0c);//0x0e,0x0f cursor
	
	WriteIns(0X01);//clear screen
	_delay_ms(1);//clear screen needs 2ms delay
	
	WriteIns(0X06);
	
	
}
/************************4BIT_MODE*************************/
#elif LCD_Mode==_4_BIT

static void WriteIns(u8 ins)
{
	
	DIO_Writepin(RS,LOW);
	DIO_Writepin(D7,READ_BIT(ins,7));
	DIO_Writepin(D6,READ_BIT(ins,6));
	DIO_Writepin(D5,READ_BIT(ins,5));
	DIO_Writepin(D4,READ_BIT(ins,4));
	DIO_Writepin(EN,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN,LOW);
	_delay_ms(1);
	
	DIO_Writepin(D7,READ_BIT(ins,3));
	DIO_Writepin(D6,READ_BIT(ins,2));
	DIO_Writepin(D5,READ_BIT(ins,1));
	DIO_Writepin(D4,READ_BIT(ins,0));
	DIO_Writepin(EN,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN,LOW);
	_delay_ms(1);
}


static void WriteData(u8 data)
{
	
	DIO_Writepin(RS,HIGH);
	
		DIO_Writepin(D7,READ_BIT(data,7));
		DIO_Writepin(D6,READ_BIT(data,6));
		DIO_Writepin(D5,READ_BIT(data,5));
		DIO_Writepin(D4,READ_BIT(data,4));
		DIO_Writepin(EN,HIGH);
		_delay_ms(1);
		DIO_Writepin(EN,LOW);
		_delay_ms(1);
		
		DIO_Writepin(D7,READ_BIT(data,3));
		DIO_Writepin(D6,READ_BIT(data,2));
		DIO_Writepin(D5,READ_BIT(data,1));
		DIO_Writepin(D4,READ_BIT(data,0));
		DIO_Writepin(EN,HIGH);
		_delay_ms(1);
		DIO_Writepin(EN,LOW);
		_delay_ms(1);
}


void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0X02);
	
	WriteIns(0X28);
	
	WriteIns(0X0c);//0x0e,0x0f cursor
	
	WriteIns(0X01);//clear screen
	_delay_ms(1);//clear screen needs 2ms delay
	
	WriteIns(0X06);
	
	
}
#endif
/******************************************************************/

void LCD_Clear(void)
{
	WriteIns(0X01);//clear screen
	_delay_ms(1);
}
void LCD_WriteNumber(s32 num)
{
	u8 i=0,str[14];
	s8 j;
	if (num==0)
	{
		LCD_WriteChar('0');
	}
	else if (num<0)
	{
		
		num=num*-1;
		LCD_WriteChar('-');
		while (num>0 )
		{
			str[i]=num%10+'0';
			num=num/10;
			i++;
			
		}
		for (j=i-1;j>=0;j--)
		{
			LCD_WriteChar(str[j]);
		}
	}
	else if (num>0)
	{
		
	
	while (num>0 )
	{
		str[i]=num%10+'0';
		num=num/10;
		i++;
		
	}
	for (j=i-1;j>=0;j--)
	{
	   LCD_WriteChar(str[j]);
	}
	}
}
void LCD_WriteBinary(u8 num)
{
	s8 i,flag=0;
	for (i=7;i>=0;i--)
	{
		if ((num>>i)&1)
		{
			LCD_WriteChar('1');
			flag =1;
		}
		else 
		{
			if (flag==1)
			{
                LCD_WriteChar('0');
			}
		}
	}
		
	 
}
void LCD_WriteHex(u8 num)
{
	u8 HN=num>>4;
	u8 LN=num&0x0f;
	if (HN<10)
	{
		LCD_WriteChar(HN+'0');
	}
	else 
	{
		LCD_WriteChar((HN-10)+'A');
	}
	if (LN<10)
	{
		LCD_WriteChar(LN+'0');
	}
	else
	{
		LCD_WriteChar((LN-10)+'A');
	}
}
void LCD_WriteNumber_4D(u16 num)
{
	LCD_WriteChar(((num%10000)/1000)+'0');
	LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar(((num%100)/10)+'0');
	LCD_WriteChar(((num%10)/1)+'0');
}
void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
	
	
}
void LCD_WriteString(u8*str)
{
	u8 i;
	for (i=0;str[i];i++)
	{
		LCD_WriteChar(str[i]);
	}
}
void LCD_GoTo(u8 line , u8 cell)
{
	if (line==0)
	{
		WriteIns(0x80+cell);
		
	}
	else if (line==1)
	{
		WriteIns(0x80+0x40+cell);
		
	}
	
}
void LCD_GoToString(u8 line,u8 cell,u8* str)
{
	LCD_GoTo(line,cell);
	LCD_WriteString(str);
}
void LCD_GoToClear(u8 line , u8 cell,u8 numOfCells)
{
	u8 i;
	LCD_GoTo(line,cell);
	for (i=0;i<numOfCells;i++)
	{
		LCD_WriteChar(' ');
	}
}
void LCD_Create_Character(u8*pattern,u8 address)
{
	u8 i;
	WriteIns(0x40+(address*8));// send the address of CGRAM
	for(i=0;i<8;i++)
	{
	  WriteData(pattern[i]);// pass the bytes of pattern on LCD
	}
	WriteIns(0x80); //back to DDRAM
}