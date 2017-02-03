#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <iostream>
using namespace std;

int main(void) {

        pid_t pid;
        char *shared; /* pointer to the shm */
        int shmid;

        shmid = shmget(IPC_PRIVATE, 1024*1024 + 1, IPC_CREAT | 0666);
        if (fork() == 0) { /* Child */
                /* Attach to shared memory and print the pointer */
                shared = (char*)shmat(shmid, (void *) 0, 0);
                //printf("Child pointer  %p\n", shared);
                //*shared=1;
                //printf("Child value=%d\n", *shared);
                sleep(2);
		for (long i = 0 ; i < 1024 ; i++)
		{
		   cout << shared[i] << endl;
		}

        } else { /* Parent */
                /* Attach to shared memory and print the pointer */
                shared = (char*)shmat(shmid, (void *) 0, 0);
		for (long i = 0 ; i < 1024 * 1024 ; i++)
		{
		   shared[i] = 42;
		}
                //*shared=42;
                sleep(5);
                shmctl(shmid, IPC_RMID, 0);
        }
}
