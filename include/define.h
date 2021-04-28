#ifndef DEFINE_H
#define DEFINE_H
#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
//type=5为特殊标记
typedef struct Node //储存每个字符的列节点
{
	unsigned char chr;   //字符
	char type;    //类型，用来显示颜色
	struct Node*next;     //后一个字符
	 char bkflag;
}Node;

/*行节点，包含该列字符数和第几行，头指针，尾指针，和next指针*/

typedef struct Hnode
{
	Node *head;      //头节点
	int cols;            //一行字符数
	struct Hnode* next;    
}Hnode;
typedef struct Cursornode //光标的前一个节点，光标为第一格则为列节点为空
{
	Hnode *nowhnode;   //当前行节点
	Node *nownode;       //当前列节点
}Cursornode;
typedef struct Clipboard
{
	char *clipboard;
	int num;
}Clipboard;
typedef struct Offset
{
	int x;
	int y;
}Offset;
#endif