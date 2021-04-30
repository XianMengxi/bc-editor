#include<stdio.h>
#include"key.h"
#include"menu.h"
#include"function.h"
#include"define.h"
#include"mouse.h"
#include"edit.h"
#include"high_li.h"
#include"code.h"
#include"chinese.h"
#include"copy.h"
#define CF 0x2106
#define CB 0x3002
void mainloop()
{
	//int key=0;
	int i;
	int ih;//���ڸ���
	int flag_t;
	int flag=0;//��˵�
	int flag2=0;//�ݲ˵�
	int flag3 = 0;//�������˵�
	int flag3_1=0;//�������Ӳ˵���xia
	//int ic;
	//char buf_c[3];

	int cflag = 0;//chinese���صı�־��

	int flag_q2 = 0;//��������
	char path[128]="C:\\BCS\\FILE\\";
	char file[16]="borland";
	Clipboard clipboard;
	clipboard.clipboard = NULL;
	clipboard.num = 0;
	Offset offset;
	offset.x=1;
	offset.y=1;
	
	
	int op=F10;//��������ֵ
	int saveflags = 1;
	int textflags = 0;
	int ismenu=0;
	Hnode *hnode = (Hnode*)malloc(sizeof(Hnode));
	Cursornode cursornode;
	char ch;
	show_mouse(); 
	
	int color[6] = {14,11,15,10,7,12};//�����ı���ɫ
	color_set2(color);//��ȡ�ļ����ϴ����õ���ɫ

	/*char* hz_s[] = {
			"YOU16",
			"FS16",
			"HP16",
			"HT16",
			"MBXS16"
		};*/
	int h = ziti_set2();
	window(5,3,80,23);
	while (1)
	{
		
		//key=0;
		getmouse();
		

		
		/*High_li(hnode, &cursornode, 15, 0);//��������ɫ������
		High_li(hnode, &cursornode, 14, 1);
		High_li(hnode, &cursornode, 10, 2);
		High_li(hnode, &cursornode, 10, 3);*/

		



		if (M_sc<0)
		{
			if (
				(
					//!pd(0, 0, 8 * 80, 8)
					!pd(24, 0, 8 * 80 - 24, 8)//24Ϊb_y
				)
				&&
				(
					(flag2 % 4 == 0) && !pd(7 * 8 + 4, 16 - 8, (16 + 1) * 8, 8 * 9)
				)
				||
				(
					(flag2 % 4 == 1) && !pd(25 * 8 + 4, 16 - 8, (7 + 1) * 8, 8 * 7)
				)
				||
				(
					(flag2 % 4 == 2) && !pd(41 * 8 + 4, 16 - 8, (5 + 1) * 8, 8 * 5)&&flag3==0
				)
				||
				(
					(flag2 % 4 == 3) && !pd(61 * 8 + 4, 16 - 8, (13 + 1) * 8, 8 * 4)
				)
				||
				(
				(flag3==1)
				&& !pd(41 * 8 + 4, 16 - 8, (5 + 1) * 8, 8 * 4)
				&& !pd((41 + 7) * 8 + 4, 16  , (5 +1)* 8, 8*7)
				)
				||
				(
				(flag3==2)
				&& !pd(41 * 8 + 4, 16 - 8, (5 + 1) * 8, 8 * 4)
				&& !pd((41 + 7) * 8 + 4, 16 + 8 , 7 * 8, 8*7)
				)
				)
			{
				flag = 0;
				flag2 = 0;
				
				if (textflags != 0)
				{
					drawmain();
					printlist(hnode, &cursornode, &offset);
				}
				window(1, 1, 80, 25);
				drawmain();
			}
			if(textflags==1 && ismenu==0)
			{
			   mouse_choose(hnode,&cursornode,&offset);
			   mouse_click(hnode,&cursornode,&offset);
			}
			if(pd(0,0,24,8))
				{

					complie(hnode,&cursornode,0,0,'(',')');
					complie(hnode,&cursornode,0,0,'[',']');
					complie(hnode,&cursornode,0,0,'{','}');
					complie(hnode,&cursornode,3,0,'"','"');
					complie(hnode,&cursornode,3,0,'\'','\'');
					complie(hnode,&cursornode,5,0,'(',')');

					flag = 0;
					flag2 = 0;
					flag3 = 0;
					
				
			 	} 
			if(pd(6*8+4,0,80,8))//�����File������
				{
					flag=drawmenu(hnode,&cursornode,&offset,textflags,F1);
					flag2=100;
					flag3 = 0;
				}
			else if(pd(24*8+4,0,80,8))//�����Edit������
				{
					flag=drawmenu(hnode,&cursornode,&offset,textflags,F2);
					flag2=101;
					flag3 = 0;
				}
			else if(pd(42*8+4,0,8*13,8))//�����settings������
				{
					flag=drawmenu(hnode,&cursornode,&offset,textflags,F3);
					flag2=102;
					flag3 = 0;
				}
			else if(pd(60*8+4,0,8*14,8))//�����pattern������
				{
					flag=drawmenu(hnode,&cursornode,&offset,textflags,F4);
					flag2=103;
					flag3 = 0;
				}
			else if(flag2!=0)//flag2!=0���Ѿ�չ��һ���ڶ����˵������������ȡ��ǰ���ָ���ǰ���ٸ���֮������̲�����ͬ���ǣ����֧�ֲ����ڵ���ת��
			{
				
					switch (flag2 % 4)
					{
					case 0://File�˵��Ѿ�չ��
						for (i = 0; i < 7; i++)
						{
							if (pd(7 * 8 + 4, 16 + 8 * i, 16 * 8, 8))//��дһ������������������������˵���֮ǰ���ݲ˵�����flag��֮����ݲ˵�����ʱflag_t
							{
								flag_t = 140 + i;
								flag = menu_ud_m(flag, flag_t);
								flag3 = 0;
								switch (flag % 7)
								{
								case 0:
									hnode = InitList(hnode, &cursornode, &saveflags, &textflags);
									if (textflags != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										printlist(hnode, &cursornode, &offset);
										find_cursor(hnode,&cursornode,&offset);
									}
									flag = 0;
									flag2 = 0;
									
									break;
								case 1:
									hnode = InitList(hnode, &cursornode, &saveflags, &textflags);
									ReadFile(hnode, &cursornode, &saveflags, &textflags,path);
									flag = 0;
									flag2 = 0;
									chigh_li(hnode);
									for (i = 0; i < 6; i++)
									{
										High_li(hnode, &cursornode, color[i], i);
									}
									if (textflags != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										printlist(hnode, &cursornode, &offset);
										find_cursor(hnode,&cursornode,&offset);
									}
									break;
								case 2:
									Save(hnode, &saveflags, &textflags,path,file);
									if (textflags != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										printlist(hnode, &cursornode, &offset);
										find_cursor(hnode,&cursornode,&offset);
									}
									flag = 0;
									flag2 = 0;
									break;
								case 3:
									SaveFile(hnode, &saveflags, &textflags, path);
									if (textflags != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										printlist(hnode, &cursornode, &offset);
										find_cursor(hnode,&cursornode,&offset);
									}
									flag = 0;
									flag2 = 0;
									break;
								case 4:
									change_dir(path);
									if (textflags != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										printlist(hnode, &cursornode, &offset);
										find_cursor(hnode,&cursornode,&offset);
									}
									flag = 0;
									flag2 = 0;
									break;
								case 5:
									close(hnode, &saveflags, &textflags);
									if (textflags != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										printlist(hnode, &cursornode, &offset);
										find_cursor(hnode,&cursornode,&offset);
									}
									flag = 0;
									flag2 = 0;
									break;
								case 6:
									close(hnode, &saveflags, &textflags);
									if (textflags != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										printlist(hnode, &cursornode, &offset);
										find_cursor(hnode,&cursornode,&offset);
									}
									flag = 0;
									flag2 = 0;
									exit(0);
									break;

								}
							}
						}
						break;
					case 1://Edit�˵��Ѿ�չ��
						for (i = 0; i < 5; i++)
						{
							if (pd(25 * 8 + 4, 16 + 8 * i, 7 * 8, 8))//��дһ������������������������˵���֮ǰ���ݲ˵�����flag��֮����ݲ˵�����ʱflag_t
							{
								flag3 = 0;
								flag_t = 280 + i;
								flag = menu_ud_m(flag, flag_t);
								switch (flag % 5)
								{
								case 0:
									putclip(hnode,&clipboard);
									clrscr();
									window(1, 1, 80, 25);
									drawmain();
									if (textflags != 0)
									{
										drawmain();
										printlist(hnode, &cursornode, &offset);
										find_cursor(hnode,&cursornode,&offset);
									}
									flag = 0;
									flag2 = 0;
									break;
								case 1:
											copy(hnode,&cursornode,&clipboard);
											clrscr();
											window(1, 1, 80, 25);
											drawmain();
											if (textflags != 0)
											{
												drawmain();
												printlist(hnode, &cursornode, &offset);
												find_cursor(hnode,&cursornode,&offset);
											}
									flag = 0;
									flag2 = 0;
									break;
								case 2:
											paste(hnode,&cursornode,&clipboard);
											clrscr();
											window(1, 1, 80, 25);
											drawmain();
											if (textflags != 0)
											{
												drawmain();
												printlist(hnode, &cursornode, &offset);
												find_cursor(hnode,&cursornode,&offset);
											}
									flag = 0;
									flag2 = 0;
									break;
								case 3:
									Search(hnode,&cursornode);
									if (textflags != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										printlist(hnode, &cursornode, &offset);
										find_cursor(hnode,&cursornode,&offset);
									}
									flag = 0;
									flag2 = 0;
									break;
								case 4:
									Replace(hnode,&cursornode);
									if (textflags != 0)
									{
										window(1, 1, 80, 25);
										drawmain();
										printlist(hnode, &cursornode, &offset);
										find_cursor(hnode,&cursornode,&offset);
									}
									flag = 0;
									flag2 = 0;
									break;

								}
							}
						}
						break;

					case 2://Settings�˵��Ѿ�չ��
						for (i = 0; i < 3; i++)
						{

							if (pd(41 * 8 + 4, 16 + 8 * i, 5 * 8, 8))//��дһ������������������������˵���֮ǰ���ݲ˵�����flag��֮����ݲ˵�����ʱflag_t
							{
								flag3 = 0;
								flag_t = 420 + i;
								flag = menu_ud_m(flag, flag_t);
								switch (flag % 3)
								{
								case 0:
									
									flag3 = 1;//��ʾ�������˵�����չ��״̬������������˵�������flag3���±�Ϊ0
									//�������˵����������1�����һ����ڶ����˵����ڶ�������setting����������
									//2.����������˵��ľ���ѡ��3.�����Ļ����λ��
									drawmenu(hnode,&cursornode,&offset,textflags,1);
									break;
								case 1:
									flag3 = 2;
									drawmenu(hnode,&cursornode,&offset,textflags,2);
									break;
								case 2:
									int graphdriver = VGA;
									int graphmode = 2;
									initgraph(&graphdriver, &graphmode, "C:\\borlandc\\bgi");
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
									flag_q2 = 0;
									closegraph();
									initmouse(0);
									show_mouse();
									drawmain();
									if (textflags != 0)
									{
										drawmain();
										printlist(hnode, &cursornode, &offset);
										find_cursor(hnode,&cursornode,&offset);
									}
									flag=0;
									flag2 = 0;
									break;
								}

							}
						}
						break;

					case 3://Pattern�˵��Ѿ�չ��
						for (i = 0; i < 2; i++)
						{
							if (pd(61 * 8 + 4, 16 + 8 * i, 13 * 8, 8))//��дһ������������������������˵���֮ǰ���ݲ˵�����flag��֮����ݲ˵�����ʱflag_t
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
									if (textflags != 0)
									{
										drawmain();
										printlist(hnode, &cursornode, &offset);
										find_cursor(hnode,&cursornode,&offset);
									}
									break;
								case 1:
									flag = 0;
									flag2 = 0;
									cflag=chinese(hnode,&cursornode, h,color,textflags);//h�����ò˵�ȷ��
									show_mouse();
									window(1, 1, 80, 25);
									drawmain();
									if (textflags != 0)
									{
										drawmain();
										printlist(hnode, &cursornode, &offset);
										find_cursor(hnode,&cursornode,&offset);
									}
									switch (cflag)
									{
									case 0:
										break;
									case 1:
										cflag = 0;
										break;
									case 2:
										cflag = 0;
										break;
									case 3:
										cflag = 0;
										break;
									case 4:
										cflag = 0;
										break;
									case 5:
										cflag = 0;
										break;
									case 11:
										cflag = 0;
										break;
									case 12:
										cflag = 0;
										break;
									case 13:
										cflag = 0;
										break;
									case 14:
										cflag = 0;
										break;
									case 15:
										cflag = 0;
										break;

									}
									break;
								}
							}
						}
						break;
					}
				
				if (flag3== 1)
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

							h = i;//�ı䴫��chinese�������ַ�����hΪ�����±꣩
							ziti_set(i);

							if (textflags != 0)
							{
								drawmain();
								printlist(hnode, &cursornode, &offset);
								find_cursor(hnode,&cursornode,&offset);
							}


						}
					}
				}
				if (flag3 == 2)
				{
					for (i = 0; i < 5; i++)
					{
						if (  pd(  (41 + 7) * 8 + 4, 16 + 8 * (i + 2), 7 * 8, 8  )  )
						{

							flag = 0;
							flag2 = 0;
							flag3 = 0;
							window(1, 1, 80, 25);
							drawmain();
							color_set(i);
							color_set2(color);
							/*
							FILE * file;
							file = fopen("c:\\color", "r");
							for (ic = 0; ic < 6; ic++)
							{
								fgets(buf_c, 3, file);
								color[i] = atoi(buf_c);
							}
							fclose(file);
							*/

							for (i = 0; i < 6; i++)
							{
								High_li(hnode, &cursornode, color[i], i);
							}
							/*High_li(hnode, &cursornode,color[0], 0);//��������ɫ������
							High_li(hnode, &cursornode,color[1], 1);
							High_li(hnode, &cursornode,color[2], 2);
							High_li(hnode, &cursornode,color[3], 3);
							High_li(hnode, &cursornode,color[4], 4);
							High_li(hnode, &cursornode,color[5], 5);*/


							
							if (textflags != 0)
							{
								drawmain();
								printlist(hnode, &cursornode, &offset);
								find_cursor(hnode,&cursornode,&offset);
							}

						}
					}
				}



			}
			//ismenu = 1;
			continue;
		 }
			/*if(op==F1||op==F2||op==F3||op==F4)
			{
				flag=drawmenu(op,hnode);//���˵�
				if(op==F1) flag2=100;//��¼�˵�λ��
				if(op==F2) flag2=101;
				if(op==F3) flag2=102;
				if(op==F4) flag2=103;
			}*/
			//flag=0;
			//flag2=0;
	
			
		
		if(bioskey(1)!=0)
		{
		 
			op=bioskey(0);
			if (op==ESC)
			exit(0);
			if(op==F1||op==F2||op==F3||op==F4)
			{
				flag3 = 0;
				flag=drawmenu(hnode,&cursornode,&offset,textflags,op);//���˵�
				if(op==F1) flag2=100;//��¼�˵�λ��
				if(op==F2) flag2=101;
				if(op==F3) flag2=102;
				if(op==F4) flag2=103;
			}
			if((op==UP||op==DOWN)&&flag!=0) 
			{
				if(flag3==0)//�������˵�δչ�� 
				flag=menu_ud(op,flag);
				else if(flag3==1||flag3==2)
				flag3_1=menu_ud3(op,flag3,flag3_1);
				
			}
			if((op==LEFT||op==RIGHT)&&flag2!=0)
			{
			
				flag2=menu_lr(op,flag2,&flag,hnode,textflags,&cursornode,&offset);
				flag3=0;
			}
			if(op==ENTER&&flag2!=0) //�ṩ�ӿ�//ֻҪflag2������0��˵���Ѿ����˲˵���flag�϶�������0 
			{
				//flag2%4��λ�����꣬���˺�����֮��flag%7or5or2��λ������
				if(flag3==0)
				{
				
						switch (flag2%4) 
						{
								case 0://file�˵��£�����ĵݽ� 
									//flag3 = 0;
									switch (flag%7)
									{
										case 0:
											hnode=InitList(hnode, &cursornode, &saveflags,&textflags);
											if (textflags != 0)
											{
												window(1, 1, 80, 25);
												drawmain();
												printlist(hnode, &cursornode, &offset);
												find_cursor(hnode,&cursornode,&offset);
											}
											flag = 0;
											flag2 = 0;
											break;
										case 1:
											hnode=InitList(hnode,&cursornode, &saveflags,&textflags);
											ReadFile(hnode,&cursornode,&saveflags,&textflags,path);
											flag = 0;
											flag2 = 0;
											chigh_li( hnode);
											if (textflags != 0)
											{
												window(1, 1, 80, 25);
												drawmain();
												printlist(hnode, &cursornode, &offset);
												find_cursor(hnode,&cursornode,&offset);
											}
											break;
										case 2:
											Save(hnode, &saveflags, &textflags, path,file);
											if (textflags != 0)
											{
												window(1, 1, 80, 25);
												drawmain();
												printlist(hnode, &cursornode, &offset);
												find_cursor(hnode,&cursornode,&offset);
											}
											flag = 0;
											flag2 = 0;
											break;
										case 3:
											SaveFile(hnode, &saveflags, &textflags, path);
											if (textflags != 0)
											{
												window(1, 1, 80, 25);
												drawmain();
												printlist(hnode, &cursornode, &offset);
												find_cursor(hnode,&cursornode,&offset);
											}
											flag = 0;
											flag2 = 0;
											break;
										case 4:
											change_dir(path);
											if (textflags != 0)
											{
												window(1, 1, 80, 25);
												drawmain();
												printlist(hnode, &cursornode, &offset);
												find_cursor(hnode,&cursornode,&offset);
											}
											flag = 0;
											flag2 = 0;
											break;
										case 5:
											close(hnode, &saveflags, &textflags);
											if (textflags != 0)
											{
												window(1, 1, 80, 25);
												drawmain();
												printlist(hnode, &cursornode, &offset);
												find_cursor(hnode,&cursornode,&offset);
											}
											flag = 0;
											flag2 = 0;
											break;
										case 6:
											close(hnode, &saveflags, &textflags);
											if (textflags != 0)
											{
												window(1, 1, 80, 25);
												drawmain();
												printlist(hnode, &cursornode, &offset);
												find_cursor(hnode,&cursornode,&offset);
											}
											flag = 0;
											flag2 = 0;
											exit(0);
											break;
										
									}
									break;
									
								case 1:
									//flag3 = 0;
									switch (flag%5)
									{
										case 0:
											putclip(hnode,&clipboard);
											if (textflags != 0)
											{
												window(1, 1, 80, 25);
												drawmain();
												printlist(hnode, &cursornode, &offset);
												find_cursor(hnode,&cursornode,&offset);
											}
											flag = 0;
											flag2 = 0;
											break;
										case 1:
											copy(hnode,&cursornode,&clipboard);
											if (textflags != 0)
											{
												window(1, 1, 80, 25);
												drawmain();
												printlist(hnode, &cursornode, &offset);
												find_cursor(hnode,&cursornode,&offset);
											}
											flag = 0;
											flag2 = 0;
											break;
										case 2:
											paste(hnode,&cursornode,&clipboard);
											if (textflags != 0)
											{
												window(1, 1, 80, 25);
												drawmain();
												printlist(hnode, &cursornode, &offset);
												find_cursor(hnode,&cursornode,&offset);
											}
											flag = 0;
											flag2 = 0;
											break;
										case 3:
											Search(hnode,&cursornode);
											if (textflags != 0)
											{
												window(1, 1, 80, 25);
												drawmain();
												printlist(hnode, &cursornode, &offset);
												find_cursor(hnode,&cursornode,&offset);
											}
											flag = 0;
											flag2 = 0;
											break;
										case 4:
											Replace(hnode ,&cursornode);
											if (textflags != 0)
											{
												window(1, 1, 80, 25);
												drawmain();
												printlist(hnode, &cursornode, &offset);
												find_cursor(hnode,&cursornode,&offset);
											}
											flag = 0;
											flag2 = 0;
											break;
										
									}
									break;
								
								case 2:
									//flag3 = 0;
									switch (flag%3)
									{
										case 0:
											drawmenu(hnode,&cursornode,&offset,textflags,1);
										
											
											flag3=1;
											flag3_1=100; 
		
											break;
										case 1:
											drawmenu(hnode,&cursornode,&offset,textflags,2);
											
											
											flag3=2;
											flag3_1=100;
											
											break;
										case 2:
											initmouse(1);
											int graphdriver = VGA;
											int graphmode = 2;
											initgraph(&graphdriver, &graphmode, "C:\\borlandc\\bgi");
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
											flag_q2 = 0;
											closegraph();
											initmouse(0);
											show_mouse();
											window(1, 1, 80, 25);
											drawmain();
											if (textflags != 0)
											{
												drawmain();
												printlist(hnode, &cursornode, &offset);
												find_cursor(hnode,&cursornode,&offset);
											}


											flag = 0;
											flag2 = 0;
											break;
									}
									break;

								case 3:
									//flag3 = 0;
									switch (flag%2)
									{
										case 0:
											flag = 0;
											flag2 = 0;
											window(1, 1, 80, 25);
											drawmain();
											if (textflags != 0)
											{
												drawmain();
												printlist(hnode, &cursornode, &offset);
												find_cursor(hnode,&cursornode,&offset);
											}
											break;
										case 1:
											cflag = chinese(hnode,&cursornode,h,color,textflags);//h�����ò˵�ȷ��
											show_mouse();
											window(1, 1, 80, 25);
											drawmain();
											if (textflags != 0)
											{
												drawmain();
												printlist(hnode, &cursornode, &offset);
												find_cursor(hnode,&cursornode,&offset);
											}
											flag = 0;
											flag2 = 0;
											switch (cflag)
											{
											case 0:
												break;
											case 1:
												cflag = 0;
												break;
											case 2:
												cflag = 0;
												break;
											case 3:
												cflag = 0;
												break;
											case 4:
												cflag = 0;
												break;
											case 5:
												cflag = 0;
												break;
											case 11:
												cflag = 0;
												break;
											case 12:
												cflag = 0;
												break;
											case 13:
												cflag = 0;
												break;
											case 14:
												cflag = 0;
												break;
											case 15:
												cflag = 0;
												break;

											}
											break;
									}
									break;
						}
				}
				else if (flag3==1)
				{

					flag = 0;
					flag2 = 0;
					flag3 = 0;
					h=flag3_1%5;

					ziti_set(h);
					window(1, 1, 80, 25);
					drawmain();
					if (textflags != 0)
					{
						drawmain();
						printlist(hnode, &cursornode, &offset);
						find_cursor(hnode,&cursornode,&offset);
					}

				}
				else if(flag3==2)
				{
					flag = 0;
					flag2 = 0;
					flag3 = 0;
					drawmain();

					color_set(flag3_1);
					color_set2(color);
					window(1, 1, 80, 25);
					drawmain();
					if (textflags != 0)
					{
						drawmain();
						printlist(hnode, &cursornode, &offset);
						find_cursor(hnode,&cursornode,&offset);
					}
				}

				//flag=0;
				//flag2=0;
				ismenu=1;
			}
			if(textflags==1&&ismenu==0&&flag==0)
			{
				hnode = Add(hnode, &cursornode, op, &saveflags, color);
				printlist(hnode,&cursornode,&offset);
				choose(hnode, &cursornode, op,&offset);
				if (op == CC)
				{
					putclip(hnode, &clipboard);
					recovery(hnode);
					printlist(hnode,&cursornode,&offset);
					find_cursor(hnode, &cursornode,&offset);
				}
				if (op == CX)
				{
					copy(hnode, &cursornode, &clipboard);
					recovery(hnode);
					printlist(hnode,&cursornode,&offset);
					find_cursor(hnode,&cursornode,&offset);
				}
				if (op == CV)
				{
					paste(hnode, &cursornode, &clipboard);
					printlist(hnode,&cursornode,&offset);
					find_cursor(hnode, &cursornode,&offset);
				}
				if(op==CF)
				{
					for(int i=0;i<10;i++)
					{
						Cursormove(hnode,&cursornode,DOWN);
						printlist(hnode,&cursornode,&offset);
						find_cursor(hnode, &cursornode,&offset);
					}
				}
				if(op==CB)
				{
					for(int i=0;i<10;i++)
					{
						Cursormove(hnode,&cursornode,UP);
						printlist(hnode,&cursornode,&offset);
						find_cursor(hnode, &cursornode,&offset);
					}
				}
			}
			
        		
		}
		ismenu = 0;

	
			
			
	}
	//getch();//just for test!
}
