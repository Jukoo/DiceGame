#!/usr/bin/env python3 

""" 
 author     : jukoo <funcscript@outlookd.fr> 
 file name  : dice.py 
 description: read and send data using Serial device communication ->T R<-
"""

import os 
import time 
import pip
try : 
    import serial 
except: 
    pip.main(["install"  , "pyserial"]) 

common_port_serial = 9600  

os_udev = {
            "lxps" : "/dev/ttyUSB0",  # linux port serial 
            "winps": "COM"            #  window port serial 
        }


a_avrC = serial.Serial(os_udev["lxps"], common_port_serial)  

print("Rx <- from a_avrC {} ", a_avrC.readline()) 

I_loop=True  

print("reading from  avr device ") 

while I_loop  : 
    print(a_avrC.readline())
