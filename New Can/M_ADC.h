
#ifndef MOTOR_ADC
#define MOTOR_ADC

// Define Message Buffer Length for ECAN1/ECAN2
#define  MAX_CHNUM	 			13		// Highest Analog input number in Channel Scan
#define  SAMP_BUFF_SIZE	 		8		// Size of the input buffer per analog input
#define  NUM_CHS2SCAN			4		// Number of channels enabled for channel scan

void InitADCReg(void);

void InitADCReg2(unsigned int CHA,unsigned int CHB);
//void Init_Phases_ADC(void);

//void Init_Adcs(void);
/*****************************************************************/
/*****************************************************************/
/*
Init_DAC

	Initialise the voltage ref of the comparator CVref and set the
	output to the desired value

	INPUT 	: 
			- Vout
			- Type: float
			- Value: 0.0f - 2.475f	any other value may result in 
									an unwanted operation

				
	OUTPUT 		:
				- None
				
	EFFECT 		:
				- The TRISB10 Value will be override and the defined
					 voltage will be set.
	SPEC		: 	
				- Output is in relation to AVdd not Vref+
				
	CALL Example:

	Init_DAC(0.5f);	//Set DAC at 0.5V
	
*/

void Init_DAC(float vout);

void UpdateDAC(float vout);

void ProcessADC2(void);
#endif

