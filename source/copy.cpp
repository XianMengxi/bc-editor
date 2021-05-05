/*
 * @Descripttion: 复制粘贴等操作
 * @version: 1.0.0
 * @Author: Zhou
 * @Date: 2021-04-28 12:18:50
 * @LastEditors: Andy
 * @LastEditTime: 2021-04-29 20:54:45
 */

#include "copy.h"
/**
 * @name: Choose
 * @msg: 按键选择文本
 * @param {Hnode} *hnode 文本节点
 * @param {Cursornode} *cursornode 光标结构体
 * @param {short} key 按键键值
 * @param {Offset} *offset 偏移量结构体
 * @return {void}
 */
void Choose(Hnode *hnode, Cursornode *cursornode, short key, Offset *offset)
{
	unsigned short c = 0;
	unsigned short d;
	Cursornode temp1 = *cursornode;
	Cursornode temp2 = *cursornode;
	if (key == CL || key == CR || key == CU || key == CD)
	{
		Show_choose(temp1, temp2);
		Printlist(hnode, cursornode, offset);
		Find_cursor(hnode, cursornode, offset);
		d = (bioskey(2) & 0x04);
		while (d == 0x04)
		{
			if (bioskey(1))
				c = bioskey(0);
			else
				c = 0;
			if (c == CL || c == CR || c == CU || c == CD)
			{
				int move = 0;
				if (c == CL)
				{
					move = LEFT;
				}
				else if (c == CR)
				{
					move = RIGHT;
				}
				else if (c == CU)
				{
					move = UP;
				}
				else if (c == CD)
				{
					move = DOWN;
				}
				Cursormove(hnode, cursornode, move);
				temp2 = *cursornode;
				Recovery(hnode);
				Show_choose(temp1, temp2);
				Printlist(hnode, cursornode, offset);
				Find_cursor(hnode, cursornode, offset);
			}
			d = (bioskey(2) & 0x04);
		}
	}
	Printlist(hnode, cursornode, offset);
	Find_cursor(hnode, cursornode, offset);
}
/**
 * @name: Show_choose
 * @msg: 显示选中的文本内容
 * @param {Cursornode} cursornode_1 光标结构体1
 * @param {Cursornode} cursornode_2 光标结构体2
 * @return {void}
 */
void Show_choose(Cursornode cursornode_1, Cursornode cursornode_2)
{
	Node *node1, *node2;
	Hnode *hnode1, *hnode2;
	if (Judgewhere(cursornode_1, cursornode_2) > 0)
	{
		node1 = cursornode_1.nownode;
		hnode1 = cursornode_1.nowhnode;
		node2 = cursornode_2.nownode;
		hnode2 = cursornode_2.nowhnode;
	}
	else
	{
		node1 = cursornode_2.nownode;
		hnode1 = cursornode_2.nowhnode;
		node2 = cursornode_1.nownode;
		hnode2 = cursornode_1.nowhnode;
	}
	if (node1 == NULL)
	{
		node1 = hnode1->head;
	}
	else if (node1->next != NULL && node1 != node2)
	{
		node1 = node1->next;
	}
	while (hnode1 != hnode2 && hnode1 != NULL)
	{
		while (node1 != NULL)
		{
			node1->bkflag = 1;
			node1 = node1->next;
		}
		hnode1 = hnode1->next;
		node1 = hnode1->head;
	}
	if (node1 == NULL)
	{
		node1 = hnode1->head;
	}
	while (node1 != node2 && node1 != NULL)
	{
		node1->bkflag = 1;
		node1 = node1->next;
	}
	node1->bkflag = 1;
}
/**
 * @name: Judgewhere
 * @msg: 判断cursornode的前后
 * @param {Cursornode} cursornode_temp1 光标结构体1
 * @param {Cursornode} cursornode_temp2 光标结构体2
 * @return {int} 若>1,则光标结构体1在光标结构体2前
 */
