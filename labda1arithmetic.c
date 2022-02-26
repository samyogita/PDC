#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(int argc, char** argv){
int x,y,tid,addition,subtraction,multiply,division,remainder;
double start_time,end_time,time;
x=70;
y=30;
start_time = omp_get_wtime();
omp_set_num_threads(5);
#pragma omp parallel shared(x,y) private(tid)
{
tid = omp_get_thread_num();
if (tid==0){
    addition=x+y;
    printf("\nThe addition of two numbers: %d from thread no: %d\n",addition,tid);
}
else if(tid==1) {
    multiply=x*y;
    printf("\nThe multiplication of two numbers: %d from thread no: %d\n",multiply,tid);
}
else if(tid==2) {
    subtraction=x-y;
    printf("\nThe subtraction of two numbers: %d from thread no: %d\n",subtraction,tid);
}
else if(tid==3) {
    division=x/y;
    printf("\nThe division of two numbers: %d from thread no: %d\n",division,tid);
}
else{
    remainder = x % y;
    printf("\nThe remainder of two numbers: %d from thread no: %d\n",remainder,tid);
}
}
end_time = omp_get_wtime();
time = end_time - start_time;
printf("Total time taken: %f\n",time);
}
