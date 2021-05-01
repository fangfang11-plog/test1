#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "unistd.h"
#include <io.h>
#include"function.h"
#include"menu.h"


//创建文件
/*指令：mkdir <笔记文件名>	接口：笔记文件名*/
Status CreateFile(char* fileTitle)
{
	if (_access(fileTitle, 0) == -1)	//判断文件是否已存在
		printf("新建成功！！！\n");
	else
	{
		printf("该文件已存在，新建失败\n");
		return ERROR;
	}
	//新建文件
	FILE* fp = NULL;
	fopen_s(&fp,fileTitle, "a+");//a+：读/追加方式
	fprintf(fp, "\n");
	fclose(fp);
	return TRUE;
}

//删除文件
/*指令：rm <笔记文件名>		接口：笔记文件名*/
Status DeleteFile(char* fileTitle)
{
	//删除文件并判断是否成功（文件名错误会失败）
	if (remove(fileTitle) == 0)
	{
		printf("成功删除 %s\n", fileTitle);
		return TRUE;
	}
	else
	{
		printf("删除失败\n");
		return ERROR;
	}
}

//重命名文件
/*指令：mv <笔记原文件名><笔记目标文件名>	接口：笔记原文件名，笔记目标文件名*/
Status RenameFile(char* fileTitle, char* newfileTitle)
{
	//重命名并判断是否成功（文件夹名错误会失败）
	if (rename(fileTitle, newfileTitle) == 0)
	{
		printf("重命名成功\n");
		return TRUE;
	}
	else
	{
		printf("重命名失败\n");
		return ERROR;
	}
}




//创建文件夹
/*指令：mkdir -r<笔记文件夹名>，接口：笔记文件夹名 */
Status CreateFolder(char* folderTitle)
{
	//文件夹不存在则创建文件夹
	if (_access(folderTitle, 0) == -1)
	{
		if (_mkdir(folderTitle) == 0)
		{
			printf("创建成功\n");
			return TRUE;
		}
		else
		{
			printf("创建失败\n");
			return ERROR;
		}
	}
	else
	{
		printf("该文件夹已存在\n");
		return ERROR;
	}
}

//删除文件夹
/*指令：rm -r<笔记文件夹名>	接口：笔记文件夹名*/
Status  DeleteFolder(char* folderTitle)
{
	if (rmdir(folderTitle) == 0)
	{
		printf("删除成功\n");
		return TRUE;
	}
	else
	{
		printf("删除失败\n");
		return TRUE;
	}
}

//将路径切换为当前目录的父目录
/*指令：cd ..	接口：无*/
Status ReturnFolder()
{
	char* path0 = getcwd(NULL, 0); 	//记录修改前的目录
	//返回上一级
	char folderTitle[50] = "../";
	chdir(folderTitle);
	char* path1 = getcwd(NULL, 0);	//记录修改后的目录
	//判断是不是已经到达根目录
	if (strcmp(path0, path1) == 0)
		printf("当前路径已经是根目录了\n");
	else
		printf("修改成功\n");
	printf("当前路径为：%s\n", getcwd(NULL, 0));
	return TRUE;
}

//将路径切换为命令中输入的文件夹路径
/*指令：cd <笔记文件夹路径>	接口：笔记文件夹路径 */
Status ChangeFolder(char* folderTitle)
{
	if (chdir(folderTitle) == 0)
		printf("修改成功\n");
	else
	{
		printf("修改失败\n");
		return ERROR;
	}
	printf("当前路径为：%s\n", getcwd(NULL, 0));
	return TRUE;
}

//打印当前路径
/*指令：无	接口：无*/
Status PrintFolder()
{
	printf("当前路径为：%s\n", getcwd(NULL, 0));
	return TRUE;
}