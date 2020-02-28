#ifndef ex_interrupt_h
#define ex_interrupt_h
#include "button_config.h"
#include "Arduino.h"
#if !defined(ESP32) &&  !defined(ESP8266) 

#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define MAX_HANDLERS 5
#define PORTB_PINS 8
#define PORTD_PINS 8
#define GPIO_PORTB_CHANGED(cb,port)  cb & (1 << (port-8))
#define GPIO_PORTD_CHANGED(cb,port)  cb & (1 << (port))
typedef void(*interrupt_callback_fn)();
typedef void(*interrupt_callback_witharg_fn)(void*);
#ifdef __cplusplus
extern "C"{
void attachInterrupt_ex(uint8_t interruptNum, interrupt_callback_witharg_fn fn, void * arg, int mode);
#ifndef BUTTON_DISABLE_PORT_B
void attachInterrupt_ex_portb(uint8_t gpionum, interrupt_callback_witharg_fn fn, void * arg, int mode);
#endif
#ifndef BUTTON_DISABLE_PORT_D
void attachInterrupt_ex_portd(uint8_t gpionum, interrupt_callback_witharg_fn fn, void * arg, int mode);
#endif
}
#else
void attachInterrupt_ex(uint8_t interruptNum, interrupt_callback_witharg_fn fn, void * arg, int mode);
#ifndef BUTTON_DISABLE_PORT_B
void attachInterrupt_ex_portb(uint8_t gpionum, interrupt_callback_witharg_fn fn, void * arg, int mode);
#endif
#ifndef BUTTON_DISABLE_PORT_D
void attachInterrupt_ex_portd(uint8_t gpionum, interrupt_callback_witharg_fn fn, void * arg, int mode);
#endif
#endif

#endif
#endif
