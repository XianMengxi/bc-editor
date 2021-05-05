/*
 * @Descripttion: 按键响应+高亮显示
 * @version: 1.0.0
 * @Author: Zhou
 * @Date: 2021-04-28 12:18:50
 * @LastEditors: Andy
 * @LastEditTime: 2021-04-29 20:28:22
 */

#include "edit.h"
#
/**
 * @name: Add
 * @msg: 对按键进行响应
 * @param {Hnode} *hnode 文本头节点
 * @param {Cursornode} *cursornode 光标节点
 * @param {int} key 按键
 * @param {int} *saveflag 文本是否保存
 * @param {int} *pcolor 颜色类型
 * @return {Hnode*} 新文本头节点
 */
Hnode *Add(Hnode *hnode, Cursornode *cursornode, int key, int *saveflag, int *pcolor)
{
	char ch = (char)(key & 0x00ff); //取bioskey键值的ASCII码
	if (key == TAB)					//tab键添加四个空格
	{
		for (int i = 0; i < 4; i++)
		{
			AddNode(cursornode, ' ');
		}
	}
	if (key == LEFT || key == RIGHT || key == UP || key == DOWN) //左右上下移动
	{
		Cursormove(hnode, cursornode, key);
	}
	else if (ch >= 32 && ch <= 127 && ch != '\n' && ch != '\r' && ch != 8) //常规字符
	{
		if (ch == '{')
			code(hnode, cursornode, 0);

		else if (ch == '(')
			code(hnode, cursornode, 2);
		else if (ch == '[')
			code(hnode, cursornode, 3);
		else if(ch=='\'')
			code(hnode, cursornode, 4);
		else if (ch == '\"')
			code(hnode, cursornode, 5);
		else
			AddNode(cursornode, ch); //添加节点
		*saveflag = 0;
	}
	else if (ch == 8) //del按键删除
	{
		DeleteNode(hnode, cursornode);
		*saveflag = 0;
	}
	else if (ch == '\n' || ch == '\r') //回车按键换行
	{
		code(hnode, cursornode, 1);
		*saveflag = 0;
	}
	//高亮显示代码
	chigh_li(hnode);
	High_li(hnode, cursornode, pcolor[0], 0);
	High_li(hnode, cursornode, pcolor[1], 1);
	High_li(hnode, cursornode, pcolor[2], 2);
	High_li(hnode, cursornode, pcolor[3], 3);
	High_li(hnode, cursornode, pcolor[4], 4);
	High_li(hnode, cursornode, pcolor[5], 5);
	return hnode;
}
