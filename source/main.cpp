#include"key.h"
#include"menu.h"
#include"mouse.h"
int main()
{
	initmouse(0);//初始化鼠标
	setmouserange(0,0,639,479);//设定鼠标移动范围
	drawmain();
	mainloop();
	
	return 0;
}
