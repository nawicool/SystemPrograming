#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


struct sum_runner_struct
{
    long long limit;
    long long answer;
};

//Thread function to generate sum of 0 to N
void *sum_runner(void* arg)
{
    long long i;
    struct sum_runner_struct *arg_struct = (struct sum_runner_struct *) arg;
    long long sum=0;

    for( i=0; i<=arg_struct->limit;i++){
    sum+=i;
}

    arg_struct->answer=sum;
    pthread_exit(0);

}
int main (int argc, char *argv[])

{

if(argc<2){

printf("Usage %s <num1 <num2>....<numN> \n",argv[0]);
exit(-1);
}

long long i;
int num_args=argc-1;

struct sum_runner_struct args[num_args];

//Thread ID
pthread_t tids[num_args];

for(i=0;i<num_args;i++){
args[i].limit =atoll(argv[i+1]);

//Create attributes
pthread_attr_t  attr;

// initialise
pthread_attr_init(&attr);
pthread_create(&tids[i],&attr,sum_runner,&args[i]);
}

//wait until thread is done
for(i=0;i<num_args;i++){
pthread_join(tids[i],NULL);

printf("\n sum is %lld \t \n",args[i].answer);
}

return 0;
}
