#include"define.h"
#include"function.h"
#include"key.h"
#include"mouse.h"
#include"copy.h"
//���ҹ�꣬������Ƶ���x,y)λ��
void find_location(Hnode *hnode, Cursornode *cursornode, int x, int y)
{
	Node *node;
	int i;
	for (i = 1; i < x && hnode->next != NULL; i++)
	{
		hnode = hnode->next;
	}
	if (y == 1)
	{
		cursornode->nowhnode = hnode;
		cursornode->nownode = NULL;
	}
	else if ((node = hnode->head) != NULL)
	{
		for (i = 2; i < y&&node != NULL &&node->next!=NULL; i++)
		{
			node = node->next;
		}
			cursornode->nowhnode = hnode;
			cursornode->nownode = node;
	}
}
//���ҹ�꣬������Ƶ���x,y)λ��
void where_cursor(Hnode *hnode, Cursornode *cursornode, int *cursor_x, int *cursor_y)
{
	int x = 1;
	int y = 1;
	Node  *temp_1=NULL;
	while (hnode != NULL && hnode != cursornode->nowhnode)
	{
		y++;
		hnode = hnode->next;
	}
	if (cursornode->nownode != NULL)
	{
		temp_1 = cursornode->nowhnode->head;
		x++;
	}
	while (temp_1 != NULL && temp_1 != cursornode->nownode)
	{
		temp_1 = temp_1->next;
		x++;
	}
	*cursor_x = x;
	*cursor_y = y;
}
void find_cursor(Hnode *hnode ,Cursornode *cursornode,Offset *offset)
{
	window(5,3,79,23);
	int cursor_x, cursor_y;
	where_cursor(hnode, cursornode, &cursor_x, &cursor_y);
	find_offset(hnode, cursornode, offset);
	gotoxy(cursor_x - offset->x+1, cursor_y - offset->y+1);
}
void Cursormove(Hnode *hnode, Cursornode *cursornode, int direction) //�����λ�ý��������ƶ�
{
	if (direction == RIGHT) //��Ӧ�����ƶ�
	{
		//δ���еľ�ͷ
		if (cursornode->nownode == NULL)
		{
			cursornode->nownode = cursornode->nowhnode->head;
		}
		else if (cursornode->nownode->next != NULL)
		{
			cursornode->nownode = cursornode->nownode->next;
		}
		else if (cursornode->nowhnode->next != NULL)
		{
			cursornode->nowhnode = cursornode->nowhnode->next;
			cursornode->nownode = NULL;
		}
	}
	else if (direction == LEFT) //��Ӧ�����ƶ�
	{
		Node *node = cursornode->nowhnode->head;
                                   //λ�ڸ�����ǰλ��
                                   if (cursornode->nownode == NULL)
		{
			if (cursornode->nowhnode != hnode)
			{
				while (hnode->next != cursornode->nowhnode)
				{
					hnode = hnode->next;
				}
				cursornode->nowhnode = hnode; 
				cursornode->nownode=cursornode->nowhnode->head;
                                                                     while(cursornode->nownode!=NULL&&cursornode->nownode->next!=NULL)
                                                                      {
                                                                                       cursornode->nownode=cursornode->nownode->next;
                                                                       }
			}
		}
		else if (node != cursornode->nownode)
		{
			while (node->next != cursornode->nownode)
			{
				node = node->next;
			}
			cursornode->nownode = node;
		}
                                   else if(node==cursornode->nownode)
                                   {
                                                    cursornode->nownode=NULL;
                                   }
	}
	else if (direction == DOWN) //��Ӧ�����ƶ�
	{
		if (cursornode->nowhnode->next == NULL)
		{

		}
		else
		{
			hnode = cursornode->nowhnode->next;
			Node *node_cur, *node_temp;
			node_cur = cursornode->nowhnode->head;
			node_temp = hnode->head;
			while (node_cur != cursornode->nownode)
			{
				node_cur = node_cur->next;
				if (node_temp->next->next != NULL)
				{
					node_temp = node_temp->next;
				}
				else
				{

				}
			}
			cursornode->nowhnode = hnode;
			cursornode->nownode = node_temp;
		}
	}
	else  //��Ӧ�����ƶ�
	{
		if (cursornode->nowhnode == hnode)
		{

		}
		else
		{
			while (hnode->next != cursornode->nowhnode)
			{
				hnode = hnode->next;
			}
			Node *node_cur, *node_temp;
			node_cur = cursornode->nowhnode->head;
			node_temp = hnode->head;
			while (node_cur != cursornode->nownode)
			{
				node_cur = node_cur->next;
				if (node_temp->next->next != NULL)
				{
					node_temp = node_temp->next;
				}
				else
				{

				}
			}
			cursornode->nowhnode = hnode;
			cursornode->nownode = node_temp;
		}
	}
}
void mouse_click(Hnode *hnode,Cursornode *cursornode,Offset *offset)
{
	getmouse();
	if (M_s==1)
	{
		unsigned short x = M_x/8+1;
		unsigned short y = M_y/8+1;
		if (x >= 5 && x <= 80 && y >= 3 && y <= 23)
		{
			find_offset(hnode, cursornode, offset);
			find_location(hnode, cursornode, y-3+offset->y, x-5+offset->x);
			printlist(hnode,cursornode,offset);
			find_cursor(hnode,cursornode,offset);
		}
		if(cursornode->nownode->bkflag!=0)
		{
			recovery(hnode);
		}
	}
}
void mouse_choose(Hnode *hnode,Cursornode *cursornode,Offset *offset)
{
	mouse_click(hnode,cursornode,offset);
	Cursornode cursornode_temp1 = *cursornode;
	Cursornode cursornode_temp2 = *cursornode;
	unsigned short x = M_x/8+1;
	unsigned short y = M_y/8+1;
	unsigned short x_ = x;
	unsigned short y_ = y;
			while (M_s==1 && M_sc<=0 && x >= 5 && x <= 80 && y >= 3 && y <= 23)
			{
				if(x_==x &&y_==y)
				{

				}
				else
				{
					find_location(hnode, cursornode, y-3+offset->y, x-5+offset->x);
					cursornode_temp2 = *cursornode;
					recovery(hnode);
					show_choose(cursornode_temp1, cursornode_temp2);
					printlist(hnode,cursornode,offset);
					find_cursor(hnode,cursornode,offset);
				}
					getmouse();
					x_=x;
					y_=y;
					x = M_x/8+1;
					y = M_y/8+1;
			}
		printlist(hnode,cursornode,offset);
		find_cursor(hnode,cursornode,offset);
}
