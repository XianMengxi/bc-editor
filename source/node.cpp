/*
 * @Descripttion: 链表操作
 * @version: 1.0.0
 * @Author: Zhou
 * @Date: 2021-04-28 12:18:50
 * @LastEditors: Andy
 * @LastEditTime: 2021-05-01 23:29:00
 */
#include "node.h"
#include"chinese.h"
/**
 * @name: InitList
 * @msg: 初始化链表
 * @param {Hnode} *hnode 文本头节点
 * @param {Cursornode} *cursornode 光标结构体
 * @param {Offset} *offset 文本偏移量结构体
 * @param {Clipboard} *clipboard 剪切板结构体
 * @param {int} *save_flag 文本是否保存
 * @param {int} *text_flag 是否打开一个文本
 * @return {Hnode *} 返回新链表的地址
 */
Hnode *InitList(Hnode *hnode, Cursornode *cursornode, Offset *offset, Clipboard *clipboard, int *save_flag, int *text_flag)
{
	
	//未保存，提示是否保存
	if (*save_flag == 0)
	{
		clrscr();
		drawmain();
		window(2, 3, 79, 24);
		textbackground(BLUE);
		textcolor(WHITE);
		hide_mouse();
		cprintf("file not save ,\n\rplease enter y to abandon this file,enter n to cancel.");
		show_mouse();
		if (getch() != 'y')
		{
			drawmain();
			return hnode;
		}
		else
		{
			ClearLists(hnode);
			clrscr();
			*save_flag = 1;
			*text_flag = 1;
			hnode = (Hnode *)malloc(sizeof(Hnode));
			drawmain();
		}
	}

	//已保存，清空链表
	else if (*text_flag == 1 && *save_flag == 1)
	{
		ClearLists(hnode);
		clrscr();
		hnode = (Hnode *)malloc(sizeof(Hnode));
		drawmain();
	}

	hnode->next = NULL;
	hnode->head = NULL;
	hnode->cols = 0;
	cursornode->nowhnode = hnode;
	cursornode->nownode = NULL;
	clipboard->clipboard = NULL;
	clipboard->num = 0;
	offset->x = 1;
	offset->y = 1;
	*text_flag = 1;
	drawmain();
	return hnode;
}
/**
 * @name: Judgetype
 * @msg: 初步判断字符类型
 * @param {unsigned short} ch 字符
 * @return {int} 类型标记
 */
int Judgetype(unsigned short ch)
{
	//字母
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
	{
		return 2;
	}
	//数字
	else if (ch >= '0' && ch <= '9')
	{
		return 1;
	}
	//数学符号
	else if (ch == '+' || ch == '-' || ch == '<' || ch == '=' || ch == '>' || ch == '*' || ch == '\\' || ch == '!') //��ѧ����
	{
		return 3;
	}
	//其它
	else
	{
		return 4;
	}
}
/**
 * @name: AddNode
 * @msg: 在光标后面添加一个节点
 * @param {Cursornode} *cursornode 光标结构体
 * @param {unsigned short} ch 字符
 * @return {void}
 */
void AddNode(Cursornode *cursornode, unsigned short ch)
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->chr = ch;
	node->type = Judgetype(ch);
	node->bkflag = 0;
	cursornode->nowhnode->cols++;
	//对应光标在第一个位置，该行无数据
	if (cursornode->nownode == NULL && cursornode->nowhnode->head == NULL)
	{
		node->next = NULL;
		cursornode->nowhnode->head = node;
		cursornode->nownode = node;
	}
	//对应光标在一行第一个位置，该行有数据
	else if (cursornode->nownode == NULL && cursornode->nowhnode->head != NULL)
	{
		node->next = cursornode->nowhnode->head;
		cursornode->nowhnode->head = node;
		cursornode->nownode = node;
	}
	//对应光标在一行末尾
	else if (cursornode->nownode->next == NULL)
	{
		node->next = NULL;
		cursornode->nownode->next = node;
		cursornode->nownode = node;
	}
	//对应光标在一行中间
	else
	{
		node->next = cursornode->nownode->next;
		cursornode->nownode->next = node;
		cursornode->nownode = node;
	}
}
/**
 * @name: AddHnode
 * @msg: 添加行节点（回车键）
 * @param {Hnode} *hnode 文本头节点
 * @param {Cursornode} *cursornode 光标结构体
 * @return {Hnode*} 新头节点的位置
 */
