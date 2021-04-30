/*
 * @Descripttion: 结构体定义
 * @version: 1.0.0
 * @Author: Zhou
 * @Date: 2021-04-28 12:18:50
 * @LastEditors: Andy
 * @LastEditTime: 2021-04-29 20:33:46
 */

#ifndef DEFINE_H
#define DEFINE_H
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
//列节点结构体
typedef struct Node
{
	unsigned char chr; //字符
	char type;		   //字符类型，用于填充颜色
	struct Node *next; //下一个字符
	char bkflag;	   //字符的背景（是否选中）
} Node;
//行节点结构体
typedef struct Hnode
{
	Node *head;			//列节点头
	int cols;			//一行的字符数
	struct Hnode *next; //行节点的下一个行节点
} Hnode;
//光标结构体
typedef struct Cursornode
{
	Hnode *nowhnode; //光标所在的行
	Node *nownode;	 //光标所在的列
} Cursornode;
//剪贴板结构体
typedef struct Clipboard
{
	char *clipboard; //剪贴板指针
	int num;		 //剪贴板字符数
} Clipboard;
//偏移量结构体
typedef struct Offset
{
	int x; //列方向上的偏移
	int y; //行方向上的偏移
} Offset;
#endif