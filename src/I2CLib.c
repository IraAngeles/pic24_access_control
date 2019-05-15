/*
 * File:   I2CLib.c
 * Author: iraan
 *
 * Created on May 11, 2019, 1:25 AM
 */


#include "xc.h"
#include "I2CLib.h"
//int main(void) {
//    return 0;
//}
// Initialize I2C module
void I2C_init(void) 
{
    TRISA = 0xFFFF; // set SCL and SDA pins as inputs
    TRISB = 0;
// I2C1BRG
    I2C1BRG = 0x25; //4 MHz and 400kHz
// I2C1CON
    I2C1CON = 0x2B80;
    I2C2CON = 0;
// IEC1
//    I2C_EN = 1;
    I2C_Flag = 0;
// Enable I2C after configuration
    I2C1CONbits.I2CEN = 1;
}

void I2C_init2(void) 
{
    TRISA = 0xFFFF; // set SCL and SDA pins as inputs
	I2C1CON = 0xA000;										//Set all bits to known state
	I2C1CONbits.I2CEN = 0;									//Disable until everything set up. Pins will be std IO.
	I2C1BRG = 37;	//I2C1BRG = (Fcy/Fscl-FCY/10E6)-1 = (16E6/400E3-16E6/10E6)-1 = 40-1.6-1 = 37.4. Actual Fscl=404kHz.
	I2C1CONbits.DISSLW = 0;									//Enable slew rate control for 400kHz operation
	IFS1bits.MI2C1IF = 0;									//Clear I2C master int flag
	I2C1CONbits.I2CEN = 1;									//Enable I2C
}

// i2c_Wait - wait for I2C transfer to finish
void I2C_Wait(void){
    while (!I2C_Flag);
	I2C_Flag = 0;
}

// Send start bit sequence
void I2C_start(void)
{
// Set Start Condition Enabled Bit
    I2C1CONbits.SEN=1;
// Wait for operation to finish by checking interrupt flag
    I2C_Wait();
// Clear interrupt flag
//    I2C_Flag = 0;
}

// Send repeated start bit sequence
void I2C_restart(void)
{
// Set Repeated Start Condition Enabled bit
    I2C1CONbits.RSEN=1;
// Wait for operation to finish by checking interrupt flag
    I2C_Wait();
// Clear interrupt flag
    I2C_Flag = 0;
}

// Send stop bit sequence
void I2C_stop(void)
{
// Set Stop Condition Enabled bit
    I2C1CONbits.PEN=1;
// Wait for operation to finish by checking interrupt flag
    I2C_Wait();
// Clear interrupt flag
    I2C_Flag = 0;
}

// Send ACK bit sequence
void I2C_ack(void)
{
// Set Acknowledge Data bit
    I2C1CONbits.ACKDT=0;
// Set Acknowledge Sequence Enabled bit
    I2C1CONbits.ACKEN=1;
// Wait for operation to finish by checking interrupt flag
    I2C_Wait();
// Clear interrupt flag
    I2C_Flag = 0;
}

// Send NACK bit sequence
void I2C_nack(void)
{
// Set Acknowledge Data bit
    I2C1CONbits.ACKDT=1;
// Set Acknowledge Sequence Enabled bit
    I2C1CONbits.ACKEN=1;
// Wait for operation to finish by checking interrupt flag
    I2C_Wait();
// Clear interrupt flag
    I2C_Flag = 0;
}

// Transfer one byte sequence
int I2C_write(unsigned char Byte)
{
// Write byte to transmit buffer register
    I2C1TRN = Byte;
// Wait for operation to finish by checking interrupt flag
    I2C_Wait();
// Return Acknowledge bit received
//    return I2C1STATbits.ACKSTAT;
    
while(I2C1STATbits.TRSTAT) {
};

// Return Acknowledge bit received
    return I2C1STATbits.ACKSTAT;    
    
}

// Receive one byte sequence
unsigned char I2C_read(void)
{
    char i2cReadData;
// Set Receive Enable bit
    I2C1CONbits.RCEN=1;
// Wait for operation to finish by checking interrupt flag
    I2C_Wait();
    i2cReadData = I2C1RCV;

// Return receive buffer contents
    return i2cReadData;
}

// EEPROM write sequence
void EEPROM_write(unsigned int waddr, unsigned char wdata)
{
// Start I2C communication
I2C_start();
// Send I2C EEPROM slave address with write command, wait if device is not available
while(I2C_write(EEPROM_slave_address + 0)){
    I2C_restart();
}
// Send address, high byte then low byte
I2C_write(waddr>>8);
I2C_write(waddr);
//// Send data
I2C_write(wdata);
//// Stop I2C communication

I2C_stop();
}

// EEPROM read sequence
unsigned EEPROM_read(unsigned int raddr)
{
    unsigned char Byte = 0;

// Start I2C communication
I2C_start();

// Send I2C EEPROM slave address with write command, wait if device is not available
while(I2C_write(EEPROM_slave_address + 0)){
    I2C_restart();
}

// Send address, high byte then low byte
I2C_write(raddr>>8);
I2C_write(raddr);

// Send repeated start
I2C_restart();

// Send I2C EEPROM slave address with read command
I2C_write(EEPROM_slave_address + 1);

// Store data from buffer
Byte = I2C_read();

// Send NACK
I2C_nack();

// Stop I2C communication
I2C_stop();
return Byte;

}
