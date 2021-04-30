#ifndef _CHINESE_H
#define _CHINESE_H
#include"define.h"
int chinese(Hnode * hnode,Cursornode *cursornode,int h,int *color,int textflags);
void drawmain_c();
void drawmenu_c(int op,Hnode*hnode,int hl,int hr,int *pcolor,int textflags);
void printline_chinese(Hnode* hnode,FILE * YOU16,int color[],int hr);//在当前位置输出hnode指向的这一行
void hz_s(int flag, char* phz_s);
void draw_com(void);
void printlist_chinese(Hnode *hnode,  int color[], int hl,int hr);//目前传入的hnode为p,color为pcolor
void ziti_set(int i);
int ziti_set2(void);
int utf_8_to_16(Node *node, unsigned short *uni);
void probar(int hl,int shl, int hr,int shr);//画进度条函数
int menu_cl(Hnode *hnode_c,int hr);//返回值为hr,//传入值为p2
int menu_cr(Hnode *hnode_c,int hr);//返回值为hr,//传入值为p2
void draw_oc();
void draw_help();
void add_cl(Hnode *hnode, Hnode *hnode_c,int flag);//在hnode行后插入hnode_c(需要复制）行
Hnode * del_l(Hnode *hnode);//将hnode行删free掉 关于删除第一行在函数外讨论
Hnode* trans(Hnode *hnode, Cursornode *cursornode, int *row, int *cols);
#endif // !_CHINESE_H