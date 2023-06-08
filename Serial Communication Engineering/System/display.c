#include "display.h"

//全局变量声明
extern uchar receive, send;
extern uchar receiveArr[];
extern uint temp;
extern uchar keyValue, preKeyValue;
extern uchar code displayArr[];
extern uchar state;
extern uchar i;
extern uchar x1, x2;

//数码管显示
void display(uchar IN, uchar BASE) {
		
	switch(temp % 16) {

		case 0: 
			P1 = 0x01 | (P1 & 0xfc);
			P0 = displayArr[IN / BASE];
		break;
		case 8: 
			P1 = 0x02 | (P1 & 0xfc);
			P0 = displayArr[IN % BASE];
		break;

	}

}