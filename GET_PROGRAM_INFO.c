#define _GNU_SOURCE
#include<unistd.h> 
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<stdio.h>
#include<regex.h>
#include"GET_PROGRAM_INFO.h"
#include"GET_IP_INFO.h"
int Find_Pid(int inode) {
	int pid;
    DIR * Proc_First_Entry_Pointer;
    struct dirent * Proc_Entry_Info;
	
    Proc_First_Entry_Pointer = opendir("/proc");

    while ((Proc_Entry_Info = readdir(Proc_First_Entry_Pointer)) != NULL) {
        regex_t reg;
        regmatch_t pmatch[1];

        regcomp(&reg, "^[0-9]+$", REG_EXTENDED);

        if (!regexec(&reg, Proc_Entry_Info->d_name, 1, pmatch, 0)) {
            char path[SIZE];

            sprintf(path, "/proc/%s/fd", Proc_Entry_Info->d_name);

//	printf("test\n");
//	printf("/proc/%s/fd\n", Proc_Entry_Info->d_name);
           
			 if (!eaccess(path, R_OK)) {
                DIR * Fd_First_Entry_Pointer;
                struct dirent * Fd_Entry_Info;

                Fd_First_Entry_Pointer = opendir(path);

                while ((Fd_Entry_Info = readdir(Fd_First_Entry_Pointer)) != NULL) {
                    sprintf(path, "/proc/%s/fd/%s", Proc_Entry_Info->d_name, Fd_Entry_Info->d_name);
//			printf("test2");
//			printf("/fd/%s\n", Fd_Entry_Info->d_name);
                    

					if (!eaccess(path, R_OK) && Fd_Entry_Info->d_type == DT_LNK) {
                        char link[SIZE];
                        int len;
                        char socket[SIZE], socket_zero[SIZE];

                        len = readlink(path, link, SIZE);
                        link[len] = '\0';
	

//	printf("len:%d", len);
	
                        sprintf(socket, "socket:[%d]", inode);
                        sprintf(socket_zero, "0000:[%d]", inode);
                        if (!strcmp(link, socket) || !strcmp(link, socket_zero)) {
                            sscanf(Proc_Entry_Info->d_name, "%d", &pid);
				//		    closedir(Fd_First_Entry_Pointer);
    			//			closedir(Proc_First_Entry_Pointer);
                            return pid;
                        }
                    }
                }

//rintf("XD\n");
                closedir(Fd_First_Entry_Pointer);
            }
        }
    }

//rintf("XD\n");
    closedir(Proc_First_Entry_Pointer);
//rintf("XD\n");
    return -1;
}

void Find_Name(char name[], int pid, int size)
{
    char cmdline_path[SIZE];
    FILE * cmdline_fp;
	for(int i = 0; i < size; i++)
		name[i] = '\0';
    sprintf(cmdline_path, "/proc/%d/cmdline", pid);
//printf("%d\n", pid);
    cmdline_fp = fopen(cmdline_path, "r");
 	if(cmdline_fp != NULL)
	  fgets(name, size, cmdline_fp);
//printf("%s\n", name);
	int len = strlen(name);
	if(len >= 1)  
	{ 
		name[strlen(name) - 1] = '\0';
		Parse_Name(name, strlen(name));
	}
	else
		name[0] = '-';
//	printf("%s\n", name);
    if(cmdline_fp !=NULL)
	    fclose(cmdline_fp);
//	printf("1\n");
}

void Parse_Name(char name[], int len){
	int First_Space;
	int Last_Slash;
	char new_name[SIZE] = {'\0'};
		Last_Slash = 0;
		First_Space = 0;
	for(int i = 0; i < len; i++)
	{
		if(name[i] == '/')
			Last_Slash = i+1;
		if(name[i] == ' ')
		{
			First_Space = i;	
			break;
		}
	}
//	printf("Last_Slash%d", Last_Slash);
	for(int i = Last_Slash; i < len; i++){
		new_name[i-Last_Slash] = name[i];
	}
	strcpy(name, new_name);
}
/*
void Find_Name(char name[], int pid, int size)
{
    char comm_path[SIZE];
    FILE * comm_fp;
	for(int i = 0; i < size; i++)
		name[i] = '\0';
    sprintf(comm_path, "/proc/%d/comm", pid);
//	printf("%d\n", pid);
    comm_fp = fopen(comm_path, "r");
 	if(comm_fp != NULL)
	  fgets(name, size, comm_fp);
	int len = strlen(name);
	if(len >= 1)   
		name[strlen(name) - 1] = '\0';
	else
		name[0] = '-';
//	printf("%s\n", name);
    if(comm_fp !=NULL)
	    fclose(comm_fp);
//	printf("1\n");
}*/

/*int main()
{
	int pid;
	int inode;
	scanf("%d", &inode);
	pid = Find_Pid(inode);
	printf("%d", pid);
}*/

