#ifndef _COPY_H
#define _COPY_H
#include"copy.h"
#include"function.h"
#include"define.h"
#include<bios.h>
#include"key.h"
#define CR 29696
#define CL 29440
#define CU 0x1615
#define CD 0x2004
#define CC 0x2E03
#define CX 0x2D18
#define CV 0x2F16
#define CS  0x1F13

void show_choose(Cursornode cursornode_1, Cursornode cursornode_2);
Cursornode choose(Hnode *hnode,Cursornode *cursornode,short key,Offset *offset);
int judgewhere(Cursornode cursornode_temp1, Cursornode cursornode_temp2);
void recovery(Hnode *hnode);
void count(Hnode *hnode, Clipboard *clipboard);
void putclip(Hnode *hnode, Clipboard *clipboard);
void copy(Hnode *hnode,Cursornode *cursornode,Clipboard *clipboard);
void paste(Hnode *hnode, Cursornode *cursornode, Clipboard *clipboard);
#endif