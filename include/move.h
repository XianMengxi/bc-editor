/*
 * @Descripttion: 光标的查找和移动
 * @version: 1.0.0
 * @Author: Zhou
 * @Date: 2021-04-28 12:18:50
 * @LastEditors: Andy
 * @LastEditTime: 2021-04-28 15:18:05
 */
#ifndef _MOVE_H
#define _MOVE_H
#include "define.h"
#include "key.h"
#include "mouse.h"
#include "copy.h"
//查找光标位置
void Where_cursor(Hnode *hnode, Cursornode *cursornode, int *cursor_x, int *cursor_y);
//跳转到光标处
void Find_cursor(Hnode *hnode, Cursornode *cursornode, Offset *offset);
//根据传进位置跳转光标
void Find_location(Hnode *hnode, Cursornode *cursornode, int x, int y);
//光标的上下左右移动
void Cursormove(Hnode *hnode, Cursornode *cursornode, int direction);
//鼠标点击跳转
void Mouse_click(Hnode *hnode, Cursornode *cursornode, Offset *offset);
//鼠标选中文本
void Mouse_choose(Hnode *hnode, Cursornode *cursornode, Offset *offset);
//查找偏移量
void Find_offset(Hnode *hnode, Cursornode *cursornode, Offset *offset);
//屏幕文本编辑部分的大小
#define WIDTH 75
#define HEIGHT 21
#endif
