#include"key.h"
#include"menu.h"
#include"mouse.h"
int main()
{
	initmouse(0);//��ʼ�����
	setmouserange(0,0,639,479);//�趨����ƶ���Χ
	drawmain();
	mainloop();
	
	return 0;
}
