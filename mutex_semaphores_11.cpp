#include <pthread.h>
#include <iostream>
#include <string>

// Instructions: 

// Compute and print the first N triangular numbers in decreasing order.
// A triangular number for a given i is calculated using the formula: i*(i+1)/2

// Example:
// Input: 
// 5

// Output:
// 15
// 10
// 6
// 3
// 1

static pthread_mutex_t bsem;
static pthread_cond_t waitTurn = PTHREAD_COND_INITIALIZER; 
static int turn;

void *printTriangularSequenceTerm(void *void_ptr)
{
    // Write the implementation of the printTriangularSequenceTerm function here
    pthread_mutex_lock(&bsem);
    int *i=(int*)void_ptr;
    
    while(*i !=turn){
        pthread_cond_wait(&waitTurn,&bsem);
    }

    int num=*i*(*i+1)/2;
    std::cout<<num<<std::endl;
    turn--;
    pthread_mutex_unlock(&bsem);


    pthread_mutex_lock(&bsem);
    pthread_cond_broadcast(&waitTurn);
    pthread_mutex_unlock(&bsem);

    return nullptr;
}
    

int main()
{
    int nterms;
    std::cin >> nterms;
    pthread_t *tid = new pthread_t[nterms];
    int *arg = new int[nterms];
    pthread_mutex_init(&bsem,nullptr);
    
    turn = nterms;// initialize the value that turn should begin at

    for(int i=0;i<nterms;i++)
    {
        arg[i] = i+1;// assign the digit for each child thread based on the question's specifications
        
        
        }
    
    for(int i=0;i<nterms;i++){
        if(pthread_create(&tid[i],NULL,printTriangularSequenceTerm,(void*)arg[i])){
            cerr<<"error creating thread"<<endl;
        }
    }
    for(int i=0;i<nterms;i++)
        pthread_join(tid[i],nullptr);
   
    if (arg != nullptr)
        delete [] arg; 
    if (tid != nullptr)
        delete [] tid;
    return 0;
}