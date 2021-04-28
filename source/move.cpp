/*
 * @Descripttion: 光标的查找和移动
 * @version: 1.0.0
 * @Author: Zhou
 * @Date: 2021-04-28 12:18:50
 * @LastEditors: Andy
 * @LastEditTime: 2021-04-28 13:07:21
 */
#include "define.h"
#include "function.h"
#include "key.h"
#include "mouse.h"
#include "copy.h"
/**
 * @name: find_location
 * @msg: 根据传进的位置使光标跳转
 * @param {Hnode}:*hnode 文本头节点
 * @param {Cursronode}:*cursornode 光标结构体
 * @param {int}:x 跳转的行数
 * @param {int}:y 跳转的列数
 * @return {void}
 */
void Find_location(Hnode *hnode, Cursornode *cursornode, int x, int y)
{
	Node *node;
	int i;
	for (i = 1; i < x && hnode->next != NULL; i++)
	{
		hnode = hnode->next;
	}
	if (y == 1)
	{
		cursornode->nowhnode = hnode;
		cursornode->nownode = NULL;
	}
	else if ((node = hnode->head) != NULL)
	{
		for (i = 2; i < y && node != NULL && node->next != NULL; i++)
		{
			node = node->next;
		}
		cursornode->nowhnode = hnode;
		cursornode->nownode = node;
	}
}
/**
 * @name: Where_cursor
 * @msg: 查找并把现在光标的位置存到cursor_x,cursor_y中
 * @param {Hnode} *hnode 文本头节点
 * @param {Cursornode} *cursornode 光标结构体
 * @param {int} *cursor_x 光标现在的列位置
 * @param {int} *cursor_y 光标现在的行位置
 * @return {void}
 */
void Where_cursor(Hnode *hnode, Cursornode *cursornode, int *cursor_x, int *cursor_y)
{
	int x = 1;
	int y = 1;
	Node *temp = NULL;
	while (hnode != NULL && hnode != cursornode->nowhnode)
	{
		y++;
		hnode = hnode->next;
	}
	if (cursornode->nownode != NULL)
	{
		temp = cursornode->nowhnode->head;
		x++;
	}
	while (temp != NULL && temp != cursornode->nownode)
	{
		temp = temp->next;
		x++;
	}
	*cursor_x = x;
	*cursor_y = y;
}
/**
 * @name: Find_cursor
 * @msg: 将光标跳转到cursornode的位置
 * @param {Hnode} *hnode 文本头节点
 * @param {Cursornode} *cursornode 光标结构体
 * @param {Offset} *offset 偏移量结构体
 * @return {void} 
 */
void Find_cursor(Hnode *hnode, Cursornode *cursornode, Offset *offset)
{
	window(5, 3, 79, 23);
	int cursor_x, cursor_y;
	Where_cursor(hnode, cursornode, &cursor_x, &cursor_y);
	Find_offset(hnode, cursornode, offset);
	gotoxy(cursor_x - offset->x + 1, cursor_y - offset->y + 1);
}
/**
 * @name: Cursormove
 * @msg: 光标移动
 * @param {Hnode} *hnode 文本头节点
 * @param {Cursornode} *cursornode 光标结构体
 * @param {int} direction 方向
 * @return {void}
 */
