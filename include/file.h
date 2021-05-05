/*
 * @Descripttion: 读取文件，保存文件操作
 * @version: 1.0.0
 * @Author: Zhou
 * @Date: 2021-04-29 19:56:37
 * @LastEditors: Andy
 * @LastEditTime: 2021-04-29 20:08:49
 */
#ifndef _FILE_H
#define _FILE_H
#include "define.h"
#include "menu.h"
#include"node.h"
//读取文件
int ReadFile(Hnode *hnode, Cursornode *cursornode, int *saveflag, int *textflag, char *path,char *name);
//保存文件，另存为
int SaveFile(Hnode *hnode, int *saveflag, int *textflag, char *path);
//保存文件，直接保存
void Save(Hnode *hnode, int *saveflag, int *textflag, char *path, char *file);
//改变默认路径
void Change_dir(char *path);
//关闭文件
Hnode *Close(Hnode *hnode, int *saveflag, int *textflag);
#endif