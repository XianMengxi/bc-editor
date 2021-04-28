#ifndef FUNCTION_H
#define FUNCTION_H
#pragma once
#include"define.h"
Hnode* InitList(Hnode *hnode, Cursornode *cursornode, int *saveflags,int *textflags); //��ʼ������
int Judgetype(unsigned short ch); //�ж��ַ�����
void AddNode(Cursornode *cursornode, unsigned short ch); //��ӽڵ�
Hnode *AddHnode(Cursornode *cursornode, Hnode*hnode_head);  //����нڵ�
//��������е�����
void ClearLists(Hnode *Hhead);
void printlist(Hnode *hnode);  //��ӡ����
//ֱ��ɾ��ͷ�ڵ㼰��������
Hnode * DeleteHnode(Hnode *hnode, Cursornode *cursornode);
//ɾ���ڵ�
void DeleteNode(Hnode *hnode, Cursornode *cursornode);
void find_location(Hnode *hnode, Cursornode *cursornode, int x, int y);  //��λ����������
void Cursormove(Hnode *hnode, Cursornode *cursornode, int direction); //�����λ�ý������������ƶ�
//��ȡ�ļ�
int ReadFile(Hnode *hnode, Cursornode *cursornode,int *saveflags,int *textflags,char *path);
//�����ļ�
int SaveFile(Hnode *hnode,int *saveflags,int *textflags,char *path);
void Save(Hnode *hnode,int *saveflags,int *textflags,char *path,char *file);
void change_dir(char *path);
//���ҹ��λ��
void find_cursor(Hnode *hnode ,Cursornode *cursornode);
void search(Hnode *hnode,Cursornode *cursornode,char *str1,char *str2,int flags,int color);
Hnode* close(Hnode *hnode,int *saveflags,int *textflags);
void readhnode(Hnode *hnode, char str[]);
void Search(Hnode *hnode,Cursornode *cursornode);
void Replace(Hnode *hnode ,Cursornode *cursornode);
void printlist(Hnode *hnode,Cursornode *cursornode,Offset *offset);
void find_offset(Hnode *hnode, Cursornode *cursornode, Offset *offset);
void where_cursor(Hnode *hnode, Cursornode *cursornode, int *cursor_x, int *cursor_y);
void find_cursor(Hnode *hnode ,Cursornode *cursornode,Offset *offset);
void mouse_click(Hnode *hnode, Cursornode *cursornode, Offset *offset);
void mouse_choose(Hnode *hnode, Cursornode *cursornode,Offset *offset);
#endif