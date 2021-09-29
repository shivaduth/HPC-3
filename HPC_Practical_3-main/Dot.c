#include<omp.h>
#include<stdio.h>

int sort(int arr[], int n)
{
    int i, j;
    #pragma omp parallel private(j)
    #pragma omp for schedule(dynamic)
    for (i = 0; i < n-1; i++)
    {
        printf(" sort thread %d \n",omp_get_thread_num());
        for (j = 0; j < n-i-1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }

    }

}
int sort_des(int arr[], int n)
{
    int i,j;
    #pragma omp parallel private(j)
    #pragma omp for schedule(dynamic)
    for (i = 0; i < n; ++i)
    {
        printf(" sort_des thread %d \n",omp_get_thread_num());
        for (j = i + 1; j < n; ++j)
        {
            if (arr[i] < arr[j])
            {
                int a = arr[i];
                arr[i] = arr[j];
                arr[j] = a;
            }
        }
    }
}
int main()
{
//fill the code;
    int n=4;
    //scanf("%d",&n);
    int arr1[4]= {1,4,3,2}, arr2[4]= {1,3,2,4};
    int i;
 
    sort(arr1, n);
    sort_des(arr2, n);
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for(i = 0; i < n ; i++)
    {
        printf(" sum thread %d \n",omp_get_thread_num());
        sum = sum + (arr1[i] * arr2[i]);
    }
    printf("%d",sum);
    return 0;
}
