#define __PIC24FJ64GB002__ 1
#include <xc.h>
#include <p24FJ64GB002.h>
#define FCY 16000000
#include "libpic30.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "LCDLib.h"
#include "I2CLib.h"
#include "rfid.h"
#include "adc1.h"

#pragma config FWDTEN=OFF
#pragma config JTAGEN=OFF
#pragma config POSCMOD = NONE           // Primary Oscillator Select (Primary Oscillator disabled)
#pragma config IOL1WAY = OFF             // IOLOCK One-Way Set Enable (Once set, the IOLOCK bit cannot be clj eared)
#pragma config OSCIOFNC = ON           // OSCO Pin Configuration (OSCO pin functions as clock output (CLKO))u
#pragma config I2C1SEL = SEC            // I2C1 Pin Select bit (Use alternative SCL1/SDA1 pins for I2C1 )
#pragma config FCKSM=CSDCMD            // 96MHz PLL Startup Select (96 MHz PLL Startup is enabled automatically on start-up)
#pragma config FNOSC = FRCPLL           // Initial Oscillator Select (Fast RC Oscillator with Postscaler and PLL module (FRCPLL))
#pragma config IESO= OFF
#pragma config PLL96MHZ = ON            // 96MHz PLL Startup Select (96 MHz PLL Startup is enabled automatically on start-up)
#pragma config PLLDIV = DIV2             // 96MHz PLL Startup Select (96 MHz PLL Startup is enabled automatically on start-up)
#pragma config SOSCSEL=IO
#pragma config ICS = PGx2

#define LED_2       _LATA4
#define DOOR_LOCK   _LATA2
#define DOOR_LIGHT  _LATA3
#define RFID_RESET  _LATB14
#define RFID
// RFID 


unsigned char FoundTag; // Variable used to check if Tag was found
unsigned char ReadTag; // Variable used to store anti-collision value to read Tag information
unsigned char TagData[16]; // Variable used to store Full Tag Data
unsigned char GoodTagSerialNumber[4] = {0x9E, 0x80, 0xB1, 0x59}; // The Tag Serial number we are looking for
int i=0;
char buffer[20],buffer2[20],text[20];
unsigned char version;
int GoodTag=0; // Variable used to confirm good Tag Detected


void readRFID();
void readRFID();
void checktag();
void readRFID();


