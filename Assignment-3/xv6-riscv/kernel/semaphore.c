#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "condvar.h"
#include "semaphore.h"


void sem_init (struct semaphore *s, int x){
    s->val=x;
    initsleeplock(&s->slk, "sem_slk");
}

void sem_wait (struct semaphore *s){
    acquiresleep(&s->slk);                           // Protection of Critical section
    while(s->val==0) {cond_wait(&s->cv,&s->slk);}
    s->val--;                                        // Decrease the semaphore cvalue
    releasesleep(&s->slk);

}

void sem_post (struct semaphore *s){
    acquiresleep(&s->slk);                             // Protection of Critical section
    s->val++;                                          // Increment semaphore value
    cond_signal(&s->cv);                               // and wakes up one process waiting on semaphore
    releasesleep(&s->slk);
}