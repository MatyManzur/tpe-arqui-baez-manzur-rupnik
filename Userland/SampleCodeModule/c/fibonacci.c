#include <fibonacci.h>

uint64_t printNewValue(uint64_t value1, uint64_t value2,uint8_t counter, char str[]);
void printFirstThree(); // las hacemos aparta para que queden lindas

void fibonacci(uint8_t argc, void ** argv){
    uint64_t first=FIRST;
    uint64_t second=SECOND;
    uint64_t third;
    char str[20]={0};
    uint8_t numSerie = 3;
    first=1;
    printFirstThree();
    //hay que hacerlo con un pequeÃ±o sleep lol
    while(1){
        third=printNewValue(first,second,numSerie,str);
        first=second;
        second=third;
        numSerie++;
        sys_sleep(9);
    }
}

uint64_t printNewValue(uint64_t value1, uint64_t value2, uint8_t counter, char str[]){
    uint64_t value3 = value1 + value2;
    ulongToStr(value3,str);
    printString(str);
    ulongToStr(counter,str);
    putChar(' ');
    printString(str);
    printString("th");
    sys_new_line(BLACK);
    return value3;
}

void printFirstThree(){
    printString("0 1st");
    sys_new_line(BLACK);
    printString("1 2nd");
    sys_new_line(BLACK);
    printString("1 3rd");
    sys_new_line(BLACK);
}
