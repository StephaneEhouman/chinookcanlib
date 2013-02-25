#include "p33EP512MU810.h"
#include "Global.h"
#include "CMD.h"
#include "M_UART.h"
#include <stdio.h>
extern char print;			//Flag to send data
/******************************************************************
					TIMER ISR
******************************************************************/
void __attribute__((interrupt,no_auto_psv))_T5Interrupt(void) 
{
	print = 1;
	IFS1bits.T5IF = 0;
}
extern unsigned int ecan1MsgBuf[NUM_OF_ECAN_BUFFERS][8] 
 __attribute__((aligned(NUM_OF_ECAN_BUFFERS * 16)));

/*******************************************************************/
/***********************  Communication   **************************/
/*******************************************************************/



/***************************** INTERRUPT DMA1 **************************
* Description : Routine d'interruption du module CAN1 (TX).
*				Note: interruption non-utilisé
* Input :	AUCUN
*
* Output :	AUCUN
*
************************************************************************/

void __attribute__((interrupt, auto_psv)) _DMA0Interrupt(void)
{

	//_RA4 =~ _RA4;
	IFS0bits.DMA0IF = 0;		// Clear the DMA0 Interrupt Flag
}

/***************************** INTERRUPT DMA1 **************************
* Description : Routine d'interruption du module CAN1 (RX).
*				Note: interruption non-utilisé
* Input :	AUCUN
*
* Output :	AUCUN
*
************************************************************************/

void __attribute__((__interrupt__,no_auto_psv)) _DMA1Interrupt(void)
{
	//_RA2 =~ _RA2;
	_DMA1IF = 0; // Clear the DMA0 Interrupt Flag
}

/***************************** INTERRUPT CAN1 **************************
* Description : Routine d'interruption du module CAN1.
*
* Input :	AUCUN
*
* Output :	AUCUN
*
************************************************************************/


void __attribute__((interrupt,no_auto_psv))_C1Interrupt(void) 
{
//	int i;
//	char temp_win;
	
	_C1IF = 0;
	
//	unsigned int buff = C1RXD;
	
	_RA3 =~ _RA3;
	if(C1INTFbits.RBIF == 1)
	{
		
		print =1;
		
		C1RXFUL1 = 0;
		C1INTFbits.RBIF = 0;
	}	
	
	if(C1INTFbits.TBIF == 1)
	{
		C1INTFbits.TBIF = 0;
		/* C'est un buffer configuré en Tx qui a généré l'interrupt. */
		/* Vérifie quel buffer en Tx s'est libéré. */	
	}
	
	if(C1INTF != 0)
	{
		
		
	}
	C1INTF = C1INTF|0x0003;
	//C1CTRL1bits.WIN = temp_win;
	
	return;	
}	
 
/******************************************************************
					UART ISR
******************************************************************/
int input=0; // changed from unsigned int to int
void __attribute__((interrupt, auto_psv)) _U1RXInterrupt(void)
{
	
	 char InCom=CharToInt(U1RXREG,&input);
	 
	 U1TXREG = InCom;		 
	 //ecan1MsgBuf[0][4] = InCom;
	_U1RXIF = 0; // clear RX interrupt flag	
}

void __attribute__((interrupt, auto_psv)) _U1TXInterrupt(void)
{
	_U1TXIF = 0; // clear TX interrupt flag
}
