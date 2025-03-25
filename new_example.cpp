#include <pthread.h>
#include <iostream>
#include <string>

using namespace std;

struct ThreadData {
    int index;
    int number;
};

static pthread_mutex_t locky;
static pthread_cond_t nextTurn = PTHREAD_COND_INITIALIZER;
static int current = 0;

void* updateAndPrint(void* param)
{
    pthread_mutex_lock(&locky);
    struct ThreadData* TD=(struct ThreadData*)param;

    while(TD->index != current){
        pthread_cond_wait(&nextTurn,&locky);
    }

    if(TD->number%2==0){
        cout<<TD->number+1;
    }else{
        cout<<TD->number;
    }




    current++;
    pthread_mutex_unlock(&locky);
    //if even +1 if odd print same

    pthread_mutex_lock(&locky);
    pthread_cond_broadcast(&nextTurn);
    pthread_mutex_unlock(&locky);

    return nullptr;
}

int main()
{
    string digitStr;
    cin >> digitStr;

    int count = digitStr.size();
    pthread_t* threads = new pthread_t[count];
    ThreadData* inputs = new ThreadData[count];

    pthread_mutex_init(&locky, nullptr);

    for (int i = 0; i < count; i++) {
        //ins
        inputs[i].index=i;
        inputs[i].number=digitStr[i]-'0';
    }
    //create
    for(int i=0;i<count;i++){
        if(pthread_create(&threads[i],NULL,updateAndPrint,(void *)&inputs[i])){
            std::cerr<<"Error Creating";
        }
    }

    for (int i = 0; i < count; i++) {
        pthread_join(threads[i], nullptr);
    }

    delete[] threads;
    delete[] inputs;

    return 0;
}
