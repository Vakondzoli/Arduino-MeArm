import serial
import time
import sys
from pynput.keyboard import Listener,Key,Controller

keyboard = Controller()
_recorded_keys = []
_record = 0

usb='COM4'
arduino=serial.Serial(usb, baudrate=9600, timeout=1)
time.sleep(1)

if(arduino.isOpen()):
    print ("Serial connection open.")


def on_press(key):    
    handle_key(key)
    


def on_release(key): 
    if key == Key.esc:
        print ("THE END")
        return False


def handle_key(key):
    #print('{0} pressed'.format(key))

    if is_valid_character(key):
        if is_record_switch(key):
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


with Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()
