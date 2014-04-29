#include <pth.h>
#include <stdio.h>
#include <sys/time.h>

pth_uctx_t u_main;
pth_uctx_t u_test;
char stack[16*1024];

void test(void *);

const int LOOP = 1000*1000;

void test(void* arg)
{
    for(int i=0; i<LOOP; i++)
    {
        pth_uctx_switch(u_test, u_main);
    }
}

void main()
{

    pth_uctx_create(&u_main);
    pth_uctx_create(&u_test);
    pth_uctx_make(u_test, stack, sizeof(stack), NULL, test, NULL, NULL);

    struct timeval begin, end;

    gettimeofday(&begin, NULL);

    for(int i=0; i<LOOP; i++) 
    {
        pth_uctx_switch(u_main, u_test);
    }
    gettimeofday(&end, NULL);

    printf("total time = %d\n", (end.tv_sec-begin.tv_sec)*1000*1000 + (end.tv_usec-begin.tv_usec));
}

