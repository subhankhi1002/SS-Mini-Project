void admin_menu(int cfd){ //showing admin menu when logged in as admin

	struct message msg;
	int readBytes, writeBytes;
	begin2:
	write_msg(cfd,1,0,"\n....... Welcome to Admin Menu .......\nWhat do you want to do?\n1. Add Student\n2. View Student Details\n3.Modify Student Details 4.Add Faculty\n5. View Faculty Details\n6. Modify Faculty Details\n7. Press any key to Exit\nEnter Your Choice: ");
	read_msg(cfd,&msg);
	int choice=atoi(msg.body);
	switch(choice){
	case 1: add_student(cfd); 	
		goto begin2;
		break;
	case 2: view_student_details(cfd); 	
		goto begin2; 
		break;
	case 3: modify_student_details(cfd);
		goto begin2; 
		break;
	case 4: add_faculty(cfd); 	
		goto begin2; 
		break;
	case 5: view_faculty_details(cfd); 	
		goto begin2; 
		break;
 
	case 6: modify_faculty_details(cfd);
		goto begin2; 
		break;
	default:
		write_msg(cfd,0,0,"");
		break;
	}

}

void student_menu(int cfd, int id){  //showing student menu when logged in as student

	struct message msg;
	int readBytes, writeBytes;
	begin3:
	write_msg(cfd,1,0,"\n....... Welcome to Student Menu .......\n1. View All Courses Available\n2. Enroll New Course\n3. View Your Enrolled Course Details\n4.Drop a Course\n 5. Change Password \n6./ any key to Exit\nEnter Your Choice: ");
	read_msg(cfd,&msg);

	int choice=atoi(msg.body);
	switch(choice){
		case 1: view_courses(cfd); 	
			goto begin3; 
			break;
		case 2: enroll_course(cfd,id); 		
			goto begin3; 
			break;
		case 3: view_course_enrolled(cfd,id);
			goto begin3;
			break;
		case 4: drop_course(cfd,id);
			goto begin3;
			break;
		case 5: set_student_password(cfd,id);
			goto begin3;
			break;

		default:
			struct student my_student;
			my_student=get_student_details(id);
			my_student.stud_login_status=0;
			set_student_details(id,&my_student);
			write_msg(cfd,0,0,"");
			break;
	}

}

void faculty_menu(int cfd, int id){ //showing faculty menu when logged in as faculty

	struct message msg;
	int readBytes, writeBytes;
	begin3:
	write_msg(cfd,1,0,"\n....... Welcome to Faculty Menu .......\n1. View Your Offered Courses\n2. Add New Course\n3. Remove Course \n4. Change Password \n5./ any key to Exit\nEnter Your Choice: ");
	read_msg(cfd,&msg);

	int choice=atoi(msg.body);
	switch(choice){
	case 1: view_courses_offered(cfd,id);
		goto begin3;
		break;
	case 2: add_new_course(cfd,id);
		goto begin3;
		break;
	case 3: remove_course(cfd,id);
		goto begin3;
		break;
	case 4: set_faculty_password(cfd,id);
		goto begin3;
		break;

	default:
        	struct faculty my_faculty;
        	my_faculty=get_faculty_details(id);
        	my_faculty.faculty_login_status=0;
        	set_faculty_details(id,&my_faculty);
        	write_msg(cfd,0,0,"");
        	break;
}

}

