#ifndef SHM_VECTOR_H
#define SHM_VECTOR_H

#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#include "shm_semaphore.h"


class shm_vector
{
    key_t  shmkey_;
    int    shmid_;
    int   *shm_;
    int   *addr_;
    u_int  size_;
    int  *indx_;
    shm_semaphore sema_;

    // copy constructor deleted
    //shm_vector(const shm_vector& v);
    // copying assignment deleted
    //shm_vector& operator=(const shm_vector& v) {}
    int& get_ptr(size_t index);
    void map();

public:
    shm_vector(key_t shmkey, size_t size);
    ~shm_vector();
    void clear();
    void push_back(int element);
    int pop();
    size_t size();
    bool empty();
    int& operator[](size_t index);

    //const int& operator[](size_t index) const;
};

#endif // SHM_VECTOR_H
