// GOAL: Given a string of lowercase letters, convert any vowel to uppercase.
// All threads must print in order using mutex semaphores (condition variables).

#include <pthread.h>
#include <iostream>
#include <string>
using namespace std;

struct infoFromMain {
    int threadID;
    char letter;
};

static pthread_mutex_t lock;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int turn = 0;

void* processLetter(void* void_ptr)
{
    pthread_mutex_lock(&lock);
    struct infoFromMain * info =(struct infoFromMain *)void_ptr;
    while(info->threadID !=turn){
        pthread_cond_wait(&cond,&lock);
    }
    if(info->letter == 'a' || info->letter == 'e' || info->letter == 'i' || info->letter == 'o' || info->letter == 'u' ){
        cout<<(char)toupper(info->letter);
    }
    else{
        cout<<info->letter;
    }
    turn++;


    pthread_mutex_unlock(&lock);


    pthread_mutex_lock(&lock);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);
    
    return nullptr;
}

int main()
{
    string input;
    cin >> input;

    int nThreads = input.size();
    pthread_t* tid = new pthread_t[nThreads];
    infoFromMain* arg = new infoFromMain[nThreads];

    pthread_mutex_init(&lock, nullptr);

    for (int i = 0; i < nThreads; i++) {
        //init
        arg[i].threadID=i;
        arg[i].letter=input[i];
    }

    //pthread_create
    for(int i=0;i<nThreads;i++){
        if(pthread_create(&tid[i],NULL,processLetter,(void *)&arg[i])){
            cerr<<"Error";
        }
    }

    for (int i = 0; i < nThreads; i++)
        pthread_join(tid[i], nullptr);

    delete[] arg;
    delete[] tid;
    return 0;
}
