#include <pthread.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

static pthread_mutex_t vehicle_lock;
static pthread_cond_t red_team = PTHREAD_COND_INITIALIZER;
static pthread_cond_t blue_team = PTHREAD_COND_INITIALIZER;
char turn[]="GS";
bool busy=false;


void *enter_vehicle(void *team_void_ptr)
{
    // Fill this function
    return NULL;
}

int main()
{
    int total_riders;
    std::cin >> total_riders;
    pthread_mutex_init(&vehicle_lock, NULL);
    pthread_t *threads = new pthread_t[total_riders];
    char **teams = new char*[total_riders];

    for (int i = 0; i < total_riders; i++)
        teams[i] = new char[20];

    for (int i = 0; i < total_riders; i++)
    {
        if(i%2==0){
            strcpy(teams[i],"GS");
        }
        else{
            strcpy(teams[i],"FB");
        }

        if(pthread_create(&threads[i],NULL,enter_vehicle,(void *)teams[i])){
            cerr<<"OOF"<<endl;
            return 1;
        }
        // Write the code to call pthread_create
    }

    for (int i = 0; i < total_riders; i++)
        pthread_join(threads[i], NULL);

    for (int i = 0; i < total_riders; i++)
        delete[] teams[i];
    delete[] teams;
    delete[] threads;
    return 0;
}
