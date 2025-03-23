#include <pthread.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

static pthread_mutex_t lab_lock;
static pthread_cond_t engineer = PTHREAD_COND_INITIALIZER;
static pthread_cond_t scientist = PTHREAD_COND_INITIALIZER;
char turn[]="Can";
bool busy=false;

void *use_lab(void *role_void_ptr)
{

    // Fill this function
    return NULL;
}

int main()
{
    int nusers;
    std::cin >> nusers;
    pthread_mutex_init(&lab_lock, NULL);
    pthread_t *tid = new pthread_t[nusers];
    char **roles = new char*[nusers];

    for (int i = 0; i < nusers; i++)
        roles[i] = new char[20];

    for (int i = 0; i < nusers; i++)
    {
        if(i%2==0)
            strcpy(roles[i],"Can");
        else
            strcpy(roles[i],"Mike");
        // Write the code to call pthread_create
        if(pthread_create(&tid[i],NULL,use_lab,(void *)roles[i]))
        {
            cerr<<"ERR"<<endl;
            return 1;
        }
    }

    for (int i = 0; i < nusers; i++)
        pthread_join(tid[i], NULL);

    for (int i = 0; i < nusers; i++)
        delete[] roles[i];
    delete[] roles;
    delete[] tid;
    return 0;
}
