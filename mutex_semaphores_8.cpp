#include <pthread.h>
#include <iostream>
#include <string>
#include <semaphore.h>

using namespace std;

struct infoFromMain
{
    int threadID; 
    char currLetter; 
};

static pthread_mutex_t bsem;    // Mutex semaphore
static pthread_cond_t waitTurn = PTHREAD_COND_INITIALIZER;  // Condition variable to control the turn
static int turn = 0; 

void *maskVowel(void *void_ptr)
{
    pthread_mutex_lock(&bsem);
    struct infoFromMain * info = (struct infoFromMain*)void_ptr;

    while(info->threadID != turn){
        pthread_cond_wait(&waitTurn,&bsem);
    }

    if(info->currLetter == 'a' || info->currLetter == 'e' || info->currLetter == 'i' || info->currLetter == 'o' || info->currLetter == 'u' ){
        cout<<"*";
    }
    else{
        cout<<info->currLetter;
    }

    turn++;

    pthread_mutex_unlock(&bsem);


    pthread_mutex_lock(&bsem);
    pthread_cond_broadcast(&waitTurn);
    pthread_mutex_unlock(&bsem);

    return nullptr;
}

int main()
{
    string input;
    cin >> input;
    
    int nThreads = input.size();
    pthread_t *tid = new pthread_t[nThreads];
    infoFromMain *arg = new infoFromMain[nThreads];
    
    pthread_mutex_init(&bsem, nullptr);
    
    for(int i = 0; i < nThreads; i++) {
        arg[i].threadID=i;
        arg[i].currLetter=input[i];
    }

    for(int i = 0; i < nThreads; i++) {
        if(pthread_create(&tid[i],NULL,maskVowel,(void*)&arg[i])){
            cerr<<"error creating thread";
        }
        }
    

    for(int i = 0; i < nThreads; i++)
        pthread_join(tid[i], nullptr);
   
    delete[] arg; 
    delete[] tid;

    return 0;
}
