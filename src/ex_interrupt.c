#include "ex_interrupt.h"
#if !defined(ESP32) &&  !defined(ESP8266) 

#define INTERRUPT_HANDLER(num)  _ex_interrupt_##num

#define INTERRUPT_HANDLER_DECLARE(num)  void INTERRUPT_HANDLER(num)()
#define INTERRUPT_HANDLER_IMPL(num) INTERRUPT_HANDLER_DECLARE(num){ \
if(intFunc_witharg_ex[num]) \
  intFunc_witharg_ex[num](intFunc_args__ex[num]); };




#if MAX_HANDLERS > 0
    INTERRUPT_HANDLER_DECLARE(0);
#endif  

#if MAX_HANDLERS >1
    INTERRUPT_HANDLER_DECLARE(1);
#endif  

#if MAX_HANDLERS > 2
    INTERRUPT_HANDLER_DECLARE(2);
#endif  
#if MAX_HANDLERS > 3
    INTERRUPT_HANDLER_DECLARE(3);
#endif  
#if MAX_HANDLERS > 4
    INTERRUPT_HANDLER_DECLARE(4);
#endif  
#if MAX_HANDLERS > 5
    INTERRUPT_HANDLER_DECLARE(5);
#endif  
#if MAX_HANDLERS > 6
    INTERRUPT_HANDLER_DECLARE(6);
#endif  
#if MAX_HANDLERS > 7
    INTERRUPT_HANDLER_DECLARE(7);
#endif 
#if MAX_HANDLERS > 8
	INTERRUPT_HANDLER_DECLARE(8);
#endif 
#if MAX_HANDLERS > 9
	INTERRUPT_HANDLER_DECLARE(9);
#endif 
#if MAX_HANDLERS > 10
	INTERRUPT_HANDLER_DECLARE(10);
#endif 
#if MAX_HANDLERS > 11
	INTERRUPT_HANDLER_DECLARE(11);
#endif 
#if MAX_HANDLERS > 12
	INTERRUPT_HANDLER_DECLARE(12);
#endif 
static volatile void* intFunc_args__ex[MAX_HANDLERS]={0};
static volatile interrupt_callback_witharg_fn intFunc_witharg_ex[MAX_HANDLERS] = {0};
static volatile interrupt_callback_fn intFunc_ex[MAX_HANDLERS] = {
#if MAX_HANDLERS > 0
    INTERRUPT_HANDLER(0)
#endif
#if MAX_HANDLERS > 1
    ,INTERRUPT_HANDLER(1)
#endif
#if MAX_HANDLERS > 2
   , INTERRUPT_HANDLER(2)
#endif
#if MAX_HANDLERS > 3
    ,INTERRUPT_HANDLER(3)
#endif
#if MAX_HANDLERS > 4
    ,INTERRUPT_HANDLER(4)
#endif
#if MAX_HANDLERS > 5
   , INTERRUPT_HANDLER(5)
#endif
#if MAX_HANDLERS > 6
    ,INTERRUPT_HANDLER(6)
#endif
#if MAX_HANDLERS > 7
   , INTERRUPT_HANDLER(7)
#endif
#if MAX_HANDLERS > 8
   , INTERRUPT_HANDLER(8)
#endif
#if MAX_HANDLERS > 9
   , INTERRUPT_HANDLER(9)
#endif
#if MAX_HANDLERS > 10
   , INTERRUPT_HANDLER(10)
#endif
#if MAX_HANDLERS > 11
   , INTERRUPT_HANDLER(11)
#endif
#if MAX_HANDLERS > 12
   , INTERRUPT_HANDLER(11)
#endif
};


#if MAX_HANDLERS > 0
    INTERRUPT_HANDLER_IMPL(0)
#endif  
#if MAX_HANDLERS >1
    INTERRUPT_HANDLER_IMPL(1)
#endif  
#if MAX_HANDLERS > 2
    INTERRUPT_HANDLER_IMPL(2)
#endif  
#if MAX_HANDLERS > 3
    INTERRUPT_HANDLER_IMPL(3)
#endif  
#if MAX_HANDLERS > 4
    INTERRUPT_HANDLER_IMPL(4)
#endif  
#if MAX_HANDLERS > 5
    INTERRUPT_HANDLER_IMPL(5)
#endif  
#if MAX_HANDLERS > 6
    INTERRUPT_HANDLER_IMPL(6)
#endif  
#if MAX_HANDLERS > 7
    INTERRUPT_HANDLER_IMPL(7)
#endif  
#if MAX_HANDLERS > 8
    INTERRUPT_HANDLER_IMPL(8)
#endif  

void attachInterrupt_ex(uint8_t interruptNum, interrupt_callback_witharg_fn fn, void * arg, int mode)
{
  if(interruptNum>MAX_HANDLERS)
    return;
  //attaching interrupt to our internal table
    attachInterrupt(interruptNum,intFunc_ex[interruptNum],mode);
    //storing function and args
    intFunc_args__ex[interruptNum]=arg;
    intFunc_witharg_ex[interruptNum]=fn;
}
//PORTB   digital pins 8 - 15 implementation
static volatile void* intPORTBFunc_args__ex[PORTB_PINS] = { 0 };
static volatile interrupt_callback_witharg_fn intPORTBFunc_witharg_ex[PORTB_PINS] = { 0 };
volatile uint8_t portbhistory = 0xFF;

ISR(PCINT0_vect)
{
	
	
	uint8_t changedbits;
	changedbits = PINB ^ portbhistory;
	portbhistory = PINB;
	for (uint8_t i = 0; i < PORTB_PINS; i++) {
		if (intPORTBFunc_witharg_ex[i]) {
			if (GPIO_PORTB_CHANGED(changedbits, i + 8)) {
				intPORTBFunc_witharg_ex[i](intPORTBFunc_args__ex[i]);
			}
		}
	}
}
void attachInterrupt_ex_portb(uint8_t gpionum, interrupt_callback_witharg_fn fn, void * arg, int mode)
{
	
	if ((gpionum < 8) || (gpionum >15))
		return;

	uint8_t bnum = gpionum - 8;
	// DDRB  will not setup suppose that base handler will do pinMode
	// PORTB  will not setup



	PCICR |= (1 << PCIE0);  // Turn on port B for interrupts
	PCMSK0 |= (1 << (PCINT0 + bnum));      //Set mask to hanle interrupt on pin

	sei();

	intPORTBFunc_args__ex[bnum] = arg;
	intPORTBFunc_witharg_ex[bnum] = fn;
	portbhistory = PINB;

}


#endif