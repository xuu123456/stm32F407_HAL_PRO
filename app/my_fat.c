#include "my_fat.h"
/*
功能:读取一个txt文件夹内的内容
参数：filename：读取txt的文件，示例：456/123.txt,456是文件上一路径
buffer:用于存放字节内容
返回值：有效字节的个数
*/
unsigned int Fat_readTxt(const char* filename,char *buf)
{
		FIL myfile;
		FRESULT fr;
		unsigned int filenum;
		fr = f_open(&myfile,filename,FA_READ);//打开文件	
		if(fr!=FR_OK)
		{
			printf("打开失败 \r\n");
			f_close(&myfile);
			return 0;
		}
		fr = f_read(&myfile,&buf,sizeof(buf),&filenum);
		f_close(&myfile);
		if(fr==FR_OK)
		{		
			return filenum;
		}			
		else
		{
			printf("读取失败 \r\n");
			return 0;
		}
			
}

//		Myfr = f_opendir(&dirfile,myfilename);//打开文件夹
//		if(Myfr==FR_OK) printf("file:%s dir open OK!\r\n",myfilename);
//		while(f_readdir(&dirfile,&finfo)==FR_OK)//按顺序读取文件夹信息
//		{
//			if(!finfo.fname[0]) break;
//			else 
//			{
//				if(finfo.fattrib == AM_ARC)
//					printf("file name: %s \r\n",finfo.fname);
//			}
//		}
//		Myfr = f_closedir(&dirfile);
//		if(Myfr==FR_OK) printf("file:%s dir close\r\n",myfilename);
