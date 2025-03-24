
#include <pthread.h>
#include <iostream>
#include <string>

#include <semaphore.h>

using namespace std;

struct infoFromMain
{
    int threadID; 
    char currLetter; 
    string cmpStr;
};


static pthread_mutex_t bsem;    // Mutex semaphore
static pthread_cond_t waitTurn = PTHREAD_COND_INITIALIZER;  // Condition variable to control the turn
static int turn = 0; 


void *compareString(void *void_ptr)
{
  //mutex semaphores
    pthread_mutex_lock(&bsem);
    struct infoFromMain* info=(struct infoFromMain *)void_ptr;

    while(info->threadID!=turn){
        pthread_cond_wait(&waitTurn,&bsem);
    }
    bool found= false;

    for (int i=0;i<info->cmpStr.length();i++){
        if (info->currLetter == info->cmpStr[i]){
            cout<<info->currLetter;
        }
    }

    if(!found){
        cout<<"*";
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
    std::string threadStr, cmpStr;
    std::cin >> threadStr >> cmpStr;
    
    int nThreads = threadStr.size();// initialize the number of threads variable;
    pthread_t *tid = new pthread_t[nThreads];
    infoFromMain *arg = new infoFromMain[nThreads];
    
    pthread_mutex_init(&bsem,nullptr);   // Initializing bsem
    
    for(int i=0;i<nThreads;i++){
      //instantiation
      arg[i].threadID=i;
      arg[i].currLetter=threadStr[i];
      arg[i].cmpStr=cmpStr;
      
    }

    //pthread create
    for(int i=0;i<nThreads;i++){
        if(pthread_create(&tid[i],NULL,compareString,(void*)&arg[i])){
            cerr<<"erro";
        }
    }
    

    for(int i=0;i<nThreads;i++)
        pthread_join(tid[i],nullptr);
   
    if (arg != nullptr)
        delete [] arg; 
    if (tid != nullptr)
        delete [] tid;
    return 0;
}