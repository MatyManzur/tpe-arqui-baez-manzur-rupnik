#include <time.h>

static unsigned long ticks = 0;
static struct timezone_t timezone={0 , 0};
static int monthdays[2][12]={{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
int isLeapYear(int year);
void timer_handler() 
{
	ticks++;
	followingTask();
}

unsigned long ticks_elapsed() {
	return ticks;
}

unsigned long seconds_elapsed() {
	return ticks / 18;
}

void getCurrentDateTime(struct datetime_t* datetime, struct timezone_t* tzone){///Falta testing
	tzone->hours=timezone.hours;
	tzone->minutes=timezone.minutes;
	int8_t h=getHours()+timezone.hours;
	int8_t m=getMinutes()+timezone.minutes;
	int8_t day=getDay();
	int8_t month=getMonth();
	uint16_t year=getYear()+getCentury()*100;
	if(m<0){
		h-=1;
	}
	if(h<0){
		if(day==1){
			month-=1;
			if(month==0){
				year-=1;
				month=12;
			}
			day=monthdays[isLeapYear(year)][month-1]; 
	}else{
		day-=1;
	}
	
	}
	h%=24;
	m%=60;
	uint8_t s=getSeconds();
	datetime->hours=h;
	datetime->mins=m;
	datetime->segs=s;


	
	datetime->day=day;
	datetime->month=month;
	datetime->year=year;

}
void setTimeZone(const struct timezone_t * tzone){//Falta testing
	timezone.hours=tzone->hours;
	timezone.minutes=tzone->minutes;
}

int isLeapYear(int year){
if(year%400==0){
return 1;
}else if(year%4==0 && year%100!=0){
return 1;
}
return 0;
}

void sleep(uint64_t miliseconds) //minimo 55 miliseconds para que espere algo
{
    	uint64_t finish = ticks + miliseconds/55;
	while(ticks < finish)
	{
		_hlt();
	}
}
