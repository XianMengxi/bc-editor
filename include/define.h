#ifndef DEFINE_H
#define DEFINE_H
#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
//type=5Ϊ������
typedef struct Node //����ÿ���ַ����нڵ�
{
	unsigned char chr;   //�ַ�
	char type;    //���ͣ�������ʾ��ɫ
	struct Node*next;     //��һ���ַ�
	 char bkflag;
}Node;

/*�нڵ㣬���������ַ����͵ڼ��У�ͷָ�룬βָ�룬��nextָ��*/

typedef struct Hnode
{
	Node *head;      //ͷ�ڵ�
	int cols;            //һ���ַ���
	struct Hnode* next;    
}Hnode;
typedef struct Cursornode //����ǰһ���ڵ㣬���Ϊ��һ����Ϊ�нڵ�Ϊ��
{
	Hnode *nowhnode;   //��ǰ�нڵ�
	Node *nownode;       //��ǰ�нڵ�
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