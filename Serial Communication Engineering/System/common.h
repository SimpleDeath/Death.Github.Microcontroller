#ifndef _common_h_
#define _common_h_
	
#include <reg52.h>

#define uint unsigned int
#define uchar unsigned char
	
//串口通信数据接收合并，调用 compare() 方法
void merge();	
//比较合并字符，改变 P1 状态（取反、流水灯）
void compare();	
//判断流水灯状态并按相应方式运行（暂停、左移、右移、闪烁）
void stateMachine(uchar IN);

#endif