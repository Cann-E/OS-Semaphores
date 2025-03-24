#include <pthread.h>
#include <iostream>
#include <string>
using namespace std;

struct infoFromMain {
    int threadID;
    char ch;
};

static pthread_mutex_t lock;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int turn = 0;

void* replaceVowel(void* void_ptr) {
    pthread_mutex_lock(&lock);
    struct infoFromMain* info= (struct infoFromMain *)void_ptr;
    while(info->threadID != turn){
        pthread_cond_wait(&cond,&lock);
    }
    
    if(info->ch == 'a' || info->ch == 'e' || info->ch == 'i' || info->ch == 'o' || info->ch == 'u' ){
        cout<<"*";
    }
    else{
        cout<<info->ch;
        }
    
    turn++;


    pthread_mutex_unlock(&lock);

    pthread_mutex_lock(&lock);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);
    

    return nullptr;
}

int main() {
    string input;
    cin >> input;

    int n = input.length();
    pthread_t* threads = new pthread_t[n];
    infoFromMain* args = new infoFromMain[n];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < n; i++) {
        //init
        args[i].threadID=i;
        args[i].ch=input[i];
    }

    for (int i = 0; i < n; i++) {
       //pthread_create
       if (pthread_create(&threads[i],NULL,replaceVowel,(void *)&args[i])){
        cerr<<"Erro";
       }
        }
    

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    delete[] threads;
    delete[] args;

    return 0;
}
