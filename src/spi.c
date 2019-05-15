/**
  MSSP Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    spi.c

  @Summary
    This is the generated driver implementation file for the MSSP driver using 
    PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs SPI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC16LF1459
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB 	          :  MPLAB X 4.15
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "libpic30.h"
#include "spi.h"
#include "stdlib.h"
#include "stdio.h"
#include "LCDLib.h"

#define CSN         LATBbits.LATB13
#define CE          LATBbits.LATB13

/**
  Section: Macro Declarations
*/

#define SPI_RX_IN_PROGRESS 0x0

/**
  Section: Module APIs
*/

void SPI_Initialize(void)
{
    // Set the SPI module to the options selected in the User Interface
    
    // R_nW write_noTX; P stopbit_notdetected; S startbit_notdetected; BF RCinprocess_TXcomplete; SMP End; UA dontupdate; CKE Active to Idle; D_nA lastbyte_address; 
    /*SSP1STAT = 0xC0;
    
    // SSPEN enabled; WCOL no_collision; CKP Idle:Low, Active:High; SSPM FOSC/64; SSPOV no_overflow; 
    SSP1CON1 = 0x22;
    
    // SSPADD 0; 
    SSP1ADD = 0x00;*/
        SPI1CON1bits.MSTEN = 1;

//     SSPCON1bits.SSPEN = 1;      //enable serial port
//    SSPBUF = 0;                 //clear SPI buffer    
    SPI1BUF = 0;
    
//    ANSELA = 0x00;              // Turn off analog inputs port A
//    ANSELB = 0x00;              // Turn off analog inputs port B
//    ANSELC = 0x00;              // Turn off analog inputs port C
//    RPINR20bits.SDI1R = 18;  // SPI Data input - RP2 - 105
//    RPINR20bits.SCK1R = 16;
//    RPINR21bits.SS1R = 24;        
//    RPOR3bits.RP7R = 17;   // SPI Data output - RP6 - 107
//    RPOR5bits.RP11R = 8;  // SPI clock output - RP11- 1010 
//    RPOR3bits.RP7R  = 9;  // SPI SS output - RP7 - 108
    
    
    TRISBbits.TRISB7 = 0;   	// SCK ,clock, output
    TRISBbits.TRISB9 = 1;   	// SDI , serial data input
    TRISBbits.TRISB8 = 0;   	// SDO, serial data output
//    TRISBbits.TRISB13 = 0;   	// CSN, chip select not, output
    TRISBbits.TRISB13 = 0;   	// CE, chip enable, output
    
    CSN = 1;                    // pin CSN disable
    CE = 1;                     // pin CE disable
    
    SPI1STATbits.SPITBF = 1;
    SPI1STATbits.SPIRBF = 1;
    
    SPI1CON1bits.CKE = 1;    // 0 - Transmit occurs on transition from Idle to active clock state, 
                            // 1 - Transmit occurs on transition from Active to Idle clock state,
    SPI1CON1bits.CKP = 0;    // 0 - idle state for a clock is a low level
                            // 1 - idle state for a clock is a high level
    SPI1CON1bits.SMP = 0;    // 1 - podatak je uzorkovan na kraju izlaznog vremena podataka
                            // 0 - na sredini
    // SPI master mode
    // 0000 = SPI Master mode, clock = FOSC/4
    // 0001 = SPI Master mode, clock = FOSC/16 
    // 0010 = SPI Master mode, clock = FOSC/64 
//    SPI1STATbits.SSPM = 0b0001;
    SPI1CON1bits.DISSCK = 0;
    SPI1CON1bits.DISSDO = 0;
    SPI1CON1bits.SSEN = 0;
    
    SPI1CON1bits.MODE16 = 0;
    _PPRE = 0b0001;
    SPI1CON2bits.SPIBEN = 0;
        SPI1STATbits.SPIEN = 1;
}

uint8_t SPI_Exchange8bit(uint8_t data)
{
    // Clear the Write Collision flag, to allow writing
//    SSP1CON1bits.WCOL = 0;
//    while (!SPI1STATbits.SPITBF);
    SPI1BUF = data;
    while(SPI1STATbits.SPIRBF == SPI_RX_IN_PROGRESS);
//    while(SPI1STATbits.SPITBF == SPI_RX_IN_PROGRESS)
//    {
//    }

    return (SPI1BUF);
   /* */
//    SPI1BUF = data;                  // Put command into SPI buffer
//    while (!SPI1STATbits.SPITBF);        // Wait for the transfer to finish - if BF then buffer is full
//    return SPI1BUF;                  // Return buffer value  
    
//    while (SPI1STATbits.SPITBF); 
//    delay_15();
////     __delay_ms(50);
//    SPI1BUF = data;
////     __delay_ms(50);
////      __delay_ms(50);
//     delay_15();
//      delay_15();
////    while(SPI1STATbits.SPIRBF == SPI_RX_IN_PROGRESS);
//    return SPI1BUF; 
}

uint8_t SPI_Exchange8bitBuffer(uint8_t *dataIn, uint8_t bufLen, uint8_t *dataOut)
{
    uint8_t bytesWritten = 0;

    if(bufLen != 0)
    {
        if(dataIn != NULL)
        {
            while(bytesWritten < bufLen)
            {
                if(dataOut == NULL)
                {
                    SPI_Exchange8bit(dataIn[bytesWritten]);
                }
                else
                {
                    dataOut[bytesWritten] = SPI_Exchange8bit(dataIn[bytesWritten]);
                }

                bytesWritten++;
            }
        }
        else
        {
            if(dataOut != NULL)
            {
                while(bytesWritten < bufLen )
                {
                    dataOut[bytesWritten] = SPI_Exchange8bit(DUMMY_DATA);

                    bytesWritten++;
                }
            }
        }
    }

    return bytesWritten;
}

bool SPI_IsBufferFull(void)
{
    return (SPI1STATbits.SPITBF);
}

bool SPI_HasWriteCollisionOccured(void)
{
//    return (SSP1CON1bits.WCOL);
    return 0;
}

void SPI_ClearWriteCollisionStatus(void)
{
//    SSP1CON1bits.WCOL = 0;
}
/**
 End of File
*/