Hnode *AddHnode(Hnode *hnode, Cursornode *cursornode)
{
	Hnode *temp = (Hnode *)malloc(sizeof(Hnode));
	temp->cols = 0;
	temp->head = NULL;
	//对应在光标在一行末尾
	if (cursornode->nownode != NULL)
	{
		Node *node = cursornode->nownode->next;
		Cursornode cur_temp;
		cur_temp = *cursornode; //保存当前光标位置
		temp->next = cursornode->nowhnode->next;
		cursornode->nowhnode->next = temp;
		cursornode->nowhnode = temp;
		cursornode->nownode = NULL;
		while (node != NULL)
		{
			AddNode(cursornode, node->chr);
			node = node->next;
		}
		while (cur_temp.nownode->next != NULL)
		{
			cur_temp.nownode = cur_temp.nownode->next;
			DeleteNode(hnode, &cur_temp);
		}
		cursornode->nownode = NULL;
		return hnode;
	}
	//对应光标在第一行且光标在第一列
	else if (cursornode->nowhnode == hnode && cursornode->nownode == NULL)
	{
		temp->next = cursornode->nowhnode;
		cursornode->nowhnode = temp;
		cursornode->nownode = NULL;
		cursornode->nowhnode = temp->next;
		return temp;
	}
	//在光标前面添加一行
	else
	{
		Hnode *htemp = hnode;
		while (htemp->next != cursornode->nowhnode)
		{
			htemp = htemp->next;
		}
		temp->next = htemp->next;
		htemp->next = temp;
		cursornode->nowhnode = temp->next;
		cursornode->nownode = NULL;
		return hnode;
	}
}
/**
 * @name: ClearLists
 * @msg: 清除链表中所有数据
 * @param {Hnode} *hnode 文本头节点
 * @return {void}
 */
void ClearLists(Hnode *hnode)
{
	Node *node, *temp;
	Hnode *Htemp;
	temp = NULL;
	while (hnode != NULL)
	{
		Htemp = hnode->next;
		node = hnode->head;
		while (node != NULL)
		{
			temp = node->next;
			free(node);
			node = temp;
		}
		free(hnode);
		hnode = Htemp;
	}
	node = NULL;
	hnode = NULL;
}
/**
 * @name: Printlist
 * @msg: 输出链表数据
 * @param {Hnode} *hnode
 * @param {Cursornode} *cursornode
 * @param {Offset} *offset
 * @return {void}
 */
void Printlist(Hnode *hnode, Cursornode *cursornode, Offset *offset)
{
	Node *node;
	Hnode *temp;
	int cols, rows;
	int x, y;
	cols = 1;
	rows = 1;
	int print_row = 1;
	Find_offset(hnode, cursornode, offset);
	Where_cursor(hnode, cursornode, &x, &y);
	for (int i = 1; i < offset->y && hnode != NULL; i++)
	{
		hnode = hnode->next;
	}
	temp = hnode;
	textbackground(3);
	textcolor(4);
	window(2, 3, 4, 23);
	clrscr();
	hide_mouse();
	//在文本最左边输出行数
	while (temp != NULL && print_row <= HEIGHT)
	{
		cprintf("%d", print_row + offset->y - 1);
		if (print_row != HEIGHT)
		{
			cprintf("\n\r");
		}
		temp = temp->next;
		print_row++;
	}
	//输出链表数据
	textbackground(BLUE);
	window(5, 3, 79, 23);
	clrscr();
	window(5, 3, 80, 23);
	while (hnode != NULL && rows <= HEIGHT)
	{
		node = hnode->head;
		for (int j = 1; j < offset->x && node != NULL; j++)
		{
			node = node->next;
		}
		while (node != NULL && cols <= WIDTH)
		{
			if (node->bkflag == 1)
			{
				textbackground(2);
			}
			else if (node->bkflag == 2)
			{
				textbackground(0);
			}
			else
			{
				textbackground(BLUE);
			}
			textcolor(node->type + 1);
			cprintf("%c", node->chr);
			node = node->next;
			cols++;
		}
		if (rows < HEIGHT)
		{
			cprintf("\n");
			cprintf("\r");
		}
		hnode = hnode->next;
		rows++;
		cols = 1;
	}
	//输出光标所在行数和列数
	window(1, 25, 70, 25);
	textbackground(7);
	clrscr();
	textcolor(BLACK);
	gotoxy(6, 1);
	cprintf("Row:%d", y);
	gotoxy(13, 1);
	cprintf("Col:%d", x);

	window(5, 3, 80, 23);
	Find_cursor(hnode, cursornode, offset);
	show_mouse();
}
/**
 * @name: DeleteHnode
 * @msg: 删除头节点
 * @param {Hnode} *hnode 文本头节点
 * @param {Cursornode} *cursornode 光标结构体
 * @return {Hnode} 新头节点的位置
 */
Hnode *DeleteHnode(Hnode *hnode, Cursornode *cursornode)
{
	Node *node, *temp;
	Hnode *htemp;
	//删除第一行数据
	if (cursornode->nowhnode == hnode)
	{
		node = cursornode->nowhnode->head;
		while (node != NULL)
		{
			temp = node->next;
			free(node);
			node = temp;
		}
		node = NULL;
		cursornode->nowhnode = cursornode->nowhnode->next;
		cursornode->nownode = NULL;
		free(hnode);
		hnode = cursornode->nowhnode;
		htemp = hnode;
		return hnode;
	}
	//删除非第一行数据
	else
	{
		htemp = hnode;
		while (htemp != NULL && htemp->next != cursornode->nowhnode)
		{
			htemp = htemp->next;
		}
		node = cursornode->nowhnode->head;
		while (node != NULL)
		{
			temp = node->next;
			free(node);
			node = temp;
		}
		node = NULL;
		cursornode->nowhnode = htemp;
		htemp = htemp->next;
		cursornode->nowhnode->next = cursornode->nowhnode->next->next;
		free(htemp);
		cursornode->nownode = cursornode->nowhnode->head;
		while (cursornode->nownode != NULL && cursornode->nownode->next != NULL)
		{
			cursornode->nownode = cursornode->nownode->next;
		}
		return hnode;
	}
}
/**
 * @name: DeleteNode
 * @msg: 删除节点
 * @param {Hnode} *hnode 文本头节点
 * @param {Cursornode} *cursornode 光标结构体
 * @return {void}
 */
