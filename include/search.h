#ifndef _SEARCH_H
#define _SEARCH_H
#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"define.h"
//flags=1:���� flags=2:�滻
void search(Hnode *hnode,Cursornode *cursornode,char *str1,char *str2,int flag,int color);
//�������б�����ַ�����
void readhnode(Hnode *hnode, char str[]);
#endif // !_SEARCH_H
