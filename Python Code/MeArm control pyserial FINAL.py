#Code to listen to keypresses and use WASD and IJKL to controll the 4 servos on a Arduino controlled MeArm

import serial #serial communication with the Arduino
import time   
import sys
from pynput.keyboard import Listener,Key,Controller #Library checking for keypresses and key releases (also possible for the mouse)

keyboard = Controller()
_recorded_keys = []
_record = 0

usb='COM4'  #or whichever usb port the arduino is connected to
arduino=serial.Serial(usb, baudrate=9600, timeout=1)    #set up serial communication and name it arduino
time.sleep(1)                                           #wait a bit to be sure serial communication is set up

if(arduino.isOpen()):
    print ("Serial connection open.")


def on_press(key):    #if a key is pressed
    handle_key(key)     #call this function
    


def on_release(key): 
    if key == Key.esc:
        print ("THE END")
        return False


def handle_key(key):                    #when key pressed
    #print('{0} pressed'.format(key))

    if is_valid_character(key):         #if its a valid caracter
        if is_record_switch(key):       #is it the one of the record switches?
            toggle_record()

        elif is_play_switch(key):
            play()

        elif is_control_switch(key):
            control_arduino(key)
            if is_recording():
                record(key)

    else:
        print('wrong input')


def is_valid_character(key):
    return hasattr(key, 'char')


def is_record_switch(key):
    return key.char == 'r'


def toggle_record():
    global _record

    if _record == 0:
        print("START RECORDING")
        _record = 1
    else:
        print("STOP RECORDING")
        _record = 0


def is_play_switch(key):
    return key.char == 'p'


def play():
    print("PLAYING")
    arduino.write(b'v')
    for key in _recorded_keys:
        control_arduino(key)


def is_control_switch(key):
    return key.char in ['a', 'd', 'w', 's', 'i', 'k', 'j', 'l', 'v']


def control_arduino(key):    
    arduino.write(key.char.encode())


def is_recording():
    return _record == 1


def record(key):
    global _recorded_keys
    _recorded_keys.append(key)


with Listener(                      #the method used from pynput library checking the keyboard
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()                 #wait until finished litening
