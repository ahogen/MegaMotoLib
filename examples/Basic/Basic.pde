/********************************************//**
 * \file     Basic.pde
 * \author   Alexander Hogen
 * \date     12/31/2016
 * \version  0.1
 * \brief    A basic example showing how to get
 *           started with the MegaMoto Arduino
 *           library.
 *
 * Demonstrates how to include and instantiate
 * a new MegaMoto object with the chosen pin
 * assignments and then start up the motor/device
 * in various speeds and directions.
 *
 *
 * [1] "MegaMoto & MegaMoto Plus User Manual," Robot Power,
 *     Version 1.6, May 28, 2016.
 *     Avaliable: http://www.robotpower.com/downloads/MegaMoto-user-manual.pdf
 ***********************************************/

// Include the MegaMoto library
#include <MegaMoto.h>

// Instantiate a "global" (all functions in your code can see/use it)
// MegaMoto object.
// For this example, it is assumed that your jumpers are connected in
// the following fashion. Please read page 3 in the MegaMoto user
// manual to understand your options. ALSO, the motor itself is wired
// in an H-bridge fashion. Please see Figure 4 on page 5 of the user
// manual to understand what this means.
// 
// -- Jumper configuration --
// PWM A ---> D11
// PWM B ---> D3
// Enable --> 5V
// Sensor --> (none. remove jumper)

MegaMoto myMotor(11, 3, TMegaMotoWiring::H_bridge);

void setup() 
{
    // Initialize the serial port
    Serial.begin(9600);
    
    // Print a message indicating the code is running
    Serial.println("Basic MegaMoto test is running...");
}


void loop()
{
    // put your main code here, to run repeatedly:

    // Move forward at full speed
    myMotor.Move(TMegaMotoDir::FWD, 255);

    // Wait for 1 second
    delay(1000);

    // Move backward at half speed
    myMotor.Move(TMegaMotoDir::REV, 128);

    // Wait for 1 second
    delay(1000);

    // Stop the device (with 'ramping')
    myMotor.Move(TMegaMotoDir::STOP, 0); // <-- Doesn't matter what number you put here.
                                         //     It will be ignored when using STOP.
    
    // Wait for 1 second
    delay(1000);
}
