/*
 * @Descripttion: 链表操作
 * @version: 1.0.0
 * @Author: Zhou
 * @Date: 2021-04-28 15:17:44
 * @LastEditors: Andy
 * @LastEditTime: 2021-05-01 23:27:24
 */

#ifndef _NODE_H
#define _NODE_H
#include "define.h"
#include "menu.h"
#include "mouse.h"
#include "move.h"
//初始化链表
Hnode *InitList(Hnode *hnode, Cursornode *cursornode, Offset *offset, Clipboard *clipboard, int *save_flag, int *text_flag);
//初步判断传进字符的类型
int Judgetype(unsigned short ch);
//添加列节点
void AddNode(Cursornode *cursornode, unsigned short ch);
//添加行节点
Hnode *AddHnode(Hnode *hnode, Cursornode *cursornode);
//清除链表
void ClearLists(Hnode *Hhead);
//打印链表数据
void Printlist(Hnode *hnode, Cursornode *cursornode, Offset *offset);
//删除行节点及该行所有数据
Hnode *DeleteHnode(Hnode *hnode, Cursornode *cursornode);
//删除列节点
void DeleteNode(Hnode *hnode, Cursornode *cursornode);
#endif
