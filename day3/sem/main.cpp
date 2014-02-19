#include <iostream>

#include <sys/ipc.h>
#include <sys/sem.h>

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

typedef union _semun
{

    int val;
    struct semid_ds *buf;
    unsigned short *array;
} semun;



int main()
{

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
}