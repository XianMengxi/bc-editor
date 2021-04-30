#include"chinese.h"
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include"mouse.h"
#include"hanzi.h"
#include"define.h"
#include"menu.h"
#include"key.h"
#include"function.h"
#include"high_li.h"
#include"code.h"
int utf_8_to_16(Node *node, unsigned short *uni)
{
	int i = 0;
	char utf8[4];
	while (i <= 2)
	{
		if (node != NULL)
		{
			utf8[i] = node->chr;
			node = node->next;
		}
		else
		{
			return 0;
		}
		i++;
	}
	utf8[3] = '\0';
	*uni = ((utf8[0] & 0x0F) << 12) + ((utf8[1] & 0x3F) << 6) + (utf8[2] & 0x3F);
	return 1;
}
//���ڴ�ӡ���ĺ��� ����p2,hr+1ʱΪ��ӡ�����ҷ�ҳ�汾������p1��hrʱΪ�������ҷ�ҳ�汾������
int chinese (Hnode * hnode,Cursornode * cursornode,int h,int *pcolor,int textflags)
{
	Hnode * p;
	p = hnode;//��¼��ʼֵ

	Node *node;
	Node *node1;
	Node *node2;
//	int hr_p = 0;

	//Hnode *hnode_pc = NULL;//���ڼ����壬ΪNULLʱ��������û�ж���
	//���ڼ��а�
	//int flag_pc=0;
	//Hnode *pc;

	Hnode *hnode_cc = NULL;
	Node *node_ccp = NULL;
	Node *node_cc = NULL;

	Hnode *hnode_cb=NULL;
//	Hnode *hnode_b=NULL;
//	Hnode *hnode_cc2 = NULL;
//	Hnode *hnode_cc3 = NULL;
	//Hnode *hnode_cc3p = NULL;
//	Node *node_cc3p = NULL;
//	Node *node_ccp2 = NULL;
//	Node *node_ccp3 = NULL;
//	Node *node_cc2 = NULL;
//	Node *node_cc3 = NULL;

 //	Cursornode *cursornode_c;
//	Cursornode *cursornode_c2;

 //	Cursornode *cursornode_c1=(Cursornode *)malloc(sizeof(Cursornode));

	Hnode *hnode_c = (Hnode*)malloc(sizeof(Hnode));
	Hnode *p2 = hnode_c;
	hnode_c->head = (Node *)malloc(sizeof(Node));
	hnode_c->head->next = NULL;//ͷ�ڵ�ָ���ʼ��
	hnode_c->next = NULL;

	Node *node_p = (Node *)malloc(sizeof(Node));//����p�ڵ����ڼ�¼��β�ڵ�
	node_p = hnode_c->head;
	node_p->next = NULL;

	Hnode *hnode_p = (Hnode *)malloc(sizeof(Hnode));
	hnode_p = hnode_c;
	hnode_p->next = NULL;

	//hnode_c->head = node_c;
	//Node *node = (Node*)malloc(sizeof(Node));
 //	int ihz = 0;//������¼�ڵ������;
 //	int ihz_1 = 0;//ѭ�����������ڼӿո����ƶ�����λ��
 //	int ihz_2 = 0;//����ʶ����
 //	int ihz_3 = 0;//���ڼ�¼�ո���

  //	int i_r=0;//��¼�����ı�������
	int shr=0;//��¼������
	int shl=0;//��¼������

	char order[80];
	int o_n = 0;
	Node *node_s;

	//int flag_cc=0;
	int flag_q2 = 0;
	/*while (hnode!=NULL)
	{
		node = hnode->head;
		node_p = hnode_p->head;//Ŀǰ�ҵ�ͷ��ֻ��һ��ͷ��û�����ݣ�

		shl++;
		i_r = 0;

		while (node != NULL)
		{
			ihz++;

			i_r++;
			if (shr < i_r)
			{
				shr = i_r;
			}
			//int utf_8_to_16(Node *node, unsigned short *uni)
			if (ihz_2 == 2 || ihz_2 == 1)//��Ҫ�����������Σ����⺺���ж�ʧ��
			{
				ihz_2--;
			}
			else if (node->chr >= 0x80&&ihz_2==0)//����������,ͨ�����ӿո���������λ��
					{
						if (ihz % 3 == 2)
						{
							ihz_3 = 2;
						}
						else if (ihz % 3 == 0)
						{
							ihz_3 = 1;
						}
						for (ihz_1 = 0; ihz%3!=1&&ihz_1 < ihz_3; ihz_1++)
						{
							node_s = (Node *)malloc(sizeof(Node));
							node_s->chr = ' ';
							node_p->next = node_s;
							node_s->next = NULL;
							node_p = node_s;
						}
						ihz_2 = 2;
						ihz += ihz_3;//��¼��������Ҫ���Ӳ������ո���
						ihz_3 = 0;
					}
			node_s = (Node *)malloc(sizeof(Node));
			node_s->chr = node->chr;
			node_s->type = node->type;
			node_p->next = node_s;
			node_s->next = NULL;
			node_p = node_s;
			node=node->next;
		}

		ihz = 0;
		hnode = hnode->next;
		if (hnode!= NULL)
		{
			Hnode *hnode_s = (Hnode*)malloc(sizeof(Hnode));
			//hnode_s->head = hnode->head;
			hnode_p->next = hnode_s;

			hnode_s->head = (Node *)malloc(sizeof(Node));
			hnode_s->head->next = NULL;
			hnode_s->next = NULL;
			hnode_p = hnode_s;
		}

	}
	*/
	


	int op;//��¼��ֵ
	short op1;

	int hl=0;//��¼���� ��ǰ��ʾ��Ϊ�ڼ���
	int hr = 1;//��¼���� ��ǰ��ʾ��Ϊ�ڼ���

	//int flag_r = 0;//�ж������ƶ�ʱ�Ƿ��������֣��������flag_r�����0
	//int flag_r1 = 0;//�ж����ƶ�ʱ�Ƿ�ͷ
	//int flag_r2 = 0;
	

	int i;//ÿ����ʾ
	int flag_c=0;//��¼���ĸ��˵���
	int flag3_c = 0;//��¼������
	int flag_q = 0;//����ʱ�ж��Ƿ���Ҫ���ȷ��

	int flag_o = 0;//��������ģʽ�������ж�
	int flag_o2 = 0;//�������������Ƿ���ȷ���ж�
	int q;

	int mouse_x;
	int mouse_y;

	//int ic;
	//char buf_c[3];
	//char buf_z[5];
	char* hz_s[] = {
			"YOU16",
			"FS16",
			"HP16",
			"HT16",
			"MBXS16"
	};

	h = ziti_set2();
	int graphdriver=VGA;
	int graphmode=2;
	initgraph(&graphdriver,&graphmode,"C:\\borlandc\\bgi");
	
	//initscreen();
	initmouse(1);
	//static int YOU16FLAG = 0;//
	static FILE* YOU16;//
	
   //	YOU16FLAG = 1;
	sethzmode(YOU16,  hz_s[h]);//��������


	drawmain_c();
	
	/*for(i=0;(i<26)&&hnode!=0;i++)//������ʾ26��
	{
		moveto(16,32+16+i*16);
		printline_chinese(hnode,YOU16,pcolor);
		hnode=hnode->next;
	}*/

	//drawmain_c();
	settextjustify(0, 0);
	settextstyle(0, 0, 1);
	hnode = p;
	p2 =trans(hnode, cursornode, &shl, &shr);
	if (hr < 0)
	{
		hr = 1;
		if (textflags != 0)
			printlist_chinese(p2, pcolor, hl, hr );//Ŀǰ�����hnodeΪp,colorΪpcolor
		probar(hl, shl, hr, shr);
	}
	else
	{
		if (textflags != 0)
			printlist_chinese(p2, pcolor, hl, hr );//Ŀǰ�����hnodeΪp,colorΪpcolor
			//printlist_chinese(p, YOU16, pcolor, hl,hr);//Ŀǰ�����hnodeΪp,colorΪpcolor
		probar(hl, shl, hr, shr);
	}
	printlist_chinese(p2, pcolor, hl, hr);
	
	
	



	while (1)
	{
		
		getmouse();
		mouse_x = M_x;
		mouse_y = M_y;

		if (M_sc<0)
		{
			if (
						flag_q==0  
						&&
						(
							!pd(45, 0, 8 * 80, 16)
						)
						&&
						(
							(flag_c == 1) && !pd(6 * 8 + 4, 80 - (6 + 1) * 8, 88, 7 * 16)
						)
						||
						(
							(flag_c == 2) && !pd(24 * 8 + 4, 80 - (6 + 1) * 8, 80, 7 * 16)
						)
						||
						(
							(flag_c == 3) && !pd(42 * 8 + 4, 80 - (6 + 1) * 8, 80, 5 * 16)&&flag3_c==0// pd(42 * 8 + 4, 80 - 2 * 8, 80, 16)
						)
						||
						(
							(flag_c == 4) && !pd((42+18) * 8 + 4, 80 - (6 + 1) * 8, 80, 4 * 16)// pd(42 * 8 + 4, 80 - 2 * 8, 80, 16)
						)
						||
						(
							(flag3_c == 1)
							&& !pd(42 * 8 + 4, 80 - (6 + 1) * 8, 80, 4 * 16)
							&& !pd(400 - 6 * 8 + (11 * 8), 32 + 16 - 16, 16 * 6, 7 * 16)
						)
						||
						(
							(flag3_c== 2)
							&& !pd(42 * 8 + 4, 80 - (6 + 1) * 8, 80, 4 * 16)
							&& !pd(400 - 6 * 8 + (11 * 8), 32 + 16 + 16 - 16, 6 * 16, 7 * 16)
						)

				)

					{
						flag_c = 0;
						flag3_c = 0;
						drawmain_c();
						hnode = p;
						if (textflags != 0)
						printlist_chinese(p2,  pcolor, hl,hr);//Ŀǰ�����hnodeΪp,colorΪpcolor
						probar(hl, shl, hr, shr);
						/*for (i = 1; i < hl; i++)
							hnode = hnode->next;
						for (i = 0; (i < 27) && hnode != NULL; i++)//������ʾ27��
						{
							moveto(16, 32 + 16 + i * 16);
							printline_chinese(hnode, YOU16,pcolor);
							hnode = hnode->next;
						}*/
					}

			if (flag_c==0&&pd(0, 0, 45, 16))
			{
				unsigned int by_1[4] = { 0x8fd0,0x884c,0x9519,0x8bef };//"���д���"
				unsigned int by_2[2] = { 0x786e,0x5b9a };//"ȷ��
				unsigned int by_3[6] = { 0x7684,0x6570,0x91cf,0x4e0d,0x5339,0x914d };//��������ƥ��
				unsigned int by_4[6] = { 0x7684,0x6570,0x91cf,0x4e0d,0x76f8,0x7b49 };//�����������
				unsigned int by_5[6] = { 0x51fd,0x6570,0x672a,0x88ab,0x627e,0x5230 };//����δ���ҵ�
				unsigned int by_6[5] = { 0x7684,0x6570,0x91cf,0x592a,0x5c11 };//����������
				char by_k[] = {
					'(',')',
					'[',']',
					'{','}'
				};
				char by_k2[] = {
					'\'','\"'
				};
				
				char by_c1[] = { '(',')', '\0'};
				/*char by_c2[] = {'[', ']'};
				char by_c3[] = { '{','}' };
				*/char by_c4[]= { "main" };

				for (i = 0; i < 3; i++)
				{
					q = complie(p2, cursornode, 0, 1, by_k[2 * i], by_k[2 * i + 1]);
					if ( q== 1)
					{
						draw_com();

						put_s_hz(96 + 20, 48 * 3 + 15, by_1, 4, YOU16);
						put_s_hz(320 - 32 - 5 - 10 + 30, 240 + 80 - 40 + 16, by_2, 2, YOU16);
						by_c1[0] = by_k[2 * i];
						by_c1[1] = by_k[2 * i + 1];
						outtextxy(96 + 20 + 20, 48 * 3 + 15 + 32 + 32, by_c1);
						put_s_hz(96 + 20 + 20  +35, 48 * 3 + 15 + 32 + 32, by_3, 6, YOU16);
						flag_q = 1;//ȷ�������
				//		show_mouse();
						while (1)
						{
							getmouse();
							if (M_sc<0&&flag_q == 1 && pd(320 - 32 - 5 - 10, 240 + 80 - 40, 10 * 2 + 37 * 2, 32 + 10))//���ȷ����
							{
								flag_q = 0;
							//	drawmain_c();
							//	printlist_chinese(p2, YOU16, pcolor, hl, hr + 1);
								break;
							}
						}
					}
					q = 0;
				}
				for (i = 0; i < 2; i++)
				{
					q = complie(p2, cursornode, 3, 1,by_k2[i], by_k2[i]);
					{
						if (q == 1)
						{
							draw_com();
							put_s_hz(96 + 20, 48 * 3 + 15, by_1, 4, YOU16);
							put_s_hz(320 - 32 - 5 - 10 + 30, 240 + 80 - 40 + 16, by_2, 2, YOU16);
							by_c1[0] = by_k[i];
							by_c1[1] = by_k[i];
							outtextxy(96 + 20 + 20, 48 * 3 + 15 + 32 + 32, by_c1);
							put_s_hz(96 + 20 + 20 + 35, 48 * 3 + 15 + 32 + 32, by_4, 6, YOU16);
							flag_q = 1;//ȷ�������
							while (1)
							{
								getmouse();
								if (M_sc < 0 && flag_q == 1 && pd(320 - 32 - 5 - 10, 240 + 80 - 40, 10 * 2 + 37 * 2, 32 + 10))//���ȷ����
								{
									flag_q = 0;
									//	drawmain_c();
									//	printlist_chinese(p2, YOU16, pcolor, hl, hr + 1);
									break;
								}
							}
						}
					}
					q = 0;
				}
				q=complie(p2, cursornode, 5,1, '(', ')');
				if (q == 1)
				{
					draw_com();
					put_s_hz(96 + 20, 48 * 3 + 15, by_1, 4, YOU16);
					put_s_hz(320 - 32 - 5 - 10 + 30, 240 + 80 - 40 + 16, by_2, 2, YOU16);
					outtextxy(96 + 20 + 20, 48 * 3 + 15 + 32 + 32, by_c4);
					put_s_hz(96 + 20 + 20 + 35, 48 * 3 + 15 + 32 + 32, by_5, 6, YOU16);
					flag_q = 1;//ȷ�������
					while (1)
					{
						getmouse();
						if (M_sc < 0 && flag_q == 1 && pd(320 - 32 - 5 - 10, 240 + 80 - 40, 10 * 2 + 37 * 2, 32 + 10))//���ȷ����
						{
							flag_q = 0;
							//	drawmain_c();
							//	printlist_chinese(p2, YOU16, pcolor, hl, hr + 1);
							break;
						}
					}
				}
				q = complie(p2, cursornode, 6, 1, '{', '}');
				if (q == 1)
				{
					draw_com();
					put_s_hz(96 + 20, 48 * 3 + 15, by_1, 4, YOU16);
					put_s_hz(320 - 32 - 5 - 10 + 30, 240 + 80 - 40 + 16, by_2, 2, YOU16);
					by_c1[0] = '{';
					by_c1[1] = '}';
					outtextxy(96 + 20 + 20, 48 * 3 + 15 + 32 + 32, by_c1);
					put_s_hz(96 + 20 + 20 + 35, 48 * 3 + 15 + 32 + 32, by_6, 5, YOU16);
					flag_q = 1;//ȷ�������
					while (1)
					{
						getmouse();
						if (M_sc < 0 && flag_q == 1 && pd(320 - 32 - 5 - 10, 240 + 80 - 40, 10 * 2 + 37 * 2, 32 + 10))//���ȷ����
						{
							flag_q = 0;
							//	drawmain_c();
							//	printlist_chinese(p2, YOU16, pcolor, hl, hr + 1);
							break;
						}
					}
				}
				
					unsigned int by_11[] = { 0x63d0,0x793a };//��ʾ
					unsigned int by_22[] = { 0x6682,0x672a,0x627e,0x5230,0x9519,0x8bef };//��δ�ҵ�����
				draw_com();
				put_s_hz(96 + 20, 48 * 3 + 15, by_11, 2, YOU16);
				put_s_hz(320 - 32 - 5 - 10 + 30, 240 + 80 - 40 + 16, by_2, 2, YOU16);
				put_s_hz(96 + 20 + 20 + 35, 48 * 3 + 15 + 32 + 32, by_22, 6, YOU16);
				flag_q = 1;//ȷ�������
				while (1)
				{
					getmouse();
					if (M_sc < 0 && flag_q == 1 && pd(320 - 32 - 5 - 10, 240 + 80 - 40, 10 * 2 + 37 * 2, 32 + 10))//���ȷ����
					{
						flag_q = 0;
						//	drawmain_c();
						//	printlist_chinese(p2, YOU16, pcolor, hl, hr + 1);
						break;
					}
				}
				
				if (textflags != 0)
				{
					printlist_chinese(p2, pcolor, hl, hr );//Ŀǰ�����hnodeΪp,colorΪpcolor

				}
				else
					drawmain_c();
				probar(hl, shl, hr, shr);
				flag_c = 0;
				flag3_c = 0;
				/*ceshi*/
				//draw_com();//������




			}
			if (flag_q == 0 && pd(0, 480 - 20, 10, 480))//���������������ͷ
			{
				//int menu_lr(Hnode *hnode_c, int hr, int hl, int op)//����ֵΪhr,//����ֵΪp2
				hr = menu_cl(p2, hr);//����ֵΪhr,//����ֵΪp2
				if (textflags != 0)
				printlist_chinese(p2,  pcolor, hl, hr );
				probar(hl, shl, hr, shr);
			}
			if (flag_q == 0 && pd(640 - 10, 480 - 20, 640, 480))//�������������Ҽ�ͷ
			{
				hr = menu_cr(p2, hr);//����ֵΪhr,//����ֵΪp2
				if (textflags != 0)
				printlist_chinese(p2,pcolor, hl, hr );
				probar(hl, shl, hr, shr);
			}
		   else	if (flag_q == 0 && pd(0+10, 480 - 20, 640-10, 480))//bar(0, 480 - 20, 640, 480);������Ǻ��������hr���
			{
				hr = (int)((float)(mouse_x - 10) / 600.0*shr);//�����㷨
				if (hr % 3 == 2)
				{
					hr += 2;
				}
				else if (hr % 3 == 0)
				{
					hr += 1;
				}
				if (hr > shr)
				{ 
					if (shr % 3 == 2)
					{
						hr = shr-1;
					}
					if (shr % 3 == 0)
					{
						hr = shr - 2;
					}
					else//shr%3==1
					{
						hr = shr;
					}
				}
				if (hr < 1)
				{
					hr = 1;
				}
				if (textflags != 0)
				printlist_chinese(p2,  pcolor, hl, hr);//Ŀǰ�����hnodeΪp,colorΪpcolor
				probar(hl, shl, hr, shr);
			}
			else if (flag_q == 0 && pd(640 - 14, 26, 640, 26 + 10))//����ϼ�ͷ
			{
				if (hl == 0);//��Ч 
				else
				{
					drawmain_c();

					hl--;//��ǰ��һ����ʾ��ʵ��������1
					hnode_c = p2;//hnode����ָ���һ�� 
					if (textflags != 0)
					printlist_chinese(p2,  pcolor, hl, hr);
					probar(hl, shl, hr, shr);
				}
			}
			else if (flag_q == 0 && pd(640 - 14, 480 - 30, 640, 480 - 20))//����¼�ͷ
			{
				//hnode = p;//hnode����ָ���һ��
				hnode_c = p2;
				for (i = 1; i < hl; i++)
					hnode_c = hnode_c->next;//hnodeָ��������ʾ�ĵ�һ�� 
				if (hnode_c->next == 0);//��ǰ��ʾ�ĵ�һ��Ϊʵ�ʵ����һ�У�������DOWN
				else
				{
					drawmain_c();

					hl++;//��ǰ��һ����ʾ��ʵ��������1
					
					hnode_c = p2;
					
					if (textflags != 0)
					printlist_chinese(p2,  pcolor, hl, hr );
					probar(hl, shl, hr, shr);
				}
			}
			else if (flag_q == 0 && pd(640 - 14, 26, 640, 480 - 20))
			{
				hl = (int)((float)(mouse_y - 40) / 367.0*shl);//�����㷨
				if (hl > shl)
				{
					hl = shl;
				}
				else if (hl < 1)
				{
					hl = 1;
				}
				if (textflags != 0)
				printlist_chinese(p2,  pcolor, hl, hr );//Ŀǰ�����hnodeΪp,colorΪpcolor
				probar(hl, shl, hr, shr);
			}

			if (flag_q==0&&pd(6 * 8 + 4, 0, 88, 16))//�����File������
			{
				flag_c = 1;
				hnode = p;//����ָ���һ��
				drawmenu_c(F1,p2,hl,hr,pcolor, textflags );
				probar(hl, shl, hr, shr);

			}
			else if (flag_q==0&&pd(24 * 8 + 4, 0, 80, 16))//�����Edit������
			{
				flag_c = 2;
				hnode = p;//����ָ���һ��
				drawmenu_c(F2,p2, hl,hr,pcolor, textflags);
				probar(hl, shl, hr, shr);

			}

			else if (flag_q==0&&pd(42 * 8 + 4, 0, 8 * 13, 16))//�����settings������
			{
				flag_c = 3;
				hnode = p;//����ָ���һ��
				drawmenu_c(F3, p2, hl,hr,pcolor, textflags);
				probar(hl, shl, hr, shr);


			}
			else if (flag_c==0&&pd(60 * 8 + 4, 0, 8 * 14, 16))//�����pattern������
			{
				flag_c = 4;
				//ClearLists(p2);
				drawmenu_c(F4, p2, hl, hr, pcolor, textflags);
				probar(hl, shl, hr, shr);
			}
			/*else if (flag_c==0&&pd(60 * 8 + 4, 0, 8 * 14, 16))//�����pattern������
			{
				ClearLists(p2);

				if (hnode_cc->head->chr != 'y')//ȷ��û��ʹ�ã�����free��
				{
					node_cc = hnode_cc->head;
					while (node_cc != NULL)
					{
						node_ccp = node_cc;
						node_cc = node_cc->next;
						free(node_ccp);
					}
					free(hnode_cc);
				}
				closegraph();
				initmouse(0);
				//inint
				return 20;
				//break;
			}*/

			//File�˵���֮��ļ����Ӳ˵�
			else if (flag_q == 0 && pd(6 * 8 + 4, 80 - 6 * 8, 88, 16) && flag_c == 1)
			{
				//flag_c = 0;//�½�
				ClearLists(p2);
				closegraph();
				initmouse(0);
				return 1;
			}
			else if (flag_q == 0 && pd(6 * 8 + 4, 80 - 5 * 8, 88, 16) && flag_c == 1)
			{
				//flag_c = 0;//��
				ClearLists(p2);
				closegraph();
				initmouse(0);
				return 2;
			}
			else if(flag_q==0&&pd(6*8+4,80-4*8,88,16)&&flag_c==1)
				//flag_c = 0;//����
			{
				ClearLists(p2);
				closegraph();
				initmouse(0);
				return 3;
			}
			else if(flag_q==0&&pd(6*8+4,80-3*8,88,16)&&flag_c==1)
				//flag_c = 0;//����Ϊ
			{
				ClearLists(p2);
				closegraph();
				initmouse(0);
				return 4;
			}
			else if(flag_q == 0 && pd(6*8+4,80-2*8,88,16)&&flag_c==1)//�˳�
			{
				ClearLists(p2);
				closegraph();
				initmouse(0);
				return 5;
				
			}

			//Edit�˵���֮��ļ����Ӳ˵�
			else if(flag_q == 0 && pd(24*8+4,80-6*8,80,16)&&flag_c==2)
				//flag_c = 0;// ����
			{
				ClearLists(p2);
				closegraph();
				initmouse(0);
				return 11;
				
			}
			else if(flag_q == 0 && pd(24*8+4,80-5*8,80,16)&&flag_c==2)
				//flag_c = 0;//����
			{
				ClearLists(p2);
				closegraph();
				initmouse(0);
				return 12;
				
			}
			else if(flag_q == 0 && pd(24*8+4,80-4*8,80,16)&&flag_c==2)
				//flag_c = 0;//ճ��
			{
				ClearLists(p2);
				closegraph();
				initmouse(0);
				return 13;
				
			}
			else if(flag_q == 0 && pd(24*8+4,80-3*8,80,16)&&flag_c==2)
				//flag_c = 0;//����
			{
				ClearLists(p2);
				closegraph();
				initmouse(0);
				return 14;
				
			}
			else if (flag_q == 0 && pd(24 * 8 + 4, 80 - 2 * 8, 80, 16) && flag_c == 2)
			//flag_c = 0;//�滻
			{
				ClearLists(p2);
				closegraph();
				initmouse(0);
				return 15;
				
			}

			//Settings�˵���֮��ļ����Ӳ˵�
			else if (flag_q == 0 && pd(42 * 8 + 4, 80 - 6 * 8, 80, 16) && flag_c == 3)
			{

				flag3_c = 1;
				hnode = p;//����ָ���һ��
				drawmenu_c(1, p2, hl,hr,pcolor, textflags);
				probar(hl, shl, hr, shr);
			}// ����
			else if (flag_q == 0 && pd(42 * 8 + 4, 80 - 4 * 8, 80, 16) && flag_c == 3)
			{

				flag3_c = 2;
				hnode = p;//����ָ���һ��
				drawmenu_c(2, p2, hl,hr,pcolor, textflags);
				probar(hl, shl, hr, shr);
			}//��ɫ
			else if (flag_q == 0 && pd(42 * 8 + 4, 80 - 2 * 8, 80, 16) && flag_c == 3)//��������
			{
				flag_c = 0;
				draw_help();
				flag_q2 = 1;
				show_mouse();
				while (1)
				{
					getmouse();
					if (M_sc < 0 && pd(320 - 32 - 5 - 10, 480 - 50, 320 - 32 - 5 + 10 + 37 * 2, 480 - 50 + 32 + 10)&&flag_q2==1)
					{
						flag_q2 = 0;
						
						break;
					}
				}
				
				drawmain_c();
				if (textflags != 0)
				{
					printlist_chinese(p2, pcolor, hl, hr );//Ŀǰ�����hnodeΪp,colorΪpcolor
					probar(hl, shl, hr, shr);
				}
				else
					drawmain_c();
			}
			else if (flag_q == 0 && pd((42+18) * 8 + 4, 80 - 6 * 8, 80, 16)&&flag_c==4 )
			{
				flag_c = 0;
				//ClearLists(p2);

				node_cc = hnode_cc->head;
				while (node_cc != NULL)
				{
					node_ccp = node_cc;
					node_cc = node_cc->next;
					free(node_ccp);
				}
				free(hnode_cc);
				
				closegraph();
				initmouse(0);
				return 20;
			
			
			}// Ӣ�ı༭
			else if (flag_q == 0 && pd((42+18) * 8 + 4, 80 - 4 * 8, 80, 16) &&flag_c==4)
			{
					flag_c = 0;
					if (textflags != 0)
					{
						printlist_chinese(p2, pcolor, hl, hr );//Ŀǰ�����hnodeΪp,colorΪpcolor

					}
					else
						drawmain_c();
					probar(hl, shl, hr, shr);
					continue;
			
			
			}// ��������
			if (flag_q == 0 && flag3_c == 1)
			{
				
				for (i = 0; i < 5; i++)
				{
					if (pd(400 - 6 * 8 + (11 * 8), 32 + 16*(i+1),16*6,16))
					{
						flag_c = 0;
						flag3_c = 0;

						h = i;//�ı䴫��chinese�������ַ�����hΪ�����±꣩
						ziti_set(i); 
						//ClearLists(hnode_c);
						//chinese(hnode,cursornode, h,pcolor);
						sethzmode(YOU16, hz_s[h]);//��������
						drawmain_c();
						if (textflags != 0)
						printlist_chinese(p2,  pcolor, hl,hr);
						probar(hl, shl, hr, shr);
					}
				}
				continue;
			}
			if (flag_q == 0 && flag3_c == 2)
			{
				for (i = 0; i < 5; i++)
				{
					if (pd(400 - 6 * 8 + (11 * 8), 32 + 16 + 16*(i+1), 6 * 16, 16))

					{
						flag_c = 0;
						flag3_c = 0;

						color_set(i);
						color_set2(pcolor);

						High_li(p2, cursornode,pcolor[0], 0);//��������ɫ������
						High_li(p2, cursornode,pcolor[1], 1);
						High_li(p2, cursornode,pcolor[2], 2);
						High_li(p2, cursornode,pcolor[3], 3);
						High_li(p2, cursornode,pcolor[4], 4);
						High_li(p2, cursornode,pcolor[5], 5);
						

							
						drawmain_c(); 
						/*for (i = 1; i < hl; i++)
							hnode = hnode->next;
						for (i = 0; (i < 27) && hnode != NULL; i++)//������ʾ27��
						{
							moveto(16, 32 + 16 + i * 16);
							printline_chinese(hnode, YOU16,pcolor);
							hnode = hnode->next;
						}*/
						if (textflags != 0)
						printlist_chinese(p2,  pcolor, hl,hr);//Ŀǰ�����hnodeΪp,colorΪpcolor
						probar(hl, shl, hr, shr);
						

					}
				}
				continue;
			}
		    
			
				
			
		}
		if (flag_q == 0 && bioskey(1) != 0)
		{

			op = bioskey(0);
			if (op == ESC)
				exit(0);
			/*else if (op == F4)
			   {
					ClearLists(p2);
					/*if (hnode_cc->head->chr != 'y')//ȷ��û��ʹ�ã�����free��
					{
						node_cc = hnode_cc->head;
						while (node_cc != NULL)
						{
							node_ccp = node_cc;
							node_cc = node_cc->next;
							free(node_ccp);
						}
						free(hnode_cc);
				//	}

					node_cc = hnode_cc->head;
					while (node_cc != NULL)
					{
						node_ccp = node_cc;
						node_cc = node_cc->next;
						free(node_ccp);
					}
					free(hnode_cc);

					break;
			   }*/
			else if (op == F1 || op == F2 || op == F3 || op == F4)
			{
				hnode = p;//����ָ���һ��
				drawmenu_c(op, hnode, hl, hr, pcolor, textflags);
				probar(hl, shl, hr, shr);
				if (op == F1) flag_c = 1;//��¼�˵�λ��
				if (op == F2) flag_c = 2;
				if (op == F3) flag_c = 3;
				if (op == F4) flag_c = 4;
			}
			else if (op == UP)
			{
				if (hl == 0);//��Ч 
				else
				{
					drawmain_c();

					hl--;//��ǰ��һ����ʾ��ʵ��������1
					hnode_c = p2;//hnode����ָ���һ�� 
					//void printlist_chinese(Hnode *hnode, FILE *YOU16, int color[], int hl, int hr)//Ŀǰ�����hnodeΪp,colorΪpcolor
					/*for (i = 1; i < hl; i++)
						hnode = hnode->next;
					for (i = 0; (i < 26) && hnode != 0; i++)//������ʾ26��
					{
						moveto(16, 32 + 16+i * 16);
						printline_chinese(hnode, YOU16,pcolor,hr);
						hnode = hnode->next;
					}*/
					if (textflags != 0)
						printlist_chinese(p2, pcolor, hl, hr);
					probar(hl, shl, hr, shr);
				}
			}
			else if (op == DOWN)//��Ч�������ǵ�ǰΪ���һ�� 
			{
				//hnode = p;//hnode����ָ���һ��
				hnode_c = p2;
				for (i = 1; i < hl; i++)
					hnode_c = hnode_c->next;//hnodeָ��������ʾ�ĵ�һ�� 
				if (hnode_c->next == 0);//��ǰ��ʾ�ĵ�һ��Ϊʵ�ʵ����һ�У�������DOWN
				else
				{
					drawmain_c();

					hl++;//��ǰ��һ����ʾ��ʵ��������1
					//hnode = p;//hnode����ָ���һ��
					hnode_c = p2;
					/*for (i = 1; i < hl; i++)
						hnode = hnode->next;
					for (i = 0; (i < 27) && hnode != NULL; i++)//������ʾ27��
					{
						moveto(16, 32 + 16+i * 16);
						printline_chinese(hnode, YOU16,pcolor,hr);
						hnode = hnode->next;
					}*/
					if (textflags != 0)
						printlist_chinese(p2, pcolor, hl, hr);
					probar(hl, shl, hr, shr);
				}

			}
			else if (op == LEFT)
			{
				hr = menu_cl(p2, hr);//����ֵΪhr,//����ֵΪp2
				if (textflags != 0)
					printlist_chinese(p2, pcolor, hl, hr);
				probar(hl, shl, hr, shr);

			}
			else if (op == RIGHT)
			{
				hr = menu_cr(p2, hr);//����ֵΪhr,//����ֵΪp2
				if (textflags != 0)
					printlist_chinese(p2, pcolor, hl, hr);
				probar(hl, shl, hr, shr);
				/*
				//hnode = hnode->next;//hnodeָ��������ʾ�ĵ�һ��

				//hnode = p;
				hnode_c = p2;
				while (hnode_c != NULL)
				{
					flag_r1++;
					node = hnode_c->head->next;
					for (i = 1; i < hr&&node!=NULL; i++)
					{
						node = node->next;
					}//��������ǰ��ʾ��һ�У����ж��Ƿ�Ϊ����
					if (node == NULL)
					{
						flag_r2++;
					}
					while (node != NULL)
					{
						if (node->chr >= 0x80)//��һ��������
						{
							flag_r++;
						}
						node = node->next;
					}
					hnode_c=hnode_c->next;
				}
				//if(tnode->chr < 0x80)
				if (flag_r1 != flag_r2)
				{
					if (flag_r != 0)
					{
						hr += 3;

					}
					else
					{
						hr++;//��ǰ��һ����ʾ��ʵ��������1
					}
					drawmain_c();
					hnode = p;//hnode����ָ���һ��
					printlist_chinese(p2, YOU16, pcolor, hl, hr+1);
					probar(hl, shl, hr, shr);
				}


				flag_r = 0;
				flag_r1 = 0;
				flag_r2 = 0;

			*/
			}
			else if ((op & 0x00ff) == 'o')//����ָ������ģʽ oΪorder
			{

				flag_o2 = 0;//��������δ��ȷ��
				draw_oc();
				unsigned int hzk_o1[2] = { 0x63d0,0x793a };
				unsigned int hzk_o2[7] = { 0x5df2,0x8fdb,0x5165,0x547d,0x4ee4,0x6a21,0x5f0f };
				unsigned int hzk_o3[5] = { 0x8bf7,0x8f93,0x5165,0x547d,0x4ee4 };

				put_s_hz(96 + 96 * 2 + 5, 48 * 3 + 5, hzk_o1, 2, YOU16);
				put_s_hz(96 + 96 * 2 + 5, 48 * 3 + 32 + 10 + 5, hzk_o2, 7, YOU16);
				put_s_hz(96 + 96 * 2 + 5, 48 * 3 + 32 + 10 + 2 + 32, hzk_o3, 5, YOU16);




				i = 0;
				while (1)
				{
					order[i] = (char)(bioskey(0) & 0x00ff);

					if (order[i] == '\r')
					{
						break;
					}
					i++;
				}
				order[i] = '\0';
				if (order[0] == 't')//��תָ��
				{
					if (order[1] == 'l')//��ת��ָ��
					{
						for (i = 0; order[2 + i] != '\0'; i++)
						{
							if (order[2 + i] >= '0'&&order[2 + i] <= '9')
							{
								;
							}
							else//ֻҪ�����һ���������֣��Ͳ���������
							{
								flag_o = -1;
							}
						}
						if (flag_o == 0)
						{
							o_n = atoi(&order[2]);
							if (o_n >= 1 && o_n <= shl)
							{
								hl = o_n - 1;//hlΪ0ʱ��ʾ��һ��
								/*if (textflags != 0)
									printlist_chinese(p2,  pcolor, hl, hr + 1);
								else
									drawmain_c();
								probar(hl, shl, hr, shr);*/
							}
						}
						flag_o2 = 1;
						flag_o = 0;
					}
					else if (order[1] == 'r')//��ת��ָ��
					{
						for (i = 0; order[2 + i] != '\0'; i++)
						{
							if (order[2 + i] >= '0'&&order[2 + i] <= '9')
							{
								;
							}
							else//ֻҪ�����һ���������֣��Ͳ���������
							{
								flag_o = -1;
							}
						}
						if (flag_o == 0)
						{
							o_n = atoi(&order[2]);

							if (o_n % 3 == 2)//����
							{
								o_n += 2;
							}
							else if (o_n % 3 == 0)
							{
								o_n += 1;
							}

							if (o_n < 1)
							{
								o_n = 1;
							}
							else if (o_n > shr)
							{
								if (shr % 3 == 1)
									o_n = shr;
								else if (shr % 3 == 2)
									o_n = shr - 1;
								else if (shr % 3 == 0)
									o_n = shr - 2;
							}
							hr = o_n;//hrΪ0ʱ��ʾ��һ��
							flag_o2 = 1;
							/*if (textflags != 0)
								printlist_chinese(p2,  pcolor, hl, hr + 1);
							else
								drawmain_c();
							probar(hl, shl, hr, shr);*/

						}

						flag_o = 0;
					}
				}
				else if (order[0] == 'd')//����ɾ��ָ��ģʽ
				{
					if (order[1] == 'l')//ɾ����
					{
						for (i = 0; order[2 + i] != '\0'; i++)
						{
							if (order[2 + i] >= '0'&&order[2 + i] <= '9');
							else//ֻҪ�����һ���������֣��Ͳ���������
								flag_o = -1;
						}
						if (flag_o == 0)
						{
							o_n = atoi(&order[2]);
							if (o_n >= 1 && o_n <= shl)
							{
								hnode_c = p2;//����ָ���һ��
								for (i = 1; i < o_n - 1; i++)
								{
									hnode_c = hnode_c->next;
								}
								hnode_cb = hnode_c;
								if (o_n != 1)
								{
									hnode_c = hnode_c->next;
								}
								if (o_n == 1)
								{
									p2 = del_l(hnode_c);
								}
								else
								{
									hnode_cb->next = hnode_c->next;
									del_l(hnode_c);
								}
								shl -= 1;
								flag_o2 = 1;
							}
						}

						flag_o = 0;
					}
					//else if (order[1] == 'r')//ɾ����
					//{

					//}
					hnode_c = p2;
					chigh_li(hnode_c);
					hnode_c = p2;
					for (i = 0; i < 6; i++)
					{
						High_li(hnode_c, cursornode, pcolor[i], i);
					}
				}
				else if (order[0] == 'a')//�������ӣ��У�ָ��ģʽ add
				{

					if (order[1] == 'b')//���ӿգ��У�
					{
						if (order[2] == 'l')//������
						{
							for (i = 0; order[3 + i] != '\0'; i++)
							{
								if (order[3 + i] >= '0'&&order[3 + i] <= '9');
								else//ֻҪ�����һ���������֣��Ͳ���������
									flag_o = -1;
							}
							if (flag_o == 0)
							{
								o_n = atoi(&order[3]);
								if (o_n >= 1 && o_n <= shl)
								{
									hnode_c = p2;//����ָ���һ��
									for (i = 1; i < o_n; i++)
									{
										hnode_c = hnode_c->next;
									}
										Hnode * hnode_p1 = (Hnode *)malloc(sizeof(Hnode));
										hnode_p1->next = NULL;
										hnode_p1->head = (Node *)malloc(sizeof(Node));
										hnode_p1->head->chr = ' ';
										hnode_p1->next = hnode_c->next;
										hnode_c->next = hnode_p1;
										shl += 1;
										

								}

								hnode_c = p2;
								chigh_li(hnode_c);
								for (i = 0; i < 6; i++)
								{
									High_li(hnode_c, cursornode, pcolor[i], i);
								}
								flag_o = 0;
								flag_o2 = 1;
							}
						}
					}
					else if (order[1] == 'c')//���Ӽ������е��Ѿ������˵ģ���
					{

						if (order[2] == 'l')//������
						{
							for (i = 0; order[3 + i] != '\0'; i++)
							{
								if (order[3 + i] >= '0'&&order[3 + i] <= '9');
								else//ֻҪ�����һ���������֣��Ͳ���������
									flag_o = -1;
							}
							if (flag_o == 0)
							{
								o_n = atoi(&order[3]);
								if (o_n >= 1 && o_n <= shl)
								{
									hnode_c = p2;//����ָ���һ��
									for (i = 1; i < o_n; i++)
									{
										hnode_c = hnode_c->next;
									}
									node = hnode_cc->head->next;
										
									add_cl(hnode_c, hnode_cc, 1);//��hnode�к����hnode_c(��Ҫ���ƣ���
										
									shl += 1;
									flag_o = 0;
									flag_o2 = 1;

									
								}

								hnode_c = p2;
								chigh_li(hnode_c);
								for (i = 0; i < 6; i++)
								{
									High_li(hnode_c, cursornode, pcolor[i], i);
								}
								
							}

						}


					}
				}
				else if (order[0] == 'c' || order[0] == 'x')//���븴��ĳ��ģʽ�����Ƶ�������
				{
					if (order[1] == 'l')//����ĳ��
					{
						for (i = 0; order[2 + i] != '\0'; i++)
						{
							if (order[2 + i] >= '0'&&order[2 + i] <= '9');
							else//ֻҪ�����һ���������֣��Ͳ���������
								flag_o = -1;
						}
						if (flag_o == 0)
						{
							o_n = atoi(&order[2]);
							if (o_n >= 1 && o_n <= shl)
							{
								flag_o2 = 1;
								
								node_cc = hnode_cc->head;
								while (node_cc != NULL)
								{
									node_ccp = node_cc;
									node_cc = node_cc->next;
									free(node_ccp);
								}
								free(hnode_cc);
								hnode_c = p2;//����ָ���һ��
								
								for (i = 1; i < o_n; i++)
								{
									hnode_c = hnode_c->next;
									
								}
								//���²���Ϊ���ƺ���������
								node = hnode_c->head;

								hnode_cc = (Hnode *)malloc(sizeof(Hnode));
								hnode_cc->next = NULL;
						//		node_ccp = (Node*)malloc(sizeof(Node));

							 //	hnode_cc->head = node_ccp;
								if(node!=NULL)
								{
									node_cc=(Node *)malloc(sizeof(Node));
									node_cc->chr=node->chr;
									node_cc->type=node->type;
									hnode_cc->head=node_cc;
									hnode_cc->head->next=NULL;
									node=node->next;
								}
								node_ccp=hnode_cc->head;
								while (node != NULL)//��ѡ���и��Ƶ��½�����������
								{
									node_cc = (Node*)malloc(sizeof(Node));
									node_cc->chr = node->chr;
									node_cc->type = node->type;
									node_ccp->next = node_cc;
									node_cc->next = NULL;
									node_ccp = node_cc;
									node = node->next;
								}

								if (order[0] == 'x')//������Ҫɾ����ԭ����
								{



										hnode_c = p2;//����ָ���һ��

										for (i = 1; i < o_n - 1; i++)
										{
											hnode_c = hnode_c->next;

										}
										hnode_cb = hnode_c;

										if (o_n != 1)
										{
											hnode_c = hnode_c->next;
										}
										if (o_n == 1)
										{
											p2 = del_l(hnode_c);//��hnode��ɾfree�� ����ɾ����һ���ں���������
										}
										else
										{
											hnode_cb->next = hnode_c->next;
											hnode_c->next = NULL;
											del_l(hnode_c);
										}
										shl -= 1;
										flag_o2 = 1;
										hnode_c = p2;
										chigh_li(hnode_c);
										for (i = 0; i < 6; i++)
										{
											High_li(hnode_c, cursornode, pcolor[i], i);
										}

								}

							}


						}
					}
				}

					draw_com();
					unsigned int o_1[2] = { 0x63d0,0x793a };//��ʾ
					unsigned int o_4[2] = { 0x786e,0x5b9a };//ȷ��
					put_s_hz(96 + 20, 48 * 3 + 15, o_1, 2, YOU16);//��ʾ
					put_s_hz(320 - 32 - 5 - 10 + 30, 240 + 80 - 40 + 16, o_4, 2, YOU16);//ȷ��
					unsigned int o_2[6] = { 0x547d,0x4ee4,0x8f93,0x5165,0x6b63,0x786e };//����������ȷ
					unsigned int o_3[6] = { 0x547d,0x4ee4,0x8f93,0x5165,0x9519,0x8bef };//�����������
					if (flag_o2 == 0)//�����˴��������
					{
						put_s_hz(96 + 20 + 20 + 35, 48 * 3 + 15 + 32 + 32, o_3, 6, YOU16);
					}
					else
					{
						put_s_hz(96 + 20 + 20 + 35, 48 * 3 + 15 + 32 + 32, o_2, 6, YOU16);;
					}

					while (1)
					{
						getmouse();
						if (M_sc < 0 && pd(320 - 32 - 5 - 10, 240 + 80 - 40, 320 - 32 - 5 + 10 + 37 * 2, 240 + 80 - 40 + 32 + 10))
						{
							break;
						}
					}

					flag_o2 = 0;//��������δ�ɹ�
					if (textflags != 0)
						printlist_chinese(p2, pcolor, hl, hr);
					else
						drawmain_c();
					probar(hl, shl, hr, shr);
				
			}
		}
	}
 }
 void drawmain_c()//������������ 
 {
 	
	hide_mouse();										
	setbkcolor(0);//��������Ϊ��ɫ��Ϊ�˳����֣�֮������0��Ȼ�Ǳ�����ɫ����֮���� 
	cleardevice();//���� 
	
	barxy(0, 0, 640, 16, 7);  //�ϲ˵��ҿ� 

	setfillstyle(1, DARKGRAY);//������
	bar(0, 480 - 20, 640, 480);
	
	//barxy(0,480-16,640,480,7);  //�²˵�
	barxy(0,16,640,480-32,1);  //��ɫ������ //Ϊʲô�Ǽ�32����16���±߻ᱻ������ȥ 

	bar(640 - 14, 26, 640, 480 - 20);//������

	setcolor(15);//�׿�
	
	line(2,16+5,2,480-16-5);//���׿� 
	line(3,16+5,3,480-16-5);
	line(3+4,16+8,3+4,480-16-8);
	line(3+5,16+8,3+5,480-16-8);
	
	 
    line(2, 16+5 , 640, 16+5);//��׿�
	line(2, 16+6 , 640, 16+6); 
    line(2+5, 16+8 , 640, 16+8);
    line(2+5, 16+9 , 640, 16+9);//�� 
    line(2, 480-(16+5), 640, 480-(16+5));
	line(2, 480-(16+6), 640, 480-(16+6)); 
    line(2+5, 480-(16+8), 640, 480-(16+8));
    line(2+5, 480-(16+9), 640, 480-(16+9));//�� 
    
	 
	
	/*char s[30];
	int x;
	for(x=16;x<640;x+=16)//���ӣ�����ֽ 
	{
		sprintf(s,"%d",x);
		line(x,0,x,480);
		outtextxy(x,0,s); 
		line(0,x,640,x);
		outtextxy(0,x,s);
	}
	line(0,0,480,480);*/ 
	 
	
	//static int YOU16FLAG = 0; 
	static FILE* YOU16; 
	//if (YOU16FLAG == 0) 
		//{ 
			// YOU16FLAG = 1;  
			 sethzmode(YOU16,  "YOU16");//������Բ16������    
		//}
										
											
			 //int  A = 0;
			 //int flag = 0;
			 //value = 0;
    unsigned  int  hzk1[6]  =  {  0x6587  ,0x4ef6  ,0x46  ,0x31  };//"�ļ�F1"    
    unsigned  int  hzk2[6]  =  {  0x4fee  ,0x6539  ,0x46  ,0x32  };//"�޸�F2"    
    unsigned  int  hzk3[6]  =  {  0x8bbe  ,0x7f6e  ,0x46  ,0x33  };//"����F3"    
	unsigned  int  hzk4[6]  =  {  0x6a21  ,0x5f0f  ,0x46  ,0x34  };//"ģʽF4"
	unsigned  int  hzk5[2]  =  { 0x8fd0,0x884c };//"����"
	
	
	setcolor(0);
	line(5 * 8 + 5, 0, 5 * 8 + 5, 16);

	line(6 * 8 + 4, 2, 6 * 8 + 4, 14);  //�����ߺ����ߣ���˵��ĸ��� 
	line(6 * 8 + 4,2,6 * 8 + 4+6,2);
	line(6 * 8 + 4,14,6 * 8 + 4+6,14);
	
    line(17 * 8 + 4, 2, 17 * 8 + 4, 14);  
    line(17 * 8 + 4, 2, 17 * 8 + 4-6, 2); 
    line(17 * 8 + 4, 14, 17 * 8 + 4-6, 14); 
    
    line(24 * 8 + 4, 2, 24 * 8 + 4, 14); 
	line(24 * 8 + 4, 2, 24 * 8 + 4+6, 2);
	line(24 * 8 + 4, 14, 24 * 8 + 4+6, 14);
	 
    line(35 * 8 + 4, 2, 35 * 8 + 4, 14); 
	line(35 * 8 + 4, 2, 35 * 8 + 4-6, 2);
	line(35 * 8 + 4, 14, 35 * 8 + 4-6, 14); 
	 
    line(42 * 8 + 4, 2, 42 * 8 + 4, 14);
	line(42 * 8 + 4, 2, 42 * 8 + 4+6, 2);
	line(42 * 8 + 4, 14, 42 * 8 + 4+6, 14);
	  
    line(53 * 8 + 4, 2, 53 * 8 + 4, 14);
	line(53 * 8 + 4, 2, 53 * 8 + 4-6, 2);
	line(53 * 8 + 4, 14, 53 * 8 + 4-6, 14);
	  
    line(60 * 8 + 4, 2, 60 * 8 + 4, 14);
	line(60 * 8 + 4, 2, 60 * 8 + 4+6, 2);
	line(60 * 8 + 4, 14, 60 * 8 + 4+6, 14);
	  
    line(71 * 8 + 4, 2, 71 * 8 + 4, 14);
    line(71 * 8 + 4, 2, 71 * 8 + 4-6, 2);
    line(71 * 8 + 4, 14, 71 * 8 + 4-6, 14);
	
							
	put_s_hz(8, 0, hzk5, 2, YOU16);
	put_s_hz(80 - 2 * 8, 0, hzk1, 4, YOU16); //��ʾ����  
	put_s_hz(240 - 4 * 8, 0, hzk2, 4, YOU16);  
	put_s_hz(400 - 6 * 8, 0, hzk3, 4, YOU16);  
	put_s_hz(560 - 8 * 8, 0, hzk4, 4, YOU16);   
	
	setfillstyle(1, DARKGRAY);
	bar(0, 480 - 20, 640, 480);

	setcolor(0);//�������εļ�ͷ
	line(0, 480 - 10, 10, 480 - 20);
	line(0, 480 - 10, 10, 480);
	line(10, 480 - 20, 10, 480);

	line(640 - 10, 480 - 20, 640, 480 - 10);
	line(640 - 10, 480, 640, 480 - 10);
	line(640 - 10, 480 - 20, 640 - 10, 480);

	//���ݽ���������������ͷ
	setfillstyle(1, DARKGRAY);
	bar(640 - 14, 26, 640, 480 - 20);

	show_mouse();
 }
 void drawmenu_c(int op,Hnode *hnode,int hl,int hr,int *pcolor,int textflags)//�����Ĳ˵�
 {
	int i;
	
	
	static FILE* YOU16;
	sethzmode(YOU16, "YOU16");//������Բ16������


	

 	
	switch(op)
	{
		case 1://���������˵� ����
			hide_mouse();
			//drawmain_c();
			drawmenu_c(F3,hnode,hl,hr,pcolor, textflags);
			barxy((42 + 11) * 8, 16 + 16, 12 * 8, 7 * 16, LIGHTGRAY);

			line((42+11+1) * 8, 24+16, (42 + 11 + 1) * 8, 24+16 + 6 * 16);  //����
			line((42 + 11 + 1) * 8, 24 +16+ 6 * 16, (42 + 11 + 1) * 8 + 10 * 8, 24+16 + 6 * 16);  //����
			line((42 + 11 + 1) * 8 + 10 * 8, 24 +16+ 6 * 16, (42 + 11 + 1) * 8 + 10 * 8, 24+16);//����
			line((42 + 11 + 1) * 8 + 10 * 8, 24+16, (42 + 11 + 1) * 8, 24+16);  //�Ϻ���

			unsigned int hzk1_1[2] = { 0x89c4,0x8303 };//"�淶"
			unsigned int hzk2_1[2] = { 0x6977,0x4f53 };//"����"
			unsigned int hzk3_1[2] = { 0x5e7c ,0x5706 };//"��Բ"
			unsigned int hzk4_1[2] = { 0x659c,0x4f53 };//"б��"
			unsigned int hzk5_1[2] = { 0x4e66,0x6cd5 };//"�鷨"
			put_s_hz(400 - 6 * 8+(11*8), 32+16, hzk1_1, 2, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 48+16, hzk2_1, 2, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 64+16, hzk3_1, 2, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 80+16, hzk4_1, 2, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 96+16, hzk5_1, 2, YOU16);
			show_mouse();
			break;
		case 2:
			hide_mouse();
			//drawmain_c();
			drawmenu_c(F3,hnode,hl,hr,pcolor, textflags);
			barxy((42 + 11) * 8, 16 + 16*2, 12 * 8, 7 * 16, LIGHTGRAY);

			line((42 + 11 + 1) * 8, 24 + 16+16, (42 + 11 + 1) * 8, 24 + 16 + 16+6 * 16);  //����
			line((42 + 11 + 1) * 8, 24 + 16 +16+ 6 * 16, (42 + 11 + 1) * 8 + 10 * 8, 24 +16+ 16 + 6 * 16);  //����
			line((42 + 11 + 1) * 8 + 10 * 8, 24 + 16 +16+ 6 * 16, (42 + 11 + 1) * 8 + 10 * 8, 24+16 + 16);//����
			line((42 + 11 + 1) * 8 + 10 * 8, 24 +16+16, (42 + 11 + 1) * 8, 24+16 + 16);  //�Ϻ���

			unsigned int hzk1_2[4] = { 0x53d6 ,0x6d88,0x989c,0x8272 };//"ȡ����ɫ"
			unsigned int hzk2_2[3] = { 0x989c,0x8272 ,0x4e00 };//"��ɫһ"
			unsigned int hzk3_2[3] = { 0x989c,0x8272 ,0x4e8c };//"��ɫ��"
			unsigned int hzk4_2[3] = { 0x989c,0x8272 , 0x4e09 };//"��ɫ��"
			unsigned int hzk5_2[3] = { 0x989c,0x8272 ,0x56db };//"��ɫ��"
			put_s_hz(400 - 6 * 8 + (11 * 8), 32 + 16+16, hzk1_2, 4, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 48 + 16+16, hzk2_2, 3, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 64 + 16+16, hzk3_2, 3, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 80 + 16+16, hzk4_2, 3, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 96 + 16+16, hzk5_2, 3, YOU16);
			show_mouse();
			break;



		case F1://��File
				hide_mouse();
				//drawmain_c();
				if (textflags != 0)
					printlist_chinese(hnode,  pcolor, hl, hr);
				else
					drawmain_c();
				/*for (i = 1; i < hl; i++)
					hnode = hnode->next;
				for (i = 0; (i < 27) && hnode != NULL; i++)//������ʾ27��
				{
					moveto(16, 32 + 16 + i * 16);
					printline_chinese(hnode, YOU16,pcolor,hr);
					hnode = hnode->next;
				}*/

				barxy(6 * 8 + 4, 16, 11 * 8, 7 * 16, LIGHTGRAY);
				setcolor(0);
				line(7 * 8, 24, 7 * 8, 24 + 6 * 16);  //����
				line(7 * 8, 24 + 6 * 16, 7 * 8 + 10 * 8, 24 +6 * 16);  //����
				line(7 * 8 + 10 * 8, 24 +  6* 16, 7 * 8 + 10 * 8, 24);//����
				line(7 * 8 + 10 * 8, 24, 7 * 8, 24);  //�Ϻ���

				unsigned int hzk1[2] = { 0x65b0 ,0x5efa };//"�½�"
				unsigned int hzk2[2] = { 0x5f00 ,0x542f };//"����"
				unsigned int hzk3[2] = { 0x4fdd ,0x5b58 };//"����"
				unsigned int hzk4[3] = { 0x53e6 ,0x5b58 ,0x4e3a };//"����Ϊ"
				unsigned int hzk5[2] = { 0x9000 ,0x51fa };//"�˳�"
				put_s_hz(80 - 2 * 8, 32, hzk1, 2, YOU16);
				put_s_hz(80 - 2 * 8, 48, hzk2, 2, YOU16);
				put_s_hz(80 - 2 * 8, 64, hzk3, 2, YOU16);
				put_s_hz(80 - 2 * 8, 80, hzk4, 3, YOU16);
				put_s_hz(80 - 2 * 8, 96, hzk5, 2, YOU16);
				show_mouse();
			break;
		case F2://��Edit
				hide_mouse();
				//drawmain_c();
				/*for (i = 1; i < hl; i++)
					hnode = hnode->next;
				for (i = 0; (i < 27) && hnode != NULL; i++)//������ʾ27��
				{
					moveto(16, 32 + 16 + i * 16);
					printline_chinese(hnode, YOU16,pcolor,hr);
					hnode = hnode->next;
				}*/
				if (textflags != 0)
				printlist_chinese(hnode,  pcolor, hl, hr);
				else
					drawmain_c();
				barxy(24 * 8 + 4, 16, 11 * 8, 7 * 16, LIGHTGRAY);
				setcolor(0);
				line(25 * 8, 24, 25 * 8, 24 + 6 * 16);
				line(25 * 8, 24 + 6 * 16, 25 * 8 + 10 * 8, 24 + 6 * 16);
				line(25 * 8 + 10 * 8, 24 + 6 * 16, 25 * 8 + 10 * 8, 24);
				line(25 * 8 + 10 * 8, 24, 25 * 8, 24);
				unsigned int hzk6[2] = { 0x590d ,0x5236 };//"����"
				unsigned int hzk7[2] = { 0x526a ,0x5207 };//"����"
				unsigned int hzk8[2] = { 0x7c98 ,0x8d34 };//"ճ��"
				unsigned int hzk9[2] = { 0x67e5 ,0x627e };//"����"
				unsigned int hzk10[2] = { 0x66ff ,0x6362 };//"�滻"
				put_s_hz(240 - 4 * 8, 32, hzk6, 2, YOU16);
				put_s_hz(240 - 4 * 8, 48, hzk7, 2, YOU16);
				put_s_hz(240 - 4 * 8, 64, hzk8, 2, YOU16);
				put_s_hz(240 - 4 * 8, 80, hzk9, 2, YOU16);
				put_s_hz(240 - 4 * 8, 96, hzk10, 2, YOU16);
				show_mouse();
			break;
		case F3://��Settings
				hide_mouse();
				//drawmain_c();
				/*for (i = 1; i < hl; i++)
					hnode = hnode->next;
				for (i = 0; (i < 27) && hnode != NULL; i++)//������ʾ27��
				{
					moveto(16, 32 + 16 + i * 16);
					printline_chinese(hnode, YOU16,pcolor,hr);
					hnode = hnode->next;
				}*/
				if (textflags != 0)
				printlist_chinese(hnode, pcolor, hl, hr);
				else
					drawmain_c();
				barxy(42 * 8 + 4, 16, 11 * 8, 4 * 16+16, LIGHTGRAY);
				setcolor(0);
				line(43 * 8, 24, 43 * 8, 24 + 3 * 16+16);
				line(43 * 8, 24 + 3 * 16+16, 43 * 8 + 10 * 8, 24 + 3 * 16+16);
				line(43 * 8 + 10 * 8, 24 + 3 * 16+16, 43 * 8 + 10 * 8, 24);
				line(43 * 8 + 10 * 8, 24, 43 * 8, 24);

				unsigned int hzk11[2] = { 0x5f62,0x4f53 };//"����"
				unsigned int hzk12[2] = { 0x989c,0x8272 };//"��ɫ"
				unsigned int hzk13[2] = { 0x5e2e,0x52a9 };//"����"

				put_s_hz(400 - 6 * 8, 32, hzk11, 2, YOU16);
				put_s_hz(400 - 6 * 8, 48, hzk12, 2, YOU16);
				put_s_hz(400 - 6 * 8, 48+16, hzk13, 2, YOU16);

				show_mouse();
			break;
		case F4:
			hide_mouse();
			if (textflags != 0)
				printlist_chinese(hnode, pcolor, hl, hr);
			else
				drawmain_c();
			barxy((42+18) * 8 + 4, 16, 11 * 8, 4 * 16, LIGHTGRAY);
			setcolor(0);
			line((43+18) * 8, 24, (43+18) * 8, 24 + 3 * 16);
			line((43+18) * 8, 24 + 3 * 16, (43+18) * 8 + 10 * 8, 24 + 3 * 16);
			line((43+18) * 8 + 10 * 8, 24 + 3 * 16, (43+18) * 8 + 10 * 8, 24);
			line((43+18) * 8 + 10 * 8, 24, (43+18) * 8, 24);

			//\u82f1\u6587\u7f16\u8f91\u4e2d\u6587\u547d\u4ee4
			unsigned int hzk14[4] = { 0x82f1,0x6587,0x7f16,0x8f91 };//"Ӣ�ı༭"
			unsigned int hzk15[2] = { 0x6c49,0x5316 };//"��������"

			put_s_hz(400 - 6 * 8+18*8, 32, hzk14, 4, YOU16);
			put_s_hz(400 - 6 * 8+18*8, 48, hzk15, 2, YOU16);

			show_mouse();
	 }
 }
