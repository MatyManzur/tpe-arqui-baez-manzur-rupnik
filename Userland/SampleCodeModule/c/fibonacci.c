#include <fibonacci.h>



void fibonacci(uint8_t argc, void ** argv){
    uint64_t first=FIRST:
    uint64_t second=SECOND;
    uint64_t third;
    printString("0"); // imprime un 0101 sino lol
    printWithFormat("%d",SECOND);
    //hay que hacerlo con un pequeÃ±o sleep lol
    while(1){
        third = first + second;
        printWithFormat("%d%d",third/100000000,third%100000000);
        sys_new_line(BLACK);
        first=second;
        second=third;
        sys_sleep(500);
    }
}

/*
uint64_t first=0;
    uint64_t second=1;
    uint64_t third;
    printWithFormat("%u",first);
    printWithFormat("%u",second);
    
    //hay que hacerlo con un pequeÃ±o sleep lol
    while(1){
                thirdA=third/100000000;
        thirdB=third%100000000;
        if(thirdA!=0 && ((third/10000000)%10 == 0))
            thirdA*=10;
        third = first + second;
        printWithFormat("%u",third);
        sys_new_line(BLACK);
        first=second;
        second=third;
        sys_sleep(1000);
    }
*/