int main(void)
{
    char buffer[17] = {NULL};
    char SN[] = {50,48,49,50,54,52,54,50,57,0}; //201264629 in ASCII
//    char SN[] = {50,48,49,50,54,52,54,50,57};
    char buffer2[17] = {NULL};
    int counter = 0;
    uint16_t ADC_Result = 0;
    
    TRISB = 0x0000;
    T1CON = 0x8030;
//    AD1PCFG = 0xFDFF;  
    AD1PCFG = 0xffff; 
    TRISA = 0xffff;
    TRISB = 0x9000;
    LATB = 0xffff; 
    LATA = 0x01;
    
    AD1PCFGLbits.PCFG2 = 0;
    TRISAbits.TRISA2 = 0;
    
    AD1PCFGLbits.PCFG3 = 0;
    TRISAbits.TRISA3 = 0;
  
    AD1PCFGLbits.PCFG4 = 0;
    TRISAbits.TRISA4 = 0;
    
    TRISBbits.TRISB14 = 0;
    RFID_RESET = 0;
    __delay_ms(150);

    LED_2=1;     

    DOOR_LOCK = 1;
    DOOR_LIGHT = 1;
    
//************ Initialization Routines **************
    ADC1_Initialize();
    
    
// Initialize LCD
    LCDInit();
   LED_2=1;     

//    clear();
    firstline();
    sprintf(buffer,"SN=%s",SN);
    string(buffer);

//// Display 16 bytes on LCD
    newline();
    sprintf(buffer,"RFID ACCESS CONTROL");
    string(buffer);

// RFID 
 #ifdef RFID   
    SYSTEM_Initialize();
//    SPI_Initialize();
    
   __delay_ms(50);
       RFID_RESET = 1;
   begin(); //initialize MFRC522


// END RFID    
    
       newline();
    sprintf(buffer,"RFID ACCESS CONTROL");
    string(buffer);
    
    
    while(1) {
        
            //  Check to see if a Tag was detected
     // If yes, then the variable FoundTag will contain "MI_OK"

        
//        LED_2=0; 
//       __delay_ms(300);
        
        FoundTag = requestTag(MF1_REQIDL, TagData);
    
        __delay_ms(200);
//        newline();
//        sprintf(buffer,"Status: %2X      ", FoundTag);
//        string(buffer);   
   
     if (FoundTag == MI_OK)
     {
//        REDLED = 1; 
       readRFID();
       checktag();
       DOOR_LOCK = 0;
       __delay_ms(50);
       newline();
       sprintf(buffer,"OPENING LOCK");
       string(buffer);
       __delay_ms(1000);
       DOOR_LOCK = 1;
     }
        

//       LED_2=1; 
//       __delay_ms(500);   
//    }
#endif
    
//    while(1) {
         LED_2=0; 
       __delay_ms(300);  
       ADC1_ChannelSelect(9);
       ADC1_Start();
       __delay_ms(300); 
       ADC1_Stop();
       while (!ADC1_IsConversionComplete);
        ADC_Result = ADC1_ConversionResultGet();
        newline();
        sprintf(buffer,"ADC = %04X      ", ADC_Result);
        string(buffer);  
       
        if ( ADC_Result < 0x40 ){
            DOOR_LIGHT = 0;
        } else {
            DOOR_LIGHT = 1;
        }
        
        
         LED_2=1; 
       __delay_ms(500);        
     }
    
    return 0;
}

// Initialize I2C peripheral
//    I2C_init();
//    I2C_init2();

//Write student number to WRITE_ADDR
//    for(counter = 0; counter < 9 ;counter++) {
//            EEPROM_write(WRITE_ADDR + counter,SN[counter]);                 
//    }
//    for ( counter=0; counter < 16; counter++) {
//        EEPROM_write(WRITE_ADDR + counter,65);
//    }

// Read 16 bytes from READ_ADDR
//    LED_2=1; 
//    for(counter = 0; counter < 16; counter++) {
//        buffer2[counter] = EEPROM_read(READ_ADDR + counter);
////        sprintf(buffer,"%c",buffer2[counter]);
////        string(buffer);
//    }

//*************************  RFID ************************

void checktag()
{
   if (GoodTag == 1)
   { 
      GoodTag=0;
      __delay_ms(50);
   }
   else
   {  
      GoodTag=0;
      __delay_ms(50);
   }
}
void readRFID()
{
    int i;
    // Get anti-collision value to properly read information from the Tag
    ReadTag = antiCollision(TagData);

   /* */
   for(i=0;i<=2;i++)
   {
    sprintf(buffer2,"TAG:%2X",(TagData[i])); //display version in hexadecimal
    __delay_ms(2);
//    printf(buffer2);
//    printf(", ");
   }

    
//    sprintf(buffer2,"%2X",(TagData[i])); //display version in hexadecimal
//    __delay_ms(2);
//    printf(buffer2);
//    printf("\r\nCheck Validity \r\n");
   
    
   for(i=0; i <= 3; i++)
   {
    if (GoodTagSerialNumber[i] != TagData[i])
   {
    GoodTag=0;
    break; // if not equal, then break out of the "for" loop
   }
   }
   
   if (TagData[3]==GoodTagSerialNumber[3])
   {
   // if we made it to 4 loops then the Tag Serial numbers are matching
   GoodTag=1;
   }
    
//   if (!GoodTag) {
            newline();
            
    for(i=0; i <= 3; i++){
        sprintf(buffer,"%2X:", TagData[i]);
        string(buffer);       
        
    }
 
    __delay_ms(2);
//   }
    
} 
  
  
 //************************  RFID ************************/