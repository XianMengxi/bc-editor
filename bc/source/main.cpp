/*
 * @Descripttion: 
 * @version: 
 * @Author: Eugene
 * @Date: 2021-04-28 12:18:50
 * @LastEditors: Andy
 * @LastEditTime: 2021-04-29 20:10:46
 */
#include "key.h"
#include "menu.h"
#include "mouse.h"
int main()
{
	initmouse(0);
	setmouserange(0, 0, 639, 479);
	drawmain();
	mainloop();
	return 0;
}
