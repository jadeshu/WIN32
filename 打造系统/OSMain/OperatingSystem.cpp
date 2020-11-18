#include "OperatingSystem.h"



COperatingSystem::COperatingSystem(const char* s)
{
	writeFileToFloppy(s, true, 0, 1);
}


COperatingSystem::~COperatingSystem()
{
}

void COperatingSystem::writeFileToFloppy(const char* fileName, bool bootable, int cylinder, int beginSec)
{
	FILE* file = fopen(fileName, "rb");
	if (!file)
	{
		printf("读取文件不存在\r\n");
	}
	char* buf = new char[512];
	memset(buf, 0, 512);
	if (bootable) {
		buf[510] = 0x55;
		buf[511] = 0xaa;
	}

	//求得文件的大小  
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);

	while (fread(buf, 1, size, file) == size)
	{
		floppyDisk->writeFloppy(MAGNETIC_HEAD::MAGNETIC_HEAD_0, cylinder, beginSec, buf, 512);
		beginSec++;

		if (beginSec > 18) {
			beginSec = 1;
			cylinder++;
		}
	}

	fclose(file);
	file = nullptr;
}

void COperatingSystem::makeFllopy()
{
	writeFileToFloppy("kernel", false, 1, 2);

	floppyDisk->makeFloppy("system.img");
}
