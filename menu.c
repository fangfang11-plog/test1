#include<stdio.h>
#include<string.h>
#include"menu.h"
#include"function.h"



//用户界面
void user_menu() {

	do {
		color(11);
		HideCursor();
		toxy(45, 6);
		printf("      欢迎来到笔记管理系统        ");
		toxy(45, 8);

		printf("|          1.登陆系统         |");
		toxy(45, 10);

		printf("|          2.注册账号         |");
		toxy(45, 12);

		printf("|          3.找回密码         |");
		toxy(45, 12);

		printf("|          4.退出软件         |");
		toxy(45, 14);
		char temp = _getch();
		system("cls");
		switch (temp) {
		case'1':Login_menu(); break;
		case'2':Register_menu(); break;
		case'3':back_cipher(); break;
		case'4':exit(1); break;
		}

	} while (1);

}



//登录界面
void Login_menu() {
	if (user == NULL) {
		toxy(48, 9);
		printf("系统中还未存在账号，建议返回建立后重试");
		_getch();
	}
	else {
		toxy(48, 9);

		printf("请输入用户名：");

		char name_input[31] = { '\0' };
		scanf_s("%s", name_input, 30);
		User* traverse = NULL;
		traverse = user_name_search(user, name_input);
		if (traverse == NULL) {//用户链表中检测是否存在该用户
			toxy(48, 9);
			printf("用户名不存在，请检查后重试");
			_getch();

			user_menu();
		}
		else {
			char cipher_input[31] = { '\0' };
			toxy(48, 10);
			printf("请输入密码：");
			scanf_s("%s", cipher_input, 30);

			if (strcmp(traverse->user_password, cipher_input) != 0) {//比较密码是否正确
				toxy(48, 9);
				printf("账号或密码错误...");
				toxy(48, 10);
				printf("现在返回登录界面...");
				_getch();
				user_menu();
			}
			else {
				toxy(48, 9);
				printf("登陆成功");
				_getch();
				menu_main(traverse);

			}

		}

	}

}



//主操作界面
void menu_main(User* nown) {

	char str[101] = { '\0' };				//用户输入整个指令
	char order[21] = { '\0' };				//指令
	char title0[51] = { '\0' }, title1[51] = { '\0' };	//文件名

	ChangeFolder(nown->user_folder->root);
	Q_p = nown->user_folder->root;

	while (1)
	{
		color(11);
		printf("请输入指令：");
		scanf_s("%s", str,100);

		SplitCommand(str, order, title0, title1);	//调用切割函数
		if (strcmp(order, "IS") == 0&&title0[0]=='\0') 
		{
			system("dir"); 
		}
		else if (strcmp(order,"IS-a")==0) {
			
			system("tree /f");

		}
		else if (strcmp(order, "IS")==0&&title0[0]!='\0') {

			char cmd[255] = { 'd','i','r' };
			strcat_s(cmd, title0,51);
			system(cmd);

		}
		else if (strcmp(order, "mkdir-r") == 0)
		{
			CreateFolder(title0);		//调用创建文件夹函数
			DIR_insert(Q_p, title0);    //文件夹插入

		}
		else if (strcmp(order, "mkdir") == 0)
		{
			CreateFile(title0);		//调用创建文件函数
			FILE_insert(Q_p, title0);//树的模拟插入文件

		}
		else if (strcmp(order, "rm") == 0)
		{

			DeleteFile(title0);		//调用删除文件函数
			FILE_delete(Q_p, title0);
		}
		else if (strcmp(order, "rm-r") == 0) 
		{

			deldir(str);
			DIR_delete(Q_p, title0);

		}
		else if (strcmp(order,"mv") == 0&&check_dot(title1) == 0) 
		{

			mvfile(str);//真实
			FILE_move(Q_p,title0,title1);

		}
		else if (strcmp(order, "mv-r")==0) 
		{
		
			DIR_move(Q_p, title0, title1);
		
		}
		else if (strcmp(order, "mv") == 0&&check_dot(title1) == 1)
		{

			RenameFile(title0, title1);	//重命名文件
			FILE_rename(Q_p, title0, title1);

		}
		else if (strcmp(order, "cd..") == 0)
		{

			ReturnFolder();			//切换路径为父目录

		}
		else if (strcmp(order, "cd") == 0)
		{
			PATH_next(Q_p, title0);
				//移动全局变量指针
			ChangeFolder(title0);		//切换路径为子目录
		}
		else if (strcmp(order,"tag")==0) 
		{


		}
		else if (strcmp(order,"tag-add")==0) 
		{

			AddFolderTag(nown->user_folder, title0, title1);

		}
		else if (strcmp(order,"tag-del")==0) 
		{




		}
		else if (strcmp(order, "tag-s") == 0) 
		{

			SearchByTag_Names(nown->user_folder, title1);

		}
		else if (strcmp(order,"tag-sa")==0) 
		{

			SearchByTag_Namesa(nown->user_folder, title1);

		}
		else if (strcmp(order,"")==0) {




		}
		else if (strcmp(order, "over") == 0)
		{

			printf("成功退出程序\n");
			break;
		}
		else
		{
			printf("指令格式有误，请重新输入\n");
		}
		system("pause");
		system("cls");
	}




}



