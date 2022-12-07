struct cond_buffer_elem
{
    int x;                                        // Value stored in buffer elem
    int full;                                     // If the element has a item or not
    struct sleeplock lk;                          // Lock to aloow only one producer to consumer to use it
    struct cond_t inserted;                       // Condition variables used while insertion
    struct cond_t deleted;                        // Condition variables used while insertion
};

