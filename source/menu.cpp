#include"menu.h"
#include"key.h"
#include"mouse.h"
#include"define.h"
#include"edit.h"
/*
 *@name:drawmain
 *@msg:画出控制台下主界面
 *@param:{void}
 *@return:{void}
*/
void drawmain()//画主界面
{
	int i;
	hide_mouse();
	window(1, 1, 80, 25);
	textbackground(BLUE);
	clrscr(); //画蓝色文本编辑区
	textcolor(WHITE); //设置蓝色文本编辑区的边框颜色

	for (i = 2; i < 24; i++) //画蓝色文本编辑区左边框
	{
		gotoxy(1, i + 1);
		cprintf("%c", 186);
	}
	for (i = 2; i < 24; i++)
	{
		gotoxy(80, i + 1);
		cprintf("%c", 186);
	}
	gotoxy(1, 2);//画蓝色文本编辑区上边框
	for (i = 0; i < 79; i++)
	{
		cprintf("%c", 205);
	}

	gotoxy(1, 24); //蓝色文本编辑区下边框
	for (i = 0; i < 79; i++)
		cprintf("%c", 205);

	gotoxy(1, 2); //画蓝色文本编辑区左上角边框
	cprintf("%c", 201);
	gotoxy(80, 2);
	cprintf("%c", 187);

	gotoxy(1, 24); //画蓝色文本编辑区左下角边框
	cprintf("%c", 200);
	gotoxy(80, 24);
	cprintf("%c", 188);

	textcolor(BLACK); //设置主菜单字体颜色
	textbackground(7);// 设置主菜单背景颜色

	gotoxy(1, 1); //画主菜单

	textcolor(RED);
	cprintf("R");
	textcolor(BLACK);
	cprintf("un");

	for (i = 0; i < 4; i++)
		cprintf(" ");//长度为7

	cprintf("[");
	textcolor(RED);
	cprintf("F");
	textcolor(BLACK);
	cprintf("ile(F1)]");//长度为10

	for (i = 0; i < 7; i++)//长度为7
		cprintf(" ");

	cprintf("[");
	textcolor(RED);
	cprintf("E");
	textcolor(BLACK);
	cprintf("dit(F2)]");//长度为10

	for (i = 0; i < 7; i++)//长度为7
		cprintf(" ");

	cprintf("[");
	textcolor(RED);
	cprintf("S");
	textcolor(BLACK);
	cprintf("ettings(F3)]");//长度为14

	for (i = 0; i < 6; i++)//长度为6
		cprintf(" ");
	cprintf("[");
	textcolor(RED);
	cprintf("P");
	textcolor(BLACK);
	cprintf("attern(F4)]");//长度为 13

	for (i = 0; i < 6; i++)//长度为6
		cprintf(" ");

	gotoxy(1, 25);//画行列计数
	insline();
	cprintf("     Row:   Col:");
	
	gotoxy(80, 25);
	show_mouse();
}
/*
 *@name:drawmenu
 *@msg:画出控制台下菜单
 *@param:{Hnode *}hnode链表头
 *@param:{Cursornode *}cursornode光标位置
 *@param:{Offset *}offset坐标偏移量
 *@param：{int}textflags当前链表中有无文本
 *@param:{int}op主循环中按下的按键扫描码
 *@return:{int}改变主循环中菜单控制变量，表示菜单位置移动
*/
int drawmenu(Hnode *hnode,Cursornode *cursornode ,Offset *offset,int textflags,int op)//画子菜单，之后要不要加存缓冲区看数据设计而定
//返回值为flag 决定上下键光条，改变主循环里的flag2，决定左右光条 
{
	drawmain();//清除之前画的子菜单，文本显示之后再说，再进行更改
	if(textflags!=0)
	Printlist(hnode,cursornode,offset);
	window(1, 1, 80, 25);
	hide_mouse();
	int i;
	char * f[] = {
	"ew",
	"pen",
	"ave",
	"ave as",
	"hange directory",
	"lose",
	"uit" };
	char *f1[] = {
		"N",
		"O",
		"S",
		"S",
		"C",
		"C",
		"Q"
	};
	char * e[] = {
	"opy",
	"ut",
	"aste",
	"earch",
	"eplace" };
	char * e1[] = {
	"C",
	"C",
	"P",
	"S",
	"R" };
	char * s[] = {
	"ont",
	"olor",
	"elp"};
	char * s1[] = {
	"F",
	"C",
	"H" };
	char * p[] = {
	"nglish/Edit",
	"hinese/order" };
	char * p1[] = {
	"E",
	"C" };
	char* co[] = {
		"olor_c",
		"olor_1",
		"olor_2",
		"olor_3",
		"olor_4"};
	char* co1[] = {
		"C",
		"C",
		"C",
		"C",
		"C"};
	char* hz[] = {
		"UIF",
		"AT",
		"OU",
		"IE",
		"HUF"};
	char* hz1[] = {
		"G",
		"K",
		"Y",
		"X",
		"S" };
	textbackground(0);//搞选中的光带黑背景 
	textcolor(15);//搞选中的光带白字体 
	
	
	show_mouse();
	
	switch (op)
	{
	case 1:
		hide_mouse();

		drawmenu(hnode,cursornode,offset,textflags,F3);
		window(1, 1, 80, 25);
		textcolor(BLACK); //设置子菜单字体颜色
		textbackground(7);// 设置子菜单背景颜色
		box(49, 3, 6, 6);

		textbackground(0);//搞选中的光带黑背景
		textcolor(15);//搞选中的光带白字体
		gotoxy(50, 4);
		cprintf("%s", hz1[0]);
		cprintf("%s", hz[0]);

		textcolor(BLACK); //设置子菜单字体颜色
		textbackground(7);// 设置子菜单背景颜色
		for (i = 4; i < 4+4; i++)
		{
			gotoxy(50, i+1);
			textcolor(RED);
			cprintf("%s", hz1[i - 3]);
			textcolor(BLACK);
			cprintf("%s", hz[i - 3]);
		}
		if (textflags != 0)
			Find_cursor(hnode, cursornode, offset);
		else
			gotoxy(80, 25);
		show_mouse();
		return 1;
	case 2:
		hide_mouse();

		//drawmenu(hnode, cursornode, offset, textflags, F3);
		window(1, 1, 80, 25);
		gotoxy(42, 1);
		cprintf("[Settings(F3)]");//加黑
		
		//box(49, 3, 6, 6);
		textcolor(BLACK); //设置子菜单字体颜色
		textbackground(7);// 设置子菜单背景颜色
		box(42, 2, 4, 6);

		textcolor(BLACK); //设置子菜单字体颜色
		textbackground(7);// 设置子菜单背景颜色
		for (i = 3; i < 6; i++)
		{
			gotoxy(43, i);
			
			textcolor(RED);
			cprintf("%s", s1[i - 3]);
			textcolor(BLACK);
			cprintf("%s", s[i - 3]);
		}


		textbackground(0);//搞选中的光带黑背景
		textcolor(15);//搞选中的光带白字体
		gotoxy(43, 4);
		cprintf("%s", s1[1]);
		cprintf("%s", s[1]);

		//以下为第三级菜单
		textcolor(BLACK); //设置子菜单字体颜色
		textbackground(7);// 设置子菜单背景颜色
		box(49, 4, 6, 8);
		
		textbackground(0);//搞选中的光带黑背景 
		textcolor(15);//搞选中的光带白字体 
		gotoxy(50, 5);
		cprintf("%s", co1[0]);
		cprintf("%s", co[0]);

		textcolor(BLACK); //设置子菜单字体颜色
		textbackground(7);// 设置子菜单背景颜色
		for (i = 4; i < 5+3; i++)
		{

			gotoxy(50, i+2);
			textcolor(RED);
			cprintf("%s", co1[i - 3]);
			textcolor(BLACK);
			cprintf("%s", co[i - 3]);
		}
		if(textflags!=0)
		Find_cursor(hnode, cursornode, offset);
		else
			gotoxy(80, 25);
		show_mouse();
		return 2;

	case F1:
		hide_mouse();
		gotoxy(8, 1);
		cprintf("[File(F1)]");//加黑

		textcolor(BLACK); //设置子菜单字体颜色,就是搞得和bc像一点罢了 
		textbackground(7);// 设置子菜单背景颜色
		box(8, 2, 8, 17);

		textbackground(0);//搞选中的光带黑背景 
		textcolor(15);//搞选中的光带白字体 
		gotoxy(9, 3);
		cprintf("%s", f1[0]);
		cprintf("%s", f[0]);

		textcolor(BLACK); //设置子菜单字体颜色,就是搞得和bc像一点罢了 
		textbackground(7);// 设置子菜单背景颜色
		for (i = 4; i < 10; i++)
		{
			gotoxy(9, i);
			textcolor(RED);
			cprintf("%s", f1[i - 3]);
			textcolor(BLACK);
			cprintf("%s", f[i - 3]);
		}
		if(textflags!=0)
		Find_cursor(hnode, cursornode, offset);
		else
			gotoxy(80, 25);
		show_mouse();
		return 140;
	case F2:
		hide_mouse();
		gotoxy(25, 1);
		cprintf("[Edit(F2)]");//加黑


		textcolor(BLACK); //设置子菜单字体颜色
		textbackground(7);// 设置子菜单背景颜色
		box(25, 2, 6, 8);

		textbackground(0);//搞选中的光带黑背景 
		textcolor(15);//搞选中的光带白字体 
		gotoxy(26, 3);
		cprintf("%s", e1[0]);
		cprintf("%s", e[0]);

		textcolor(BLACK); //设置子菜单字体颜色
		textbackground(7);// 设置子菜单背景颜色
		for (i = 4; i < 8; i++)
		{
			gotoxy(26, i);
			textcolor(RED);
			cprintf("%s", e1[i - 3]);
			textcolor(BLACK);
			cprintf("%s", e[i - 3]);
		}
		if(textflags!=0)
		Find_cursor(hnode, cursornode, offset);
		else
			gotoxy(80, 25);
		show_mouse();
		return 280;
	case F3:
		hide_mouse();
		gotoxy(42, 1);
		cprintf("[Settings(F3)]");//加黑


		textcolor(BLACK); //设置子菜单字体颜色
		textbackground(7);// 设置子菜单背景颜色
		box(42, 2, 4, 6);

		textbackground(0);//搞选中的光带黑背景 
		textcolor(15);//搞选中的光带白字体 
		gotoxy(43, 3);
		cprintf("%s", s1[0]);
		cprintf("%s", s[0]);

		textcolor(BLACK); //设置子菜单字体颜色
		textbackground(7);// 设置子菜单背景颜色
		for (i = 4; i < 6; i++)
		{
			gotoxy(43, i);
			textcolor(RED);
			cprintf("%s", s1[i - 3]);
			textcolor(BLACK);
			cprintf("%s", s[i - 3]);
		}
		if(textflags!=0)
		Find_cursor(hnode, cursornode, offset);
		else
			gotoxy(80, 25);
		show_mouse();
		return 420;
	case F4:
		hide_mouse();
		gotoxy(62, 1);
		cprintf("[pattern(F4)]");//加黑


		textcolor(BLACK); //设置子菜单字体颜色
		textbackground(7);// 设置子菜单背景颜色
		box(62, 2, 3, 14);

		textbackground(0);//搞选中的光带黑背景 
		textcolor(15);//搞选中的光带白字体 
		gotoxy(63, 3);
		cprintf("%s", p1[0]);
		cprintf("%s", p[0]);

		textcolor(BLACK); //设置子菜单字体颜色
		textbackground(7);// 设置子菜单背景颜色
		for (i = 4; i < 5; i++)
		{
			gotoxy(63, i);
			textcolor(RED);
			cprintf("%s", p1[i - 3]);
			textcolor(BLACK);
			cprintf("%s", p[i - 3]);
		}
		if(textflags!=0)
		{
			Find_cursor(hnode, cursornode, offset);
		}
		else
			gotoxy(80, 25);
		show_mouse();
		return 560;
	
	}
	return 0;
    
}
/*
 *@name:box
 *@msg:画出控制台下方框，以减少代码量
 *@param:{int}x左上角横坐标
 *@param:{int}y左上角纵坐标
 *@param:{int}h高度
 *@param;{int}w宽度
 *@return:{void}
*/
void box(int x, int y, int h, int w) //画下拉子菜单边框
{
	hide_mouse();
	int i, j;
	gotoxy(x, y);
	for (i = 0; i < h; i++)
	{
		gotoxy(x, y + i);
		for (j = 0; j < w; j++)
			cprintf(" ");
	}
	gotoxy(x, y);
	putch(169);
	for (i = x + 1; i < x + w; i++)
	{
		putch(0xc4);
	}
	putch(0xbf);
	for (i = y + 1; i < y + h; i++)
	{
		gotoxy(x, i);
		putch(0xb3);
		gotoxy(x + w, i);
		putch(0xb3);
	}
	gotoxy(x, y + h);
	putch(0xc0);
	for (i = x + 1; i < x + w; i++)
	{
		putch(0xc4);
	}
	putch(0xd9);
	gotoxy(80, 25);
	show_mouse();
}
/*
 *@name:menu_lr
 *@msg:通过响应按键值控制菜单左右移动
 *@param:{int}op按键扫描码
 *@param:{int}flag_2记录菜单位置的标志
 *@param:{Hnode *}hnode 链表头节点
 *@param:{int}textflags 当前链表中有无文本的标识
 *@param;{Cursornode *}光标位置
 *@param;{Offset *}坐标偏移量
 *@return:{int}flag_2纪录菜单位置的标识
*/
int menu_lr(int op, int flag2, int * pflag,Hnode *hnode,int textflags,Cursornode *cursornode,Offset *offset)//与menu_ud类似
{
	if (op == LEFT)
		flag2--;
	else if (op == RIGHT)
		flag2++;

	if (flag2 % 4 == 0)
		*pflag =drawmenu(hnode,cursornode,offset,textflags,F1);
	else if (flag2 % 4 == 1)
		*pflag =drawmenu(hnode,cursornode,offset,textflags,F2);
	else if (flag2 % 4 == 2)
		*pflag =drawmenu(hnode,cursornode,offset,textflags,F3);
	else if (flag2 % 4 == 3)
		*pflag =drawmenu(hnode,cursornode,offset,textflags,F4);
	return flag2;
}
/*
 *@name:menu_ud3
 *@msg:通过响应按键值控制第三级菜单上下移动
 *@param:{int}op按键扫描码
 *@param:{int}flag_3记录菜单位置的标志
 *@param:{int}flag3_1记录第三级菜单位置的标志
 *@param:{Hnode *}hnode 链表头节点
 *@param;{Cursornode *}光标位置
 *@param;{Offset *}坐标偏移量
 *@param:{int} textflags 是否打开文本的标志
 *@return:{int}flag3_1记录第三级菜单位置的标志
*/
int menu_ud3(int op,int flag3,int flag3_1,Hnode *hnode,Cursornode *cursornode,Offset *offset,int textflag)
{
	hide_mouse();
	
	char* c[] = {
		"olor_c",
		"olor_1",
		"olor_2",
		"olor_3",
		"olor_4" };
	char* c1[] = {
		"C",
		"C",
		"C",
		"C",
		"C" };
	char* s[] = {
		"UIF",
		"AT",
		"OU",
		"IE",
		"HUF" };
	char* s1[] = {
		"G",
		"K",
		"Y",
		"X",
		"S" };
	textcolor(BLACK); //设置子菜单字体颜色
	textbackground(7);// 设置子菜单背景颜色
	if(flag3==1)
	{
		gotoxy(50, flag3_1 % 5 + 4);//flag%5  原位置
		textcolor(RED);
		cprintf("%s", s1[flag3_1 % 5]);
		textcolor(BLACK);
		cprintf("%s", s[flag3_1 % 5]);

		if (op == DOWN)
			flag3_1++;
		else if (op == UP)
			flag3_1--;

		textbackground(0);//搞选中的光带黑背景
		textcolor(15);//搞选中的光带白字体
		gotoxy(50, flag3_1 % 5 + 4);//flag%5  改变之后的位置
		
		cprintf("%s", s1[flag3_1 % 5]);
		cprintf("%s", s[flag3_1 % 5]);
	}

	else if(flag3==2)
	{
		gotoxy(50, flag3_1 % 5 + 5);//flag%5  原位置
		textcolor(RED);
		cprintf("%s", c1[flag3_1 % 5]);
		textcolor(BLACK);
		cprintf("%s", c[flag3_1 % 5]);

		if (op == DOWN)
			flag3_1++;
		else if (op == UP)
			flag3_1--;

		textbackground(0);//搞选中的光带黑背景
		textcolor(15);//搞选中的光带白字体
		gotoxy(50, flag3_1 % 5 + 5);//flag%5  改变之后的位置
	
		cprintf("%s", c1[flag3_1 % 5]);
		cprintf("%s", c[flag3_1 % 5]);
	}
	show_mouse();
	if(textflag!=0)
	Find_cursor(hnode, cursornode, offset);
	else
		gotoxy(80, 25);
	return flag3_1;
}
/*
 *@name:menu_ud
 *@msg:通过上下按键控制菜单上下移动，画光带条
 *@param:{int}op主循环中按下的按键值
 *@param:{int}flag子菜单的子选项，表明要画子菜单的第几个
 *@return:{int}flag 表明移动完成后菜单位置，传回主循环
*/
int menu_ud(int op, int flag,Hnode *hnode,Cursornode *cursornode,Offset *offset,int textflag)//子菜单的子选项，从上往下0123...,flag增加相当于余数增加，对应DOWN
{
	hide_mouse();
	char * f[] = {
	"ew",
	"pen",
	"ave",
	"ave as",
	"hange directory",
	"lose",
	"uit" };
	char * f1[] = {
	"N",
	"O",
	"S",
	"S",
	"C",
	"C",
	"Q" };
	char * e[] = {
	"opy",
	"ut",
	"aste",
	"earch",
	"eplace" };
	char * e1[] = {
	"C",
	"C",
	"P",
	"S",
	"R" };
	char * s[] = {
	"ont",
	"olor",
	"elp"};
	char * s1[] = {
	"F",
	"C",
	"H" };
	char * p[] = {
	"nglish/Edit",
	"hinese/order" };
	char * p1[] = {
	"E",
	"C" };
	textcolor(BLACK); //设置子菜单字体颜色
	textbackground(7);// 设置子菜单背景颜色
	if (flag > 70 && flag < 210)//在file子菜单下
	{
		gotoxy(9, flag % 7 + 3);//flag%7  原位置
		textcolor(RED);
		cprintf("%s", f1[flag % 7]);
		textcolor(BLACK);
		cprintf("%s", f[flag % 7]);

		if (op == DOWN)
			flag++;
		else if (op == UP)
			flag--;

		textbackground(0);//搞选中的光带黑背景
		textcolor(15);//搞选中的光带白字体
		gotoxy(9, flag % 7 + 3);//flag%7  改变之后的位置
	
		cprintf("%s", f1[flag % 7]);
		cprintf("%s", f[flag % 7]);
	}
	else if (flag > 210 && flag < 350)//在edit子菜单下
	{
		gotoxy(26, flag % 5 + 3);//flag%5  原位置
		textcolor(RED);
		cprintf("%s", e1[flag % 5]);
		textcolor(BLACK);
		cprintf("%s", e[flag % 5]);

		if (op == DOWN)
			flag++;
		else if (op == UP)
			flag--;

		textbackground(0);//搞选中的光带黑背景
		textcolor(15);//搞选中的光带白字体
		gotoxy(26, flag % 5 + 3);//flag%5  改变之后的位置
		cprintf("%s", e1[flag % 5]);
		cprintf("%s", e[flag % 5]);

	}
	else if (flag > 350 && flag < 490)//在settings子菜单下
	{
		gotoxy(43, flag % 3 + 3);//flag%2  原位置
		textcolor(RED);
		cprintf("%s", s1[flag % 3]);
		textcolor(BLACK);
		cprintf("%s", s[flag % 3]);

		if (op == DOWN)
			flag++;
		else if (op == UP)
			flag--;

		textbackground(0);//搞选中的光带黑背景
		textcolor(15);//搞选中的光带白字体
		gotoxy(43, flag % 3 + 3);//flag%2 改变之后的位置
		cprintf("%s", s1[flag % 3]);
		cprintf("%s", s[flag % 3]);
	}
	else if (flag > 490)//在patterns子菜单下
	{
		gotoxy(63, flag % 2 + 3);//flag%2  原位置
		textcolor(RED);
		cprintf("%s", p1[flag % 2]);
		textcolor(BLACK);
		cprintf("%s", p[flag % 2]);

		if (op == DOWN)
			flag++;
		else if (op == UP)
			flag--;

		textbackground(0);//搞选中的光带黑背景
		textcolor(15);//搞选中的光带白字体
		gotoxy(63, flag % 2 + 3);//flag%2 改变之后的位置
		cprintf("%s", p1[flag % 2]);
		cprintf("%s", p[flag % 2]);
	}
	if(textflag!=0)
		Find_cursor(hnode, cursornode, offset);
	else
		gotoxy(80, 25);
	show_mouse();
	return flag;
}
/*
 *@name:menu_ud_m
 *@msg:通过鼠标完成子菜单上下的选择
 *@param:{int}flag记录选择后的子菜单
 *@param:{int}flag_t记录选择前的子菜单
 *@return:{int}flag_t记录选择后的子菜单传回主循环
*/
int menu_ud_m(int flag,int flag_t)
{
	hide_mouse();
	char * f[]={
	"New",
	"Open",
	"Save",
	"Save as",
	"Change directory",
	"Close",
	"Quit"};
	char * e[]={
	"Copy",
	"Cut",
	"Paste",
	"Search",
	"Replace"};
	char * s[]={
	"Font",
	"Color",
	"Help"};
	char * p[]={
	"English/Edit",
	"Chinese/order"};
	textcolor(BLACK); //设置子菜单字体颜色
	textbackground(7);// 设置子菜单背景颜色
	if(flag>70&&flag<210)//在file子菜单下
	{
		gotoxy(9,flag%7+3);//flag%7  原位置
		cprintf("%s",f[flag%7]);
				
				
		textbackground(0);//搞选中的光带黑背景
		textcolor(15);//搞选中的光带白字体
		gotoxy(9,flag_t%7+3);//flag_t%7  改变之后的位置
		cprintf("%s",f[flag_t%7]);
	}
	else if(flag>210&&flag<350)//在edit子菜单下
	{
		gotoxy(26,flag%5+3);//flag%5  原位置
		cprintf("%s",e[flag%5]);
		
		
		textbackground(0);//搞选中的光带黑背景
		textcolor(15);//搞选中的光带白字体
		gotoxy(26,flag_t%5+3);//flag_t%5  改变之后的位置
		cprintf("%s",e[flag_t%5]);
		
	}
	else if(flag>350&&flag<490)//在settings子菜单下
	{
		gotoxy(43,flag%2+3);//flag%2  原位置
		cprintf("%s",s[flag%2]);
		
		
		textbackground(0);//搞选中的光带黑背景
		textcolor(15);//搞选中的光带白字体
		gotoxy(43,flag_t%2+3);//flag_t%2 改变之后的位置
		cprintf("%s",s[flag_t%2]);
	}
	else if(flag>490)//在patterns子菜单下
	{
		gotoxy(63,flag%2+3);//flag%2  原位置
		cprintf("%s",p[flag%2]);
		
			
		textbackground(0);//搞选中的光带黑背景
		textcolor(15);//搞选中的光带白字体
		gotoxy(63,flag_t%2+3);//flag_t%2 改变之后的位置
		cprintf("%s",p[flag_t%2]);
	}
	
	gotoxy(80, 25);
	show_mouse();
	return flag_t;
} 

