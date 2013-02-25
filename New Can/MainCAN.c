/******************************************************************
							Includes
******************************************************************/
#include "p33EP512MU810.h"
#include "Global.h"
#include "M_UART.h"
#include "M_TMR.h"
#include <stdio.h>
#include "can.h"
/******************************************************************
                    Variable, Macro & Const
******************************************************************/


/******************************************************************
							Prototype
******************************************************************/
void initAdc1(void);
void initBTIO(void);
void set_clk(void);
void InitQEI(void);
void InitServos(char Sselect);
void MatGeartoothSim(void);
void Init_PWM_Brake(void);
void CanInit(unsigned char f_Mode);
void SetupDMA(void);
void SendCAN(void);
/******************************************************************
							Main
******************************************************************/

unsigned int ecan1MsgBuf[NUM_OF_ECAN_BUFFERS][8] 
 __attribute__((aligned(NUM_OF_ECAN_BUFFERS * 16)));
 
volatile unsigned int CFLAG =0;

#define _CNTo 7
#define _CNTi 7
#define _AMODEi 0b10
#define _MODEi 0b00

char print=0;
char buffTX[50];
char buffRX[50];
int tx,rx;

 int main(void)
 {
	int i;
	unsigned int cnt;
	unsigned int tmp;
	set_clk();
	
	PORTA = 0;
	TRISA = 0xFFE0;
	
	// INITIALISATON DU UART 
	Init_Timer5(10.0f);
	if(_RF2==1 && _RF8==1 );	
	{
		//Connect RP118 to U1TX
		_RP98R =	0b000001;	
		//Init Uart and connect RP104 to U1RX 	
		Init_UART((unsigned int)(FOSC/BAUDRATE/32.0f)-1,104);
	}

	// INITIALISATON DU CAN

	CanInit(CAN_LOOPBACK);

	/*IO settings*/
   	//Inputs (RPINxxbits.registre)
   	_C1RXR = 124;             	
   	//Outputs (RPORxxbits.registre)
  	_RP126R = 0b001110;  


	for(;;)
	{

	SendCAN();

		if(print)
		{
			
			cnt =0;
			tmp = 7;
			for(i=0;i<tmp;i++)
			{
				rx = sprintf(buffRX, "%d is the value received on MsgBuff %d",ecan1MsgBuf[8][i],i);
				tx = sprintf(buffTX, "%d is the value sent on MsgBuff %d",ecan1MsgBuf[0][i],i);
				printf("%s and %s\n", buffRX,buffTX);
				cnt++;
			}
				
			printf("\n");
			
			print=0;
		}
 	}
  
 return 0; 
 }

 void CanInit(unsigned char f_Mode)
 {
 // 4bits Module 7Bits message type
 // Ced: 0b0001 
  
 //Make the appropriate pin assignments to set up the CAN1RX and CAN1TX according to the pin layout
  
 //RPINR26 = 0;                                           //clear register
 //RPINR26bits.C1RXR = 0x4C; //assign pin 79 to C1RXR by using 0b100 1100 = 0x4C (for can recieve)
  
 //RPOR9bits.RP101R = 0x0E;        //assing pin 50 to output (for can transmit) 0b001110
  
  
 /* The ECAN module should be first placed in configuration mode. */
 C1CTRL1bits.REQOP = 4; 
 while(C1CTRL1bits.OPMODE != 4);
  
 /*WIN = CiCTRL1<0> = 1, the message acceptance filters, masks and filter buffer pointer registers are accessed by the user application.
 WIN = CiCTRL1<0> = 0, the buffer control and status registers, and the transmit and receive data registers are accessed by the user application*/
 C1CTRL1bits.WIN = 0;                             
  
  
  
 /******************************************************************************
 **     Bit Timing for CAN Bus. Includes Tq and various syncronization rates//
 ** Set up the CAN module for 125kbps speed with 10 Tq per bit.
 **
 ******************************************************************************/
  
 /* FCAN is selected to be FP by clearing the CANCKS bit */
 /* Fcan = Fp = Fcy= 50 MHz */
 C1CTRL1bits.CANCKS = 0x1;
  
 /* Phase Segment 1 time is 2 TQ */ 
 C1CFG2bits.SEG1PH = 0x1;
  
 /* Phase Segment 2 time is set to be programmable */ 
 C1CFG2bits.SEG2PHTS = 0x1; 
  
 /* Phase Segment 2 time is 2 TQ */ 
 C1CFG2bits.SEG2PH = 0x1;
  
 /* Propagation Segment time is 4 TQ */
 C1CFG2bits.PRSEG = 0x3; 
  
 /* Bus line is sampled three times at the sample point */ 
 C1CFG2bits.SAM = 0x1; 
  
 /* Synchronization Jump Width set to 1 TQ */ 
 C1CFG1bits.SJW = 0x0;
  
  
 /* Baud Rate Prescaler bits set to BRP=(Fcan/(2*Ftq))-1 and  BRP=(50000000)/(2*(1.25x10^6))-1=19, and 19 = 0x13
 // Ftq= N * Fbaud, where N chosen to be 10 so, Ftq=10*(125x10^3)= 1.25MHz
 */
 C1CFG1bits.BRP = 0x13;
  
  
  
 C1FCTRL = 0xC01F;      //DMABS<2:0> = 0b110 = 32 Buffers, FIFO start address set to Read Buffer RB31 FSA<4:0> = Ob11111 = NO FIFO since starting at last address!!
  
  
 /* Configure Message Buffer 0 for Transmission and assign priority */
 C1TR01CONbits.TXEN0 = 0x1;     //1 = Buffer TRBn is a transmit buffer
 C1TR01CONbits.TX0PRI = 0x3;    //11 = Highest message priority
  
 SetupDMA();    //Set up the appropriate DMA initializations
  
 C1CTRL1bits.WIN = 1;           //Set WIN = 1, so the message acceptance filters, masks and filter buffer pointer registers are accessed by the user application. 
  
  
 /***************************************************************
 ** Set up Receive registers and paramters
 ** 
 ** Select Acceptance Filter Mask 0 for Acceptance Filter 0 
 ****************************************************************/
  
 /* Select Acceptance Filter Mask 0 for Acceptance Filter 0 */ 
 C1FMSKSEL1bits.F0MSK = 0x0; 
  
 /* Configure Acceptance Filter Mask 0 register to Mask Bits (11-bits) : 0b111 1111 1111
 1 = Include bit, SIDx, in filter comparison (OR) 0 = Bit, SIDx, is a don’t care in filter comparison*/
 C1RXM0SIDbits.SID = 0x7FF;
  
 /* Configure Acceptance Filter 0 to match standard identifier Filter Bits (11-bits): 
 0b000 0000 0001 with the mask setting, message with SID range 0x1D0-0x1D7 will be accepted by the ECAN module. */
 C1RXF0SIDbits.SID = 0x002; 
  
 /* Acceptance Filter 0 to check for Standard Identifier */
 C1RXM0SIDbits.MIDE = 0x1;      //1 = Match only message types (standard or extended address) that correspond to EXIDE bit in filter
 C1RXF0SIDbits.EXIDE = 0x0;     //0 = Match only messages with standard identifier addresses
  
 /* Acceptance Filter 0 to use Message Buffer 8 to store message, buffers 8-14 are for receiving only */ 
 C1BUFPNT1bits.F0BP = 0x8;
  
 /* Filter 0 enabled for Identifier match with incoming message */ 
 C1FEN1bits.FLTEN0 = 0x1;
  

 /* Clear Window Bit to Access ECAN * Control Registers 
 CiCTRL1<0> = 0, the buffer control and status registers, and the transmit and receive data registers are accessed by the user application*/
 C1CTRL1bits.WIN = 0x0;
  
 /* Place the ECAN module in normal * mode. */
 C1CTRL1bits.REQOP = f_Mode; 
 while(C1CTRL1bits.OPMODE != f_Mode);
  
  
 }
  
 void SetupDMA(void)
 {
 /* Assign  Message Buffers for ECAN1 in device RAM. Use DMA Channel 0 for TX
 // Only use message buffers 0 - 7 for transmission
 */
  
 DMA0CONbits.SIZE = 0x0;                //0 = Word for Data Transfer Size bit
 DMA0CONbits.DIR = 0x1;         //1 = Read from DPSRAM (or RAM) address, write to peripheral address
 DMA0CONbits.AMODE = 0x2;       //0b10 = Peripheral Indirect Addressing mode
 DMA0CONbits.MODE = 0x0;                //0b00 = Continuous, Ping-Pong modes disabled
 DMA0REQ = 70;                          //0b01000110 = 70 = ECAN1 – TX Data Request 
 DMA0CNT = 7;                           //The number of DMA transfers = CNT<13:0> + 1 = 8 transfers
 DMA0PAD = (volatile unsigned int)&C1TXD;       // Creates a pointer to the address where the DMA must write to the peripheral, The address is 0x0442 = C1TXD
  
 //address = (unsigned long) &ecan1MsgBuf;
 //
 DMA0STAL = (unsigned int) &ecan1MsgBuf;                //
 DMA0STAH = (unsigned int) &ecan1MsgBuf;                //
  
 DMA0CONbits.CHEN = 0x1;       //1 = channel enable
  
 /* Assign Message Buffers for ECAN1 in devie RAM. Use DMA Channel 1 for RX
 // Only use message buffers 8-14 for receive
 */
  
 DMA1CONbits.SIZE = 0x0;                //0 = Word for Data Transfer Size bit
 DMA1CONbits.DIR = 0x0;         //0 = Read from Peripheral address, write to DPSRAM (or RAM) address
 DMA1CONbits.AMODE = 0x2;       //0b10 = Peripheral Indirect Addressing mode
 DMA1CONbits.MODE = 0x0;                //0b00 = Continuous, Ping-Pong modes disabled
 DMA1REQ = 34;                          //0b00100010 = 34 = ECAN1 – RX Data Ready
 DMA1CNT = 7;                           //The number of DMA transfers in words = CNT<13:0> + 1 = 8 transfers
 DMA1PAD = (volatile unsigned int)&C1RXD;       // Creates a pointer to the address where the DMA must read from the peripheral, The address is 0x0440 = C1RXD
  
 //
 DMA1STAL = (unsigned int) &ecan1MsgBuf;                //
 DMA1STAH = (unsigned int) &ecan1MsgBuf;                //
  
 DMA1CONbits.CHEN = 0x1;     //1 = channel enable
  
 }
  
