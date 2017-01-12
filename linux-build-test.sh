#!/bin/sh

ARD_VER="1.8.0"
ERROR_CNT=0

#sleep 3

#echo "Downloading version $ARD_VER of the Arduino IDE..."
#wget http://downloads.arduino.cc/arduino-$ARD_VER-linux64.tar.xz

#echo "Extracting the Arduino IDE..."
#tar xf arduino-$ARD_VER-linux64.tar.xz

#echo "Moving Arduino IDE..."
#sudo mv arduino-$ARD_VER /usr/local/share/arduino
#echo "Linking Arduino IDE..."
#sudo ln -s /usr/local/share/arduino/arduino /usr/local/bin/arduino
#echo "Removing Arduino IDE ver $ARD_VER tar that was downloaded..."
#rm arduino-$ARD_VER-linux64.tar.xz


echo "Linking Library under Test (LUT) to the Arduino libraries folder..."
ln -s $PWD ~/Arduino/libraries/MegaMoto

arduino --verify --board arduino:avr:uno --verbose-build $PWD/examples/H-Bridge/H-Bridge.pde
if [ $? -ne 0 ] 
then
    ERROR_CNT=$(($ERROR_CNT+1))
fi

arduino --verify --board arduino:avr:uno --verbose-build $PWD/tests/h-bridge-all/h-bridge-all.ino
if [ $? -ne 0 ] 
then
    ERROR_CNT=$(($ERROR_CNT+1))
fi

echo "--------------------------"
echo "--------------------------"
echo "Error count: $ERROR_CNT"

