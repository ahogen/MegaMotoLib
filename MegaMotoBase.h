/********************************************//**
 * \file     MegaMotoBase.h
 * \author   Alexander Hogen
 * \date     1/11/2017
 * \version  0.1
 * \brief    An object oriented Arduino library
 *           to control the MegaMoto Plus by Robot
 *           Power
 *
 * This is a base class for the MegaMoto library.
 * You should not be including this header in
 * your code. Instead, go look at the MegaMotoHB
 * or MegaMotoHalfB classes. You should use one
 * of those in your project. 
 *
 * NOTE: References to MegaMoto, MegaMoto Plus,
 *       and Robot Power are either reserved or
 *       trademarked by Robot Power:
 *
 *       2745 Martin Way E, Suite D
 *       Olympia, WA 98506
 *       http://www.robotpower.com/
 *
 * I do not own or claim ownership to these names.
 *
 * Released into the public domain.
 *
 * [1] "MegaMoto & MegaMoto Plus User Manual," Robot Power,
 *     Version 1.6, May 28, 2016.
 *     Avaliable: http://www.robotpower.com/downloads/MegaMoto-user-manual.pdf
 ***********************************************/

#ifndef MEGAMOTOBASE_H
#define MEGAMOTOBASE_H

#include <Arduino.h>

/********************************************//**
 * \class MegaMotoBase
 * \brief Provides an easy way to interface with
 *        the MegaMoto controller by Robot Power
 * 
 * This is a parent class. You should not be
 * directly using this class in your code.
 * Instead, use MegaMotoHB or MegaMotoHalfB in
 * your code, depending on your device hookup
 * configuration.
 *
 * Please see the example file(s) for, well...
 * examples! ;-)
 ***********************************************/
class MegaMotoBase {

public:
  

	MegaMotoBase(
		unsigned char pin_pwm_a, 
		unsigned char pin_pwm_b);

	MegaMotoBase(
		unsigned char pin_pwm_a, 
		unsigned char pin_pwm_b,
		unsigned char pin_enable);

	void SetStepDelay(int new_ms_delay);
	int  GetStepDelay() const;

	void Enable();
	virtual void Disable() = 0;
    virtual void Kill() = 0;

protected:

	const bool use_enable_pin;  //!< TRUE if Enable pin will be controlled by this object
	const unsigned char pin_en; //!< Arduino pin number of the Enable line
	const unsigned char pin_a;  //!< Arduino pin number of MegaMoto PWM A
	const unsigned char pin_b;  //!< Arduino pin number of MegaMoto PWM B

	/********************************************//**
	* \var pwm_step_delay_ms
	* \brief Defines the delay in milliseconds
	*        used when "fading" the PWM duty cycle
	*        up or down.
	*
	* This defines the value used in a delay() call
	* in the StepPwmDuty() method. Therefore, this
	* value is in milliseconds (ms). To slow the
	* changes in speed (make the change longer),
	* increase this value.
	*
	***********************************************/
	unsigned char pwm_step_delay_ms;
  
private:

  // Nothing here, since the children classes are intended to inheirit
  // everything currently in this parent class

};

#endif // MegaMotoBase_h
