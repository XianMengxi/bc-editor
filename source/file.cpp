#include"define.h"
#include"function.h"
#include"menu.h"
//读取文件
int ReadFile(Hnode *hnode, Cursornode *cursornode,int *saveflags,int *textflags,char *path)
{
	char filename[128];
	char file[128];
	char ch;
	window(2,3,79,23);
	textbackground(BLUE);
	strcpy(file,path);
	if(*saveflags==0 && *textflags==1)
	{
		return 0;
	}
	cprintf("please enter the filename\n\r");
	gets(filename);
	if (strstr(filename, "C:\\") != NULL)
	{
		strcpy(file,filename);
	}
	else
	strcat(file, filename);
	FILE *fp;
	fp = fopen(file, "r");
	if (fp == NULL)
	{
		clrscr();
		drawmain();
		window(2,3,79,23);
		textbackground(BLUE);
		cprintf(" open file error,press any key to continue.\n\r");
		bioskey(0);
		return 0;
	}
	while ((ch = fgetc(fp)) != EOF)
	{
                                   //读取文件到链表
		if (ch != '\n'&&ch != '\r')
		{
			AddNode(cursornode, ch);
		}
		else
		{
			hnode = AddHnode(cursornode, hnode);
		}
	}
	*textflags=1;
	fclose(fp);
	clrscr();
	drawmain();
	return 1;
}
//保存文件
int SaveFile(Hnode *hnode,int *saveflags,int *textflags,char *path)
{
	Node *node;
	char filename[128];
	char file[128];
	if (*textflags != 1 || *saveflags != 0)
	{
		clrscr();
		drawmain();
		return 0;
	}
	strcpy(file,path);
	clrscr();
	drawmain();
	window(2,3,79,24);
	textbackground(BLUE);
	cprintf("please enter the filename\n\r");
	gets(filename);
	if(strstr(filename,"C:\\")!=NULL)
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
	*saveflags = 1;
	clrscr();
	drawmain();
	fclose(fp);
	return 1;
}
void Save(Hnode *hnode,int *saveflags,int *textflags,char *path,char *file)
{
	Node *node;
	static int i=0;
	char filename[128];
	sprintf(filename,"%s%s%03d.cpp",path,file,i);
	if (*textflags != 1 || *saveflags != 0)
	{
		clrscr();
        drawmain();
		return;
	}
	clrscr();
	drawmain();
	window(2,3,79,24);
	textbackground(BLUE);
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
	*saveflags = 1;
	i+=1;
	clrscr();
	drawmain();
	fclose(fp);
}
void change_dir(char *path)
{
		char temp[128];
		drawmain();
		window(2, 3, 79, 23);
		textbackground(BLUE);
		clrscr();
		cprintf("please enter the new location\n\r");
		memset(temp,'\0', 128 * sizeof(char));
		gets(temp);
		if(strstr(temp,"C:\\")!=NULL)
		{
			clrscr();
			drawmain();
			window(2,3,79,23);
			textbackground(BLUE);
			cprintf("change directory fail,please press any key to continue\n\r");
			bioskey(0);
			clrscr();
			drawmain();
			return;
		}
		strcpy(path,temp);
		clrscr();
		drawmain();
}
Hnode* close(Hnode *hnode,int *saveflags,int *textflags)
{
	if (textflags == 0)
	{
		clrscr();
		drawmain();
		return hnode;
	}
	else if (saveflags == 0)
	{
		clrscr();
		drawmain();
		window(2, 3, 79, 24);
		textbackground(BLUE);
		cprintf("your file is not save,please y to continue\n\r");
		if (getch() == 'y')
		{
			clrscr();
			ClearLists(hnode);
			hnode = (Hnode*)malloc(sizeof(Hnode));
			*textflags = 0;
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
		hnode = (Hnode*)malloc(sizeof(Hnode));
		*textflags = 0;
		drawmain();
		return hnode;
	}
}