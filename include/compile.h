#ifndef _COMPILE_H_
#define _COMPILE_H_
#include"search.h"
#include"define.h"
#include"menu.h"
#include "high_li.h"
/*
 *@name:complie
 *@msg:完成部分的编译功能
 *@param:{Hnode *}hnode 链表头
 *@param:{Cursornode *}cursornode 光标位置
 *@param:{int}flag 表示编译类型
 *@param:{int}flag_c 表示图形界面还是控制台
 *@param:{char}ch1编译用字符
 *@param:{char}ch2
 *@return:{int}传回编译结果 即是否发现错误
*/
int complie(Hnode* hnode,Cursornode *cursornode,int flag,int flag_c,char ch1,char ch2);
#endif