#ifndef RELEVE_H
#define RELEVE_H

#include <windows.h>
#include "ftd2xx.h"
#include "define.h"
#include <stdio.h>


FT_STATUS read_temp(FT_HANDLE ftHandle, temp_t *temp);

#endif
