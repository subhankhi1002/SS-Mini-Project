bool admin_login(char* id,char* password){
	struct administrator my_admin;
	my_admin=get_admin_details(0);//default admin credentials
	if(my_admin.id==-1) return 0;
	if(strcmp(id,my_admin.login_id) == 0 && strcmp(password,my_admin.password) == 0)
	return 1;
return 0;
}
bool student_login(char* id,char* password){
	struct student stu;
	stu=get_student_details(atoi(id+6));
	if(stu.stud_id==-1)return 0;
	if(stu.stud_login_status==1) return 0;
	if(strcmp(stu.stud_login_id,id)==0 && strcmp(stu.stud_password,password)==0){
	stu.stud_login_status=0;
	set_student_details(atoi(id+6),&stu);
	return 1;
	}
return 0;
}

bool faculty_login(char* id,char* password){
        struct faculty fac;
        fac=get_faculty_details(atoi(id+2));
        if(fac.faculty_id==-1)return 0;
        if(fac.faculty_login_status==1) return 0;
        if(strcmp(fac.faculty_login_id,id)==0 && strcmp(fac.faculty_password,password)==0){
        fac.faculty_login_status=0;
        set_faculty_details(atoi(id+2),&fac);
        return 1;
        }
	return 0;
}

void login(int cfd,int type){
	struct message msg;
	char id[11];
	char password[11];
	int readBytes, writeBytes;

	//Getting Login_id of the user
	write_msg(cfd,1,0,"\nEnter Login-Id: ");
	read_msg(cfd,&msg);

	strcpy(id,msg.body);
	id[10]='\0';

	//Getting Password of the user
	write_msg(cfd,1,2,"\nEnter Password: ");
	read_msg(cfd,&msg);


	strcpy(password,msg.body); //putting it to variable password
	password[10]='\0';
	
	if(type==0 && admin_login(id,password)){
	write_msg(cfd,0,1,"\nLogin Successful! ");
	//goto menu
	admin_menu(cfd);  //If Admin Login Successful, show admin menu
	}
	else if(type==1 && student_login(id,password)){
	write_msg(cfd,0,1,"\nLogin Successful! "); //If Student Login Successful, show student menu
	
		//goto menu
	student_menu(cfd,atoi(id+6));
	}

	else if(type==2 && faculty_login(id,password)){
	write_msg(cfd,0,1,"\nLogin Successful! ");  //If faculty Login Successful, show faculty menu
	
	//goto menu
	faculty_menu(cfd,atoi(id+5));
	}

	else{
	write_msg(cfd,1,0,"\nLogin Failed:Invalid Details or Already Login...\nDo you want to Try again(Y/N): ");
	read_msg(cfd,&msg);

	if((msg.body[0]=='Y' && msg.body[1]=='\0') || (msg.body[0]=='y' && msg.body[1]=='\0')) 
	login(cfd,type);
	else{
	write_msg(cfd,0,0,"");
	}

}
}
