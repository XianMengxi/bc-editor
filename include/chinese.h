#ifndef _CHINESE_H
#define _CHINESE_H
#include"define.h"
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include"mouse.h"
#include"hanzi.h"
#include"menu.h"
#include"key.h"
#include"high_li.h"
#include"code.h"
#include"node.h"
/*
 *@name:chinese
 *@msg:汉化界面的总函数
 *@param:{Hnode *} hnode 链表头
 *@param:{Cursornode *}cursornode 光标位置
 *@param:{int}h字体变量//以后删了
 *@param:{int *}颜色控制数组
 *@param:{int}textflags 表示当前有无链表显示
 *@param:{int *}记录在汉化模式下按下的菜单
 *@return:{Hnode *}改变后的链表头
*/
Hnode* chinese(Hnode * hnode,Cursornode *cursornode,int *menu_c,int *color,int textflags);
/*
 *@name:drawmain_c
 *@msg:画图形界面下主界面
 *@param:{void}
 *@return:{void}
*/
void drawmain_c();
/*
 *@name:drawmenu_c
 *@msg:画图形界面菜单
 *@param:{int}op 主循环中按下的按键扫描码
 *@param:{Hnode *}hnode 链表头
 *@param:{int}hl 当前所处链表行数
 *@param:{int}hr 当前所处列表列数
 *@param:{int *}pcolor 颜色数组
 *@param:{int}textflags 当前链表有无显示的标志
 *@return:{void}
*/
void drawmenu_c(int op,Hnode*hnode,int hl,int hr,int *pcolor,int textflags);
/*
 *@name:printline_chinese
 *@msg:打印汉化模式下一行链表
 *@param:{Hnode *}hnode 链表头
 *@param:{FILE *}YOU16 汉字文件指针
 *@param:{int *}color 颜色数组
 *@param:{int}hr 当前显示的列数
 *@return:{void}
*/
void printline_chinese(Hnode* hnode,FILE * YOU16,int color[],int hr);//在当前位置输出hnode指向的这一行
void hz_s(int flag, char* phz_s);
/*
 *@name:draw_com
 *@msg:画中文界面下提示框
 *@param:{void}
 *@return:{void}
*/
void draw_com(void);
/*
 *@name:printlist_chinese
 *@msg:打印汉化模式下链表
 *@param:{Hnode *}hnode 链表头节点
 *@param:{int *}color 颜色数组
 *@param:{int}hl 当前显示的链表行数
 *@param:{int}hr 当前显示的链表列数
 *@return:{void}
*/
void printlist_chinese(Hnode *hnode,  int color[], int hl,int hr);//目前传入的hnode为p,color为pcolor
/*
 *@name:ziti_set
 *@msg:将字体配置写入文件
 *@param:{int}i字体配置标志
 *@return:{void}
*/
void ziti_set(int i);
/*
 *@name:ziti_set2
 *@msg:从文件中读取字体配置
 *@param:{void}
 *@return:{int}t 返回字体配置标志
*/
int ziti_set2(void);
/*
 *@name:utf_8_to_utf_16
 *@msg:完成编码转换
 *@param:{Node *}node 储存字符的链表节点
 *@param:{unsigned short}转换后的utf_16字符
 *@return:{int}1--》成功，0：失败
*/
int utf_8_to_16(Node *node, unsigned short *uni);
/*
 *@name:probar
 *@msg:画汉化模式下进度条
 *@param:{int}hl 当前显示行数
 *@param:{int}shl 当前显示总行数
 *@param:{int}hr 当前显示列数
 *@param:{int}shr 当前显示总列数
 *@return:{void}
*/
void probar(int hl,int shl, int hr,int shr);//画进度条函数
/*
 *@name:menu_cl
 *@msg:汉化模式下向左翻页
 *@param:{Hnode *}hnode_c 列表头
 *@param:{int}hr 翻页前所处列数
 *@return:{int}hr 翻页后所处列数
*/
int menu_cl(Hnode *hnode_c,int hr);//返回值为hr,//传入值为p2
/*
 *@name:menu_cr
 *@msg:汉化模式下向右翻页
 *@param:{Hnode *}hnode_c 链表头
 *@param:{int}hr 翻页前所处列数
 *@return:{int}hr 翻页后所处列数
*/
int menu_cr(Hnode *hnode_c,int hr);//返回值为hr,//传入值为p2
/*
 *@name:draw_oc
 *@msg:汉化模式下画提示框
 *@param:{void}
 *@return:{void}
*/
void draw_oc();
/*
 *@name:draw_help
 *@msg:画帮助界面
 *@param:{void}
 *@return:{void}
*/
void draw_help();
/*
 *@name:draw_help2
 *@msg:画帮助界面
 *@param:{void}
 *@return:{void}
*/
void draw_help2();
/*
 *@name:add_cl
 *@msg:命令模式下插入剪切板中一行
 *@param:{Hnode *}hnode 插入行之前的行链表头
 *@param:{Hnode *}hnode_c 剪切板中一行链表头
 *@param:{}//遗留问题 需要处理
 *@return:{void}
*/
void add_cl(Hnode *hnode, Hnode *hnode_c);//在hnode行后插入hnode_c(需要复制）行
/*
 *@name:del_l
 *@msg:汉化命令模式下删除一行
 *@param:{Hnode *}hnode 要删除行的链表头节点
 *@return:{Hnode *}删除后的行链表头节点
*/
Hnode * del_l(Hnode *hnode);//将hnode行删free掉 关于删除第一行在函数外讨论
/*
 *@name:trans
 *@msg:将链表进行转换 汉字对齐
 *@param:{Hnode *}hnode 链表头节点
 *@param:{Cursornode *}cursornode 光标位置
 *@param:{int *}row 总行数
 *@param:{int *}cols 总列数
 *@return:{Hnode *}转换后的链表头节点
*/
Hnode* trans(Hnode *hnode, Cursornode *cursornode, int *row, int *cols);
/*
 *@name:copy_l
 *@msg:命令模式下将链表中一行复制到剪切板中
 *@param:{Hnode *}hnode_c 复制行的链表头
 *@param:{Hnode *}hnode_cc 剪切板的链表头
 *@return:{void}
*/
void copy_l(Hnode *hnode_c, Hnode *hnode_cc);
/*
 *@name:free_copy
 *@msg:清空剪切板
 *@param:{Hnode *}hnode 剪切板头
 *@return:{void}
*/
void  free_copy(Hnode * hnode);
#endif // !_CHINESE_H