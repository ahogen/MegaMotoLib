/********************************************//**
 * \file     MegaMoto.h
 * \author   Alexander Hogen
 * \date     12/30/2016
 * \version  0.1
 * \brief    An object oriented Arduino library
 *           to control the MegaMoto Plus by Robot
 *           Power
 *
 * [1] "MegaMoto & MegaMoto Plus User Manual," Robot Power,
 *     Version 1.6, May 28, 2016.
 *     Avaliable: http://www.robotpower.com/downloads/MegaMoto-user-manual.pdf
 ***********************************************/

#ifndef MEGAMOTO_H
#define MEGAMOTO_H

#include <Arduino.h>

#define MEGA_MOTO_FEATHER_STEP 3

/********************************************//**
 * \enum TMegaMotoWiring
 * \brief Two possible wiring configurations for
 *        the MegaMoto controller
 *
 * 
 ***********************************************/
enum TMegaMotoWiring {
    H_bridge,
    half_bridge
};

enum TMegaMotoDir {
    FWD,
    REV,
    STOP
};

/********************************************//**
 * \class MegaMoto
 * \brief 
 * 
 ***********************************************/
class MegaMoto {

public:
  
  MegaMoto(byte pin_pwm_a, 
           byte pin_pwm_b, 
           TMegaMotoWiring wire_config);
  
  MegaMoto(byte pin_pwm_a, 
           byte pin_pwm_b,
           byte pin_enable,
           TMegaMotoWiring wire_config);

  //void SetSpeed( const byte pwm_duty_in ){ pwm_duty = pwm_duty_in;};

  void Move(const TMegaMotoDir dir, const byte pwm_duty);
  
  void FeatherSpeed( const byte pwm_duty_in );
  
  void Forward();
  void Forward( const byte pwm_duty );
  
  void Reverse();
  void Reverse( const byte pwm_duty );

  void StopBrake();

protected:

private:

  const bool use_enable_pin;
  const byte pin_enable;
  const byte pin_a;
  const byte pin_b;
  byte pwm_duty;
  TMegaMotoWiring wire_config;
  TMegaMotoDir current_dir;
};

#endif // MegaMoto_h
