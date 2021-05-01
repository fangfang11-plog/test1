#pragma once

typedef enum {
	ERROR=0,TRUE=1

}Status;




//��ǩ�ṹ�� 
typedef struct tag
{
	char tag_node[20];			//һ����ǩ
}Tag;



//�ļ������� 
typedef struct file
{
	char file_title[50];		//�ļ���
	Tag file_tag[5];			//�ļ���ǩ�����5���� 
	struct file* next;			//��һ���
}File, * FilePtr;



//�ļ��ж����� 
typedef struct folder
{
	char folder_title[51];		//�ļ�����
	Tag folder_tag[5];			//�ļ��б�ǩ�����5����
	FilePtr file_head;			//�ļ�ͷָ�루�ļ��������ļ�=NULL����
	struct folder* left, * right;	//���Һ��ӽ��
}Folder, * FolderPtr;




//�������� 
typedef struct folderhead
{
	FolderPtr root;				//���ڵ�
}FolderTree, * FolderTreePtr;





//�û�������
typedef struct user
{
	char user_name[31];			//�û���
	char user_password[31];		//����
	char user_id[31];			//֤������
	struct user* user_next;     //��һ���û�
	FolderTreePtr user_folder;	//�û��ĸ�Ŀ¼
}User, * UserPtr;



extern User* user;//�û�����ͷָ��
extern FolderPtr Q_p;

void build_dir(User* newn);//ע��ʱ��ʼ��Ŀ¼
Status DIR_init(FolderTreePtr* F_T);//�ļ�Ŀ¼����ʼ��
Status DIR_insert(FolderPtr);//�ļ��в���


User* user_name_search(User* user_temp, char* name_input);
User* user_id_search(User* user_temp, char* id_input);




//ҳ����ƺ���


/////////////////////////////////////////////////////////////////////////////////////////////////////

void HideCursor();    //���ع��
void toxy(int x, int y);    //������ƶ���X,Y���괦
void color(short x);     //������ɫ


//////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////



FolderPtr Find_folder(FolderTreePtr F_T, char* name);
Status Tree_Traverse(FolderTreePtr F_T, void (*fvisit)(FolderPtr q));
void visit(FolderPtr p);//��ӡ��㣻

//���ܶ���

typedef struct Qnode
{
	FolderPtr pdata;                   //������ָ��
	struct Qnode* Qnext;            //ָ��ǰ������һ���
} QNode;


typedef struct Lqueue
{
	QNode* front;                   //��ͷ
	QNode* rear;                    //��β
	size_t length;            //���г���
} LQueue;



//��ʼ������
Status Queue_Init(LQueue** q);
//�ж϶����Ƿ�Ϊ��
Status Queue_Empty(LQueue* q);
//����
Status Queue_In(LQueue** q, FolderPtr BNode);
//����
Status Queue_Out(LQueue** q);
//��ͷ
FolderPtr Queue_Front(LQueue* q);



//��ʵ�ļ����������骣�
////////////////////////////////////////////////////////////////////////////////////////




//folder.c

Status CreateFolder(char* folderTitle);				//�����ļ���
Status ReturnFolder();						//��·���л�Ϊ��ǰĿ¼�ĸ�Ŀ¼
Status ChangeFolder(char* folderTitle);				//��·���л�Ϊ������������ļ���·��
Status PrintFolder();						//��ӡ��ǰ·��	/*û��Ҫ���*/

//file.c

Status CreateFile(char* fileTitle);			//�����ļ�
Status DeleteFile(char* fileTitle);			//ɾ���ļ�
Status RenameFile(char* fileTitle, char* newfileTitle);	//�������ļ�


//command.c

Status SplitCommand(char *str,char *order,char *title0,char *title1);	//�и�ָ��
Status IsCommand(char* title);




////////////////////////////////////////////////////////////////////////////////////




//�ļ��������������骣�
////////////////////////////////////////////////////////////////////////////////////

Status DIR_insert(FolderPtr F_path, char* title);			//�½��ļ���
Status DIR_delete(FolderPtr F_path, char* title);			//ɾ���ļ��У���������ļ��к��ļ���
Status DIR_destroy(FolderPtr p);					//���ٶ�������ɾ���ļ��еĸ���������
Status DIR_move(FolderPtr F_path, char* oldtitle, char* newtitle);	//�ƶ��ļ���



/////////////////////////////////////////////////////////////////////////////////////

//�ļ�������������骣�
/////////////////////////////////////////////////////////////////////////////////////

Status FILE_insert(FolderPtr F_path, char* title);				//�½��ļ�
Status FILE_delete(FolderPtr F_path, char* title);				//ɾ���ļ�
Status FILE_move(FolderPtr F_path, char* file_title, char* folder_title);		//�ƶ��ļ�
Status FILE_rename(FolderPtr F_path, char* oldtitle, char* newtitle);		//�������ļ�

//////////////////////////////////////////////////////////////////////////////////////

//·���޸ģ����骣�
//Status PATH_return(FolderTreePtr F_T, FolderPtr* F_path);	//�޸�·��Ϊ��Ŀ¼
Status PATH_next(FolderPtr* F_path, char* title);		//�޸�·��Ϊ��Ŀ¼



//�ļ������ƹ㳬��
Status InitList(FilePtr* p);						//��ʼ��
Status InsertList(FilePtr p, char* file_name);				//����
Status DestoryList(FilePtr* p);						//��������
Status DeleteByName(FilePtr p, char* file_title);			//���ļ���ɾ��
Status printList(FilePtr p);						//��ӡ�����ļ���
FilePtr searchByName(FilePtr p, char* file_title);			//�����ֲ���
Status AddTag(FilePtr p, char* file_title, char* TagNode);		//��ӱ�ǩ
Status ReName(FilePtr p, char* PreFile_title, char* NewFile_title);	//������




Status deldir(char* p);

//�ı��ļ�·��·��
Status mvfile(char* p);



//FolderTag.c
Status AddFolderTag(FolderTreePtr F_T, char* folder_title, char* TagNode);
FolderPtr SearchByTag_Names(FolderTreePtr F_T, char* TagNode);
FolderPtr SearchByTag_Namesa(FolderPtr F_T, char* TagNode);