void DeleteNode(Hnode *hnode, Cursornode *cursornode)
{
	Node *node = cursornode->nowhnode->head;
	Hnode *htemp = hnode;
	//该行无数据且在第一行
	if (htemp == cursornode->nowhnode && node == NULL)
	{
	}
	//该行无数据，不在第一行
	else if (node == NULL)
	{
		DeleteHnode(htemp, cursornode);
		return;
	}
	//该行有数据，且在一行第二个位置
	else if (node == cursornode->nownode)
	{
		cursornode->nownode = cursornode->nownode->next;
		cursornode->nowhnode->head = cursornode->nownode;
		cursornode->nownode = NULL;
		free(node);
		node = NULL;
		cursornode->nowhnode->cols--;
	}
	//光标在一行中间位置
	else if (cursornode->nownode != NULL)
	{
		while (node != NULL && node->next != cursornode->nownode)
		{
			node = node->next;
		}
		cursornode->nownode = cursornode->nownode->next;
		free(node->next);
		node->next = cursornode->nownode;
		cursornode->nownode = node;
		cursornode->nowhnode->cols--;
	}
	//不在第一行且光标在第一格位置
	else if (cursornode->nowhnode != hnode)
	{
		Cursornode temp;
		Node *node = cursornode->nowhnode->head;
		while (htemp->next != cursornode->nowhnode)
		{
			htemp = htemp->next;
		}
		cursornode->nowhnode = htemp;
		cursornode->nownode = cursornode->nowhnode->head;
		while (cursornode->nownode != NULL && cursornode->nownode->next != NULL)
		{
			cursornode->nownode = cursornode->nownode->next;
		}
		temp = *cursornode;
		while (node != NULL)
		{
			AddNode(cursornode, node->chr);
			node = node->next;
		}
		cursornode->nowhnode = htemp->next;
		cursornode->nownode = cursornode->nowhnode->head;
		DeleteHnode(hnode, cursornode);
		*cursornode = temp;
	}
}
/*
 *@name:utf_8_to_utf_16
 *@msg:完成编码转换
 *@param:{Node *}node 储存字符的链表节点
 *@param:{unsigned short}转换后的utf_16字符
 *@return:{int}1--》成功，0：失败
*/
int utf_8_to_16(Node *node, unsigned short *uni)
{
	int i = 0;
	char utf8[4];
	while (i <= 2)
	{
		if (node != NULL)
		{
			utf8[i] = node->chr;
			node = node->next;
		}
		else
		{
			return 0;
		}
		i++;
	}
	utf8[3] = '\0';
	*uni = ((utf8[0] & 0x0F) << 12) + ((utf8[1] & 0x3F) << 6) + (utf8[2] & 0x3F);
	return 1;
}
/*
 *@name:trans
 *@msg:将链表进行转换 汉字对齐
 *@param:{Hnode *}hnode 链表头节点
 *@param:{Cursornode *}cursornode 光标位置
 *@param:{int *}row 总行数
 *@param:{int *}cols 总列数
 *@return:{Hnode *}转换后的链表头节点
*/
Hnode* trans(Hnode *hnode, Cursornode *cursornode, int *row, int *cols)
{
	Node *node;
	Node *temp;
	Hnode *head = hnode;
	Cursornode cur_temp = *cursornode;
	*row = 1;
	int count = 0;
	int is_chinese = 0;
	int max_count = 0;
	while (hnode != NULL)
	{
		node = hnode->head;
		count = 0;
		while (node != NULL)
		{
			count++;
			if (node->chr < 0x80)
			{
				is_chinese = 0;
			}
			else if (node->chr >= 0x80 && count % 3 != 1)
			{
				cursornode->nowhnode = hnode;
				cursornode->nownode = temp;
				if (count % 3 == 2 && is_chinese != 1)
				{
					AddNode(cursornode, ' ');
					AddNode(cursornode, ' ');
					count += 2;
				}
				if (count % 3 == 0 && is_chinese != 1)
				{
					AddNode(cursornode, ' ');
					count++;
				}
				for (int i = 0; i < 2 && node != NULL; i++)
				{
					temp = node;
					node = node->next;
					count++;
				}
				is_chinese = 1;
			}
			else
			{
				for (int i = 0; i < 2 && node != NULL; i++)
				{
					temp = node;
					node = node->next;
					count++;
				}
			}
			if (node != NULL)
			{
				temp = node;
				node = node->next;
			}
		}
		if (count > max_count)
		{
			max_count = count;
		}

		hnode = hnode->next;
		(*row)++;
	}
	*cols = max_count;
	*cursornode = cur_temp;
	return head;
}
