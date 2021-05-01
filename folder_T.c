#include<stdio.h>
#include"function.h"
#include"menu.h"

//文件树的层序遍历和查找（方立煌）
/////////////////////////////////////////////////////////////////////////////////////////////////////////////



//文件目录建立
Status DIR_init(FolderTreePtr* F_T) {


	if ((*F_T)) {

		return ERROR;

	}
	else {
		(*F_T) = (FolderTreePtr)malloc(sizeof(FolderTree));

		if (!(*F_T)) {

			exit(0);

		}
		else {

			(*F_T)->root = NULL;
			return TRUE;

		}

	}

}


//查找对应文件的结点返回指向该结点的指针，否则返回NULL
FolderPtr Find_folder(FolderTreePtr F_T, char* name) {

	LQueue* Q = NULL;
	Queue_Init(&Q);
	Queue_In(&Q, F_T->root);
	while (!Queue_Empty(Q)) {//如果跳出循环，说明没有找到该文件
		FolderPtr node = Queue_Front(Q);
		if (!node) {
			Queue_Out(&Q);
			continue;
		}

		if (strcmp(node->folder_title, name) == 0) {
			return node;

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


//遍历树
Status Tree_Traverse(FolderTreePtr F_T, void (*visit)(FolderPtr q)) {
	LQueue* Q = NULL;
	Queue_Init(&Q);
	Queue_In(&Q, F_T->root);
	while (!Queue_Empty(Q)) {
		FolderPtr node = Queue_Front(Q);
		if (!node) {
			Queue_Out(&Q);
			continue;
		}
		visit(node);
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
}



//打印结点
void visit(FolderPtr p)
{
	printf("%s\n", p->folder_title);
}


//功能队列
Status Queue_Init(LQueue** q) {
	(*q) = (LQueue*)malloc(sizeof(LQueue));
	if (!(*q))return ERROR;
	QNode* p = (QNode*)malloc(sizeof(QNode));
	if (p == NULL) return ERROR;
	p->Qnext = NULL;
	(*q)->rear = p;
	(*q)->front = p;
	return TRUE;
}


Status Queue_Empty(LQueue* q) {
	return q->front == q->rear ? TRUE : ERROR;
}


Status Queue_In(LQueue** q, FolderPtr BNode) {

	QNode* temp;
	temp = (QNode*)malloc(sizeof(QNode));
	if (!temp) {
		return ERROR;
	}
	temp->pdata = BNode;
	(*q)->rear->Qnext = temp;
	(*q)->rear = temp;
	(*q)->rear->Qnext = NULL;
	return TRUE;

}


Status Queue_Out(LQueue** q) {

	if ((*q)->front == (*q)->rear) {
		return ERROR;
	}
	else if ((*q)->front->Qnext == (*q)->rear) {
		free((*q)->rear);
		(*q)->front->Qnext = NULL;
		(*q)->rear = (*q)->front;
	}
	else {
		QNode* temp = NULL;
		temp = (*q)->front->Qnext;
		(*q)->front->Qnext = temp->Qnext;
		temp->Qnext = NULL;
		free(temp);
	}
	return TRUE;

}


Folder* Queue_Front(LQueue* q) {
	if (q->front == q->rear) {
		return NULL;
	}
	else {
		Folder* temp = q->front->Qnext->pdata;
		return temp;
	}
}








//////////////////////////////////////////////////////////////////////////////////////////////





//文件夹树的处理（吴滨楠）
/// /////////////////////////////////////////////////////////////////////////////////////////////////


Status DIR_insert(FolderPtr F_path, char* title)
{
	FolderPtr p = F_path;
	//生成新结点
	FolderPtr t = (FolderPtr)malloc(sizeof(Folder));
	strcpy(t->folder_title, title);	//保存文件夹名到新结点
	/*在这里可以对标签Tag做赋值*/
	t->left = t->right = NULL;
	t->file_head = NULL;
	//找到插入位置，插入结点
	if (p->left != NULL)	//左孩子不为空，判断是否重名
	{
		if (strcmp(p->left->folder_title, title) == 0)	//结点已经存在（文件夹重名）
		{
			printf("该文件夹已存在，新建失败\n");
			free(t);
			return ERROR;
		}
	}
	if (p->right != NULL)	//右孩子不为空，判断是否重名
	{
		if (strcmp(p->right->folder_title, title) == 0)	//结点已经存在（文件夹重名）
		{
			printf("该文件夹已存在，新建失败\n");
			free(t);
			return ERROR;
		}
	}

	if (p->left == NULL)	//左孩子为空
	{
	
		p->left = t;
		return TRUE;
	
	}
	else if (p->right == NULL)	//右孩子为空
	{
		p->right = t;
		return TRUE;
	}
	else
	{
		printf("该路径下文件夹已满，不准许新建文件夹\n");
		free(t);
		return ERROR;
	}
}

Status DIR_delete(FolderPtr F_path, char* title)
{
	FolderPtr p = F_path;
	FolderPtr q;
	//判断目标结点是否存（左孩子或右孩子）
	if (p->left != NULL)	//先进行非空的判断再进行是否匹配的判断
	{
		if (strcmp(p->left->folder_title, title) == 0)	//目标结点是路径结点的左孩子
		{
			q = p->left;	//q：准备删除的目标结点（p的左孩子）
			p->left = NULL;	//p的左孩子置空
			//先对第三指针做是否为空的判断，若不为空，销毁链表并指针置空
			if (q->file_head != NULL)
			{
				FilePtr t = q->file_head;
				q->file_head = NULL;	//q的第三指针置空
				//function(t);		//调用销毁整个链表的函数/////////////////////////////////
				free(t);
			}
			//目标结点左右孩子均为空，直接删除
			if ((q->left == NULL) && (q->right == NULL))
			{
				free(q);
			}
			//目标结点左孩子不为空
			else if (q->left != NULL)
			{
				DIR_destroy(q->left);	//调用销毁二叉树辅助函数，销毁该结点以下所有分支结点（包括该结点）
				free(q);
			}
			//目标结点右孩子不为空
			else if (q->right != NULL)
			{
				DIR_destroy(q->right);
				free(q);
			}
			return TRUE;
		}
	}
	if (p->right != NULL)
	{
		if (strcmp(p->right->folder_title, title) == 0)	//目标结点是路径结点的右孩子
		{
			q = p->right;	//q：准备删除的目标结点（p的右孩子）
			p->right = NULL;	//p的右孩子置空
			//先对第三指针做是否为空的判断，若不为空，销毁链表并指针置空
			if (q->file_head != NULL)
			{
				FilePtr t = q->file_head;
				q->file_head = NULL;	//q的第三指针置空
				//function(t)		//调用销毁整个链表的函数/////////////////////////////////
				free(t);
			}
			//目标结点左右孩子均为空，直接删除
			if ((q->left == NULL) && (q->right == NULL))
			{
				free(q);
			}
			//目标结点左孩子不为空
			else if (q->left != NULL)
			{
				DIR_destroy(q->left);
				free(q);
			}
			//目标结点右孩子不为空
			else if (q->right != NULL)
			{
				DIR_destroy(q->right);
				free(q);
			}
			return TRUE;
		}
	}
	else		//找不到该文件夹
	{
		printf("在当前目录下找不到该文件夹，建议返回上一级目录查找\n");
		return ERROR;
	}
}

//销毁二叉树
/*销毁传入的结点下面所有分支结点，递归实现
  DIR_delete()函数的辅助函数*/
Status DIR_destroy(FolderPtr p)
{
	if (p == NULL)
		return;
	if (p->left != NULL)
	{
		DIR_destroy(p->left);
		p->left = NULL;
	}
	if (p->right != NULL)
	{
		DIR_destroy(p->right);
		p->right = NULL;
	}
	if (p != NULL)
	{
		free(p);
		p = NULL;
	}
}

//移动文件夹	/*old移动到new里面*/
Status DIR_move(FolderPtr F_path, char* oldtitle, char* newtitle)
{
	//只有存在两个文件夹才肯进行移动
	if ((F_path->left == NULL) || (F_path->right == NULL))
	{
		if ((F_path->left == NULL) && (F_path->right == NULL))
			printf("在当前目录下没有文件夹，不能进行移动\n");
		else
			printf("在当前目录下只有一个文件夹，不能进行移动\n");
		return ERROR;
	}
	if (strcmp(F_path->left->folder_title, oldtitle) == 0)	//old是路径的左孩子
	{
		if (strcmp(F_path->right->folder_title, newtitle) == 0)	//new是路径的右孩子，判断new的孩子是否满了
		{
			if (F_path->right->left == NULL)	//若new的左孩子为空，插入到左孩子
			{
				FolderPtr temp = (FolderPtr)malloc(sizeof(Folder));
				temp = F_path->left;		//保存old
				F_path->right->left = temp;	//将old插入到new的左孩子
				F_path->left = NULL;		//路径的左孩子置空（原本放old）
				return TRUE;
			}
			if (F_path->right->right == NULL)	//若new的右孩子为空，插入到右孩子
			{
				FolderPtr temp = (FolderPtr)malloc(sizeof(Folder));
				temp = F_path->left;		//保存old
				F_path->right->right = temp;	//将old插入到new的右孩子
				F_path->left = NULL;		//路径的左孩子置空（原本放old）
				return TRUE;
			}
			else 	//new的左右孩子都不为空，不能进行插入
			{
				printf("目标文件夹已满，不能进行移动\n");
				return ERROR;
			}
		}
		printf("在当前目录下找不到 %s 文件夹\n", newtitle);
		return ERROR;
	}
	if (strcmp(F_path->right->folder_title, oldtitle) == 0)	//old是路径的右孩子
	{
		if (strcmp(F_path->left->folder_title, newtitle) == 0)	//new是路径的左孩子，判断new的孩子是否满了
		{
			if (F_path->left->left == NULL)	//若new的左孩子为空，插入到左孩子
			{
				FolderPtr temp = (FolderPtr)malloc(sizeof(Folder));
				temp = F_path->right;		//保存old
				F_path->left->left = temp;	//将old插入到new的左孩子
				F_path->right = NULL;		//路径的右孩子置空（原本放old）
				return TRUE;
			}
			if (F_path->left->right == NULL)	//若new的右孩子为空，插入到右孩子
			{
				FolderPtr temp = (FolderPtr)malloc(sizeof(Folder));
				temp = F_path->right;		//保存old
				F_path->left->right = temp;	//将old插入到new的右孩子
				F_path->right = NULL;		//路径的右孩子置空（原本放old）
				return TRUE;
			}
			else 	//new的左右孩子都不为空，不能进行插入
			{
				printf("目标文件夹已满，不能进行移动\n");
				return ERROR;
			}
		}
		printf("在当前目录下找不到 %s 文件夹\n", newtitle);
		return ERROR;
	}
	printf("在当前目录下找不到 %s 文件夹\n", oldtitle);
	return ERROR;
}



///////////////////////////////////////////////////////////////////////////////////////////////////


//文件控制（吴滨楠）

///////////////////////////////////////////////////////////////////////////////////////////////////

//新建文件
Status FILE_insert(FolderPtr F_path, char* title)
{
	//若文件夹为空，直接新建文件
	if (F_path->file_head == NULL)
	{
		InitList(&F_path->file_head);
		InsertList(F_path->file_head, title);
		//printf("title is %s\n",F_path->file_head->next->file_title);
		//CreateFile(title);	//真实文件创建
		return TRUE;
	}
	//文件夹不为空，判断是否已有重名文件存在
	if (searchByName(F_path->file_head, title) == NULL)//无重名，新建文件
	{
		InsertList(F_path->file_head, title);
		//CreateFile(title);	//真实文件创建
		return TRUE;
	}
	else 	//存在重名文件，返回失败
	{
		printf("该文件已存在\n");
		return ERROR;
	}
}

//删除文件
Status FILE_delete(FolderPtr F_path, char* title)
{
	//若文件夹为空，直接输出错误
	if (F_path->file_head == NULL)
	{
		printf("在当前目录下找不到该文件，建议返回上一级\n");
		return ERROR;
	}
	//文件夹不为空，判断是否有该文件存在
	if (searchByName(F_path->file_head, title) != NULL)//文件存在，删除
	{
		if (DeleteByName(F_path->file_head, title) == 1)
			return TRUE;
		else
			return ERROR;
	}
	else	//文件不存在，输出错误
	{
		printf("在当前目录下找不到该文件，建议返回上一级\n");
		return ERROR;
	}
}

//移动文件
Status FILE_move(FolderPtr F_path, char* file_title, char* folder_title)
{
	//若文件夹为空，直接输出错误
	if (F_path->file_head == NULL)
	{
		printf("在当前目录下找不到该文件，建议返回上一级\n");
		return ERROR;
	}
	//文件夹不为空，判断是否有该文件存在
	if (searchByName(F_path->file_head, file_title) != NULL)	//文件存在，进行文件夹判断
	{
		//判断目标文件夹是否存在
		if ((F_path->left == NULL) && (F_path->right == NULL))	//若不存在文件夹
		{
			printf("在当前目录下找不到该文件夹，建议返回上一级\n");
			return ERROR;
		}
		if (F_path->left != NULL)	//先对左孩子进行非空判断
		{
			if (strcmp(F_path->left->folder_title, folder_title) == 0)	//文件夹是左孩子，进行移动
			{
				//获取目标文件
				FilePtr pf = (FilePtr)malloc(sizeof(File));
				pf = searchByName(F_path->file_head, file_title);	//pf：获取目标文件
				//在目标文件夹新建文件
				int i;
				Tag temp_tag[5];	//保存Tag，调用函数为Tag赋值时使用
				for (i = 0; i < 5; i++)
				{
					strcpy(temp_tag[i].tag_node, pf->file_tag[i].tag_node);	//为temp_tag逐个赋值
				}
				InsertList(F_path->left->file_head, file_title);		//在左孩字的链表插入结点

				AddTag(F_path->left->file_head, file_title, temp_tag[0].tag_node);	//为刚插入的结点赋Tag
				AddTag(F_path->left->file_head, file_title, temp_tag[1].tag_node);
				AddTag(F_path->left->file_head, file_title, temp_tag[2].tag_node);
				AddTag(F_path->left->file_head, file_title, temp_tag[3].tag_node);
				AddTag(F_path->left->file_head, file_title, temp_tag[4].tag_node);
				//删除原文件
				DeleteByName(F_path->file_head, file_title);		//删除被移动的结点

				return TRUE;
			}
		}
		else if (F_path->right != NULL)	//先对右孩子进行非空判断
		{
			if (strcmp(F_path->right->folder_title, folder_title) == 0)	//文件夹是右孩子，进行移动
			{
				//获取目标文件
				FilePtr pf = (FilePtr)malloc(sizeof(File));
				pf = searchByName(F_path->file_head, file_title);	//pf：获取目标文件
				//在目标文件夹新建文件
				int i;
				Tag temp_tag[5];	//保存Tag，调用函数为Tag赋值时使用
				for (i = 0; i < 5; i++)
				{
					strcpy(temp_tag[i].tag_node, pf->file_tag[i].tag_node);	//为temp_tag逐个赋值
				}

				InsertList(F_path->right->file_head, file_title);	//在右孩子的链表插入结点

				AddTag(F_path->right->file_head, file_title, temp_tag[0].tag_node);	//为刚插入的结点赋Tag
				AddTag(F_path->right->file_head, file_title, temp_tag[1].tag_node);
				AddTag(F_path->right->file_head, file_title, temp_tag[2].tag_node);
				AddTag(F_path->right->file_head, file_title, temp_tag[3].tag_node);
				AddTag(F_path->right->file_head, file_title, temp_tag[4].tag_node);
				//删除原文件
				DeleteByName(F_path->file_head, file_title);		//删除被移动的结点

				return TRUE;
			}
		}
		//该目录存在文件夹，但不存在目标文件夹
		printf("在当前目录下找不到该文件夹，建议返回上一级\n");
		return ERROR;
	}
	else	//文件不存在，输出错误
	{
		printf("在当前目录下找不到该文件，建议返回上一级\n");
		return ERROR;
	}
}

//重命名文件
Status FILE_rename(FolderPtr F_path, char* oldtitle, char* newtitle)
{
	//若文件夹为空，直接输出错误
	if (F_path->file_head == NULL)
	{
		printf("在当前目录下找不到该文件，建议返回上一级\n");
		return ERROR;
	}
	//文件夹不为空，判断是否有该文件存在
	if (searchByName(F_path->file_head, oldtitle) != NULL)//文件存在，重命名
	{
		if (ReName(F_path->file_head, oldtitle, newtitle) == 1)	//调用重命名函数
			return TRUE;
		else
		{
			return ERROR;
		}
	}
	else	//文件不存在，输出错误
	{
		printf("在当前目录下找不到该文件，建议返回上一级\n");
		return ERROR;
	}
}







///////////////////////////////////////////////////////////////////////////////////////////




//改变路径（吴滨楠）
//////////////////////////////////////////////////////////////////////////////////////////




//遍历树
/*
Status PATH_return(FolderTreePtr F_T, FolderPtr* F_path)//F_path为当前路径
{
	//先进行当前目录是否为根目录的判断
	if (F_T->root == *F_path)
	{
		printf("当前路径已经是根目录了\n");
		return ERROR;
	}
	//使用遍历，在其中加入判断
	LQueue* Q = NULL;
	Queue_Init(&Q);//建立队列
	Queue_In(&Q, F_T->root);//根节点入队
	FolderPtr node, f;	//f：node的双亲
	while (!Queue_Empty(Q))
	{
		node = Queue_Front(Q);
		if (!node)
		{
			Queue_Out(&Q);
			continue;
		}
		if (node == *F_path)	//node为当前路径，跳出循环
			break;
		//visit(node);
		Queue_Out(&Q);
		if (node->left)
		{
			Queue_In(&Q, node->left);
		}
		if (node->right)
		{
			Queue_In(&Q, node->right);
		}
		f = node;
	}
	free(Q);
	Q = NULL;
	if ( f != NULL)//存在结点
	{
		(*F_path) = f;	//将当前路径改为node的双亲
		return TRUE;
	}
	else
		return ERROR;
}
/*
//修改路径为父目录
Status PATH_return(FolderTreePtr F_T,FolderPtr *F_path)
{
	//FolderPtr temp=Tree_Traverse0(F_T,*F_path);
	//*F_path=temp;
	return TRUE;
}
*/




//修改路径为子目录
Status PATH_next(FolderPtr* F_path, char* title)
{
	//先左后右，先非空后匹配，在左右孩子查找是否是目标文件夹
	if ((*F_path)->left != NULL)	//左孩子非空
	{
		if (strcmp((*F_path)->left->folder_title, title) == 0)	//左孩子是目标文件夹
		{
			(*F_path) = (*F_path)->left;	//路径指针移动
			return TRUE;
		}
	}
	else if ((*F_path)->right != NULL)	//右孩子非空
	{
		if (strcmp((*F_path)->right->folder_title, title) == 0)	//右孩子是目标文件夹
		{
			(*F_path) = (*F_path)->right;	//路径指针移动
			return TRUE;
		}
	}
	else
	{
		printf("在当前路径下找不到目标文件夹，建议返回上一级目录\n");
		return ERROR;
	}
}




//////////////////////////////////////////////////////////////////////////////////////////



//文件链表建立（黄广超）
////////////////////////////////////////////////////////////////////////////////////////////



//FilePtr p = NULL;
Status InitList(FilePtr* p)//初始化链表
{
	*p = (FilePtr)malloc(sizeof(File));//给头结点分配一块内存空间
	if ((*p) == NULL)
		return ERROR;
	if ((*p) != NULL) {
		(*p)->next = NULL;
		strcpy((*p)->file_title, "\0");
		int i;
		for (i = 0; i < 5; i++) {
			strcpy((*p)->file_tag[i].tag_node, "\0");
		}
		// printf("初始化成功！\n");////////////////我把这个注释掉
	}

	return TRUE;

}
/*void TraverseList(FilePtr p)
{
	FilePtr p0 = p;//用p0遍历链表;
	do {
		p0 = p0->next;
	} while (p0->next != NULL);
}*/
Status InsertList(FilePtr p, char* file_name)//传入头结点指针和文件名
{
	if (p == NULL) {
		return ERROR;
	}
	FilePtr k = p;//k指向表尾，q用来创造新结点插入
	while (k->next != NULL) {
		k = k->next;
	}
	FilePtr	q = (FilePtr)malloc(sizeof(File));//////////我把sizeof()里面的改掉
	int i;
	for (i = 0; i < 5; i++) {
		strcpy(q->file_tag[i].tag_node, "\0");
	}
	strcpy(q->file_title, file_name);
	k->next = q;
	q->next = NULL;
	return TRUE;

}

Status AddTag(FilePtr p, char* file_title, char* TagNode)//对每一个tag进行判断，不为空则将名字加入
{
	if (p == NULL)
		return ERROR;

	FilePtr q = searchByName(p, file_title);
	if (q == NULL) {
		printf("未找到指定文件\n");
		return ERROR;
	}
	if (strlen(q->file_tag[0].tag_node) == 0) {
		strcpy(q->file_tag[0].tag_node, TagNode);
		return TRUE;
	}
	if (strlen(q->file_tag[1].tag_node) == 0) {
		strcpy(q->file_tag[1].tag_node, TagNode);
		return TRUE;
	}
	if (strlen(q->file_tag[2].tag_node) == 0) {
		strcpy(q->file_tag[2].tag_node, TagNode);
		return TRUE;
	}
	if (strlen(q->file_tag[3].tag_node) == 0) {
		strcpy(q->file_tag[3].tag_node, TagNode);
		return TRUE;
	}
	if (strlen(q->file_tag[4].tag_node) == 0) {
		strcpy(q->file_tag[4].tag_node, TagNode);
		return TRUE;
	}
	/*	int i = 0;
		while (1) {//输入标签  scanf("%s",q->file_tag[i].tag_node, 19)
			//while (getchar() != '\n');
			printf("请选择是否继续添加标签:1.添加，2取消");
			while (strlen(q->file_tag[i].tag_node)==0) {
				strcpy(q->file_tag[i].tag_node, TagNode);
				i++;
			}
				int x;
				scanf("%d", &x);
				//strcpy(q->file_tag[i].tag_node, TagNode);
				if (x == 2 || i > 5)
					break;
			}*/
	return TRUE;
}

Status DestoryList(FilePtr* p) {//销毁链表
	if ((*p) == NULL)
		return ERROR;
	FilePtr p1;
	do {
		p1 = *p;
		(*p) = (*p)->next;
		free(p1);
	} while (*p != NULL);
	p1 = NULL;
	p = NULL;		//利用一前一后两个指针销毁所有结点
	printf("链表已成功销毁！\n");
	return TRUE;
}

Status DeleteByName(FilePtr p, char* file_name) {//根据文件名删除
	FilePtr L = p;
	FilePtr q = p->next;
	while (q != NULL && strcmp(q->file_title, file_name)) {//q不是最后一个结点或没匹配到文件名字
		L = q;
		q = q->next;
	}
	if (strcmp(q->file_title, file_name) == 0)
	{
		L->next = q->next;
		free(q);
		q = NULL;
		printf("删除成功！");
		return TRUE;
	}
	return ERROR;
	/*else
	{
		L->next = q->next;
		free(q);
		q = NULL;
		printf("删除成功！");
	}*/


}
Status DeletebyTag(FilePtr p, char* tag_Name)//根据标签名删除
{
	if (p == NULL) {
		return ERROR;
	}
	FilePtr L = p;
	FilePtr q = p->next;
	int i;
	for (i = 0; i < 5; i++) {
		while (q != NULL && strcmp(q->file_tag[i].tag_node, tag_Name)) {//q不是最后一个结点或没匹配到标签名字
			L = q;
			q = q->next;
		}
		if (q != NULL && strcmp(q->file_tag[i].tag_node, tag_Name) == 0)
		{
			L->next = q->next;
			free(q);
			q = NULL;
			//printf("删除成功！");
			//return TRUE;
		}
		else if (q == NULL) {
			return ERROR;
		}
	}

	return
		TRUE;
}


FilePtr searchByName(FilePtr p, char* file_name)//根据文件名查找
{
	FilePtr q = p;
	while (q != NULL && strcmp(q->file_title, file_name))
	{
		q = q->next;
	}
	return q;
}
FilePtr searchByTag_Name(FilePtr p, char* tag_Name) {
	if (p == NULL) {
		return NULL;
	}
	FilePtr L = p;
	FilePtr q = p->next;
	int i;
	for (i = 0; i < 5; i++) {
		while (q != NULL && strcmp(q->file_tag[i].tag_node, tag_Name)) {//q不是最后一个结点或没匹配到文件名字
			L = q;
			q = q->next;
		}
		if (strcmp(q->file_tag[i].tag_node, tag_Name) == 0)
		{
			return q;
		}
		else if (q == NULL) {
			return NULL;
		}
	}

}
Status printList(FilePtr p)
{
	if (p == NULL) {
		return ERROR;
	}
	FilePtr s = p->next;
	while (s)
	{
		printf("文件名\t%s\t\n", s->file_title);
		int i;
		for (i = 0; i < 5; i++) {
			printf("标签\t%s\n", s->file_tag[i].tag_node);
		}
		s = s->next;
	}
	return TRUE;
}

Status ReName(FilePtr p, char* PreFile_title, char* NewFile_title) {//重命名
	FilePtr q = searchByName(p, PreFile_title);//找不到返回错误
	if (q == NULL) {
		printf("未找到指定文件\n");
		return ERROR;
	}
	strcpy(q->file_title, "\0");//先清空
	strcpy(q->file_title, NewFile_title);//再复制
	return TRUE;

}



//////////////////////////////////////////////////////////////////////////////////////////////

