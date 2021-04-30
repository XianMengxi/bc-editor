#ifndef _COPY_H
#define _COPY_H
#include "copy.h"
#include "function.h"
#include "define.h"
#include <bios.h>
#include "key.h"
#include "code.h"
#include "menu.h"
//显示选中内容
void Show_choose(Cursornode cursornode_1, Cursornode cursornode_2);
//按键对文本进行选中
Cursornode Choose(Hnode *hnode, Cursornode *cursornode, short key, Offset *offset);
//判断光标的前后位置
int Judgewhere(Cursornode cursornode_1, Cursornode cursornode_2);
//恢复所有选中内容
void Recovery(Hnode *hnode);
//计算被选中的字符个数
void Count(Hnode *hnode, Clipboard *clipboard);
//把选中的字符放进剪切板（复制）
void Putclip(Hnode *hnode, Clipboard *clipboard);
//剪切功能
void Cut(Hnode *hnode, Cursornode *cursornode, Clipboard *clipboard);
//粘贴功能
void Paste(Hnode *hnode, Cursornode *cursornode, Clipboard *clipboard);
#endif