/*
 * @Descripttion: 文本添加，鼠标按键操作等
 * @version: 1.0.0
 * @Author: Zhou
 * @Date: 2021-04-28 12:18:50
 * @LastEditors: Andy
 * @LastEditTime: 2021-04-29 20:28:41
 */
#ifndef _EDIT_H
#define _EDIT_H
#pragma once
#include "function.h"
#include "define.h"
//按键响应+高亮显示
Hnode *Add(Hnode *hnode, Cursornode *cursornode, int key, int *saveflag, int *pcolor);
#endif