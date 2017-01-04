/********************************************//**
 * \file     MegaMoto.cpp
 * \author   Alexander Hogen
 * \date     1/1/2017
 * \version  0.1
 * \brief    Contains the definitions for all the
 *           member methods of the MegaMoto class.
 *
 ***********************************************/

#include "MegaMotoHB.h"

/********************************************//**
 * \brief Constructor to initialize with pin
 *        numbers for PWM A and PWM B and
 *        specify the motor wiring.
 *
 * Initializes the data members and sets up the
 * Arduino pins appropariately to be able to talk
 * to the MegaMoto properly.
 *
 * \param pin_pwm_a is a byte. Specify the pin
 *        used for MegaMoto PWM A here.
 *
 * \param pin_pwm_b is a byte. Specify the pin
 *        used for MegaMoto PWM B here.
 *
 ***********************************************/
MegaMotoHB::MegaMotoHB(
	unsigned char pin_pwm_a,
	unsigned char pin_pwm_b):
	MegaMoto(pin_pwm_a, pin_pwm_b),
	pwm_duty(0),
	current_dir(TMegaMotoHBDir::STOP)
{}

/********************************************//**
 * \brief Constructor to initialize with pin
 *        numbers for PWM A, PWM B, and Enable.
 *
 * Initializes the data members and sets up the
 * Arduino pins appropariately to be able to talk
 * to the MegaMoto properly.
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
MegaMotoHB::MegaMotoHB(
	char pin_pwm_a,
	char pin_pwm_b,
	char pin_enable):
	MegaMoto(pin_pwm_a, pin_pwm_b, pin_enable),
	pwm_duty(0),
	current_dir(TMegaMotoHBDir::STOP)
{}

/********************************************//**
 * \brief Change the power output, either speed
 *        (power strength) or direction (polarity)
 *
 * Use this method to change the current output
 * state of the MegaMoto. If the device being 
 * controlled is a motor, then this adjusts the
 * direction (polarity) and speed (PWM duty cycle).
 * However, for a light or some other device, you
 * might call it changing the voltage direction
 * and power/brightness.
 *
 * Calls StepPwmDuty() to gradually adjust the
 * old PWM duty cycle to the new PWM duty cycle
 * (i.e. If going from TMegaMotoDir::FWD to 
 * TMegaMotoDir::REV, this method will slow down
 * in the FWD direction, and then speed up in the
 * REV direction.)
 *
 * \param dir is the new motor direction, defined
 *        by TMegaMotoDir states.
 *
 * \param new_pwm_duty is the new PWM duty cycle or
 *        power output in the aforementioned
 *        direction. Valid values are 0 - 255, so
 *        it is a byte datatype.
 *
 ***********************************************/
void MegaMotoHB::Power(const TMegaMotoHBDir dir, const unsigned char new_pwm_duty)
{

  if ( dir == current_dir )
  {
    StepPwmDuty(new_pwm_duty);
  }
  else if ( dir == TMegaMotoHBDir::STOP )
  {
    // Slow to a stop
    StepPwmDuty( 0 );

    // Change current direction to the STOP case
    current_dir = TMegaMotoHBDir::STOP;

    // Turn off both A and B sides and brake (if internal brakes)
    Stop();
  }
  // We are going to be changing directions (i.e. forward -> reverse)
  else
  {
    // Slow down previous direction
    StepPwmDuty( 0 );

    // Change directions
    current_dir = dir;

    // Speed up in new direction
    StepPwmDuty( new_pwm_duty );
  }
}

/********************************************//**
 * \brief Gradually change the PWM output from
 *        what it was to the new desired PWM
 *        duty cycle.
 *
 * Since motors and many other physical things
 * don't like sudden changes, it is a good idea
 * to fade between different speeds/power levels.
 * See the definition of MEGA_MOTO_FEATHER_STEP
 * for the actual fade speed.
 *
 * Called by the Power() method.
 *
 * \param pwm_duty_in is the new desired duty
 *        cycle. Acceptable values range from
 *        0 - 255.
 *
 ***********************************************/
void MegaMotoHB::StepPwmDuty(unsigned char pwm_duty_in)
{
	bool increment = (pwm_duty_in > pwm_duty ? true : false);

	if ( increment )
	{
		// Loop until current PWM matches the larger, target PWM
		for ( ; pwm_duty < pwm_duty_in; pwm_duty++)
		{
			// Call the correct direction function
			if ( current_dir == TMegaMotoHBDir::FWD )
			{
				// FORWARD
				analogWrite(pin_a, pwm_duty);
				//analogWrite(pin_b, 0);
			}
			
			else if ( current_dir == TMegaMotoHBDir::REV )
			{
				// REVERSE
				//analogWrite(pin_a, 0);
				analogWrite(pin_b, pwm_duty);
			}
			else
			{
				// Must have been an error. 
				// Set both current and desired PWMs to 0
				// so that the for() loop exits.
				pwm_duty = pwm_duty_in = 0;
			}

			// Wait for _ time before reducing another step
			delay( pwm_step_delay_ms );
		}
	}
	
	// We need to decrement to reach the new duty cycle
	else
	{
		// Loop until current PWM matches the reduced, target PWM
		for ( ; pwm_duty > pwm_duty_in; pwm_duty--)
		{

			// Call the correct direction function
			if ( current_dir == TMegaMotoHBDir::FWD )
			{
				// FORWARD
				analogWrite(pin_a, pwm_duty);
				//analogWrite(pin_b, 0);
			}
			
			else if ( current_dir == TMegaMotoHBDir::REV )
			{
				// REVERSE
				//analogWrite(pin_a, 0);
				analogWrite(pin_b, pwm_duty);
			}
			
			else
			{
				// Must have been an error. 
				// Set both current and desired PWMs to 0
				// so that the for() loop exits.
				pwm_duty = pwm_duty_in = 0;
			}

			// Wait for _ time before reducing another step
			delay( pwm_step_delay_ms );
		}
	}
}

/********************************************//**
 * \brief "Gracefully" power down the motor/device
 *        and then (if applicable) disable the
 *        MegaMoto.
 *
 * If the Enable pin IS being used, you will need
 * to call Enable() to resume operation after
 * using Disable().
 *
 *
 ***********************************************/
void MegaMotoHB::Disable()
{
  
  // Turn off the output device(s)
  Power(STOP, 0);
  
  // Disable the MegaMoto
  if (use_enable_pin)
  {
    digitalWrite(pin_en, LOW);
  }
}