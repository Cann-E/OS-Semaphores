//GOAL: given a string of numbers, increment any even digits in this number, and keep the odd digits the same, using mutex semaphores to do so.
#include <pthread.h>
#include <iostream>
#include <string>

#include <semaphore.h>

using namespace std;

struct infoFromMain
{
    int threadID; //e.g. thread 0, thread 1....
    int digit; //e.g. 1234, first digit - 1, second digit - 2...
};


static pthread_mutex_t bsem;    // Mutex semaphore
static pthread_cond_t waitTurn = PTHREAD_COND_INITIALIZER;  // Condition variable to control the turn
static int turn = 0; // value to control which child thread enters the critical section


void *printDigit(void *void_ptr)
{
    //GOAL: given a string of numbers, increment any even digits in this number, and keep the odd digits the same, using mutex semaphores to do so.
    pthread_mutex_lock(&bsem);
        struct infoFromMain* info = (struct infoFromMain*)void_ptr;
        while (info->threadID != turn){ //telling any other threads to go to sleep if it's not their turn
            pthread_cond_wait(&waitTurn, &bsem);
        }
        if (info->digit % 2 == 0){
            cout << info->digit+1;
        }
        else if (info->digit % 2 == 1){
            cout << info->digit;
        }
        turn++;
    pthread_mutex_unlock(&bsem);

    pthread_mutex_lock(&bsem);
        pthread_cond_broadcast(&waitTurn); //wake everyone up
    pthread_mutex_unlock(&bsem);

    return nullptr;
}



int main()
{
    std::string input;
    std::cin >> input; //e.g. 1234
    
    int nThreads = input.size();// initialize the number of threads variable;
    pthread_t *tid = new pthread_t[nThreads];
    infoFromMain *arg = new infoFromMain[nThreads];
    
    pthread_mutex_init(&bsem,nullptr);   // Initializing bsem
    
    for(int i=0;i<nThreads;i++)
    {
        arg[i].threadID = i;// initialize the threadID based on the question's specifications
        arg[i].digit = input[i] - '0'; // assign the digit for each child thread based on the question's specifications
        
    }
    for (int i=0;i<nThreads; i++){
        if (pthread_create(&tid[i], nullptr, printDigit, &arg[i])){
            cerr << "thread oofed" << endl;
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