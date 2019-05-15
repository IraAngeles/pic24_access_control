/*
 * File:   LCDLib.c
 * Author: iraan
 *
 * Created on May 11, 2019, 1:07 AM
 */


#include "xc.h"
#include "LCDLib.h"
#include "string.h"
//int main(void) {
//    return 0;
//}

//*******************  LCD ROUTINES **************************

//#define LCD_EN _LATB5
//#define LCD_RS _LATB4
//#define LCD_COMMAND 0
//#define LCD_DATA 1

void Nop () {
    return;
}

void delay_15 (void){ //15ms
    int k=0;
    while (k < 1880)
    k = k + 1;
    return;
}

void delay340us (void){ //340us
    int k=0;
    while (k < 1880)
    k = k + 1;
    return;
}


void send4toLCD (int w){
    
    LATB = 0x0000;
    Nop();
    //w=w<<8;        
    w = w & 0x000F;
    w = w | 0x0020;
    w = LATB | w;
    LATB = w;

    delay_15();
    _LATB5 = 0;
//    LATBbits.LATB5 = 0;
    return;
}

//void send4toLCD (int w){
//
//
//
//}


void send8toLCD (int x){
    int y;
    LATB = 0x0000;
    Nop();
    //x=x<<4;  
    y = x & 0x00F0;
    y = y >> 4;
    y = y | 0x0020;
    y = LATB | y;
    LATB = y;
    delay340us();
     _LATB5 = 0;
//    LATBbits.LATB5 = 0;
    
    
    LATB = 0x0000;
    Nop();
    //x=x>>4;       
    y = x & 0x000F;
    y = y | 0x0020;
    y = LATB | y;
    LATB = y;
    delay340us();
     _LATB5 = 0;
//    LATBbits.LATB5 = 0;
    return;
}


void LCD4BitWrite(int byteData) {
    _LATB3 = byteData >> 3;
    _LATB2 = byteData >> 2;
    _LATB1 = byteData >> 1;
    _LATB0 = byteData & 0x01;
//    LCD_RS = 0;
    LCD_EN = 1;
    delay340us();
    LCD_EN = 0;
}    

void LCDWriteData(int z, unsigned char writeMode){
    
    int u ;
    unsigned char tempMode;
    
//    LATB = 0x0000;
    Nop();
    //x=x<<4;  
    u = z & 0x00F0;
    u = u >> 4;
//    u = u | 0x0030;
//    LATB = u;
    LCD_RS = writeMode;
    LCD4BitWrite(u);
    delay340us();
 
//    LATBbits.LATB5 = 0;
    tempMode = writeMode;
    LCD_RS ^= 1UL << tempMode;   
    Nop();
    //x=x<<4;       
    u = z & 0x000F;
//    u = u | 0x0030;    
//    LATB = u;
    LCD_RS = writeMode;
    LCD4BitWrite(u);
    delay340us();
//    LCD_EN = 0;
    LCD_RS = 0;
//    LATBbits.LATB5 = 0;
//    LATBbits.LATB4 = 0;
    return;    
}


void string (char* buf){
    int a = 0;
    int b = 0;
    int c = 0;
    
    a = strlen(buf);
    
//    while ( b <= 9 ){
    while (b < a){
        c = buf[b];
        b = b+1;
//        LCDcmd(c);
        LCDWriteData(c, LCD_DATA);
    }   
    return;
}
void firstline (void){
//    send8toLCD(0x80);
    LCDWriteData( 0x80, LCD_COMMAND);
}
void newline (void){
//    send8toLCD(0xC0);
    LCDWriteData( 0xC0, LCD_COMMAND);
}
void clear (void){
    send8toLCD(0x01);
}
void cursor (void){
    send8toLCD(0xE);
}



void LCDInit(void){
    delay_15();
    LCD_RS = 0;
    LCD4BitWrite(0x03);

    LCD4BitWrite(0x03);

    LCD4BitWrite(0x03);
    
    LCD4BitWrite(0x02);
    delay340us();

    //function set
    LCD4BitWrite(0x02);
    delay340us();  
    LCD4BitWrite(0x0C);
    delay340us();    

//    //clear display
    LCD4BitWrite(0x00);     
    delay340us();
    LCD4BitWrite(0x01); 
    delay340us();   

    //display on
    LCD4BitWrite(0x00);     
    delay340us();
    LCD4BitWrite(0x0C); 
    delay340us();

    //increment cursor
    LCD4BitWrite(0x00);
    delay340us();
    LCD4BitWrite(0x06);
    delay340us();

}

//******************* END LCD ROUTINES ***************
