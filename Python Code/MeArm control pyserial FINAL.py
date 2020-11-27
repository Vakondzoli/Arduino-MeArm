#Code to listen to keypresses and use WASD and IJKL to controll the 4 servos on a Arduino controlled MeArm

import serial #serial communication with the Arduino
import time   #import library so Python knows what time is and can perform sleep function
import sys    #needed to have access to keyboard presses
from pynput.keyboard import Listener,Key,Controller #Library checking for keypresses and key releases (also possible for the mouse)

keyboard = Controller()
_recorded_keys = []     #empty list for the keys pressed through recording so the movement of the arm can be repeated infinite times after it was performed and recorded once
_record = 0

usb='COM4'  #or whichever usb port the arduino is connected to (can be found in Arduino IDE)
arduino=serial.Serial(usb, baudrate=9600, timeout=1)    #set up serial communication and name it arduino
time.sleep(1)                                           #wait a bit to be sure serial communication is set up

if(arduino.isOpen()):
    print ("Serial connection open.")   #feedback to see connection is open and succesful with Arduino (if not probably because wrong USB port selected)
    
def on_press(key):    #if a key is pressed
    handle_key(key)     #call this function
    
def on_release(key): #also possible to assign function to key releases instead of presses
    if key == Key.esc:  #if Esc is pressed returns false
        print ("THE END")
        return False

def handle_key(key):                    #when key pressed
    #print('{0} pressed'.format(key))
    if is_valid_character(key):         #if its a valid caracter
        if is_record_switch(key):       #is it the one of the record switches? it returns true if the key pressed is "r"
            toggle_record()             #starts recording by calling this function if r was pressed
        elif is_play_switch(key):       #returns true if "p" was pressed
            play()                      #play function send arduino the same keys that been recorded
        elif is_control_switch(key):    #if non of the above checks if the key pressed is one of the control keys for the servos
            control_arduino(key)
            if is_recording():          #also records them if the reocording is on
                record(key)             #recording function
    else:
        print('wrong input')            #if the key does not have attribute returns message

def is_valid_character(key):            #the main function (handle_key) only runs if this function returns true
    return hasattr(key, 'char')

def is_record_switch(key):              #checking if r was pressed and returns true 
    return key.char == 'r'

def toggle_record():                    #record function
    global _record                      #make variable global througout the code otherwise it would only exist in this function
    if _record == 0:                    #if not recording yet turn on recording by making record variable 1
        print("START RECORDING")
        _record = 1
    else:
        print("STOP RECORDING")
        _record = 0
        
def is_play_switch(key):                #if p was pressed returns true
    return key.char == 'p'

def play():                             #send arduino the control keys stored in a list, this way repeating the previously recorded movement of the arm
    print("PLAYING")
    arduino.write(b'v')                 #moves the arm to starting position
    for key in _recorded_keys:          #for loop sends the characters one by one
        control_arduino(key)

def is_control_switch(key):             #returns true if one of these characters were pressed form this list
    return key.char in ['a', 'd', 'w', 's', 'i', 'k', 'j', 'l', 'v']

def control_arduino(key):               #the function actually sending the characters to the arduino
    arduino.write(key.char.encode())

def is_recording():                     #returns true when recording is on
    return _record == 1

def record(key):                        #record function
    global _recorded_keys
    _recorded_keys.append(key)          #when recording is on it adds the pressed character to the list

with Listener(                      #the method used from pynput library checking the keyboard
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()                 #wait until finished litening
