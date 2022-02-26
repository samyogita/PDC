#include <stdio.h>
#include <omp.h>

long long fib(long long n)
{
        if (n < 2) {
                return 1;
        }
        return fib(n - 2) + fib(n - 1);
}

int main(int argc, char ** argv)
{
        long long n = 0;
        long long num;
        printf("Enter the number of Fibonacci terms you want to see: ");
        scanf("%lld",&num);

        omp_set_num_threads(omp_get_num_procs());

        #pragma omp parallel private(n)
        {
                #pragma omp for schedule(dynamic, 1)
                for (n = 0; n <= num; n++) {
                        printf("Fibonacci of (%lld) is: %lld\n", n, fib(n));
                }

        }
        return 0;
}