//注册界面
void Register_menu() {

	printf("欢迎来到注册界面");
	printf("请输入用户ID:");
	char id_input[31] = { '\0' };
	scanf_s("%s", id_input, 30);
	User* traverse = NULL;

	//用户链表中检测是否存在该用户ID,存在时返回错误，重新进行注册
	traverse = user_id_search(user, id_input);
	if (traverse != NULL) {
		printf("用户ID已存在");
		Register_menu();
	}

	traverse = NULL;//方便再次检测
	printf("请输入要注册的用户名：");
	char name_input[31] = { '\0' };
	scanf_s("%s", name_input, 30);

	//用户链表中检测是否存在该用户ID,存在时返回错误，重新进行注册	
	traverse = user_name_search(user, name_input);
	if (traverse != NULL) {
		printf("用户名已存在");
		Register_menu();
	}

	char cipher_input[31] = { '\0' };
	char cipher_repeat[31] = { '\0' };
	printf("请输入注册密码：");
	scanf_s("%s", cipher_input, 30);
	printf("请再次输入密码");
	scanf_s("%s", cipher_repeat, 30);
	if (strcmp(cipher_input, cipher_repeat) != 0) {
		printf("两次输入密码不一致，请检查输入");
		Register_menu();
	}

	User* newn = user_insert();
	int i = 0;
	while (id_input[i] != '\0') {//读入ID数据
		newn->user_id[i] = id_input[i];
		i++;
	}
	newn->user_id[i] = '\0';
	i = 0;
	while (name_input[i] != '\0') {//读入用户名数据
		newn->user_name[i] = name_input[i];
		i++;
	}
	newn->user_name[i] = '\0';

	i = 0;
	while (cipher_input[i] != '\0')//读入密码数据
	{
		newn->user_password[i] = cipher_input[i];
		i++;
	}
	newn->user_password[i] = '\0';
	printf("注册成功");
	build_dir(newn);
	user_menu();
}



//找回密码界面 ID与用户名匹配时可找回密码
void back_cipher() {
	if (user == NULL) {
		printf("系统中还未存在账号，建议返回建立后重试");

	}
	else {

		printf("欢迎来到找回密码界面");
		printf("请输入找回的用户ID:");
		char id_input[31] = { '\0' };
		scanf_s("%s", id_input, 30);
		User* traverse = NULL;

		//用户链表中检测是否存在该用户ID,存在时返回错误，重新进行注册
		traverse = user_id_search(user, id_input);
		if (traverse == NULL) {
			printf("用户ID不存在，请检查输入是否错误");
			printf("现在返回用户界面");
			Register_menu();

		}
		else {//成功找到ID时进入

			printf("请输入对应用户名：");
			char name_input[31] = { '\0' };
			scanf_s("%s", name_input, 30);

			//用户链表中检测是否存在该用户ID,存在时返回错误，重新进行注册	
			if (strcmp(traverse->user_name, name_input) != 0) {
				printf("ID与用户不匹配");
				printf("现在返回用户界面");
				Register_menu();
			}
			else {//用户名与ID匹配时进入
				printf("您的旧密码为：%s", traverse->user_password);

			}

		}

	}

}




//初次登陆对工作目录进行设定，此处需要进行建立真实根目录操作
void build_dir(User* newn) {
	newn->user_folder = NULL;
	if (DIR_init(&newn->user_folder) == 0)//初始化文件目录
	{
		printf("文件目录初始化失败");

	}
	else {//进行对工作目录命名

		newn->user_folder->root = (FolderPtr)malloc(sizeof(Folder));
		if (!newn->user_folder->root)exit(0);

		printf("请输入你的工作目录名：");
		scanf_s("%s", newn->user_folder->root->folder_title, 50);
		CreateFolder(newn->user_folder->root->folder_title);
		printf("请输入工作目录标签：");
		int i = 0;
		i = 0;
		while (scanf_s("%s", newn->user_folder->root->folder_tag[i].tag_node, 19)) {//输入标签
			while (getchar() != '\n');
			printf("请选择是否继续添加标签:1.添加，2取消");
			i++;
			char temp;
			scanf_s("%c", &temp);
			if (temp == '2' || i > 5) {
				break;
			}

		}
		newn->user_folder->root->left = NULL;
		newn->user_folder->root->right = NULL;
		newn->user_folder->root->file_head = NULL;
		printf("工作目录初始化成功");
	}
}



