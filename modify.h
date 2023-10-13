void set_student_password(int cfd, int id){
	struct student stu;
	struct message msg;
	int rb, wb;

	write_msg(cfd,1,2,"\nEnter/ Set New Password: # ");
	read_msg(cfd,&msg);

	stu=get_student_details(id);
	if(stu.stud_id==-1){
		write_msg(cfd,0,1,"\nInvalid Student-Id...");
		return;
	}
	bzero(stu.stud_password,sizeof(stu.stud_password));
	strcpy(stu.stud_password,msg.body);

	bool status=set_student_details(id,&stu);
	if(status==0){
		write_msg(cfd,0,1,"\nPassword Setting Failed...");
	}
	else{
		write_msg(cfd,0,1,"\nPassword Set Successfully...");
	}
}

	
void set_faculty_password(int cfd, int id){
	struct faculty fac;
	struct message msg;
	int rb, wb;

	write_msg(cfd,1,2,"\nEnter/ Set New Password: # ");
	read_msg(cfd,&msg);

	fac=get_faculty_details(id);
	if(fac.faculty_id==-1){
		write_msg(cfd,0,1,"\nInvalid Faculty-Id...");
		return;
	}
	bzero(fac.faculty_password,sizeof(fac.faculty_password));
	strcpy(fac.faculty_password,msg.body);

	bool status=set_faculty_details(id,&fac);
	if(status==0){
		write_msg(cfd,0,1,"\nPassword Setting Failed...");
	}
	else{
		write_msg(cfd,0,1,"\nPassword Set Successfully...");
	}
}

void modify_student_details(int cfd){
	struct student stu;
	struct message msg;
	int rb, wb;

	write_msg(cfd,1,0,"\nEnter Student-Id: ");
	read_msg(cfd,&msg);
	int id=atoi(msg.body);
	stu=get_student_details(id);
	if(stu.stud_id==-1){
		write_msg(cfd,0,1,"\nInvalid Student-Id...");
		return;
	}
	// Getting New Details
	write_msg(cfd,1,1,"\nEnter New Name: ");
	read_msg(cfd,&msg);

	strcpy(stu.stud_name,msg.body);



	write_msg(cfd,1,0,"\nEnter New Gender: ");
	read_msg(cfd,&msg);

	stu.stud_gender=msg.body[0];

	write_msg(cfd,1,1,"\nEnter New Phone Number: ");
	read_msg(cfd,&msg);

	strcpy(stu.stud_phone,msg.body);

	write_msg(cfd,1,1,"\nEnter New email: ");
	read_msg(cfd,&msg);

	strcpy(stu.stud_email,msg.body);

	write_msg(cfd,1,1,"\nEnter New Address: ");
	read_msg(cfd,&msg);

	strcpy(stu.stud_address,msg.body);

	write_msg(cfd,1,2,"\nEnter New Password: # ");
	read_msg(cfd,&msg);

	strcpy(stu.stud_password,msg.body);


	bool status=set_student_details(id,&stu);
	if(status==0){
		write_msg(cfd,0,1,"\nUpdation Failed...");
	}
	else{
		write_msg(cfd,0,1,"\nDetails Updated Successfully...");
	}	
}


void modify_faculty_details(int cfd){
	struct faculty fac;
	struct message msg;
	int rb, wb;

	write_msg(cfd,1,0,"\nEnter Faculty-Id: ");
	read_msg(cfd,&msg);
	int id=atoi(msg.body);
	fac=get_faculty_details(id);
	if(fac.faculty_id==-1){
		write_msg(cfd,0,1,"\nInvalid Faculty-Id...");
		return;
	}
	// Getting New Details
	write_msg(cfd,1,1,"\nEnter New Name: ");
	read_msg(cfd,&msg);

	strcpy(fac.faculty_name,msg.body);



	write_msg(cfd,1,0,"\nEnter New Gender: ");
	read_msg(cfd,&msg);

	fac.faculty_gender=msg.body[0];
	write_msg(cfd,1,1,"\nEnter New Phone Number: ");
	read_msg(cfd,&msg);

	strcpy(fac.faculty_phone,msg.body);
	
	write_msg(cfd,1,1,"\nEnter New email: ");
	read_msg(cfd,&msg);

	strcpy(fac.faculty_email,msg.body);

	write_msg(cfd,1,1,"\nEnter New Address: ");
	read_msg(cfd,&msg);

	strcpy(fac.faculty_address,msg.body);

	write_msg(cfd,1,2,"\nEnter New Password: # ");
	read_msg(cfd,&msg);

	strcpy(fac.faculty_password,msg.body);


	bool status=set_faculty_details(id,&fac);
	if(status==0){
		write_msg(cfd,0,1,"\nUpdation Failed...");
	}
	else{
		write_msg(cfd,0,1,"\nDetails Updated Successfully...");
	}
}


