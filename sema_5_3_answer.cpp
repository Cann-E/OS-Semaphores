/*
Goal: we will take in two threads, threadStr, cmpStr, respectively.
We will compare threadStr to cmpStr whether each character exists in cmpStr, if so, print it, if not print * instead.
Make one thread per character in threadStr.
*/
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
     
      
    }

    //pthread create
    

    for(int i=0;i<nThreads;i++)
        pthread_join(tid[i],nullptr);
   
    if (arg != nullptr)
        delete [] arg; 
    if (tid != nullptr)
        delete [] tid;
    return 0;
}