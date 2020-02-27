#ifndef ex_interrupt_h
#define ex_interrupt_h
#include <Arduino.h>
#define MAX_HANDLERS 5


typedef void(*interrupt_callback_fn)();
typedef void(*interrupt_callback_witharg_fn)(void*);
#ifdef __cplusplus
extern "C"{
void attachInterrupt_ex(uint8_t interruptNum, interrupt_callback_witharg_fn fn, void * arg, int mode);
}
#else
void attachInterrupt_ex(uint8_t interruptNum, interrupt_callback_witharg_fn fn, void * arg, int mode);
#endif

#endif
