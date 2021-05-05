#include"high_li.h"
/*
 *@name:High_li
 *@msg:完成代码高亮的染色
 *@param:{Hnode *}hnode链表头
 *@param:{Cursornode *}cursornode光标位置
 *@param:{int}color待染颜色的标号
 *@return:{void}
*/
void High_li(Hnode* hnode,Cursornode* cursornode,int color,int flag)//仅进行颜色的设置
{
		switch(flag)
		{
			case 0://处理保留字
					static char * c[32] = { "long","short","float","double",
					"char","unsigned","signed","const","void","volatile",
					"enum","struct","union","if","else","goto","switch","case",
					"do","while","for","continue","break","return","default","typedef",
					"auto","register","extern","static","sizeof","int" };//保留字
		
					int i;
					for (i = 0; i < 32; i++)
					{
						high_li(hnode, cursornode, c[i], color);//15是bc的原色
					}
					break ;

			case 1://处理“＃”//10为bc原色
							Node* node;
							while (hnode != NULL)
							{
								node = hnode->head;
								
								while (node != NULL)
								{
									if(node->chr=='#')//如果找到，则将其后的全部染色（本行）
									{
										while (node != NULL)
										{
											node->type = color;
											node = node->next;
										}

									}
									if (node != NULL)//如果找到，跳出时node已经==NULL,不能再往下指了
									{
										node = node->next;
									}
								}
								hnode = hnode->next;
							}
			case 2://处理“//注释”
						//Node * node;
						Node* node_b;//记录前一个的位置，防止丢失，条件是连续遇到两个“/”

						while (hnode != NULL)
						{
							node_b = hnode->head;
							node = hnode->head->next;
							while (node != NULL)
							{
								if (node->chr == '/' && node_b->chr == '/')//此时满足条件，将他俩以及其后的一行全部染色
								{
									while (node != NULL)
									{
										node->type = color;
										node_b->type = color;
										node_b = node_b->next;
										node = node->next;
									}

								}
								if (node != NULL)//如果找到，跳出时node已经==NULL,不能再往下指了
								{
									node_b = node_b->next;
									node = node->next;
								}
							}
							hnode = hnode->next;
						}
							break ;
			case 3://处理/* */注释
						//node_b记录前一个的位置，防止丢失，条件是连续遇到两个“/”
						int flag_1=0;//纪录之前有没有找到“/*”

						while (hnode != NULL)
						{
							node_b = hnode->head;
							node = hnode->head->next;
							while (node != NULL)
							{
								if (flag_1 == 0)//未找到“/*”
								{
									if(node->chr == '*' && node_b->chr == '/')//此时满足条件，将他俩以及其后全部染色，直到再遇到*/
									{
										flag_1 = 1;//记录已经找到“/*”
										node_b ->type= color;//将这两个染色
										node->type = color;
									}

									if (node != NULL)//如果找到，跳出时node已经==NULL,不能再往下指了
									{
										node_b = node_b->next;
										node = node->next;
									}
								}
								else if (flag_1 == 1)//表示已经找到“/*”，正在染色，正在寻找“*/”
								{
									if(node->chr == '/' && node_b->chr == '*')//此时满足条件，染色结束，将他俩染色，然后停止染色
									{
										flag_1 = 0;//记录又未找到“/*”

											node->type = color;
											node_b->type = color;
											node_b = node_b->next;
											node = node->next;
									}
									else//未停止染色
									{
										node_b->type = color;
										node->type = color;
									}
									if (node != NULL)//如果找到，跳出时node已经==NULL,不能再往下指了
									{
										node_b = node_b->next;
										node = node->next;
									}

								}
							}
							hnode = hnode->next;
						}
						break;
			case 4://处理“”字符串//node_b记录前一个的位置，防止丢失，条件是连续遇到两个“/”
				int flag_2 = 0;//纪录之前有没有找到“/*”
				while (hnode != NULL)
				{
					node_b = hnode->head;
					while (node_b != NULL)
					{
						if (flag_2 == 0)//未找到“/*”
						{
							if (node_b->chr == '"' )//此时满足条件，将他俩以及其后全部染色，直到再遇到*/
							{
								flag_2 = 1;//记录已经找到“/*”
								node_b->type = color;//将这两个染色
							}
							if (node_b != NULL)//如果找到，跳出时node已经==NULL,不能再往下指了
							{
								node_b = node_b->next;
							}
						}
						else if (flag_2 == 1)//表示已经找到“/*”，正在染色，正在寻找“*/”
						{
							if ( node_b->chr == '"')//此时满足条件，染色结束，将他俩染色，然后停止染色
							{
								flag_2 = 0;//记录又未找到“/*”
								node_b->type = color;
								node_b = node_b->next;
							}

							else//未停止染色
							{
								node_b->type = color;
							}
							if (node_b != NULL)//如果找到，跳出时node已经==NULL,不能再往下指了
							{
								node_b = node_b->next;
							}
						}
					}
					hnode = hnode->next;
				}
				break;
			case 5://处理“”字符串//Node* node_b;//记录前一个的位置，防止丢失，条件是连续遇到两个“/”						
				int flag_3 = 0;//纪录之前有没有找到“/*”
				while (hnode != NULL)
				{
					node_b = hnode->head;
					while (node_b != NULL)
					{
						if (flag_3 == 0)//未找到“/*”
						{
							if (node_b->chr == '\'')//此时满足条件，将他俩以及其后全部染色，直到再遇到*/
							{
								flag_3 = 1;//记录已经找到“/*”
								node_b->type = color;//将这两个染色
							}
							if (node_b != NULL)//如果找到，跳出时node已经==NULL,不能再往下指了
							{
								node_b = node_b->next;
							}
						}
						else if (flag_3 == 1)//表示已经找到“/*”，正在染色，正在寻找“*/”
						{
							if (node_b->chr == '\'')//此时满足条件，染色结束，将他俩染色，然后停止染色
							{
								flag_3 = 0;//记录又未找到“/*”
								node_b->type = color;
								node_b = node_b->next;
							}

							else//未停止染色
							{
								node_b->type = color;
							}
							if (node_b != NULL)//如果找到，跳出时node已经==NULL,不能再往下指了
							{
								node_b = node_b->next;
							}

						}
					}
					hnode = hnode->next;
				}
				break;
		}
}
/*
 *@name:high_li
 *@msg:完成对保留字的染色，并兼顾模拟编译中对main函数的查找
 *@param:{Hnode *}hnode 链表头
 *@param:{Cursornode *}cursornode 光标位置
 *@param:{char *} 专用于传入"main"
 *@return:{int} flag2 表明是否找到main
*/
int high_li(Hnode *hnode, Cursornode *cursornode, char str[], int color)//15是bc的原色//返回值用于判断有没有main函数
{

	int flag1 = 0;
	int flag2 = 0;
	if(strcmp("main",str)==0)//如果flag1=1就跳过染色，在编译时使用
	{
		flag1 = 1;
	}
	char* s;//用来储存一行的字符
	
	char* p;
	char* p_t;  //指向查找首地址，可以一行查多个
	char* p2;//用于查找保留字后是否有特定字符
	int n1;
	int i = 0;//负责遍历
	int j;
	int flag = 0;
	Node* node;
	Cursornode cursornode_t = *cursornode;
	Cursornode cursornode_temp;//用于保留字检查
	cursornode->nowhnode = hnode;//这里改变了光标位置，所以需要先保留下来//这里改为从头遍历
	while (cursornode->nowhnode != NULL)
	{
		cursornode->nownode = cursornode->nowhnode->head;//从第一个开始遍历
		s = (char*)malloc(1 +  cursornode->nowhnode->cols);//1用来存放'\0'
		node = cursornode->nowhnode->head;
		i = 0;
		while (node != NULL)
		{
			s[i] = node->chr;
			node = node-> next;
			i++;
		}
		s[i] = '\0';
		p_t = s;
		while ((p = strstr(p_t, str)) != NULL)
		{
				n1 = p - s;//偏移量

				cursornode->nownode = cursornode->nowhnode->head;
				for (i = 0; i < n1 - 1; i++)//n>=1时cursornode指向为待替换的保留字的前一个
				{
					cursornode->nownode = cursornode->nownode->next;//光标移动至待替换位置开头
				}//之后需再步进一格//需要先判断满足条件再替换	
				if (n1 == 0 ||
					(
						!(
							((cursornode->nownode->chr) >= '0' && (cursornode->nownode->chr) <= '9') ||
							((cursornode->nownode->chr) >= 'A' && (cursornode->nownode->chr) <= 'Z') ||
							((cursornode->nownode->chr) >= 'a' && (cursornode->nownode->chr) <= 'z') ||
							((cursornode->nownode->chr) == '_')
							)
						)
					)
				{
					flag++;//保留字之前的字符条件满足了
				}
				if (flag == 1)
				{
					cursornode_temp = *cursornode;
					if (n1 == 0)
						j = 0;
					else
						j = 1;
					for (i = 0; i < (strlen(str) + j); i++)
					{
						cursornode->nownode = cursornode->nownode->next;
					}
					if (cursornode->nownode == NULL || (!(((cursornode->nownode->chr) >= '0' && (cursornode->nownode->chr) <= '9') || ((cursornode->nownode->chr) >= 'A' && (cursornode->nownode->chr) <= 'Z') || ((cursornode->nownode->chr) >= 'a' && (cursornode->nownode->chr) <= 'z') || ((cursornode->nownode->chr) == '_'))))
						flag++;
					*cursornode = cursornode_temp;
				}
				if (n1 != 0)
					cursornode->nownode = cursornode->nownode->next;//之前的补回来
				if (flag == 2)//满足保留字染色条件
				{
					if (flag1 != 0)//有main
						flag2 = 1;
					for (i = 0; i < strlen(str); i++)
					{
						p++;
						if (flag1 == 0)//不是main 染色
						{
							cursornode->nownode->type = color;
						}
						cursornode->nownode = cursornode->nownode->next;//颜色逐个替换

					}
					p_t = p;
				}
				else
					p_t = p + strlen(str);
				flag = 0;	
		}
		free(s);//释放内存
		cursornode->nowhnode = cursornode->nowhnode->next;
	}
	*cursornode = cursornode_t;//保留之前的光标位置
	return flag2;
}
		
			
	

	
/*
 *@name:color_set
 *@msg:完成对文件中颜色配置的写入
 *@param:{int}颜色组号
 *@return:{void}
*/
void color_set(int flag)//, int* pcolor)
{
	int i;
	FILE * file;
	file = fopen("c:\\color", "w");
	switch (flag)
	{
	case 0://关闭高亮
		for (i = 0; i < 6; i++)
		{
			fputs("2\n", file);//#8紫 9绿 7偏棕 6偏灰 比较正常 5红 4粉红 3红 2偏浅蓝 正常 1僵尸绿 0不能显示
		}
		break;
	case 1:
		fputs("3\n", file);
		fputs("4\n", file);
		fputs("5\n", file);
		fputs("6\n", file);
		fputs("7\n", file);
		fputs("5\n", file);
		break;
	case 2:
		fputs("9\n", file);
		fputs("2\n", file);
		fputs("3\n", file);
		fputs("4\n", file);
		fputs("5\n", file);
		fputs("6\n", file);
		break;
	case 3:

		fputs("3\n", file);
		fputs("2\n", file);
		fputs("9\n", file);
		fputs("2\n", file);
		fputs("7\n", file);
		fputs("6\n", file);
		break;
	case 4:

		fputs("1\n", file);
		fputs("3\n", file);
		fputs("2\n", file);
		fputs("4\n", file);
		fputs("5\n", file);
		fputs("6\n", file);
		break;

	}
	fclose(file);
}
/*
 *@name:color_set2
 *@msg:从文件中读取颜色配置将其写入数组，再由High_li染色
 *@param:{int *}pcolor 记录颜色的数组
 *@return:{void}
*/
void color_set2(int *pcolor)
{
	int ic;
	char buf_c[3];
	FILE * file;
	file = fopen("c:\\color", "r");
	for (ic = 0; ic < 6; ic++)
	{
		fgets(buf_c, 3, file);
		pcolor[ic] = atoi(buf_c);
	}
	fclose(file);
}
/*
 *@name:chigh_li
 *@msg:刷新高亮
 *@param:{Hnode  *}hnode 链表头
 *@return:{void}
*/
void chigh_li(Hnode* hnode)//刷新高亮
{
		Node* node;
		while (hnode != NULL)
		{
			node = hnode->head;
			while (node != NULL)
			{
				node->type = Judgetype(node->chr);
				node = node->next;
			}
			hnode = hnode->next;
		}
}
