#!/usr/bin/env python3 

""" 
 author     : jukoo <funcscript@outlookd.fr> 
 file name  : dice.py 
 description: read and send data using Serial device communication ->T R<-
"""

import os 
import time 
import pip
import json 

try : 
    import serial 
except: 
    pip.main(["install"  , "pyserial"]) 

class UndefineCommonOSFlag(Exception) : 
    def __init__(self ,*args , **kwargs ) : 
        Exception.__init__(self , *args , **kwargs) 


file_settings = "os_setting.json" 


def os_call () : 
    """     
        os_call  call automaticly the current os and set the correct 
        serial device comminucation  
    """ 
    assert os.path.exists(file_settings) 
    current_os = os.sys.platform
    setting_data = json.load(open(file_settings))
    os_section , sp=  setting_data["os"] ,setting_data["serial_port"]  
    os_flag = [os_type  for os_type in os_section.keys() if current_os == os_type] 
    if len(os_flag) < 1 : 
        raise UndefineCommonOSFlag("""
         undefine  os type in  os_setting.json file 
         add your os name  in  os flag section
         ---
         'os' : {
            'your_os_name':'serial_port_comminucation' 
         }
        """)  
    return os_section[os_flag[0]] , sp 


udev  , port  = os_call() 
    
a_avrC = serial.Serial(udev , port)   

print("Rx <- from a_avrC {} ", a_avrC.readline()) 

I_loop=True  

print("reading from  avr device ") 

while I_loop  : 
    print(a_avrC.readline()) 
    time.slee(2)  
    uplay  = input("[Tx -> send data]") 
    a_avrC.write(uplay.encode())
    

