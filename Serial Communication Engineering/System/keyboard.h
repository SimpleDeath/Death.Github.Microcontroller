#ifndef _keyboard_h_
#define _keyboard_h_

#include <reg52.h>

#define uint unsigned int
#define uchar unsigned char

//行选
uchar rowSelection();
//列选
uchar columnSelection();
//键盘扫描
void scan();

#endif