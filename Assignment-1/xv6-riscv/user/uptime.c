#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	int ut = uptime();
	int hours= ut/36000;
	int min = (ut-(hours*36000))/600;
	int sec= (ut-(hours*36000)-(min*600))/10;
	
	fprintf(2, "uptime: %d hours, %d mins, %d secs\n", hours,min,sec);
	exit(0);
}