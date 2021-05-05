#include"chinese.h"
 //返回值：1->成功，0：失败

/*
 *@name:chinese
 *@msg:汉化界面的总函数
 *@param:{Hnode *} hnode 链表头
 *@param:{Cursornode *}cursornode 光标位置
 *@param:{int}h字体变量 //以后删了
 *@param:{int *}颜色控制数组
 *@param:{int}textflags 表示当前有无链表显示
 *@param:{int *}记录在汉化模式下按下的菜单
 *@return:{Hnode *}改变后的链表头
*/
Hnode * chinese (Hnode * hnode,Cursornode * cursornode,int *menu_c,int *pcolor,int textflags)
{
	
	Hnode *hnode_cc = NULL; //用于剪切板的链表指针
	//Node *node_ccp = NULL;
	//Node *node_cc = NULL;

	Hnode *hnode_cb=NULL; //记录前一个节点

	Hnode *hnode_c=hnode;
	Hnode *p2 = hnode;

	int shr=0; //记录总列数
	int shl=0; //记录总行数

	char order[80]; //命令储存
	int o_n = 0;

	int flag_q2 = 0;

	int op; //记录键值
	short op1;

	int hl=0; //记录行数 当前显示的为第几行
	int hr = 1; //记录列数 当前显示的为第几列

	int i; //每行显示
	int flag_c=0; //记录在哪个菜单下
	int flag3_c = 0; //记录第三级
	int flag_q = 0; //编译时判断是否需要点击确定

	int flag_o = 0; //用于命令模式的数字判断
	int flag_o2 = 0; //用于命令输入是否正确的判断
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
	sethzmode(YOU16,  hz_s[h]); //设置字体

	settextjustify(0, 0);
	settextstyle(0, 0, 1);

	p2 =trans(hnode, cursornode, &shl, &shr); //转换链表，手动对齐
	if (hr < 0)
	{
		hr = 1;
		if (textflags != 0)
			printlist_chinese(p2, pcolor, hl, hr ); //目前传入的hnode为p,color为pcolor
		else
			drawmain_c();
		probar(hl, shl, hr, shr);
	}
	else
	{
		if (textflags != 0)
			printlist_chinese(p2, pcolor, hl, hr ); //目前传入的hnode为p,color为pcolor
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
			/*跳离菜单*/
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
					printlist_chinese(p2, pcolor, hl, hr); //目前传入的hnode为p,color为pcolor
				else
					drawmain_c();
				probar(hl, shl, hr, shr);
			}

			if (flag_c == 0 && pd(0, 0, 45, 16)) //执行编译功能
			{
				unsigned int by_1[4] = { 0x8fd0,0x884c,0x9519,0x8bef }; //"运行错误"
				unsigned int by_2[2] = { 0x786e,0x5b9a }; //"确定
				unsigned int by_3[6] = { 0x7684,0x6570,0x91cf,0x4e0d,0x5339,0x914d }; //的数量不匹配
				unsigned int by_4[6] = { 0x7684,0x6570,0x91cf,0x4e0d,0x76f8,0x7b49 }; //的数量不相等
				unsigned int by_5[6] = { 0x51fd,0x6570,0x672a,0x88ab,0x627e,0x5230 }; //函数未被找到
				unsigned int by_6[5] = { 0x7684,0x6570,0x91cf,0x592a,0x5c11 }; //的数量过少
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
						flag_q = 1; //确定待点击
						while (1)
						{
							getmouse();
							if (M_sc < 0 && flag_q == 1 && pd(320 - 32 - 5 - 10, 240 + 80 - 40, 10 * 2 + 37 * 2, 32 + 10)) //点击确定键
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
							flag_q = 1; //确定待点击
							while (1)
							{
								getmouse();
								if (M_sc < 0 && flag_q == 1 && pd(320 - 32 - 5 - 10, 240 + 80 - 40, 10 * 2 + 37 * 2, 32 + 10)) //点击确定键
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
					flag_q = 1; //确定待点击
					while (1)
					{
						getmouse();
						if (M_sc < 0 && flag_q == 1 && pd(320 - 32 - 5 - 10, 240 + 80 - 40, 10 * 2 + 37 * 2, 32 + 10)) //点击确定键
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
					flag_q = 1; //确定待点击
					while (1)
					{
						getmouse();
						if (M_sc < 0 && flag_q == 1 && pd(320 - 32 - 5 - 10, 240 + 80 - 40, 10 * 2 + 37 * 2, 32 + 10)) //点击确定键
						{
							flag_q = 0;
					
							break;
						}
					}
				}

				unsigned int by_11[] = { 0x63d0,0x793a }; //提示
				unsigned int by_22[] = { 0x6682,0x672a,0x627e,0x5230,0x9519,0x8bef }; //暂未找到错误
				draw_com();
				put_s_hz(96 + 20, 48 * 3 + 15, by_11, 2, YOU16);
				put_s_hz(320 - 32 - 5 - 10 + 30, 240 + 80 - 40 + 16, by_2, 2, YOU16);
				put_s_hz(96 + 20 + 20 + 35, 48 * 3 + 15 + 32 + 32, by_22, 6, YOU16);
				flag_q = 1; //确定待点击
				while (1)
				{
					getmouse();
					if (M_sc < 0 && flag_q == 1 && pd(320 - 32 - 5 - 10, 240 + 80 - 40, 10 * 2 + 37 * 2, 32 + 10)) //点击确定键
					{
						flag_q = 0;

						break;
					}
				}

				if (textflags != 0)
				{
					printlist_chinese(p2, pcolor, hl, hr); //目前传入的hnode为p,color为pcolor

				}
				else
					drawmain_c();
				probar(hl, shl, hr, shr);
				flag_c = 0;
				flag3_c = 0;
			}
			if (flag_q == 0 && pd(0, 480 - 20, 10, 480)) //点击横进度条的左箭头
			{
				if(hr==1)
					;
				else
				{
					if (textflags != 0)
					{
						hr = menu_cl(p2, hr); //返回值为hr, //传入值为p2
						printlist_chinese(p2, pcolor, hl, hr);
					}
					probar(hl, shl, hr, shr);
				}
			}
			if (flag_q == 0 && pd(640 - 10, 480 - 20, 640, 480)) //点击横进度条的右箭头
			{
				if (hr == shr)
					;
				else
				{
					if (textflags != 0)
					{
						hr = menu_cr(p2, hr); //返回值为hr, //传入值为p2
						printlist_chinese(p2, pcolor, hl, hr);
					}
					probar(hl, shl, hr, shr);
				}
			}
			else	if (flag_q == 0 && pd(0 + 10, 480 - 20, 640 - 10, 480)) //bar(0, 480 - 20, 640, 480);点击的是横进度条，hr相关
			{
				if (textflags != 0)
				{
					hr = (int)((float)(mouse_x - 10) / 600.0*shr); //近似算法
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

					printlist_chinese(p2, pcolor, hl, hr); //目前传入的hnode为p,color为pcolor
				}
				probar(hl, shl, hr, shr);
			}
			else if (flag_q == 0 && pd(640 - 14, 26, 640, 26 + 10)) //点击上箭头
			{
				if (hl == 0); //无效 
				else
				{
					
					if (textflags != 0)
					{
						hl--; //当前第一行显示的实际行数减1
						hnode_c = p2; //hnode重新指向第一行 
						printlist_chinese(p2, pcolor, hl, hr);
					}
					else
						drawmain_c();
					probar(hl, shl, hr, shr);
				}
			}
			else if (flag_q == 0 && pd(640 - 14, 480 - 30, 640, 480 - 20)) //点击下箭头
			{
				 //hnode = p; //hnode重新指向第一行
				if (textflags != 0)
				{
					hnode_c = p2;
					for (i = 1; i < hl; i++)
						hnode_c = hnode_c->next; //hnode指向现在显示的第一行 
					if (hnode_c->next == 0); //当前显示的第一行为实际的最后一行，不能再DOWN
					else
					{

						if (textflags != 0)
						{
							hl++; //当前第一行显示的实际行数加1
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
					hl = (int)((float)(mouse_y - 40) / 367.0*shl); //近似算法
					if (hl > shl)
					{
						hl = shl;
					}
					else if (hl < 1)
					{
						hl = 1;
					}

					printlist_chinese(p2, pcolor, hl, hr); //目前传入的hnode为p,color为pcolor
				}
				else
					drawmain_c();
				probar(hl, shl, hr, shr);
			}

			if (flag_q == 0 && pd(6 * 8 + 4, 0, 88, 16)) //鼠标在File处按下
			{
				flag_c = 1;
			   //	hnode = p; //重新指向第一行
				drawmenu_c(F1, p2, hl, hr, pcolor, textflags);
				probar(hl, shl, hr, shr);

			}
			else if (flag_q == 0 && pd(24 * 8 + 4, 0, 80, 16)) //鼠标在Edit处按下
			{
				flag_c = 2;
			    //	hnode = p; //重新指向第一行
				drawmenu_c(F2, p2, hl, hr, pcolor, textflags);
				probar(hl, shl, hr, shr);

			}

			else if (flag_q == 0 && pd(42 * 8 + 4, 0, 8 * 13, 16)) //鼠标在settings处按下
			{
				flag_c = 3;
			   //	hnode = p; //重新指向第一行
				drawmenu_c(F3, p2, hl, hr, pcolor, textflags);
				probar(hl, shl, hr, shr);


			}
			else if (flag_c == 0 && pd(60 * 8 + 4, 0, 8 * 14, 16)) //鼠标在pattern处按下
			{
				flag_c = 4;
				drawmenu_c(F4, p2, hl, hr, pcolor, textflags);
				probar(hl, shl, hr, shr);
			}

			 //File菜单打开之后的几个子菜单
			else if (flag_q == 0 && pd(6 * 8 + 4, 80 - 6 * 8, 88, 16) && flag_c == 1) //新建
			{
				closegraph();
				initmouse(0);
				*menu_c = 1;
				if (hnode_cc != NULL)
					free_copy( hnode_cc);
				hnode_cc =NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(6 * 8 + 4, 80 - 4 * 8, 88, 16) && flag_c == 1) //打开
			{
				
				closegraph();
				initmouse(0);
				*menu_c = 2;
				if (hnode_cc != NULL)
					free_copy( hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(6 * 8 + 4, 80 - 2 * 8, 88, 16) && flag_c == 1) //保存	
			{
				closegraph();
				initmouse(0);
				*menu_c = 3;
				if (hnode_cc != NULL)
					free_copy( hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(6 * 8 + 4, 80 - 0 * 8, 88, 16) && flag_c == 1) //另存为
			{
				closegraph();
				initmouse(0);
				*menu_c = 4;
				if (hnode_cc != NULL)
					free_copy( hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(6 * 8 + 4, 80 - (-2) * 8, 88, 16) && flag_c == 1) //改变路径
			{
				closegraph();
				initmouse(0);
				*menu_c = 5;
				if (hnode_cc != NULL)
					free_copy(hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(6 * 8 + 4, 80 - (-4) * 8, 88, 16) && flag_c == 1) //关闭
			{
				closegraph();
				initmouse(0);
				*menu_c = 6;
				if (hnode_cc != NULL)
					free_copy(hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(6 * 8 + 4, 80 - (-6) * 8, 88, 16) && flag_c == 1) //退出
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
			/*Edit菜单打开之后的几个子菜单*/
			else if (flag_q == 0 && pd(24 * 8 + 4, 80 - 6 * 8, 80, 16) && flag_c == 2) // 复制
			{
				closegraph();
				initmouse(0);
				*menu_c = 11;
				if (hnode_cc != NULL)
					free_copy( hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(24 * 8 + 4, 80 - 4 * 8, 80, 16) && flag_c == 2) //剪切	
			{
				closegraph();
				initmouse(0);
				*menu_c = 12;
				if (hnode_cc != NULL)
					free_copy( hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(24 * 8 + 4, 80 - 2 * 8, 80, 16) && flag_c == 2) //粘贴
			{
				closegraph();
				initmouse(0);
				*menu_c = 13;
				if (hnode_cc != NULL)
					free_copy( hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(24 * 8 + 4, 80 - 0 * 8, 80, 16) && flag_c == 2) //查找
			{
				closegraph();
				initmouse(0);
				*menu_c = 14;
				if (hnode_cc != NULL)
					free_copy(hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			else if (flag_q == 0 && pd(24 * 8 + 4, 80 -(-2) * 8, 80, 16) && flag_c == 2) //替换
			{
				closegraph();
				initmouse(0);
				*menu_c = 15;
				if (hnode_cc != NULL)
					free_copy(hnode_cc);
				hnode_cc = NULL;
				return p2;
			}
			/*Settings菜单打开之后的几个子菜单*/
			else if (flag_q == 0 && pd(42 * 8 + 4, 80 - 6 * 8, 80, 16) && flag_c == 3)
			{

				flag3_c = 1;
				drawmenu_c(1, p2, hl, hr, pcolor, textflags);
				probar(hl, shl, hr, shr);
			} // 字体
			else if (flag_q == 0 && pd(42 * 8 + 4, 80 - 4 * 8, 80, 16) && flag_c == 3)
			{

				flag3_c = 2;
				drawmenu_c(2, p2, hl, hr, pcolor, textflags);
				probar(hl, shl, hr, shr);
			} //颜色
			else if (flag_q == 0 && pd(42 * 8 + 4, 80 - 2 * 8, 80, 16) && flag_c == 3) //帮助界面
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
					printlist_chinese(p2, pcolor, hl, hr); //目前传入的hnode为p,color为pcolor
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


			} // 英文编辑
			else if (flag_q == 0 && pd((42 + 18) * 8 + 4, 80 - 4 * 8, 80, 16) && flag_c == 4)
			{
				flag_c = 0;
				if (textflags != 0)
				{
					printlist_chinese(p2, pcolor, hl, hr); //目前传入的hnode为p,color为pcolor

				}
				else
					drawmain_c();
				probar(hl, shl, hr, shr);
				continue;


			} // 中文命令
			if (flag_q == 0 && flag3_c == 1)
			{

				for (i = 0; i < 5; i++)
				{
					if (pd(400 - 6 * 8 + (11 * 8), 32 + 16 * (i + 1), 16 * 6, 16))
					{
						flag_c = 0;
						flag3_c = 0;
						h = i; //改变传入chinese（）的字符串（h为数组下标）
						ziti_set(i);
						sethzmode(YOU16, hz_s[h]); //设置字体
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

						High_li(p2, cursornode, pcolor[0], 0); //仅进行颜色的设置
						High_li(p2, cursornode, pcolor[1], 1);
						High_li(p2, cursornode, pcolor[2], 2);
						High_li(p2, cursornode, pcolor[3], 3);
						High_li(p2, cursornode, pcolor[4], 4);
						High_li(p2, cursornode, pcolor[5], 5);

						if (textflags != 0)
							printlist_chinese(p2, pcolor, hl, hr); //目前传入的hnode为p,color为pcolor
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
			  //	hnode = p; //重新指向第一行
				drawmenu_c(op, hnode, hl, hr, pcolor, textflags);
				probar(hl, shl, hr, shr);
				if (op == F1) flag_c = 1; //记录菜单位置
				if (op == F2) flag_c = 2;
				if (op == F3) flag_c = 3;
				if (op == F4) flag_c = 4;
			}
			else if (op == UP)
			{
				if (textflags != 0)
				{
					if (hl == 0); //无效 
					else
					{

						hl--; //当前第一行显示的实际行数减1
						hnode_c = p2; //hnode重新指向第一行 
						if (textflags != 0)
							printlist_chinese(p2, pcolor, hl, hr);
						else
							drawmain_c();
						probar(hl, shl, hr, shr);
					}
				}
			}
			else if (op == DOWN) //无效的条件是当前为最后一行 
			{
				if (textflags != 0)
				{
					hnode_c = p2;
					for (i = 1; i < hl; i++)
						hnode_c = hnode_c->next; //hnode指向现在显示的第一行 
					if (hnode_c->next == 0); //当前显示的第一行为实际的最后一行，不能再DOWN
					else
					{

						hl++; //当前第一行显示的实际行数加1
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
						hr = menu_cl(p2, hr); //返回值为hr, //传入值为p2
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
						hr = menu_cr(p2, hr); //返回值为hr, //传入值为p2
						if (textflags != 0)
							printlist_chinese(p2, pcolor, hl, hr);
						else
							drawmain_c();
						probar(hl, shl, hr, shr);
					}
				}
			}
			else if ((op & 0x00ff) == 'o') //进入指令输入模式 o为order
			{

				flag_o2 = 0; //输入的命令“未正确”
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
				if (order[0] == 't') //跳转指令
				{
					if (order[1] == 'l') //跳转行指令
					{
						for (i = 0; order[2 + i] != '\0'; i++)
						{
							if (order[2 + i] >= '0'&&order[2 + i] <= '9')
							{
								;
							}
							else //只要后边有一个不是数字，就不满足条件
							{
								flag_o = -1;
							}
						}
						if (flag_o == 0)
						{
							o_n = atoi(&order[2]);
							if (o_n >= 1 && o_n <= shl)
							{
								hl = o_n - 1; //hl为0时显示第一行
							}
						}
						flag_o2 = 1;
						flag_o = 0;
					}
					else if (order[1] == 'r') //跳转列指令
					{
						for (i = 0; order[2 + i] != '\0'; i++)
						{
							if (order[2 + i] >= '0'&&order[2 + i] <= '9')
							{
								;
							}
							else //只要后边有一个不是数字，就不满足条件
							{
								flag_o = -1;
							}
						}
						if (flag_o == 0)
						{
							o_n = atoi(&order[2]);

							if (o_n % 3 == 2) //对齐
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
							hr = o_n; //hr为0时显示第一行
							flag_o2 = 1;
							flag_o = 0;
						}
					}
				}
					else if (order[0] == 'd') //进入删除指令模式
					{
						if (order[1] == 'l') //删除行
						{
							for (i = 0; order[2 + i] != '\0'; i++)
							{
								if (order[2 + i] >= '0'&&order[2 + i] <= '9');
								else //只要后边有一个不是数字，就不满足条件
									flag_o = -1;
							}
							if (flag_o == 0)
							{
								o_n = atoi(&order[2]);
								if (o_n >= 1 && o_n <= shl)
								{
									hnode_c = p2; //重新指向第一行
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
					else if (order[0] == 'a') //进入添加（行）指令模式 add
					{

						if (order[1] == 'b') //添加空（行）
						{
							if (order[2] == 'l') //添加行
							{
								for (i = 0; order[3 + i] != '\0'; i++)
								{
									if (order[3 + i] >= '0'&&order[3 + i] <= '9');
									else //只要后边有一个不是数字，就不满足条件
										flag_o = -1;
								}
								if (flag_o == 0)
								{
									o_n = atoi(&order[3]);
									if (o_n >= 1 && o_n <= shl)
									{
										hnode_c = p2; //重新指向第一行
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
						else if (order[1] == 'c') //添加剪贴板中的已经复制了的（行
						{

							if (order[2] == 'l') //添加行
							{
								for (i = 0; order[3 + i] != '\0'; i++)
								{
									if (order[3 + i] >= '0'&&order[3 + i] <= '9');
									else //只要后边有一个不是数字，就不满足条件
										flag_o = -1;
								}
								if (flag_o == 0)
								{
									o_n = atoi(&order[3]);
									if (o_n >= 1 && o_n <= shl)
									{
										hnode_c = p2; //重新指向第一行
										for (i = 1; i < o_n; i++)
										{
											hnode_c = hnode_c->next;
										}
										 //node_c = hnode_cc->head->next;
										if (hnode_cc != NULL)
										{
											add_cl(hnode_c, hnode_cc); //在hnode行后插入hnode_c(需要复制）行

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
					else if (order[0] == 'c' || order[0] == 'x') //进入复制某行模式（复制到剪贴板
					{
						if (order[1] == 'l') //复制某行
						{
							for (i = 0; order[2 + i] != '\0'; i++)
							{
								if (order[2 + i] >= '0'&&order[2 + i] <= '9');
								else //只要后边有一个不是数字，就不满足条件
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
									hnode_c = p2; //重新指向第一行

									for (i = 1; i < o_n; i++)
									{
										hnode_c = hnode_c->next;

									}
									hnode_cc = (Hnode *)malloc(sizeof(Hnode));
									copy_l(hnode_c, hnode_cc);

									if (order[0] == 'x') //剪切需要删除掉原来的
									{
										hnode_c = p2; //重新指向第一行
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
											p2 = del_l(hnode_c); //将hnode行删free掉 关于删除第一行在函数外讨论
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
					unsigned int o_1[2] = { 0x63d0,0x793a }; //提示
					unsigned int o_4[2] = { 0x786e,0x5b9a }; //确定
					put_s_hz(96 + 20, 48 * 3 + 15, o_1, 2, YOU16); //提示
					put_s_hz(320 - 32 - 5 - 10 + 30, 240 + 80 - 40 + 16, o_4, 2, YOU16); //确认
					unsigned int o_2[6] = { 0x547d,0x4ee4,0x8f93,0x5165,0x6b63,0x786e }; //命令输入正确
					unsigned int o_3[6] = { 0x547d,0x4ee4,0x8f93,0x5165,0x9519,0x8bef }; //命令输入错误
					if (flag_o2 == 0) //输入了错误的命令
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

					flag_o2 = 0; //输入命令未成功
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
 *@msg:画图形界面下主界面
 *@param:{void}
 *@return:{void}
*/
 void drawmain_c() //画中文主界面 
 {
 	
	hide_mouse();										
	setbkcolor(0); //背景设置为黑色，为了出黑字，之后设置0居然是背景颜色？谜之操作 
	cleardevice(); //清屏 
	
	barxy(0, 0, 640, 16, 7);   //上菜单灰框 

	setfillstyle(1, DARKGRAY); //进度条
	bar(0, 480 - 20, 640, 480);
	
	 //barxy(0,480-16,640,480,7);   //下菜单
	barxy(0,16,640,480-32,1);   //蓝色主界面  //为什么是减32？减16最下边会被包括进去 

	bar(640 - 14, 26, 640, 480 - 20); //进度条

	setcolor(15); //白框
	
	line(2,16+5,2,480-16-5); //竖白框 
	line(3,16+5,3,480-16-5);
	line(3+4,16+8,3+4,480-16-8);
	line(3+5,16+8,3+5,480-16-8);
	
	 
    line(2, 16+5 , 640, 16+5); //横白框
	line(2, 16+6 , 640, 16+6); 
    line(2+5, 16+8 , 640, 16+8);
    line(2+5, 16+9 , 640, 16+9); //上 
    line(2, 480-(16+5), 640, 480-(16+5));
	line(2, 480-(16+6), 640, 480-(16+6)); 
    line(2+5, 480-(16+8), 640, 480-(16+8));
    line(2+5, 480-(16+9), 640, 480-(16+9)); //下 
    
	static FILE* YOU16; 
	sethzmode(YOU16, "YOU16"); //设置字体
	settextjustify(0, 0);
	settextstyle(0, 0, 1);

    unsigned  int  hzk1[6]  =  {  0x6587  ,0x4ef6  ,0x46  ,0x31  }; //"文件F1"    
    unsigned  int  hzk2[6]  =  {  0x4fee  ,0x6539  ,0x46  ,0x32  }; //"修改F2"    
    unsigned  int  hzk3[6]  =  {  0x8bbe  ,0x7f6e  ,0x46  ,0x33  }; //"设置F3"    
	unsigned  int  hzk4[6]  =  {  0x6a21  ,0x5f0f  ,0x46  ,0x34  }; //"模式F4"
	unsigned  int  hzk5[2]  =  { 0x8fd0,0x884c }; //"运行"
	
	setcolor(0);
	line(5 * 8 + 5, 0, 5 * 8 + 5, 16);

	line(6 * 8 + 4, 2, 6 * 8 + 4, 14);   //画竖线和竖线，搞菜单的格子 
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
	put_s_hz(80 - 2 * 8, 0, hzk1, 4, YOU16);  //显示汉字  
	put_s_hz(240 - 4 * 8, 0, hzk2, 4, YOU16);  
	put_s_hz(400 - 6 * 8, 0, hzk3, 4, YOU16);  
	put_s_hz(560 - 8 * 8, 0, hzk4, 4, YOU16);   
	
	setfillstyle(1, DARKGRAY);
	bar(0, 480 - 20, 640, 480);

	setcolor(0); //画三角形的箭头
	line(0, 480 - 10, 10, 480 - 20);
	line(0, 480 - 10, 10, 480);
	line(10, 480 - 20, 10, 480);

	line(640 - 10, 480 - 20, 640, 480 - 10);
	line(640 - 10, 480, 640, 480 - 10);
	line(640 - 10, 480 - 20, 640 - 10, 480);

	 //画纵进度条，不包括箭头
	setfillstyle(1, DARKGRAY);
	bar(640 - 14, 26, 640, 480 - 20);

	show_mouse();
 }
/*
 *@name:drawmenu_c
 *@msg:画图形界面菜单
 *@param:{int}op 主循环中按下的按键扫描码
 *@param:{Hnode *}hnode 链表头
 *@param:{int}hl 当前所处链表行数
 *@param:{int}hr 当前所处列表列数
 *@param:{int *}pcolor 颜色数组
 *@param:{int}textflags 当前链表有无显示的标志
 *@return:{void}
*/
 void drawmenu_c(int op,Hnode *hnode,int hl,int hr,int *pcolor,int textflags) //画中文菜单
 {
	int i;
	
	
	static FILE* YOU16;
	sethzmode(YOU16, "YOU16"); //设置幼圆16号字体
	settextjustify(0, 0);
	settextstyle(0, 0, 1);

	

 	
	switch(op)
	{
		case 1: //画第三级菜单 字体
			hide_mouse();
			drawmenu_c(F3,hnode,hl,hr,pcolor, textflags);
			barxy((42 + 11) * 8, 16 + 16, 12 * 8, 7 * 16, LIGHTGRAY);

			line((42+11+1) * 8, 24+16, (42 + 11 + 1) * 8, 24+16 + 6 * 16);   //竖线
			line((42 + 11 + 1) * 8, 24 +16+ 6 * 16, (42 + 11 + 1) * 8 + 10 * 8, 24+16 + 6 * 16);   //横线
			line((42 + 11 + 1) * 8 + 10 * 8, 24 +16+ 6 * 16, (42 + 11 + 1) * 8 + 10 * 8, 24+16); //竖线
			line((42 + 11 + 1) * 8 + 10 * 8, 24+16, (42 + 11 + 1) * 8, 24+16);   //上横线

			unsigned int hzk1_1[2] = { 0x89c4,0x8303 }; //"规范"
			unsigned int hzk2_1[2] = { 0x6977,0x4f53 }; //"楷体"
			unsigned int hzk3_1[2] = { 0x5e7c ,0x5706 }; //"幼圆"
			unsigned int hzk4_1[2] = { 0x659c,0x4f53 }; //"斜体"
			unsigned int hzk5_1[2] = { 0x4e66,0x6cd5 }; //"书法"
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

			line((42 + 11 + 1) * 8, 24 + 16+16, (42 + 11 + 1) * 8, 24 + 16 + 16+6 * 16);   //竖线
			line((42 + 11 + 1) * 8, 24 + 16 +16+ 6 * 16, (42 + 11 + 1) * 8 + 10 * 8, 24 +16+ 16 + 6 * 16);   //横线
			line((42 + 11 + 1) * 8 + 10 * 8, 24 + 16 +16+ 6 * 16, (42 + 11 + 1) * 8 + 10 * 8, 24+16 + 16); //竖线
			line((42 + 11 + 1) * 8 + 10 * 8, 24 +16+16, (42 + 11 + 1) * 8, 24+16 + 16);   //上横线

			unsigned int hzk1_2[4] = { 0x53d6 ,0x6d88,0x989c,0x8272 }; //"取消颜色"
			unsigned int hzk2_2[3] = { 0x989c,0x8272 ,0x4e00 }; //"颜色一"
			unsigned int hzk3_2[3] = { 0x989c,0x8272 ,0x4e8c }; //"颜色二"
			unsigned int hzk4_2[3] = { 0x989c,0x8272 , 0x4e09 }; //"颜色三"
			unsigned int hzk5_2[3] = { 0x989c,0x8272 ,0x56db }; //"颜色四"
			put_s_hz(400 - 6 * 8 + (11 * 8), 32 + 16+16, hzk1_2, 4, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 48 + 16+16, hzk2_2, 3, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 64 + 16+16, hzk3_2, 3, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 80 + 16+16, hzk4_2, 3, YOU16);
			put_s_hz(400 - 6 * 8 + (11 * 8), 96 + 16+16, hzk5_2, 3, YOU16);
			show_mouse();
			break;



		case F1: //画File
				hide_mouse();
				if (textflags != 0)
					printlist_chinese(hnode, pcolor, hl, hr);
				else
					drawmain_c();

				//barxy(6 * 8 + 4, 16, 11 * 8, 7 * 16, LIGHTGRAY);
				barxy(6 * 8 + 4, 16, 11 * 8, 7 * 16+2*16, LIGHTGRAY);
				setcolor(0);
				/*
				line(7 * 8, 24, 7 * 8, 24 + 6 * 16);   //竖线
				line(7 * 8, 24 + 6 * 16, 7 * 8 + 10 * 8, 24 +6 * 16);   //横线
				line(7 * 8 + 10 * 8, 24 +  6* 16, 7 * 8 + 10 * 8, 24); //竖线
				line(7 * 8 + 10 * 8, 24, 7 * 8, 24);   //上横线
				*/
				line(7 * 8, 24, 7 * 8, 24 + 8 * 16);   //竖线
				line(7 * 8, 24 + 8 * 16, 7 * 8 + 10 * 8, 24 + 8 * 16);   //横线
				line(7 * 8 + 10 * 8, 24 + 8 * 16, 7 * 8 + 10 * 8, 24); //竖线
				line(7 * 8 + 10 * 8, 24, 7 * 8, 24);   //上横线
				unsigned int hzk1[2] = { 0x65b0 ,0x5efa }; //"新建"
				unsigned int hzk2[2] = { 0x5f00 ,0x542f }; //"开启"
				unsigned int hzk3[2] = { 0x4fdd ,0x5b58 }; //"保存"
				unsigned int hzk4[3] = { 0x53e6 ,0x5b58 ,0x4e3a }; //"另存为"
				unsigned int hzk5[2] = { 0x9000 ,0x51fa }; //"退出"
				unsigned int hzf1[4] = {0x6539,0x53d8,0x8def,0x5f84};//改变路径
				unsigned int hzf2[2] = {0x5173,0x95ed};//关闭
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
		case F2: //画Edit
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
				unsigned int hzk6[2] = { 0x590d ,0x5236 }; //"复制"
				unsigned int hzk7[2] = { 0x526a ,0x5207 }; //"剪切"
				unsigned int hzk8[2] = { 0x7c98 ,0x8d34 }; //"粘贴"
				unsigned int hzk9[2] = { 0x67e5 ,0x627e }; //"查找"
				unsigned int hzk10[2] = { 0x66ff ,0x6362 }; //"替换"
				put_s_hz(240 - 4 * 8, 32, hzk6, 2, YOU16);
				put_s_hz(240 - 4 * 8, 48, hzk7, 2, YOU16);
				put_s_hz(240 - 4 * 8, 64, hzk8, 2, YOU16);
				put_s_hz(240 - 4 * 8, 80, hzk9, 2, YOU16);
				put_s_hz(240 - 4 * 8, 96, hzk10, 2, YOU16);
				show_mouse();
			break;
		case F3: //画Settings
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

				unsigned int hzk11[2] = { 0x5f62,0x4f53 }; //"形体"
				unsigned int hzk12[2] = { 0x989c,0x8272 }; //"颜色"
				unsigned int hzk13[2] = { 0x5e2e,0x52a9 }; //"帮助"

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

			unsigned int hzk14[4] = { 0x82f1,0x6587,0x7f16,0x8f91 }; //"英文编辑"
			unsigned int hzk15[2] = { 0x6c49,0x5316 }; //"中文命令"

			put_s_hz(400 - 6 * 8+18*8, 32, hzk14, 4, YOU16);
			put_s_hz(400 - 6 * 8+18*8, 48, hzk15, 2, YOU16);

			show_mouse();
			break;
	 }
 }
/*
 *@name:printline_chinese
 *@msg:打印汉化模式下一行链表
 *@param:{Hnode *}hnode 链表头
 *@param:{FILE *}YOU16 汉字文件指针
 *@param:{int *}color 颜色数组
 *@param:{int}hr 当前显示的列数
 *@return:{void}
*/
void printline_chinese(Hnode* hnode,FILE * YOU16,int color[],int hr) //在当前位置输出hnode指向的这一行
{
	hide_mouse();
	settextjustify(0,0);
	settextstyle(0,0,1);
	unsigned short uni;

	char alp[2]={'\0','\0'}; //输出英文（非汉字
	Node * tnode;
	int x,y; //汉字输出需要坐标
	int i; //列数遍历
	tnode=hnode->head; //第一个Node
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
				put_a_hz(x, y-12, uni, YOU16, color[tnode->type], -1); //手动调整最美观位置
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
		tnode=tnode->next; //指向下一个Node 
	} //完事之后，画笔停在本行末尾
	show_mouse(); 
 }
/*
 *@name:printlist_chinese
 *@msg:打印汉化模式下链表
 *@param:{Hnode *}hnode 链表头节点
 *@param:{int *}color 颜色数组
 *@param:{int}hl 当前显示的链表行数
 *@param:{int}hr 当前显示的链表列数
 *@return:{void}
*/
void printlist_chinese(Hnode *hnode, int color[],int hl,int hr) //目前传入的hnode为p,color为pcolor
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
	sethzmode(ziti, hz_s[h]); //设置字体
	settextjustify(0, 0);
	settextstyle(0, 0, 1);
	
	for (i = 0; i < hl&&hnode!=NULL ;i++)
		hnode = hnode->next;
	for (i = 0; (i < 26) && hnode != NULL; i++) //共能显示26行
		//for (i = 0; (i < 26) && hnode != NULL&&hnode->head!=NULL; i++) //共能显示26行
	{
		sprintf(hang, "%d", i + hl+1); //输出行号
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
 *@msg:画中文界面下提示框
 *@param:{void}
 *@return:{void}
*/
void draw_com(void)
{
	
	hide_mouse();
	
	setbkcolor(0); //背景设置为黑色，为了出黑字，之后设置0居然是背景颜色？谜之操作 
	cleardevice(); //清屏 
	drawmain_c();

	barxy(96, 48*3, 640-96*2, 48*4, 15);   //大白框 
	
	line(96, 48*3+32+10, 96+32*4+10,48*3+32+10 );   //分割线
	 //从左边框过50开始打{与}的。。。。
	setfillstyle(1, 7);
	bar(320 - 32 - 5-10, 240 + 80-40, 320 - 32 - 5+10+37 * 2, 240 + 80-40+ 32 + 10);
	 //全用的xy x1y1x2y2
	show_mouse();
}
/*
 *@name:ziti_set
 *@msg:将字体配置写入文件
 *@param:{int}i字体配置标志
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
 *@msg:从文件中读取字体配置
 *@param:{void}
 *@return:{int}t 返回字体配置标志
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
 *@msg:画汉化模式下进度条
 *@param:{int}hl 当前显示行数
 *@param:{int}shl 当前显示总行数
 *@param:{int}hr 当前显示列数
 *@param:{int}shr 当前显示总列数
 *@return:{void}
*/
void probar(int hl,int shl, int hr,int shr) //画进度条函数
{
	int r; //行坐标 //行进度条从横坐标为0开始，至横坐标为640结束 总计为640 箭头各占十，纯进度条为630
	if (hr == 1)
		r=10;
	else
	r = (int)(((float)hr / (float)shr) * (610-10)) + 10; //行进度条方块的左坐标
	int l; //列坐标 列进度条从30开始，至纵坐标为480结束，总计为450，箭头各占十，纯进度条为430
	
	l = (int)(((float)hl / (float)shl) * (430-20-20-23))  + 40;

	 //画横进度条，包括箭头
	setfillstyle(1, DARKGRAY);
	bar(0, 480 - 20, 640, 480);
	setfillstyle(1, BLACK);
	bar(r, 480 - 20, r + 10, 480);

	setcolor(0); //画三角形的箭头
	line(0, 480-10, 10,480-20 );
	line(0, 480-10, 10, 480);
	line(10, 480 - 20, 10, 480);

	line(640 - 10, 480 - 20, 640, 480 - 10);
	line(640 - 10, 480, 640, 480 - 10);
	line(640 - 10, 480 - 20, 640 - 10, 480);

	 //画纵进度条，不包括箭头
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
 *@msg:汉化模式下向左翻页
 *@param:{Hnode *}hnode_c 列表头
 *@param:{int}hr 翻页前所处列数
 *@return:{int}hr 翻页后所处列数
*/
int menu_cl(Hnode *hnode_c,int hr) //返回值为hr, //传入值为p2
{
	 //Hnode *p2 = hnode_c;
	Node *node;
	int i=0;
	int flag_r = 0;

	if (hr == 1); //无效 
	else
	{
		while (hnode_c != NULL)
		{
			node = hnode_c->head->next;

			for (i = 1; i < hr - 3 && node != NULL; i++)
			{
				node = node->next;
			} //步进到当前显示第一列的前三列，再判断下一个是否为中文

			while (node != NULL)
			{
				if (node->chr >= 0x80 && (hr - 3) % 3 == 1) //下一个是中文
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
			hr--; //当前第一行显示的实际行数减1
		}

	}
	return hr;
}
/*
 *@name:menu_cr
 *@msg:汉化模式下向右翻页
 *@param:{Hnode *}hnode_c 链表头
 *@param:{int}hr 翻页前所处列数
 *@return:{int}hr 翻页后所处列数
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
			} //步进到当前显示第一列，再判断是否为中文
			if (node == NULL)
			{
				flag_r2++;
			}
			while (node != NULL)
			{
				if (node->chr >= 0x80) //下一个是中文
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
				hr++; //当前第一列显示的实际列数加1
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
 *@msg:汉化模式下画提示框
 *@param:{void}
 *@return:{void}
*/
void draw_oc()
{
	hide_mouse();
	setbkcolor(0); //背景设置为黑色，为了出黑字，之后设置0居然是背景颜色？谜之操作
	barxy(96+96*2, 48 * 3, 640 - 96 * 5, 48 * 2, 15);
	setcolor(0);
	line(96+96*2, 48 * 3 + 32 + 10, 96 + 32 * 2 + 10+96*2, 48 * 3 + 32 + 10);   //分割线
	setfillstyle(1, 7);
	show_mouse();
}
/*
 *@name:draw_help
 *@msg:画帮助界面
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
	sethzmode(YOU16, hz_s[h]); //设置字体
	settextjustify(0, 0);
	settextstyle(0, 0, 1);
	hide_mouse();
	unsigned int hzg_1[2] = { 0x5e2e,0x52a9 }; //"帮助"
	unsigned  int  hzg1[7] = { 0x5de6,0x53f3,0x002f,0x4e0a,0x4e0b,0x7ffb,0x9875 }; //左右/上下翻页
	unsigned  int  hzg2[8] = { 0x0031,0x002e,0x70b9,0x51fb,0x7bad,0x5934,0x7b26,0x53f7 }; //点击箭头符号
	unsigned  int  hzg3[7] = { 0x0032,0x002e,0x70b9,0x51fb,0x8fdb,0x5ea6,0x6761 }; //点击进度条
	unsigned  int  hzg4[10] = { 0x0033,0x002e,0x6309,0x4e0b,0x4e0a,0x4e0b,0x5de6,0x53f3,0x6309,0x952e }; //按下上下左右按键
	unsigned  int  hzg5[7] = { 0x547d,0x4ee4,0x6a21,0x5f0f,0x6307,0x4ee4,0x8868 }; //命令模式指令表
	unsigned  int  hzg6[9] = { 0x8f93,0x5165,0x547d,0x4ee4,0x540e,0x6309,0x4e0b,0x56de,0x8f66 }; //输入命令后按下回车
	unsigned  int  hzg7[2] = { 0x4f8b,0x5982 }; //例如
	unsigned  int  hzg8[18] = { 0x006f,0x0074,0x006c,0x0035,0x5f53,0x524d,0x663e,0x793a,0x7b2c,0x4e00,0x884c,0x8df3,0x8f6c,0x5230,0x603b,0x7b2c,0x4e94,0x884c }; //当前显示第一行跳转到总第五行
	unsigned  int  hzg9[18] = { 0x006f,0x0074,0x0072,0x0035,0x5f53,0x524d,0x663e,0x793a,0x7b2c,0x4e00,0x5217,0x8df3,0x8f6c,0x5230,0x603b,0x7b2c,0x4e94,0x5217 }; //当前显示第一列跳转到总第五列
	unsigned  int  hzg10[9] = { 0x006f,0x0064,0x006c,0x0035,0x5220,0x9664,0x7b2c,0x4e94,0x884c }; //删除第五行
	unsigned  int  hzg11[2] = { 0x006f,0x0061 };//oa
	unsigned int hzg11_1[13]={0x0062,0x006c,0x0035,0x5728,0x7b2c,0x4e94,0x884c,0x4e0b,0x65b9,0x63d2,0x5165,0x7a7a,0x884c }; //在第五行下方插入空行
	unsigned  int  hzg12[20] = { 0x006f,0x0061,0x0063,0x006c,0x0035,0x5728,0x7b2c,0x4e94,0x884c,0x4e0b,0x65b9,0x63d2,0x5165,0x526a,0x8d34,0x677f,0x4e2d,0x7684,0x4e00,0x884c }; //在第五行下方插入剪贴板中的一行行
	unsigned  int  hzg13[15] = { 0x006f,0x0063,0x006c,0x0035, 0x5c06,0x7b2c,0x4e94,0x884c,0x590d,0x5236,0x5230,0x526a,0x8d34,0x677f,0x4e2d }; //将第五行复制到剪贴板中
	unsigned  int  hzg130[15] = { 0x006f,0x0078,0x006c,0x0035, 0x5c06,0x7b2c,0x4e94,0x884c,0x526a,0x5207,0x5230,0x526a,0x8d34,0x677f,0x4e2d }; //将第五行剪切到剪贴板中
	unsigned  int  hzg14[4] = { 0x82f1,0x6587,0x542b,0x4e49 }; //英文含义
	unsigned  int  hzg15[6] = { 0x0074,0x003a,0x0074,0x006f,0x8df3,0x8f6c }; //t:to跳转
	unsigned  int  hzg16[7] = { 0x006c,0x003a,0x006c,0x0069,0x006e,0x0065,0x884c }; //l
	unsigned  int  hzg17[6] = { 0x0072,0x003a,0x0072,0x006f,0x0077,0x5217 }; //r
	unsigned  int  hzg18[10] = { 0x0064,0x003a,0x0064,0x0065,0x006c,0x0065,0x0074,0x0065,0x5220,0x9664 }; //d
	unsigned  int  hzg19[7] = { 0x0061,0x003a,0x0061,0x0064,0x0064,0x6dfb,0x52a0 }; //a
	unsigned  int  hzg20[9] = { 0x0020,0x003a,0x0020,0x006c,0x0061,0x006e,0x0020,0x7a7a,0x767d }; //b //由于汉字库不全 用 代替b和k 将补上；
	char blank_1[] = { 'b','\0' };
	char blank_2[] = { 'k','\0' };
	unsigned  int  hzg21[8] = { 0x0063,0x003a,0x0063,0x006f,0x0070,0x0079,0x590d,0x5236 }; //c
	unsigned int hzg0[2] = { 0x786e,0x5b9a };
	hide_mouse();
	setbkcolor(0);
	cleardevice();
	barxy(0, 0, 640, 480, 15); //屏幕变白
	line(0, 32 + 10, 32 * 4 + 10, 32 + 10); //分隔线
	setfillstyle(1, 7);
	bar(320 - 32 - 5 - 10, 480 - 50, 320 - 32 - 5 + 10 + 37 * 2, 480 - 50 + 32 + 10);
	 //全用的xy x1y1x2y2
	put_s_hz(0 + 10, 2, hzg_1, 2, YOU16);
	put_s_hz(320 - 32 - 5 - 10 + 30, 480 - 50 + 16, hzg0, 2, YOU16); //确定
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
 *@msg:命令模式下插入剪切板中一行
 *@param:{Hnode *}hnode 插入行之前的行链表头
 *@param:{Hnode *}hnode_c 剪切板中一行链表头
 *@param:{} //遗留问题 需要处理
 *@return:{void}
*/
void add_cl(Hnode *hnode, Hnode *hnode_c) //在hnode行后插入hnode_c(需要复制）行
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
 *@msg:命令模式下将链表中一行复制到剪切板中
 *@param:{Hnode *}hnode_c 复制行的链表头
 *@param:{Hnode *}hnode_cc 剪切板的链表头
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
	while (node != NULL) //把选中行复制到新建的链表行里
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
 *@msg:汉化命令模式下删除一行
 *@param:{Hnode *}hnode 要删除行的链表头节点
 *@return:{Hnode *}删除后的行链表头节点
*/
Hnode * del_l(Hnode *hnode) //将hnode行删free掉 
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
	
	 //链表重新连接的操作在外边完成
	
}

/*
 *@name:draw_help2
 *@msg:画帮助界面
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
	sethzmode(YOU16, hz_s1[h]); //设置字体
	settextjustify(0, 0);
	settextstyle(0, 0, 1);
	hide_mouse();
	unsigned int hzg_1[2] = { 0x5e2e,0x52a9 }; //"帮助"
	unsigned  int  hzg5[5] = { 0x5f00,0x53d1,0x4eba,0x5458,0xff1a}; //开发人员
	unsigned  int  hzg8[9] = { 0x81ea,0x52a8,0x5316,0x7c7b,0x0032,0x0030,0x0030,0x0037,0x73ed }; //自动化类2007班
	unsigned  int  hzg9[3] = { 0x5468,0x500d,0x8fdb }; //周倍进
	unsigned  int  hzg10[3] = { 0x7530,0x660e,0x5b66 }; //田明学
	unsigned  int  hzg11[14] = { 0x5982,0x679c,0x60a8,0x6709,0x4efb,0x4f55,0x95ee,0x9898,0xff0c,0x8bf7,0x8054,0x7cfb,0x6211,0x4eec }; //如果您有任何问题，请联系我们
	unsigned  int  hzg12[6] = { 0x6211,0x4eec,0x7684,0x90ae,0x7bb1,0xff1a }; //我们的邮箱：
	unsigned  int  hzg13[17] = {0x0031,0x0030,0x0033,0x0030,0x0030,0x0031,0x0034,0x0033,0x0036,0x0030,0x0040,0x0071,0x0071,0x002e,0x0063,0x006f,0x006d }; //1030014360@qq.com
	unsigned int hzg0[2] = { 0x786e,0x5b9a };
	hide_mouse();
	setbkcolor(0);
	cleardevice();
	barxy(0, 0, 640, 480, 15); //屏幕变白
	line(0, 32 + 10, 32 * 4 + 10, 32 + 10); //分隔线
	setfillstyle(1, 7);
	bar(320 - 32 - 5 - 10, 480 - 50, 320 - 32 - 5 + 10 + 37 * 2, 480 - 50 + 32 + 10);
	 //全用的xy x1y1x2y2
	put_s_hz(0 + 10, 2+10, hzg_1, 2, YOU16);
	put_s_hz(320 - 32 - 5 - 10 + 30, 480 - 50 + 16, hzg0, 2, YOU16); //确定
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
 *@msg:清空剪切板
 *@param:{Hnode *}hnode 剪切板头
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
