/********************************************//**
 * \file     MegaMotoHB.h
 * \author   Alexander Hogen
 * \date     1/1/2011
 * \version  0.1
 * \brief    H-Bridge configuration -- An Arduino
 *           library to control the MegaMoto Plus
 *           by Robot Power
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
 * [1] "MegaMoto & MegaMoto Plus User Manual," Robot Power,
 *     Version 1.6, May 28, 2016.
 *     Avaliable: http://www.robotpower.com/downloads/MegaMoto-user-manual.pdf
 ***********************************************/

#ifndef MEGAMOTOHB_H
#define MEGAMOTOHB_H

#include "MegaMoto.h"

/********************************************//**
 * \class MegaMotoHB
 * \brief MegaMoto class for H-bridge driving
 *        configurations.
 * 
 * This is the class used when you are using a
 * single motor/device with both (+) and (-)
 * terminals hooked up directly to the A and B
 * outputs of the MegaMoto controller.
 *
 * See section "3. Application Configurations"
 * in the MegaMoto user manual for more wiring
 * information.
 *
 * Please see the example file(s) for, well...
 * examples! ;-)
 ***********************************************/
class MegaMotoHB : public MegaMoto {

public:

	// -- Constructors
	MegaMotoHB(
		unsigned char pin_pwm_a, 
		unsigned char pin_pwm_b);

	MegaMotoHB(
		char pin_pwm_a, 
		char pin_pwm_b,
		char pin_enable);
		
	/********************************************//**
	 * \enum TMegaMotoHBDir
	 * \brief Defines the three possible output
	 *        directions
	 *
	 * Thinking from a single motor wired in H-bridge
	 * mode, there are three possible directions
	 *
	 * \var FWD
	 *      Forward direction: PWM A is on at a duty
	 *      cycle defined by pwm_duty. PWM B is off.
	 *      MegaMoto output MA will have a higher
	 *      potential than MB.
	 *
	 * \var REV
	 *      Reverse direction: PWMA is off. PWMB is
	 *      on at a duty cycle defined by pwm_duty.
	 *      MegaMoto output MA will have a higher
	 *      potential than MB.
	 *
	 * \var STOP
	 *      Motor is off: PWMA is off. PWMB is off.
	 *      MegaMoto output MA will have the same
	 *      potential as MB (which is 0V).
	 * 
	 ***********************************************/
	enum TMegaMotoHBDir {
		FWD,
		REV,
		STOP
	};

	inline void Fwd( const unsigned char new_pwm_duty )
		{ Power( TMegaMotoHBDir::FWD, new_pwm_duty ); }
		
	inline void Rev( const unsigned char new_pwm_duty )
		{ Power( TMegaMotoHBDir::REV, new_pwm_duty ); }
		
	inline void Stop()
		{ Power( TMegaMotoHBDir::STOP, 0 ); }
		
	void Power(const TMegaMotoHBDir dir, const unsigned char pwm_duty);
  
	void StepPwmDuty( unsigned char pwm_duty_in );

	void Disable();

protected:

  // Nothing here :-)

private:
 
	/********************************************//**
	 * \var pwm_duty 
	 * \brief Current PWM duty cycle being output 
	 ***********************************************/
	unsigned char pwm_duty;

	TMegaMotoHBDir current_dir;
};

#endif // MegaMotoHB_h
