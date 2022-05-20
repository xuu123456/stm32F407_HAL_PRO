#ifndef _my_fat_h_
#define _my_fat_h_
#include "fatfs.h"
#include <stdio.h>

unsigned int Fat_readTxt(const char* filename,char *buffer);

#endif

