#include <fibonacci.h>

void fibonacci(uint8_t argc, void ** argv){
    uint64_t first=FIRST;

    uint64_t second=SECOND;
    uint64_t third;
    char str[20]={0};
    printString("0"); // imprime un 0101 sino lol
    printString("1");
    //hay que hacerlo con un pequeÃ±o sleep lol
    while(1){
        third = first + second;
        ulongToStr(third,str);
        printString(str);
        sys_new_line(BLACK);
        first=second;
        second=third;
        sys_sleep(500);
    }
}
