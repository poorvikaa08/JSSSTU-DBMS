#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char sid[20];
	char name[30];
	char branch[10];
	int sem;
	char address[50];
} student;

const char *filename = "student.txt";

void print_student(student s) {
	printf("\nSID: %s\nName: %s\nBranch: %s\nSem: %d\nAddress: %s\n",s.sid, s.name, s.branch, s.sem, s.address );
}

void insert() {
	student s;
	FILE *fp = fopen(filename,"a");
	
	if(!fp) {
		printf("File error\n");
		return;
	}
	
	printf("Enter the student details: \nname: ");
	scanf("%s", s.name);
	
	printf("student-ID: ");
	scanf("%s", s.sid);
	
	printf("branch: ");
	scanf("%s", s.branch);
	
	printf("sem: ");
	scanf("%d", &s.sem);
	
	printf("address: ");
	scanf("%s", s.address);
	
	fprintf(fp, "%s %s %s %d %s\n", s.sid, s.name, s.branch, s.sem, s.address);
	
	fclose(fp);
	printf("Student added successfully\n");
}


void modify() {

	student s;
	char id[10], addr[40];
	int found = 0;
	
	FILE *fp = fopen(filename, "r");
	FILE *temp = fopen("temp.txt", "w");
	
	printf("Enter the student ID: ");
	scanf("%s", id);
	
	while (fscanf(fp, "%s %s %s %d %s", s.sid, s.name, s.branch, &s.sem, s.address) != EOF) {
		if(strcmp(s.sid, id) == 0) {
			printf("Enter the new address: ");
			scanf("%s", addr);
			strcpy(s.address, addr);
			found = 1;
		}
		
		fprintf(temp, "%s %s %s %d %s\n",
                s.sid, s.name, s.branch, s.sem, s.address);	
	}
	
	fclose(fp);
	fclose(temp);
	
	remove(filename);
	rename("temp.txt", filename);
	
	if(found) printf("address updated\n");
	else printf("student not found\n");
	
}

void delete() {
	student s;
	char id[10], addr[40];
	int found = 0;
	
	FILE *fp = fopen(filename, "r");
	FILE *temp = fopen("temp.txt", "w");
	
	printf("Enter the student ID: ");
	scanf("%s", id);
	
	while (fscanf(fp, "%s %s %s %d %s", s.sid, s.name, s.branch, &s.sem, s.address) != EOF) {
		if(strcmp(s.sid, id) != 0) {
			fprintf(temp, "%s %s %s %d %s\n",
                s.sid, s.name, s.branch, s.sem, s.address);
		} else found = 1;
			
	}
	
	fclose(fp);
	fclose(temp);
	
	remove(filename);
	rename("temp.txt", filename);
	
	if(found) printf("student deleted\n");
	else printf("student not found\n");
	
}

void listAll() {
	student s;
	FILE *fp = fopen(filename, "r");
	
	while(fscanf(fp, "%s %s %s %d %s", s.sid, s.name, s.branch, &s.sem, s.address) != EOF) {
		print_student(s);
	}
	
	fclose(fp);
}

void listCSE() {
	student s;
	FILE *fp = fopen(filename, "r");
	
	while(fscanf(fp, "%s %s %s %d %s", s.sid, s.name, s.branch, &s.sem, s.address) != EOF) {
		if(strcmp(s.branch, "CSE") == 0) {
			print_student(s);
		}
	}
	
	fclose(fp);
}

void listCSEandKu() {
	student s;
	FILE *fp = fopen(filename, "r");
	
	while(fscanf(fp, "%s %s %s %d %s", s.sid, s.name, s.branch, &s.sem, s.address) != EOF) {
		if(strcmp(s.branch, "CSE") == 0 && strcmp(s.address, "Kuvempunagara") == 0) {
			print_student(s);
		}
	}
	
	fclose(fp);

}

int main () {
	int choice;
	
	while(1) {
		printf("\n(1) Insert a student\n(2) Modify address\n(3) Delete\n(4) List all\n(5) List CSE students\n(6) List CSE and kuvempunagar\n(7) Exit\n\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		 
		switch(choice) {
			case 1: insert(); break;
			case 2: modify(); break;
			case 3: delete(); break;
			case 4: listAll(); break;
			case 5: listCSE(); break;
			case 6: listCSEandKu(); break;
			case 7: exit(0);
			default : printf("Invalid choice\n");
		}
	}
	
	return 0;
}
