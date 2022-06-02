#include <prime.h>

// imprime los números primos, con un sleep de 1 tick
void prime(uint8_t argc, void ** argv)
{
	uint64_t counter=3;
	printString("2");
	char str[20]={0};
	newLine();
	int isPrime;
	int stop;
	while(1){
		isPrime=1;
		stop=sqrt(counter);
		for(int i=3;i<stop;i+=2){
			if(counter%i==0){
				isPrime=0;
			}
		}
		if(isPrime){
			ulongToStr(counter,str);
			printString(str);
	    	newLine();
	    	sys_sleep(1);
		}
	counter+=2;
	
	}
}
