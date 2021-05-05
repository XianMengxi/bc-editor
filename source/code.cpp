#include"code.h"
 /*
 *@name:code
 *@msg:完成括号匹配与自动缩进
 *@param:{Hnode *}hnode 链表头
 *@param:{Cursornode *}cursornode 光标位置
 *@param:{int}flag 表示括号匹配的类型
 *@return:{void}
*/
void code (Hnode *hnode,Cursornode *cursornode,int flag)
{
	Node *node;
	Node *node_b=cursornode->nownode;
	Hnode *hnode_b=cursornode->nowhnode;
	node=hnode_b->head;

	static flag2 = 0;
	int i = 1;//从第一个就相等开始（进不去循环
	int j, k;

	int flag1 = 0;//判断是否是在表头，以矫正误差

	switch(flag)
	{
		case 0://如果监测到按下了“{”，则调用
		
			if (node_b == NULL)
			{
				flag1 = 1;
				flag2++;
			}
			AddNode(cursornode, '{');
			while (node->next != node_b->next)
			{
				i++;
				node = node->next;
			}//得到{所在的node是该行的第几个

			AddHnode(hnode,cursornode);
			node=hnode_b->next->head;
			if (flag1 != 1)
			{
				for (j = 0; j < i; j++)
				{
					AddNode(cursornode, ' ');

				}
			}
			AddNode(cursornode,'}');
			if (flag1 == 1)
			{
				Cursormove(hnode, cursornode, LEFT);
			}
			
			Cursormove(hnode,cursornode,UP);
			Cursormove(hnode, cursornode, RIGHT);

			//if(flag1==1&&flag2!=1)
			//Cursormove(hnode, cursornode, UP);

				break;
		case 1://如果检测到按下enter键 
			
			AddHnode(hnode,cursornode);
			if(node_b->chr=='{'&&(node_b->next->chr!='}'))
			{
				while (node->next != node_b->next)
				{
					i++;
					node = node->next;
				}//得到{所在的node是该行的第几个
				//AddHnode(cursornode, hnode);
				for (j = 0; j < i+4-1; j++)
				{
					AddNode(cursornode,' ');
				}	
			}
			break;
		case 2://如果监测到按下了“(”，则调用
			AddNode(cursornode, '(');
			
			AddNode(cursornode, ')');
			Cursormove(hnode, cursornode, LEFT);

			break;
		case 3://如果监测到按下了“[”，则调用
			AddNode(cursornode, '[');

			AddNode(cursornode, ']');
			Cursormove(hnode, cursornode, LEFT);

			break;
		case 4://如果监测到按下了“\'”，则调用
			AddNode(cursornode,'\'');
			AddNode(cursornode, '\'');
			Cursormove(hnode, cursornode, LEFT);
			break;
		case 5://如果监测到按下了“\”"，则调用
			AddNode(cursornode, '\"');
			AddNode(cursornode, '\"');
			Cursormove(hnode, cursornode, LEFT);
			break;
	
	}
}


