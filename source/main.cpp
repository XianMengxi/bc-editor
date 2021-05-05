#include"key.h"
#include"menu.h"
#include"mouse.h"
#include"mainloop.h"
/*
 *@name:main
 *@msg:主函数
 *@param:{void}
 *@return:{int} 0
*/
int main()
{
	textmode(C80);
	initmouse(0);//初始化鼠标
	setmouserange(0,0,639,479);//设定鼠标移动范围
	drawmain();
	mainloop();
	
	return 0;
}
