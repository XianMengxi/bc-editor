#include"define.h"
#include"menu.h"
#include"function.h"
#include"mouse.h"
#define WIDTH 75
#define HEIGHT 21
Hnode* InitList(Hnode *hnode,Cursornode *cursornode,int *saveflags,int *textflags) //��ʼ������
{
	if (*saveflags == 0)  //�ļ�δ����
	{
		clrscr();
		drawmain();
		window(5, 3, 80, 23);
		textbackground(BLUE);
		cprintf("file not save please enter y to continue");
		if (getch() != 'y')
		{
			drawmain();
			return hnode;
		}
		else 
		{
			ClearLists(hnode);
			clrscr();
			*saveflags=1;
			*textflags=1;
			hnode = (Hnode*)malloc(sizeof(Hnode));
			drawmain();
		}
		//yes no
	}
	else if(*textflags == 1&& *saveflags==1) //�ļ��ѱ��棬����ǰ���ļ�
	{
		ClearLists(hnode);
		clrscr();
		hnode = (Hnode*)malloc(sizeof(Hnode));
		drawmain();
	}
	//��Ϊ��ʼ������
	hnode->next = NULL;
	hnode->head = NULL;
	hnode->cols = 0;
	cursornode->nowhnode = hnode;
	cursornode->nownode = NULL;
	*textflags = 1;
	drawmain();
	return hnode;
}
int Judgetype(unsigned short ch) //�ж��ַ�����
{
	if ((ch >= 'A'&&ch <= 'Z') || (ch >= 'a'&&ch <= 'z')) //��ĸ
	{
		return 2;
	}
	else if (ch >= '0'&&ch <= '9') //����
	{
		return 1;
	}
	else if (ch == '+' || ch == '-' || ch == '<' || ch == '=' || ch == '>'
		       || ch=='*'|| ch=='\\'|| ch=='!') //��ѧ����
	{
		return 3;
	}
	else //����
	{
		return 4;
	}
}
void AddNode(Cursornode *cursornode, unsigned short ch) //���ӽڵ�
{
	Node *node = (Node*)malloc(sizeof(Node));
	node->chr = ch;
	node->type = Judgetype(ch);
	node->bkflag=0;
	cursornode->nowhnode->cols++;
	//��Ӧ����Ϊ�������
	if (cursornode->nownode == NULL&&cursornode->nowhnode->head==NULL)
	{
		node->next = NULL;
		cursornode->nowhnode->head = node;
		cursornode->nownode = node;
	}
	//��Ӧ���в�Ϊ�� �����������λ
	else if (cursornode->nownode == NULL && cursornode->nowhnode->head != NULL)
	{
		node->next = cursornode->nowhnode->head;
		cursornode->nowhnode->head = node;
		cursornode->nownode = node;
	}
	//��Ӧβ�����
	else if (cursornode->nownode->next == NULL)
	{
		node->next = NULL;
		cursornode->nownode->next = node;
		cursornode->nownode = node;
	}
	//��Ӧ���м�������
	else
	{
		node->next = cursornode->nownode->next;
		cursornode->nownode->next = node;
		cursornode->nownode = node;
	}	
}
Hnode *AddHnode(Cursornode *cursornode,Hnode*hnode_head)
{
	Hnode *hnode = (Hnode*)malloc(sizeof(Hnode));
	hnode->cols = 0;
	hnode->head = NULL;
	//ֱ���ں������ͷ�ڵ�
	if (cursornode->nownode != NULL)
	{
		Node *node = cursornode->nownode->next;
		Cursornode cursornode_temp1;
		cursornode_temp1 = *cursornode;
		hnode->next = cursornode->nowhnode->next;
		cursornode->nowhnode->next = hnode;
		cursornode->nowhnode = hnode;
		cursornode->nownode = NULL;
		while (node != NULL)
		{
			AddNode(cursornode, node->chr);
			node = node->next;
		}
		while (cursornode_temp1.nownode->next != NULL)
		{
			cursornode_temp1.nownode = cursornode_temp1.nownode->next;
			DeleteNode(hnode_head, &cursornode_temp1);
		}
		cursornode->nownode = NULL;
		return hnode_head;
	}
	//��ͷ����ͷ�ڵ�
	else if(cursornode->nowhnode == hnode_head && cursornode->nownode==NULL)
	{
		hnode->next = cursornode->nowhnode;
		cursornode->nowhnode = hnode;
		cursornode->nownode = NULL;
		cursornode->nowhnode=hnode->next;
		return hnode;
	}
	//���м�ǰ����ͷ�ڵ�
	else 
	{
		Hnode *hnode_temp = hnode_head;
		while (hnode_temp->next != cursornode->nowhnode)
		{
			hnode_temp=hnode_temp->next;
		}
		hnode->next = hnode_temp->next;
		hnode_temp->next = hnode;
		cursornode->nowhnode = hnode -> next;
		cursornode->nownode = NULL;
		return hnode_head;
	}
}
//��������е�����
void ClearLists(Hnode *Hhead)
{
	Node *node,*temp;
	Hnode *Htemp;
	temp = NULL;
	while (Hhead!= NULL)
	{
		Htemp = Hhead->next;
		node = Hhead->head;
		while (node != NULL)
		{
			temp = node->next;
			free (node);
			node = temp;
		}
		free(Hhead);
		Hhead = Htemp;
	}
	node = NULL;
	Hhead = NULL;
}
//��ӡ��������
void printlist(Hnode *hnode,Cursornode *cursornode,Offset *offset)
{
	Node *node;
	Hnode *temp;
	int cols,rows;
	int x,y;
	cols=1;
	rows=1;
	int print_row=1;
	find_offset(hnode, cursornode, offset);
	where_cursor(hnode,cursornode,&x,&y);
	for (int i = 1; i < offset->y && hnode != NULL; i++)
	{
		hnode = hnode->next;
	}
	temp=hnode;
	textbackground(3);
	textcolor(4);
	window(2,3,4,23);
	clrscr();
	hide_mouse();
	while(temp!=NULL && print_row<= HEIGHT)
	{
	  cprintf("%d",print_row+offset->y-1);
	  if(print_row !=HEIGHT)
	  {
		cprintf("\n\r");
	  }
	  temp=temp->next;
	  print_row++;
	}
	textbackground(BLUE);
	window(5,3,79,23);
	clrscr();
    window(5,3,80,23);
	while (hnode != NULL && rows<=HEIGHT)
	{
		node = hnode->head;
		for (int j = 1; j < offset->x && node != NULL; j++)
		{
			node = node->next;
		}
		while (node != NULL && cols<=WIDTH)
		{
			if(node->bkflag==1)
			{
			   textbackground(2);
			}
			else if(node->bkflag==2)
			{
			   textbackground(0);
			}
			else
			{
			   textbackground(BLUE);
			}
			textcolor(node->type+1);
			cprintf("%c", node->chr);
			node=node->next;
			cols++;
		}
		if ( rows<HEIGHT)
		{
			cprintf("\n");
			cprintf("\r");
		}
		hnode=hnode->next;
		rows++;
		cols=1;
	}
	window(1,25,70,25);
	textbackground(7);
	clrscr();
	textcolor(BLACK);
	gotoxy(6,1);
	cprintf("Row:%d",y);
	gotoxy(13,1);
	cprintf("Col:%d",x);
	window(5,3,80,23);
	find_cursor(hnode,cursornode,offset);
	show_mouse();
}
//ֱ��ɾ��ͷ�ڵ㼰��������
Hnode* DeleteHnode(Hnode *hnode,Cursornode *cursornode)
{
	Node *node, *temp;
	Hnode *htemp;
	if (cursornode-> nowhnode== hnode)     //��ͷɾ��һ��
	{
		node = cursornode->nowhnode->head;
		    while (node != NULL)
		    {
				temp = node->next;
				free(node);
				node = temp;
		    }
		node = NULL;
		cursornode->nowhnode = cursornode->nowhnode->next;
		cursornode->nownode = NULL;
		free(hnode);
		hnode = cursornode->nowhnode;
		htemp = hnode;
		return hnode;
	}
	//���м�ɾ��һ��
	else
	{
		htemp = hnode;
		while (htemp!=NULL &&htemp->next != cursornode->nowhnode)
		{
			htemp = htemp->next;
		}
		node = cursornode->nowhnode->head;
		while (node != NULL)
		{
			temp = node->next;
			free(node);
			node = temp;
		}
		node = NULL;
		cursornode->nowhnode = htemp;
		htemp = htemp->next;
		cursornode->nowhnode->next = cursornode->nowhnode->next->next;
		free(htemp);
		cursornode->nownode = cursornode->nowhnode->head;
		while (cursornode->nownode!=NULL&&cursornode->nownode->next != NULL)
		{
			cursornode->nownode = cursornode->nownode->next;
		}
		return hnode;
	}
}
//ɾ���ڵ�
void DeleteNode(Hnode *hnodel,Cursornode *cursornode)
{
	Node *node=cursornode->nowhnode->head;
	Hnode *hnode = hnodel;
	//��Ӧ����Ϊ�յ��������һ�У�
	if (hnode == cursornode->nowhnode&&node == NULL)
	{

	}
	//��Ӧ����Ϊ���Ҳ�Ϊ��һ��
	else if (node == NULL)
	{
		DeleteHnode(hnode, cursornode);
		return;
	}
	//��Ӧɾ�����е�һ���ڵ�״̬
	else if (node == cursornode->nownode)
	{
		cursornode->nownode = cursornode->nownode->next;
		cursornode->nowhnode->head = cursornode->nownode;
		cursornode->nownode = NULL;
		free(node);
		node = NULL;
		cursornode->nowhnode->cols--;
	}
	//��Ӧɾ���м�ڵ�״��
	else if(cursornode->nownode!=NULL)
	{
		while (node != NULL && node->next != cursornode->nownode)
		{
			node = node->next;
		}   
		cursornode->nownode = cursornode->nownode->next;
		free(node->next);
		node->next = cursornode->nownode;
		cursornode->nownode = node;
		cursornode->nowhnode->cols--;
	}
	//��Ӧ�ǵ�һ���ڵ�һ��ɾ�����⣨�漰���У�
	else if(cursornode->nowhnode != hnode)
	{
		Cursornode temp;
		Node *node = cursornode->nowhnode->head;
		while (hnode->next != cursornode->nowhnode)
		{
			hnode = hnode->next;
		}
		cursornode->nowhnode = hnode;
		cursornode->nownode = cursornode->nowhnode->head;
		while (cursornode->nownode!=NULL&&cursornode->nownode->next != NULL)
		{
			cursornode->nownode = cursornode->nownode->next;
		}
		temp = *cursornode;
		while (node != NULL)
		{
			AddNode(cursornode, node->chr);
			node = node->next;
		}
		cursornode->nowhnode = hnode->next;
		cursornode->nownode = cursornode->nowhnode->head;
		DeleteHnode(hnodel,cursornode);
		*cursornode = temp;
	}
}
void find_offset(Hnode *hnode, Cursornode *cursornode, Offset *offset)
{
	int cursor_x, cursor_y;
	where_cursor(hnode, cursornode, &cursor_x, &cursor_y);
	if (cursor_x < offset->x)
	{
		offset->x = cursor_x;
	}
	if (cursor_y < offset->y)
	{
		offset->y = cursor_y;
	}
	if (cursor_x >= offset->x + WIDTH)
	{
		offset->x = cursor_x - WIDTH + 1 ;
	}
	if (cursor_y >= offset->y + HEIGHT)
	{
		offset->y = cursor_y - HEIGHT + 1  ;
	}
	if(cursornode->nownode!=NULL &&cursornode->nownode->next==NULL && cursor_x >=WIDTH)
	{
		offset->x=cursor_x-WIDTH+1;
	}
}

