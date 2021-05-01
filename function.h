#pragma once

typedef enum {
	ERROR=0,TRUE=1

}Status;




//标签结构体 
typedef struct tag
{
	char tag_node[20];			//一个标签
}Tag;



//文件单链表 
typedef struct file
{
	char file_title[50];		//文件名
	Tag file_tag[5];			//文件标签（最多5个） 
	struct file* next;			//下一结点
}File, * FilePtr;



//文件夹二叉树 
typedef struct folder
{
	char folder_title[51];		//文件夹名
	Tag folder_tag[5];			//文件夹标签（最多5个）
	FilePtr file_head;			//文件头指针（文件，若无文件=NULL）、
	struct folder* left, * right;	//左右孩子结点
}Folder, * FolderPtr;




//二叉树根 
typedef struct folderhead
{
	FolderPtr root;				//根节点
}FolderTree, * FolderTreePtr;





//用户单链表
typedef struct user
{
	char user_name[31];			//用户名
	char user_password[31];		//密码
	char user_id[31];			//证件号码
	struct user* user_next;     //下一个用户
	FolderTreePtr user_folder;	//用户的根目录
}User, * UserPtr;



extern User* user;//用户链表头指针
extern FolderPtr Q_p;

void build_dir(User* newn);//注册时初始化目录
Status DIR_init(FolderTreePtr* F_T);//文件目录树初始化
Status DIR_insert(FolderPtr);//文件夹插入


User* user_name_search(User* user_temp, char* name_input);
User* user_id_search(User* user_temp, char* id_input);




//页面设计函数


/////////////////////////////////////////////////////////////////////////////////////////////////////

void HideCursor();    //隐藏光标
void toxy(int x, int y);    //将光标移动到X,Y坐标处
void color(short x);     //设置颜色


//////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////



FolderPtr Find_folder(FolderTreePtr F_T, char* name);
Status Tree_Traverse(FolderTreePtr F_T, void (*fvisit)(FolderPtr q));
void visit(FolderPtr p);//打印结点；

//功能队列

typedef struct Qnode
{
	FolderPtr pdata;                   //数据域指针
	struct Qnode* Qnext;            //指向当前结点的下一结点
} QNode;


typedef struct Lqueue
{
	QNode* front;                   //队头
	QNode* rear;                    //队尾
	size_t length;            //队列长度
} LQueue;



//初始化队列
Status Queue_Init(LQueue** q);
//判断队列是否为空
Status Queue_Empty(LQueue* q);
//进队
Status Queue_In(LQueue** q, FolderPtr BNode);
//出队
Status Queue_Out(LQueue** q);
//队头
FolderPtr Queue_Front(LQueue* q);



//真实文件操作（吴滨楠）
////////////////////////////////////////////////////////////////////////////////////////




//folder.c

Status CreateFolder(char* folderTitle);				//创建文件夹
Status ReturnFolder();						//将路径切换为当前目录的父目录
Status ChangeFolder(char* folderTitle);				//将路径切换为命令中输入的文件夹路径
Status PrintFolder();						//打印当前路径	/*没做要求的*/

//file.c

Status CreateFile(char* fileTitle);			//创建文件
Status DeleteFile(char* fileTitle);			//删除文件
Status RenameFile(char* fileTitle, char* newfileTitle);	//重命名文件


//command.c

Status SplitCommand(char *str,char *order,char *title0,char *title1);	//切割指令
Status IsCommand(char* title);




////////////////////////////////////////////////////////////////////////////////////




//文件夹树操作（吴滨楠）
////////////////////////////////////////////////////////////////////////////////////

Status DIR_insert(FolderPtr F_path, char* title);			//新建文件夹
Status DIR_delete(FolderPtr F_path, char* title);			//删除文件夹（及里面的文件夹和文件）
Status DIR_destroy(FolderPtr p);					//销毁二叉树（删除文件夹的辅助函数）
Status DIR_move(FolderPtr F_path, char* oldtitle, char* newtitle);	//移动文件夹



/////////////////////////////////////////////////////////////////////////////////////

//文件链表操作（吴滨楠）
/////////////////////////////////////////////////////////////////////////////////////

Status FILE_insert(FolderPtr F_path, char* title);				//新建文件
Status FILE_delete(FolderPtr F_path, char* title);				//删除文件
Status FILE_move(FolderPtr F_path, char* file_title, char* folder_title);		//移动文件
Status FILE_rename(FolderPtr F_path, char* oldtitle, char* newtitle);		//重命名文件

//////////////////////////////////////////////////////////////////////////////////////

//路径修改（吴滨楠）
//Status PATH_return(FolderTreePtr F_T, FolderPtr* F_path);	//修改路径为父目录
Status PATH_next(FolderPtr* F_path, char* title);		//修改路径为子目录



//文件链表（黄广超）
Status InitList(FilePtr* p);						//初始化
Status InsertList(FilePtr p, char* file_name);				//插入
Status DestoryList(FilePtr* p);						//销毁链表
Status DeleteByName(FilePtr p, char* file_title);			//按文件名删除
Status printList(FilePtr p);						//打印所有文件名
FilePtr searchByName(FilePtr p, char* file_title);			//按名字查找
Status AddTag(FilePtr p, char* file_title, char* TagNode);		//添加标签
Status ReName(FilePtr p, char* PreFile_title, char* NewFile_title);	//重命名




Status deldir(char* p);

//改变文件路径路径
Status mvfile(char* p);



//FolderTag.c
Status AddFolderTag(FolderTreePtr F_T, char* folder_title, char* TagNode);
FolderPtr SearchByTag_Names(FolderTreePtr F_T, char* TagNode);
FolderPtr SearchByTag_Namesa(FolderPtr F_T, char* TagNode);