#include <fibonacci.h>

uint64_t printNewValue(uint64_t value1, uint64_t value2,uint8_t counter, char str[],  char* terminations[]);

// imprime la serie de Fibonacci con un sleep de 3 ticks
void fibonacci(uint8_t argc, void ** argv)
{
    uint64_t first=FIRST;
    uint64_t second=SECOND;
    uint64_t third;
    char* terminations[] = {"st","nd","rd","th"};
    char str[20]={0};
    printStringColor("0 1st", BLACK, WHITE);   // imprime los primeros aparte
    sys_new_line(BLACK);
    printStringColor("1 2nd", BLACK, WHITE);
    sys_new_line(BLACK);
    uint8_t numSerie = 3;
    //hay que hacerlo con un pequeÃ±o sleep lol
    while(1){
        third=printNewValue(first,second,numSerie,str,terminations);
        first=second;
        second=third;
        numSerie++;
        sys_sleep(3);
    }
}

uint64_t printNewValue(uint64_t value1, uint64_t value2, uint8_t counter, char str[], char* terminations[])
{   // realiza la impresión
    uint64_t value3 = value1 + value2;
    ulongToStr(value3,str);
    printStringColor(str,BLACK,WHITE);
    ulongToStr(counter,str);
    putCharColor(' ',BLACK,WHITE);
    printStringColor(str,BLACK,WHITE);
    uint8_t termination = counter%10 -1;
    termination = (termination>=3)? 3:termination;
    printStringColor(terminations[termination],BLACK,WHITE);
    sys_new_line(BLACK);
    return value3;
}

