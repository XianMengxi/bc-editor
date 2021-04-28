#include<stdlib.h>
int high_li(Hnode *hnode, Cursornode *cursornode, char str[], int color);//15是bc的原色
void High_li(Hnode* hnode,Cursornode * cursornode,int color,int flag);//仅进行颜色的设置
void color_set(int flag);//设置菜单中的颜色组，flag代表组号
void color_set2(int * pcolor);//读取文件中的颜色
void chigh_li(Hnode* hnode);
