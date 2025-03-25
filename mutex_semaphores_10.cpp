#include <pthread.h>
#include <iostream>
#include <string>
#include <semaphore.h>

using namespace std;

struct ThreadJob {
    int position;
    char symbol;
    string pattern;
};

static pthread_mutex_t locker;
static pthread_cond_t allowNext = PTHREAD_COND_INITIALIZER;
static int active = 0;

void* checkSymbol(void* ptr) {

    pthread_mutex_lock(&locker);
    struct ThreadJob * TJ =(struct ThreadJob *)ptr;//derefe
    while(TJ->position != active){
        pthread_cond_wait(&allowNext,&locker);
    }

    bool found=false;
    for(int i=0;i<TJ->pattern.lenght();i++){
        if(TJ->symbol == TJ->pattern[i]){
            cout<<TJ->symbol;
            found=true;
            break;
        }
    }
    if(!found){
        cout<<"#";

    }
    active++;

    pthread_mutex_unlock(&locker);


    pthread_mutex_lock(&locker);
    pthread_cond_broadcast(&allowNext);
    pthread_mutex_unlock(&locker);

   
    

    return nullptr;
}

int main() {
    string inputSeq, patternSeq;
    cin >> inputSeq >> patternSeq;

    int total = inputSeq.length();
    pthread_t* workers = new pthread_t[total];
    ThreadJob* tasks = new ThreadJob[total];

    pthread_mutex_init(&locker, nullptr);

    for (int i = 0; i < total; i++) {
        //instation
        tasks[i].position=i;
        tasks[i].symbol=inputSeq[i];
        tasks[i].pattern=patternSeq;
    }

    //pthread_created
    for(int i=0;i<total;i++){
        if(pthread_create(&workers[i],NULL,checkSymbol,(void *)&tasks[i])){
            std::cerr<<"Error Creating the thread!"<<std::endl
        }
    }   
    

    for (int i = 0; i < total; i++) {
        pthread_join(workers[i], nullptr);
    }

    delete[] workers;
    delete[] tasks;

    return 0;
}
