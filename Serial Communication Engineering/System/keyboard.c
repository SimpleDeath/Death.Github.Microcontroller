#include "keyboard.h"
#include "interrupt.h"
#include "uart.h"

//全局变量声明
extern uchar receive, send;
extern uchar receiveArr[];
extern uint temp;
extern uchar keyValue, preKeyValue;
extern uchar code displayArr[];
extern uchar state;
extern uchar i;
extern uchar x1, x2;

//行选
uchar rowSelection() {
	
	uchar temp;
	P2 = 0x0f;
	
	switch(P2 ^ 0x0f) {
	
		case 0: temp = 4; break;
		case 0x01: temp = 0; break;
		case 0x02: temp = 1; break;
		case 0x04: temp = 2; break;
		case 0x08: temp = 3; break;
	
	}
	
	return temp;
	
}

//列选
uchar columnSelection() {

	uchar temp;
	P2 = 0xf0;
	
	switch(P2 ^ 0xf0) {
	
		case 0: temp = 4; break;
		case 0x10: temp = 0;break;
		case 0x20: temp = 1;break;
		case 0x40: temp = 2; break;
		case 0x80: temp = 3; break;
	
	}
	
	return temp;

}

//键盘扫描
void scan() {

	keyValue = rowSelection() * 4 + columnSelection();
	
	if(keyValue != 20 | preKeyValue != 20) {	
		
		if(keyValue == 20) {
				
			send = preKeyValue;
			uartSend(send);
			
		}
		
		preKeyValue = keyValue;
		
	}

}