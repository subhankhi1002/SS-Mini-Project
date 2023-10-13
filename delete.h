void remove_course(cfd,id){

	int course_id;
	struct course my_course;
	struct message msg;
	struct student stu;
	struct faculty fac;
	int total_courses;
	int total_stud;
	
	total_courses=get_record_details(0);
	total_stud=get_record_details(1);
	fac=get_faculty_details(id);

	write_msg(cfd,1,0,"\nEnter course id: ");
	read_msg(cfd,&msg);
	course_id=atoi(msg.body);
	my_course=get_course_details(course_id);
	my_course.status=0;
	bool set1=set_course_details(course_id,&my_course);
	for(int i=0;i<fac.n_courses_offered;i++){
	if(fac.courses_offered[i]=course_id){
		fac.courses_offered[i]=-1;
		fac.n_courses_offered=fac.n_courses_offered-1;
		break;
	}
	}
	bool set2=set_faculty_details(fac.faculty_id,&fac);
	if(set_record_details(0,total_courses-1)){
	for(int j=0;j<total_stud;j++){
	int flag=0;
	stu=get_student_details(j);
	for(int k=0;k<stu.n_courses;k++){
	if(stu.courses[k]==course_id){
		stu.courses[k]=-1;
		stu.n_courses=stu.n_courses-1;
		flag=1;
		break;
	}
	}
	if(flag==1){
	bool set=set_student_details(stu.stud_id,&stu);
	}
	}
	bzero(msg.body,sizeof(msg.body));

	write_msg(cfd,0,1,"\nCourse removed");

	}




}





void drop_course(cfd,id){
	struct message msg;
	struct student stu;
	struct course my_course;
	int course_id;

	write_msg(cfd,1,0,"\nEnter the course id: ");
	read_msg(cfd,&msg);
	course_id=atoi(msg.body);
	stu=get_student_details(id);
	my_course=get_course_details(course_id);
	for(int i=0; i<stu.n_courses;i++){
		if(stu.courses[i]==course_id){
		stu.courses[i]=-1;
		stu.n_courses=stu.n_courses-1;
		my_course.avail_n_seats=my_course.avail_n_seats+1;
		break;
		}
	}
	if(set_student_details(id,&stu)){
		if(set_course_details(course_id,&my_course)){
		bzero(msg.body,sizeof(msg.body));

		write_msg(cfd,0,1,"\nAbove Course dropped!!");
		}
	}
	else{
		bzero(msg.body,sizeof(msg.body));

		write_msg(cfd,0,1,"\nCan't be dropped");
	}
}






