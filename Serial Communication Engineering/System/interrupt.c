#include "interrupt.h"
#include "uart.h"
#include "common.h"


#include <stdio.h>
#include <string.h>

//全局变量声明
extern uchar receive, send;
extern uchar receiveArr[];
extern uint temp;
extern uchar keyValue, preKeyValue;
extern uchar code displayArr[];
extern uchar state;
extern uchar i;
extern uchar x1, x2;

//中断初始化
void timerInit() {

	TMOD |= 0x01;
	TH0 = (65536 - 1000) / 256;
	TL0 = (65536 - 1000) % 256;
	EA = 1;
	ET0 = 1; TR0 = 1;
	EX0 = 1; IT0 = 1;

}

//外部中断 0
void timer0() interrupt 0 {
	
	switch(P3 ^ 0xff) {
	
		case 0x04:
			send = 0; printf("%c", send);
		break;
		case 0x14:
			send++; printf("%c", send);
		break;
		case 0x24:
			send--; printf("%c", send);
		break;
		case 0x44:
			x1 = !x1;
			printf(x1 ? "Led0:ON#" : "Led0:OFF#");
			
		break;
		case 0x84:
			x2 = !x2;
			printf(x2 ? "Led1:ON#" : "Led1:OFF#");
			
		break;
	
	}
	
}

//定时器 0
void timer1() interrupt 1 {
	
	TH0 = (65536 - 1000) / 256;
	TL0 = (65536 - 1000) % 256;
	if(temp++ >= 10000) temp = 0;
	
}

//外部中断 1
void timer2() interrupt 2 {
	
}

//定时器 1
void timer3() interrupt 3 {
	
}

//串口中断
void serial() interrupt 4 {

	if(RI) {
		
		RI = 0;
		receive = SBUF;
		merge();		
		
	}

}