[![Gitter](https://badges.gitter.im/Join%20Chat.svg)]




Simple Button
===========

This is a library for easily button usage

Supports natvelly ESP32 and and Arduino processors


## Benefits

Library supports multi touch functionality with internal queue stack. For instance you fast pressed double, even triple times. But want to execute quite long code, for instance push some data to the internet cloud. All presses will be stored and and callback will be execute seqentially one by one. Definetelly those calls will be out of ISR
Supports two modes: Short press and Long Press

## Tricks

Button library is implementd by attaching hardware interrupts and each event is stored in queue immediatelly, than 
each callback is processed with possible option
- By timer (supports only ESP32), means on timer function (out of ISR) callback will be called. this is simplify a process

- By Standard loop. You need a call .HandleLoop function and than your defined callback will be called in the same process (loop process)


## Limits

Due to the hardware limitation not all gpio's supports interrupts. Button will still work without Queue possibbilities
In this case button state is analyzed each loop.
This give an advantage to simplify code 

You can check [here](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/) which pins are supported by interrupts

## Usage
first declare a button
CSimpleButton btn;

in setup  call

btn.Create(gpionum, callback,pressed);

where :

gpionum   - gpio number

callback  - callback function

pressed   - bool , defines initial state. For instance for button that wired to gnd during the press should be false. For touch button when is raised signal during touch should be true


 
## Simple example


CSimpleButton btn;   //declare button

void button_callback(uint8_t gpio, button_event_t event) {

Serial.println("Button callback");

}

void setup() {

  // put your setup code here, to run once:
  
btn.Create(4, button_callback,true);  //create button  attache to gpio 4 and with normal low value

}


## For more information




*TODO* - 
