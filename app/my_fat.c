#include "my_fat.h"
/*
����:��ȡһ��txt�ļ����ڵ�����
������filename����ȡtxt���ļ���ʾ����456/123.txt,456���ļ���һ·��
buffer:���ڴ���ֽ�����
����ֵ����Ч�ֽڵĸ���
*/
unsigned int Fat_readTxt(const char* filename,char *buf)
{
		FIL myfile;
		FRESULT fr;
		unsigned int filenum;
		fr = f_open(&myfile,filename,FA_READ);//���ļ�	
		if(fr!=FR_OK)
		{
			printf("��ʧ�� \r\n");
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
			printf("��ȡʧ�� \r\n");
			return 0;
		}
			
}

//		Myfr = f_opendir(&dirfile,myfilename);//���ļ���
//		if(Myfr==FR_OK) printf("file:%s dir open OK!\r\n",myfilename);
//		while(f_readdir(&dirfile,&finfo)==FR_OK)//��˳���ȡ�ļ�����Ϣ
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
