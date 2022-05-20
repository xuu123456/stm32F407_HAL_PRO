#ifndef __USB_H
#define __USB_H 			   
#include <sys.h>	  
#include "main.h"
#include "usbd_cdc_if.h"
#include <stdarg.h>


void USB_Printf(const char *format, ...);
void USB_Reset(void);
#endif





























