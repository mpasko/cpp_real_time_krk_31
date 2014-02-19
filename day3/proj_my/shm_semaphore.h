#ifndef SHM_SEMAPHORE_H
#define SHM_SEMAPHORE_H
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>

#define NUM_SEM 5

class shm_semaphore
{
    key_t semkey_;
    int semid_;
    u_int numsem_;
    struct sembuf sem_lock_;
    struct sembuf sem_unlock_;
    static int numsem_gen_;

public:

    shm_semaphore(key_t semkey);

    int get_value();

    void lock();
    void unlock();

    ~shm_semaphore();
};

#endif // SHM_SEMAPHORE_H
