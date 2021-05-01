#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"function.h"
#include"menu.h"



//切割指令
/*
	指令有<，但缺少>，报错
	忽视两个<>中间的字符，只取第一个<>前面的字符作为指令
*/
Status SplitCommand(char* str, char* order, char* title0, char* title1)
{
	int i, j = 0, k = 0, m = 0, flag0 = 0, flag1 = 0;
	int len = strlen(str);
	for (i = 0; i < len; i++)
	{
		if (str[i] == '<' && flag0 == 0)
		{	//第一个文件名
			for (j = 0, i++; str[i] != '>'; j++, i++)
			{
				if (str[i] == '\0')
				{
					printf("输入指令格式有误\n");
					return ERROR;
				}
				title0[j] = str[i];
				flag0 = 1;
			}
		}
		else if ((str[i] == '<'||str[i]=='"')&& flag0 == 1)
		{	//若有第二个文件名
			for (k = 0, i++; str[i] != '>'&& str[i]!='"'; k++, i++)
			{
				if (str[i] == '\0')
				{
					printf("输入指令格式有误\n");
					return ERROR;
				}
				title1[k] = str[i];
			}
		}
		else
		{	//指令
			order[m] = str[i];
			m++;
		}
	}

	title0[j++] = '\0';
	title1[k++] = '\0';
	order[m++] = '\0';

	return TRUE;
}

Status IsCommand(char* title)
{
	int len = strlen(title);
	int i;
	for (i = 0; i < len; i++)
	{
		if (title[i] == '.')
			return TRUE;
	}
	return ERROR;
}




Status deldir(char* p)
{
	if (p[0] == 'r' && p[1] == 'm' && p[2] == '-' && p[3] == 'r' && p[4] == '<')
	{
		int i = 0;
		while (p[i] != '>' && p[i] != '\0')
		{
			i++;
		}//这时候跳出循环的p[i]要么是>或者是\0
		if (p[i] == '\0')
		{
			printf("指令输入错误，请重新输入！\n");
			return ERROR;
		}
		else//进入到这一步的话说明p[i]=='>'的
		{
			char cmd[255] = { 'r','m','d','i','r',' ','/','s',' ' };
			for (int n = 5, j = 9; n < i; n++, j++)
			{
				cmd[j] = p[n];
			}
			//printf("%s\n",cmd);
			system(cmd);
			printf("指令执行成功！\n");
			return TRUE;
		}

	}
	else
	{
		printf("指令输入错误，请重新输入!\n");
		return ERROR;
	}
}



//改变路径（刘俊帆）
Status mvfile(char* p)//移动
{
	char title0[15];
	char title1[15];
	char Userorder[25];
	char tureorder[100] = { 'm','o','v','e',' ' };

	SplitCommand(p, Userorder, title0, title1);

	strcat_s(tureorder, title0,15);

	int L = strlen(tureorder);
	tureorder[L] = ' ';

	strcat_s(tureorder, title1,15);

	printf("%s\n", tureorder);
	system(tureorder);
	system("pause");
}


//检查小数点,检查到时返回TRUE
Status check_dot(char* str) {
	char* p = str;
	while (p) {
		
		if (p == '.') {
			return TRUE;
		}
		else {
			p++;
		}

	}
	return ERROR;

}





Status AddFolderTag(FolderTreePtr F_T, char* folder_title, char* TagNode)
{
	if (F_T == NULL) {
		return ERROR;
	}
	FolderPtr temp = Find_folder(F_T, folder_title);
	if (temp == NULL) {
		printf("未找到指定文件夹\n");
		return ERROR;
	}
	if (strlen(temp->folder_tag[0].tag_node) == 0) {
		strcpy(temp->folder_tag[0].tag_node, TagNode);
		return TRUE;
	}
	if (strlen(temp->folder_tag[1].tag_node) == 0) {
		strcpy(temp->folder_tag[1].tag_node, TagNode);
		return TRUE;
	}
	if (strlen(temp->folder_tag[2].tag_node) == 0) {
		strcpy(temp->folder_tag[2].tag_node, TagNode);
		return TRUE;
	}
	if (strlen(temp->folder_tag[3].tag_node) == 0) {
		strcpy(temp->folder_tag[3].tag_node, TagNode);
		return TRUE;
	}
	if (strlen(temp->folder_tag[4].tag_node) == 0) {
		strcpy(temp->folder_tag[4].tag_node, TagNode);
		return TRUE;
	}
	return TRUE;
}




FolderPtr SearchByTag_Names(FolderTreePtr F_T, char* TagNode)//这是整棵树查找对应指令：tag- s” 标签内容 ”
{
	LQueue* Q = NULL;
	Queue_Init(&Q);
	Queue_In(&Q, F_T->root);//如果是在当前目录下查找就是Queue_In(&Q, FolderPtr BNode);
//出队
	while (!Queue_Empty(Q)) {//如果跳出循环，说明没有找到该文件
		FolderPtr node = Queue_Front(Q);
		if (!node) {
			Queue_Out(&Q);
			continue;
		}
		int i;
		for (i = 0; i < 5; i++) {
			if (strcmp(node->folder_tag[i].tag_node, TagNode) == 0) {
				return node;

			}
		}
		Queue_Out(&Q);
		if (node->left) {
			Queue_In(&Q, node->left);
		}
		if (node->right) {
			Queue_In(&Q, node->right);
		}
	}
	free(Q);
	Q = NULL;
	return NULL;
}
FolderPtr SearchByTag_Namesa(FolderPtr F_T, char* TagNode)//这是在当前目录下查找对应指令：tag -sa” 标签内容 ”
{
	LQueue* Q = NULL;
	Queue_Init(&Q);
	Queue_In(&Q, F_T);
	//出队
	while (!Queue_Empty(Q)) {//如果跳出循环，说明没有找到该文件
		FolderPtr node = Queue_Front(Q);
		if (!node) {
			Queue_Out(&Q);
			continue;
		}
		int i;
		for (i = 0; i < 5; i++) {
			if (strcmp(node->folder_tag[i].tag_node, TagNode) == 0) {
				return node;

			}
		}
		Queue_Out(&Q);
		if (node->left) {
			Queue_In(&Q, node->left);
		}
		if (node->right) {
			Queue_In(&Q, node->right);
		}
	}
	free(Q);
	Q = NULL;
	return NULL;
}