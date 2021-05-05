#include"compile.h"
/*
 *@name:complie
 *@msg:��ɲ��ֵı��빦��
 *@param:{Hnode *}hnode ����ͷ
 *@param:{Cursornode *}cursornode ���λ��
 *@param:{int}flag ��ʾ��������
 *@param:{int}flag_c ��ʾͼ�ν��滹�ǿ���̨
 *@param:{char}ch1�������ַ�
 *@param:{char}ch2
 *@return:{int}���ر����� ���Ƿ��ִ���
*/
int complie(Hnode* hnode,Cursornode * cursornode, int flag,int flag_c,char ch1,char ch2)
{
	Node* node;
	int i = 0;
	int j = 0;
	switch (flag)
	{
	case 0://��⼸��ƥ��
		while (hnode != NULL)
		{
			node = hnode->head;
			while (node != NULL)
			{
				if (node->chr == ch1)
				{
					i++;
				}
				else if (node->chr == ch2)
				{
					j++;
				}
				node=node->next;
			}
			hnode = hnode->next;
		}
		if (flag_c == 0)//����̨������
		{
			if (i != j)
			{
				drawmain();
				window(2, 3, 79, 24);
			
				textbackground(BLUE);
				textcolor(WHITE);
				cprintf("The number of %c and %c does not match\n",ch1,ch2);
				cprintf("enter y to continue");
				while (getch() != 'y')
				{
					;
				}
			}
			drawmain();
		}
		else if (flag_c == 1)
		{
			if (i != j)
			{
				return 1;//���Ĳ��ֺ͵��ȷ���Ĳ�����������
			}
		}
		return 0;


	case 3://�������ƥ��
		while (hnode != NULL)
		{
			node = hnode->head;
			while (node != NULL)
			{
				if (node->chr == ch1)
				{
					i++;
				}
				node = node->next;
			}
			hnode = hnode->next;
		}
		if (flag_c == 0)
		{
			if (i % 2 == 1)
			{
				drawmain();
				window(2, 3, 79, 24);
				textbackground(BLUE);
				textcolor(WHITE);
				cprintf("The number of   %c  and  %c   does not match\n",ch1,ch2);
				cprintf("enter y to continue");
				while (getch() != 'y')
				{
					;
				}
			}
			drawmain();
		}
		else if (flag_c == 1)
		{
			if (i%2==1)
			{
				return 1;//���Ĳ��ֺ͵��ȷ���Ĳ�����������
			}
		}
		return 0;
	case 5://�������main����
		if (high_li(hnode, cursornode, "main",flag_c) == 0)
		{
			if (flag_c == 0)
			{
				drawmain();
				window(2, 3, 79, 24);
				textbackground(BLUE);
				textcolor(WHITE);
				cprintf("Don't find \'main\'\n");
				cprintf("enter y to continue");
				while (getch() != 'y')
				{
					;
				}
				drawmain();
			}
			else if (flag_c == 1)
			{
				return 1;
			}
		}
		return 0;
	}
	return 0;
}
