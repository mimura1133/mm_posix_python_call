#include <stdio.h>
#include <Windows.h>

#define LEN 2048

void main(int argc, char *argv[]){
	int i,j,k,l;
	char c,temp[LEN] = {0};
	char cmdline[LEN] = {0};
	PROCESS_INFORMATION pi;
	STARTUPINFO si;

	memset(&si,0,sizeof(STARTUPINFO));
	memset(&pi,0,sizeof(PROCESS_INFORMATION));

	si.cb = sizeof(STARTUPINFO);
	sprintf_s(cmdline,LEN,"C:\\Windows\\posix.exe /u /c /usr/local/bin/python ");

	for(i = 0; i < (argc-1); i++){
		if(strstr(argv[i+1],":") != NULL){
			k = 10;
			l = strlen(argv[i+1]);
			sprintf_s(temp,LEN,"\"/dev/fs/%c",argv[i+1][0]);
			for(j = 2; j < l; j++){
				c = argv[i+1][j];
				temp[k++] = c == '\\' ? '/' : c;
			}
			temp[k++] = '\"';
			temp[k++] = ' ';
			temp[k++] = 0;
			strcat_s(cmdline,LEN,temp);
		} else {
			strcat_s(cmdline,LEN,argv[i+1]);
			strcat_s(cmdline,LEN," ");
		}
	}

	CreateProcess(NULL,cmdline,NULL,NULL,0,NORMAL_PRIORITY_CLASS,NULL,NULL,&si,&pi);
	
	WaitForSingleObject(pi.hProcess,INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}