#include "common.h"
#include "interrupt.h"

#include <intrins.h>
#include <string.h>
	
//用于发送、接收串口通信数据
uchar receive = 0, send = 0;
uchar receiveArr[8];
//用于中断定时器轮询
uint temp = 1;
//用于矩阵扫描的高低电平切换
uchar keyValue = 0, preKeyValue = 0;
//用于数码管显示（0 ~ F）
uchar code displayArr[] = {

	0xc0, 0xf9, 0xa4, 0xb0,
	0x99, 0x92, 0x82, 0xf8,
	0x80, 0x90, 0x88, 0x83,
	0xc6, 0xa1, 0x86, 0x8e

};
//用于改变流水灯状态（状态机模式）
uchar state = 0;
//用于数组索引
uchar i = 0;
//用于灯状态取反（灯1、灯2）
uchar x1 = 1, x2 = 1;

//串口通信数据接收合并
void merge() {
		
	
	if(receive != '#' & receive != 0) {
	
		receiveArr[i++] = receive;
	
	} else {
	
		receiveArr[i] = '\0';
		i = 0;
		compare();
	
	}

}

//比较合并字符，改变 P1 状态（取反、流水灯）
//P1 = ((P1 & 0x04) ^ 0x04) | (P1 & 0xfb);
void compare() {

	if(strcmp(receiveArr, "Led0:OFF") == 0) {
	
		P1 &= 0xfb;
	
	} else if(strcmp(receiveArr, "Led0:ON") == 0){
		
		P1 = 0x04 | (P1 & 0xfb);
	
	}
	if(strcmp(receiveArr, "Led1:OFF") == 0) {

		P1 &= 0xf7;

	} else if(strcmp(receiveArr, "Led1:ON") == 0){
	
		P1 = 0x08 | (P1 & 0xf7);
	
	}
	
	if(strcmp(receiveArr, "left") == 0) {

		state = 1;

	}else if(strcmp(receiveArr, "right") == 0) {

		state = 2; 

	}else if(strcmp(receiveArr, "flashing") == 0) {

		state = 3;

	}else if(strcmp(receiveArr, "Time out") == 0) {

		state = 0;
		
	}

}

//判断流水灯状态并按相应方式运行（暂停、左移、右移、闪烁）
void stateMachine(uchar IN) {

	if(temp % 500 == 0) {
		
		switch(IN) {
		
			case 0 : ; break;
			case 1 :
				switch(P1 & 0xf0) {
				
					case 0: case 0xf0: P1 = 0x10 | (P1 & 0x0f); break;
					case 0x10: P1 = 0x20 | (P1 & 0x0f); break;
					case 0x20: P1 = 0x40 | (P1 & 0x0f); break;
					case 0x40: P1 = 0x80 | (P1 & 0x0f); break;
					case 0x80: P1 = 0x10 | (P1 & 0x0f); break;
				
				};
			break;		
			case 2 :
				switch(P1 & 0xf0) {
				
					case 0: case 0xf0: P1 = 0x80 | (P1 & 0x0f); break;
					case 0x10: P1 = 0x80 | (P1 & 0x0f); break;
					case 0x20: P1 = 0x10 | (P1 & 0x0f); break;
					case 0x40: P1 = 0x20 | (P1 & 0x0f); break;
					case 0x80: P1 = 0x40 | (P1 & 0x0f); break;
				
				};
			break;
			case 3 :
				P1 = ((P1 & 0xf0) ^ 0xf0) | (P1 & 0x0f);
			break;
		
		}
		
	}

}