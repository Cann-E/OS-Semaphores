#include <pthread.h>
#include <iostream>
#include <string>
using namespace std;

struct TaskInfo {
    int id;
    char letter;
    string filter;
};

static pthread_mutex_t mtx;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int currentTurn = 0;

void* matchAndPrint(void* arg)
{
    pthread_mutex_lock(&mtx);
    struct TaskInfo* TI = (struct TaskInfo*)arg;

    while(TI->id != currentTurn){
        pthread_cond_wait(&cond,&mtx);
    }
    bool found = false;
    for(int i =0;i<TI->filter.length();i++){
        if(TI->letter == TI->filter[i]){
            found = true;
            cout<<TI->letter;
            break;
        }
    }

    if(!found){
        cout<<"#";
    }


    currentTurn++;
    pthread_mutex_unlock(&mtx);


    pthread_mutex_lock(&mtx);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mtx);
    

    return nullptr;
}

int main()
{
    string inputStr, filterStr;
    cin >> inputStr >> filterStr;

    int n = inputStr.length();
    pthread_t* threads = new pthread_t[n];
    TaskInfo* jobs = new TaskInfo[n];

    pthread_mutex_init(&mtx, NULL);

    for (int i = 0; i < n; i++) {
        jobs[i].id=i;
        jobs[i].letter=inputStr[i];
        jobs[i].filter=filterStr;

    }
        

    for (int i = 0; i < n; i++) {
        if(pthread_create(&threads[i],NULL,matchAndPrint,(void*)&jobs[i])){
            cerr<<"Error";
        }
    }
    

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    delete[] threads;
    delete[] jobs;

    return 0;
}
