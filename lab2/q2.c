#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ---------- Standard Merge Sort ---------- */

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for(int i=0;i<n1;i++)
        L[i]=arr[l+i];
    for(int i=0;i<n2;i++)
        R[i]=arr[m+1+i];

    int i=0,j=0,k=l;

    while(i<n1 && j<n2)
    {
        if(L[i]<=R[j])
            arr[k++]=L[i++];
        else
            arr[k++]=R[j++];
    }

    while(i<n1)
        arr[k++]=L[i++];

    while(j<n2)
        arr[k++]=R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r)
{
    if(l<r)
    {
        int m=(l+r)/2;
        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);
        merge(arr,l,m,r);
    }
}

/* ---------- Three-Way Merge ---------- */

void merge3(int arr[], int low, int mid1, int mid2, int high)
{
    int n = high-low+1;
    int *temp = (int*)malloc(n*sizeof(int));

    int i=low;
    int j=mid1+1;
    int k=mid2+1;
    int t=0;

    while(i<=mid1 && j<=mid2 && k<=high)
    {
        if(arr[i]<=arr[j] && arr[i]<=arr[k])
            temp[t++]=arr[i++];
        else if(arr[j]<=arr[i] && arr[j]<=arr[k])
            temp[t++]=arr[j++];
        else
            temp[t++]=arr[k++];
    }

    while(i<=mid1 && j<=mid2)
        temp[t++]=(arr[i]<=arr[j])?arr[i++]:arr[j++];

    while(j<=mid2 && k<=high)
        temp[t++]=(arr[j]<=arr[k])?arr[j++]:arr[k++];

    while(i<=mid1 && k<=high)
        temp[t++]=(arr[i]<=arr[k])?arr[i++]:arr[k++];

    while(i<=mid1)
        temp[t++]=arr[i++];

    while(j<=mid2)
        temp[t++]=arr[j++];

    while(k<=high)
        temp[t++]=arr[k++];

    for(i=0;i<n;i++)
        arr[low+i]=temp[i];

    free(temp);
}

void mergeSort3(int arr[], int low, int high)
{
    if(low>=high)
        return;

    int third=(high-low)/3;
    int mid1=low+third;
    int mid2=low+2*third+1;

    if(mid2>high)
        mid2=high;

    mergeSort3(arr,low,mid1);
    mergeSort3(arr,mid1+1,mid2);
    mergeSort3(arr,mid2+1,high);

    merge3(arr,low,mid1,mid2,high);
}

/* ---------- Utility ---------- */

void generate(int arr[], int n)
{
    for(int i=0;i<n;i++)
        arr[i]=rand();
}

int main()
{
    srand(time(NULL));

    printf("Size\tMerge(ms)\t3-Way(ms)\n");

    for(int n=1000;n<=64000;n*=2)
    {
        int *a=(int*)malloc(n*sizeof(int));
        int *b=(int*)malloc(n*sizeof(int));

        generate(a,n);

        for(int i=0;i<n;i++)
            b[i]=a[i];

        clock_t start,end;

        start=clock();
        mergeSort(a,0,n-1);
        end=clock();
        double t1=(double)(end-start)*1000/CLOCKS_PER_SEC;

        start=clock();
        mergeSort3(b,0,n-1);
        end=clock();
        double t2=(double)(end-start)*1000/CLOCKS_PER_SEC;

        printf("%d\t%.3f\t\t%.3f\n",n,t1,t2);

        free(a);
        free(b);
    }

    return 0;
}