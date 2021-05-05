#include"menu.h"
#include"key.h"
#include"mouse.h"
#include"define.h"
#include"edit.h"
/*
 *@name:drawmain
 *@msg:��������̨��������
 *@param:{void}
 *@return:{void}
*/
void drawmain()//��������
{
	int i;
	hide_mouse();
	window(1, 1, 80, 25);
	textbackground(BLUE);
	clrscr(); //����ɫ�ı��༭��
	textcolor(WHITE); //������ɫ�ı��༭���ı߿���ɫ

	for (i = 2; i < 24; i++) //����ɫ�ı��༭����߿�
	{
		gotoxy(1, i + 1);
		cprintf("%c", 186);
	}
	for (i = 2; i < 24; i++)
	{
		gotoxy(80, i + 1);
		cprintf("%c", 186);
	}
	gotoxy(1, 2);//����ɫ�ı��༭���ϱ߿�
	for (i = 0; i < 79; i++)
	{
		cprintf("%c", 205);
	}

	gotoxy(1, 24); //��ɫ�ı��༭���±߿�
	for (i = 0; i < 79; i++)
		cprintf("%c", 205);

	gotoxy(1, 2); //����ɫ�ı��༭�����ϽǱ߿�
	cprintf("%c", 201);
	gotoxy(80, 2);
	cprintf("%c", 187);

	gotoxy(1, 24); //����ɫ�ı��༭�����½Ǳ߿�
	cprintf("%c", 200);
	gotoxy(80, 24);
	cprintf("%c", 188);

	textcolor(BLACK); //�������˵�������ɫ
	textbackground(7);// �������˵�������ɫ

	gotoxy(1, 1); //�����˵�

	textcolor(RED);
	cprintf("R");
	textcolor(BLACK);
	cprintf("un");

	for (i = 0; i < 4; i++)
		cprintf(" ");//����Ϊ7

	cprintf("[");
	textcolor(RED);
	cprintf("F");
	textcolor(BLACK);
	cprintf("ile(F1)]");//����Ϊ10

	for (i = 0; i < 7; i++)//����Ϊ7
		cprintf(" ");

	cprintf("[");
	textcolor(RED);
	cprintf("E");
	textcolor(BLACK);
	cprintf("dit(F2)]");//����Ϊ10

	for (i = 0; i < 7; i++)//����Ϊ7
		cprintf(" ");

	cprintf("[");
	textcolor(RED);
	cprintf("S");
	textcolor(BLACK);
	cprintf("ettings(F3)]");//����Ϊ14

	for (i = 0; i < 6; i++)//����Ϊ6
		cprintf(" ");
	cprintf("[");
	textcolor(RED);
	cprintf("P");
	textcolor(BLACK);
	cprintf("attern(F4)]");//����Ϊ 13

	for (i = 0; i < 6; i++)//����Ϊ6
		cprintf(" ");

	gotoxy(1, 25);//�����м���
	insline();
	cprintf("     Row:   Col:");
	
	gotoxy(80, 25);
	show_mouse();
}
/*
 *@name:drawmenu
 *@msg:��������̨�²˵�
 *@param:{Hnode *}hnode����ͷ
 *@param:{Cursornode *}cursornode���λ��
 *@param:{Offset *}offset����ƫ����
 *@param��{int}textflags��ǰ�����������ı�
 *@param:{int}op��ѭ���а��µİ���ɨ����
 *@return:{int}�ı���ѭ���в˵����Ʊ�������ʾ�˵�λ���ƶ�
*/
int drawmenu(Hnode *hnode,Cursornode *cursornode ,Offset *offset,int textflags,int op)//���Ӳ˵���֮��Ҫ��Ҫ�Ӵ滺������������ƶ���
//����ֵΪflag �������¼��������ı���ѭ�����flag2���������ҹ��� 
{
	drawmain();//���֮ǰ�����Ӳ˵����ı���ʾ֮����˵���ٽ��и���
	if(textflags!=0)
	Printlist(hnode,cursornode,offset);
	window(1, 1, 80, 25);
	hide_mouse();
	int i;
	char * f[] = {
	"ew",
	"pen",
	"ave",
	"ave as",
	"hange directory",
	"lose",
	"uit" };
	char *f1[] = {
		"N",
		"O",
		"S",
		"S",
		"C",
		"C",
		"Q"
	};
	char * e[] = {
	"opy",
	"ut",
	"aste",
	"earch",
	"eplace" };
	char * e1[] = {
	"C",
	"C",
	"P",
	"S",
	"R" };
	char * s[] = {
	"ont",
	"olor",
	"elp"};
	char * s1[] = {
	"F",
	"C",
	"H" };
	char * p[] = {
	"nglish/Edit",
	"hinese/order" };
	char * p1[] = {
	"E",
	"C" };
	char* co[] = {
		"olor_c",
		"olor_1",
		"olor_2",
		"olor_3",
		"olor_4"};
	char* co1[] = {
		"C",
		"C",
		"C",
		"C",
		"C"};
	char* hz[] = {
		"UIF",
		"AT",
		"OU",
		"IE",
		"HUF"};
	char* hz1[] = {
		"G",
		"K",
		"Y",
		"X",
		"S" };
	textbackground(0);//��ѡ�еĹ���ڱ��� 
	textcolor(15);//��ѡ�еĹ�������� 
	
	
	show_mouse();
	
	switch (op)
	{
	case 1:
		hide_mouse();

		drawmenu(hnode,cursornode,offset,textflags,F3);
		window(1, 1, 80, 25);
		textcolor(BLACK); //�����Ӳ˵�������ɫ
		textbackground(7);// �����Ӳ˵�������ɫ
		box(49, 3, 6, 6);

		textbackground(0);//��ѡ�еĹ���ڱ���
		textcolor(15);//��ѡ�еĹ��������
		gotoxy(50, 4);
		cprintf("%s", hz1[0]);
		cprintf("%s", hz[0]);

		textcolor(BLACK); //�����Ӳ˵�������ɫ
		textbackground(7);// �����Ӳ˵�������ɫ
		for (i = 4; i < 4+4; i++)
		{
			gotoxy(50, i+1);
			textcolor(RED);
			cprintf("%s", hz1[i - 3]);
			textcolor(BLACK);
			cprintf("%s", hz[i - 3]);
		}
		if (textflags != 0)
			Find_cursor(hnode, cursornode, offset);
		else
			gotoxy(80, 25);
		show_mouse();
		return 1;
	case 2:
		hide_mouse();

		//drawmenu(hnode, cursornode, offset, textflags, F3);
		window(1, 1, 80, 25);
		gotoxy(42, 1);
		cprintf("[Settings(F3)]");//�Ӻ�
		
		//box(49, 3, 6, 6);
		textcolor(BLACK); //�����Ӳ˵�������ɫ
		textbackground(7);// �����Ӳ˵�������ɫ
		box(42, 2, 4, 6);

		textcolor(BLACK); //�����Ӳ˵�������ɫ
		textbackground(7);// �����Ӳ˵�������ɫ
		for (i = 3; i < 6; i++)
		{
			gotoxy(43, i);
			
			textcolor(RED);
			cprintf("%s", s1[i - 3]);
			textcolor(BLACK);
			cprintf("%s", s[i - 3]);
		}


		textbackground(0);//��ѡ�еĹ���ڱ���
		textcolor(15);//��ѡ�еĹ��������
		gotoxy(43, 4);
		cprintf("%s", s1[1]);
		cprintf("%s", s[1]);

		//����Ϊ�������˵�
		textcolor(BLACK); //�����Ӳ˵�������ɫ
		textbackground(7);// �����Ӳ˵�������ɫ
		box(49, 4, 6, 8);
		
		textbackground(0);//��ѡ�еĹ���ڱ��� 
		textcolor(15);//��ѡ�еĹ�������� 
		gotoxy(50, 5);
		cprintf("%s", co1[0]);
		cprintf("%s", co[0]);

		textcolor(BLACK); //�����Ӳ˵�������ɫ
		textbackground(7);// �����Ӳ˵�������ɫ
		for (i = 4; i < 5+3; i++)
		{

			gotoxy(50, i+2);
			textcolor(RED);
			cprintf("%s", co1[i - 3]);
			textcolor(BLACK);
			cprintf("%s", co[i - 3]);
		}
		if(textflags!=0)
		Find_cursor(hnode, cursornode, offset);
		else
			gotoxy(80, 25);
		show_mouse();
		return 2;

	case F1:
		hide_mouse();
		gotoxy(8, 1);
		cprintf("[File(F1)]");//�Ӻ�

		textcolor(BLACK); //�����Ӳ˵�������ɫ,���Ǹ�ú�bc��һ����� 
		textbackground(7);// �����Ӳ˵�������ɫ
		box(8, 2, 8, 17);

		textbackground(0);//��ѡ�еĹ���ڱ��� 
		textcolor(15);//��ѡ�еĹ�������� 
		gotoxy(9, 3);
		cprintf("%s", f1[0]);
		cprintf("%s", f[0]);

		textcolor(BLACK); //�����Ӳ˵�������ɫ,���Ǹ�ú�bc��һ����� 
		textbackground(7);// �����Ӳ˵�������ɫ
		for (i = 4; i < 10; i++)
		{
			gotoxy(9, i);
			textcolor(RED);
			cprintf("%s", f1[i - 3]);
			textcolor(BLACK);
			cprintf("%s", f[i - 3]);
		}
		if(textflags!=0)
		Find_cursor(hnode, cursornode, offset);
		else
			gotoxy(80, 25);
		show_mouse();
		return 140;
	case F2:
		hide_mouse();
		gotoxy(25, 1);
		cprintf("[Edit(F2)]");//�Ӻ�


		textcolor(BLACK); //�����Ӳ˵�������ɫ
		textbackground(7);// �����Ӳ˵�������ɫ
		box(25, 2, 6, 8);

		textbackground(0);//��ѡ�еĹ���ڱ��� 
		textcolor(15);//��ѡ�еĹ�������� 
		gotoxy(26, 3);
		cprintf("%s", e1[0]);
		cprintf("%s", e[0]);

		textcolor(BLACK); //�����Ӳ˵�������ɫ
		textbackground(7);// �����Ӳ˵�������ɫ
		for (i = 4; i < 8; i++)
		{
			gotoxy(26, i);
			textcolor(RED);
			cprintf("%s", e1[i - 3]);
			textcolor(BLACK);
			cprintf("%s", e[i - 3]);
		}
		if(textflags!=0)
		Find_cursor(hnode, cursornode, offset);
		else
			gotoxy(80, 25);
		show_mouse();
		return 280;
	case F3:
		hide_mouse();
		gotoxy(42, 1);
		cprintf("[Settings(F3)]");//�Ӻ�


		textcolor(BLACK); //�����Ӳ˵�������ɫ
		textbackground(7);// �����Ӳ˵�������ɫ
		box(42, 2, 4, 6);

		textbackground(0);//��ѡ�еĹ���ڱ��� 
		textcolor(15);//��ѡ�еĹ�������� 
		gotoxy(43, 3);
		cprintf("%s", s1[0]);
		cprintf("%s", s[0]);

		textcolor(BLACK); //�����Ӳ˵�������ɫ
		textbackground(7);// �����Ӳ˵�������ɫ
		for (i = 4; i < 6; i++)
		{
			gotoxy(43, i);
			textcolor(RED);
			cprintf("%s", s1[i - 3]);
			textcolor(BLACK);
			cprintf("%s", s[i - 3]);
		}
		if(textflags!=0)
		Find_cursor(hnode, cursornode, offset);
		else
			gotoxy(80, 25);
		show_mouse();
		return 420;
	case F4:
		hide_mouse();
		gotoxy(62, 1);
		cprintf("[pattern(F4)]");//�Ӻ�


		textcolor(BLACK); //�����Ӳ˵�������ɫ
		textbackground(7);// �����Ӳ˵�������ɫ
		box(62, 2, 3, 14);

		textbackground(0);//��ѡ�еĹ���ڱ��� 
		textcolor(15);//��ѡ�еĹ�������� 
		gotoxy(63, 3);
		cprintf("%s", p1[0]);
		cprintf("%s", p[0]);

		textcolor(BLACK); //�����Ӳ˵�������ɫ
		textbackground(7);// �����Ӳ˵�������ɫ
		for (i = 4; i < 5; i++)
		{
			gotoxy(63, i);
			textcolor(RED);
			cprintf("%s", p1[i - 3]);
			textcolor(BLACK);
			cprintf("%s", p[i - 3]);
		}
		if(textflags!=0)
		{
			Find_cursor(hnode, cursornode, offset);
		}
		else
			gotoxy(80, 25);
		show_mouse();
		return 560;
	
	}
	return 0;
    
}
/*
 *@name:box
 *@msg:��������̨�·����Լ��ٴ�����
 *@param:{int}x���ϽǺ�����
 *@param:{int}y���Ͻ�������
 *@param:{int}h�߶�
 *@param;{int}w���
 *@return:{void}
*/
void box(int x, int y, int h, int w) //�������Ӳ˵��߿�
{
	hide_mouse();
	int i, j;
	gotoxy(x, y);
	for (i = 0; i < h; i++)
	{
		gotoxy(x, y + i);
		for (j = 0; j < w; j++)
			cprintf(" ");
	}
	gotoxy(x, y);
	putch(169);
	for (i = x + 1; i < x + w; i++)
	{
		putch(0xc4);
	}
	putch(0xbf);
	for (i = y + 1; i < y + h; i++)
	{
		gotoxy(x, i);
		putch(0xb3);
		gotoxy(x + w, i);
		putch(0xb3);
	}
	gotoxy(x, y + h);
	putch(0xc0);
	for (i = x + 1; i < x + w; i++)
	{
		putch(0xc4);
	}
	putch(0xd9);
	gotoxy(80, 25);
	show_mouse();
}
/*
 *@name:menu_lr
 *@msg:ͨ����Ӧ����ֵ���Ʋ˵������ƶ�
 *@param:{int}op����ɨ����
 *@param:{int}flag_2��¼�˵�λ�õı�־
 *@param:{Hnode *}hnode ����ͷ�ڵ�
 *@param:{int}textflags ��ǰ�����������ı��ı�ʶ
 *@param;{Cursornode *}���λ��
 *@param;{Offset *}����ƫ����
 *@return:{int}flag_2��¼�˵�λ�õı�ʶ
*/
int menu_lr(int op, int flag2, int * pflag,Hnode *hnode,int textflags,Cursornode *cursornode,Offset *offset)//��menu_ud����
{
	if (op == LEFT)
		flag2--;
	else if (op == RIGHT)
		flag2++;

	if (flag2 % 4 == 0)
		*pflag =drawmenu(hnode,cursornode,offset,textflags,F1);
	else if (flag2 % 4 == 1)
		*pflag =drawmenu(hnode,cursornode,offset,textflags,F2);
	else if (flag2 % 4 == 2)
		*pflag =drawmenu(hnode,cursornode,offset,textflags,F3);
	else if (flag2 % 4 == 3)
		*pflag =drawmenu(hnode,cursornode,offset,textflags,F4);
	return flag2;
}
/*
 *@name:menu_ud3
 *@msg:ͨ����Ӧ����ֵ���Ƶ������˵������ƶ�
 *@param:{int}op����ɨ����
 *@param:{int}flag_3��¼�˵�λ�õı�־
 *@param:{int}flag3_1��¼�������˵�λ�õı�־
 *@param:{Hnode *}hnode ����ͷ�ڵ�
 *@param;{Cursornode *}���λ��
 *@param;{Offset *}����ƫ����
 *@param:{int} textflags �Ƿ���ı��ı�־
 *@return:{int}flag3_1��¼�������˵�λ�õı�־
*/
int menu_ud3(int op,int flag3,int flag3_1,Hnode *hnode,Cursornode *cursornode,Offset *offset,int textflag)
{
	hide_mouse();
	
	char* c[] = {
		"olor_c",
		"olor_1",
		"olor_2",
		"olor_3",
		"olor_4" };
	char* c1[] = {
		"C",
		"C",
		"C",
		"C",
		"C" };
	char* s[] = {
		"UIF",
		"AT",
		"OU",
		"IE",
		"HUF" };
	char* s1[] = {
		"G",
		"K",
		"Y",
		"X",
		"S" };
	textcolor(BLACK); //�����Ӳ˵�������ɫ
	textbackground(7);// �����Ӳ˵�������ɫ
	if(flag3==1)
	{
		gotoxy(50, flag3_1 % 5 + 4);//flag%5  ԭλ��
		textcolor(RED);
		cprintf("%s", s1[flag3_1 % 5]);
		textcolor(BLACK);
		cprintf("%s", s[flag3_1 % 5]);

		if (op == DOWN)
			flag3_1++;
		else if (op == UP)
			flag3_1--;

		textbackground(0);//��ѡ�еĹ���ڱ���
		textcolor(15);//��ѡ�еĹ��������
		gotoxy(50, flag3_1 % 5 + 4);//flag%5  �ı�֮���λ��
		
		cprintf("%s", s1[flag3_1 % 5]);
		cprintf("%s", s[flag3_1 % 5]);
	}

	else if(flag3==2)
	{
		gotoxy(50, flag3_1 % 5 + 5);//flag%5  ԭλ��
		textcolor(RED);
		cprintf("%s", c1[flag3_1 % 5]);
		textcolor(BLACK);
		cprintf("%s", c[flag3_1 % 5]);

		if (op == DOWN)
			flag3_1++;
		else if (op == UP)
			flag3_1--;

		textbackground(0);//��ѡ�еĹ���ڱ���
		textcolor(15);//��ѡ�еĹ��������
		gotoxy(50, flag3_1 % 5 + 5);//flag%5  �ı�֮���λ��
	
		cprintf("%s", c1[flag3_1 % 5]);
		cprintf("%s", c[flag3_1 % 5]);
	}
	show_mouse();
	if(textflag!=0)
	Find_cursor(hnode, cursornode, offset);
	else
		gotoxy(80, 25);
	return flag3_1;
}
/*
 *@name:menu_ud
 *@msg:ͨ�����°������Ʋ˵������ƶ����������
 *@param:{int}op��ѭ���а��µİ���ֵ
 *@param:{int}flag�Ӳ˵�����ѡ�����Ҫ���Ӳ˵��ĵڼ���
 *@return:{int}flag �����ƶ���ɺ�˵�λ�ã�������ѭ��
*/
int menu_ud(int op, int flag,Hnode *hnode,Cursornode *cursornode,Offset *offset,int textflag)//�Ӳ˵�����ѡ���������0123...,flag�����൱���������ӣ���ӦDOWN
{
	hide_mouse();
	char * f[] = {
	"ew",
	"pen",
	"ave",
	"ave as",
	"hange directory",
	"lose",
	"uit" };
	char * f1[] = {
	"N",
	"O",
	"S",
	"S",
	"C",
	"C",
	"Q" };
	char * e[] = {
	"opy",
	"ut",
	"aste",
	"earch",
	"eplace" };
	char * e1[] = {
	"C",
	"C",
	"P",
	"S",
	"R" };
	char * s[] = {
	"ont",
	"olor",
	"elp"};
	char * s1[] = {
	"F",
	"C",
	"H" };
	char * p[] = {
	"nglish/Edit",
	"hinese/order" };
	char * p1[] = {
	"E",
	"C" };
	textcolor(BLACK); //�����Ӳ˵�������ɫ
	textbackground(7);// �����Ӳ˵�������ɫ
	if (flag > 70 && flag < 210)//��file�Ӳ˵���
	{
		gotoxy(9, flag % 7 + 3);//flag%7  ԭλ��
		textcolor(RED);
		cprintf("%s", f1[flag % 7]);
		textcolor(BLACK);
		cprintf("%s", f[flag % 7]);

		if (op == DOWN)
			flag++;
		else if (op == UP)
			flag--;

		textbackground(0);//��ѡ�еĹ���ڱ���
		textcolor(15);//��ѡ�еĹ��������
		gotoxy(9, flag % 7 + 3);//flag%7  �ı�֮���λ��
	
		cprintf("%s", f1[flag % 7]);
		cprintf("%s", f[flag % 7]);
	}
	else if (flag > 210 && flag < 350)//��edit�Ӳ˵���
	{
		gotoxy(26, flag % 5 + 3);//flag%5  ԭλ��
		textcolor(RED);
		cprintf("%s", e1[flag % 5]);
		textcolor(BLACK);
		cprintf("%s", e[flag % 5]);

		if (op == DOWN)
			flag++;
		else if (op == UP)
			flag--;

		textbackground(0);//��ѡ�еĹ���ڱ���
		textcolor(15);//��ѡ�еĹ��������
		gotoxy(26, flag % 5 + 3);//flag%5  �ı�֮���λ��
		cprintf("%s", e1[flag % 5]);
		cprintf("%s", e[flag % 5]);

	}
	else if (flag > 350 && flag < 490)//��settings�Ӳ˵���
	{
		gotoxy(43, flag % 3 + 3);//flag%2  ԭλ��
		textcolor(RED);
		cprintf("%s", s1[flag % 3]);
		textcolor(BLACK);
		cprintf("%s", s[flag % 3]);

		if (op == DOWN)
			flag++;
		else if (op == UP)
			flag--;

		textbackground(0);//��ѡ�еĹ���ڱ���
		textcolor(15);//��ѡ�еĹ��������
		gotoxy(43, flag % 3 + 3);//flag%2 �ı�֮���λ��
		cprintf("%s", s1[flag % 3]);
		cprintf("%s", s[flag % 3]);
	}
	else if (flag > 490)//��patterns�Ӳ˵���
	{
		gotoxy(63, flag % 2 + 3);//flag%2  ԭλ��
		textcolor(RED);
		cprintf("%s", p1[flag % 2]);
		textcolor(BLACK);
		cprintf("%s", p[flag % 2]);

		if (op == DOWN)
			flag++;
		else if (op == UP)
			flag--;

		textbackground(0);//��ѡ�еĹ���ڱ���
		textcolor(15);//��ѡ�еĹ��������
		gotoxy(63, flag % 2 + 3);//flag%2 �ı�֮���λ��
		cprintf("%s", p1[flag % 2]);
		cprintf("%s", p[flag % 2]);
	}
	if(textflag!=0)
		Find_cursor(hnode, cursornode, offset);
	else
		gotoxy(80, 25);
	show_mouse();
	return flag;
}
/*
 *@name:menu_ud_m
 *@msg:ͨ���������Ӳ˵����µ�ѡ��
 *@param:{int}flag��¼ѡ�����Ӳ˵�
 *@param:{int}flag_t��¼ѡ��ǰ���Ӳ˵�
 *@return:{int}flag_t��¼ѡ�����Ӳ˵�������ѭ��
*/
int menu_ud_m(int flag,int flag_t)
{
	hide_mouse();
	char * f[]={
	"New",
	"Open",
	"Save",
	"Save as",
	"Change directory",
	"Close",
	"Quit"};
	char * e[]={
	"Copy",
	"Cut",
	"Paste",
	"Search",
	"Replace"};
	char * s[]={
	"Font",
	"Color",
	"Help"};
	char * p[]={
	"English/Edit",
	"Chinese/order"};
	textcolor(BLACK); //�����Ӳ˵�������ɫ
	textbackground(7);// �����Ӳ˵�������ɫ
	if(flag>70&&flag<210)//��file�Ӳ˵���
	{
		gotoxy(9,flag%7+3);//flag%7  ԭλ��
		cprintf("%s",f[flag%7]);
				
				
		textbackground(0);//��ѡ�еĹ���ڱ���
		textcolor(15);//��ѡ�еĹ��������
		gotoxy(9,flag_t%7+3);//flag_t%7  �ı�֮���λ��
		cprintf("%s",f[flag_t%7]);
	}
	else if(flag>210&&flag<350)//��edit�Ӳ˵���
	{
		gotoxy(26,flag%5+3);//flag%5  ԭλ��
		cprintf("%s",e[flag%5]);
		
		
		textbackground(0);//��ѡ�еĹ���ڱ���
		textcolor(15);//��ѡ�еĹ��������
		gotoxy(26,flag_t%5+3);//flag_t%5  �ı�֮���λ��
		cprintf("%s",e[flag_t%5]);
		
	}
	else if(flag>350&&flag<490)//��settings�Ӳ˵���
	{
		gotoxy(43,flag%2+3);//flag%2  ԭλ��
		cprintf("%s",s[flag%2]);
		
		
		textbackground(0);//��ѡ�еĹ���ڱ���
		textcolor(15);//��ѡ�еĹ��������
		gotoxy(43,flag_t%2+3);//flag_t%2 �ı�֮���λ��
		cprintf("%s",s[flag_t%2]);
	}
	else if(flag>490)//��patterns�Ӳ˵���
	{
		gotoxy(63,flag%2+3);//flag%2  ԭλ��
		cprintf("%s",p[flag%2]);
		
			
		textbackground(0);//��ѡ�еĹ���ڱ���
		textcolor(15);//��ѡ�еĹ��������
		gotoxy(63,flag_t%2+3);//flag_t%2 �ı�֮���λ��
		cprintf("%s",p[flag_t%2]);
	}
	
	gotoxy(80, 25);
	show_mouse();
	return flag_t;
} 

