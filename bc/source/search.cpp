/*
 * @Descripttion: 查找替换等操作
 * @version: 1.0.0
 * @Author: Zhou
 * @Date: 2021-04-28 12:18:50
 * @LastEditors: Andy
 * @LastEditTime: 2021-04-29 19:54:33
 */

#include "search.h"
/**
 * @name: Readhnode
 * @msg: 读取一行数据进字符串中
 * @param {Hnode} *hnode 文本头节点
 * @param {char} str 传进接受数据的字符串
 * @return {void}
 */
void Readhnode(Hnode *hnode, char str[])
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
/**
 * @name: Find
 * @msg: 查找，替换
 * @param {Hnode} *hnode 文本头节点
 * @param {Cursornode} *cursornode 光标结构体
 * @param {char} str_search 搜索的字符串
 * @param {char} str_replace 替换的字符串
 * @param {int} flag flag==1:查找 flag==2:替换
 * @param {int} type 把搜索到的字符串变为该种type
 * @return {void}
 */
void Find(Hnode *hnode, Cursornode *cursornode, char str_search[], char str_replace[], int flag, int type)
{
	char str_[128];
	char *str; //str为处理的字符指针，默认不去动态开辟数组
	char *p;   //通过三个指针的移动达到遍历查找或者替换过程
	char *p1;
	char *p2;
	int k; //用k来记录两个移动指针的字节差
	Cursornode cursornode_temp = *cursornode;
	cursornode->nowhnode = hnode;
	while (cursornode->nowhnode != NULL)
	{
		cursornode->nownode = cursornode->nowhnode->head;
		//字符数超过默认
		if (cursornode->nowhnode->cols >= 128)
		{
			str = (char *)malloc(sizeof(cursornode->nowhnode->cols));
		}
		else
		{
			str = str_;
		}
		readhnode(cursornode->nowhnode, str);
		p2 = str;
		while ((p = strstr(p2, str_search)) != NULL)
		{
			p1 = str_replace;
			k = p - p2;
			for (int i = 0; i < k && cursornode->nownode != NULL; i++)
			{
				cursornode->nownode = cursornode->nownode->next;
			}
			if (flag == 1)
			{
				for (int i = 0; i < strlen(str_search); i++)
				{
					p++;
					cursornode->nownode->bkflag = type;
					cursornode->nownode = cursornode->nownode->next;
				}
			}
			if (flag == 2)
			{
				for (int i = 0; i < strlen(str_search) - 1; i++)
				{
					p++;
					cursornode->nownode = cursornode->nownode->next;
				}
				p++;
				for (int i = 0; i < strlen(str_search); i++)
				{
					DeleteNode(hnode, cursornode);
				}
				for (int i = 0; i < strlen(str_replace); i++, p1++)
				{
					AddNode(cursornode, *p1);
					cursornode->nownode->bkflag = type;
				}
				cursornode->nownode = cursornode->nownode->next;
			}
			p2 = p;
		}
		cursornode->nowhnode = cursornode->nowhnode->next;
	}
	*cursornode = cursornode_temp;
}
/**
 * @name: Search
 * @msg: 将提示功能和查找功能结合
 * @param {Hnode} *hnode 文本头节点
 * @param {Cursornode} *cursornode 光标结构体
 * @return {void}
 */
void Search(Hnode *hnode, Cursornode *cursornode)
{
	char str_search[128];
	memset(str_search, '\0', 128);
	char str_replace[2] = "\0";
	clrscr();
	drawmain();
	window(2, 3, 24, 79);
	textbackground(BLUE);
	cprintf("please enter the string you want to search\n\r");
	gets(str_search);
	search(hnode, cursornode, str_search, str_replace, 1, 5);
	clrscr();
	drawmain();
}
/**
 * @name: Replace
 * @msg: 将替换功能和提示结合在一起
 * @param {Hnode} *hnode 文本头节点
 * @param {Cursornode} *cursornode 光标结构体
 * @return {void}
 */
void Replace(Hnode *hnode, Cursornode *cursornode)
{
	char str_search[128];
	char str_replace[128];
	memset(str_replace, '\0', 128);
	memset(str_search, '\0', 128);
	clrscr();
	drawmain();
	window(2, 3, 79, 24);
	textbackground(BLUE);
	cprintf("please enter the string you want to replace\r\n");
	gets(str_search);
	window(2, 3, 79, 24);
	clrscr();
	cprintf("please enter the new string\r\n");
	gets(str_replace);
	search(hnode, cursornode, str_search, str_replace, 2, 4);
	clrscr();
	drawmain();
}