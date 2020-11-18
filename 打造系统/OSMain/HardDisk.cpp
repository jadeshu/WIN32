#include "HardDisk.h"

CHardDisk::CHardDisk()
{
	char* buf = nullptr;
	// 初始化硬盘,在分配和初始化内存中的数据
	for (int i = 0; i < CYLINDER_COUNT; i++)
	{
		for (int j = 0; j < SECTORS_COUNT; j++)
		{
			buf = new char[SECTOR_SIZE];	// 效率低下
			memset(buf, 0, SECTOR_SIZE);
			this->disk0[i][j] = buf;

			buf = new char[SECTOR_SIZE];
			memset(buf, 0, SECTOR_SIZE);
			this->disk1[i][j] = buf;

			buf = new char[SECTOR_SIZE];
			memset(buf, 0, SECTOR_SIZE);
			this->disk2[i][j] = buf;

			buf = new char[SECTOR_SIZE];
			memset(buf, 0, SECTOR_SIZE);
			this->disk3[i][j] = buf;
		}
	}
}


CHardDisk::~CHardDisk()
{
	// 释放分配的内存
	for (int i = 0; i < CYLINDER_COUNT; i++)
	{
		for (int j = 0; j < SECTORS_COUNT; j++)
		{
			delete[] this->disk0[i][j];
			delete[] this->disk1[i][j];
			delete[] this->disk2[i][j];
			delete[] this->disk3[i][j];

		}
	}
}

char* CHardDisk::getDiskBuffer(unsigned int head, int cylinder_num, int sector_num)
{
	this->setMagneticHead(head);
	this->setCylinder(cylinder_num);
	this->setSector(sector_num);
	//printf("获取到(磁头:%d - 柱面:%d - 扇区:%d)\n", head, cylinder_num, sector_num);
	switch (head)
	{
		case 0:
		{
			return this->disk0[cylinder_num][sector_num];
			break;
		}
		case 1:
		{
			return this->disk1[cylinder_num][sector_num];
			break;
		}
		case 2:
		{
			return this->disk2[cylinder_num][sector_num];
			break;
		}
		case 3:
		{
			return this->disk3[cylinder_num][sector_num];
			break;
		}
	}
	//if (head == 0)
	//{
	//	return this->disk0[cylinder_num][sector_num];
	//}
	//else if(head == 1)
	//{
	//	return this->disk1[cylinder_num][sector_num];
	//}
	
	return nullptr;
}

void CHardDisk::setDiskBuffer(unsigned int head, int cylinder_num, int sector_num, char* buf)
{
	char* bufTmp = getDiskBuffer(head, cylinder_num, sector_num);
	//memcpy_s(bufTmp, SECTOR_SIZE, buf, SECTOR_SIZE);
	memcpy(bufTmp, buf, SECTOR_SIZE);
	printf("已经写入到(磁头:%d - 柱面:%d - 扇区:%d)\n", head, cylinder_num, sector_num);
}

void CHardDisk::makeVirtualDisk(const char* name)
{
	printf("准备开始打包......\r\n");
	FILE* file = nullptr;
	fopen_s(&file, name, "wb");

	//for (int head = 0; head <= 1; head++) {	// 先读完0面在读1面
		for (int cylinder = 0; cylinder < CYLINDER_COUNT; cylinder++)
		{
			// 读完0面就读同一位置的1面数据
			for (int head = 0; head < 4; head++)
			{
				for (int sector = 0; sector < SECTORS_COUNT; sector++)
				{
					char* buf = getDiskBuffer(head, cylinder, sector);
					// 将软件模拟的磁盘内容写入指定文件内
					fwrite(buf, 1, SECTOR_SIZE, file);
				}
			}
		}
	//}
	

	fclose(file);
	printf("打包成功\r\n");
}

void CHardDisk::writeFileToDisk(const char* fileName, /*bool bootable,*/ int cylinder, int beginSec)
{
	FILE* file = nullptr;
    fopen_s(&file, fileName, "rb");
	if (file == nullptr)
	{
		printf("读取文件不存在\r\n");
		return; 
	}
	char* buf = new char[512];
	memset(buf, 0, 512);
	//if (bootable) {
	//	buf[510] = (char)0x55;
	//	buf[511] = (char)0xaa;
	//}

	//求得文件的大小  
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);

	if (size > SECTOR_SIZE)
	{
		int count_test = 0;
		// 文件数据大于512字节，另作处理
		while (!feof(file)) {
			fread(buf, 1, SECTOR_SIZE, file);
			setDiskBuffer(this->head, cylinder, beginSec, buf);
			memset(buf, 0, SECTOR_SIZE);
			beginSec++;

			// 填充0面磁头扇区完后就填充1面同样柱面的扇区
			//if (beginSec >= SECTORS_COUNT) {
			//	beginSec = 0;
			//	count_test++;
			//	if (count_test % 2 == 0)
			//	{
			//		cylinder++;
			//	}
			//	this->head == 0 ? this->head = 1 : this->head = 0;
			//	cylinder++;
			//}

			// 填充完整个0面在填充1面扇区
			if (beginSec >= SECTORS_COUNT) {
				beginSec = 0;
				//count_test++;
				//if (count_test % 2 == 0)
				//{
				//	cylinder++;
				//}

				//this->head == 0 ? this->head = 1 : this->head = 0;
				
				//cylinder++;
				this->head++;
			}

			if (this->head == 4)
			{
				this->head = 0;
				cylinder++;
			}
			if (cylinder >= CYLINDER_COUNT)
			{
				printf("空间不足以存储\r\n");
				return;
			}
		}

	}
	else
	{
		fread(buf, 1, size, file);
		setDiskBuffer(0, cylinder, beginSec, buf);
	}

	fclose(file);
	file = nullptr;
}


void CHardDisk::writeExisteVHD(const char* name)
{
	printf("准备写入到VHD......\r\n");
	FILE* file = nullptr;
	fopen_s(&file, name, "r+b");
	if (file == nullptr)
	{
		printf("读取文件不存在\r\n");
		return; 
	}
	//for (int head = 0; head <= 1; head++) {	// 先读完0面在读1面
		for (int cylinder = 0; cylinder < CYLINDER_COUNT; cylinder++)
		{
			// 读完0面就读同一位置的1面数据
			for (int head = 0; head <= 1; head++)
			{
				for (int sector = 0; sector < SECTORS_COUNT; sector++)
				{
					char* buf = getDiskBuffer(head, cylinder, sector);
					// 将软件模拟的磁盘内容写入指定文件内
					fwrite(buf, 1, SECTOR_SIZE, file);
				}
			}
		}
	//}
	

	fclose(file);
	printf("写入成功\r\n");
}