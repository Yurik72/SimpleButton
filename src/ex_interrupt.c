#include "ex_interrupt.h"


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
    INTERRUPT_HANDLER_DECLARE(5);
#endif  
#if MAX_HANDLERS > 7
    INTERRUPT_HANDLER_DECLARE(5);
#endif  
static volatile intFunc_args__ex[MAX_HANDLERS]={0};
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
