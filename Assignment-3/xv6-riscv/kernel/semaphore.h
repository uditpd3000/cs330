struct semaphore
{  
    int val;               // Value of semaphore
    struct cond_t cv;      // Condition variable (channel)
    struct sleeplock slk;   // Lock used for semaphore value increment and decrement
};