 #include<stdio.h>
#include<omp.h>
void f1(int,int);
void f2(int,int);
void main(void)
{
    int tid;
    int x,y;
    x=12;
    y=5;
    #pragma omp parallel shared(x,y) private(tid)
    {
    tid=omp_get_thread_num();

    if(tid==0)
    {
       f1(x,y);

    }
    else if(tid==1)
    {
        f2(x,y);
    }
    }

}
void f1(int a1,int a2)
{

    int sum;
    sum=a1+a2;
    printf("sum is %d\t\n",sum);
}
void f2(int b1,int b2)
{

    int diff;
    diff=b1-b2;
    printf("Difference is %d\t\n",diff);
}
