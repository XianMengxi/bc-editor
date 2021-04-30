#include"search.h"
#include"define.h"
#include"menu.h"
#include"function.h"
#include "high_li.h"
int complie(Hnode* hnode,Cursornode * cursornode, int flag,int flag_c,char ch1,char ch2)
{
	//search(hnode, cursornode, "main()", "\0", 1, color);
	//void search(Hnode * hnode, Cursornode * cursornode, char* str1, char* str2, int flag, int color);
	Node* node;
	//Hnode *hnode_b;
	//hnode_b = hnode;//记录当前位置

	int i = 0;
	int j = 0;
	switch (flag)
	{
	case 0:
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
				//cprintf("（）数量不等");
			{
				drawmain();
				window(2, 3, 79, 24);
				textbackground(BLUE);
				cprintf("The number of %c and %c does not match\n",ch1,ch2);
				cprintf("enter y to continue");
				while (getch() != 'y')
				{
					;
				}
			}
			drawmain();
			//printlist(hnode_b);
		}
		else if (flag_c == 1)
		{
			if (i != j)
			{
				return 1;//画的部分和点击确定的部分在外边完成
			}
		}
		return 0;


	case 3:
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
				cprintf("The number of   %c  and  %c   does not match\n",ch1,ch2);
				cprintf("enter y to continue");
				while (getch() != 'y')
				{
					;
				}
			}
			drawmain();
			//printlist(hnode_b);
		}
		else if (flag_c == 1)
		{

		}

		return 0;


	case 5:
		if (high_li(hnode, cursornode, "main",flag_c) == 0)
		{
			if (flag_c == 0)
			{
				drawmain();
				window(2, 3, 79, 24);
				textbackground(BLUE);
				cprintf("Don't find \'main\'\n");
				cprintf("enter y to continue");
				while (getch() != 'y')
				{
					;
				}
				drawmain();
				//printlist(hnode_b);
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
