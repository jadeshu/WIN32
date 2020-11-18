#include "HardDisk.h"

CHardDisk::CHardDisk()
{
	char* buf = nullptr;
	// ��ʼ��Ӳ��,�ڷ���ͳ�ʼ���ڴ��е�����
	for (int i = 0; i < CYLINDER_COUNT; i++)
	{
		for (int j = 0; j < SECTORS_COUNT; j++)
		{
			buf = new char[SECTOR_SIZE];	// Ч�ʵ���
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
	// �ͷŷ�����ڴ�
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
	//printf("��ȡ��(��ͷ:%d - ����:%d - ����:%d)\n", head, cylinder_num, sector_num);
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
	printf("�Ѿ�д�뵽(��ͷ:%d - ����:%d - ����:%d)\n", head, cylinder_num, sector_num);
}

void CHardDisk::makeVirtualDisk(const char* name)
{
	printf("׼����ʼ���......\r\n");
	FILE* file = nullptr;
	fopen_s(&file, name, "wb");

	//for (int head = 0; head <= 1; head++) {	// �ȶ���0���ڶ�1��
		for (int cylinder = 0; cylinder < CYLINDER_COUNT; cylinder++)
		{
			// ����0��Ͷ�ͬһλ�õ�1������
			for (int head = 0; head < 4; head++)
			{
				for (int sector = 0; sector < SECTORS_COUNT; sector++)
				{
					char* buf = getDiskBuffer(head, cylinder, sector);
					// �����ģ��Ĵ�������д��ָ���ļ���
					fwrite(buf, 1, SECTOR_SIZE, file);
				}
			}
		}
	//}
	

	fclose(file);
	printf("����ɹ�\r\n");
}

void CHardDisk::writeFileToDisk(const char* fileName, /*bool bootable,*/ int cylinder, int beginSec)
{
	FILE* file = nullptr;
    fopen_s(&file, fileName, "rb");
	if (file == nullptr)
	{
		printf("��ȡ�ļ�������\r\n");
		return; 
	}
	char* buf = new char[512];
	memset(buf, 0, 512);
	//if (bootable) {
	//	buf[510] = (char)0x55;
	//	buf[511] = (char)0xaa;
	//}

	//����ļ��Ĵ�С  
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);

	if (size > SECTOR_SIZE)
	{
		int count_test = 0;
		// �ļ����ݴ���512�ֽڣ���������
		while (!feof(file)) {
			fread(buf, 1, SECTOR_SIZE, file);
			setDiskBuffer(this->head, cylinder, beginSec, buf);
			memset(buf, 0, SECTOR_SIZE);
			beginSec++;

			// ���0���ͷ�����������1��ͬ�����������
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

			// ���������0�������1������
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
				printf("�ռ䲻���Դ洢\r\n");
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
	printf("׼��д�뵽VHD......\r\n");
	FILE* file = nullptr;
	fopen_s(&file, name, "r+b");
	if (file == nullptr)
	{
		printf("��ȡ�ļ�������\r\n");
		return; 
	}
	//for (int head = 0; head <= 1; head++) {	// �ȶ���0���ڶ�1��
		for (int cylinder = 0; cylinder < CYLINDER_COUNT; cylinder++)
		{
			// ����0��Ͷ�ͬһλ�õ�1������
			for (int head = 0; head <= 1; head++)
			{
				for (int sector = 0; sector < SECTORS_COUNT; sector++)
				{
					char* buf = getDiskBuffer(head, cylinder, sector);
					// �����ģ��Ĵ�������д��ָ���ļ���
					fwrite(buf, 1, SECTOR_SIZE, file);
				}
			}
		}
	//}
	

	fclose(file);
	printf("д��ɹ�\r\n");
}