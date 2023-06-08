#ifndef _uart_h_
#define _uart_h_

#include <reg52.h>

#define uint unsigned int
#define uchar unsigned char

//串口通信发送数据
void uartSend(uchar IN);
//串口通信初始化
void uartInit();
//中断初始化

#endif