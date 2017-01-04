/********************************************//**
 * \file     MegaMotoBase.cpp
 * \author   Alexander Hogen
 * \date     1/3/2017
 * \version  0.1
 * \brief    Contains the definitions for all the
 *           member methods of the MegaMotoBase class.
 *
 * Released into the public domain.
 *
 ***********************************************/

#include "MegaMotoBase.h"

/********************************************//**
 * \brief Constructor to initialize with pin
 *        numbers for PWM A and PWM B and
 *        specify the motor wiring.
 *
 * All data members initialized to their empty
 * or default values. The name of the multiplier
 * is set to the string passed in as the first
 * argument. The multiplier bit width is set
 * to the value of the second argument.
 *
 * \param pin_pwm_a is a byte. Specify the pin
 *        used for MegaMoto PWM A here.
 *
 * \param pin_pwm_b is a byte. Specify the pin
 *        used for MegaMoto PWM B here.
 *
 ***********************************************/
MegaMotoBase::MegaMotoBase( 
	unsigned char pin_pwm_a, 
	unsigned char pin_pwm_b)
	: use_enable_pin( false ), 
	pin_en( 255 ),
	pin_a ( pin_pwm_a ),
	pin_b ( pin_pwm_b ),
	pwm_step_delay_ms (3)
{
  // Set pins to output mode for MegaMoto
  pinMode(pin_a, OUTPUT);
  pinMode(pin_b, OUTPUT);

  // Turn OFF both A and B PWM outputs
  analogWrite(pin_a, 0);
  analogWrite(pin_b, 0);
}

/********************************************//**
 * \brief Constructor to initialize with pin
 *        numbers for PWM A, PWM B, and Enable.
 *        Also specify the motor wiring.
 *
 * All data members initialized to their empty
 * or default values. The name of the multiplier
 * is set to the string passed in as the first
 * argument. The multiplier bit width is set
 * to the value of the second argument.
 *
 * \param pin_pwm_a is a byte. Specify the pin
 *        used for MegaMoto PWM A here.
 *
 * \param pin_pwm_b is a byte. Specify the pin
 *        used for MegaMoto PWM B here.
 *
 * \param pin_enable is a byte. Specify the pin
 *        used for the MegaMoto Enable pin here.
 *
 ***********************************************/
MegaMotoBase::MegaMotoBase( 
	unsigned char pin_pwm_a, 
	unsigned char pin_pwm_b,
	unsigned char pin_enable )
	: use_enable_pin( true ), 
	pin_en( pin_enable ),
	pin_a ( pin_pwm_a ),
	pin_b ( pin_pwm_b ),
	pwm_step_delay_ms (3)
{
  // Set pins to output mode for MegaMoto
  pinMode(pin_a, OUTPUT);
  pinMode(pin_b, OUTPUT);
  pinMode(pin_en, OUTPUT);

  // Turn OFF both A and B PWM outputs
  analogWrite(pin_a, 0);
  analogWrite(pin_b, 0);

  // Enable the MegaMoto
  digitalWrite(pin_en, HIGH);
}


/********************************************//**
 * \brief Setter to change the ms delay when
 *        stepping up or down the PWM duty cycle.
 *
 * Provide the new delay time in milliseconds to
 * this method if you want to change the delay
 * time when "fading/feathering/sliding/ramping"
 * the PWM duty cycle up or down.
 *
 * \param new_ms_delay is an int 
 ***********************************************/
void MegaMotoBase::SetStepDelay( int new_ms_delay )
{
	pwm_step_delay_ms = new_ms_delay;
}

/********************************************//**
 * \brief Getter which returns the current delay
 *        used when changing the PWM duty cycle.
 *
 * Returns the delay time in milliseconds used
 * when "fading/feathering/sliding/ramping" the
 * PWM duty cycle up or down.
 *
 * \return integer value of pwm_step_delay_ms
 *
 ***********************************************/
int MegaMotoBase::GetStepDelay() const
{
	return( pwm_step_delay_ms );
}
 
/********************************************//**
 * \brief Enable the MegaMoto controller
 *
 * Used when the Enable pin is being controlled
 * to enable the MegaMoto controller. If you have
 * called Disable(), you will probably need to call
 * this function again.
 *
 ***********************************************/
void MegaMotoBase::Enable()
{
	if(use_enable_pin)
	{
		digitalWrite(pin_en, HIGH);
	}
}

/********************************************//**
 * \brief Immediatly turn off the output
 *
 * Might be good to use for some safety-critical
 * situation where slowing down the motor/device
 * before turning it off is a *bad* idea.
 *
 ***********************************************/
void MegaMotoBase::Kill()
{
	// Turn on the MegaMoto if it was off previously
	if (use_enable_pin)
	{
		digitalWrite(pin_en, HIGH);
	}

	// Turn off both PWM outputs
	analogWrite(pin_a, 0);
	analogWrite(pin_b, 0);
	
	// Don't disable the MegaMoto. Holding the output
	// might allow some motors with internal brakes
	// to keep their brakes on. This is very useful
	// in a situation where we needed to kill the
	// motor very quickly. Disableing the MegaMoto
	// and letting the motor "free-run" could be bad!
}