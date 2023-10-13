void add_faculty(int cfd){
	int faculty_id;
	struct faculty fac;
	struct message msg;
	int rb, wb;

	//Getting details
	write_msg(cfd,1,1,"\nEnter Name: ");
	read_msg(cfd,&msg);

	strcpy(fac.faculty_name,msg.body);




	write_msg(cfd,1,0,"\nEnter Gender: ");
	read_msg(cfd,&msg);
	
	fac.faculty_gender=msg.body[0];

	fac.status=1;

	write_msg(cfd,1,0,"\nEnter Address: ");
	read_msg(cfd,&msg);

	strcpy(fac.faculty_address,msg.body);

	write_msg(cfd,1,0,"\nEnter phone number: ");
	read_msg(cfd,&msg);

	strcpy(fac.faculty_phone,msg.body);

	write_msg(cfd,1,0,"\nEnter email: ");
	read_msg(cfd,&msg);

	strcpy(fac.faculty_email,msg.body);

	write_msg(cfd,1,0,"\nEnter department: ");
	read_msg(cfd,&msg);

	strcpy(fac.faculty_department,msg.body);


	write_msg(cfd,1,2,"\nEnter Password: # ");
	read_msg(cfd,&msg);

	strcpy(fac.faculty_password,msg.body);

	//Initializing...
	strcpy(fac.faculty_login_id,"");
	fac.n_courses_offered=0;
	for(int i=0;i<3;i++)
		fac.courses_offered[i]=-1;
	fac.faculty_login_status=0;
	//Update to file
	faculty_id=save_faculty(&fac);
	if(faculty_id==-1){
		write_msg(cfd,0,1,"\nCannot Save the Faculty...");
		return;
	}
	else{
		write_msg2(cfd,0,1,"\nFaculty Created Successfully!\nNote: Login-Id is iiitb%d\nFaculty-Id %d is Generated",faculty_id);
	}
	//set Login-Id...
	sprintf(fac.faculty_login_id,"iiitb%d",faculty_id);
	bool status=set_faculty_details(faculty_id,&fac);
	if(status==0){
		write_msg(cfd,0,1,"\nLogin-Id Setting Failed...");
	}
	else{
	
		write_msg2(cfd,0,1,"\nLogin-Id Settings Completed Successfully... Login-Id: iiitb%d",faculty_id);

	}

}






void add_new_course(cfd,id){
	int course_id;
	struct course my_course;
	struct message msg;
	int rb, wb;
	struct faculty fac;
	int total_course=get_record_details(0);
	//Getting details
	write_msg(cfd,1,1,"\nEnter course Name: ");
	read_msg(cfd,&msg);

	strcpy(my_course.course_name,msg.body);


	write_msg(cfd,1,0,"\nEnter faculty id: ");
	read_msg(cfd,&msg);

	my_course.faculty_id=msg.body;

	write_msg(cfd,1,0,"\nEnter credits: ");
	read_msg(cfd,&msg);

	my_course.credits=msg.body;

	write_msg(cfd,1,0,"\nEnter total seats: ");
	read_msg(cfd,&msg);

	my_course.total_n_seats=msg.body;

	my_course.avail_n_seats=msg.body;
	my_course.status=1;
	
	fac=get_faculty_details(id);
	
	fac.courses_offered[fac.n_courses_offered]=my_course.course_id;
	
	fac.n_courses_offered= fac.n_courses_offered +1;
	int c = save_course(&my_course);
	
	
	
	bool set1=set_faculty_details(id,&fac);
	if(c==-1){
		write_msg(cfd,0,1,"\nCannot Save the course...");
		return;
	}
	else{
		write_msg2(cfd,0,1,"\ncourse Created Successfully!\nNote: Id is ",c);
	}

}



void add_student(int cfd){
	int student_id;
	struct student stu;
	struct message msg;
	int rb, wb;

	//Getting details
	write_msg(cfd,1,1,"\nEnter Name: ");
	read_msg(cfd,&msg);

	strcpy(stu.stud_name,msg.body);




	write_msg(cfd,1,0,"\nEnter Gender: ");
	read_msg(cfd,&msg);

	stu.stud_gender=msg.body[0];

	write_msg(cfd,1,0,"\nEnter Address: ");
	read_msg(cfd,&msg);

	strcpy(stu.stud_address,msg.body);

	write_msg(cfd,1,0,"\nEnter phone number: ");
	read_msg(cfd,&msg);

	strcpy(stu.stud_phone,msg.body);

	write_msg(cfd,1,0,"\nEnter email: ");
	read_msg(cfd,&msg);

	strcpy(stu.stud_email,msg.body);

	stu.status=1;


	write_msg(cfd,1,2,"\nEnter Password: # ");
	read_msg(cfd,&msg);

	strcpy(stu.stud_password,msg.body);

	//Initializing...
	strcpy(stu.stud_login_id,"");
	stu.n_courses=0;
	for(int i=0;i<5;i++)
	stu.courses[i]=-1;
	stu.stud_login_status=0;
	//Update to file
	student_id=save_student(&stu);
	if(student_id==-1){
		write_msg(cfd,0,1,"\nCannot Save the Student...");
		return;
	}	
	else{
		write_msg2(cfd,0,1,"\nStudent Created Successfully!\nNote: Login-Id is MT2023{student}\nStud-Id Generated is %d",student_id);
	}
//set Login-Id...
	sprintf(stu.stud_login_id,"MT2023%d",student_id);
	bool status=set_student_details(student_id,&stu);
	if(status==0){
	write_msg(cfd,0,1,"\nLogin-Id Setting Failed...");
	}
	else{

		write_msg2(cfd,0,1,"\nLogin-Id Settings Completed Successfully... Login-Id: MT2023%d",student_id);

	}

}

