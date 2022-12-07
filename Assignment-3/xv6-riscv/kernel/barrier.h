struct barrier
{
    int count;                              //  number of process whi have reached the barrier
    int allocated;                          // If this barrier is allocated or not
    struct sleeplock lock;                  // Lock used to change the count of barrier
    struct cond_t cv;                       // Condition variable (channel) on which waiting process will sleep
};