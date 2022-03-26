#include<stdio.h>
#include<omp.h>
#include <sys/time.h>
#define N 4
int addition(int size,int ARR1[size][size],int ARR2[size][size])
{
int sum[size][size];
printf("\nThe sum of the matrices is : \n");
for (int i=0;i< size;i++)
{
for (int j=0;j<size;j++)
{
sum[i][j] = ARR1[i][j] + ARR2[i][j];
printf("%d\t", sum[i][j]);
}
printf("\n");
}
}
int subtraction(int size, int ARR1[size][size], int ARR2[size][size])
{
int sub[size][size];
printf("\n:The subtraction of the matrices is : \n");
for (int i=0;i< size;i++)
{
for (int j=0;j<size;j++)
{
sub[i][j] = ARR1[i][j] - ARR2[i][j];
printf("%d\t", sub[i][j]);
}
printf("\n");
}
}
int multiplication(int size, int ARR1[size][size],int ARR2[size][size])
{
int mul[size][size];
printf("\nThe multiplication of the matrices is : \n");
for(int i=0;i<size;i++)
{
for(int j=0;j<size;j++)
{
mul[i][j]=0;
for(int k=0;k<size;k++)
{
mul[i][j]+=ARR1[i][k]*ARR2[k][j];
}
printf("%d\t",mul[i][j]);
}
printf("\n");
}
}
void RowColumnSum(int size, int M[size][size])
{
int rsum[size],csum[size];
printf("\nThe sum of the rows and columns of the first matrix is:\n\n");
for(int i=0;i<size;i++)
{
rsum[i]=0;
csum[i]=0;
for(int j=0;j<size;j++)
{
csum[i]=csum[i]+M[j][i];
rsum[i]=rsum[i]+M[i][j];
}
printf("Rows[%d]: %d\n",i+1,rsum[i]);
printf("Columns[%d]: %d\n",i+1,csum[i]);
}
}
void loweruppermatrix(int size, int M[size][size])
{
printf("\nThe lower triangular matrix is given by : ");
for(int i=0;i<size;i++)
{
printf("\n");
for(int j=0;j<size;j++){
if(i >= j)
printf("%d\t ", M[i][j]);
else{
printf("0\t");
}
}
}
printf("\n\nThe upper triangular matrix is given by : ");
for(int i=0;i<size;i++){
printf("\n");
for(int j=0;j<size;j++){
if(i > j){
printf("0\t");
}
else{
printf("%d\t ", M[i][j]);
}
}
}
}
void transpose(int size, int M[size][size])
{
int transpose[size][size];
for(int i=0;i<size;i++){
for(int j=0;j<size;j++){
transpose[j][i]=M[i][j];
}
}
printf("\nThe transpose of the matrix is given by : \n");
for(int i=0;i<size;i++){
for(int j=0;j<size;j++){
printf("%d\t",transpose[i][j]);
}
printf("\n");
}
}
int main()
{
int size=N;
int tid,thread;
struct timeval tv1, tv2;
struct timezone tz;
double stime;
int ARR1[size][size];
int ARR2[size][size];
#pragma omp parallel for schedule(dynamic)
for(int i=0;i<size;i++)
{
for(int j=0;j<size;j++)
{
ARR1[i][j]=i+1+(j+2)*2;
ARR2[i][j]=(i+j+1)*10/2;
}
}
printf("The first matrix is:\n");
for(int i=0;i<size;i++)
{
for(int j=0;j<size;j++)
{
printf("%d\t",ARR1[i][j]);
}
printf("\n");
}
printf("The second matrix is:\n");
for(int i=0;i<size;i++)
{
for(int j=0;j<size;j++)
{
printf("%d\t",ARR2[i][j]);
}
printf("\n");
}
//serial Computation
printf("\n\nThe Serial Execution is\n");
gettimeofday(&tv1, &tz);
addition(size,ARR1,ARR2);
subtraction(size,ARR1,ARR2);
multiplication(size,ARR1,ARR2);
RowColumnSum(size,ARR1);
loweruppermatrix(size,ARR1);
transpose(size,ARR1);
gettimeofday(&tv2, &tz);
stime = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
printf("\nThe time taken by serial execution is: %f seconds.\n", stime);

gettimeofday(&tv1, &tz);
omp_set_num_threads(thread);
printf("\n\nThe Parallel Execution\n");
#pragma omp parallel sections
{
#pragma omp section
{
tid=omp_get_thread_num();
printf("\nMatrix Addition using Thread Id: %d is: \n",tid);
addition(size,ARR1,ARR2);
}
#pragma omp section
{
tid=omp_get_thread_num();
printf("\nMatrix Subtraction using Thread Id: %d is: \n",tid);
subtraction(size,ARR1,ARR2);
}
#pragma omp section
{
tid=omp_get_thread_num();
printf("\nMatrix Multiplication using Thread Id: %d is:\n",tid);
multiplication(size,ARR1,ARR2);
}
#pragma omp section
{
tid=omp_get_thread_num();
printf("\Row sum & Column sum using Thread Id: %d is: \n",tid);
RowColumnSum(size,ARR1);
}
#pragma omp section
{
tid=omp_get_thread_num();
printf("\nLower & Upper Triangular using Thread Id: %d is: \n",tid);
loweruppermatrix(size,ARR1);
}
#pragma omp section
{
tid=omp_get_thread_num();
printf("\n\nMatrix Transpose using Thread Id: %d is: \n",tid);
transpose(size,ARR1);
}
}
gettimeofday(&tv2, &tz);
stime = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
printf("\nTime taken for parallel execution is: %f seconds.\n", stime/6);
return 0;
}
