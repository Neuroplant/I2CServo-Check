/**********************************************************************

**********************************************************************/
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPiI2C.h>
#include <pca9685.h>

#define OFFSET_MS 0     
#define SERVO_MIN_MS 5+OFFSET_MS        
#define SERVO_MAX_MS 30+OFFSET_MS       

#define devId0	0x40
#define devId1	0x41
#define PIN_BASE0 64
#define PIN_BASE1 81
#define MAX_PWM 4096
#define HERTZ 50

struct s_Servo {
	int min;
	int max;
};
struct s_Servo Servo[34];

char key;

long map(long value,long fromLow,long fromHigh,long toLow,long toHigh){
    return (toHigh-toLow)*(value-fromLow) / (fromHigh-fromLow) + toLow;
}

void servoInit(int pin){        //initialization function for servo PMW pin
	pinMode(pin+PINBASE0,OUTPUT);
	Servo[pin].min=10;
	Servo[pin].max=10;
	servoWriteMS(pin+PINBASE0,10);	
}

void servoWriteMS(int pin, int ms){     //specific the unit for pulse(5-25ms) with specific duration output by servo pin: 0.1ms
	if(ms > SERVO_MAX_MS) {
		printf("Pin: %i ms: %i too big\n",pin,ms);
		ms = SERVO_MAX_MS;
	}
	if(ms < SERVO_MIN_MS) {
		printf("Pin: %i ms: %i too small\n",pin,ms);
		ms = SERVO_MIN_MS;
	};
	pwmWrite(pin,map(ms,0,200,0,PWM_MAX));
	delay(10);
	printf("Pin: %i ms: %i \n",pin,ms);
}


int main (int argc, char *argv[]) {
	int i;
	if(wiringPiSetup() == -1){ //when initialize wiring faiservo,print messageto screen
		printf("setup wiringPi faiservo !");
        return 1; 
    }
	if(wiringPiI2CSetup(devId0) == -1){ 
       		printf("setup wiringPi I2C faiservo !");
       	return 1; 
	};
	
	int fd0 = pca9685Setup(PIN_BASE0, devId0, HERTZ);
	if (fd0 < 0)	{
		printf("Error in setup\n");
		return fd0;
	}
	pca9685PWMReset(fd0);
	if(wiringPiI2CSetup(devId1) == -1){ 
       		printf("setup wiringPi I2C faiservo !");
       	return 1; 
	};
	
	int fd1 = pca9685Setup(PIN_BASE1, devId1, HERTZ);
	if (fd1 < 0)	{
		printf("Error in setup\n");
		return fd10;
	}
	pca9685PWMReset(fd1);
	
	for (i=0;i<16;i++) {
		printf("Testing Servo Nr. %i an Modul %h\n",i,devID0);
		servoInit(i);
		printf("Setze MIN Value (+/-/x)");
		while (key != 120) {		
			key=getchar();
			if (key==34) {
				Servo[i].min++;
			}
			if (key==45) {
				Servo[i].min--;
			}
			printf("Servo %i min:/i\n",i,Servo[i].min);
		}
		printf("Setze MAX Value (+/-/x)");
		while (key != 120) {
			key=getchar();
			if (key==34) {
				Servo[i].max++;
			}
			if (key==45) {
				Servo[i].max--
			}
			ServoWriteMS(i+PIN_BASE0,Servo[i].min);
			printf("Servo %i max:/i\n",i,Servo[i].min);
		}
		servoWriteMS(i+PIN_BASE0,(Servo[i].min+Servo[i].max)/2);

	}
	for (i=17;i<33;i++) {
		printf("Testing Servo Nr. %i an Modul %h\n",i-17,devID1);
		servoInit(i);
		printf("Setze MIN Value (+/-/x)");
		while (key != 120) {		
			key=getchar();
			if (key==34) {
				Servo[i].min++;
				servoWriteMS(i+PIN_BASE1,Servo[i].min);
				printf("Servo %i min:/i\n",i,Servo[i].min);
			}
			if (key==45) {
				Servo[i].min--
				servoWriteMS(i+PIN_BASE1,Servo[i].min);
				printf("Servo %i min:/i\n",i,Servo[i].min);
			}
		}
		printf("Setze MAX Value (+/-/x)");
		while (key != 120) {
			key=getchar();
			if (key==34) {
				Servo[i].max++;
			}
			if (key==45) {
				Servo[i].max--
			}
			ServoWriteMS(i+PIN_BASE0,Servo[i].min);
			printf("Servo %i min:/i\n",i,Servo[i].min);
		}
		servoWriteMS(i+PIN_BASE0,(Servo[i].min+Servo[i].max)/2);
	}
	printf("\n\nDatenerfassung beendet\n");
	for (i=0;1<=33;i++) {
		printf("Servo Nr. %i min :%i, max:%i \n",i,Servo[i].min,Servo[i].max);
	}
    return 0;
}