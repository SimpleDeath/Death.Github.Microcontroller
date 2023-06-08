/*
 *项目名称：Serial Communication Engineering（串口通信工程）
 *项目意义：实现用串口控制管脚
 *作者：Death
 *创建日期：2023/5/22 8:11
 *创建路径：D:\User Software\Engineering Projects\Microcontroller - All\Serial Communication Engineering\Main\main.c
 */
 
#include "common.h"
#include "interrupt.h"
#include "uart.h"
#include "display.h"
#include "keyboard.h"


//全局变量声明
extern uchar receive, send;
extern uchar receiveArr[];
extern uint temp;
extern uchar keyValue, preKeyValue;
extern uchar code displayArr[];
extern uchar state;
extern uchar i;
extern uchar x1, x2;

void main() {

	uartInit();						//串口通信初始化
	timerInit();					//中断初始化
	P3 = 0xff;						//管脚初始化
	while(1) {
	
		display(receive, 16);		//数码管显示
		scan();						//键盘扫描
		stateMachine(state);		//判断流水灯状态并按相应方式运行（暂停、左移、右移、闪烁）
	
	}
	
}