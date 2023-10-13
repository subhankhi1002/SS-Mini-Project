#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>


struct faculty get_faculty_details(int faculty_id){
	int rBytes,wBytes, fd, offset;
	struct faculty fac;
	//check validity of faculty-Id

	//valid
	fd=open("./records/faculty_file",O_RDONLY);
	if(fd==-1){
		perror("Cannot Open File");
		return (struct faculty){-1,"NULL",'\0',"NULL","NULL","NULL","NULL","NULL","NULL",{0,0,0},0,0,0};
	}
	offset=lseek(fd,faculty_id*sizeof(struct faculty),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in faculty File");
		return (struct faculty){-1,"NULL",'\0',"NULL","NULL","NULL","NULL","NULL","NULL",{0,0,0},0,0,0};

	}
/*Setting Lock*/
	struct flock lock = {F_RDLCK, SEEK_SET, faculty_id*sizeof(struct faculty), sizeof(struct faculty), getpid()};
	int lockingStatus = fcntl(fd, F_SETLKW, &lock);
	if (lockingStatus == -1)
	{
		perror("Error obtaining lock");
		return (struct faculty){-1,"NULL",'\0',"NULL","NULL","NULL","NULL","NULL","NULL",{0,0,0},0,0,0};

	}
/*...........*/
	rBytes=read(fd,&fac,sizeof(fac));
	/*Unlocking....*/
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
/*...........*/
	if(rBytes<=0){
		perror("Cannot read the file");
		return (struct faculty){-1,"NULL",'\0',"NULL","NULL","NULL","NULL","NULL","NULL",{0,0,0},0,0,0};

	}
	close(fd);

	//success...
	return fac;
}

/* Setter Program */

bool set_faculty_details(int faculty_id, struct faculty *fac){
	int rBytes,wBytes, fd, offset;
	//check validity of faculty-Id
	
	//valid
	fac->faculty_id=faculty_id;
	fd=open("./records/faculty_file",O_WRONLY);
	if(fd==-1){
		perror("Cannot Open File");
		return 0;
	}
	offset=lseek(fd,faculty_id*sizeof(struct faculty),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in faculty File");
		return 0;
	}
	/*Setting Lock*/
	struct flock lock = {F_WRLCK, SEEK_SET, faculty_id*sizeof(struct faculty), sizeof(struct faculty), getpid()};
	int lockingStatus = fcntl(fd, F_SETLKW, &lock);
	if (lockingStatus == -1)
	{
		perror("Error obtaining lock!");
		return 0;
}
	/*...........*/
	wBytes=write(fd,&(*fac),sizeof(*fac));
	/*Unlocking....*/
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	/*...........*/
	if(wBytes<=0){
		perror("Cannot write into the file");
		return 0;
}
	close(fd);


	//success...
	return 1;
}

/*
Create/ Save new faculty:: Update to file...
*/

int save_faculty(struct faculty *fac){
	int faculty_id;
	int rBytes,wBytes, fd, offset;
	faculty_id=get_record_details(2);
	if(faculty_id==-1) return -1;
	
	fac->faculty_id=faculty_id;
	fd=open("./records/faculty_file",O_WRONLY | O_CREAT,0777);
	if(fd==-1){
		perror("Cannot Open File");
		return -1;
	}
	offset=lseek(fd,faculty_id*sizeof(struct faculty),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in faculty File");
		return -1;
	}
	/*Setting Lock*/
	struct flock lock = {F_WRLCK, SEEK_SET, faculty_id*sizeof(struct faculty), sizeof(struct faculty), getpid()};
	int lockingStatus = fcntl(fd, F_SETLKW, &lock);
	if (lockingStatus == -1)
		{
		perror("Error obtaining lock!");
		return -1;
		}


	wBytes=write(fd,&(*fac),sizeof(*fac));
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
	if(!set_record_details(2,faculty_id+1)){
		printf("Error while updating record file\n");
		return -1;
}

//success...
	return faculty_id;
}
