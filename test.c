#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char buff[1000];
	char data[1000];
	char buff1[1000];
	char i = 0;
	char ch;
	FILE *fptr = NULL;
	fptr = fopen(argv[1],"r");
	memset(buff, 0, 1000);
	memset(buff1, 0, 1000);
	if(fptr==NULL)
	{
		printf("%s\n","Error opening the file.");
		exit(1);
	}
	ch = fgetc(fptr);
	int i1 = 0;
    while (ch != EOF)
    {
        data[i1] = ch;
        i1++;
        ch = fgetc(fptr);
    }
    fclose(fptr);
    int fp = open("/dev/encdev", O_RDWR);
	write(fp, data, strlen(data));
	system("cat /dev/encdev > /dev/decdev");
	//int l = read(fp, buff, 1000);
	system("cat /dev/decdev");
	
}