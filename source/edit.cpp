#include"function.h"
#include"edit.h"
#include"key.h"
#include"code.h"
#include"code.h"
#include"high_li.h"
#define TAB 0x0F09
//key涓篵ioskey()寰楀埌鐨勯敭鍊?
Hnode* Add(Hnode* hnode, Cursornode* cursornode, int key, int* saveflags, int* pcolor)
{
	char ch = (char)(key & 0x00ff); //鍙朅SCII鐮?
	if(key==TAB)
	{
		for(int i=0;i<4;i++)
		{
			AddNode(cursornode,' ');
		}
	}
	if (key==LEFT || key==RIGHT || key==UP || key==DOWN)
	{
		Cursormove(hnode, cursornode, key);  //绉诲姩鍏夋爣鑺傜偣
	}
	else if (ch>=32&&ch<=127&&ch != '\n'&&ch != '\r'&&ch != 8)
	{
		if (ch == '{')
			code(hnode, cursornode, 0);

		else if (ch == '(')
			code(hnode, cursornode, 2);
		else if (ch == '[')
			code(hnode, cursornode, 3);
		else
			AddNode(cursornode, ch);  //娣诲姞鑺傜偣
		*saveflags=0;

	}
	else if(ch==8)
	{
		DeleteNode(hnode, cursornode);  //鍒犻櫎鑺傜偣
		*saveflags=0;
	}
	else if(ch=='\n'||ch=='\r')
	{
								 //娣诲姞琛岃妭鐐?
		//hnode=AddHnode(cursornode, hnode);

		code(hnode, cursornode,  1);
		*saveflags=0;
	}
	chigh_li(hnode);//刷新高亮
	
	High_li(hnode, cursornode,pcolor[0], 0);//仅进行颜色的设置
	High_li(hnode, cursornode,pcolor[1], 1);
	High_li(hnode, cursornode,pcolor[2], 2);
	High_li(hnode, cursornode,pcolor[3], 3);
	High_li(hnode, cursornode,pcolor[4], 4);
	High_li(hnode, cursornode,pcolor[5], 5);
	return hnode;
}
