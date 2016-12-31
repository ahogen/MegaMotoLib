#include "MegaMoto.h"

MegaMoto::MegaMoto( byte pin_a_in, 
          byte pin_b_in, 
          TMegaMotoWiring wire_config )
          : use_enable_pin( false ), 
          pin_enable( 255 ),
          pin_a ( pin_a_in ),
          pin_b ( pin_b_in ),
          pwm_duty  ( 0 ), 
          wire_config( wire_config ),
          current_dir (TMegaMotoDir::STOP)
{
  // Set pins to output mode for MegaMoto
  pinMode(pin_a, OUTPUT);
  pinMode(pin_b, OUTPUT);

  // Turn OFF both A and B PWM outputs
  analogWrite(pin_a, 0);
  analogWrite(pin_b, 0);
}


MegaMoto::MegaMoto( byte pin_a_in, 
          byte pin_b_in,
          byte pin_enable_in,
          TMegaMotoWiring wire_config )
          : use_enable_pin( true ), 
          pin_enable( pin_enable_in ),
          pin_a ( pin_a_in ),
          pin_b ( pin_b_in ),
          pwm_duty  ( 0 ), 
          wire_config( wire_config ),
          current_dir (TMegaMotoDir::STOP)
{
  // Set pins to output mode for MegaMoto
  pinMode(pin_a, OUTPUT);
  pinMode(pin_b, OUTPUT);
  pinMode(pin_enable, OUTPUT);

  // Turn OFF both A and B PWM outputs
  analogWrite(pin_a, 0);
  analogWrite(pin_b, 0);

  // Enable the MegaMoto
  digitalWrite(pin_enable, HIGH);
}


void MegaMoto::Forward()
{
  if (use_enable_pin)
  {
    digitalWrite(pin_enable, HIGH);
  }
  
  analogWrite(pin_a, pwm_duty);
  analogWrite(pin_b, 0);
}

void MegaMoto::Forward( byte pwm_duty_in )
{
  if (use_enable_pin)
  {
    digitalWrite(pin_enable, HIGH);
  }
  
  analogWrite(pin_a, pwm_duty_in);
  analogWrite(pin_b, 0);
}

void MegaMoto::Reverse()
{
  if (use_enable_pin)
  {
    digitalWrite(pin_enable, HIGH);
  }
  
  analogWrite(pin_a, 0);
  analogWrite(pin_b, pwm_duty);
}

void MegaMoto::Reverse( byte pwm_duty_in )
{
  if (use_enable_pin)
  {
    digitalWrite(pin_enable, HIGH);
  }
  
  analogWrite(pin_a, 0);
  analogWrite(pin_b, pwm_duty_in);
}

void MegaMoto::Move(const TMegaMotoDir dir, const byte pwm_duty_in)
{

  if ( dir == current_dir )
  {
    FeatherSpeed(pwm_duty_in);
  }
  else if ( dir == TMegaMotoDir::STOP )
  {
    // Slow to a stop
    FeatherSpeed( 0 );

    // Change current direction to the STOP case
    current_dir = TMegaMotoDir::STOP;

    // Turn off both A and B sides and brake (if internal brakes)
    StopBrake();
  }
  // We are going to be changing directions (i.e. forward -> reverse)
  else
  {
    // Slow down previous direction
    FeatherSpeed( 0 );

    // Change directions
    current_dir = dir;

    // Speed up in new direction
    FeatherSpeed( pwm_duty_in );
  }
}

void MegaMoto::FeatherSpeed(const byte pwm_duty_in)
{
  bool increment = (pwm_duty_in > pwm_duty ? true : false);

  if ( increment )
  {
    // Loop until current PWM matches the larger, target PWM
    for ( ; pwm_duty < pwm_duty_in; pwm_duty++)
    {
      // Call the correct direction function
      if ( current_dir == TMegaMotoDir::FWD )
      {
        Forward();
      }
      else if ( current_dir == TMegaMotoDir::REV )
      {
        Reverse();
      }
      else
      {
        // Nothing to do. Don't waste time here
        break;
      }
  
      // Wait for _ time before reducing another step
      delay(MEGA_MOTO_FEATHER_STEP);
    }
  }
  else
  {
    // Loop until current PWM matches the reduced, target PWM
    for ( ; pwm_duty > pwm_duty_in; pwm_duty--)
    {
  
      // Call the correct direction function
      if ( current_dir == TMegaMotoDir::FWD )
      {
        Forward();
      }
      else if ( current_dir == TMegaMotoDir::REV )
      {
        Reverse();
      }
      else
      {
        // Nothing to do. Don't waste time here
        break;
      }
  
      // Wait for _ time before reducing another step
      delay(MEGA_MOTO_FEATHER_STEP);
    }
  }
}

void MegaMoto::StopBrake()
{
  if (use_enable_pin)
  {
    digitalWrite(pin_enable, HIGH);
  }
  
  analogWrite(pin_a, 0);
  analogWrite(pin_b, 0);
}

