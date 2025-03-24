#include <pthread.h>
#include <iostream>
#include <string>
#include <semaphore.h>

using namespace std;

struct ThreadPayload
{
    int index;
    char symbol;
};

static pthread_mutex_t locky;
static pthread_cond_t goNext = PTHREAD_COND_INITIALIZER;
static int step = 0;

void* cleanSymbol(void* arg)
{
    pthread_mutex_lock(&locky);
    struct ThreadPayload* payload = (struct ThreadPayload *)arg;
    while(payload->index != step){
        pthread_cond_wait(&goNext,&locky);
    }

    if(!isalnum(payload->symbol)){
        cout<<"@";
    }
    else{
        cout<<payload->symbol;
    }

    step++;


    pthread_mutex_unlock(&locky);

    pthread_mutex_lock(&locky);
    pthread_cond_broadcast(&goNext);
    pthread_mutex_unlock(&locky);
    

    return nullptr;
}

int main()
{
    string dirtyInput;
    cin >> dirtyInput;

    int len = dirtyInput.length();
    pthread_t* threads = new pthread_t[len];
    ThreadPayload* jobs = new ThreadPayload[len];

    pthread_mutex_init(&locky, nullptr);

    for (int i = 0; i < len; i++) {
        //init
        jobs[i].index=i;
        jobs[i].symbol=dirtyInput[i];
    }

    for (int i = 0; i < len; i++) {
        //create
        if(pthread_create(&threads[i],NULL,cleanSymbol,(void *)&jobs[i])){
            cerr<<"error";
        }
    }
    

    for (int i = 0; i < len; i++) {
        pthread_join(threads[i], nullptr);
    }

    delete[] threads;
    delete[] jobs;

    return 0;
}
