#ifndef __SYSTEM_H__
#define __SYSTEM_H__
#include "Floppy.h"
class COperatingSystem
{
public:
	COperatingSystem(const char* s);
	~COperatingSystem();

	void writeFileToFloppy(const char* fileName, bool bootable, int cylinder, int beginSec);
	void makeFllopy();
private:
	CFloppy *floppyDisk = new CFloppy();

};

#endif