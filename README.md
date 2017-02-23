# C64 keyboard to serial

An arduino sketch, created for an Arduino mini, that makes a serial keyboard out of a C64 keyboard.

It makes use of the cool [http://playground.arduino.cc/Code/Keypad](Keypad library).

## Pin layout

Sorry, I have lost my notes on how to connect the keyboard to the Arduino mini.

I started from the C64 documentation, but is is wrong:

  * https://www.c64-wiki.com/wiki/Keyboard
  * http://www.zimmers.net/anonftp/pub/cbm/documents/cables/c64-keyboard.txt

From the code:

  ```C
byte colPins[COLS] = {2,3,4,9,6,7,8,5};
byte rowPins[ROWS] = {10,11,12,13,A0,A1,A2,A3};
```

Columns would be A through H
Rows would be 0 to 7
