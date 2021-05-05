#include"compile.h"
/*
 *@name:complie
 *@msg:完成部分的编译功能
 *@param:{Hnode *}hnode 链表头
 *@param:{Cursornode *}cursornode 光标位置
 *@param:{int}flag 表示编译类型
 *@param:{int}flag_c 表示图形界面还是控制台
 *@param:{char}ch1编译用字符
 *@param:{char}ch2
 *@return:{int}传回编译结果 即是否发现错误
*/
int complie(Hnode* hnode,Cursornode * cursornode, int flag,int flag_c,char ch1,char ch2)
{
	Node* node;
	int i = 0;
	int j = 0;
	switch (flag)
	{
	case 0://检测几种匹配
		while (hnode != NULL)
		{
			node = hnode->head;
			while (node != NULL)
			{
				if (node->chr == ch1)
				{
					i++;
				}
				else if (node->chr == ch2)
				{
					j++;
				}
				node=node->next;
			}
			hnode = hnode->next;
		}
		if (flag_c == 0)//控制台窗口下
		{
			if (i != j)
			{
				drawmain();
				window(2, 3, 79, 24);
			
				textbackground(BLUE);
				textcolor(WHITE);
				cprintf("The number of %c and %c does not match\n",ch1,ch2);
				cprintf("enter y to continue");
				while (getch() != 'y')
				{
					;
				}
			}
			drawmain();
		}
		else if (flag_c == 1)
		{
			if (i != j)
			{
				return 1;//画的部分和点击确定的部分在外边完成
			}
		}
		return 0;


	case 3://检测另几种匹配
		while (hnode != NULL)
		{
			node = hnode->head;
			while (node != NULL)
			{
				if (node->chr == ch1)
				{
					i++;
				}
				node = node->next;
			}
			hnode = hnode->next;
		}
		if (flag_c == 0)
		{
			if (i % 2 == 1)
			{
				drawmain();
				window(2, 3, 79, 24);
				textbackground(BLUE);
				textcolor(WHITE);
				cprintf("The number of   %c  and  %c   does not match\n",ch1,ch2);
				cprintf("enter y to continue");
				while (getch() != 'y')
				{
					;
				}
			}
			drawmain();
		}
		else if (flag_c == 1)
		{
			if (i%2==1)
			{
				return 1;//画的部分和点击确定的部分在外边完成
			}
		}
		return 0;
	case 5://检测有无main函数
		if (high_li(hnode, cursornode, "main",flag_c) == 0)
		{
			if (flag_c == 0)
			{
				drawmain();
				window(2, 3, 79, 24);
				textbackground(BLUE);
				textcolor(WHITE);
				cprintf("Don't find \'main\'\n");
				cprintf("enter y to continue");
				while (getch() != 'y')
				{
					;
				}
				drawmain();
			}
			else if (flag_c == 1)
			{
				return 1;
			}
		}
		return 0;
	}
	return 0;
}
