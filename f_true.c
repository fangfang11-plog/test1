#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "unistd.h"
#include <io.h>
#include"function.h"
#include"menu.h"


//�����ļ�
/*ָ�mkdir <�ʼ��ļ���>	�ӿڣ��ʼ��ļ���*/
Status CreateFile(char* fileTitle)
{
	if (_access(fileTitle, 0) == -1)	//�ж��ļ��Ƿ��Ѵ���
		printf("�½��ɹ�������\n");
	else
	{
		printf("���ļ��Ѵ��ڣ��½�ʧ��\n");
		return ERROR;
	}
	//�½��ļ�
	FILE* fp = NULL;
	fopen_s(&fp,fileTitle, "a+");//a+����/׷�ӷ�ʽ
	fprintf(fp, "\n");
	fclose(fp);
	return TRUE;
}

//ɾ���ļ�
/*ָ�rm <�ʼ��ļ���>		�ӿڣ��ʼ��ļ���*/
Status DeleteFile(char* fileTitle)
{
	//ɾ���ļ����ж��Ƿ�ɹ����ļ��������ʧ�ܣ�
	if (remove(fileTitle) == 0)
	{
		printf("�ɹ�ɾ�� %s\n", fileTitle);
		return TRUE;
	}
	else
	{
		printf("ɾ��ʧ��\n");
		return ERROR;
	}
}

//�������ļ�
/*ָ�mv <�ʼ�ԭ�ļ���><�ʼ�Ŀ���ļ���>	�ӿڣ��ʼ�ԭ�ļ������ʼ�Ŀ���ļ���*/
Status RenameFile(char* fileTitle, char* newfileTitle)
{
	//���������ж��Ƿ�ɹ����ļ����������ʧ�ܣ�
	if (rename(fileTitle, newfileTitle) == 0)
	{
		printf("�������ɹ�\n");
		return TRUE;
	}
	else
	{
		printf("������ʧ��\n");
		return ERROR;
	}
}




//�����ļ���
/*ָ�mkdir -r<�ʼ��ļ�����>���ӿڣ��ʼ��ļ����� */
Status CreateFolder(char* folderTitle)
{
	//�ļ��в������򴴽��ļ���
	if (_access(folderTitle, 0) == -1)
	{
		if (_mkdir(folderTitle) == 0)
		{
			printf("�����ɹ�\n");
			return TRUE;
		}
		else
		{
			printf("����ʧ��\n");
			return ERROR;
		}
	}
	else
	{
		printf("���ļ����Ѵ���\n");
		return ERROR;
	}
}

//ɾ���ļ���
/*ָ�rm -r<�ʼ��ļ�����>	�ӿڣ��ʼ��ļ�����*/
Status  DeleteFolder(char* folderTitle)
{
	if (rmdir(folderTitle) == 0)
	{
		printf("ɾ���ɹ�\n");
		return TRUE;
	}
	else
	{
		printf("ɾ��ʧ��\n");
		return TRUE;
	}
}

//��·���л�Ϊ��ǰĿ¼�ĸ�Ŀ¼
/*ָ�cd ..	�ӿڣ���*/
Status ReturnFolder()
{
	char* path0 = getcwd(NULL, 0); 	//��¼�޸�ǰ��Ŀ¼
	//������һ��
	char folderTitle[50] = "../";
	chdir(folderTitle);
	char* path1 = getcwd(NULL, 0);	//��¼�޸ĺ��Ŀ¼
	//�ж��ǲ����Ѿ������Ŀ¼
	if (strcmp(path0, path1) == 0)
		printf("��ǰ·���Ѿ��Ǹ�Ŀ¼��\n");
	else
		printf("�޸ĳɹ�\n");
	printf("��ǰ·��Ϊ��%s\n", getcwd(NULL, 0));
	return TRUE;
}

//��·���л�Ϊ������������ļ���·��
/*ָ�cd <�ʼ��ļ���·��>	�ӿڣ��ʼ��ļ���·�� */
Status ChangeFolder(char* folderTitle)
{
	if (chdir(folderTitle) == 0)
		printf("�޸ĳɹ�\n");
	else
	{
		printf("�޸�ʧ��\n");
		return ERROR;
	}
	printf("��ǰ·��Ϊ��%s\n", getcwd(NULL, 0));
	return TRUE;
}

//��ӡ��ǰ·��
/*ָ���	�ӿڣ���*/
Status PrintFolder()
{
	printf("��ǰ·��Ϊ��%s\n", getcwd(NULL, 0));
	return TRUE;
}