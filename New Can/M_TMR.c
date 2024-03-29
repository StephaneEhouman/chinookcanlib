/*
Propri�t� du 
Club Chinook/ETS
*/
/******************************************************************
					M_TMR.c
******************************************************************/
 
 
#include "p33EP512MU810.h"
#include "Global.h"

/******************************************************************
					TMR3
******************************************************************/
void Init_Timer3(float freq)
{
	float div=2.0f;
	//Init Timer 3
	TMR3 = 0x0000;
	
	//Calibrate prescaller with given freq
	if(FOSC/(256.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*256.0f;	
		T3CONbits.TCKPS	= 0b11;
	}
	else if(FOSC/(64.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*64.0f;
		T3CONbits.TCKPS	= 0b10;
	}
	else if(FOSC/(8.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*8.0f;
		T3CONbits.TCKPS	= 0b01;
	}
	else
	{
		T3CONbits.TCKPS	= 0b00;
	}
	
	PR3 = (unsigned int)(FOSC/(div*freq));	
	div=1.0f/div;	
	_T3IF = 0;// Clear Timer3 interrupt
	_T3IP = 6;
	_T3IE = 1;// Disable Timer3 interrupt
	T3CONbits.TON = 1;// Start Timer3
}

/******************************************************************
					TMR5
******************************************************************/
void Init_Timer5(float freq)
{
	float div=2.0f;
	//Init Timer 5
	TMR5 = 0x0000;
	
	//Calibrate prescaller with given freq
	if(FOSC/(256.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*256.0f;	
		T5CONbits.TCKPS	= 0b11;
	}
	else if(FOSC/(64.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*64.0f;
		T5CONbits.TCKPS	= 0b10;
	}
	else if(FOSC/(8.0f*2.0f*freq)>2.0f)
	{
		div=2.0f*8.0f;
		T5CONbits.TCKPS	= 0b01;
	}
	else
	{
		T5CONbits.TCKPS	= 0b00;
	}
	
	PR5 = (unsigned int)(FOSC/(div*freq));	
	div=1.0f/div;	
	_T5IF = 0;// Clear Timer5 interrupt
	_T5IE = 1;// Enable Timer5 interrupt
	_T5IP = 5;
	T5CONbits.TON = 1;// Start Timer5
}





/**********************************************************/
void Init_Timer6(void)
{
	//Gate input
	_T6CKR = 47;
	//
	T6CON			=0;
	T6CONbits.TGATE =1;	//Gated mode-> count nbr of clock in Gate signal
	T6CONbits.TCKPS = 0b11; //1:256 prescaller
	PR6 = (unsigned int)(0.5f*FOSC/256.0f)/5.0;
	_T6IF=0;
	_T6IE=1;
	T6CONbits.TON	=1;
}

void Init_Timer7(void)
{
	//Gate input
	_T7CKR = 46;
	//
	T7CON			=0;
	T7CONbits.TGATE =1;	//Gated mode-> count nbr of clock in Gate signal
	T7CONbits.TCKPS = 0b11; //1:256 prescaller
	PR7 = (unsigned int)(0.5f*FOSC/256.0f)/5.0;
	_T7IF=0;
	_T7IE=1;
	T7CONbits.TON	=1;
}
/******************************************************************
					TMR8
******************************************************************

					TMR8 in CMD.c
*********************************************************/

void Init_Timer9(void)
{
	//Timer 9 Is used to divide the wind turbine input by 4
	//This frequency reduction is use by QEI
	_ODCD10 =0;	
	_RD10=    0;
	_TRISD10= 0;
	_T9CKR = 73;	// Input RPI20
	T9CON =0;
	PR9 = 1;	
	T9CONbits.TCS=1;
	_T9IF = 0;// Clear Timer3 interrupt
	_T9IP = 7;
	_T9IE = 1;// Disable Timer3 interrupt
	T9CONbits.TON = 1;// Start Timer3
}
