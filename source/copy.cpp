#include"copy.h"
#include"code.h"
#include"menu.h"
Cursornode choose(Hnode *hnode ,Cursornode *cursornode,short key,Offset *offset)
{
	unsigned short c=0;
	unsigned short d;
	Cursornode cursornode_temp1 = *cursornode;
	Cursornode cursornode_temp2 = *cursornode;
	if (key == CL || key == CR || key ==CU || key == CD)
	{
		show_choose(cursornode_temp1, cursornode_temp2);
		printlist(hnode,cursornode,offset);
		find_cursor(hnode,cursornode,offset);
		d=(bioskey(2)&0x04);
		while (d==0x04)
		{
            if(bioskey(1))
			c=bioskey(0);
			else
			c=0;
			if (c == CL || c == CR || c ==CU || c == CD)
			{
				int move=0;
				if (c == CL)
				{
					move = LEFT;
				}
				else if(c == CR)
				{
					move = RIGHT;
				}
				else if (c == CU)
				{
					move = UP;
				}
				else if(c == CD)
				{
					move = DOWN;
				}
				Cursormove(hnode, cursornode, move);
				cursornode_temp2 = *cursornode;
				recovery(hnode);
				show_choose(cursornode_temp1, cursornode_temp2);
				printlist(hnode,cursornode,offset);
				find_cursor(hnode,cursornode,offset);
			}
			d=(bioskey(2)&0x04);
		}
	}
	printlist(hnode,cursornode,offset);
	find_cursor(hnode,cursornode,offset);
	return cursornode_temp1;
}
void show_choose(Cursornode cursornode_1, Cursornode cursornode_2)
{
	Node *node1,*node2;
	Hnode *hnode1,*hnode2;
	if (judgewhere(cursornode_1, cursornode_2) > 0)
	{
		node1 = cursornode_1.nownode;
		hnode1 = cursornode_1.nowhnode;
		node2 = cursornode_2.nownode;
		hnode2 = cursornode_2.nowhnode;
	}
	else
	{
		node1 = cursornode_2.nownode;
		hnode1 = cursornode_2.nowhnode;
		node2 = cursornode_1.nownode;
		hnode2 = cursornode_1.nowhnode;
	}
	if(node1 == NULL )
	{
		   node1=hnode1->head;
	}
	else if(node1->next!=NULL && node1!=node2)
	{
		node1=node1->next;
	}
	while (hnode1 != hnode2 && hnode1 != NULL)
	{
		while (node1 != NULL)
		{
			    node1->bkflag = 1;
			    node1 = node1->next;
		}
		hnode1 = hnode1->next;
		node1 = hnode1->head;
	}
	if(node1 == NULL)
	{
	  node1 = hnode1->head;
	}
	while (node1!=node2 && node1!=NULL)
	{
		node1->bkflag = 1;
		node1 = node1->next;
	}
	node1->bkflag = 1;
}
int judgewhere(Cursornode cursornode_temp1, Cursornode cursornode_temp2)
{
	Cursornode cursornode_temp;
	Node *node;
	Hnode *temp=cursornode_temp1.nowhnode;
	if(temp != cursornode_temp2.nowhnode)
	{
		while(temp!=cursornode_temp2.nowhnode &&temp!=NULL)
		{
		   temp=temp->next;
		}
		if(temp==NULL)
		{
		  return -1;
		}
		else
		{
		  return 1;
		}
	}

	else if (cursornode_temp1.nownode == cursornode_temp2.nownode)
	{
		return 1;
	}
		else if (cursornode_temp1.nownode == NULL)
		{
			return 1;
		}
		else if (cursornode_temp2.nownode == NULL)
		{
			return -1;
		}
	else
	{
		node = cursornode_temp1.nowhnode->head;
		while (node != cursornode_temp1.nownode && node != cursornode_temp2.nownode)
		{
			node = node->next;
		}
		if (node == cursornode_temp1.nownode)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
}
void recovery(Hnode *hnode)
{
	Hnode *hnode_temp = hnode;
	Node *node;
	while (hnode_temp != NULL)
	{
		node = hnode_temp->head;
		while (node != NULL)
		{
			node->bkflag = 0;
			node = node->next;
		}
		hnode_temp = hnode_temp->next;
	}
}
//放进剪贴板
void putclip(Hnode *hnode, Clipboard *clipboard)
{
	Node *node;
	Hnode *hnode_temp=hnode;
	char *temp;
	if (clipboard->clipboard != NULL)
	{
		free(clipboard->clipboard);
		clipboard->clipboard = NULL;
	}
	count(hnode, clipboard);
	clipboard->clipboard = (char*)malloc((clipboard->num + 1) * sizeof(char));
	memset(clipboard->clipboard, '\0', (clipboard->num + 1) * sizeof(char));
	temp = clipboard->clipboard;
	while (hnode_temp != NULL)
	{
		node = hnode_temp->head;
		while (node != NULL)
		{
			if (node->bkflag == 1)
			{
				*temp = node->chr;
				temp++;
			}
			node = node->next;
		}
		hnode_temp = hnode_temp->next;
		if (hnode_temp != NULL && hnode_temp->head->bkflag == 1)
		{
			*temp = '\n';
			temp++;
		}
	}
	drawmain();
}
void count(Hnode *hnode, Clipboard *clipboard)
{
	Hnode *temp = hnode;
	Node *node;
	clipboard->num = 0;
	while (temp != NULL)
	{
		node = temp->head;
		while (node != NULL)
		{
			if (node->bkflag == 1)
			{
				clipboard->num++;
			}
			node = node->next;
		}
		temp = temp->next;
		if (temp != NULL && temp->head->bkflag == 1)
		{
			clipboard->num++;
		}
	}
}
//粘贴
void paste(Hnode *hnode, Cursornode *cursornode, Clipboard *clipboard)
{
	char *temp = clipboard->clipboard;
	while (temp != NULL && *temp != '\0')
	{
		if(*temp=='\n'||*temp=='\r')
		{
		  code(hnode,cursornode,1);
		}
		else
		{
		   AddNode(cursornode, *temp);
		}
		temp++ ;
	}
}
//剪切
void copy(Hnode *hnode,Cursornode *cursornode,Clipboard *clipboard)
{
	Hnode *temp = hnode;
	Node *node;
	putclip(hnode,clipboard);
	while (temp != NULL)
	{
		node = temp->head;
		while (node != NULL)
		{
			if (node->bkflag == 1)
			{
				cursornode->nowhnode = temp;
				cursornode->nownode = node;
			}
			node = node->next;
		}
		temp = temp->next;
	}
	while (cursornode->nownode->bkflag == 1)
	{
		DeleteNode(hnode, cursornode);
		if(cursornode->nownode==NULL)
		{
		   DeleteNode(hnode,cursornode);
        }
	}
	clrscr();
	drawmain();
}