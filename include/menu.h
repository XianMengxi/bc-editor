#ifndef DRAW_FUNCTION_H
#define DRAW_FUNCTION_H
#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<conio.h>
#include<bios.h>
#include"define.h"
void drawmain();
void box(int x, int y, int h, int w);
int drawmenu(Hnode *hnode,Cursornode *cursornode,Offset *offset ,int textflags,int op);
int menu_ud(int op, int flag);
int menu_lr(int op, int flag2, int*pflag,Hnode * hnode,int textflags,Cursornode *cursornode ,Offset *offset);
int menu_ud_m(int flag,int flag_t);
void mainloop();
int menu_ud3(int op,int flag3,int flag3_1);
#endif
