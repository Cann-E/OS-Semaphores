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
        //ins
        jobs[i].id=i;
        jobs[i].letter=inputStr[i];
        jobs[i].filter=filterStr;

    }
        

    //pthread_create
    

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    delete[] threads;
    delete[] jobs;

    return 0;
}
