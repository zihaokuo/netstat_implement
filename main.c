#include <stdio.h>
#include <getopt.h>
#include "GET_IP_INFO.h"
#include <string.h>

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

	char filter[SIZE] = {'\0'};

    switch (argc) {
        case 0:
            break;

        default:
            strcpy(filter, argv[0]);

            for (int i = 1; i <= argc - 1; i++) {
                strcat(filter, "[ ]+");
                strcat(filter, argv[i]);
            }
            break;
    }

	if(t==1 && u==0){
		List_Connection_INFO(0,filter);
	}else if(t==0 && u==1){
		List_Connection_INFO(1,filter);
	}else{
		List_Connection_INFO(2,filter);
	}
	return 0;
}
