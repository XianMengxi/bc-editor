#include"search.h"
#include"function.h"
#include"menu.h"
void readhnode(Hnode *hnode, char str[])
{
	Node *node;
	int i = 0;
	memset(str, '\0', sizeof(str));
	node = hnode->head;
	while (node != NULL)
	{
		str[i] = node->chr;
		i++;
		node = node->next;
	}
	str[i] = '\0';
}
//flags=1:查找 flags=2:替换,str1为搜索的字符串
//color为将搜索得到的字符变为的颜色或类型
void search(Hnode *hnode,Cursornode *cursornode,char str_search[],char str_replace[],int flags, int color)
{
	char str_[128];
	char *str;
	char *p;
	char *p1;  //p1为指向str的指针
	char *p2;  //p,p2为个搜索需要用到的指针
	int k,i;
	Cursornode cursornode_temp = *cursornode;
	cursornode->nowhnode = hnode;
	while (cursornode->nowhnode != NULL)
	{
		cursornode->nownode = cursornode->nowhnode->head;
		if (cursornode->nowhnode->cols >= 128)
		{
			str = (char*)malloc(sizeof(cursornode->nowhnode->cols));
		}
		else
		{
			str = str_;
		}
		readhnode(cursornode->nowhnode, str);
		p2 = str;
		while ((p = strstr(p2 , str_search)) != NULL)
		{
			p1 = str_replace;
			k = p - p2;
			for (i = 0; i < k && cursornode->nownode != NULL; i++)
			{
				cursornode->nownode = cursornode->nownode->next;
			}
			if (flags == 1)
			{
				for (i = 0; i < strlen(str_search); i++)
				{
					p++;
					//显示搜索得到的字符
					cursornode->nownode->bkflag = 2;
					cursornode->nownode = cursornode->nownode->next;
				}
			}
			if (flags == 2)
			{
				for (i = 0; i < strlen(str_search)-1; i++)
				{
					p++;
					cursornode->nownode = cursornode->nownode->next;
				}
				p++;
				for (i = 0; i < strlen(str_search); i++)
				{
					DeleteNode(hnode, cursornode);
				}
				for (i = 0; i < strlen(str_replace); i++,p1++)
				{
					AddNode(cursornode, *p1);
					cursornode->nownode->bkflag=2;
				}
				cursornode->nownode = cursornode->nownode->next;
			}
			p2 = p;
		}
		cursornode->nowhnode = cursornode->nowhnode->next;
	}
	*cursornode = cursornode_temp;
}
void Search(Hnode *hnode,Cursornode *cursornode)
{
	char str_search[128];
	memset(str_search, '\0', 128);
	char str_replace[2] = "\0";
	clrscr();
	drawmain();
	window(2, 3, 24, 79);
	textbackground(BLUE);
	cprintf("please enter the string you want to search");
	gets(str_search);
	search(hnode, cursornode, str_search,str_replace , 1 , 5);
	clrscr();
	drawmain();
}
void Replace(Hnode *hnode ,Cursornode *cursornode)
{
	char str_search[128];
	char str_replace[128];
	memset(str_replace,'\0',128);
	memset(str_search, '\0', 128);
	clrscr();
	drawmain();
	window(2, 3, 79, 24);
	textbackground(BLUE);
	cprintf("please enter the string you want to replace\r\n");
	gets(str_search);
	window(2,3,79,24);
	clrscr();
	cprintf("please enter the new string\r\n");
	gets(str_replace);
	search(hnode, cursornode, str_search, str_replace, 2 , 4);
	clrscr();
	drawmain();
}