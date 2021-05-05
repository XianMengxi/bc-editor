#ifndef _HIGH_LI_H
#define _HIGH_LI_H
#include<stdlib.h>
#include"define.h"
#include"node.h"
/*
 *@name:high_li
 *@msg:完成对保留字的染色，并兼顾模拟编译中对main函数的查找
 *@param:{Hnode *}hnode 链表头
 *@param:{Cursornode *}cursornode 光标位置
 *@param:{char *} 专用于传入"main"
 *@return:{int} flag2 表明是否找到main
*/
int high_li(Hnode*hnode, Cursornode* cursornode, char str[], int color);//15是bc的原色
/*
 *@name:High_li
 *@msg:完成代码高亮的染色
 *@param:{Hnode *}hnode链表头
 *@param:{Cursornode *}cursornode光标位置
 *@param:{int}color待染颜色的标号
 *@return:{void}
*/
void High_li(Hnode* hnode,Cursornode* cursornode,int color,int flag);//仅进行颜色的设置
/*
 *@name:color_set
 *@msg:完成对文件中颜色配置的写入
 *@param:{int}颜色组号
 *@return:{void}
*/
void color_set(int flag);//设置菜单中的颜色组，flag代表组号
/*
 *@name:color_set2
 *@msg:从文件中读取颜色配置将其写入数组，再由High_li染色
 *@param:{int *}pcolor 记录颜色的数组
 *@return:{void}
*/
void color_set2(int * pcolor);//读取文件中的颜色
/*
 *@name:chigh_li
 *@msg:刷新高亮
 *@param:{Hnode  *}hnode 链表头
 *@return:{void}
*/
void chigh_li(Hnode* hnode);
#endif
