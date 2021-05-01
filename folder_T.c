#include<stdio.h>
#include"function.h"
#include"menu.h"

//�ļ����Ĳ�������Ͳ��ң������ͣ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////



//�ļ�Ŀ¼����
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


//���Ҷ�Ӧ�ļ��Ľ�㷵��ָ��ý���ָ�룬���򷵻�NULL
FolderPtr Find_folder(FolderTreePtr F_T, char* name) {

	LQueue* Q = NULL;
	Queue_Init(&Q);
	Queue_In(&Q, F_T->root);
	while (!Queue_Empty(Q)) {//�������ѭ����˵��û���ҵ����ļ�
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


//������
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



//��ӡ���
void visit(FolderPtr p)
{
	printf("%s\n", p->folder_title);
}


//���ܶ���
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





//�ļ������Ĵ������骣�
/// /////////////////////////////////////////////////////////////////////////////////////////////////


Status DIR_insert(FolderPtr F_path, char* title)
{
	FolderPtr p = F_path;
	//�����½��
	FolderPtr t = (FolderPtr)malloc(sizeof(Folder));
	strcpy(t->folder_title, title);	//�����ļ��������½��
	/*��������ԶԱ�ǩTag����ֵ*/
	t->left = t->right = NULL;
	t->file_head = NULL;
	//�ҵ�����λ�ã�������
	if (p->left != NULL)	//���Ӳ�Ϊ�գ��ж��Ƿ�����
	{
		if (strcmp(p->left->folder_title, title) == 0)	//����Ѿ����ڣ��ļ���������
		{
			printf("���ļ����Ѵ��ڣ��½�ʧ��\n");
			free(t);
			return ERROR;
		}
	}
	if (p->right != NULL)	//�Һ��Ӳ�Ϊ�գ��ж��Ƿ�����
	{
		if (strcmp(p->right->folder_title, title) == 0)	//����Ѿ����ڣ��ļ���������
		{
			printf("���ļ����Ѵ��ڣ��½�ʧ��\n");
			free(t);
			return ERROR;
		}
	}

	if (p->left == NULL)	//����Ϊ��
	{
	
		p->left = t;
		return TRUE;
	
	}
	else if (p->right == NULL)	//�Һ���Ϊ��
	{
		p->right = t;
		return TRUE;
	}
	else
	{
		printf("��·�����ļ�����������׼���½��ļ���\n");
		free(t);
		return ERROR;
	}
}

Status DIR_delete(FolderPtr F_path, char* title)
{
	FolderPtr p = F_path;
	FolderPtr q;
	//�ж�Ŀ�����Ƿ�棨���ӻ��Һ��ӣ�
	if (p->left != NULL)	//�Ƚ��зǿյ��ж��ٽ����Ƿ�ƥ����ж�
	{
		if (strcmp(p->left->folder_title, title) == 0)	//Ŀ������·����������
		{
			q = p->left;	//q��׼��ɾ����Ŀ���㣨p�����ӣ�
			p->left = NULL;	//p�������ÿ�
			//�ȶԵ���ָ�����Ƿ�Ϊ�յ��жϣ�����Ϊ�գ���������ָ���ÿ�
			if (q->file_head != NULL)
			{
				FilePtr t = q->file_head;
				q->file_head = NULL;	//q�ĵ���ָ���ÿ�
				//function(t);		//����������������ĺ���/////////////////////////////////
				free(t);
			}
			//Ŀ�������Һ��Ӿ�Ϊ�գ�ֱ��ɾ��
			if ((q->left == NULL) && (q->right == NULL))
			{
				free(q);
			}
			//Ŀ�������Ӳ�Ϊ��
			else if (q->left != NULL)
			{
				DIR_destroy(q->left);	//�������ٶ������������������ٸý���������з�֧��㣨�����ý�㣩
				free(q);
			}
			//Ŀ�����Һ��Ӳ�Ϊ��
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
		if (strcmp(p->right->folder_title, title) == 0)	//Ŀ������·�������Һ���
		{
			q = p->right;	//q��׼��ɾ����Ŀ���㣨p���Һ��ӣ�
			p->right = NULL;	//p���Һ����ÿ�
			//�ȶԵ���ָ�����Ƿ�Ϊ�յ��жϣ�����Ϊ�գ���������ָ���ÿ�
			if (q->file_head != NULL)
			{
				FilePtr t = q->file_head;
				q->file_head = NULL;	//q�ĵ���ָ���ÿ�
				//function(t)		//����������������ĺ���/////////////////////////////////
				free(t);
			}
			//Ŀ�������Һ��Ӿ�Ϊ�գ�ֱ��ɾ��
			if ((q->left == NULL) && (q->right == NULL))
			{
				free(q);
			}
			//Ŀ�������Ӳ�Ϊ��
			else if (q->left != NULL)
			{
				DIR_destroy(q->left);
				free(q);
			}
			//Ŀ�����Һ��Ӳ�Ϊ��
			else if (q->right != NULL)
			{
				DIR_destroy(q->right);
				free(q);
			}
			return TRUE;
		}
	}
	else		//�Ҳ������ļ���
	{
		printf("�ڵ�ǰĿ¼���Ҳ������ļ��У����鷵����һ��Ŀ¼����\n");
		return ERROR;
	}
}

//���ٶ�����
/*���ٴ���Ľ���������з�֧��㣬�ݹ�ʵ��
  DIR_delete()�����ĸ�������*/
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

//�ƶ��ļ���	/*old�ƶ���new����*/
Status DIR_move(FolderPtr F_path, char* oldtitle, char* newtitle)
{
	//ֻ�д��������ļ��вſϽ����ƶ�
	if ((F_path->left == NULL) || (F_path->right == NULL))
	{
		if ((F_path->left == NULL) && (F_path->right == NULL))
			printf("�ڵ�ǰĿ¼��û���ļ��У����ܽ����ƶ�\n");
		else
			printf("�ڵ�ǰĿ¼��ֻ��һ���ļ��У����ܽ����ƶ�\n");
		return ERROR;
	}
	if (strcmp(F_path->left->folder_title, oldtitle) == 0)	//old��·��������
	{
		if (strcmp(F_path->right->folder_title, newtitle) == 0)	//new��·�����Һ��ӣ��ж�new�ĺ����Ƿ�����
		{
			if (F_path->right->left == NULL)	//��new������Ϊ�գ����뵽����
			{
				FolderPtr temp = (FolderPtr)malloc(sizeof(Folder));
				temp = F_path->left;		//����old
				F_path->right->left = temp;	//��old���뵽new������
				F_path->left = NULL;		//·���������ÿգ�ԭ����old��
				return TRUE;
			}
			if (F_path->right->right == NULL)	//��new���Һ���Ϊ�գ����뵽�Һ���
			{
				FolderPtr temp = (FolderPtr)malloc(sizeof(Folder));
				temp = F_path->left;		//����old
				F_path->right->right = temp;	//��old���뵽new���Һ���
				F_path->left = NULL;		//·���������ÿգ�ԭ����old��
				return TRUE;
			}
			else 	//new�����Һ��Ӷ���Ϊ�գ����ܽ��в���
			{
				printf("Ŀ���ļ������������ܽ����ƶ�\n");
				return ERROR;
			}
		}
		printf("�ڵ�ǰĿ¼���Ҳ��� %s �ļ���\n", newtitle);
		return ERROR;
	}
	if (strcmp(F_path->right->folder_title, oldtitle) == 0)	//old��·�����Һ���
	{
		if (strcmp(F_path->left->folder_title, newtitle) == 0)	//new��·�������ӣ��ж�new�ĺ����Ƿ�����
		{
			if (F_path->left->left == NULL)	//��new������Ϊ�գ����뵽����
			{
				FolderPtr temp = (FolderPtr)malloc(sizeof(Folder));
				temp = F_path->right;		//����old
				F_path->left->left = temp;	//��old���뵽new������
				F_path->right = NULL;		//·�����Һ����ÿգ�ԭ����old��
				return TRUE;
			}
			if (F_path->left->right == NULL)	//��new���Һ���Ϊ�գ����뵽�Һ���
			{
				FolderPtr temp = (FolderPtr)malloc(sizeof(Folder));
				temp = F_path->right;		//����old
				F_path->left->right = temp;	//��old���뵽new���Һ���
				F_path->right = NULL;		//·�����Һ����ÿգ�ԭ����old��
				return TRUE;
			}
			else 	//new�����Һ��Ӷ���Ϊ�գ����ܽ��в���
			{
				printf("Ŀ���ļ������������ܽ����ƶ�\n");
				return ERROR;
			}
		}
		printf("�ڵ�ǰĿ¼���Ҳ��� %s �ļ���\n", newtitle);
		return ERROR;
	}
	printf("�ڵ�ǰĿ¼���Ҳ��� %s �ļ���\n", oldtitle);
	return ERROR;
}



///////////////////////////////////////////////////////////////////////////////////////////////////


//�ļ����ƣ����骣�

///////////////////////////////////////////////////////////////////////////////////////////////////

//�½��ļ�
Status FILE_insert(FolderPtr F_path, char* title)
{
	//���ļ���Ϊ�գ�ֱ���½��ļ�
	if (F_path->file_head == NULL)
	{
		InitList(&F_path->file_head);
		InsertList(F_path->file_head, title);
		//printf("title is %s\n",F_path->file_head->next->file_title);
		//CreateFile(title);	//��ʵ�ļ�����
		return TRUE;
	}
	//�ļ��в�Ϊ�գ��ж��Ƿ����������ļ�����
	if (searchByName(F_path->file_head, title) == NULL)//���������½��ļ�
	{
		InsertList(F_path->file_head, title);
		//CreateFile(title);	//��ʵ�ļ�����
		return TRUE;
	}
	else 	//���������ļ�������ʧ��
	{
		printf("���ļ��Ѵ���\n");
		return ERROR;
	}
}

//ɾ���ļ�
Status FILE_delete(FolderPtr F_path, char* title)
{
	//���ļ���Ϊ�գ�ֱ���������
	if (F_path->file_head == NULL)
	{
		printf("�ڵ�ǰĿ¼���Ҳ������ļ������鷵����һ��\n");
		return ERROR;
	}
	//�ļ��в�Ϊ�գ��ж��Ƿ��и��ļ�����
	if (searchByName(F_path->file_head, title) != NULL)//�ļ����ڣ�ɾ��
	{
		if (DeleteByName(F_path->file_head, title) == 1)
			return TRUE;
		else
			return ERROR;
	}
	else	//�ļ������ڣ��������
	{
		printf("�ڵ�ǰĿ¼���Ҳ������ļ������鷵����һ��\n");
		return ERROR;
	}
}

//�ƶ��ļ�
Status FILE_move(FolderPtr F_path, char* file_title, char* folder_title)
{
	//���ļ���Ϊ�գ�ֱ���������
	if (F_path->file_head == NULL)
	{
		printf("�ڵ�ǰĿ¼���Ҳ������ļ������鷵����һ��\n");
		return ERROR;
	}
	//�ļ��в�Ϊ�գ��ж��Ƿ��и��ļ�����
	if (searchByName(F_path->file_head, file_title) != NULL)	//�ļ����ڣ������ļ����ж�
	{
		//�ж�Ŀ���ļ����Ƿ����
		if ((F_path->left == NULL) && (F_path->right == NULL))	//���������ļ���
		{
			printf("�ڵ�ǰĿ¼���Ҳ������ļ��У����鷵����һ��\n");
			return ERROR;
		}
		if (F_path->left != NULL)	//�ȶ����ӽ��зǿ��ж�
		{
			if (strcmp(F_path->left->folder_title, folder_title) == 0)	//�ļ��������ӣ������ƶ�
			{
				//��ȡĿ���ļ�
				FilePtr pf = (FilePtr)malloc(sizeof(File));
				pf = searchByName(F_path->file_head, file_title);	//pf����ȡĿ���ļ�
				//��Ŀ���ļ����½��ļ�
				int i;
				Tag temp_tag[5];	//����Tag�����ú���ΪTag��ֵʱʹ��
				for (i = 0; i < 5; i++)
				{
					strcpy(temp_tag[i].tag_node, pf->file_tag[i].tag_node);	//Ϊtemp_tag�����ֵ
				}
				InsertList(F_path->left->file_head, file_title);		//�����ֵ����������

				AddTag(F_path->left->file_head, file_title, temp_tag[0].tag_node);	//Ϊ�ղ���Ľ�㸳Tag
				AddTag(F_path->left->file_head, file_title, temp_tag[1].tag_node);
				AddTag(F_path->left->file_head, file_title, temp_tag[2].tag_node);
				AddTag(F_path->left->file_head, file_title, temp_tag[3].tag_node);
				AddTag(F_path->left->file_head, file_title, temp_tag[4].tag_node);
				//ɾ��ԭ�ļ�
				DeleteByName(F_path->file_head, file_title);		//ɾ�����ƶ��Ľ��

				return TRUE;
			}
		}
		else if (F_path->right != NULL)	//�ȶ��Һ��ӽ��зǿ��ж�
		{
			if (strcmp(F_path->right->folder_title, folder_title) == 0)	//�ļ������Һ��ӣ������ƶ�
			{
				//��ȡĿ���ļ�
				FilePtr pf = (FilePtr)malloc(sizeof(File));
				pf = searchByName(F_path->file_head, file_title);	//pf����ȡĿ���ļ�
				//��Ŀ���ļ����½��ļ�
				int i;
				Tag temp_tag[5];	//����Tag�����ú���ΪTag��ֵʱʹ��
				for (i = 0; i < 5; i++)
				{
					strcpy(temp_tag[i].tag_node, pf->file_tag[i].tag_node);	//Ϊtemp_tag�����ֵ
				}

				InsertList(F_path->right->file_head, file_title);	//���Һ��ӵ����������

				AddTag(F_path->right->file_head, file_title, temp_tag[0].tag_node);	//Ϊ�ղ���Ľ�㸳Tag
				AddTag(F_path->right->file_head, file_title, temp_tag[1].tag_node);
				AddTag(F_path->right->file_head, file_title, temp_tag[2].tag_node);
				AddTag(F_path->right->file_head, file_title, temp_tag[3].tag_node);
				AddTag(F_path->right->file_head, file_title, temp_tag[4].tag_node);
				//ɾ��ԭ�ļ�
				DeleteByName(F_path->file_head, file_title);		//ɾ�����ƶ��Ľ��

				return TRUE;
			}
		}
		//��Ŀ¼�����ļ��У���������Ŀ���ļ���
		printf("�ڵ�ǰĿ¼���Ҳ������ļ��У����鷵����һ��\n");
		return ERROR;
	}
	else	//�ļ������ڣ��������
	{
		printf("�ڵ�ǰĿ¼���Ҳ������ļ������鷵����һ��\n");
		return ERROR;
	}
}

//�������ļ�
Status FILE_rename(FolderPtr F_path, char* oldtitle, char* newtitle)
{
	//���ļ���Ϊ�գ�ֱ���������
	if (F_path->file_head == NULL)
	{
		printf("�ڵ�ǰĿ¼���Ҳ������ļ������鷵����һ��\n");
		return ERROR;
	}
	//�ļ��в�Ϊ�գ��ж��Ƿ��и��ļ�����
	if (searchByName(F_path->file_head, oldtitle) != NULL)//�ļ����ڣ�������
	{
		if (ReName(F_path->file_head, oldtitle, newtitle) == 1)	//��������������
			return TRUE;
		else
		{
			return ERROR;
		}
	}
	else	//�ļ������ڣ��������
	{
		printf("�ڵ�ǰĿ¼���Ҳ������ļ������鷵����һ��\n");
		return ERROR;
	}
}







///////////////////////////////////////////////////////////////////////////////////////////




//�ı�·�������骣�
//////////////////////////////////////////////////////////////////////////////////////////




//������
/*
Status PATH_return(FolderTreePtr F_T, FolderPtr* F_path)//F_pathΪ��ǰ·��
{
	//�Ƚ��е�ǰĿ¼�Ƿ�Ϊ��Ŀ¼���ж�
	if (F_T->root == *F_path)
	{
		printf("��ǰ·���Ѿ��Ǹ�Ŀ¼��\n");
		return ERROR;
	}
	//ʹ�ñ����������м����ж�
	LQueue* Q = NULL;
	Queue_Init(&Q);//��������
	Queue_In(&Q, F_T->root);//���ڵ����
	FolderPtr node, f;	//f��node��˫��
	while (!Queue_Empty(Q))
	{
		node = Queue_Front(Q);
		if (!node)
		{
			Queue_Out(&Q);
			continue;
		}
		if (node == *F_path)	//nodeΪ��ǰ·��������ѭ��
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
	if ( f != NULL)//���ڽ��
	{
		(*F_path) = f;	//����ǰ·����Ϊnode��˫��
		return TRUE;
	}
	else
		return ERROR;
}
/*
//�޸�·��Ϊ��Ŀ¼
Status PATH_return(FolderTreePtr F_T,FolderPtr *F_path)
{
	//FolderPtr temp=Tree_Traverse0(F_T,*F_path);
	//*F_path=temp;
	return TRUE;
}
*/




//�޸�·��Ϊ��Ŀ¼
Status PATH_next(FolderPtr* F_path, char* title)
{
	//������ң��ȷǿպ�ƥ�䣬�����Һ��Ӳ����Ƿ���Ŀ���ļ���
	if ((*F_path)->left != NULL)	//���ӷǿ�
	{
		if (strcmp((*F_path)->left->folder_title, title) == 0)	//������Ŀ���ļ���
		{
			(*F_path) = (*F_path)->left;	//·��ָ���ƶ�
			return TRUE;
		}
	}
	else if ((*F_path)->right != NULL)	//�Һ��ӷǿ�
	{
		if (strcmp((*F_path)->right->folder_title, title) == 0)	//�Һ�����Ŀ���ļ���
		{
			(*F_path) = (*F_path)->right;	//·��ָ���ƶ�
			return TRUE;
		}
	}
	else
	{
		printf("�ڵ�ǰ·�����Ҳ���Ŀ���ļ��У����鷵����һ��Ŀ¼\n");
		return ERROR;
	}
}




//////////////////////////////////////////////////////////////////////////////////////////



//�ļ����������ƹ㳬��
////////////////////////////////////////////////////////////////////////////////////////////



//FilePtr p = NULL;
Status InitList(FilePtr* p)//��ʼ������
{
	*p = (FilePtr)malloc(sizeof(File));//��ͷ������һ���ڴ�ռ�
	if ((*p) == NULL)
		return ERROR;
	if ((*p) != NULL) {
		(*p)->next = NULL;
		strcpy((*p)->file_title, "\0");
		int i;
		for (i = 0; i < 5; i++) {
			strcpy((*p)->file_tag[i].tag_node, "\0");
		}
		// printf("��ʼ���ɹ���\n");////////////////�Ұ����ע�͵�
	}

	return TRUE;

}
/*void TraverseList(FilePtr p)
{
	FilePtr p0 = p;//��p0��������;
	do {
		p0 = p0->next;
	} while (p0->next != NULL);
}*/
Status InsertList(FilePtr p, char* file_name)//����ͷ���ָ����ļ���
{
	if (p == NULL) {
		return ERROR;
	}
	FilePtr k = p;//kָ���β��q���������½�����
	while (k->next != NULL) {
		k = k->next;
	}
	FilePtr	q = (FilePtr)malloc(sizeof(File));//////////�Ұ�sizeof()����ĸĵ�
	int i;
	for (i = 0; i < 5; i++) {
		strcpy(q->file_tag[i].tag_node, "\0");
	}
	strcpy(q->file_title, file_name);
	k->next = q;
	q->next = NULL;
	return TRUE;

}

Status AddTag(FilePtr p, char* file_title, char* TagNode)//��ÿһ��tag�����жϣ���Ϊ�������ּ���
{
	if (p == NULL)
		return ERROR;

	FilePtr q = searchByName(p, file_title);
	if (q == NULL) {
		printf("δ�ҵ�ָ���ļ�\n");
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
		while (1) {//�����ǩ  scanf("%s",q->file_tag[i].tag_node, 19)
			//while (getchar() != '\n');
			printf("��ѡ���Ƿ������ӱ�ǩ:1.��ӣ�2ȡ��");
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

Status DestoryList(FilePtr* p) {//��������
	if ((*p) == NULL)
		return ERROR;
	FilePtr p1;
	do {
		p1 = *p;
		(*p) = (*p)->next;
		free(p1);
	} while (*p != NULL);
	p1 = NULL;
	p = NULL;		//����һǰһ������ָ���������н��
	printf("�����ѳɹ����٣�\n");
	return TRUE;
}

Status DeleteByName(FilePtr p, char* file_name) {//�����ļ���ɾ��
	FilePtr L = p;
	FilePtr q = p->next;
	while (q != NULL && strcmp(q->file_title, file_name)) {//q�������һ������ûƥ�䵽�ļ�����
		L = q;
		q = q->next;
	}
	if (strcmp(q->file_title, file_name) == 0)
	{
		L->next = q->next;
		free(q);
		q = NULL;
		printf("ɾ���ɹ���");
		return TRUE;
	}
	return ERROR;
	/*else
	{
		L->next = q->next;
		free(q);
		q = NULL;
		printf("ɾ���ɹ���");
	}*/


}
Status DeletebyTag(FilePtr p, char* tag_Name)//���ݱ�ǩ��ɾ��
{
	if (p == NULL) {
		return ERROR;
	}
	FilePtr L = p;
	FilePtr q = p->next;
	int i;
	for (i = 0; i < 5; i++) {
		while (q != NULL && strcmp(q->file_tag[i].tag_node, tag_Name)) {//q�������һ������ûƥ�䵽��ǩ����
			L = q;
			q = q->next;
		}
		if (q != NULL && strcmp(q->file_tag[i].tag_node, tag_Name) == 0)
		{
			L->next = q->next;
			free(q);
			q = NULL;
			//printf("ɾ���ɹ���");
			//return TRUE;
		}
		else if (q == NULL) {
			return ERROR;
		}
	}

	return
		TRUE;
}


FilePtr searchByName(FilePtr p, char* file_name)//�����ļ�������
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
		while (q != NULL && strcmp(q->file_tag[i].tag_node, tag_Name)) {//q�������һ������ûƥ�䵽�ļ�����
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
		printf("�ļ���\t%s\t\n", s->file_title);
		int i;
		for (i = 0; i < 5; i++) {
			printf("��ǩ\t%s\n", s->file_tag[i].tag_node);
		}
		s = s->next;
	}
	return TRUE;
}

Status ReName(FilePtr p, char* PreFile_title, char* NewFile_title) {//������
	FilePtr q = searchByName(p, PreFile_title);//�Ҳ������ش���
	if (q == NULL) {
		printf("δ�ҵ�ָ���ļ�\n");
		return ERROR;
	}
	strcpy(q->file_title, "\0");//�����
	strcpy(q->file_title, NewFile_title);//�ٸ���
	return TRUE;

}



//////////////////////////////////////////////////////////////////////////////////////////////

