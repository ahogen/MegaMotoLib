/********************************************//**
 * \file     h-bridge-all.ino
 * \author   Alexander Hogen
 *           https://github.com/ahogen/MegaMoto
 * \date     1/11/2017
 * \version  0.1
 * \brief    Demonstrating all methods of the
 *           MegaMotoHB class.
 *
 * This is used in build tests to make sure no
 * old functions get broken by future code edits.
 * At least that is the idea... All methods
 * avaliable to the end user should be here in
 * this code project somewhere so the compiler
 * can build them in.
 ***********************************************/

// Include the MegaMoto library
#include <MegaMotoHB.h>

// Format is:  <yourObjectName>( <pin_for_pwm_a>, <pin_for_pwm_b> );
MegaMotoHB m1(11, 3);
MegaMotoHB m2(6, 5, 13);

void setup() 
{
	// Initialize the serial port
	Serial.begin(9600);
    
	// Print a message indicating the code is running
	Serial.println("MegaMotoHB build test is running...");
	
	m1.Enable();
    m2.Enable();

    m1.SetStepDelay(2);
    Serial.print("New step delay for m1 is: ");
    Serial.println( m1.GetStepDelay() );

    m2.SetStepDelay(3);
    Serial.print("New step delay for m2 is: ");
    Serial.println( m2.GetStepDelay() );
}


void loop()
{

    // Move forward at full speed
    m1.Fwd(255);
    m2.Fwd(255);

    // Wait for 1 second
    delay(1000);

    // Stop the device (with 'ramping')
    m1.Stop();
    m2.Stop();

    // Wait for 1 second
    delay(1000);

    // Move backward at half speed
    m1.Rev(128);
    m2.Rev(128);

    // Wait for 1 second
    delay(1000);

    // Disable and attempt to move forward at half speed
    m1.Disable();
    m2.Disable();
    m1.Fwd(128);
    m2.Fwd(128);

    // Wait for 1 sec
    delay(1000);

    m1.Enable();
    m2.Enable();

    delay(500);

    m1.Kill();
    m2.Kill();

    delay(500);
}
