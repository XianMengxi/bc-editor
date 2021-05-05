#include"chinese.h"
 //����ֵ��1->�ɹ���0��ʧ��

/*
 *@name:chinese
 *@msg:����������ܺ���
 *@param:{Hnode *} hnode ����ͷ
 *@param:{Cursornode *}cursornode ���λ��
 *@param:{int}h������� //�Ժ�ɾ��
 *@param:{int *}��ɫ��������
 *@param:{int}textflags ��ʾ��ǰ����������ʾ
 *@param:{int *}��¼�ں���ģʽ�°��µĲ˵�
 *@return:{Hnode *}�ı�������ͷ
*/
Hnode * chinese (Hnode * hnode,Cursornode * cursornode,int *menu_c,int *pcolor,int textflags)
{
	
	Hnode *hnode_cc = NULL; //���ڼ��а������ָ��
	//Node *node_ccp = NULL;
	//Node *node_cc = NULL;

	Hnode *hnode_cb=NULL; //��¼ǰһ���ڵ�

	Hnode *hnode_c=hnode;
	Hnode *p2 = hnode;

	int shr=0; //��¼������
	int shl=0; //��¼������

	char order[80]; //�����
	int o_n = 0;

	int flag_q2 = 0;

	int op; //��¼��ֵ
	short op1;

	int hl=0; //��¼���� ��ǰ��ʾ��Ϊ�ڼ���
	int hr = 1; //��¼���� ��ǰ��ʾ��Ϊ�ڼ���

	int i; //ÿ����ʾ
	int flag_c=0; //��¼���ĸ��˵���
	int flag3_c = 0; //��¼������
	int flag_q = 0; //����ʱ�ж��Ƿ���Ҫ���ȷ��

	int flag_o = 0; //��������ģʽ�������ж�
	int flag_o2 = 0; //�������������Ƿ���ȷ���ж�
	int q;

	int mouse_x;
	int mouse_y;

	char* hz_s[] = {
			"YOU16",
			"FS16",
			"HP16",
			"HT16",
			"MBXS16"
	};
	int h;
	h = ziti_set2();
	int graphdriver=VGA;
	int graphmode=2;
	initgraph(&graphdriver,&graphmode,"C:\\borlandc\\bgi");
	cleardevice();

	initmouse(1);
	
	static FILE* YOU16;
	sethzmode(YOU16,  hz_s[h]); //��������

	settextjustify(0, 0);
	settextstyle(0, 0, 1);

	p2 =trans(hnode, cursornode, &shl, &shr); //ת�������ֶ�����
	if (hr < 0)
	{
		hr = 1;
		if (textflags != 0)
			printlist_chinese(p2, pcolor, hl, hr ); //Ŀǰ�����hnodeΪp,colorΪpcolor
		else
			drawmain_c();
		probar(hl, shl, hr, shr);
	}
	else
	{
		if (textflags != 0)
			printlist_chinese(p2, pcolor, hl, hr ); //Ŀǰ�����hnodeΪp,colorΪpcolor
		else
			drawmain_c();
		probar(hl, shl, hr, shr);
	}
	
	while (1)
	{

		getmouse();
		mouse_x = M_x;
		mouse_y = M_y;

		if (M_sc < 0)
		{
			/*����˵�*/
			if (
				flag_q == 0
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
				(flag_c == 3) && !pd(42 * 8 + 4, 80 - (6 + 1) * 8, 80, 5 * 16) && flag3_c == 0
					)
				||
				(
				(flag_c == 4) && !pd((42 + 18) * 8 + 4, 80 - (6 + 1) * 8, 80, 4 * 16)
					)
				||
				(
				(flag3_c == 1)
					&& !pd(42 * 8 + 4, 80 - (6 + 1) * 8, 80, 4 * 16)
					&& !pd(400 - 6 * 8 + (11 * 8), 32 + 16 - 16, 16 * 6, 7 * 16)
					)
				||
				(
				(flag3_c == 2)
					&& !pd(42 * 8 + 4, 80 - (6 + 1) * 8, 80, 4 * 16)
					&& !pd(400 - 6 * 8 + (11 * 8), 32 + 16 + 16 - 16, 6 * 16, 7 * 16)
					)

				)

			{
				flag_c = 0;
				flag3_c = 0;
	
				if (textflags != 0)
					printlist_chinese(p2, pcolor, hl, hr); //Ŀǰ�����hnodeΪp,colorΪpcolor
				else
					drawmain_c();
				probar(hl, shl, hr, shr);
			}

			if (flag_c == 0 && pd(0, 0, 45, 16)) //ִ�б��빦��
			{
				unsigned int by_1[4] = { 0x8fd0,0x884c,0x9519,0x8bef }; //"���д���"
				unsigned int by_2[2] = { 0x786e,0x5b9a }; //"ȷ��
				unsigned int by_3[6] = { 0x7684,0x6570,0x91cf,0x4e0d,0x5339,0x914d }; //��������ƥ��
				unsigned int by_4[6] = { 0x7684,0x6570,0x91cf,0x4e0d,0x76f8,0x7b49 }; //�����������
				unsigned int by_5[6] = { 0x51fd,0x6570,0x672a,0x88ab,0x627e,0x5230 }; //����δ���ҵ�
				unsigned int by_6[5] = { 0x7684,0x6570,0x91cf,0x592a,0x5c11 }; //����������
				char by_k[] = {
					'(',')',
					'[',']',
					'{','}'
				};
				char by_k2[] = {
					'\'','\"'
				};

				char by_c1[] = { '(',')', '\0' };
				/*char by_c2[] = {'[', ']'};
				char by_c3[] = { '{','}' };
				*/char by_c4[] = { "main" };

				for (i = 0; i < 3; i++)
				{
					q = complie(p2, cursornode, 0, 1, by_k[2 * i], by_k[2 * i + 1]);
					if (q == 1)
					{
						draw_com();

						put_s_hz(96 + 20, 48 * 3 + 15, by_1, 4, YOU16);
						put_s_hz(320 - 32 - 5 - 10 + 30, 240 + 80 - 40 + 16, by_2, 2, YOU16);
						by_c1[0] = by_k[2 * i];
						by_c1[1] = by_k[2 * i + 1];
						outtextxy(96 + 20 + 20, 48 * 3 + 15 + 32 + 32, by_c1);
						put_s_hz(96 + 20 + 20 + 35, 48 * 3 + 15 + 32 + 32, by_3, 6, YOU16);
						flag_q = 1; //ȷ�������
						while (1)
						{
							getmouse();
							if (M_sc < 0 && flag_q == 1 && pd(320 - 32 - 5 - 10, 240 + 80 - 40, 10 * 2 + 37 * 2, 32 + 10)) //���ȷ����
							{
								flag_q = 0;

								break;
							}
						}
					}
					q = 0;
				}
				for (i = 0; i < 2; i++)
				{
					q = complie(p2, cursornode, 3, 1, by_k2[i], by_k2[i]);
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
							flag_q = 1; //ȷ�������
							while (1)
							{
								getmouse();
								if (M_sc < 0 && flag_q == 1 && pd(320 - 32 - 5 - 10, 240 + 80 - 40, 10 * 2 + 37 * 2, 32 + 10)) //���ȷ����
								{
									flag_q = 0;
									break;
								}
							}
						}
					}
					q = 0;
				}
				q = complie(p2, cursornode, 5, 1, '(', ')');
				if (q == 1)
				{
					draw_com();
					put_s_hz(96 + 20, 48 * 3 + 15, by_1, 4, YOU16);
					put_s_hz(320 - 32 - 5 - 10 + 30, 240 + 80 - 40 + 16, by_2, 2, YOU16);
					outtextxy(96 + 20 + 20, 48 * 3 + 15 + 32 + 32, by_c4);
					put_s_hz(96 + 20 + 20 + 35, 48 * 3 + 15 + 32 + 32, by_5, 6, YOU16);
					flag_q = 1; //ȷ�������
					while (1)
					{
						getmouse();
						if (M_sc < 0 && flag_q == 1 && pd(320 - 32 - 5 - 10, 240 + 80 - 40, 10 * 2 + 37 * 2, 32 + 10)) //���ȷ����
						{
							flag_q = 0;
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
					flag_q = 1; //ȷ�������
					while (1)
					{
						getmouse();
						if (M_sc < 0 && flag_q == 1 && pd(320 - 32 - 5 - 10, 240 + 80 - 40, 10 * 2 + 37 * 2, 32 + 10)) //���ȷ����
						{
							flag_q = 0;
					
							break;
						}
					}
				}

				unsigned int by_11[] = { 0x63d0,0x793a }; //��ʾ
				unsigned int by_22[] = { 0x6682,0x672a,0x627e,0x5230,0x9519,0x8bef }; //��δ�ҵ�����
				draw_com();
				put_s_hz(96 + 20, 48 * 3 + 15, by_11, 2, YOU16);
				put_s_hz(320 - 32 - 5 - 10 + 30, 240 + 80 - 40 + 16, by_2, 2, YOU16);
				put_s_hz(96 + 20 + 20 + 35, 48 * 3 + 15 + 32 + 32, by_22, 6, YOU16);
				flag_q = 1; //ȷ�������
				while (1)
				{
					getmouse();
					if (M_sc < 0 && flag_q == 1 && pd(320 - 32 - 5 - 10, 240 + 80 - 40, 10 * 2 + 37 * 2, 32 + 10)) //���ȷ����
					{
						flag_q = 0;

						break;
					}
				}

				if (textflags != 0)
				{
					printlist_chinese(p2, pcolor, hl, hr); //Ŀǰ�����hnodeΪp,colorΪpcolor

				}
				else
					drawmain_c();
				probar(hl, shl, hr, shr);
				flag_c = 0;
				flag3_c = 0;
			}
			if (flag_q == 0 && pd(0, 480 - 20, 10, 480)) //���������������ͷ
			{
				if(hr==1)
					;
				else
				{
					if (textflags != 0)
					{
						hr = menu_cl(p2, hr); //����ֵΪhr, //����ֵΪp2
						printlist_chinese(p2, pcolor, hl, hr);
					}
					probar(hl, shl, hr, shr);
				}
			}
			if (flag_q == 0 && pd(640 - 10, 480 - 20, 640, 480)) //�������������Ҽ�ͷ
			{
				if (hr == shr)
					;
				else
				{
					if (textflags != 0)
					{
						hr = menu_cr(p2, hr); //����ֵΪhr, //����ֵΪp2
						printlist_chinese(p2, pcolor, hl, hr);
					}
					probar(hl, shl, hr, shr);
				}
			}
			else	if (flag_q == 0 && pd(0 + 10, 480 - 20, 640 - 10, 480)) //bar(0, 480 - 20, 640, 480);������Ǻ��������hr���
			{
				if (textflags != 0)
				{
					hr = (int)((float)(mouse_x - 10) / 600.0*shr); //�����㷨
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
							hr = shr - 1;
						}
						if (shr % 3 == 0)
						{
							hr = shr - 2;
						}
						else //shr%3==1
						{
							hr = shr;
						}
					}
					if (hr < 1)
					{
						hr = 1;
					}

					printlist_chinese(p2, pcolor, hl, hr); //Ŀǰ�����hnodeΪp,colorΪpcolor
				}
				probar(hl, shl, hr, shr);
			}
			else if (flag_q == 0 && pd(640 - 14, 26, 640, 26 + 10)) //����ϼ�ͷ
			{
				if (hl == 0); //��Ч 
				else
				{
					
					if (textflags != 0)
					{
						hl--; //��ǰ��һ����ʾ��ʵ��������1
						hnode_c = p2; //hnode����ָ���һ�� 
						printlist_chinese(p2, pcolor, hl, hr);
					}
					else
						drawmain_c();
					probar(hl, shl, hr, shr);
				}
			}
			else if (flag_q == 0 && pd(640 - 14, 480 - 30, 640, 480 - 20)) //����¼�ͷ
			{
				 //hnode = p; //hnode����ָ���һ��
				if (textflags != 0)
				{
					hnode_c = p2;
					for (i = 1; i < hl; i++)
						hnode_c = hnode_c->next; //hnodeָ��������ʾ�ĵ�һ�� 
					if (hnode_c->next == 0); //��ǰ��ʾ�ĵ�һ��Ϊʵ�ʵ����һ�У�������DOWN
					else
					{

						if (textflags != 0)
						{
							hl++; //��ǰ��һ����ʾ��ʵ��������1
							hnode_c = p2;
							printlist_chinese(p2, pcolor, hl, hr);
						}
						else
							drawmain_c();
						probar(hl, shl, hr, shr);
					}
				}
			}
			else if (flag_q == 0 && pd(640 - 14, 26, 640, 480 - 20))
			{
				if (textflags != 0)
				{
					hl = (int)((float)(mouse_y - 40) / 367.0*shl); //�����㷨
					if (hl > shl)
					{
						hl = shl;
					}
					else if (hl < 1)
					{
						hl = 1;
					}

					printlist_chinese(p2, pcolor, hl, hr); //Ŀǰ�����hnodeΪp,colorΪpcolor
				}
				else
					drawmain_c();
				probar(hl, shl, hr, shr);
			}

			if (flag_q == 0 && pd(6 * 8 + 4, 0, 88, 16)) //�����File������
			{
				flag_c = 1;
			   //	hnode = p; //����ָ���һ��
				drawmenu_c(F1, p2, hl, hr, pcolor, textflags);
				probar(hl, shl, hr, shr);

			}
			else if (flag_q == 0 && pd(24 * 8 + 4, 0, 80, 16)) //�����Edit������
			{
				flag_c = 2;
			    //	hnode = p; //����ָ���һ��
				drawmenu_c(F2, p2, hl, hr, pcolor, textflags);
				probar(hl, shl, hr, shr);

			}

			else if (flag_q == 0 && pd(42 * 8 + 4, 0, 8 * 13, 16)) //�����settings������
			{
				flag_c = 3;
			   //	hnode = p; //����ָ���һ��
				drawmenu_c(F3, p2, hl, hr, pcolor, textflags);
				probar(hl, shl, hr, shr);


			}
			else if (flag_c == 0 && pd(60 * 8 + 4, 0, 8 * 14, 16)) //�����pattern������
			{
				flag_c = 4;
				drawmenu_c(F4, p2, hl, hr, pcolor, textflags);
				probar(hl, shl, hr, shr);
			}

			 //File�˵���֮��ļ����Ӳ˵�
			else if (flag_q == 0 && pd(6 * 8 + 4, 80 - 6 * 8, 88, 16) && flag_c == 1) //�½�
			{
				closegraph();
				initmouse(0);
				*menu_c = 1;
				if (hnode_cc != NULL)
					free_copy( hnode_cc);
				hnode_cc =NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(6 * 8 + 4, 80 - 4 * 8, 88, 16) && flag_c == 1) //��
			{
				
				closegraph();
				initmouse(0);
				*menu_c = 2;
				if (hnode_cc != NULL)
					free_copy( hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(6 * 8 + 4, 80 - 2 * 8, 88, 16) && flag_c == 1) //����	
			{
				closegraph();
				initmouse(0);
				*menu_c = 3;
				if (hnode_cc != NULL)
					free_copy( hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(6 * 8 + 4, 80 - 0 * 8, 88, 16) && flag_c == 1) //���Ϊ
			{
				closegraph();
				initmouse(0);
				*menu_c = 4;
				if (hnode_cc != NULL)
					free_copy( hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(6 * 8 + 4, 80 - (-2) * 8, 88, 16) && flag_c == 1) //�ı�·��
			{
				closegraph();
				initmouse(0);
				*menu_c = 5;
				if (hnode_cc != NULL)
					free_copy(hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(6 * 8 + 4, 80 - (-4) * 8, 88, 16) && flag_c == 1) //�ر�
			{
				closegraph();
				initmouse(0);
				*menu_c = 6;
				if (hnode_cc != NULL)
					free_copy(hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(6 * 8 + 4, 80 - (-6) * 8, 88, 16) && flag_c == 1) //�˳�
			{
				closegraph();
				initmouse(0);
				*menu_c = 7;
				ClearLists(p2);
				free(p2);
				if (hnode_cc != NULL)
					free_copy(hnode_cc);
				hnode_cc = NULL;
				p2 = NULL;
				exit(0);
				
			}
			/*Edit�˵���֮��ļ����Ӳ˵�*/
			else if (flag_q == 0 && pd(24 * 8 + 4, 80 - 6 * 8, 80, 16) && flag_c == 2) // ����
			{
				closegraph();
				initmouse(0);
				*menu_c = 11;
				if (hnode_cc != NULL)
					free_copy( hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(24 * 8 + 4, 80 - 4 * 8, 80, 16) && flag_c == 2) //����	
			{
				closegraph();
				initmouse(0);
				*menu_c = 12;
				if (hnode_cc != NULL)
					free_copy( hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(24 * 8 + 4, 80 - 2 * 8, 80, 16) && flag_c == 2) //ճ��
			{
				closegraph();
				initmouse(0);
				*menu_c = 13;
				if (hnode_cc != NULL)
					free_copy( hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(24 * 8 + 4, 80 - 0 * 8, 80, 16) && flag_c == 2) //����
			{
				closegraph();
				initmouse(0);
				*menu_c = 14;
				if (hnode_cc != NULL)
					free_copy(hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(24 * 8 + 4, 80 -(-2) * 8, 80, 16) && flag_c == 2) //�滻
			{
				closegraph();
				initmouse(0);
				*menu_c = 15;
				if (hnode_cc != NULL)
					free_copy(hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			/*Settings�˵���֮��ļ����Ӳ˵�*/
			else if (flag_q == 0 && pd(42 * 8 + 4, 80 - 6 * 8, 80, 16) && flag_c == 3)
			{

				flag3_c = 1;
				drawmenu_c(1, p2, hl, hr, pcolor, textflags);
				probar(hl, shl, hr, shr);
			} // ����
			else if (flag_q == 0 && pd(42 * 8 + 4, 80 - 4 * 8, 80, 16) && flag_c == 3)
			{

				flag3_c = 2;
				drawmenu_c(2, p2, hl, hr, pcolor, textflags);
				probar(hl, shl, hr, shr);
			} //��ɫ
			else if (flag_q == 0 && pd(42 * 8 + 4, 80 - 2 * 8, 80, 16) && flag_c == 3) //��������
			{
				flag_c = 0;
				draw_help();
				flag_q2 = 1;
				show_mouse();
				while (1)
				{
					getmouse();
					if (M_sc < 0 && pd(320 - 32 - 5 - 10, 480 - 50, 320 - 32 - 5 + 10 + 37 * 2, 480 - 50 + 32 + 10) && flag_q2 == 1)
					{
						

						break;
					}
				}
				draw_help2();
				show_mouse();
				while (1)
				{
					getmouse();
					if (M_sc < 0 && pd(320 - 32 - 5 - 10, 480 - 50, 320 - 32 - 5 + 10 + 37 * 2, 480 - 50 + 32 + 10) && flag_q2 == 1)
					{
						flag_q2 = 0;
						break;
					}
				}

				if (textflags != 0)
				{
					printlist_chinese(p2, pcolor, hl, hr); //Ŀǰ�����hnodeΪp,colorΪpcolor
					probar(hl, shl, hr, shr);
				}
				else
					drawmain_c();
			}
			else if (flag_q == 0 && pd((42 + 18) * 8 + 4, 80 - 6 * 8, 80, 16) && flag_c == 4)
			{
				flag_c = 0;
				if (hnode_cc != NULL)
				{
					free_copy(hnode_cc);
				}
				hnode_cc = NULL;
				closegraph();
				initmouse(0);
				*menu_c = 0;
				return p2;


			} // Ӣ�ı༭
			else if (flag_q == 0 && pd((42 + 18) * 8 + 4, 80 - 4 * 8, 80, 16) && flag_c == 4)
			{
				flag_c = 0;
				if (textflags != 0)
				{
					printlist_chinese(p2, pcolor, hl, hr); //Ŀǰ�����hnodeΪp,colorΪpcolor

				}
				else
					drawmain_c();
				probar(hl, shl, hr, shr);
				continue;


			} // ��������
			if (flag_q == 0 && flag3_c == 1)
			{

				for (i = 0; i < 5; i++)
				{
					if (pd(400 - 6 * 8 + (11 * 8), 32 + 16 * (i + 1), 16 * 6, 16))
					{
						flag_c = 0;
						flag3_c = 0;
						h = i; //�ı䴫��chinese�������ַ�����hΪ�����±꣩
						ziti_set(i);
						sethzmode(YOU16, hz_s[h]); //��������
						settextjustify(0, 0);
						settextstyle(0, 0, 1);
						
						if (textflags != 0)
							printlist_chinese(p2, pcolor, hl, hr);
						else
							drawmain_c();
						probar(hl, shl, hr, shr);
					}
				}
				continue;
			}
			if (flag_q == 0 && flag3_c == 2)
			{
				for (i = 0; i < 5; i++)
				{
					if (pd(400 - 6 * 8 + (11 * 8), 32 + 16 + 16 * (i + 1), 6 * 16, 16))

					{
						flag_c = 0;
						flag3_c = 0;

						color_set(i);
						color_set2(pcolor);

						High_li(p2, cursornode, pcolor[0], 0); //��������ɫ������
						High_li(p2, cursornode, pcolor[1], 1);
						High_li(p2, cursornode, pcolor[2], 2);
						High_li(p2, cursornode, pcolor[3], 3);
						High_li(p2, cursornode, pcolor[4], 4);
						High_li(p2, cursornode, pcolor[5], 5);

						if (textflags != 0)
							printlist_chinese(p2, pcolor, hl, hr); //Ŀǰ�����hnodeΪp,colorΪpcolor
						else
							drawmain_c();
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
			else if (op == F1 || op == F2 || op == F3 || op == F4)
			{
			  //	hnode = p; //����ָ���һ��
				drawmenu_c(op, hnode, hl, hr, pcolor, textflags);
				probar(hl, shl, hr, shr);
				if (op == F1) flag_c = 1; //��¼�˵�λ��
				if (op == F2) flag_c = 2;
				if (op == F3) flag_c = 3;
				if (op == F4) flag_c = 4;
			}
			else if (op == UP)
			{
				if (textflags != 0)
				{
					if (hl == 0); //��Ч 
					else
					{

						hl--; //��ǰ��һ����ʾ��ʵ��������1
						hnode_c = p2; //hnode����ָ���һ�� 
						if (textflags != 0)
							printlist_chinese(p2, pcolor, hl, hr);
						else
							drawmain_c();
						probar(hl, shl, hr, shr);
					}
				}
			}
			else if (op == DOWN) //��Ч�������ǵ�ǰΪ���һ�� 
			{
				if (textflags != 0)
				{
					hnode_c = p2;
					for (i = 1; i < hl; i++)
						hnode_c = hnode_c->next; //hnodeָ��������ʾ�ĵ�һ�� 
					if (hnode_c->next == 0); //��ǰ��ʾ�ĵ�һ��Ϊʵ�ʵ����һ�У�������DOWN
					else
					{

						hl++; //��ǰ��һ����ʾ��ʵ��������1
						hnode_c = p2;
						if (textflags != 0)
							printlist_chinese(p2, pcolor, hl, hr);
						else
							drawmain_c();
						probar(hl, shl, hr, shr);
					}
				}

			}
			else if (op == LEFT)
			{
				if (textflags != 0)
				{
					if (hr == 1)
						;
					else
					{
						hr = menu_cl(p2, hr); //����ֵΪhr, //����ֵΪp2
						if (textflags != 0)
							printlist_chinese(p2, pcolor, hl, hr);
						else
							drawmain_c();
						probar(hl, shl, hr, shr);
					}
				}

			}
			else if (op == RIGHT)
			{
				if (textflags != 0)
				{
					if (hr == shr)
						;
					else
					{
						hr = menu_cr(p2, hr); //����ֵΪhr, //����ֵΪp2
						if (textflags != 0)
							printlist_chinese(p2, pcolor, hl, hr);
						else
							drawmain_c();
						probar(hl, shl, hr, shr);
					}
				}
			}
			else if ((op & 0x00ff) == 'o') //����ָ������ģʽ oΪorder
			{

				flag_o2 = 0; //��������δ��ȷ��
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
				if (order[0] == 't') //��תָ��
				{
					if (order[1] == 'l') //��ת��ָ��
					{
						for (i = 0; order[2 + i] != '\0'; i++)
						{
							if (order[2 + i] >= '0'&&order[2 + i] <= '9')
							{
								;
							}
							else //ֻҪ�����һ���������֣��Ͳ���������
							{
								flag_o = -1;
							}
						}
						if (flag_o == 0)
						{
							o_n = atoi(&order[2]);
							if (o_n >= 1 && o_n <= shl)
							{
								hl = o_n - 1; //hlΪ0ʱ��ʾ��һ��
							}
						}
						flag_o2 = 1;
						flag_o = 0;
					}
					else if (order[1] == 'r') //��ת��ָ��
					{
						for (i = 0; order[2 + i] != '\0'; i++)
						{
							if (order[2 + i] >= '0'&&order[2 + i] <= '9')
							{
								;
							}
							else //ֻҪ�����һ���������֣��Ͳ���������
							{
								flag_o = -1;
							}
						}
						if (flag_o == 0)
						{
							o_n = atoi(&order[2]);

							if (o_n % 3 == 2) //����
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
							hr = o_n; //hrΪ0ʱ��ʾ��һ��
							flag_o2 = 1;
							flag_o = 0;
						}
					}
				}
					else if (order[0] == 'd') //����ɾ��ָ��ģʽ
					{
						if (order[1] == 'l') //ɾ����
						{
							for (i = 0; order[2 + i] != '\0'; i++)
							{
								if (order[2 + i] >= '0'&&order[2 + i] <= '9');
								else //ֻҪ�����һ���������֣��Ͳ���������
									flag_o = -1;
							}
							if (flag_o == 0)
							{
								o_n = atoi(&order[2]);
								if (o_n >= 1 && o_n <= shl)
								{
									hnode_c = p2; //����ָ���һ��
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
						hnode_c = p2;
						chigh_li(hnode_c);
						hnode_c = p2;
						for (i = 0; i < 6; i++)
						{
							High_li(hnode_c, cursornode, pcolor[i], i);
						}
					}
					else if (order[0] == 'a') //������ӣ��У�ָ��ģʽ add
					{

						if (order[1] == 'b') //��ӿգ��У�
						{
							if (order[2] == 'l') //�����
							{
								for (i = 0; order[3 + i] != '\0'; i++)
								{
									if (order[3 + i] >= '0'&&order[3 + i] <= '9');
									else //ֻҪ�����һ���������֣��Ͳ���������
										flag_o = -1;
								}
								if (flag_o == 0)
								{
									o_n = atoi(&order[3]);
									if (o_n >= 1 && o_n <= shl)
									{
										hnode_c = p2; //����ָ���һ��
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
						else if (order[1] == 'c') //��Ӽ������е��Ѿ������˵ģ���
						{

							if (order[2] == 'l') //�����
							{
								for (i = 0; order[3 + i] != '\0'; i++)
								{
									if (order[3 + i] >= '0'&&order[3 + i] <= '9');
									else //ֻҪ�����һ���������֣��Ͳ���������
										flag_o = -1;
								}
								if (flag_o == 0)
								{
									o_n = atoi(&order[3]);
									if (o_n >= 1 && o_n <= shl)
									{
										hnode_c = p2; //����ָ���һ��
										for (i = 1; i < o_n; i++)
										{
											hnode_c = hnode_c->next;
										}
										 //node_c = hnode_cc->head->next;
										if (hnode_cc != NULL)
										{
											add_cl(hnode_c, hnode_cc); //��hnode�к����hnode_c(��Ҫ���ƣ���

											shl += 1;
											flag_o = 0;

											flag_o2 = 1;
										}
										else
											flag_o2 = 0;
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
					else if (order[0] == 'c' || order[0] == 'x') //���븴��ĳ��ģʽ�����Ƶ�������
					{
						if (order[1] == 'l') //����ĳ��
						{
							for (i = 0; order[2 + i] != '\0'; i++)
							{
								if (order[2 + i] >= '0'&&order[2 + i] <= '9');
								else //ֻҪ�����һ���������֣��Ͳ���������
									flag_o = -1;
							}
							if (flag_o == 0)
							{
								o_n = atoi(&order[2]);
								if (o_n >= 1 && o_n <= shl)
								{
									flag_o2 = 1;

									if (hnode_cc != NULL)
									{
										free_copy(hnode_cc);
									}
									hnode_cc = NULL;
									hnode_c = p2; //����ָ���һ��

									for (i = 1; i < o_n; i++)
									{
										hnode_c = hnode_c->next;

									}
									hnode_cc = (Hnode *)malloc(sizeof(Hnode));
									copy_l(hnode_c, hnode_cc);

									if (order[0] == 'x') //������Ҫɾ����ԭ����
									{
										hnode_c = p2; //����ָ���һ��
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
											p2 = del_l(hnode_c); //��hnode��ɾfree�� ����ɾ����һ���ں���������
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
					unsigned int o_1[2] = { 0x63d0,0x793a }; //��ʾ
					unsigned int o_4[2] = { 0x786e,0x5b9a }; //ȷ��
					put_s_hz(96 + 20, 48 * 3 + 15, o_1, 2, YOU16); //��ʾ
					put_s_hz(320 - 32 - 5 - 10 + 30, 240 + 80 - 40 + 16, o_4, 2, YOU16); //ȷ��
					unsigned int o_2[6] = { 0x547d,0x4ee4,0x8f93,0x5165,0x6b63,0x786e }; //����������ȷ
					unsigned int o_3[6] = { 0x547d,0x4ee4,0x8f93,0x5165,0x9519,0x8bef }; //�����������
					if (flag_o2 == 0) //�����˴��������
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

					flag_o2 = 0; //��������δ�ɹ�
					if (textflags != 0)
						printlist_chinese(p2, pcolor, hl, hr);
					else
						drawmain_c();
					probar(hl, shl, hr, shr);

			}
		}
	}
}

/*
 *@name:drawmain_c
 *@msg:��ͼ�ν�����������
 *@param:{void}
 *@return:{void}
*/
 void drawmain_c() //������������ 
 {
 	
	hide_mouse();										
	setbkcolor(0); //��������Ϊ��ɫ��Ϊ�˳����֣�֮������0��Ȼ�Ǳ�����ɫ����֮���� 
	cleardevice(); //���� 
	
	barxy(0, 0, 640, 16, 7);   //�ϲ˵��ҿ� 

	setfillstyle(1, DARKGRAY); //������
	bar(0, 480 - 20, 640, 480);
	
	 //barxy(0,480-16,640,480,7);   //�²˵�
	barxy(0,16,640,480-32,1);   //��ɫ������  //Ϊʲô�Ǽ�32����16���±߻ᱻ������ȥ 

	bar(640 - 14, 26, 640, 480 - 20); //������

	setcolor(15); //�׿�
	
	line(2,16+5,2,480-16-5); //���׿� 
	line(3,16+5,3,480-16-5);
	line(3+4,16+8,3+4,480-16-8);
	line(3+5,16+8,3+5,480-16-8);
	
	 
    line(2, 16+5 , 640, 16+5); //��׿�
	line(2, 16+6 , 640, 16+6); 
    line(2+5, 16+8 , 640, 16+8);
    line(2+5, 16+9 , 640, 16+9); //�� 
    line(2, 480-(16+5), 640, 480-(16+5));
	line(2, 480-(16+6), 640, 480-(16+6)); 
    line(2+5, 480-(16+8), 640, 480-(16+8));
    line(2+5, 480-(16+9), 640, 480-(16+9)); //�� 
    
	static FILE* YOU16; 
	sethzmode(YOU16, "YOU16"); //��������
	settextjustify(0, 0);
	settextstyle(0, 0, 1);

    unsigned  int  hzk1[6]  =  {  0x6587  ,0x4ef6  ,0x46  ,0x31  }; //"�ļ�F1"    
    unsigned  int  hzk2[6]  =  {  0x4fee  ,0x6539  ,0x46  ,0x32  }; //"�޸�F2"    
    unsigned  int  hzk3[6]  =  {  0x8bbe  ,0x7f6e  ,0x46  ,0x33  }; //"����F3"    
	unsigned  int  hzk4[6]  =  {  0x6a21  ,0x5f0f  ,0x46  ,0x34  }; //"ģʽF4"
	unsigned  int  hzk5[2]  =  { 0x8fd0,0x884c }; //"����"
	
	setcolor(0);
	line(5 * 8 + 5, 0, 5 * 8 + 5, 16);

	line(6 * 8 + 4, 2, 6 * 8 + 4, 14);   //�����ߺ����ߣ���˵��ĸ��� 
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
	put_s_hz(80 - 2 * 8, 0, hzk1, 4, YOU16);  //��ʾ����  
	put_s_hz(240 - 4 * 8, 0, hzk2, 4, YOU16);  
	put_s_hz(400 - 6 * 8, 0, hzk3, 4, YOU16);  
	put_s_hz(560 - 8 * 8, 0, hzk4, 4, YOU16);   
	
	setfillstyle(1, DARKGRAY);
	bar(0, 480 - 20, 640, 480);

	setcolor(0); //�������εļ�ͷ
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
/*
 *@name:drawmenu_c
 *@msg:��ͼ�ν���˵�
 *@param:{int}op ��ѭ���а��µİ���ɨ����
 *@param:{Hnode *}hnode ����ͷ
 *@param:{int}hl ��ǰ������������
 *@param:{int}hr ��ǰ�����б�����
 *@param:{int *}pcolor ��ɫ����
 *@param:{int}textflags ��ǰ����������ʾ�ı�־
 *@return:{void}
*/
 void drawmenu_c(int op,Hnode *hnode,int hl,int hr,int *pcolor,int textflags) //�����Ĳ˵�
 {
	int i;
	
	
	static FILE* YOU16;
	sethzmode(YOU16, "YOU16"); //������Բ16������
	settextjustify(0, 0);
	settextstyle(0, 0, 1);

	

 	
	switch(op)
	{
		case 1: //���������˵� ����
			hide_mouse();
			drawmenu_c(F3,hnode,hl,hr,pcolor, textflags);
			barxy((42 + 11) * 8, 16 + 16, 12 * 8, 7 * 16, LIGHTGRAY);

			line((42+11+1) * 8, 24+16, (42 + 11 + 1) * 8, 24+16 + 6 * 16);   //����
			line((42 + 11 + 1) * 8, 24 +16+ 6 * 16, (42 + 11 + 1) * 8 + 10 * 8, 24+16 + 6 * 16);   //����
			line((42 + 11 + 1) * 8 + 10 * 8, 24 +16+ 6 * 16, (42 + 11 + 1) * 8 + 10 * 8, 24+16); //����
			line((42 + 11 + 1) * 8 + 10 * 8, 24+16, (42 + 11 + 1) * 8, 24+16);   //�Ϻ���

			unsigned int hzk1_1[2] = { 0x89c4,0x8303 }; //"�淶"
			unsigned int hzk2_1[2] = { 0x6977,0x4f53 }; //"����"
			unsigned int hzk3_1[2] = { 0x5e7c ,0x5706 }; //"��Բ"
			unsigned int hzk4_1[2] = { 0x659c,0x4f53 }; //"б��"
			unsigned int hzk5_1[2] = { 0x4e66,0x6cd5 }; //"�鷨"
			put_s_hz(400 - 6 * 8+(11*8), 32+16, hzk1_1, 2, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 48+16, hzk2_1, 2, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 64+16, hzk3_1, 2, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 80+16, hzk4_1, 2, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 96+16, hzk5_1, 2, YOU16);
			show_mouse();
			break;
		case 2:
			hide_mouse();
			drawmenu_c(F3,hnode,hl,hr,pcolor, textflags);
			barxy((42 + 11) * 8, 16 + 16*2, 12 * 8, 7 * 16, LIGHTGRAY);

			line((42 + 11 + 1) * 8, 24 + 16+16, (42 + 11 + 1) * 8, 24 + 16 + 16+6 * 16);   //����
			line((42 + 11 + 1) * 8, 24 + 16 +16+ 6 * 16, (42 + 11 + 1) * 8 + 10 * 8, 24 +16+ 16 + 6 * 16);   //����
			line((42 + 11 + 1) * 8 + 10 * 8, 24 + 16 +16+ 6 * 16, (42 + 11 + 1) * 8 + 10 * 8, 24+16 + 16); //����
			line((42 + 11 + 1) * 8 + 10 * 8, 24 +16+16, (42 + 11 + 1) * 8, 24+16 + 16);   //�Ϻ���

			unsigned int hzk1_2[4] = { 0x53d6 ,0x6d88,0x989c,0x8272 }; //"ȡ����ɫ"
			unsigned int hzk2_2[3] = { 0x989c,0x8272 ,0x4e00 }; //"��ɫһ"
			unsigned int hzk3_2[3] = { 0x989c,0x8272 ,0x4e8c }; //"��ɫ��"
			unsigned int hzk4_2[3] = { 0x989c,0x8272 , 0x4e09 }; //"��ɫ��"
			unsigned int hzk5_2[3] = { 0x989c,0x8272 ,0x56db }; //"��ɫ��"
			put_s_hz(400 - 6 * 8 + (11 * 8), 32 + 16+16, hzk1_2, 4, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 48 + 16+16, hzk2_2, 3, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 64 + 16+16, hzk3_2, 3, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 80 + 16+16, hzk4_2, 3, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 96 + 16+16, hzk5_2, 3, YOU16);
			show_mouse();
			break;



		case F1: //��File
				hide_mouse();
				if (textflags != 0)
					printlist_chinese(hnode, pcolor, hl, hr);
				else
					drawmain_c();

				//barxy(6 * 8 + 4, 16, 11 * 8, 7 * 16, LIGHTGRAY);
				barxy(6 * 8 + 4, 16, 11 * 8, 7 * 16+2*16, LIGHTGRAY);
				setcolor(0);
				/*
				line(7 * 8, 24, 7 * 8, 24 + 6 * 16);   //����
				line(7 * 8, 24 + 6 * 16, 7 * 8 + 10 * 8, 24 +6 * 16);   //����
				line(7 * 8 + 10 * 8, 24 +  6* 16, 7 * 8 + 10 * 8, 24); //����
				line(7 * 8 + 10 * 8, 24, 7 * 8, 24);   //�Ϻ���
				*/
				line(7 * 8, 24, 7 * 8, 24 + 8 * 16);   //����
				line(7 * 8, 24 + 8 * 16, 7 * 8 + 10 * 8, 24 + 8 * 16);   //����
				line(7 * 8 + 10 * 8, 24 + 8 * 16, 7 * 8 + 10 * 8, 24); //����
				line(7 * 8 + 10 * 8, 24, 7 * 8, 24);   //�Ϻ���
				unsigned int hzk1[2] = { 0x65b0 ,0x5efa }; //"�½�"
				unsigned int hzk2[2] = { 0x5f00 ,0x542f }; //"����"
				unsigned int hzk3[2] = { 0x4fdd ,0x5b58 }; //"����"
				unsigned int hzk4[3] = { 0x53e6 ,0x5b58 ,0x4e3a }; //"���Ϊ"
				unsigned int hzk5[2] = { 0x9000 ,0x51fa }; //"�˳�"
				unsigned int hzf1[4] = {0x6539,0x53d8,0x8def,0x5f84};//�ı�·��
				unsigned int hzf2[2] = {0x5173,0x95ed};//�ر�
				put_s_hz(80 - 2 * 8, 32, hzk1, 2, YOU16);
				put_s_hz(80 - 2 * 8, 48, hzk2, 2, YOU16);
				put_s_hz(80 - 2 * 8, 64, hzk3, 2, YOU16);
				put_s_hz(80 - 2 * 8, 80, hzk4, 3, YOU16);
				//put_s_hz(80 - 2 * 8, 96, hzk5, 2, YOU16);
				put_s_hz(80 - 2 * 8, 96, hzf1, 4, YOU16);
				put_s_hz(80 - 2 * 8, 96+16, hzf2, 2, YOU16);
				put_s_hz(80 - 2 * 8, 96+16+16, hzk5, 2, YOU16);
				show_mouse();
			break;
		case F2: //��Edit
				hide_mouse();
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
				unsigned int hzk6[2] = { 0x590d ,0x5236 }; //"����"
				unsigned int hzk7[2] = { 0x526a ,0x5207 }; //"����"
				unsigned int hzk8[2] = { 0x7c98 ,0x8d34 }; //"ճ��"
				unsigned int hzk9[2] = { 0x67e5 ,0x627e }; //"����"
				unsigned int hzk10[2] = { 0x66ff ,0x6362 }; //"�滻"
				put_s_hz(240 - 4 * 8, 32, hzk6, 2, YOU16);
				put_s_hz(240 - 4 * 8, 48, hzk7, 2, YOU16);
				put_s_hz(240 - 4 * 8, 64, hzk8, 2, YOU16);
				put_s_hz(240 - 4 * 8, 80, hzk9, 2, YOU16);
				put_s_hz(240 - 4 * 8, 96, hzk10, 2, YOU16);
				show_mouse();
			break;
		case F3: //��Settings
				hide_mouse();

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

				unsigned int hzk11[2] = { 0x5f62,0x4f53 }; //"����"
				unsigned int hzk12[2] = { 0x989c,0x8272 }; //"��ɫ"
				unsigned int hzk13[2] = { 0x5e2e,0x52a9 }; //"����"

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

			unsigned int hzk14[4] = { 0x82f1,0x6587,0x7f16,0x8f91 }; //"Ӣ�ı༭"
			unsigned int hzk15[2] = { 0x6c49,0x5316 }; //"��������"

			put_s_hz(400 - 6 * 8+18*8, 32, hzk14, 4, YOU16);
			put_s_hz(400 - 6 * 8+18*8, 48, hzk15, 2, YOU16);

			show_mouse();
			break;
	 }
 }
/*
 *@name:printline_chinese
 *@msg:��ӡ����ģʽ��һ������
 *@param:{Hnode *}hnode ����ͷ
 *@param:{FILE *}YOU16 �����ļ�ָ��
 *@param:{int *}color ��ɫ����
 *@param:{int}hr ��ǰ��ʾ������
 *@return:{void}
*/
void printline_chinese(Hnode* hnode,FILE * YOU16,int color[],int hr) //�ڵ�ǰλ�����hnodeָ�����һ��
{
	hide_mouse();
	settextjustify(0,0);
	settextstyle(0,0,1);
	unsigned short uni;

	char alp[2]={'\0','\0'}; //���Ӣ�ģ��Ǻ���
	Node * tnode;
	int x,y; //���������Ҫ����
	int i; //��������
	tnode=hnode->head; //��һ��Node
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
			int ischinese = utf_8_to_16(tnode, &uni);
			if (ischinese)
			{
				put_a_hz(x, y-12, uni, YOU16, color[tnode->type], -1); //�ֶ�����������λ��
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
		tnode=tnode->next; //ָ����һ��Node 
	} //����֮�󣬻���ͣ�ڱ���ĩβ
	show_mouse(); 
 }
/*
 *@name:printlist_chinese
 *@msg:��ӡ����ģʽ������
 *@param:{Hnode *}hnode ����ͷ�ڵ�
 *@param:{int *}color ��ɫ����
 *@param:{int}hl ��ǰ��ʾ����������
 *@param:{int}hr ��ǰ��ʾ����������
 *@return:{void}
*/
void printlist_chinese(Hnode *hnode, int color[],int hl,int hr) //Ŀǰ�����hnodeΪp,colorΪpcolor
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
	sethzmode(ziti, hz_s[h]); //��������
	settextjustify(0, 0);
	settextstyle(0, 0, 1);
	
	for (i = 0; i < hl&&hnode!=NULL ;i++)
		hnode = hnode->next;
	for (i = 0; (i < 26) && hnode != NULL; i++) //������ʾ26��
		//for (i = 0; (i < 26) && hnode != NULL&&hnode->head!=NULL; i++) //������ʾ26��
	{
		sprintf(hang, "%d", i + hl+1); //����к�
		setcolor(10);
	
		moveto(16, 32 + 16 + i * 16);
		outtext(hang);
		moveto(16+32, 32 + 16 + i * 16);
		printline_chinese(hnode, ziti, color,hr);
		hnode = hnode->next;
	}
	show_mouse();
}
/*
 *@name:draw_com
 *@msg:�����Ľ�������ʾ��
 *@param:{void}
 *@return:{void}
*/
void draw_com(void)
{
	
	hide_mouse();
	
	setbkcolor(0); //��������Ϊ��ɫ��Ϊ�˳����֣�֮������0��Ȼ�Ǳ�����ɫ����֮���� 
	cleardevice(); //���� 
	drawmain_c();

	barxy(96, 48*3, 640-96*2, 48*4, 15);   //��׿� 
	
	line(96, 48*3+32+10, 96+32*4+10,48*3+32+10 );   //�ָ���
	 //����߿��50��ʼ��{��}�ġ�������
	setfillstyle(1, 7);
	bar(320 - 32 - 5-10, 240 + 80-40, 320 - 32 - 5+10+37 * 2, 240 + 80-40+ 32 + 10);
	 //ȫ�õ�xy x1y1x2y2
	show_mouse();
}
/*
 *@name:ziti_set
 *@msg:����������д���ļ�
 *@param:{int}i�������ñ�־
 *@return:{void}
*/
void ziti_set(int i) //xie
{
	FILE * file;
	char t;
	t = i + '0';
	file = fopen("c:\\ziti", "w");
	fputc(t, file);
	fclose(file);
}
/*
 *@name:ziti_set2
 *@msg:���ļ��ж�ȡ��������
 *@param:{void}
 *@return:{int}t �����������ñ�־
*/
int ziti_set2(void) //duqu
{
	int t;
	FILE * file;
	file = fopen("c:\\ziti", "r");
	t = fgetc(file) - '0';
	fclose(file);
	return t;
}
/*
 *@name:probar
 *@msg:������ģʽ�½�����
 *@param:{int}hl ��ǰ��ʾ����
 *@param:{int}shl ��ǰ��ʾ������
 *@param:{int}hr ��ǰ��ʾ����
 *@param:{int}shr ��ǰ��ʾ������
 *@return:{void}
*/
void probar(int hl,int shl, int hr,int shr) //������������
{
	int r; //������ //�н������Ӻ�����Ϊ0��ʼ����������Ϊ640���� �ܼ�Ϊ640 ��ͷ��ռʮ����������Ϊ630
	if (hr == 1)
		r=10;
	else
	r = (int)(((float)hr / (float)shr) * (610-10)) + 10; //�н����������������
	int l; //������ �н�������30��ʼ����������Ϊ480�������ܼ�Ϊ450����ͷ��ռʮ����������Ϊ430
	
	l = (int)(((float)hl / (float)shl) * (430-20-20-23))  + 40;

	 //�����������������ͷ
	setfillstyle(1, DARKGRAY);
	bar(0, 480 - 20, 640, 480);
	setfillstyle(1, BLACK);
	bar(r, 480 - 20, r + 10, 480);

	setcolor(0); //�������εļ�ͷ
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
/*
 *@name:menu_cl
 *@msg:����ģʽ������ҳ
 *@param:{Hnode *}hnode_c �б�ͷ
 *@param:{int}hr ��ҳǰ��������
 *@return:{int}hr ��ҳ����������
*/
int menu_cl(Hnode *hnode_c,int hr) //����ֵΪhr, //����ֵΪp2
{
	 //Hnode *p2 = hnode_c;
	Node *node;
	int i=0;
	int flag_r = 0;

	if (hr == 1); //��Ч 
	else
	{
		while (hnode_c != NULL)
		{
			node = hnode_c->head->next;

			for (i = 1; i < hr - 3 && node != NULL; i++)
			{
				node = node->next;
			} //��������ǰ��ʾ��һ�е�ǰ���У����ж���һ���Ƿ�Ϊ����

			while (node != NULL)
			{
				if (node->chr >= 0x80 && (hr - 3) % 3 == 1) //��һ��������
				{
					flag_r++;
				}
				node = node->next;
			}

			hnode_c = hnode_c->next;
		}
		if (flag_r != 0)
		{
			hr -= 3;
			flag_r = 0;
		}
		else
		{
			hr--; //��ǰ��һ����ʾ��ʵ��������1
		}

	}
	return hr;
}
/*
 *@name:menu_cr
 *@msg:����ģʽ�����ҷ�ҳ
 *@param:{Hnode *}hnode_c ����ͷ
 *@param:{int}hr ��ҳǰ��������
 *@return:{int}hr ��ҳ����������
*/
int menu_cr(Hnode *hnode_c, int hr)
{
	
	int flag_r=0;
	int flag_r1 = 0;
	int flag_r2 = 0;
	int i=0;
	Node * node;
	Hnode *p2=hnode_c;

		while (hnode_c != NULL)
		{
			flag_r1++;
			node = hnode_c->head->next;
			for (i = 1; i < hr&&node != NULL; i++)
			{
				node = node->next;
			} //��������ǰ��ʾ��һ�У����ж��Ƿ�Ϊ����
			if (node == NULL)
			{
				flag_r2++;
			}
			while (node != NULL)
			{
				if (node->chr >= 0x80) //��һ��������
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
				hr++; //��ǰ��һ����ʾ��ʵ��������1
			}
		}


		flag_r = 0;
		flag_r1 = 0;
		flag_r2 = 0;
		hnode_c=p2;
		return hr;
}
/*
 *@name:draw_oc
 *@msg:����ģʽ�»���ʾ��
 *@param:{void}
 *@return:{void}
*/
void draw_oc()
{
	hide_mouse();
	setbkcolor(0); //��������Ϊ��ɫ��Ϊ�˳����֣�֮������0��Ȼ�Ǳ�����ɫ����֮����
	barxy(96+96*2, 48 * 3, 640 - 96 * 5, 48 * 2, 15);
	setcolor(0);
	line(96+96*2, 48 * 3 + 32 + 10, 96 + 32 * 2 + 10+96*2, 48 * 3 + 32 + 10);   //�ָ���
	setfillstyle(1, 7);
	show_mouse();
}
/*
 *@name:draw_help
 *@msg:����������
 *@param:{void}
 *@return:{void}
*/
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
	static FILE* YOU16; //

	setcolor(0);
	settextjustify(0, 0);
	settextstyle(0, 0, 1);

    //	YOU16FLAG = 1;
	sethzmode(YOU16, hz_s[h]); //��������
	settextjustify(0, 0);
	settextstyle(0, 0, 1);
	hide_mouse();
	unsigned int hzg_1[2] = { 0x5e2e,0x52a9 }; //"����"
	unsigned  int  hzg1[7] = { 0x5de6,0x53f3,0x002f,0x4e0a,0x4e0b,0x7ffb,0x9875 }; //����/���·�ҳ
	unsigned  int  hzg2[8] = { 0x0031,0x002e,0x70b9,0x51fb,0x7bad,0x5934,0x7b26,0x53f7 }; //�����ͷ����
	unsigned  int  hzg3[7] = { 0x0032,0x002e,0x70b9,0x51fb,0x8fdb,0x5ea6,0x6761 }; //���������
	unsigned  int  hzg4[10] = { 0x0033,0x002e,0x6309,0x4e0b,0x4e0a,0x4e0b,0x5de6,0x53f3,0x6309,0x952e }; //�����������Ұ���
	unsigned  int  hzg5[7] = { 0x547d,0x4ee4,0x6a21,0x5f0f,0x6307,0x4ee4,0x8868 }; //����ģʽָ���
	unsigned  int  hzg6[9] = { 0x8f93,0x5165,0x547d,0x4ee4,0x540e,0x6309,0x4e0b,0x56de,0x8f66 }; //����������»س�
	unsigned  int  hzg7[2] = { 0x4f8b,0x5982 }; //����
	unsigned  int  hzg8[18] = { 0x006f,0x0074,0x006c,0x0035,0x5f53,0x524d,0x663e,0x793a,0x7b2c,0x4e00,0x884c,0x8df3,0x8f6c,0x5230,0x603b,0x7b2c,0x4e94,0x884c }; //��ǰ��ʾ��һ����ת���ܵ�����
	unsigned  int  hzg9[18] = { 0x006f,0x0074,0x0072,0x0035,0x5f53,0x524d,0x663e,0x793a,0x7b2c,0x4e00,0x5217,0x8df3,0x8f6c,0x5230,0x603b,0x7b2c,0x4e94,0x5217 }; //��ǰ��ʾ��һ����ת���ܵ�����
	unsigned  int  hzg10[9] = { 0x006f,0x0064,0x006c,0x0035,0x5220,0x9664,0x7b2c,0x4e94,0x884c }; //ɾ��������
	unsigned  int  hzg11[2] = { 0x006f,0x0061 };//oa
	unsigned int hzg11_1[13]={0x0062,0x006c,0x0035,0x5728,0x7b2c,0x4e94,0x884c,0x4e0b,0x65b9,0x63d2,0x5165,0x7a7a,0x884c }; //�ڵ������·��������
	unsigned  int  hzg12[20] = { 0x006f,0x0061,0x0063,0x006c,0x0035,0x5728,0x7b2c,0x4e94,0x884c,0x4e0b,0x65b9,0x63d2,0x5165,0x526a,0x8d34,0x677f,0x4e2d,0x7684,0x4e00,0x884c }; //�ڵ������·�����������е�һ����
	unsigned  int  hzg13[15] = { 0x006f,0x0063,0x006c,0x0035, 0x5c06,0x7b2c,0x4e94,0x884c,0x590d,0x5236,0x5230,0x526a,0x8d34,0x677f,0x4e2d }; //�������и��Ƶ���������
	unsigned  int  hzg130[15] = { 0x006f,0x0078,0x006c,0x0035, 0x5c06,0x7b2c,0x4e94,0x884c,0x526a,0x5207,0x5230,0x526a,0x8d34,0x677f,0x4e2d }; //�������м��е���������
	unsigned  int  hzg14[4] = { 0x82f1,0x6587,0x542b,0x4e49 }; //Ӣ�ĺ���
	unsigned  int  hzg15[6] = { 0x0074,0x003a,0x0074,0x006f,0x8df3,0x8f6c }; //t:to��ת
	unsigned  int  hzg16[7] = { 0x006c,0x003a,0x006c,0x0069,0x006e,0x0065,0x884c }; //l
	unsigned  int  hzg17[6] = { 0x0072,0x003a,0x0072,0x006f,0x0077,0x5217 }; //r
	unsigned  int  hzg18[10] = { 0x0064,0x003a,0x0064,0x0065,0x006c,0x0065,0x0074,0x0065,0x5220,0x9664 }; //d
	unsigned  int  hzg19[7] = { 0x0061,0x003a,0x0061,0x0064,0x0064,0x6dfb,0x52a0 }; //a
	unsigned  int  hzg20[9] = { 0x0020,0x003a,0x0020,0x006c,0x0061,0x006e,0x0020,0x7a7a,0x767d }; //b //���ں��ֿⲻȫ �� ����b��k �����ϣ�
	char blank_1[] = { 'b','\0' };
	char blank_2[] = { 'k','\0' };
	unsigned  int  hzg21[8] = { 0x0063,0x003a,0x0063,0x006f,0x0070,0x0079,0x590d,0x5236 }; //c
	unsigned int hzg0[2] = { 0x786e,0x5b9a };
	hide_mouse();
	setbkcolor(0);
	cleardevice();
	barxy(0, 0, 640, 480, 15); //��Ļ���
	line(0, 32 + 10, 32 * 4 + 10, 32 + 10); //�ָ���
	setfillstyle(1, 7);
	bar(320 - 32 - 5 - 10, 480 - 50, 320 - 32 - 5 + 10 + 37 * 2, 480 - 50 + 32 + 10);
	 //ȫ�õ�xy x1y1x2y2
	put_s_hz(0 + 10, 2, hzg_1, 2, YOU16);
	put_s_hz(320 - 32 - 5 - 10 + 30, 480 - 50 + 16, hzg0, 2, YOU16); //ȷ��
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
	put_s_hz(10 + 70, 32 + 12 + 28 * 7-28, hzg11, 2, YOU16);
	put_s_hz(10 + 70+16+32, 32 + 12 + 28 * 7 - 28, hzg11_1, 13, YOU16);
	put_s_hz(10 + 70, 32 + 12 + 28 * 8-28, hzg12, 20, YOU16);
	put_s_hz(10 + 70, 32 + 12 + 28 * 9-28, hzg13, 15, YOU16);
	put_s_hz(10 + 70, 32 + 12 + 28 * 9 - 28+28, hzg130, 15, YOU16);
	put_s_hz(10, 32 + 12 + 28 * 10, hzg14, 4, YOU16);
	put_s_hz(10 + 170, 32 + 12 + 28 * 10, hzg15, 6, YOU16);
	put_s_hz(10 + 170 + 240, 32 + 12 + 28 * 10, hzg16, 7, YOU16);
	put_s_hz(10 + 170, 32 + 12 + 28 * 11, hzg17, 6, YOU16);
	put_s_hz(10 + 170 + 240, 32 + 12 + 28 * 11, hzg18, 10, YOU16);
	put_s_hz(10 + 170, 32 + 12 + 28 * 12, hzg19, 7, YOU16);
	put_s_hz(10 + 170 + 240, 32 + 12 + 28 * 12, hzg20, 9, YOU16); //blank
	outtextxy(10 + 170 + 240, 32 + 12 + 28 * 12+12, blank_1);
	outtextxy(10 + 170 + 240+32+2, 32 + 12 + 28 * 12 + 12, blank_1);
	outtextxy(10 + 170 + 240 + 32 + 2+64+7, 32 + 12 + 28 * 12 + 12, blank_2);
	outtextxy(10 + 70+16+20, 32 + 12 + 28 *7  - 28+12, blank_1);
	put_s_hz(10 + 170, 32 + 12 + 28 * 13, hzg21, 8, YOU16);


	show_mouse();
}
/*
 *@name:add_cl
 *@msg:����ģʽ�²�����а���һ��
 *@param:{Hnode *}hnode ������֮ǰ��������ͷ
 *@param:{Hnode *}hnode_c ���а���һ������ͷ
 *@param:{} //�������� ��Ҫ����
 *@return:{void}
*/
void add_cl(Hnode *hnode, Hnode *hnode_c) //��hnode�к����hnode_c(��Ҫ���ƣ���
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
		hnode_c1->next = hnode->next;
		hnode->next = hnode_c1;


}
/*
 *@name:copy_l
 *@msg:����ģʽ�½�������һ�и��Ƶ����а���
 *@param:{Hnode *}hnode_c �����е�����ͷ
 *@param:{Hnode *}hnode_cc ���а������ͷ
 *@return:{void}
*/
void copy_l(Hnode *hnode_c, Hnode *hnode_cc)
{
	Node *node;
	Node *node_ccp;
	node = hnode_c->head;

	hnode_cc->next = NULL;

	if (node != NULL)
	{
		Node * node_cc = (Node *)malloc(sizeof(Node));
		node_cc->chr = node->chr;
		node_cc->type = node->type;
		hnode_cc->head = node_cc;
		hnode_cc->head->next = NULL;
		node = node->next;
	}
	node_ccp = hnode_cc->head;
	while (node != NULL) //��ѡ���и��Ƶ��½�����������
	{
	   Node *  node_cc = (Node*)malloc(sizeof(Node));
		node_cc->chr = node->chr;
		node_cc->type = node->type;
		node_ccp->next = node_cc;
		node_cc->next = NULL;
		node_ccp = node_cc;
		node = node->next;
	}
}

/*
 *@name:del_l
 *@msg:��������ģʽ��ɾ��һ��
 *@param:{Hnode *}hnode Ҫɾ���е�����ͷ�ڵ�
 *@return:{Hnode *}ɾ�����������ͷ�ڵ�
*/
Hnode * del_l(Hnode *hnode) //��hnode��ɾfree�� 
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

/*
 *@name:draw_help2
 *@msg:����������
 *@param:{void}
 *@return:{void}
*/
void draw_help2()
{
	char* hz_s1[] = {
			"YOU16",
			"FS16",
			"HP16",
			"HT16",
			"MBXS16"
	};
	int h;
	h = ziti_set2();
	static FILE* YOU16; //
	setcolor(0);
	settextjustify(0, 0);
	settextstyle(0, 0, 1);
	sethzmode(YOU16, hz_s1[h]); //��������
	settextjustify(0, 0);
	settextstyle(0, 0, 1);
	hide_mouse();
	unsigned int hzg_1[2] = { 0x5e2e,0x52a9 }; //"����"
	unsigned  int  hzg5[5] = { 0x5f00,0x53d1,0x4eba,0x5458,0xff1a}; //������Ա
	unsigned  int  hzg8[9] = { 0x81ea,0x52a8,0x5316,0x7c7b,0x0032,0x0030,0x0030,0x0037,0x73ed }; //�Զ�����2007��
	unsigned  int  hzg9[3] = { 0x5468,0x500d,0x8fdb }; //�ܱ���
	unsigned  int  hzg10[3] = { 0x7530,0x660e,0x5b66 }; //����ѧ
	unsigned  int  hzg11[14] = { 0x5982,0x679c,0x60a8,0x6709,0x4efb,0x4f55,0x95ee,0x9898,0xff0c,0x8bf7,0x8054,0x7cfb,0x6211,0x4eec }; //��������κ����⣬����ϵ����
	unsigned  int  hzg12[6] = { 0x6211,0x4eec,0x7684,0x90ae,0x7bb1,0xff1a }; //���ǵ����䣺
	unsigned  int  hzg13[17] = {0x0031,0x0030,0x0033,0x0030,0x0030,0x0031,0x0034,0x0033,0x0036,0x0030,0x0040,0x0071,0x0071,0x002e,0x0063,0x006f,0x006d }; //1030014360@qq.com
	unsigned int hzg0[2] = { 0x786e,0x5b9a };
	hide_mouse();
	setbkcolor(0);
	cleardevice();
	barxy(0, 0, 640, 480, 15); //��Ļ���
	line(0, 32 + 10, 32 * 4 + 10, 32 + 10); //�ָ���
	setfillstyle(1, 7);
	bar(320 - 32 - 5 - 10, 480 - 50, 320 - 32 - 5 + 10 + 37 * 2, 480 - 50 + 32 + 10);
	 //ȫ�õ�xy x1y1x2y2
	put_s_hz(0 + 10, 2+10, hzg_1, 2, YOU16);
	put_s_hz(320 - 32 - 5 - 10 + 30, 480 - 50 + 16, hzg0, 2, YOU16); //ȷ��
	put_s_hz(10, 32 + 12 + 28 * 3 - 28, hzg5, 5, YOU16);
	put_s_hz(10 + 70, 32 + 12 + 28 * 4 - 28, hzg8, 9, YOU16);
	put_s_hz(10 + 70, 32 + 12 + 28 * 5 - 28, hzg9, 3, YOU16);
	put_s_hz(10 + 70, 32 + 12 + 28 * 6 - 28, hzg10, 3, YOU16);
	put_s_hz(10 + 70, 32 + 12 + 28 * 7 - 28, hzg11, 14, YOU16);
	put_s_hz(10 + 70, 32 + 12 + 28 * 8 - 28, hzg12, 6, YOU16);
	put_s_hz(10 + 70, 32 + 12 + 28 * 9 - 28, hzg13, 17, YOU16);
	show_mouse();
}
/*
 *@name:free_copy
 *@msg:��ռ��а�
 *@param:{Hnode *}hnode ���а�ͷ
 *@return:{void}
*/
void  free_copy(Hnode * hnode)
{
	Node *node;
	node= hnode->head;
	Node *node_p;
	while (node != NULL)
	{
		node_p = node;
		node = node->next;
		free(node_p);
	}
	free(hnode);
}