void SendCAN(void)
 {
 /* Write to message buffer 0 */ 
 /* CiTRBnSID = 0bxxx0 0000 0000 1000
 IDE = 0b0 
 SRR = 0b0 
 SID<10:0>= 0b000 0000 0010 = motor controller ID*/ 
  
 ecan1MsgBuf[0][0] = 8;
 /* CiTRBnEID = 0bxxxx 0000 0000 0000 
 EID<17:6> = 0b0000 0000 0000 */
  
 ecan1MsgBuf[0][1] = 0; // this buffer always gives '0'
 /* CiTRBnDLC = 0b0000 0000 xxx0 0111
 EID<17:6> = 0b000000 
 RTR = 0b0 
 RB1 = 0b0 
 RB0 = 0b0
 DLC = 0b0111 */
  
 ecan1MsgBuf[0][2] = 7; 
 /* Write message data bytes */
 ecan1MsgBuf[0][3] = 3; 
 
 ecan1MsgBuf[0][4] = 1;
 
 ecan1MsgBuf[0][5] = 4;
 
 ecan1MsgBuf[0][6] = 5; 

 /* Request message buffer 0 transmission */
 C1TR01CONbits.TXREQ0 = 0x1;
  
 /* The following shows an example of how the TXREQ bit can be polled to check if transmission is complete. */
      while(C1TR01CONbits.TXREQ0 == 1);
  
 /* Message was placed successfully on the bus */
 }
/******************************************************************
							Functions
******************************************************************/
void set_clk(void)
{					//datasheet section 7 p.21
_PLLPRE=0;
_PLLPOST=0;
_PLLDIV=(unsigned int) (4.0f*FOSC_MHZ/(7.37f))-1;
//OSCTUNbits.TUN-=3;
while(OSCCONbits.LOCK !=1);
}