void printline_chinese(Hnode* hnode,FILE * YOU16,int color[],int hr)//�ڵ�ǰλ�����hnodeָ�����һ��
{
	hide_mouse();
	settextjustify(0,0);
	settextstyle(0,0,1);
	unsigned short uni;

	char alp[2]={'\0','\0'};//���Ӣ�ģ��Ǻ���
	Node * tnode;
	int x,y;//���������Ҫ����
	int i;//��������
	tnode=hnode->head;//��һ��Node
	for (i = 1; i < hr&&tnode!=NULL; i++)
	{
		tnode = tnode->next;
	}
	while(tnode!=NULL)
	{
		setcolor(color[tnode->type]);
		if(tnode->chr<0x80)
		{
			alp[0]=char(tnode->chr);
			outtext(alp);
			
		}
		else
		{
			x=getx();
			y=gety();
			
			//put_a_hz(x,y,tnode->chr,YOU16,color[tnode->type],-1);
			
			int ischinese = utf_8_to_16(tnode, &uni);
			if (ischinese)
			{
				put_a_hz(x, y-12, uni, YOU16, color[tnode->type], -1);//�ֶ�����������λ��
				moverel(8, 0);
				tnode = tnode->next->next;
			}
			else
			{
				alp[0] = char(tnode->chr);
				outtext(alp);
				
			}
			moverel(8, 0);

			 
		} 
		tnode=tnode->next;//ָ����һ��Node 
		
	}//����֮�󣬻���ͣ�ڱ���ĩβ
	show_mouse(); 
 }
