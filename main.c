#include <stdio.h>
#include <time.h>
#define MAX 20

typedef struct
{
    int s, e;
} Task;


void sort(Task t[], int n)
{
    Task temp;
    for(int i=0; i<n-1; i++)
        for(int j=0; j<n-1-i; j++)
            if(t[j].e > t[j+1].e)
            {
                temp=t[j];
                t[j]=t[j+1];
                t[j+1]=temp;
            }
}


int overlap(Task a, Task b)
{
    if(a.s < b.e && a.e > b.s)
        return 1;
    else
        return 0;
}

void brute(Task t[], int n, int i, Task cur[], int c, Task best[], int *bc)
{
    if(i==n)
    {
        if(c>*bc)
        {
            *bc=c;
            for(int k=0; k<c; k++)
                best[k]=cur[k];
        }
        return;
    }

    brute(t,n,i+1,cur,c,best,bc);

    int ok=1;
    for(int k=0; k<c; k++)
        if(overlap(cur[k],t[i]))
            ok=0;

    if(ok == 1)
    {
        cur[c]=t[i];
        brute(t,n,i+1,cur,c+1,best,bc);
    }
}

int main()
{
    Task t[MAX], temp[MAX], g[MAX], b[MAX], cur[MAX];
    int n, gc=0, bc=0;

    printf("Enter number of tasks: ");
    scanf("%d",&n);

    if(n<1 || n>MAX)
    {
        printf("Invalid n\n");
        return 0;
    }

    for(int i=0; i<n; i++)
    {
        printf("Task %d (start end): ",i+1);
        scanf("%d %d",&t[i].s,&t[i].e);

        if(t[i].s<0 || t[i].e<=t[i].s)
        {
            printf("Invalid task\n");
            return 0;
        }
        temp[i]=t[i];
    }


    clock_t g1=clock();

    sort(temp,n);
    g[gc++]=temp[0];
    int last=temp[0].e;

    for(int i=1; i<n; i++)
        if(temp[i].s>=last)
        {
            g[gc++]=temp[i];
            last=temp[i].e;
        }

    clock_t g2=clock();


    clock_t b1=clock();
    brute(t,n,0,cur,0,b,&bc);
    clock_t b2=clock();


    printf("\nGreedy:\n");
    for(int i=0; i<gc; i++)
        printf("(%d,%d)\n",g[i].s,g[i].e);
    printf("Total = %d\n",gc);

    printf("\nBrute:\n");
    for(int i=0; i<bc; i++)
        printf("(%d,%d)\n",b[i].s,b[i].e);
    printf("Total = %d\n",bc);

    printf("\nTime:\n");
    printf("Greedy = %.2f us\n",(double)(g2-g1)*1000000/CLOCKS_PER_SEC);
    printf("Brute  = %.2f us\n",(double)(b2-b1)*1000000/CLOCKS_PER_SEC);

    if(gc==bc) printf("Optimal \n");
    else printf("Error \n");

    return 0;
}

