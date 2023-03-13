#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H

#include <FS.h>


void Init_File_System(void);

void readTestFile(void);

void printDirectory(File dir, int numTabs = 3);



#endif