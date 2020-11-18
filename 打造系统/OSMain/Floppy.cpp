#include "Floppy.h"



CFloppy::CFloppy()
{
	floppy_map.insert(make_pair(MAGNETIC_HEAD::MAGNETIC_HEAD_0, initFloppyDisk()));
	floppy_map.insert(make_pair(MAGNETIC_HEAD::MAGNETIC_HEAD_1, initFloppyDisk()));
}

void CFloppy::setMagneticHead(MAGNETIC_HEAD head)
{
	this->magneticHead = head;
}

void CFloppy::setCylinder(int cylinder)
{
	if (cylinder < 0) {
		this->current_cylinder = 0;
	}
	else if (cylinder >= 80) {
		this->current_cylinder = 79;
	}
	else {
		this->current_cylinder = cylinder;
	}
}

void CFloppy::setSector(int sector)
{
	//sector 编号从1到18
	if (sector < 0) {
		this->current_sector = 0;
	}
	else if (sector > 18) {
		this->current_sector = 18 - 1;
	}
	else {
		this->current_sector = sector - 1;
	}
}

char* CFloppy::readFloppy(MAGNETIC_HEAD head, int cylinder_num, int sector_num)
{
	this->setMagneticHead(head);
	this->setCylinder(cylinder_num);
	this->setSector(sector_num);

	vector<vector<char*>> disk = floppy_map.find(this->magneticHead)->second;
	vector<char*> cylinder = disk.at(this->current_cylinder);
	char* buf = cylinder.at(this->current_sector);

	return buf;
}

void CFloppy::writeFloppy(MAGNETIC_HEAD head, int cylinder_num, int sector_num, char* buf, int len)
{
	char* bufTmp = readFloppy(head, cylinder_num, sector_num);
	memcpy_s(bufTmp, 512, buf, len);
}

void CFloppy::makeFloppy(const char* fileName)
{
	printf("准备开始写入......\r\n");
	FILE* file = fopen("system.img", "wb");
	for (int cylinder = 0; cylinder < CYLINDER_COUNT; cylinder++) 
	{
		// 读完0面就读同一位置的1面数据
		for (int head = 0; head <= 1; head++) 
		{
			for (int sector = 1; sector <= SECTORS_COUNT; sector++) 
			{
				char* buf = readFloppy((MAGNETIC_HEAD)head, cylinder, sector);
				// 将软件模拟的磁盘内容写入指定文件内
				fwrite(buf, 1, SECTOR_SIZE, file);
			}
		}
	}

	fclose(file);
	printf("写入成功\r\n");
}

vector<vector<char*>>& CFloppy::initFloppyDisk()
{
	vector<vector<char*>> *floppyDisk = new vector<vector<char *>>();
	for (int i = 0; i < this->CYLINDER_COUNT; i++)
	{
		floppyDisk->push_back(initCylinder());
	}

	return *floppyDisk;
}

vector<char*>& CFloppy::initCylinder()
{
	vector<char*>* cylinder = new vector<char *>();
	for (int i = 0; i < this->SECTORS_COUNT; i++)
	{
		char* newBuf = new char[this->SECTOR_SIZE];
		memset(newBuf, 0, this->SECTOR_SIZE);
		cylinder->push_back(newBuf);
	}

	return *cylinder;
}
