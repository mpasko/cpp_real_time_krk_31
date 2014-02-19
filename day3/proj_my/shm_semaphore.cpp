#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include "shm_semaphore.h"


shm_semaphore:: shm_semaphore(key_t semkey)
{
    semkey_ = semkey;
    semid_ = semget(semkey_, NUM_SEM, 0666 | IPC_CREAT);
    if (-1 == semid_)
    {
        std::cout << strerror( errno ) << std::endl;
        exit(1);
    }
    numsem_ = 0;
    sem_lock_.sem_num  = numsem_;
    sem_lock_.sem_op   = -1;
    sem_lock_.sem_flg  = SEM_UNDO;
    sem_unlock_.sem_num  = numsem_;
    sem_unlock_.sem_op   = 1;
    sem_unlock_.sem_flg  = SEM_UNDO;
}

int shm_semaphore:: get_value()
{
    return semctl( semid_, 0, GETVAL, 0);
}

void shm_semaphore:: lock()
{
    semop( semid_, &sem_lock_, 1);
}
void shm_semaphore:: unlock()
{
    semop( semid_, &sem_unlock_, 1);
}

shm_semaphore:: ~shm_semaphore()
{

}

/*
using namespace std;

int main(){
    //shm_semaphore::numsem_gen_=0;
    shm_semaphore Sem(10);
    cout << Sem.get_value() << endl;
    Sem.unlock();
    cout << Sem.get_value() << endl;
    Sem.lock();
    Sem.lock();
    cout << Sem.get_value() << endl;
}
*/

/*
    key_t semkey = 0x10;
    int semid;

    semid = semget( semkey, 1, 0666 | IPC_CREAT );  // IPC_EXCL

    if ( semid == -1 )
    {
        std::cout << strerror( errno ) << std::endl;
        exit(1);
    }

    semun arg;
    arg.val = 1;
    semctl( semid, 0, SETVAL, arg);     //  1

    std::cout << semctl( semid, 0, GETVAL, 0) <<  std::endl;

    struct sembuf sem_info;

    // LOCK
    sem_info.sem_num  = 0;
    sem_info.sem_op   = -1;
    sem_info.sem_flg  = SEM_UNDO;

    std::cout << "LOCK " << std::endl;

    semop( semid, &sem_info, 1);        //  0

    std::cout << semctl( semid, 0, GETVAL, 0) <<  std::endl;

    std::cout << "LOCK" << std::endl;
    semop( semid, &sem_info, 1);        //  -1


    // UNLOCK
    sem_info.sem_num  = 0;
    sem_info.sem_op   = 1;
    sem_info.sem_flg  = SEM_UNDO;
    semop( semid, &sem_info, 1);        //  1


    std::cout << semctl( semid, 0, GETVAL, 0) <<  std::endl;
 */
