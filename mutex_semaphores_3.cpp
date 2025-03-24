#include <pthread.h>
#include <iostream>
#include <string>
using namespace std;

struct infoFromMain
{
    int threadID; 
    char currLetter; 
};

static pthread_mutex_t lock;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int turn = 0;

void *checkUppercase(void *void_ptr)
{
    pthread_mutex_lock(&lock);
    struct infoFromMain* IFM =(struct infoFromMain *)void_ptr;
    while(IFM->threadID != turn){
        pthread_cond_wait(&cond,&lock);
    }
    if(IFM->currLetter >= 'A' && IFM->currLetter <= 'Z'){
        cout<<IFM->currLetter;
    }
    else{
        cout<<"*";
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

    int nThreads = input.length();
    pthread_t *tid = new pthread_t[nThreads];
    infoFromMain *arg = new infoFromMain[nThreads];

    pthread_mutex_init(&lock, nullptr);

    for (int i = 0; i < nThreads; i++)
    {
        arg[i].threadID=i;
        arg[i].currLetter=input[i];
    
    }

    for(int i=0;i<nThreads;i++){
        if(pthread_create(&tid[i],NULL,checkUppercase,(void*)&arg[i])){
            cerr<<"err";
        }
    }

    

    for (int i = 0; i < nThreads; i++)
        pthread_join(tid[i], nullptr);

    delete[] arg;
    delete[] tid;

    return 0;
}
