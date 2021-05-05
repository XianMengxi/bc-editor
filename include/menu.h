#ifndef DRAW_FUNCTION_H
#define DRAW_FUNCTION_H
#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<bios.h>
#include"define.h"
/*
 *@name:drawmain
 *@msg:画出控制台下主界面
 *@param:{void}
 *@return:{void}
*/
void drawmain();
/*
 *@name:box
 *@msg:画出控制台下方框，以减少代码量
 *@param:{int}x左上角横坐标
 *@param:{int}y左上角纵坐标
 *@param:{int}h高度
 *@param;{int}w宽度
 *@return:{void}
*/
void box(int x, int y, int h, int w);
/*
 *@name:drawmenu
 *@msg:画出控制台下菜单
 *@param:{Hnode *}hnode链表头
 *@param:{Cursornode *}cursornode光标位置
 *@param:{Offset *}offset坐标偏移量
 *@param：{int}textflags当前链表中有无文本
 *@param:{int}op主循环中按下的按键扫描码
 *@return:{int}改变主循环中菜单控制变量，表示菜单位置移动
*/
int drawmenu(Hnode *hnode,Cursornode *cursornode,Offset *offset ,int textflags,int op);
/*
 *@name:menu_ud
 *@msg:通过上下按键控制菜单上下移动，画光带条
 *@param:{int}op主循环中按下的按键值
 *@param:{int}flag子菜单的子选项，表明要画子菜单的第几个
 *@return:{int}flag 表明移动完成后菜单位置，传回主循环
*/
int menu_ud(int op, int flag,Hnode *hnode,Cursornode *cursornode,Offset *offset,int textflag);
/*
 *@name:menu_lr
 *@msg:通过响应按键值控制菜单左右移动
 *@param:{int}op按键扫描码
 *@param:{int}flag_2记录菜单位置的标志
 *@param:{Hnode *}hnode 链表头节点
 *@param:{int}textflags 当前链表中有无文本的标识
 *@param;{Cursornode *}光标位置
 *@param;{Offset *}坐标偏移量
 *@return:{int}flag_2纪录菜单位置的标识
*/
int menu_lr(int op, int flag2, int*pflag,Hnode * hnode,int textflags,Cursornode *cursornode ,Offset *offset);
/*
 *@name:menu_ud_m
 *@msg:通过鼠标完成子菜单上下的选择
 *@param:{int}flag记录选择后的子菜单
 *@param:{int}flag_t记录选择前的子菜单
 *@return:{int}flag_t记录选择后的子菜单传回主循环
*/
int menu_ud_m(int flag,int flag_t);
/*
 *@name:menu_ud3
 *@msg:通过响应按键值控制第三级菜单上下移动
 *@param:{int}op按键扫描码
 *@param:{int}flag_3记录菜单位置的标志
 *@param:{int}flag3_1记录第三级菜单位置的标志
 *@param:{Hnode *}hnode 链表头节点
 *@param;{Cursornode *}光标位置
 *@param;{Offset *}坐标偏移量
 *@param:{int} textflags 是否打开文本的标志
 *@return:{int}flag3_1记录第三级菜单位置的标志
*/
int menu_ud3(int op,int flag3,int flag3_1,Hnode *hnode,Cursornode *cursornode,Offset *offset,int textflag);
#endif
