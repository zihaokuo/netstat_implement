#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "GET_IP_INFO.h"
#include "GET_PROGRAM_INFO.h"
void Translate_IPv4_INFO(Connection_INFO* info, const char* line)
{			
	struct in_addr local_addr, rem_addr;
	sscanf(line, "%*d: %X:%X %X:%X %*X %*X:%*X %*X:%*X %*d %*d %*d %d", &local_addr.s_addr, &info->local_Port, &rem_addr.s_addr, &info->rem_Port, &info->inode);
	inet_ntop(AF_INET, &local_addr, info->local_IP, SIZE);
	inet_ntop(AF_INET, &rem_addr, info->rem_IP, SIZE);
}

void Translate_IPv6_INFO(Connection_INFO* info, const char* line)
{
	struct in6_addr local_addr6;
	struct in6_addr rem_addr6;
	uint32_t *local_addr6_8 = local_addr6.s6_addr32;
	uint32_t *rem_addr6_8 = rem_addr6.s6_addr32;
	
	sscanf(line, "%*d: %8X%8X%8X%8X:%X %8X%8X%8X%8X:%X %*X %*X:%*X %*X:%*X %*X %*X %*X %d", 
		&local_addr6_8[0],&local_addr6_8[1],&local_addr6_8[2],&local_addr6_8[3],
		&info->local_Port, 
		&rem_addr6_8[0],&rem_addr6_8[1], &rem_addr6_8[2], &rem_addr6_8[3], 
		&info->rem_Port, 
		&info->inode);
    
	inet_ntop(AF_INET6, &local_addr6, info->local_IP, SIZE);
	inet_ntop(AF_INET6, &rem_addr6, info->rem_IP, SIZE);
}

void List_Connection_INFO(int version, const char* filter)
{
	char line[SIZE];
	FILE* pf = NULL;
	Connection_INFO connect_info;
	if(version != UDP){
	//List our title tcp	
		printf("List of TCP connection:\n");
		printf("%-5s %-45s %-45s %-50s\n", "Proto", "Local Address", "Foreign Address", "PID/Program name and arguments");
	//open the file	
		pf = fopen("/proc/net/tcp", "r");
	//remove the title
		fgets(line, SIZE, pf);
	//get ip_info
		while(fgets(line, SIZE, pf) != NULL){
			char tmp[10];
			Translate_IPv4_INFO(&connect_info, line);
			sprintf(tmp, ":%d", connect_info.local_Port);
			strcat(connect_info.local_IP, tmp);	
			sprintf(tmp, ":%d", connect_info.rem_Port);
			strcat(connect_info.rem_IP, tmp);
			int Pid = Find_Pid(connect_info.inode);
			char name[SIZE];
			Find_Name(name, Pid, SIZE);
			char Program_Info[SIZE] = {'\0'};				

			if(Pid == -1)
				Program_Info[0] = '-';
			else				
			{
				sprintf(Program_Info,"%d" ,Pid);
				strcat(Program_Info, "/");
				strcat(Program_Info, name);	
			}
//			printf("%c%c%c%c", name[strlen(name)] , name[strlen(name)+1] , name[strlen(name)+2], name[strlen(name)+3]); 
			printf("%-5s %-45s %-45s %-50s\n", "tcp", connect_info.local_IP, connect_info.rem_IP, Program_Info);
		}
	//open the file	
		pf = fopen("/proc/net/tcp6", "r");
	//remove the title
		fgets(line, SIZE, pf);
	//get ip_info
		while(fgets(line, SIZE, pf) != NULL){
			char tmp[10];
			Translate_IPv6_INFO(&connect_info, line);
			sprintf(tmp, ":%d", connect_info.local_Port);
			strcat(connect_info.local_IP, tmp);	
			sprintf(tmp, ":%d", connect_info.rem_Port);
			strcat(connect_info.rem_IP, tmp);
			int Pid = Find_Pid(connect_info.inode);
			char name[SIZE];
			Find_Name(name, Pid, SIZE);
			char Program_Info[SIZE] = {'\0'};
			if(Pid == -1)
				Program_Info[0] = '-';
			else				
			{
				sprintf(Program_Info,"%d" ,Pid);
				strcat(Program_Info, "/");
				strcat(Program_Info, name);	
			}
			printf("%-5s %-45s %-45s %-50s\n", "tcp6", connect_info.local_IP, connect_info.rem_IP, Program_Info);
		}
	}
	if(version == 2)
		printf("\n");
	if(version != TCP)
	{
	//List our title udp	
		printf("List of UDP connection:\n");
		printf("%-5s %-45s %-45s %-50s\n", "Proto", "Local Address", "Foreign Address", "PID/Program name and arguments");
	//open the file	
		pf = fopen("/proc/net/udp", "r");
	//remove the title
		fgets(line, SIZE, pf);
	//get ip_info
		while(fgets(line, SIZE, pf) != NULL){
			char tmp[10];
			Translate_IPv4_INFO(&connect_info, line);
			sprintf(tmp, ":%d", connect_info.local_Port);
			strcat(connect_info.local_IP, tmp);	
			sprintf(tmp, ":%d", connect_info.rem_Port);
			strcat(connect_info.rem_IP, tmp);
			int Pid = Find_Pid(connect_info.inode);
			char name[SIZE];
			Find_Name(name, Pid, SIZE);
			char Program_Info[SIZE] = {'\0'};	
			if(Pid == -1)
				Program_Info[0] = '-';
			else				
			{
				sprintf(Program_Info,"%d" ,Pid);
				strcat(Program_Info, "/");
				strcat(Program_Info, name);	
			}
			printf("%-5s %-45s %-45s %-50s\n", "udp", connect_info.local_IP, connect_info.rem_IP, Program_Info);
		}
	//open the file	
		pf = fopen("/proc/net/udp6", "r");
	//remove the title
		fgets(line, SIZE, pf);
	//get ip_info
		while(fgets(line, SIZE, pf) != NULL){
			char tmp[10];
			Translate_IPv6_INFO(&connect_info, line);
			sprintf(tmp, ":%d", connect_info.local_Port);
			strcat(connect_info.local_IP, tmp);	
			sprintf(tmp, ":%d", connect_info.rem_Port);
			strcat(connect_info.rem_IP, tmp);
			int Pid = Find_Pid(connect_info.inode);
			char name[SIZE];
			Find_Name(name, Pid, SIZE);
			char Program_Info[SIZE] = {'\0'};
//printf("xD");
			if(Pid == -1)
				Program_Info[0] = '-';
			else				
			{
				sprintf(Program_Info,"%d" ,Pid);
				strcat(Program_Info, "/");
				strcat(Program_Info, name);	
			}
			printf("%-5s %-45s %-45s %-50s\n", "udp6", connect_info.local_IP, connect_info.rem_IP, Program_Info);
		}
	}
}

/*int main(int argc, void* argv[])
{
	List_Connection_INFO(TCP, "no write");
}*/
