#include "p33EP512MU810.h"
#include "Global.h"
#include "M_ADC.h"

// Number of locations for ADC buffer = 14 (AN0 to AN13) x 8 = 112 words
// Align the buffer to 128 words or 256 bytes. This is needed for peripheral indirect mode
__eds__ int BufferA[MAX_CHNUM+1][SAMP_BUFF_SIZE] __attribute__((eds,space(dma),aligned(256)));
__eds__ int BufferB[MAX_CHNUM+1][SAMP_BUFF_SIZE] __attribute__((eds,space(dma),aligned(256)));

void initDma0(void)
{
	DMA0CONbits.AMODE = 2;			// Configure DMA for Peripheral indirect mode
	DMA0CONbits.MODE  = 2;			// Configure DMA for Continuous Ping-Pong mode
	DMA0PAD=(int)&ADC1BUF0;
	DMA0CNT = (SAMP_BUFF_SIZE*NUM_CHS2SCAN)-1;					
	DMA0REQ = 13;					// Select ADC1 as DMA Request source

	DMA0STAL = __builtin_dmaoffset(&BufferA);
	DMA0STAH = __builtin_dmapage(&BufferA);

	DMA0STBL = __builtin_dmaoffset(&BufferB);
	DMA0STBH = __builtin_dmapage(&BufferB);

	IFS0bits.DMA0IF = 0;			//Clear the DMA interrupt flag bit
    IEC0bits.DMA0IE = 1;			//Set the DMA interrupt enable bit

	DMA0CONbits.CHEN=1;				// Enable DMA

}

