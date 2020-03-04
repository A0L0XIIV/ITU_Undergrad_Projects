#include <stdio.h>

typedef struct
	{
		int hr;
		int min;
		int sec;
	} CLOCK;
	
void increment(CLOCK * clock);
void show (CLOCK * clock);

int main(){
	CLOCK clock = {14,38,56};
	int i;
	
	for(i=0;i<6;i++){
		increment(&clock);
		show(&clock);
	}
	return 0;
}

void increment(CLOCK * clock){
	(clock->sec)++;
	if(clock->sec == 60){
		clock->sec = 0;
		(clock->min)++;
		if(clock->min == 60){
			clock->min = 0;
			(clock->hr)++;
			if(clock->hr == 24){
				clock->hr = 0;
			}
		}
	}
	return;
}

void show(CLOCK * clock){
	printf("%02d:%02d:%02d\n",clock->hr,clock->min,clock->sec);
	return;
}
