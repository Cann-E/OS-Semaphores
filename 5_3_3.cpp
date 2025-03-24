#include <pthread.h>
#include <iostream>
#include <string>
using namespace std;

struct infoFromMain
{
    int threadID;
    char currChar;
    string filterStr;
};

static pthread_mutex_t lock;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int turn = 0;

void *filterCharacter(void *void_ptr)
{
    pthread_mutex_lock(&lock);
    struct infoFromMain * info = (struct infoFromMain *)void_ptr;
    while(info->threadID != turn){
        pthread_cond_wait(&cond,&lock);
    }
    bool found=false;
    for(int i=0;i<info->filterStr.length();i++){
        if(info->currChar == info->filterStr[i]){
            found = true;
            cout<<info->currChar;
        }
    }
    if(!found){
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
    string inputStr, filterStr;
    cin >> inputStr >> filterStr;

    int n = inputStr.length();
    pthread_t *threads = new pthread_t[n];
    infoFromMain *args = new infoFromMain[n];

    pthread_mutex_init(&lock, nullptr);

    for (int i = 0; i < n; i++)
    {
       //init
       args[i].threadID=i;
       args[i].currChar=inputStr[i];
       args[i].filterStr=filterStr;
    }

    for (int i = 0; i < n; i++)
    {
       //pthread create
       if(pthread_create(&threads[i],NULL,filterCharacter,(void *)&args[i])){
        cerr<<"Err";
       }
    }

    for (int i = 0; i < n; i++)
        pthread_join(threads[i], nullptr);

    delete[] threads;
    delete[] args;
    return 0;
}
