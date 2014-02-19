#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <iostream>

#include "shm_semaphore.h"
#include "shm_vector.h"

int& shm_vector::get_ptr(size_t index)
{
    int * val;
    sema_.lock();
    if ((index < *indx_) && (index>=0)) {
        val=&shm_[index];
    }
    else
    {
        val=NULL;
    }
    sema_.unlock();
    return *val;
}

void shm_vector::map()
{
    addr_ = (int *)shmat(shmid_,0,0);
    indx_ = (int *)addr_;
    shm_ = &addr_[1];
}
void shm_vector::clear()
{
    sema_.lock();
    (*indx_)=0;
    sema_.unlock();
}

shm_vector::shm_vector(key_t shmkey, size_t size): sema_(shmkey)
{
    size_ = size;
    shmkey_ = shmkey;
    if (size>0)
    {
        shmid_ = shmget( shmkey_, size*sizeof(int), 0666 | IPC_CREAT );
    }
    else
    {

    }
    map();
}
void shm_vector::push_back(int element)
{
    sema_.lock();
    shm_[*indx_] = element;
    ++(*indx_);
    sema_.unlock();
}
int shm_vector::pop()
{
    sema_.lock();
    --(*indx_);
    return shm_[*indx_];
    sema_.unlock();
}
size_t shm_vector::size()
{
    sema_.lock();
    return *indx_;
    sema_.unlock();
}
bool shm_vector::empty()
{
    sema_.lock();
    return (*indx_)==0;
    sema_.unlock();
}
int& shm_vector::operator[](size_t index)
{
    return get_ptr(index);
}
/*
const int& shm_vector::operator[](size_t index) const
{
    return get_ptr(index);
}
*/

shm_vector::~shm_vector()
{
    shmdt(addr_);
}

/* */
using namespace std;

int main(){
    //shm_semaphore::numsem_gen_=0;
    shm_vector vec(10,5);
    shm_semaphore sem(10);
    sem.unlock();
    cout<<"created"<<endl;
    vec.clear();
    cout<<"cleared"<<endl;
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    cout << vec.pop() << endl;
    cout << vec.pop() << endl;
    cout << vec.pop() << endl;
}
/* */

/*
#include <iostream>
#include <sys/ipc.h>

#include <sys/shm.h>

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MEM_SIZE 100

int main(int argc, char **argv)
{

    key_t shm_key = 0x0b;

    int* shm;

    int shm_id = shmget( shm_key, MEM_SIZE*sizeof(int), 0666 | IPC_CREAT );

    if( shm_id == -1)
    {
        std::cout <<  strerror( errno ) << std::endl;

        exit(1);
    }

    shm = (int*)shmat(shm_id, 0, 0);
    shm[10] = 123;

    std ::cout << shm[10] << std::endl;

    return 0;
}
 */
