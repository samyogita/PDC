
#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
int solve(float data[],int n,float min,float max,int bins)
{
    int ans[200];
    int m = (int)max + 1;
    if(bins%m!=0)
    {
        printf("Invalid number of buckets.The number should be divisible by 5! Enter a new number\n");
        return 0;
    }
    int partition = bins/m;
    #pragma omp parallel for
    for (int i=0; i<n; i++)
    {
        if(data[i]<1.0)
        {
            float val = 1.0/partition;
            #pragma omp parallel for
            for(int j=0; j<partition; j++)
            {
                if(data[i]<=val)
                {
                    ans[j]++;
                }
                val += 1.0/partition;
            }
        }
        else
        {
            int idx = (int)(data[i]*partition);
            ans[idx]++;
        }
    }
    float x = 1.0/partition;
    float st = 0.0;
    #pragma omp parallel for ordered
    for(int i=0; i<bins; i++)
    {
        printf("Total number of float-point values from range %f and %f is: %d \n",st,st+x,ans[i]);
        st += x;
    }
    printf("%s%13s%17s\n","Given", "Histogram", "Values");
    st=0;
#pragma op parallel for ordered
    for(int i=0; i <bins; i++)
    {
        printf("%f to %f %d ",st,st+x, ans[i]);
        st=st+=x;
        for(int j = 0; j< ans[i]; j++)
            printf("*");
        printf("\n");
    }
}
int main()
{
    float data[250];
    int data_count;
    printf("Enter the total number of values: \n");
    scanf("%d",&data_count);
    srand((unsigned int)time(NULL));
    #pragma omp parallel for
    for (int i=0; i<data_count; i++)
        data[i] = (((float)rand()/(float)(RAND_MAX)) * 5.0);
    for (int i=0; i<data_count; i++)
        printf("%f\n",data[i]);
    int bins;
    printf("Enter the number of bins: \n");
    scanf("%d",&bins);
    float min = data[0];
    float max = data[0];
    #pragma omp parallal for
    for (int i=1; i<data_count; i++)
    {
        if(data[i]>max)
            max=data[i];
        if(data[i]<min)
            min=data[i];
    }
    int freq = solve(data,data_count,min,max,bins);
    return 0;
}
