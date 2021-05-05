#include "mainloop.h"

/*
 *@name:mainloop
 *@msg:主循环，进行菜单控制变量等的初始化，响应鼠标按键操作
 *@param:{void}
 *@return:{void}
*/
void mainloop()
{

	int menu_c = 0;  //判断chinese中按下了哪个菜单
	int i;
	int ih;			  //用于高亮
	int flag_t;		  //用于临时储存菜单控制变量
	int flag = 0;	  //横菜单控制变量
	int flag2 = 0;	  //纵菜单控制变量
	int flag3 = 0;	  //第三级菜单控制变量一
	int flag3_1 = 0;  //第三季菜单控制变量二
	int flag_q2 = 0;  //判断是否需要按下确认键及是否按下

	char path[128] = "C:\\BCS\\FILE\\";		 //默认文件路径
	char file[64]= "\0";
	int color[6] = {14, 11, 15, 10, 7, 12};  //储存文本颜色

	int op = F10;	   //按键返回值
	int saveflag = 1;  //文件是否保存
	int textflag = 0;  //是否有文本正在打开
	int ismenu = 0;	   //菜单是否正在打开
	char ch;
	int h;  //字体控制变量
	Hnode *hnode = (Hnode *)malloc(sizeof(Hnode));
	Cursornode cursornode;
	Clipboard clipboard;
	Offset offset;

	color_set2(color);  //读取文件中上次设置的颜色
	h = ziti_set2();    //读取文件中上次设置的字体

	show_mouse();
	window(5, 3, 80, 23);

	while (1)
	{
		getmouse();
		if (M_sc < 0)
		{
			/*点击非菜单时将菜单隐藏*/
			if (
				(
					!pd(24, 0, 8 * 80 - 24, 8)  //b_y按钮
					) &&
					((flag2 % 4 == 0) && !pd(7 * 8 + 4, 16 - 8, (16 + 1) * 8, 8 * 9)  //file
					 ) ||
				((flag2 % 4 == 1) && !pd(25 * 8 + 4, 16 - 8, (7 + 1) * 8, 8 * 7)  //edit
				 ) ||
				((flag2 % 4 == 2) && !pd(41 * 8 + 4, 16 - 8, (5 + 1) * 8, 8 * 5) && flag3 == 0  //setting
				 ) ||
				((flag2 % 4 == 3) && !pd(61 * 8 + 4, 16 - 8, (13 + 1) * 8, 8 * 4)  //pattern
				 ) ||
				((flag3 == 1)  //style
				 && !pd(41 * 8 + 4, 16 - 8, (5 + 1) * 8, 8 * 4) && !pd((41 + 7) * 8 + 4, 16, (5 + 1) * 8, 8 * 7)) ||
				((flag3 == 2)  //color
				 && !pd(41 * 8 + 4, 16 - 8, (5 + 1) * 8, 8 * 4) && !pd((41 + 7) * 8 + 4, 16 + 8, 7 * 8, 8 * 7)))
			{
				flag = 0;  //菜单变量置零
				flag2 = 0;

				if (textflag != 0)
				{
					drawmain();
					Printlist(hnode, &cursornode, &offset);
				}
				window(1, 1, 80, 25);
				drawmain();
			}
			 //鼠标点击跳转模块
			if (textflag == 1 && ismenu == 0 &&flag==0)  //如果菜单未打开，且文本已打开，鼠标点击跳转
			{
				Mouse_choose(hnode, &cursornode, &offset);
				Mouse_click(hnode, &cursornode, &offset);
			}
			 //编译模块
			if (pd(0, 0, 24, 8))
			{

				complie(hnode, &cursornode, 0, 0, '(', ')');
				complie(hnode, &cursornode, 0, 0, '[', ']');
				complie(hnode, &cursornode, 0, 0, '{', '}');
				complie(hnode, &cursornode, 3, 0, '"', '"');
				complie(hnode, &cursornode, 3, 0, '\'', '\'');
				complie(hnode, &cursornode, 5, 0, '(', ')');
				if (textflag != 0)
				{
					Printlist(hnode, &cursornode, &offset);
					Find_cursor(hnode, &cursornode, &offset);
				}

				flag = 0;
				flag2 = 0;
				flag3 = 0;
			}
			 //鼠标点击各个菜单栏模块
			if (pd(6 * 8 + 4, 0, 80, 8))  //File
			{
				flag = drawmenu(hnode, &cursornode, &offset, textflag, F1);
				flag2 = 100;
				flag3 = 0;
			}
			else if (pd(24 * 8 + 4, 0, 80, 8))  //Edit
			{
				flag = drawmenu(hnode, &cursornode, &offset, textflag, F2);
				flag2 = 101;
				flag3 = 0;
			}
			else if (pd(42 * 8 + 4, 0, 8 * 13, 8))  //settings
			{
				flag = drawmenu(hnode, &cursornode, &offset, textflag, F3);
				flag2 = 102;
				flag3 = 0;
			}
			else if (pd(60 * 8 + 4, 0, 8 * 14, 8))  //pattern
			{
				flag = drawmenu(hnode, &cursornode, &offset, textflag, F4);
				flag2 = 103;
				flag3 = 0;
			}
			else if (flag2 != 0)  //flag2!=0表示菜单已经展开
			{

				switch (flag2 % 4)
				{
				case 0:  //File
					for (i = 0; i < 7; i++)
					{
						if (pd(7 * 8 + 4, 16 + 8 * i, 16 * 8, 8))  //判断点击的菜单
						{
							flag_t = 140 + i;
							flag = menu_ud_m(flag, flag_t);
							flag3 = 0;
							switch (flag % 7)
							{
							case 0:  //new
								hnode = InitList(hnode, &cursornode, &offset, &clipboard, &saveflag, &textflag);
								strcpy(file,"\0");
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;

								break;
							case 1:  //readfile
								hnode = InitList(hnode, &cursornode, &offset, &clipboard, &saveflag, &textflag);
								ReadFile(hnode, &cursornode, &saveflag, &textflag, path,file);
								flag = 0;
								flag2 = 0;
								
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									chigh_li(hnode);
									for (i = 0; i < 6; i++)
									{
										High_li(hnode, &cursornode, color[i], i);
									}
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								break;
							case 2:  //save
								Save(hnode, &saveflag, &textflag, path, file);
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								break;
							case 3:  //save as
								SaveFile(hnode, &saveflag, &textflag, path);
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								break;
							case 4:  //change_directories
								Change_dir(path);
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								break;
							case 5:  //close
								Close(hnode, &saveflag, &textflag);
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								break;
							case 6:  //exit
								Close(hnode, &saveflag, &textflag);
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								free(hnode);
								hnode = NULL;
								exit(0);
								break;
							}
						}
					}
					break;
				case 1:  //Edit
					for (i = 0; i < 5; i++)
					{
						if (pd(25 * 8 + 4, 16 + 8 * i, 7 * 8, 8))  //判断点击的菜单
						{
							flag3 = 0;
							flag_t = 280 + i;
							flag = menu_ud_m(flag, flag_t);
							switch (flag % 5)
							{
							case 0:  //copy
								Putclip(hnode, &clipboard);
								clrscr();
								window(1, 1, 80, 25);
								drawmain();
								if (textflag != 0)
								{
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								break;
							case 1:  //cut
								Cut(hnode, &cursornode, &clipboard);
								clrscr();
								window(1, 1, 80, 25);
								drawmain();
								chigh_li(hnode);
								for (i = 0; i < 6; i++)
								{
									High_li(hnode, &cursornode, color[i], i);
								}
								if (textflag != 0)
								{
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								break;
							case 2:  //paste
								Paste(hnode, &cursornode, &clipboard);
								clrscr();
								window(1, 1, 80, 25);
								drawmain();
								chigh_li(hnode);
								for (i = 0; i < 6; i++)
								{
									High_li(hnode, &cursornode, color[i], i);
								}
								if (textflag != 0)
								{
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								break;
							case 3:  //search
								Search(hnode, &cursornode);
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								break;
							case 4:  //replace
								Replace(hnode, &cursornode);
								chigh_li(hnode);
								for (i = 0; i < 6; i++)
								{
									High_li(hnode, &cursornode, color[i], i);
								}
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								break;
							}
						}
					}
					break;

				case 2:  //Settings
					for (i = 0; i < 3; i++)
					{

						if (pd(41 * 8 + 4, 16 + 8 * i, 5 * 8, 8))  //判断点击的菜单
						{
							flag3 = 0;
							flag_t = 420 + i;
							flag = menu_ud_m(flag, flag_t);
							switch (flag % 3)
							{
							case 0:
								flag3 = 1;
								drawmenu(hnode, &cursornode, &offset, textflag, 1);
								break;
							case 1:
								flag3 = 2;
								drawmenu(hnode, &cursornode, &offset, textflag, 2);
								break;
							case 2:
								int graphdriver = VGA;
								int graphmode = 2;
								initgraph(&graphdriver, &graphmode, "C:\\borlandc\\bgi");
								cleardevice();
								initmouse(1);
								flag_q2 = 1;
								draw_help();
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

										break;
									}
								}
								flag_q2 = 0;
								closegraph();
								initmouse(0);
								show_mouse();
								drawmain();
								if (textflag != 0)
								{
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								break;
							}
						}
					}
					break;

				case 3:  //Pattern
					for (i = 0; i < 2; i++)
					{
						if (pd(61 * 8 + 4, 16 + 8 * i, 13 * 8, 8))  //同上
						{
							flag3 = 0;
							flag_t = 560 + i;
							flag = menu_ud_m(flag, flag_t);
							switch (flag % 2)
							{
							case 0:
								flag = 0;
								flag2 = 0;
								window(1, 1, 80, 25);
								drawmain();
								if (textflag != 0)
								{
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								break;
							case 1:
								flag = 0;
								flag2 = 0;
								hnode = chinese(hnode, &cursornode, &menu_c, color, textflag);
								show_mouse();
								window(1, 1, 80, 25);
								drawmain();
								if (textflag != 0)
								{
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								switch (menu_c)
								{
								case 0:
									flag = 0;
									flag2 = 0;
									break;
								case 1:
									flag = 0;
									flag2 = 0;
									hnode = InitList(hnode, &cursornode, &offset, &clipboard, &saveflag, &textflag);
									if (textflag != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										Printlist(hnode, &cursornode, &offset);
										Find_cursor(hnode, &cursornode, &offset);
									}
									menu_c = 0;
									break;
								case 2:
									hnode = InitList(hnode, &cursornode, &offset, &clipboard, &saveflag, &textflag);
									ReadFile(hnode, &cursornode, &saveflag, &textflag, path,file);
									flag = 0;
									flag2 = 0;
									
									if (textflag != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										chigh_li(hnode);
										for (i = 0; i < 6; i++)
										{
											High_li(hnode, &cursornode, color[i], i);
										}
										Printlist(hnode, &cursornode, &offset);
										Find_cursor(hnode, &cursornode, &offset);
									}
									menu_c = 0;
									break;
								case 3:
									Save(hnode, &saveflag, &textflag, path, file);
									if (textflag != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										Printlist(hnode, &cursornode, &offset);
										Find_cursor(hnode, &cursornode, &offset);
									}
									flag = 0;
									flag2 = 0;
									menu_c = 0;
									break;
								case 4:
									SaveFile(hnode, &saveflag, &textflag, path);
									if (textflag != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										Printlist(hnode, &cursornode, &offset);
										Find_cursor(hnode, &cursornode, &offset);
									}
									flag = 0;
									flag2 = 0;
									menu_c = 0;
									break;
								case 5:
									Change_dir(path);
									if (textflag != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										Printlist(hnode, &cursornode, &offset);
										Find_cursor(hnode, &cursornode, &offset);
									}
									flag = 0;
									flag2 = 0;
									menu_c = 0;
									break;

								case 6:  //close
									Close(hnode, &saveflag, &textflag);
									if (textflag != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										Printlist(hnode, &cursornode, &offset);
										Find_cursor(hnode, &cursornode, &offset);
									}
									flag = 0;
									flag2 = 0;
									break;
								case 7:  //exit
									Close(hnode, &saveflag, &textflag);
									if (textflag != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										Printlist(hnode, &cursornode, &offset);
										Find_cursor(hnode, &cursornode, &offset);
									}
									flag = 0;
									flag2 = 0;
									free(hnode);
									hnode = NULL;
									exit(0);
									break;
								case 11:
									Putclip(hnode, &clipboard);
									if (textflag != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										Printlist(hnode, &cursornode, &offset);
										Find_cursor(hnode, &cursornode, &offset);
									}
									flag = 0;
									flag2 = 0;
									menu_c = 0;
									break;
								case 12:

									Cut(hnode, &cursornode, &clipboard);
									if (textflag != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										chigh_li(hnode);
										for (i = 0; i < 6; i++)
										{
											High_li(hnode, &cursornode, color[i], i);
										}
										Printlist(hnode, &cursornode, &offset);
										Find_cursor(hnode, &cursornode, &offset);
									}
									flag = 0;
									flag2 = 0;
									menu_c = 0;
									break;
								case 13:
									Paste(hnode, &cursornode, &clipboard);
									if (textflag != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										chigh_li(hnode);
										for (i = 0; i < 6; i++)
										{
											High_li(hnode, &cursornode, color[i], i);
										}
										Printlist(hnode, &cursornode, &offset);
										Find_cursor(hnode, &cursornode, &offset);
									}
									flag = 0;
									flag2 = 0;
									menu_c = 0;
									break;
								case 14:

									Search(hnode, &cursornode);
									if (textflag != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										Printlist(hnode, &cursornode, &offset);
										Find_cursor(hnode, &cursornode, &offset);
									}
									flag = 0;
									flag2 = 0;
									menu_c = 0;
									break;
								case 15:
									Replace(hnode, &cursornode);
									if (textflag != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										chigh_li(hnode);
										for (i = 0; i < 6; i++)
										{
											High_li(hnode, &cursornode, color[i], i);
										}
										Printlist(hnode, &cursornode, &offset);
										Find_cursor(hnode, &cursornode, &offset);
									}
									flag = 0;
									flag2 = 0;
									menu_c = 0;
									break;
								}
								break;
							}
						}
					}
					break;
				}

				if (flag3 == 1)
				{
					for (i = 0; i < 5; i++)
					{
						if (pd((41 + 7) * 8 + 4, 16 + 8 * (i + 1), 5 * 8, 8))
						{

							flag = 0;
							flag2 = 0;
							flag3 = 0;
							window(1, 1, 80, 25);
							drawmain();

							h = i;		  //字体变量的设置
							ziti_set(i);  //改变文件中的字体变量储存

							if (textflag != 0)
							{
								drawmain();
								Printlist(hnode, &cursornode, &offset);
								Find_cursor(hnode, &cursornode, &offset);
							}
						}
					}
				}
				if (flag3 == 2)
				{
					for (i = 0; i < 5; i++)
					{
						if (pd((41 + 7) * 8 + 4, 16 + 8 * (i + 2), 7 * 8, 8))
						{

							flag = 0;
							flag2 = 0;
							flag3 = 0;
							window(1, 1, 80, 25);
							drawmain();
							color_set(i);
							color_set2(color);

							for (i = 0; i < 6; i++)
							{
								High_li(hnode, &cursornode, color[i], i);
							}

							if (textflag != 0)
							{
								drawmain();
								Printlist(hnode, &cursornode, &offset);
								Find_cursor(hnode, &cursornode, &offset);
							}
						}
					}
				}
			}
			continue;
		}

		if (bioskey(1) != 0) //按键响应
		{

			op = bioskey(0);
			if (op == ESC)
			{
				ClearLists(hnode);
				free(hnode);
				hnode = NULL;
				exit(0);
			}
			if (op == F1 || op == F2 || op == F3 || op == F4)
			{
				flag3 = 0;
				flag = drawmenu(hnode, &cursornode, &offset, textflag, op);
				if (op == F1)
					flag2 = 100;
				if (op == F2)
					flag2 = 101;
				if (op == F3)
					flag2 = 102;
				if (op == F4)
					flag2 = 103;
			}
			if ((op == UP || op == DOWN) && flag != 0)
			{
				if (flag3 == 0)
				{
					window(1, 1, 80, 25);
					flag = menu_ud(op, flag, hnode, &cursornode, &offset, textflag);
				}

				else if (flag3 == 1 || flag3 == 2)
				{
					window(1, 1, 80, 25);
					flag3_1 = menu_ud3(op, flag3, flag3_1, hnode, &cursornode, &offset, textflag);
				}
			}
			if ((op == LEFT || op == RIGHT) && flag2 != 0)
			{

				flag2 = menu_lr(op, flag2, &flag, hnode, textflag, &cursornode, &offset);
				flag3 = 0;
			}
			if (op == ENTER && flag2 != 0)  // 提供接口 //只要flag2不等于0，说明已经画了菜单，flag肯定不等于0
			{
				 //flag2%4定位横坐标，有了横坐标之后flag%7or5or2定位纵坐标
				if (flag3 == 0)
				{

					switch (flag2 % 4)
					{
					case 0:  //file菜单下，下面的递进
						switch (flag % 7)
						{
						case 0:
							hnode = InitList(hnode, &cursornode, &offset, &clipboard, &saveflag, &textflag);
							if (textflag != 0)
							{
								window(1, 1, 80, 25);
								drawmain();
								Printlist(hnode, &cursornode, &offset);
								Find_cursor(hnode, &cursornode, &offset);
							}
							flag = 0;
							flag2 = 0;
							break;
						case 1:
							hnode = InitList(hnode, &cursornode, &offset, &clipboard, &saveflag, &textflag);
							ReadFile(hnode, &cursornode, &saveflag, &textflag, path,file);
							flag = 0;
							flag2 = 0;
							
							if (textflag != 0)
							{
								window(1, 1, 80, 25);
								drawmain();
								chigh_li(hnode);

								for (i = 0; i < 6; i++)
								{
									High_li(hnode, &cursornode, color[i], i);
								}
								Printlist(hnode, &cursornode, &offset);
								Find_cursor(hnode, &cursornode, &offset);
							}
							break;
						case 2:
							Save(hnode, &saveflag, &textflag, path, file);
							if (textflag != 0)
							{
								window(1, 1, 80, 25);
								drawmain();
								Printlist(hnode, &cursornode, &offset);
								Find_cursor(hnode, &cursornode, &offset);
							}
							flag = 0;
							flag2 = 0;
							break;
						case 3:
							SaveFile(hnode, &saveflag, &textflag, path);
							if (textflag != 0)
							{
								window(1, 1, 80, 25);
								drawmain();
								Printlist(hnode, &cursornode, &offset);
								Find_cursor(hnode, &cursornode, &offset);
							}
							flag = 0;
							flag2 = 0;
							break;
						case 4:
							Change_dir(path);
							if (textflag != 0)
							{
								window(1, 1, 80, 25);
								drawmain();
								Printlist(hnode, &cursornode, &offset);
								Find_cursor(hnode, &cursornode, &offset);
							}
							flag = 0;
							flag2 = 0;
							break;
						case 5:
							Close(hnode, &saveflag, &textflag);
							if (textflag != 0)
							{
								window(1, 1, 80, 25);
								drawmain();
								Printlist(hnode, &cursornode, &offset);
								Find_cursor(hnode, &cursornode, &offset);
							}
							flag = 0;
							flag2 = 0;
							break;
						case 6:
							Close(hnode, &saveflag, &textflag);
							if (textflag != 0)
							{
								window(1, 1, 80, 25);
								drawmain();
								Printlist(hnode, &cursornode, &offset);
								Find_cursor(hnode, &cursornode, &offset);
							}
							flag = 0;
							flag2 = 0;
							exit(0);
							break;
						}
						break;

					case 1:
						switch (flag % 5)
						{
						case 0:
							Putclip(hnode, &clipboard);
							if (textflag != 0)
							{
								window(1, 1, 80, 25);
								drawmain();
								Printlist(hnode, &cursornode, &offset);
								Find_cursor(hnode, &cursornode, &offset);
							}
							flag = 0;
							flag2 = 0;
							break;
						case 1:
							Cut(hnode, &cursornode, &clipboard);
							
							if (textflag != 0)
							{
								window(1, 1, 80, 25);
								drawmain();
								chigh_li(hnode);
								for (i = 0; i < 6; i++)
								{
									High_li(hnode, &cursornode, color[i], i);
								}
								Printlist(hnode, &cursornode, &offset);
								Find_cursor(hnode, &cursornode, &offset);
							}
							flag = 0;
							flag2 = 0;
							break;
						case 2:
							Paste(hnode, &cursornode, &clipboard);
							
							if (textflag != 0)
							{
								window(1, 1, 80, 25);
								drawmain();
								chigh_li(hnode);
								for (i = 0; i < 6; i++)
								{
									High_li(hnode, &cursornode, color[i], i);
								}
								Printlist(hnode, &cursornode, &offset);
								Find_cursor(hnode, &cursornode, &offset);
							}
							flag = 0;
							flag2 = 0;
							break;
						case 3:
							Search(hnode, &cursornode);
							if (textflag != 0)
							{
								window(1, 1, 80, 25);
								drawmain();
								Printlist(hnode, &cursornode, &offset);
								Find_cursor(hnode, &cursornode, &offset);
							}
							flag = 0;
							flag2 = 0;
							break;
						case 4:
							chigh_li(hnode);
							for (i = 0; i < 6; i++)
							{
								High_li(hnode, &cursornode, color[i], i);
							}
							Replace(hnode, &cursornode);
							if (textflag != 0)
							{
								window(1, 1, 80, 25);
								drawmain();
								Printlist(hnode, &cursornode, &offset);
								Find_cursor(hnode, &cursornode, &offset);
							}
							flag = 0;
							flag2 = 0;
							break;
						}
						break;

					case 2:
						switch (flag % 3)
						{
						case 0:
							drawmenu(hnode, &cursornode, &offset, textflag, 1);

							flag3 = 1;
							flag3_1 = 100;

							break;
						case 1:
							drawmenu(hnode, &cursornode, &offset, textflag, 2);

							flag3 = 2;
							flag3_1 = 100;

							break;
						case 2:
							initmouse(1);
							int graphdriver = VGA;
							int graphmode = 2;
							initgraph(&graphdriver, &graphmode, "C:\\borlandc\\bgi");
							cleardevice();
							draw_help();
							flag_q2 = 1;
							show_mouse();
							while (1)
							{
								getmouse();
								 //int a=0;
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

									break;
								}
							}
							flag_q2 = 0;
							closegraph();
							initmouse(0);
							show_mouse();
							window(1, 1, 80, 25);
							drawmain();
							if (textflag != 0)
							{
								drawmain();
								Printlist(hnode, &cursornode, &offset);
								Find_cursor(hnode, &cursornode, &offset);
							}

							flag = 0;
							flag2 = 0;
							break;
						}
						break;

					case 3:
						switch (flag % 2)
						{
						case 0:
							flag = 0;
							flag2 = 0;
							window(1, 1, 80, 25);
							drawmain();
							if (textflag != 0)
							{
								drawmain();
								Printlist(hnode, &cursornode, &offset);
								Find_cursor(hnode, &cursornode, &offset);
							}
							break;
						case 1:
							hnode = chinese(hnode, &cursornode, &menu_c, color, textflag);  //h�����ò˵�ȷ��
							show_mouse();
							window(1, 1, 80, 25);
							drawmain();
							if (textflag != 0)
							{
								drawmain();
								Printlist(hnode, &cursornode, &offset);
								Find_cursor(hnode, &cursornode, &offset);
							}
							flag = 0;
							flag2 = 0;
							switch (menu_c)
							{
							case 0:
								flag = 0;
								flag2 = 0;
								break;
							case 1:
								flag = 0;
								flag2 = 0;
								hnode = InitList(hnode, &cursornode, &offset, &clipboard, &saveflag, &textflag);
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								menu_c = 0;
								break;
							case 2:
								hnode = InitList(hnode, &cursornode, &offset, &clipboard, &saveflag, &textflag);
								ReadFile(hnode, &cursornode, &saveflag, &textflag, path,file);
								flag = 0;
								flag2 = 0;
								
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									chigh_li(hnode);
									for (i = 0; i < 6; i++)
									{
										High_li(hnode, &cursornode, color[i], i);
									}
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								menu_c = 0;
								break;
							case 3:
								Save(hnode, &saveflag, &textflag, path, file);
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								menu_c = 0;
								break;
							case 4:
								SaveFile(hnode, &saveflag, &textflag, path);
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								menu_c = 0;
								break;
							case 5:
								Change_dir(path);
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								menu_c = 0;
								break;
							case 6:  //close
								Close(hnode, &saveflag, &textflag);
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								break;
							case 7:  //exit
								Close(hnode, &saveflag, &textflag);
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								free(hnode);
								hnode = NULL;
								exit(0);
								break;
							case 11:
								Putclip(hnode, &clipboard);
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								menu_c = 0;
								break;
							case 12:

								Cut(hnode, &cursornode, &clipboard);
								
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									chigh_li(hnode);
									for (i = 0; i < 6; i++)
									{
										High_li(hnode, &cursornode, color[i], i);
									}
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								menu_c = 0;
								break;
							case 13:
								Paste(hnode, &cursornode, &clipboard);
								
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									chigh_li(hnode);
									for (i = 0; i < 6; i++)
									{
										High_li(hnode, &cursornode, color[i], i);
									}
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								menu_c = 0;
								break;
							case 14:

								Search(hnode, &cursornode);
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								menu_c = 0;
								break;
							case 15:
								Replace(hnode, &cursornode);
								if (textflag != 0)
								{
									window(1, 1, 80, 25);
									drawmain();
									chigh_li(hnode);
									for (i = 0; i < 6; i++)
									{
										High_li(hnode, &cursornode, color[i], i);
									}
									Printlist(hnode, &cursornode, &offset);
									Find_cursor(hnode, &cursornode, &offset);
								}
								flag = 0;
								flag2 = 0;
								menu_c = 0;
								break;
							}
							break;
						}
						break;
					}
				}
				else if (flag3 == 1) //字体设置
				{

					flag = 0;
					flag2 = 0;
					flag3 = 0;
					h = flag3_1 % 5;

					ziti_set(h);
					window(1, 1, 80, 25);
					drawmain();
					if (textflag != 0)
					{
						drawmain();
						Printlist(hnode, &cursornode, &offset);
						Find_cursor(hnode, &cursornode, &offset);
					}
				}
				else if (flag3 == 2) //颜色设置
				{
					flag = 0;
					flag2 = 0;
					flag3 = 0;
					drawmain();

					color_set(flag3_1);
					color_set2(color);
					window(1, 1, 80, 25);
					drawmain();
					if (textflag != 0)
					{
						drawmain();
						Printlist(hnode, &cursornode, &offset);
						Find_cursor(hnode, &cursornode, &offset);
					}
				}
				ismenu = 1;
			}
			if (textflag == 1 && ismenu == 0 && flag == 0)
			{
				hnode = Add(hnode, &cursornode, op, &saveflag, color);
				Printlist(hnode, &cursornode, &offset);
				Choose(hnode, &cursornode, op, &offset);
				if (op == CC)
				{
					Putclip(hnode, &clipboard);
					Recovery(hnode);
					Printlist(hnode, &cursornode, &offset);
					Find_cursor(hnode, &cursornode, &offset);
				}
				if (op == CX)
				{
					Cut(hnode, &cursornode, &clipboard);
					Recovery(hnode);
					Printlist(hnode, &cursornode, &offset);
					Find_cursor(hnode, &cursornode, &offset);
				}
				if (op == CV)
				{
					Paste(hnode, &cursornode, &clipboard);
					Printlist(hnode, &cursornode, &offset);
					Find_cursor(hnode, &cursornode, &offset);
				}
				if (op == CF)
				{
					for (int i = 0; i < 10; i++)
					{
						Cursormove(hnode, &cursornode, DOWN);
						Printlist(hnode, &cursornode, &offset);
						Find_cursor(hnode, &cursornode, &offset);
					}
				}
				if (op == CB)
				{
					for (int i = 0; i < 10; i++)
					{
						Cursormove(hnode, &cursornode, UP);
						Printlist(hnode, &cursornode, &offset);
						Find_cursor(hnode, &cursornode, &offset);
					}
				}
			}
		}
		ismenu = 0;
	}
}
