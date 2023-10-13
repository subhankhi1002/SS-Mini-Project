void view_student_details(int cfd){
	struct student stu;
	struct message msg;
	int id;
	int rb, wb;
	write_msg(cfd,1,0,"\nEnter Student-Id: ");
	read_msg(cfd,&msg);

	id=atoi(msg.body);

	stu=get_student_details(id);
	if(stu.stud_id==-1){
	write_msg(cfd,0,1,"\nError while viewing the Student...");
	return;
	}

	char buffer[1000];
	sprintf(buffer,"...................Student Details..................\nName:  %s\nGender: %c\nAddress: %s\nPhone-number: %s\nEmail: %s\nLogin-Id: %s\nPassword: %s\nNumber of courses enrolled: 	%d\nCourse ids: %d, %d, %d, %d, %d\n...................End of Statement..................\n",stu.stud_name,stu.stud_gender,stu.stud_address,stu.stud_phone,stu.stud_email,stu.stud_login_id,stu.stud_password,stu.n_courses,stu.courses[0],stu.courses[1],stu.courses[2],stu.courses[3],stu.courses[4]);
	write_msg(cfd,0,1,buffer);
	
	}

void view_faculty_details(int cfd){
	struct faculty fac;
	struct message msg;
	int id;
	int rb, wb;
	write_msg(cfd,1,0,"\nEnter Faculty-Id: ");
	read_msg(cfd,&msg);

	id=atoi(msg.body);

	fac=get_faculty_details(id);
	if(fac.faculty_id==-1){
	write_msg(cfd,0,1,"\nCannot view the Faculty...");
	return;
	}

	char buffer[1000];
	sprintf(buffer,"...................Faculty Details..................\nName:  %s\nGender: %c\nAddress: %s\nPhone-number: %s\nEmail: %s\nDepartment: %s\nLogin-Id: %s\nPassword: %s\nNumber of courses offered: %d\nCourse ids: %d, %d, %d\n...................End of Statement..................\n",fac.faculty_name,fac.faculty_gender,fac.faculty_address,fac.faculty_phone,fac.faculty_email,fac.faculty_department,fac.faculty_login_id,fac.faculty_password,fac.n_courses_offered,fac.courses_offered[0],fac.courses_offered[1],fac.courses_offered[2]);
	write_msg(cfd,0,1,buffer);

}

void view_course_enrolled(int cfd,int student_id){
	struct student stu;
	struct message msg;
	stu=get_student_details(student_id);
	if(stu.stud_id==-1){
	write_msg(cfd,0,1,"\nCannot view the Student...");
	return;
	}
	if(stu.n_courses==0){
	write_msg(cfd,0,1,"\nNo Courses to Enrolled");
	return;
	}
	for(int i=0;i<stu.n_courses;i++){
	int courses_id=stu.courses[i];
	write_msg2(cfd,0,1,"\nCourse ID ",courses_id);
	}
	write_msg(cfd,0,1,"\n...................End of Statement..................\n");
}

void view_courses_offered(int cfd,int faculty_id){
	struct faculty fac;
	struct message msg;
	fac=get_faculty_details(faculty_id);
	if(fac.faculty_id==-1){
	write_msg(cfd,0,1,"\nCannot view the course...");
	return;
	}
	if(fac.n_courses_offered==0){
	write_msg(cfd,0,1,"\nNo Courses Offered");
	return;
	}

	for(int i=0;i<fac.n_courses_offered;i++){
	int courses_id=fac.courses_offered[i];
	write_msg2(cfd,0,1,"\nCourse ID ",courses_id);
	}
	//write_msg2(cfd,0,1,"\nCourses ",fac.n_courses_offered);
	write_msg(cfd,0,1,"\n...................End of Statement..................\n");
}




void view_courses(cfd){
	int total_records;
	int i=0;
	struct message msg;
	total_records=get_record_details(0);
	struct course my_course;
	while(i<total_records){
		my_course=get_course_details(i);
		if(my_course.status==1){
			sprintf(msg.body,"%d %s",my_course.course_id, my_course.course_name);
			write_msg(cfd,0,1,msg.body);
			bzero(msg.body,sizeof(msg.body));
		}
		i++;
	}



}

void enroll_course(cfd,id){
	struct message msg;
	struct student stu;
	struct course my_course;
	int course_id;

	write_msg(cfd,1,0,"\nEnter the course id: ");
	read_msg(cfd,&msg);
	course_id=atoi(msg.body);
	stu=get_student_details(id);
	my_course=get_course_details(course_id);
	if(my_course.avail_n_seats>0){
		stu.courses[stu.n_courses]=course_id;
		stu.n_courses=stu.n_courses+1;
		my_course.avail_n_seats=my_course.avail_n_seats-1;

	if(set_student_details(id,&stu)){
		if(set_course_details(course_id,&my_course)){
			bzero(msg.body,sizeof(msg.body));
			write_msg(cfd,0,1,"\nCourse enrolled");
		}
	}
	else{
		bzero(msg.body,sizeof(msg.body));
		write_msg(cfd,0,1,"\nNot enrolled");}

	}
	else{
		bzero(msg.body,sizeof(msg.body));
	
		write_msg(cfd,0,1,"\nNo Seats unavailable");
	}




}








