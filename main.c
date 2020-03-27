#include <stdio.h>
#include <getopt.h>
#include "GET_IP_INFO.h"

int main(int argc, char**argv){
		struct option opts[]={
		{"tcp",0,NULL,'t'},
		{"udp",0,NULL,'u'},
		{NULL,0,NULL,0}//When no argument is given
	};
	int opt_index,c;
	int t=0,u=0;
	while((c=getopt_long(argc,argv,"tu",opts,&opt_index))!=-1){
		switch(c){
			case 't':
				t=1;
				break;
			case 'u':
				u=1;
				break;
			default:
				break;
		}
	}

	argc-=optind;
	argv+=optind;
#ifdef DEBUG
	if(argv[0]!=NULL)
		printf("%s\n",argv[0]);	
	else
		printf("no pattern");
#endif
	if(t==1 && u==0){
		List_Connection_INFO(0,NULL);
	}else if(t==0 && u==1){
		List_Connection_INFO(1,NULL);
	}else{
		List_Connection_INFO(2,NULL);
	}
	return 0;
}
