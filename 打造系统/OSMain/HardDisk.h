#ifndef __HARDDISK_H__
#define __HARDDISK_H__

#define SECTOR_SIZE 512		// 1个扇区占字节大小
#define CYLINDER_COUNT 80	//80  121 柱面80
#define SECTORS_COUNT 16//18 63	//80 1个柱面的扇区数18
#include <string>

// 用数组存储
class CHardDisk
{
public:
	CHardDisk();
	~CHardDisk();

	// 设置硬盘盘面、柱面、扇区
	void  setMagneticHead(unsigned int head) { this->head = head; }
	void  setCylinder(int cylinder) { this->current_cylinder = cylinder; }
	void  setSector(int sector) { this->current_sector = sector; }

	// 获取扇区数据
	char* getDiskBuffer(unsigned int  head, int cylinder_num, int sector_num);
	// 将buf数据写入指定扇区
	void  setDiskBuffer(unsigned int  head, int cylinder_num, int sector_num, char* buf);
	// 制作映像文件
	void  makeVirtualDisk(const char* name = "system.img");


	void writeFileToDisk(const char* fileName,/* bool bootable,*/ int cylinder, int beginSec);
	
	void writeExisteVHD(const char* name = "boot.vhd");
private:
	unsigned int head = 0;		// 默认盘面
	int current_cylinder = 0;	// 当前磁道号
	int current_sector = 0;		// 当前扇区号
	char* disk0[CYLINDER_COUNT][SECTORS_COUNT];
	char* disk1[CYLINDER_COUNT][SECTORS_COUNT];
	char* disk2[CYLINDER_COUNT][SECTORS_COUNT];
	char* disk3[CYLINDER_COUNT][SECTORS_COUNT];
};

#endif