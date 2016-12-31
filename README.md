# MegaMoto Arduino Library
An Arduino library for interfacing with the MegaMoto and MegaMoto Plus by [Robot Power](http://www.robotpower.com/)

![MegaMoto Plus by Robot Power](http://www.robotpower.com/images/MM-Plus-top-sm.jpg)

[TOC]

## What is this?

This is a library to (hopefully) simplify the interface with Robot Power's "MegaMoto" platform(s).

**NOTE: I have currently only have access to an Arduino UNO and the MegaMoto PLUS** so testing has only been performed with that setup. I cannot garuntee anything working for another configuration, although, by what I read in their documentation, it should be similar enough to be just fine. You have been warned. :-) 

## Features

* Easy pin configuration
* Won't touch any pins it doesn't have to. (Example: You chose to set the MegaMoto Enable to a constant 5V, if you use the correct class constructor, the code won't attempt to use the Enable pin.
* Can "ramp" the motor speed instead of abruptly changing from, say, forward to reverse. This is much nicer to the motor you are controlling.

## Getting Started

1. Download this library and unzip in your Arduino/libraries folder. 
   * Click "Clone or download" here in GitHub. 
   * Click "Download as .ZIP" 
   * See [these instructions](https://www.arduino.cc/en/Guide/Libraries) to add the library to your Arduino IDE installation

2. Include the MegaMoto header file in your project .ino file by writing `#include <MegaMoto.h>` at the top of your program.
3. Instantiate a new MegaMoto object and provide the correct pin assignments and hardware configuration you used.
4. Use the `MegaMoto::Move()` function to start your motor moving!

For more information about how to use this library, plese visit the `/doc` folder of this repository (or your downloaded .ZIP file.


## Useful Links

* Robot Power website: [http://www.robotpower.com/](http://www.robotpower.com/)
* MegaMoto info page: [http://www.robotpower.com/products/MegaMoto_info.html](http://www.robotpower.com/products/MegaMoto_info.html)
* MegaMoto Plus info page: [http://www.robotpower.com/products/MegaMotoPlus_info.html](http://www.robotpower.com/products/MegaMotoPlus_info.html)
* MegaMoto and MegaMoto Plus User's guide: [http://www.robotpower.com/downloads/MegaMoto-user-manual.pdf](http://www.robotpower.com/downloads/MegaMoto-user-manual.pdf)
* MegaMoto and MegaMoto Plus schematic: [http://www.robotpower.com/downloads/MegaMoto-v1.5-schematic.pdf](http://www.robotpower.com/downloads/MegaMoto-v1.5-schematic.pdf)
