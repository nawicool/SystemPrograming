#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


//Thread function to generate sum of 0 to N
void *sum_runner(void* arg)
{
long long i;
long long  *limit_ptr= (long long*) arg;
long long limit=*limit_ptr;
free(arg);
long long sum=0;
for( i=0; i<limit;i++){
sum+=i;

}
// pass back data in dynamically allocated memory
long long *answer =malloc(sizeof(*answer));
*answer=sum;
pthread_exit(answer);

}




int main (int argc, char *argv[])
{

if(argc<2){

printf("Usage %s <num> \n",argv[0]);
exit(-1);
}
long long *limit=malloc(sizeof(*limit));
*limit =atoll(argv[1]);

//Thread ID
pthread_t tid;

//Create attributes
pthread_attr_t  attr;

// initialise
pthread_attr_init(&attr);

pthread_create(&tid,&attr,sum_runner,limit);

//wait until thread is done

long long *result;
pthread_join(tid,(void**)&result);

printf("sum is %lld\n",*result);
free(result);
}
