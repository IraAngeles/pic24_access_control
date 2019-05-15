/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set SDO aliases
#define SDO_TRIS                 TRISBbits.TRISB8
#define SDO_LAT                  LATBbits.LATB8
#define SDO_PORT                 PORTBbits.RB8
#define SDO_WPU                  WPUBbits.WPUB8
#define SDO_ANS                  ANSELBbits.ANSB8
#define SDO_SetHigh()            do { LATBbits.LATB8 = 1; } while(0)
#define SDO_SetLow()             do { LATBbits.LATB8 = 0; } while(0)
#define SDO_Toggle()             do { LATBbits.LATB8 = ~LATBbits.LATB8; } while(0)
#define SDO_GetValue()           PORTBbits.RB8
#define SDO_SetDigitalInput()    do { TRISBbits.TRISB8 = 1; } while(0)
#define SDO_SetDigitalOutput()   do { TRISBbits.TRISB8 = 0; } while(0)
#define SDO_SetPullup()          do { WPUBbits.WPUB8 = 1; } while(0)
#define SDO_ResetPullup()        do { WPUBbits.WPUB8 = 0; } while(0)
#define SDO_SetAnalogMode()      do { ANSELBbits.ANSB8 = 1; } while(0)
#define SDO_SetDigitalMode()     do { ANSELBbits.ANSB8 = 0; } while(0)

// get/set SCK aliases
#define SCK_TRIS                 TRISBbits.TRISB7
#define SCK_LAT                  LATBbits.LATB7
#define SCK_PORT                 PORTBbits.RB7
#define SCK_WPU                  WPUBbits.WPUB7
#define SCK_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define SCK_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define SCK_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define SCK_GetValue()           PORTBbits.RB7
#define SCK_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define SCK_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define SCK_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define SCK_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)

// get/set IO_RC6 aliases
#define IO_RC6_TRIS                 TRISBbits.TRISB13
#define IO_RC6_LAT                  LATBbits.LATB13
#define IO_RC6_PORT                 PORTBbits.RB13
#define IO_RC6_ANS                  ANSELBbits.ANSB13
#define IO_RC6_SetHigh()            do { LATBbits.LATB13 = 1; } while(0)
#define IO_RC6_SetLow()             do { LATBbits.LATB13 = 0; } while(0)
#define IO_RC6_Toggle()             do { LATBbits.LATB13 = ~LATBbits.LATB13; } while(0)
#define IO_RC6_GetValue()           PORTBbits.RB13
#define IO_RC6_SetDigitalInput()    do { LATBbits.TRISB13 = 1; } while(0)
#define IO_RC6_SetDigitalOutput()   do { LATBbits.TRISB13 = 0; } while(0)
#define IO_RC6_SetAnalogMode()      do { ANSELBbits.ANSB7 = 1; } while(0)
#define IO_RC6_SetDigitalMode()     do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set SDI aliases
#define SDI_TRIS                 TRISBbits.TRISB9
#define SDI_LAT                  LATBbits.LATB9
#define SDI_PORT                 PORTBbits.RB9
#define SDI_ANS                  ANSELBbits.ANSB9
#define SDI_SetHigh()            do { LATBbits.LATB9 = 1; } while(0)
#define SDI_SetLow()             do { LATBbits.LATB9 = 0; } while(0)
#define SDI_Toggle()             do { LATBbits.LATB9 = ~LATBbits.LATB9; } while(0)
#define SDI_GetValue()           PORTBbits.RB9
#define SDI_SetDigitalInput()    do { TRISBbits.TRISB9 = 1; } while(0)
#define SDI_SetDigitalOutput()   do { TRISBbits.TRISB9 = 0; } while(0)
#define SDI_SetAnalogMode()      do { ANSELBbits.ANSB9 = 1; } while(0)
#define SDI_SetDigitalMode()     do { ANSELBbits.ANSB9 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/