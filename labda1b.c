#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(int argc, char** argv){
int i,tid,a,b,c;
#pragma omp parallel
{
printf("Hello World from thread = %d\n",omp_get_thread_num());
}

double start_time,end_time,time;
start_time = omp_get_wtime();
i = omp_get_num_procs();
printf("The total number of processor is: %d\n",i); // number of processors

#pragma omp parallel
{
a = omp_get_max_threads(); //Maximum thread number
b = omp_get_num_threads();//Number of threads
}
printf("The total number of \n Maximum threads: %d \n Number of threads: %d\n",a,b);
#pragma omp parallel
{
tid = omp_get_thread_num();
printf("The thread number is: %d\n",tid); //Fetch the thread number
}

omp_set_num_threads(8); //Set the number of thread
#pragma omp parallel
{
c=omp_get_num_threads();
}
printf("Total number of threads present is: %d\n",c);
//To get the time for the given computation
end_time=omp_get_wtime();
time=end_time-start_time;
printf("Total time taken for computation is: %f\n",time);
}
