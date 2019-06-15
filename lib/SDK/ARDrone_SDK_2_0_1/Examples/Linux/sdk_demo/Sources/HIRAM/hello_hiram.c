#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <termios.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

#include <config.h>

#include <ardrone_tool/ardrone_tool.h>
#include <ardrone_tool/Com/config_com.h>


DEFINE_THREAD_ROUTINE(hello_hiram, data)
{
  C_RESULT res;
	while(1){ 
		printf("hello drone, hur mar du ?\n");
		sleep(10);
		fflush(0);
	}
  return (THREAD_RET)0;
}

