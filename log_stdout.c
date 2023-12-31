#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include <stdarg.h>
char buf[1024];
int read_stdin(char* buf) {
	/*
	Description: Read stdin into buf
	Example:
	- read_stdin(); // Read the stdin into buf
	Parameters:
	- buf (char*): A buffer to store all characters
	Return:
	- 0 (int)
	*/
	// Your code here
	if(fork()==0){
		close(1);
		write(0,buf,strlen(buf));
		exit(0);
	}
	return 0;
	// End
	//read stdin into buf
}
int log_stdout(uint i) {
	/*
	Description: Redirect stdout to a log file named i.log
	Example:
	- log_stdout(1); // Redirect the stdout to 1.log and return 0
	Parameters:
	- i (uint): A number
	Return:
	- 0 (int)
	*/
	char log_name[15] = "0.log";
	// Your code here
	uint base = 1, i_temp;
	if (i != 0) {
		for (base = 0, i_temp = i; i_temp != 0; ++base, i_temp /= 10);
		for (uint base_temp = 0, i_temp = i; i_temp != 0; ++base_temp, i_temp /= 10) {
			log_name[base - base_temp - 1] = '0' + i_temp % 10;
		}
		strcpy(log_name + base, ".log");
	}
	close(1);
	if (open(log_name, O_CREATE | O_WRONLY) != 1) {
		fprintf(2, "log_stdout: open failed\n");
		return -1;
	}
	// End
	return 0;
}
int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(2, "Usage: log_stdout number\n");
		exit(1);
	}
	if (log_stdout(atoi(argv[1])) != 0) {
		fprintf(2, "log_stdout: log_stdout failed\n");
		exit(1);
	}
	if (read_stdin(buf) != 0) {
		fprintf(2, "log_stdout: read_stdin failed\n");
		exit(1);
	}
	printf(buf);
	exit(0);
}