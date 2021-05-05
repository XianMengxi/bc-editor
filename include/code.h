#ifndef _CODE_H
#define _CODE_H
#include"define.h"
#include"key.h"
#include"node.h"
#include"move.h"
#include"chinese.h"
#include"compile.h"
/*
 *@name:code
 *@msg:完成括号匹配与自动缩进
 *@param:{Hnode *}hnode 链表头
 *@param:{Cursornode *}cursornode 光标位置
 *@param:{int}flag 表示括号匹配的类型
 *@return:{void}
*/
void code (Hnode *hnode,Cursornode *cursornode,int flag);



#endif