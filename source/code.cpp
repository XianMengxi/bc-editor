#include"code.h"
 /*
 *@name:code
 *@msg:�������ƥ�����Զ�����
 *@param:{Hnode *}hnode ����ͷ
 *@param:{Cursornode *}cursornode ���λ��
 *@param:{int}flag ��ʾ����ƥ�������
 *@return:{void}
*/
void code (Hnode *hnode,Cursornode *cursornode,int flag)
{
	Node *node;
	Node *node_b=cursornode->nownode;
	Hnode *hnode_b=cursornode->nowhnode;
	node=hnode_b->head;

	static flag2 = 0;
	int i = 1;//�ӵ�һ������ȿ�ʼ������ȥѭ��
	int j, k;

	int flag1 = 0;//�ж��Ƿ����ڱ�ͷ���Խ������

	switch(flag)
	{
		case 0://�����⵽�����ˡ�{���������
		
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
			}//�õ�{���ڵ�node�Ǹ��еĵڼ���

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
		case 1://�����⵽����enter�� 
			
			AddHnode(hnode,cursornode);
			if(node_b->chr=='{'&&(node_b->next->chr!='}'))
			{
				while (node->next != node_b->next)
				{
					i++;
					node = node->next;
				}//�õ�{���ڵ�node�Ǹ��еĵڼ���
				//AddHnode(cursornode, hnode);
				for (j = 0; j < i+4-1; j++)
				{
					AddNode(cursornode,' ');
				}	
			}
			break;
		case 2://�����⵽�����ˡ�(���������
			AddNode(cursornode, '(');
			
			AddNode(cursornode, ')');
			Cursormove(hnode, cursornode, LEFT);

			break;
		case 3://�����⵽�����ˡ�[���������
			AddNode(cursornode, '[');

			AddNode(cursornode, ']');
			Cursormove(hnode, cursornode, LEFT);

			break;
		case 4://�����⵽�����ˡ�\'���������
			AddNode(cursornode,'\'');
			AddNode(cursornode, '\'');
			Cursormove(hnode, cursornode, LEFT);
			break;
		case 5://�����⵽�����ˡ�\��"�������
			AddNode(cursornode, '\"');
			AddNode(cursornode, '\"');
			Cursormove(hnode, cursornode, LEFT);
			break;
	
	}
}