void Cursormove(Hnode *hnode, Cursornode *cursornode, int direction) //�����λ�ý��������ƶ�
{
	if (direction == RIGHT) //光标向右移动
	{
		//光标在第一位
		if (cursornode->nownode == NULL)
		{
			cursornode->nownode = cursornode->nowhnode->head;
		}
		//光标在一行的中间
		else if (cursornode->nownode->next != NULL)
		{
			cursornode->nownode = cursornode->nownode->next;
		}
		//光标所在行不为最后一行
		else if (cursornode->nowhnode->next != NULL)
		{
			cursornode->nowhnode = cursornode->nowhnode->next;
			cursornode->nownode = NULL;
		}
	}
	else if (direction == LEFT) //对应向左移动
	{
		Node *node = cursornode->nowhnode->head;
		//光标在一行的开头
		if (cursornode->nownode == NULL)
		{
			//光标不在第一行
			if (cursornode->nowhnode != hnode)
			{
				while (hnode->next != cursornode->nowhnode)
				{
					hnode = hnode->next;
				}
				cursornode->nowhnode = hnode;
				cursornode->nownode = cursornode->nowhnode->head;
				while (cursornode->nownode != NULL && cursornode->nownode->next != NULL)
				{
					cursornode->nownode = cursornode->nownode->next;
				}
			}
		}
		//光标在一行的中间（不包括第二号位）
		else if (node != cursornode->nownode)
		{
			while (node->next != cursornode->nownode)
			{
				node = node->next;
			}
			cursornode->nownode = node;
		}
		//光标在第二号位置
		else if (node == cursornode->nownode)
		{
			cursornode->nownode = NULL;
		}
	}
	else if (direction == DOWN) //对应光标向下移动
	{
		//光标所在行的下一行不为空，通过两行的node同时移动达到向下移动的目的
		if (cursornode->nowhnode->next != NULL)
		{
			hnode = cursornode->nowhnode->next;
			Node *cur_node, *node_temp;
			cur_node = cursornode->nowhnode->head;
			temp = hnode->head;
			while (cur_node != cursornode->nownode)
			{
				cur_node = cur_node->next;
				if (temp->next->next != NULL)
				{
					temp = temp->next;
				}
			}
			cursornode->nowhnode = hnode;
			cursornode->nownode = temp;
		}
	}
	else if (direction == UP) //对应光标向上移动
	{
		//光标不在第一行，通过两行的node同时移动达到向上移动的目的
		if (cursornode->nowhnode != hnode)
		{
			while (hnode->next != cursornode->nowhnode)
			{
				hnode = hnode->next;
			}
			Node *cur_node, *temp;
			cur_node = cursornode->nowhnode->head;
			temp = hnode->head;
			while (cur_node != cursornode->nownode)
			{
				cur_node = cur_node->next;
				if (temp->next->next != NULL)
				{
					temp = temp->next;
				}
			}
			cursornode->nowhnode = hnode;
			cursornode->nownode = temp;
		}
	}
}
/**
 * @name: MouseClick
 * @msg: 鼠标点击，光标跳转
 * @param {Hnode} *hnode 文本头节点
 * @param {Cursornode} *cursornode 光标结构体
 * @param {Offset} *offset 偏移量结构体
 * @return {void}
 */
void MouseClick(Hnode *hnode, Cursornode *cursornode, Offset *offset)
{
	getmouse();
	if (M_s == 1) //左键按下
	{
		unsigned short x = M_x / 8 + 1;
		unsigned short y = M_y / 8 + 1;
		//按下的位置属于文本输出位置
		if (x >= 5 && x <= 80 && y >= 3 && y <= 23)
		{
			Find_offset(hnode, cursornode, offset);
			Find_location(hnode, cursornode, y - 3 + offset->y, x - 5 + offset->x);
			Printlist(hnode, cursornode, offset);
			Find_cursor(hnode, cursornode, offset);
		}
		//点在没有被选中的字符，则将所有选中去除
		if (cursornode->nownode->bkflag != 0)
		{
			Recovery(hnode);
		}
	}
}
/**
 * @name: Mouse_choose
 * @msg: 鼠标对文本进行选中
 * @param {Hnode} *hnode 文本头节点
 * @param {Cursornode} *cursornode 光标结构体
 * @param {Offset} *offset 偏移量结构体
 * @return {void}
 */
void Mouse_choose(Hnode *hnode, Cursornode *cursornode, Offset *offset)
{
	Mouse_click(hnode, cursornode, offset);
	Cursornode temp1 = *cursornode;
	Cursornode temp2 = *cursornode;
	unsigned short x = M_x / 8 + 1;
	unsigned short y = M_y / 8 + 1;
	unsigned short pre_x = x;
	unsigned short pre_y = y;
	//左键按下且按下位置在文本位置
	while (M_s == 1 && M_sc <= 0 && x >= 5 && x <= 80 && y >= 3 && y <= 23)
	{
		//这一次按下位置和上一次不一样才更新位置
		if (pre_x != x || pre_y != y)
		{
			Find_location(hnode, cursornode, y - 3 + offset->y, x - 5 + offset->x);
			temp2 = *cursornode;
			Recovery(hnode);
			Show_choose(temp1, temp2);
			Printlist(hnode, cursornode, offset);
			Find_cursor(hnode, cursornode, offset);
		}
		getmouse();
		pre_x = x;
		pre_y = y;
		x = M_x / 8 + 1;
		y = M_y / 8 + 1;
	}
	Printlist(hnode, cursornode, offset);
	Find_cursor(hnode, cursornode, offset);
}
