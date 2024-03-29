/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC16LF1459
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB             :  MPLAB X 4.15

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
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

#include <xc.h>
#include "pin_manager.h"
#include "stdbool.h"





void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
//    LATA = 0x00;
//    LATB = 0x00;
//    LATC = 0x40;

    /**
    TRISx registers
    */
//    TRISA = 0x30;
//    TRISB = 0xB0;
//    TRISC = 0x3F;

    /**
    ANSELx registers
    */
//    ANSELC = 0x0F;
//    ANSELB = 0x00;
//    ANSELA = 0x10;

    /**
    WPUx registers
    */
//    WPUB = 0x00;
//    WPUA = 0x00;
//    OPTION_REGbits.nWPUEN = 1;

    /**
    ODx registers
    */

    /**
    APFCONx registers
    */
//    APFCON = 0x00;


//    RPOR6bits.RP13R = 0x0009;    //RB13->SPI1:SS1OUT
//    RPOR4bits.RP9R = 0x0007;    //RB9->SPI1:SDO1
//    RPOR3bits.RP7R = 0x0008;    //RB7->SPI1:SCK1OUT
//    RPINR20bits.SDI1R = 0x0008;    //RB8->SPI1:SDI1

    RPOR4bits.RP8R = 0x0007;    //RB8->SPI1:SDO1
    RPOR3bits.RP7R = 0x0008;    //RB7->SPI1:SCK1OUT
    RPINR20bits.SDI1R = 0x0009;    //RB9->SPI1:SDI1
    RPOR6bits.RP13R = 0x0009;    //RB13->SPI1:SS1OUT   
    
}
  
void PIN_MANAGER_IOC(void)
{   
}

/**
 End of File
*/