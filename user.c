#include<stdio.h>
#include"function.h"

User* user;
FolderPtr Q_p;//全局指针跟随路径


//由用户名找用户
User* user_name_search(User* user_temp, char* name_input) {

	if (!user_temp) {
		return NULL;
	}
	else {
		User* p = user_temp;
		while (p) {
			if (strcmp(p->user_name, name_input) == 0) {
				return p;
			}
			else {
				p = p->user_next;
			}
		}
		return NULL;
	}

}


//由用户ID找用户
User* user_id_search(User* user_temp, char* id_input) {

	if (!user_temp) {
		return NULL;
	}
	else {
		User* p = user_temp;
		while (p) {
			if (strcmp(p->user_id, id_input) == 0) {
				return p;
			}
			else {
				p = p->user_next;
			}
		}
		return NULL;
	}

}


//新增用户
User* user_insert() {
	User* newn = (User*)malloc(sizeof(User));
	if (!newn)exit(0);
	if (!user) {
		user = newn;
		user->user_next = NULL;

	}
	else {
		User* p = user;

		while (p->user_next) {
			p = p->user_next;

		}
		p->user_next = newn;
		newn->user_next = NULL;

	}


}





