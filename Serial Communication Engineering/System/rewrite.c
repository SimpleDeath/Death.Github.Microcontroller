#include "rewrite.h"
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

//重写 putchar 方法，实现 printf 函数调用
char putchar(char c) {

	uartSend(c);
	return c;

}