#ifndef FUNCTION_H
#define FUNCTION_H
#pragma once
#include"define.h"
Hnode* InitList(Hnode *hnode, Cursornode *cursornode, int *saveflags,int *textflags); //初始化链表
int Judgetype(unsigned short ch); //判断字符类型
void AddNode(Cursornode *cursornode, unsigned short ch); //添加节点
Hnode *AddHnode(Cursornode *cursornode, Hnode*hnode_head);  //添加行节点
//清除链表中的数据
void ClearLists(Hnode *Hhead);
void printlist(Hnode *hnode);  //打印链表
//直接删除头节点及里面数据
Hnode * DeleteHnode(Hnode *hnode, Cursornode *cursornode);
//删除节点
void DeleteNode(Hnode *hnode, Cursornode *cursornode);
void find_location(Hnode *hnode, Cursornode *cursornode, int x, int y);  //定位，根据坐标
void Cursormove(Hnode *hnode, Cursornode *cursornode, int direction); //按光标位置进行上下左右移动
//读取文件
int ReadFile(Hnode *hnode, Cursornode *cursornode,int *saveflags,int *textflags,char *path);
//保存文件
int SaveFile(Hnode *hnode,int *saveflags,int *textflags,char *path);
void Save(Hnode *hnode,int *saveflags,int *textflags,char *path,char *file);
void change_dir(char *path);
//查找光标位置
void find_cursor(Hnode *hnode ,Cursornode *cursornode);
void search(Hnode *hnode,Cursornode *cursornode,char *str1,char *str2,int flags,int color);
Hnode* close(Hnode *hnode,int *saveflags,int *textflags);
void readhnode(Hnode *hnode, char str[]);
void Search(Hnode *hnode,Cursornode *cursornode);
void Replace(Hnode *hnode ,Cursornode *cursornode);
void printlist(Hnode *hnode,Cursornode *cursornode,Offset *offset);
void find_offset(Hnode *hnode, Cursornode *cursornode, Offset *offset);
void where_cursor(Hnode *hnode, Cursornode *cursornode, int *cursor_x, int *cursor_y);
void find_cursor(Hnode *hnode ,Cursornode *cursornode,Offset *offset);
void mouse_click(Hnode *hnode, Cursornode *cursornode, Offset *offset);
void mouse_choose(Hnode *hnode, Cursornode *cursornode,Offset *offset);
#endif