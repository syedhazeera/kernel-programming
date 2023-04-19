#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int8_t write_buf[1024];
int8_t read_buf[1024];

int main()
{
	int fd;
	char option;
	printf("character device driver...\n");
	
	fd = open("/dev/my_device",o_RDWR);
	if(fd<0)
	{
		printf("cannot open device file...\n");
		return 0;
	}
	while(1)	
	{
		printf("*********please enter your option*********\n");
		printf("		1.Write			\n");
		printf("		2.Read		\n");
		printf("		3.Exit			\n");
		scanf("%c",&option);
		printf(" your options = %c\n",option);
		switch(option)
		{
			case '1':
				printf("enter the string to write into driver:\n");
				scanf("%[^\t\n]s",write_buf);
				printf("Data written...");
				write(fd,write_buf,strlen(write_buf)+1);
				printf("DONE...\n");
				break;
			case '2':
				printf("Data is Reading...");
				read(fd,read_buf,1024);
				printf("Done..\n\n");
				printf("Data = %s\n\n",read_buf);
				break;
			case '3':
				close(fd);
				exit(1);
				break;
			default:
				printf("enter the valid option =%c\n",option);
				break;
		}
	}
	close(fd);
}

/*output:
syed@syed-VirtualBox:~/Desktop/kernel$ cc test_drv.c -o test_drv
syed@syed-VirtualBox:~/Desktop/kernel$ sudo ./test_drv
[sudo] password for syed: 
character device driver...
cannot open device file..
*/
