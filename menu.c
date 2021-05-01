#include<stdio.h>
#include<string.h>
#include"menu.h"
#include"function.h"



//�û�����
void user_menu() {

	do {
		color(11);
		HideCursor();
		toxy(45, 6);
		printf("      ��ӭ�����ʼǹ���ϵͳ        ");
		toxy(45, 8);

		printf("|          1.��½ϵͳ         |");
		toxy(45, 10);

		printf("|          2.ע���˺�         |");
		toxy(45, 12);

		printf("|          3.�һ�����         |");
		toxy(45, 12);

		printf("|          4.�˳����         |");
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



//��¼����
void Login_menu() {
	if (user == NULL) {
		toxy(48, 9);
		printf("ϵͳ�л�δ�����˺ţ����鷵�ؽ���������");
		_getch();
	}
	else {
		toxy(48, 9);

		printf("�������û�����");

		char name_input[31] = { '\0' };
		scanf_s("%s", name_input, 30);
		User* traverse = NULL;
		traverse = user_name_search(user, name_input);
		if (traverse == NULL) {//�û������м���Ƿ���ڸ��û�
			toxy(48, 9);
			printf("�û��������ڣ����������");
			_getch();

			user_menu();
		}
		else {
			char cipher_input[31] = { '\0' };
			toxy(48, 10);
			printf("���������룺");
			scanf_s("%s", cipher_input, 30);

			if (strcmp(traverse->user_password, cipher_input) != 0) {//�Ƚ������Ƿ���ȷ
				toxy(48, 9);
				printf("�˺Ż��������...");
				toxy(48, 10);
				printf("���ڷ��ص�¼����...");
				_getch();
				user_menu();
			}
			else {
				toxy(48, 9);
				printf("��½�ɹ�");
				_getch();
				menu_main(traverse);

			}

		}

	}

}



//����������
void menu_main(User* nown) {

	char str[101] = { '\0' };				//�û���������ָ��
	char order[21] = { '\0' };				//ָ��
	char title0[51] = { '\0' }, title1[51] = { '\0' };	//�ļ���

	ChangeFolder(nown->user_folder->root);
	Q_p = nown->user_folder->root;

	while (1)
	{
		color(11);
		printf("������ָ�");
		scanf_s("%s", str,100);

		SplitCommand(str, order, title0, title1);	//�����и��
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
			CreateFolder(title0);		//���ô����ļ��к���
			DIR_insert(Q_p, title0);    //�ļ��в���

		}
		else if (strcmp(order, "mkdir") == 0)
		{
			CreateFile(title0);		//���ô����ļ�����
			FILE_insert(Q_p, title0);//����ģ������ļ�

		}
		else if (strcmp(order, "rm") == 0)
		{

			DeleteFile(title0);		//����ɾ���ļ�����
			FILE_delete(Q_p, title0);
		}
		else if (strcmp(order, "rm-r") == 0) 
		{

			deldir(str);
			DIR_delete(Q_p, title0);

		}
		else if (strcmp(order,"mv") == 0&&check_dot(title1) == 0) 
		{

			mvfile(str);//��ʵ
			FILE_move(Q_p,title0,title1);

		}
		else if (strcmp(order, "mv-r")==0) 
		{
		
			DIR_move(Q_p, title0, title1);
		
		}
		else if (strcmp(order, "mv") == 0&&check_dot(title1) == 1)
		{

			RenameFile(title0, title1);	//�������ļ�
			FILE_rename(Q_p, title0, title1);

		}
		else if (strcmp(order, "cd..") == 0)
		{

			ReturnFolder();			//�л�·��Ϊ��Ŀ¼

		}
		else if (strcmp(order, "cd") == 0)
		{
			PATH_next(Q_p, title0);
				//�ƶ�ȫ�ֱ���ָ��
			ChangeFolder(title0);		//�л�·��Ϊ��Ŀ¼
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

			printf("�ɹ��˳�����\n");
			break;
		}
		else
		{
			printf("ָ���ʽ��������������\n");
		}
		system("pause");
		system("cls");
	}




}



//ע�����
void Register_menu() {

	printf("��ӭ����ע�����");
	printf("�������û�ID:");
	char id_input[31] = { '\0' };
	scanf_s("%s", id_input, 30);
	User* traverse = NULL;

	//�û������м���Ƿ���ڸ��û�ID,����ʱ���ش������½���ע��
	traverse = user_id_search(user, id_input);
	if (traverse != NULL) {
		printf("�û�ID�Ѵ���");
		Register_menu();
	}

	traverse = NULL;//�����ٴμ��
	printf("������Ҫע����û�����");
	char name_input[31] = { '\0' };
	scanf_s("%s", name_input, 30);

	//�û������м���Ƿ���ڸ��û�ID,����ʱ���ش������½���ע��	
	traverse = user_name_search(user, name_input);
	if (traverse != NULL) {
		printf("�û����Ѵ���");
		Register_menu();
	}

	char cipher_input[31] = { '\0' };
	char cipher_repeat[31] = { '\0' };
	printf("������ע�����룺");
	scanf_s("%s", cipher_input, 30);
	printf("���ٴ���������");
	scanf_s("%s", cipher_repeat, 30);
	if (strcmp(cipher_input, cipher_repeat) != 0) {
		printf("�����������벻һ�£���������");
		Register_menu();
	}

	User* newn = user_insert();
	int i = 0;
	while (id_input[i] != '\0') {//����ID����
		newn->user_id[i] = id_input[i];
		i++;
	}
	newn->user_id[i] = '\0';
	i = 0;
	while (name_input[i] != '\0') {//�����û�������
		newn->user_name[i] = name_input[i];
		i++;
	}
	newn->user_name[i] = '\0';

	i = 0;
	while (cipher_input[i] != '\0')//������������
	{
		newn->user_password[i] = cipher_input[i];
		i++;
	}
	newn->user_password[i] = '\0';
	printf("ע��ɹ�");
	build_dir(newn);
	user_menu();
}



//�һ�������� ID���û���ƥ��ʱ���һ�����
void back_cipher() {
	if (user == NULL) {
		printf("ϵͳ�л�δ�����˺ţ����鷵�ؽ���������");

	}
	else {

		printf("��ӭ�����һ��������");
		printf("�������һص��û�ID:");
		char id_input[31] = { '\0' };
		scanf_s("%s", id_input, 30);
		User* traverse = NULL;

		//�û������м���Ƿ���ڸ��û�ID,����ʱ���ش������½���ע��
		traverse = user_id_search(user, id_input);
		if (traverse == NULL) {
			printf("�û�ID�����ڣ����������Ƿ����");
			printf("���ڷ����û�����");
			Register_menu();

		}
		else {//�ɹ��ҵ�IDʱ����

			printf("�������Ӧ�û�����");
			char name_input[31] = { '\0' };
			scanf_s("%s", name_input, 30);

			//�û������м���Ƿ���ڸ��û�ID,����ʱ���ش������½���ע��	
			if (strcmp(traverse->user_name, name_input) != 0) {
				printf("ID���û���ƥ��");
				printf("���ڷ����û�����");
				Register_menu();
			}
			else {//�û�����IDƥ��ʱ����
				printf("���ľ�����Ϊ��%s", traverse->user_password);

			}

		}

	}

}




//���ε�½�Թ���Ŀ¼�����趨���˴���Ҫ���н�����ʵ��Ŀ¼����
void build_dir(User* newn) {
	newn->user_folder = NULL;
	if (DIR_init(&newn->user_folder) == 0)//��ʼ���ļ�Ŀ¼
	{
		printf("�ļ�Ŀ¼��ʼ��ʧ��");

	}
	else {//���жԹ���Ŀ¼����

		newn->user_folder->root = (FolderPtr)malloc(sizeof(Folder));
		if (!newn->user_folder->root)exit(0);

		printf("��������Ĺ���Ŀ¼����");
		scanf_s("%s", newn->user_folder->root->folder_title, 50);
		CreateFolder(newn->user_folder->root->folder_title);
		printf("�����빤��Ŀ¼��ǩ��");
		int i = 0;
		i = 0;
		while (scanf_s("%s", newn->user_folder->root->folder_tag[i].tag_node, 19)) {//�����ǩ
			while (getchar() != '\n');
			printf("��ѡ���Ƿ������ӱ�ǩ:1.��ӣ�2ȡ��");
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
		printf("����Ŀ¼��ʼ���ɹ�");
	}
}



