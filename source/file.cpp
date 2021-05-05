/*
 * @Descripttion: 文件操作
 * @version: 1.0.0
 * @Author: Zhou
 * @Date: 2021-04-28 12:18:50
 * @LastEditors: Andy
 * @LastEditTime: 2021-04-29 20:10:36
 */

#include "file.h"
/**
 * @name: ReadFile
 * @msg: 读取文件
 * @param {Hnode} *hnode 文本头节点
 * @param {Cursornode} *cursornode 光标结构体
 * @param {int} *saveflag 文本是否保存
 * @param {int} *textflag 是否有文本在操作
 * @param {char} *path 文件路径
 * @return {int} 文本是否读取成功
 */
int ReadFile(Hnode *hnode, Cursornode *cursornode, int *saveflag, int *textflag, char *path,char *name)
{
	char filename[128];
	char file[128];
	char ch;
	window(2, 3, 79, 23);
	textbackground(BLUE);
	textcolor(WHITE);
	strcpy(file, path);
	if (*saveflag == 0 && *textflag == 1)
	{
		return 0;
	}
	cprintf("please enter the filename\n\r");
	gets(filename);
	if (strstr(filename, "C:\\") != NULL || strstr(filename, "c:\\") != NULL)
	{
		strcpy(file, filename);
	}
	else
		strcat(file, filename);
	FILE *fp;
	fp = fopen(file, "r");
	if (fp == NULL)
	{
		clrscr();
		drawmain();
		window(2, 3, 79, 23);
		textbackground(BLUE);
		cprintf(" open file error,press any key to continue.\n\r");
		bioskey(0);
		return 0;
	}
	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch != '\n' && ch != '\r')
		{
			AddNode(cursornode, ch);
		}
		else
		{
			hnode = AddHnode(hnode,cursornode);
		}
	}
	*textflag = 1;
	fclose(fp);
	strcpy(name,filename);
	clrscr();
	drawmain();
	return 1;
}
/**
 * @name: SaveFile
 * @msg: 保存文件,另存为
 * @param {Hnode} *hnode 文本头节点
 * @param {int} *saveflag 文本是否保存
 * @param {int} *textflag 是否有文本在显示
 * @param {char} *path 文件路径
 * @return {int} 文本是否保存成功
 */
int SaveFile(Hnode *hnode, int *saveflag, int *textflag, char *path)
{
	Node *node;
	char filename[128];
	char file[128];
	if (*textflag != 1)
	{
		clrscr();
		drawmain();
		return 0;
	}
	strcpy(file, path);
	clrscr();
	drawmain();
	window(2, 3, 79, 24);
	textbackground(BLUE);
	textcolor(WHITE);
	cprintf("please enter the filename\n\r");
	gets(filename);
	if (strstr(filename, "C:\\") != NULL || strstr(filename, "c:\\") != NULL)
	{
		memset(file, '\0', 128 * sizeof(char));
	}
	strcat(file, filename);
	FILE *fp;
	fp = fopen(file, "wt");
	if (fp == NULL)
	{
		printf("save file error,please press any key to continue;");
		bioskey(0);
		return 0;
	}
	while (hnode != NULL)
	{
		node = hnode->head;
		while (node != NULL)
		{
			putc(node->chr, fp);
			node = node->next;
			if (node == NULL)
			{
				putc('\n', fp);
			}
		}
		hnode = hnode->next;
	}
	*saveflag = 1;
	clrscr();
	drawmain();
	fclose(fp);
	return 1;
}
/**
 * @name: Save
 * @msg: 保存文件，默认路径保存
 * @param {Hnode} *hnode 文本头节点
 * @param {int} *saveflag 文本是否保存
 * @param {int} *textflag 是否有文本正在输入
 * @param {char} *path 路径
 * @param {char} *file 文件名
 * @return {void}
 */
void Save(Hnode *hnode, int *saveflag, int *textflag, char *path, char *file)
{
	Node *node;
	char filename[128];
	textcolor(WHITE);
	if(strcmp(file,"\0")==0)
	{
		clrscr();
		drawmain();
		window(2,3,79,24);
		textbackground(BLUE);
        textcolor(WHITE);
		cprintf("please enter the new file name\n\r");
		gets(file);
		sprintf(filename,"%s%s",path,file);
	}
	else
	{
		sprintf(filename, "%s%s",path,file);
	}
	if (*textflag != 1 || *saveflag != 0)
	{
		clrscr();
		drawmain();
		return;
	}
	clrscr();
	drawmain();
	window(2, 3, 79, 24);
	textbackground(BLUE);
	textcolor(WHITE);
	FILE *fp;
	fp = fopen(filename, "wt");
	if (fp == NULL)
	{
		printf("save file error,please press any key to continue;");
		bioskey(0);
		return;
	}
	while (hnode != NULL)
	{
		node = hnode->head;
		while (node != NULL)
		{
			putc(node->chr, fp);
			node = node->next;
			if (node == NULL)
			{
				putc('\n', fp);
			}
		}
		hnode = hnode->next;
	}
	*saveflag = 1;
	clrscr();
	drawmain();
	fclose(fp);
}
/**
 * @name: Change_dir
 * @msg: 更改默认路径
 * @param {char} *path 默认路径
 * @return {void}
 */
void Change_dir(char *path)
{
	char temp[128];
	drawmain();
	window(2, 3, 79, 23);
	textbackground(BLUE);
	textcolor(WHITE);
	clrscr();
	cprintf("please enter the new location\n\r");
	textcolor(WHITE);
	memset(temp, '\0', 128 * sizeof(char));
	gets(temp);
	if (strstr(temp, "C:\\") == NULL && strstr(temp, "c:\\") == NULL)
	{
		clrscr();
		drawmain();
		window(2, 3, 79, 23);
		textbackground(BLUE);
		cprintf("change directory fail,please press any key to continue\n\r");
		bioskey(0);
		clrscr();
		drawmain();
		return;
	}
	strcpy(path, temp);
	clrscr();
	drawmain();
}
/**
 * @name: Close
 * @msg: 关闭文本
 * @param {Hnode} *hnode 文本头节点
 * @param {int} *saveflag 文本是否保存
 * @param {int} *textflag 文本是否打开
 * @return {Hnode*} 把新的头节点的位置返回
 */
Hnode *Close(Hnode *hnode, int *saveflag, int *textflag)
{
	if (textflag == 0)
	{
		clrscr();
		drawmain();
		return hnode;
	}
	else if (saveflag == 0)
	{
		clrscr();
		drawmain();
		window(2, 3, 79, 24);
		textbackground(BLUE);
		textcolor(WHITE);
		cprintf("your file is not save,please y to continue\n\r");
		if (getch() == 'y')
		{
			clrscr();
			ClearLists(hnode);
			hnode = (Hnode *)malloc(sizeof(Hnode));
			*textflag = 0;
			drawmain();
			return hnode;
		}
		else
		{
			clrscr();
			drawmain();
			return hnode;
		}
	}
	else
	{
		clrscr();
		ClearLists(hnode);
		hnode = (Hnode *)malloc(sizeof(Hnode));
		*textflag = 0;
		drawmain();
		return hnode;
	}
}