int Judgewhere(Cursornode cursornode_1, Cursornode cursornode_2)
{
	Cursornode cursornode_temp;
	Node *node;
	Hnode *temp = cursornode_1.nowhnode;
	if (temp != cursornode_2.nowhnode)
	{
		while (temp != cursornode_2.nowhnode && temp != NULL)
		{
			temp = temp->next;
		}
		if (temp == NULL)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}

	else if (cursornode_1.nownode == cursornode_2.nownode)
	{
		return 1;
	}
	else if (cursornode_1.nownode == NULL)
	{
		return 1;
	}
	else if (cursornode_2.nownode == NULL)
	{
		return -1;
	}
	else
	{
		node = cursornode_1.nowhnode->head;
		while (node != cursornode_1.nownode && node != cursornode_2.nownode)
		{
			node = node->next;
		}
		if (node == cursornode_1.nownode)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
}
/**
 * @name: Recovery
 * @msg: 恢复所有选中为初始状态
 * @param {Hnode} *hnode 文本头节点
 * @return {void}
 */
void Recovery(Hnode *hnode)
{
	Hnode *temp = hnode;
	Node *node;
	while (temp != NULL)
	{
		node = temp->head;
		while (node != NULL)
		{
			node->bkflag = 0;
			node = node->next;
		}
		temp = temp->next;
	}
}
/**
 * @name: Putclip
 * @msg: 把文本中选中的结构体全部放进剪贴板中
 * @param {Hnode} *hnode 文本头节点
 * @param {Clipboard} *clipboard 剪贴板
 * @return {void}
 */
void Putclip(Hnode *hnode, Clipboard *clipboard)
{
	Node *node;
	Hnode *htemp = hnode;
	char *temp;
	char isbkflag=0;
	if (clipboard->clipboard != NULL)
	{
		free(clipboard->clipboard);
		clipboard->clipboard = NULL;
	}
	Count(hnode, clipboard);
	clipboard->clipboard = (char *)malloc((clipboard->num + 1) * sizeof(char));
	memset(clipboard->clipboard, '\0', (clipboard->num + 1) * sizeof(char));
	temp = clipboard->clipboard;
	while (htemp != NULL)
	{
		node = htemp->head;
		while (node != NULL)
		{
			if (node->bkflag == 1)
			{
				isbkflag=1;
				*temp = node->chr;
				temp++;
			}
			node = node->next;
		}
		htemp = htemp->next;
		if (isbkflag==1 && htemp != NULL && htemp->head->bkflag == 1)
		{
			*temp = '\n';
			temp++;
		}
	}
	drawmain();
}
/**
 * @name: Count
 * @msg: 计算剪贴板中字符个数
 * @param {Hnode} *hnode 文本头节点
 * @param {Clipboard} *clipboard 剪切版
 * @return {void}
 */
void Count(Hnode *hnode, Clipboard *clipboard)
{
	Hnode *temp = hnode;
	Node *node;
	clipboard->num = 0;
	while (temp != NULL)
	{
		node = temp->head;
		while (node != NULL)
		{
			if (node->bkflag == 1)
			{
				clipboard->num++;
			}
			node = node->next;
		}
		temp = temp->next;
		if (temp != NULL && temp->head->bkflag == 1)
		{
			clipboard->num++;
		}
	}
}
/**
 * @name: Paste
 * @msg: 粘贴功能
 * @param {Hnode} *hnode 文本头节点
 * @param {Cursornode} *cursornode 光标结构体
 * @param {Clipboard} *clipboard 剪切板
 * @return {void}
 */
void Paste(Hnode *hnode, Cursornode *cursornode, Clipboard *clipboard)
{
	char *temp = clipboard->clipboard;
	while (temp != NULL && *temp != '\0')
	{
		if (*temp == '\n' || *temp == '\r')
		{
			code(hnode, cursornode, 1);
		}
		else
		{
			AddNode(cursornode, *temp);
		}
		temp++;
	}
}
/**
 * @name: Cut
 * @msg: 剪切功能
 * @param {Hnode} *hnode 文本头节点
 * @param {Cursornode} *cursornode 光标结构体
 * @param {Clipboard} *clipboard 剪切板
 * @return {void}
 */
void Cut(Hnode *hnode, Cursornode *cursornode, Clipboard *clipboard)
{
	Hnode *temp = hnode;
	Node *node;
	Putclip(hnode, clipboard);
	while (temp != NULL)
	{
		node = temp->head;
		while (node != NULL)
		{
			if (node->bkflag == 1)
			{
				cursornode->nowhnode = temp;
				cursornode->nownode = node;
			}
			node = node->next;
		}
		temp = temp->next;
	}
	while (cursornode->nownode->bkflag == 1)
	{
		DeleteNode(hnode, cursornode);
		while (cursornode->nownode == NULL)
		{
			DeleteNode(hnode, cursornode);
		}
	}
	clrscr();
	drawmain();
}