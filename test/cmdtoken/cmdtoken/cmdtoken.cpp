// cmdtoken.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <stdlib.h>




typedef struct _command {
	int argc;
	int type; //0 cmd 1 file(>) 2 file(>>)
	char argv[10][256];
} command;



int main(int argc, char* argv[])
{
	command mycmd[10];



	char cmd[1024];
	strcpy(cmd, "  ni hao ni2 hao3       | shui shi && zhu | zhu | jiu shi ni > hahaha      ");
	
	int pcmd = 0;
	char * p = cmd;

	mycmd[0].argc = 0;
	mycmd[0].type = 0;


	while (1) {
		p = strtok(strstr(p, " "), " ");
		if (!p)
			break;

		if (strncmp("|", p, 2) == 0)
		{
			pcmd++;
			mycmd[pcmd].type = 0;
			mycmd[pcmd].argc = 0;
		}
		else if (strncmp(">", p, 2) == 0)
		{
			pcmd++;
			mycmd[pcmd].type = 1;
			mycmd[pcmd].argc = 0;
		}
		else if (strncmp(">>", p, 3) == 0)
		{
			pcmd++;
			mycmd[pcmd].type = 2;
			mycmd[pcmd].argc = 0;
		}
		else
		{
			strncpy(mycmd[pcmd].argv[mycmd[pcmd].argc], p, 256);
			mycmd[pcmd].argv[mycmd[pcmd].argc++][255] = '\0';
		}

		//printf("%s\n", p);
	}


	return 0;
}

