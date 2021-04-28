#include"define.h"
#include"function.h"
#include"key.h"
//#include<conio.h>
 
void code (Hnode *hnode,Cursornode *cursornode,int flag)
{
	Node *node;
	Node *node_b=cursornode->nownode;
	Hnode *hnode_b=cursornode->nowhnode;
	node=hnode_b->head;


	int i = 1;//从第一个就相等开始（进不去循环
	int j, k;

	int flag1 = 0;
	if (node == node_b )
	{
		flag1 = 1;
	}

	
	switch(flag)
	{
		case 0://如果监测到按下了“{”，则调用
		
			AddNode(cursornode, '{');
			while (node->next != node_b->next)
			{
				/*if (node->chr != ' ')//如果输入的{之前有非空格字符
				{
					AddNode(cursornode, '}');
					Cursormove(hnode, cursornode, LEFT);
					return;
				}*/
				i++;
				node = node->next;
			}//得到{所在的node是该行的第几个

		
			AddHnode(cursornode,hnode);
			node=hnode_b->next->head;
			//void AddNode(Cursornode *cursornode, unsigned short ch) //添加节点
			//if (flag1 == 0)
			//{
				for (j = 0; j < i; j++)
				{
					AddNode(cursornode, ' ');
					//Hnode *AddHnode(Cursornode *cursornode,Hnode*hnode_head)

				}
			//}
			AddNode(cursornode,'}');
			if (flag1 == 1)
			{
				Cursormove(hnode, cursornode, LEFT);
				DeleteNode(hnode, cursornode);
			}
			Cursormove(hnode,cursornode,UP);
			if(flag1!=1)
			Cursormove(hnode, cursornode, RIGHT);

				break;
		case 1://如果检测到按下enter键 
			
			AddHnode(cursornode,hnode); 
			if(node_b->chr=='{'&&(node_b->next->chr!='}'))
			{
				while (node->next != node_b->next)
				{
					i++;
					node = node->next;
				}//得到{所在的node是该行的第几个
				//AddHnode(cursornode, hnode);
				for (j = 0; j < i+4; j++)
				{
					//Cursormove(hnode, cursornode, RIGHT);
					//Hnode *AddHnode(Cursornode *cursornode,Hnode*hnode_head)
					AddNode(cursornode,' ');
				}
				//Cursormove(hnode, cursornode, UP);
				//for (j = 0; j < 4; j++)
				//{
					//Cursormove(hnode, cursornode, RIGHT);//这部分不知道为啥没起作用
				//	AddNode(cursornode,' ');
				//}

				
			}
			break;
		case 2://如果监测到按下了“(”，则调用
			AddNode(cursornode, '(');
			
			AddNode(cursornode, ')');
			Cursormove(hnode, cursornode, LEFT);

			break;
		case 3:
			AddNode(cursornode, '[');

			AddNode(cursornode, ']');
			Cursormove(hnode, cursornode, LEFT);

			break;

	//AddHnode(cursornode,hnode_head);
	//Hnode *AddHnode(Cursornode *cursornode,Hnode*hnode_head)//返回值为原来的第一行 
	
	}
}


