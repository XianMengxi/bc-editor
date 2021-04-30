/*
 * @Descripttion: 查找替换等功能
 * @version: 1.0.0
 * @Author: Zhou
 * @Date: 2021-04-28 12:18:50
 * @LastEditors: Andy
 * @LastEditTime: 2021-04-29 20:59:31
 */
#ifndef _SEARCH_H
#define _SEARCH_H
#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "define.h"
#include "menu.h"
//查找替换
void Find(Hnode *hnode, Cursornode *cursornode, char *str1, char *str2, int flag, int color);
//将一行放进字符串中
void Readhnode(Hnode *hnode, char str[]);
//查找加提示功能
void Search(Hnode *hnode, Cursornode *cursornode);
//替换加提示功能
void Replace(Hnode *hnode, Cursornode *cursornode);
#endif // !_SEARCH_H
