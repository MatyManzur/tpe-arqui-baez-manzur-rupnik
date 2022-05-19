#include <time.h>

static unsigned long ticks = 0;
static struct timezone_t timezone={0,0};
void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void getCurrentDateTime(struct datetime_t* datetime,struct timezone_t* tzone){///Falta testing
	tzone->hours=timezone.hours;
	tzone->minutes=timezone.minutes;
	uint8_t h=getHours()+timezone.hours;
	h%=24;
	uint8_t m=getMinutes()+timezone.minutes;
	m%=60;
	uint8_t s=getSeconds();
	datetime->hours=h;
	datetime->mins=m;
	datetime->segs=s;


	uint8_t day=getDay();
	uint8_t month=getMonth();
	uint16_t year=getYear()+getCentury()*100;
	datetime->day=day;
	datetime->month=month;
	datetime->year=year;

}
void setTimeZone(const struct timezone_t * tzone){//Falta testing
	timezone.hours=tzone->hours;
	timezone.minutes=tzone->minutes;
}
