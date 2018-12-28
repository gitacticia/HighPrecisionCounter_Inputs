#include<sys/time.h>
#include<stdio.h>
#include<stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <omp.h>
#include <io.h>


#define INIT_TIMER() struct timeval  tv1, tv2;
#define TICK() gettimeofday(&tv1, NULL);
#define TOCK() gettimeofday(&tv2, NULL); printf ("%f;",(double) (tv2.tv_usec - tv1.tv_usec) / 1000000 +(double) (tv2.tv_sec - tv1.tv_sec));


int main (void){
    INIT_TIMER();
    const __UINT_FAST64_TYPE__ endloop = 10000000000;
    const __UINT_FAST64_TYPE__ test = 141592653589793;
    printf("512 BITS LONG UNSIGNED INT - STACK OF 4x64 __UINT_FAST64_TYPE__ - 10G - ALL CPU \n");
    static __UINT_FAST64_TYPE__ bfuint_4_64_t[4];
    srand(time(NULL));
    for (unsigned char i=0;i<4;i++){
       bfuint_4_64_t[i]=(__UINT_FAST64_TYPE__) rand() << 42 | (__UINT_FAST64_TYPE__) rand() << 24 |(__UINT_FAST64_TYPE__) rand() << 16|(__UINT_FAST64_TYPE__) rand() << 8;
    }
    for (unsigned char i=0;i<2;i++){
    TICK();
    //#pragma omp parallel for
    for (__UINT64_TYPE__ i = 0; i<endloop;i++){
        bfuint_4_64_t[0]++;
        if ( bfuint_4_64_t[0] == test){
        printf("%016" PRIx64 ":%016" PRIx64 ":%016" PRIx64 ":%016" PRIx64 " @ %" PRIu64"\n",bfuint_4_64_t[0],bfuint_4_64_t[1],bfuint_4_64_t[2],bfuint_4_64_t[3],i);
        }
    }
    //printf("%016" PRIx64 " %016" PRIx64 " %016" PRIx64 " %016" PRIx64"\n",bfuint_4_64_t[0],bfuint_4_64_t[1],bfuint_4_64_t[2],bfuint_4_64_t[3]);
    TOCK();
    }
    printf("\n");
    return 0;
}
