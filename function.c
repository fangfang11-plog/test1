#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"function.h"
#include"menu.h"



//�и�ָ��
/*
	ָ����<����ȱ��>������
	��������<>�м���ַ���ֻȡ��һ��<>ǰ����ַ���Ϊָ��
*/
Status SplitCommand(char* str, char* order, char* title0, char* title1)
{
	int i, j = 0, k = 0, m = 0, flag0 = 0, flag1 = 0;
	int len = strlen(str);
	for (i = 0; i < len; i++)
	{
		if (str[i] == '<' && flag0 == 0)
		{	//��һ���ļ���
			for (j = 0, i++; str[i] != '>'; j++, i++)
			{
				if (str[i] == '\0')
				{
					printf("����ָ���ʽ����\n");
					return ERROR;
				}
				title0[j] = str[i];
				flag0 = 1;
			}
		}
		else if ((str[i] == '<'||str[i]=='"')&& flag0 == 1)
		{	//���еڶ����ļ���
			for (k = 0, i++; str[i] != '>'&& str[i]!='"'; k++, i++)
			{
				if (str[i] == '\0')
				{
					printf("����ָ���ʽ����\n");
					return ERROR;
				}
				title1[k] = str[i];
			}
		}
		else
		{	//ָ��
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
		}//��ʱ������ѭ����p[i]Ҫô��>������\0
		if (p[i] == '\0')
		{
			printf("ָ������������������룡\n");
			return ERROR;
		}
		else//���뵽��һ���Ļ�˵��p[i]=='>'��
		{
			char cmd[255] = { 'r','m','d','i','r',' ','/','s',' ' };
			for (int n = 5, j = 9; n < i; n++, j++)
			{
				cmd[j] = p[n];
			}
			//printf("%s\n",cmd);
			system(cmd);
			printf("ָ��ִ�гɹ���\n");
			return TRUE;
		}

	}
	else
	{
		printf("ָ�������������������!\n");
		return ERROR;
	}
}



//�ı�·������������
Status mvfile(char* p)//�ƶ�
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


//���С����,��鵽ʱ����TRUE
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
		printf("δ�ҵ�ָ���ļ���\n");
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




FolderPtr SearchByTag_Names(FolderTreePtr F_T, char* TagNode)//�������������Ҷ�Ӧָ�tag- s�� ��ǩ���� ��
{
	LQueue* Q = NULL;
	Queue_Init(&Q);
	Queue_In(&Q, F_T->root);//������ڵ�ǰĿ¼�²��Ҿ���Queue_In(&Q, FolderPtr BNode);
//����
	while (!Queue_Empty(Q)) {//�������ѭ����˵��û���ҵ����ļ�
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
FolderPtr SearchByTag_Namesa(FolderPtr F_T, char* TagNode)//�����ڵ�ǰĿ¼�²��Ҷ�Ӧָ�tag -sa�� ��ǩ���� ��
{
	LQueue* Q = NULL;
	Queue_Init(&Q);
	Queue_In(&Q, F_T);
	//����
	while (!Queue_Empty(Q)) {//�������ѭ����˵��û���ҵ����ļ�
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