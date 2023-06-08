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

//串口通信发送数据
void uartSend(uchar IN) {

	SBUF = IN;
	while(!TI);
	TI = 0;

}

//串口通信初始化
void uartInit() {

	TMOD |= 0x20;
	PCON = 0x80;
	SCON = 0x50;
	TH1 = 0xfa;
	TL1 = TH1;	
	EA = 1;
	ES = 1;
	ET1 = 0; TR1 = 1;	
	
}