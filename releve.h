#ifndef RELEVE_H
#define RELEVE_H

#include <windows.h>
#include "ftd2xx.h"
#include <stdio.h>


FT_HANDLE init_usb();
void read_temp(FT_HANDLE ftHandle);

#endif
