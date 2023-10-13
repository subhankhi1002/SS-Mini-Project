#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>


struct student get_student_details(int student_id){
	int rBytes,wBytes, fd, offset;
	struct student stu;
	
	fd=open("./records/student_file",O_CREAT | O_RDONLY);
	if(fd==-1){
		perror("Cannot Open File");
		return (struct student){-1,"NULL",'\0',"NULL","NULL","NULL","NULL","NULL",{0,0,0,0,0},0,0,0};
	}
	offset=lseek(fd,student_id*sizeof(struct student),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in student File");
		return (struct student){-1,"NULL",'\0',"NULL","NULL","NULL","NULL","NULL",{0,0,0,0,0},0,0,0};
	}
	/*Setting Lock*/
	struct flock lock = {F_RDLCK, SEEK_SET, student_id*sizeof(struct student), sizeof(struct student), getpid()};
	int lockingStatus = fcntl(fd, F_SETLKW, &lock);
	if (lockingStatus == -1)
	{
		perror("Error obtaining lock");
		return (struct student){-1,"NULL",'\0',"NULL","NULL","NULL","NULL","NULL",{0,0,0,0,0},0,0,0};
	}

	rBytes=read(fd,&stu,sizeof(stu));
	/*Unlocking....*/
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	/*...........*/
	if(rBytes<=0){
		perror("Cannot read the file");
		return (struct student){-1,"NULL",'\0',"NULL","NULL","NULL","NULL","NULL",{0,0,0,0,0},0,0,0};
	}
	close(fd);

//success...
	return stu;
}

/* Setter Program */

bool set_student_details(int student_id, struct student *stu){
	int rBytes,wBytes, fd, offset;
	//check validity of student-Id
	if(is_validId(1,student_id)){
	//valid
	stu->stud_id=student_id;
	fd=open("./records/student_file",O_WRONLY);
	if(fd==-1){
		perror("Cannot Open File");
		return 0;
	}
	offset=lseek(fd,student_id*sizeof(struct student),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in student File");
		return 0;
	}
	/*Setting Lock*/
	struct flock lock = {F_WRLCK, SEEK_SET, student_id*sizeof(struct student), sizeof(struct student), getpid()};
		int lockingStatus = fcntl(fd, F_SETLKW, &lock);
		if (lockingStatus == -1)
	{
		perror("Error obtaining lock!");
		return 0;
	}

	wBytes=write(fd,&(*stu),sizeof(*stu));
	/*Unlocking....*/
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	/*...........*/
	if(wBytes<=0){
		perror("Cannot write into the file");
		return 0;
	}
	close(fd);
	}
	else{
		printf("Record Not Exists\n");
	return 0;
	}

	//success...
	return 1;
}

/*
Create/ Save new student
*/

int save_student(struct student *stu){
	int student_id;
	int rBytes,wBytes, fd, offset;
	student_id=get_record_details(1);
	if(student_id==-1) return -1;

	stu->stud_id=student_id;
	fd=open("./records/student_file",O_WRONLY | O_CREAT,0777);
	if(fd==-1){
		perror("Cannot Open File");
		return -1;
	}
	offset=lseek(fd,student_id*sizeof(struct student),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in student File");
		return -1;
	}
	/*Setting Lock*/
	struct flock lock = {F_WRLCK, SEEK_SET, student_id*sizeof(struct student), sizeof(struct student), getpid()};
	int lockingStatus = fcntl(fd, F_SETLKW, &lock);
	if (lockingStatus == -1)
	{
	perror("Error obtaining lock!");
	return -1;
	}
	wBytes=write(fd,&(*stu),sizeof(*stu));
	/*Unlocking....*/
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	/*...........*/
	if(wBytes<=0){
		perror("Cannot write into the file");
		return -1;
	}
	close(fd);

	//upadate available account-no...
	if(!set_record_details(1,student_id+1)){
		printf("Error while updating record file\n");
		return -1;
	}

	//success...
	//success...
	return student_id;
}
