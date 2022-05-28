#include <fibonacci.h>

void fibonacci(uint8_t argc, void ** argv){
    uint64_t first=0;
    uint64_t second=1;
    uint64_t third;
    //hay que hacerlo con un pequeÃ±o sleep lol
    while(1){
        //sleep(1);
        third = first + second;
        printWithFormat("%d",third);
        sys_new_line(BLACK);
        first=second;
        second=third;
    }
}
