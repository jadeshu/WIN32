#ifndef __HARDDISK_H__
#define __HARDDISK_H__

#define SECTOR_SIZE 512		// 1������ռ�ֽڴ�С
#define CYLINDER_COUNT 80	//80  121 ����80
#define SECTORS_COUNT 16//18 63	//80 1�������������18
#include <string>

// ������洢
class CHardDisk
{
public:
	CHardDisk();
	~CHardDisk();

	// ����Ӳ�����桢���桢����
	void  setMagneticHead(unsigned int head) { this->head = head; }
	void  setCylinder(int cylinder) { this->current_cylinder = cylinder; }
	void  setSector(int sector) { this->current_sector = sector; }

	// ��ȡ��������
	char* getDiskBuffer(unsigned int  head, int cylinder_num, int sector_num);
	// ��buf����д��ָ������
	void  setDiskBuffer(unsigned int  head, int cylinder_num, int sector_num, char* buf);
	// ����ӳ���ļ�
	void  makeVirtualDisk(const char* name = "system.img");


	void writeFileToDisk(const char* fileName,/* bool bootable,*/ int cylinder, int beginSec);
	
	void writeExisteVHD(const char* name = "boot.vhd");
private:
	unsigned int head = 0;		// Ĭ������
	int current_cylinder = 0;	// ��ǰ�ŵ���
	int current_sector = 0;		// ��ǰ������
	char* disk0[CYLINDER_COUNT][SECTORS_COUNT];
	char* disk1[CYLINDER_COUNT][SECTORS_COUNT];
	char* disk2[CYLINDER_COUNT][SECTORS_COUNT];
	char* disk3[CYLINDER_COUNT][SECTORS_COUNT];
};

#endif