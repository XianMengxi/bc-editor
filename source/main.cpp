#include"key.h"
#include"menu.h"
#include"mouse.h"
#include"mainloop.h"
/*
 *@name:main
 *@msg:������
 *@param:{void}
 *@return:{int} 0
*/
int main()
{
	textmode(C80);
	initmouse(0);//��ʼ�����
	setmouserange(0,0,639,479);//�趨����ƶ���Χ
	drawmain();
	mainloop();
	
	return 0;
}