void printlist_chinese(Hnode *hnode, int color[],int hl,int hr)//Ŀǰ�����hnodeΪp,colorΪpcolor
{
	hide_mouse();
	drawmain_c();
	int i;
	int h;
	char hang[5];

	char* hz_s[] = {
			"YOU16",
			"FS16",
			"HP16",
			"HT16",
			"MBXS16"
	};

	h = ziti_set2();
	static FILE* ziti;
	sethzmode(ziti, hz_s[h]);//��������
	
	for (i = 0; i < hl&&hnode!=NULL ;i++)
		hnode = hnode->next;
	for (i = 0; (i < 27) && hnode != NULL&&hnode->head!=NULL; i++)//������ʾ27��
	{
		sprintf(hang, "%d", i + hl+1);
		setcolor(10);
		//moveto(16, 32 + 16 + i * 16);
		moveto(16, 32 + 16 + i * 16);
		outtext(hang);
		moveto(16+32, 32 + 16 + i * 16);
		printline_chinese(hnode, ziti, color,hr);
		hnode = hnode->next;
	}
	show_mouse();
}
void draw_com(void)
{
	
	hide_mouse();
	
	setbkcolor(0);//��������Ϊ��ɫ��Ϊ�˳����֣�֮������0��Ȼ�Ǳ�����ɫ����֮���� 
	cleardevice();//���� 
	drawmain_c();

	barxy(96, 48*3, 640-96*2, 48*4, 15);  //��׿� 
	
	line(96, 48*3+32+10, 96+32*4+10,48*3+32+10 );  //�ָ���
	//����߿��50��ʼ��{��}�ġ�������
	setfillstyle(1, 7);
	bar(320 - 32 - 5-10, 240 + 80-40, 320 - 32 - 5+10+37 * 2, 240 + 80-40+ 32 + 10);
	//ȫ�õ�xy x1y1x2y2
	show_mouse();
}
void ziti_set(int i)//xie
{
	FILE * file;
	char t;
	t = i + '0';
	file = fopen("c:\\ziti", "w");
	fputc(t, file);
	fclose(file);
}
int ziti_set2(void)//duqu
{
	int t;
	FILE * file;
	file = fopen("c:\\ziti", "r");
	t = fgetc(file) - '0';
	fclose(file);
	return t;
}
void probar(int hl,int shl, int hr,int shr)//������������
{
	int r;//������//�н������Ӻ�����Ϊ0��ʼ����������Ϊ640���� �ܼ�Ϊ640 ��ͷ��ռʮ����������Ϊ630
	r = (int)(((float)hr / (float)shr) * (610-10)) + 10;//�н����������������
	int l;//������ �н�������30��ʼ����������Ϊ480�������ܼ�Ϊ450����ͷ��ռʮ����������Ϊ430
	l = (int)(((float)hl / (float)shl) * (430-20-20-23))  + 40;

	//�����������������ͷ
	setfillstyle(1, DARKGRAY);
	bar(0, 480 - 20, 640, 480);
	setfillstyle(1, BLACK);
	bar(r, 480 - 20, r + 10, 480);

	setcolor(0);//�������εļ�ͷ
	line(0, 480-10, 10,480-20 );
	line(0, 480-10, 10, 480);
	line(10, 480 - 20, 10, 480);

	line(640 - 10, 480 - 20, 640, 480 - 10);
	line(640 - 10, 480, 640, 480 - 10);
	line(640 - 10, 480 - 20, 640 - 10, 480);

	//���ݽ���������������ͷ
	setfillstyle(1, DARKGRAY);
	bar(640 - 14, 26, 640, 480-20);
	//bar(640 - 20, 40 + 10,640 ,480 - 10);
	setfillstyle(1, BLACK);
	bar(640 - 14, l, 640, l + 10);

	line(640 - 14, 26 + 10, 640-7, 26);
	line(640, 26 + 10, 640 - 7, 26);
	line(640 - 14, 26 + 10, 640, 26 + 10);

	line(640 - 14, 480-10-20, 640 - 7, 480-20);
	line(640, 480-10-20, 640 - 7, 480-20);
	line(640 - 14, 480-10-20, 640, 480-10-20);
}
int menu_cl(Hnode *hnode_c,int hr)//����ֵΪhr,//����ֵΪp2
{
	//Hnode *p2 = hnode_c;
	Node *node;
	int i=0;
	int flag_r = 0;

	if (hr == 1);//��Ч 
	else
	{
		//drawmain_c();


		//hnode = p;
		//hnode_c = p2;
		while (hnode_c != NULL)
		{
			node = hnode_c->head->next;

			for (i = 1; i < hr - 3 && node != NULL; i++)
			{
				node = node->next;
			}//��������ǰ��ʾ��һ�е�ǰ���У����ж���һ���Ƿ�Ϊ����

			while (node != NULL)
			{
				if (node->chr >= 0x80 && (hr - 3) % 3 == 1)//��һ��������
				{
					flag_r++;
				}
				node = node->next;
			}
			//hnode = hnode->next;
			hnode_c = hnode_c->next;
		}
		//if(tnode->chr < 0x80)
		if (flag_r != 0)
		{
			hr -= 3;
			flag_r = 0;
		}
		else
		{
			hr--;//��ǰ��һ����ʾ��ʵ��������1
		}




		//hr--;//��ǰ��һ����ʾ��ʵ��������1
		//hnode = p;//hnode����ָ���һ�� 
		//void printlist_chinese(Hnode *hnode, FILE *YOU16, int color[], int hl, int hr)//Ŀǰ�����hnodeΪp,colorΪpcolor
		/*for (i = 1; i < hl; i++)
			hnode = hnode->next;
		for (i = 0; (i < 26) && hnode != 0; i++)//������ʾ26��
		{
			moveto(16, 32 + 16+i * 16);
			printline_chinese(hnode, YOU16,pcolor,hr);
			hnode = hnode->next;
		}*/
		//printlist_chinese(p2, YOU16, pcolor, hl, hr + 1);
		//probar(hl, shl, hr, shr);
	}
	return hr;
}
int menu_cr(Hnode *hnode_c, int hr)
{
	
	int flag_r=0;
	int flag_r1 = 0;
	int flag_r2 = 0;
	int i=0;
	Node * node;
	Hnode *p2=hnode_c;
		//hnode = hnode->next;//hnodeָ��������ʾ�ĵ�һ��

		//hnode = p;

		while (hnode_c != NULL)
		{
			flag_r1++;
			node = hnode_c->head->next;
			for (i = 1; i < hr&&node != NULL; i++)
			{
				node = node->next;
			}//��������ǰ��ʾ��һ�У����ж��Ƿ�Ϊ����
			if (node == NULL)
			{
				flag_r2++;
			}
			while (node != NULL)
			{
				if (node->chr >= 0x80)//��һ��������
				{
					flag_r++;
				}
				node = node->next;
			}
			hnode_c = hnode_c->next;
		}
		//if(tnode->chr < 0x80)
		if (flag_r1 != flag_r2)
		{
			if (flag_r != 0)
			{
				hr += 3;

			}
			else
			{
				hr++;//��ǰ��һ����ʾ��ʵ��������1
			}
			//drawmain_c();

		   //	printlist_chinese(p2, YOU16, color, hl, hr + 1);
		   //	probar(hl, shl, hr, shr);
		}


		flag_r = 0;
		flag_r1 = 0;
		flag_r2 = 0;
		hnode_c=p2;
		return hr;
}
void draw_oc()
{
	hide_mouse();

	setbkcolor(0);//��������Ϊ��ɫ��Ϊ�˳����֣�֮������0��Ȼ�Ǳ�����ɫ����֮����

	//barxy(96, 48 * 3, 640 - 96 * 2, 48 * 4, 15);  //��׿�
	barxy(96+96*2, 48 * 3, 640 - 96 * 5, 48 * 2, 15);
	setcolor(0);
	line(96+96*2, 48 * 3 + 32 + 10, 96 + 32 * 2 + 10+96*2, 48 * 3 + 32 + 10);  //�ָ���
	setfillstyle(1, 7);
	//bar(320 - 32 - 5 - 10, 240 + 80 - 40, 320 - 32 - 5 + 10 + 37 * 2, 240 + 80 - 40 + 32 + 10);
	//ȫ�õ�xy x1y1x2y2
	show_mouse();
}
void draw_help()
{
	char* hz_s[] = {
			"YOU16",
			"FS16",
			"HP16",
			"HT16",
			"MBXS16"
	};
	int h;
	h = ziti_set2();
	static FILE* YOU16;//

	setcolor(0);
	settextjustify(0, 0);
	settextstyle(0, 0, 1);

   //	YOU16FLAG = 1;
	sethzmode(YOU16, hz_s[h]);//��������
	hide_mouse();
	unsigned int hzg_1[2] = { 0x5e2e,0x52a9 };//"����"
	unsigned  int  hzg1[7] = { 0x5de6,0x53f3,0x002f,0x4e0a,0x4e0b,0x7ffb,0x9875 };//����/���·�ҳ
	unsigned  int  hzg2[8] = { 0x0031,0x002e,0x70b9,0x51fb,0x7bad,0x5934,0x7b26,0x53f7 };//�����ͷ����
	unsigned  int  hzg3[7] = { 0x0032,0x002e,0x70b9,0x51fb,0x8fdb,0x5ea6,0x6761 };//���������
	unsigned  int  hzg4[10] = { 0x0033,0x002e,0x6309,0x4e0b,0x4e0a,0x4e0b,0x5de6,0x53f3,0x6309,0x952e };//�����������Ұ���
	unsigned  int  hzg5[7] = { 0x547d,0x4ee4,0x6a21,0x5f0f,0x6307,0x4ee4,0x8868 };//����ģʽָ���
	unsigned  int  hzg6[9] = { 0x8f93,0x5165,0x547d,0x4ee4,0x540e,0x6309,0x4e0b,0x56de,0x8f66 };//����������»س�
	unsigned  int  hzg7[2] = { 0x4f8b,0x5982 };//����
	unsigned  int  hzg8[18] = { 0x006f,0x0074,0x006c,0x0035,0x5f53,0x524d,0x663e,0x793a,0x7b2c,0x4e00,0x884c,0x8df3,0x8f6c,0x5230,0x603b,0x7b2c,0x4e94,0x884c };//��ǰ��ʾ��һ����ת���ܵ�����
	unsigned  int  hzg9[18] = { 0x006f,0x0074,0x0072,0x0035,0x5f53,0x524d,0x663e,0x793a,0x7b2c,0x4e00,0x5217,0x8df3,0x8f6c,0x5230,0x603b,0x7b2c,0x4e94,0x5217 };//��ǰ��ʾ��һ����ת���ܵ�����
	unsigned  int  hzg10[9] = { 0x006f,0x0064,0x006c,0x0035,0x5220,0x9664,0x7b2c,0x4e94,0x884c };//ɾ��������
	unsigned  int  hzg11[15] = { 0x006f,0x0061,0x0062,0x006c,0x0035,0x5728,0x7b2c,0x4e94,0x884c,0x4e0b,0x65b9,0x63d2,0x5165,0x7a7a,0x884c };//�ڵ������·��������
	unsigned  int  hzg12[20] = { 0x006f,0x0061,0x0063,0x006c,0x0035,0x5728,0x7b2c,0x4e94,0x884c,0x4e0b,0x65b9,0x63d2,0x5165,0x526a,0x8d34,0x677f,0x4e2d,0x7684,0x4e00,0x884c };//�ڵ������·�����������е�һ����
	unsigned  int  hzg13[15] = { 0x006f,0x0063,0x006c,0x0035, 0x5c06,0x7b2c,0x4e94,0x884c,0x590d,0x5236,0x5230,0x526a,0x8d34,0x677f,0x4e2d };//�������и��Ƶ���������
	unsigned  int  hzg130[15] = { 0x006f,0x0078,0x006c,0x0035, 0x5c06,0x7b2c,0x4e94,0x884c,0x526a,0x5207,0x5230,0x526a,0x8d34,0x677f,0x4e2d };//�������м��е���������
	unsigned  int  hzg14[4] = { 0x82f1,0x6587,0x542b,0x4e49 };//Ӣ�ĺ���
	unsigned  int  hzg15[6] = { 0x0074,0x003a,0x0074,0x006f,0x8df3,0x8f6c };//t:to��ת
	unsigned  int  hzg16[7] = { 0x006c,0x003a,0x006c,0x0069,0x006e,0x0065,0x884c };//l
	unsigned  int  hzg17[6] = { 0x0072,0x003a,0x0072,0x006f,0x0077,0x5217 };//r
	unsigned  int  hzg18[10] = { 0x0064,0x003a,0x0064,0x0065,0x006c,0x0065,0x0074,0x0065,0x5220,0x9664 };//d
	unsigned  int  hzg19[7] = { 0x0061,0x003a,0x0061,0x0064,0x0064,0x6dfb,0x52a0 };//a
	unsigned  int  hzg20[9] = { 0x0020,0x003a,0x0020,0x006c,0x0061,0x006e,0x0020,0x7a7a,0x767d };//b//���ں��ֿⲻȫ �� ����b��k �����ϣ�
	char blank_1[] = { 'b','\0' };
	char blank_2[] = { 'k','\0' };
	unsigned  int  hzg21[8] = { 0x0063,0x003a,0x0063,0x006f,0x0070,0x0079,0x590d,0x5236 };//c
	unsigned int hzg0[2] = { 0x786e,0x5b9a };
	hide_mouse();
	setbkcolor(0);
	cleardevice();
	barxy(0, 0, 640, 480, 15);//��Ļ���
	line(0, 32 + 10, 32 * 4 + 10, 32 + 10);//�ָ���
	setfillstyle(1, 7);
	bar(320 - 32 - 5 - 10, 480 - 50, 320 - 32 - 5 + 10 + 37 * 2, 480 - 50 + 32 + 10);
	//ȫ�õ�xy x1y1x2y2
	put_s_hz(0 + 10, 2, hzg_1, 2, YOU16);
	put_s_hz(320 - 32 - 5 - 10 + 30, 480 - 50 + 16, hzg0, 2, YOU16);//ȷ��
	put_s_hz(10, 32 + 12-28, hzg1, 7, YOU16);
	put_s_hz(230, 32 + 12-28, hzg2, 8, YOU16);
	put_s_hz(230, 32 + 12 + 28 * 1-28, hzg3, 7, YOU16);
	put_s_hz(230, 32 + 12 + 28 * 2-28, hzg4, 10, YOU16);
	put_s_hz(10, 32 + 12 + 28 * 3-28, hzg5, 7, YOU16);
	put_s_hz(230, 32 + 12 + 28 * 3-28, hzg6, 9, YOU16);
	put_s_hz(10, 32 + 12 + 28 * 4-28, hzg7, 2, YOU16);
	put_s_hz(10 + 70, 32 + 12 + 28 * 4-28, hzg8, 18, YOU16);
	put_s_hz(10 + 70, 32 + 12 + 28 * 5-28, hzg9, 18, YOU16);
	put_s_hz(10 + 70, 32 + 12 + 28 * 6-28, hzg10, 9, YOU16);
	put_s_hz(10 + 70, 32 + 12 + 28 * 7-28, hzg11, 15, YOU16);
	put_s_hz(10 + 70, 32 + 12 + 28 * 8-28, hzg12, 20, YOU16);
	put_s_hz(10 + 70, 32 + 12 + 28 * 9-28, hzg13, 15, YOU16);
	put_s_hz(10 + 70, 32 + 12 + 28 * 9 - 28+28, hzg130, 15, YOU16);
	put_s_hz(10, 32 + 12 + 28 * 10, hzg14, 4, YOU16);
	put_s_hz(10 + 170, 32 + 12 + 28 * 10, hzg15, 6, YOU16);
	put_s_hz(10 + 170 + 240, 32 + 12 + 28 * 10, hzg16, 7, YOU16);
	put_s_hz(10 + 170, 32 + 12 + 28 * 11, hzg17, 6, YOU16);
	put_s_hz(10 + 170 + 240, 32 + 12 + 28 * 11, hzg18, 10, YOU16);
	put_s_hz(10 + 170, 32 + 12 + 28 * 12, hzg19, 7, YOU16);
	put_s_hz(10 + 170 + 240, 32 + 12 + 28 * 12, hzg20, 9, YOU16);//blank
	outtextxy(10 + 170 + 240, 32 + 12 + 28 * 12+12, blank_1);
	outtextxy(10 + 170 + 240+32+2, 32 + 12 + 28 * 12 + 12, blank_1);
	outtextxy(10 + 170 + 240 + 32 + 2+64+7, 32 + 12 + 28 * 12 + 12, blank_2);
	put_s_hz(10 + 170, 32 + 12 + 28 * 13, hzg21, 8, YOU16);

	
	show_mouse();
}
void add_cl(Hnode *hnode, Hnode *hnode_c,int flag)//��hnode�к����hnode_c(��Ҫ���ƣ���
{
		Node *node_c = hnode_c->head;
		Hnode *hnode_c1 = (Hnode *)malloc(sizeof(Hnode));
		hnode_c1->next = NULL;

		Node *node_c1 = (Node *)malloc(sizeof(Node));

		node_c1->next = NULL;
		//hnode_c1->head = node_c1;
		if (node_c != NULL)
		{
			Node *node_c2 = (Node *)malloc(sizeof(Node));
			node_c2->chr = node_c->chr;
			node_c2->type = node_c->type;
			hnode_c1->head = node_c2;
			node_c = node_c->next;
			hnode_c1->head->next=NULL;
		}
		node_c1 = hnode_c1->head;
		while (node_c != NULL)
		{
			Node *node_c2 = (Node *)malloc(sizeof(Node));
			node_c2->chr = node_c->chr;
			node_c2->type = node_c->type;
			node_c1->next = node_c2;
			node_c2->next = NULL;
			node_c1 = node_c2;
			node_c = node_c->next;
		}
		if (flag == 1)
		{
			hnode_c1->next = hnode->next;
			hnode->next = hnode_c1;
		}
		else if (flag == 0)
		{
			Node *node_c2 = (Node *)malloc(sizeof(Node));
			node_c2=hnode_c1->head;
			hnode_c1->head = hnode_c1->head->next;
			hnode_c1->next = NULL;
			free(node_c2);

			hnode_c1->next = hnode->next;
			hnode->next = hnode_c1;
		}

}
Hnode * del_l(Hnode *hnode)//��hnode��ɾfree�� 
{
	Node *node;
	Node *node_p;
	Hnode *hnode_p;
	hnode_p = hnode->next;
	node = hnode->head;
	while (node != NULL)
	{
		node_p = node;
		node = node->next;
		free(node_p);
	}
	free(hnode);
	return hnode_p;
	
	//�����������ӵĲ�����������
	
}
Hnode* trans(Hnode *hnode, Cursornode *cursornode, int *row, int *cols)
{
	Node *node;
	Node *temp;
	Hnode *head = hnode;
	Cursornode cur_temp = *cursornode;
	*row = 1;
	int count = 0;
	int is_chinese = 0;
	int max_count = 0;
	while (hnode != NULL)
	{
		node = hnode->head;
		count = 0;
		while (node != NULL)
		{
			count++;
			if(node->chr <0x80)
			{
			  is_chinese=0;
			}
			else if (node->chr>=0x80&& count % 3 != 1)
			{
				cursornode->nowhnode = hnode;
				cursornode->nownode=temp;
				if (count % 3 == 2 && is_chinese!=1)
				{
					AddNode(cursornode, ' ');
					AddNode(cursornode, ' ');
					count += 2;
				}
				if (count % 3 == 0 && is_chinese!=1)
				{
					AddNode(cursornode, ' ');
					count++;
				}
				for (int i = 0; i < 2 && node != NULL; i++)
				{
					temp = node;
					node = node->next;
					count++;
				}
				is_chinese = 1;
			}
			else
			{
				for (int i = 0; i < 2 && node != NULL; i++)
				{
					temp = node;
					node = node->next;
					count++;
				}
			}
			if (node != NULL)
			{
				temp = node;
				node = node->next;
			}
		}
		if (count > max_count)
		{
			max_count = count;
		}

		hnode = hnode->next;
		(*row)++;
	}
	*cols = max_count;
	*cursornode =cur_temp;
	return head;
}
