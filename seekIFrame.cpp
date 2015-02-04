#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1*1024*1024
int main(int argc, char ** argv)
{
int retvalue = -1;
FILE * fp_input = NULL;
unsigned char buffer[BUFFER_SIZE];
unsigned int  readlen = 0;

	if(argc < 2)
	{
		printf("%s inputfile.264\n",argv[0]);
		return -1;
	}
	fp_input = fopen(argv[1],"rb");
	if(fp_input == NULL)
	{
		retvalue = -1;
		goto END;
	}
	printf("Input File Name:%s\n",argv[1]);
	while((readlen = fread(buffer,1,BUFFER_SIZE, fp_input)) > 5)
	{
		unsigned char * pbuf = buffer;
		while(pbuf <= (buffer + readlen))
		{
			if( (*(pbuf) == 0) && (*(pbuf + 1) == 0) && (*(pbuf + 2) == 0) && (*(pbuf + 3) == 1) )
			{//Start code: 00 00 00 01

				//SPS
				if( ((*(pbuf + 4)) & 0x1F) == 7)
				{
					printf("SPS at :0x%lx\n",(ftell(fp_input) - readlen) + (pbuf - buffer));
				}
				
				//PPS
				if( ((*(pbuf + 4)) & 0x1F) == 8)
				{
					printf("PPS at :0x%lx\n",(ftell(fp_input) - readlen) + (pbuf - buffer));
				}	
											
				//I Frame
				if( ((*(pbuf + 4)) & 0x1F) == 5)
				{
					printf("IDR Frame at :0x%lx\n",(ftell(fp_input) - readlen) + (pbuf - buffer));
				}
				//Normal Frame
				//if( ((*(pbuf + 4)) & 0x1F) == 1)
				//{
				//	printf("Normal Frame at :0x%lx\n",(ftell(fp_input) - readlen) + (pbuf - buffer));
				//}
			}
				pbuf ++;
		}//while(pbuf <= (buffer + readlen))
		
	}//while((readlen = fread(buffer,1,BUFFER_SIZE, fp_input)) > 5)

END:
	fclose(fp_input);
return retvalue;
}
