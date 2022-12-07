#include "condvar.h"
#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "spinlock.h"
#include "sleeplock.h"

void cond_wait (struct cond_t *cv, struct sleeplock *lock){        
    condsleep(cv,lock);                                    
}

void cond_signal (struct cond_t *cv){
    wakeupone(cv);                           
}

void cond_broadcast (struct cond_t *cv){
    wakeup(cv);
}