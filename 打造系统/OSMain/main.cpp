#include "HardDisk.h"

int main()
{
	CHardDisk disk;

	printf("==========mbr=========\n");
	disk.writeFileToDisk("mbr", true, 0, 0);	//0-512

	// ��kernel�������ļ�д��0����ƫ��2����
	printf("==========loader=========\n");
	disk.writeFileToDisk("loader", false, 0, 2);  // 1024-
	

	printf("==========kernel=========\n");
	//disk.writeFileToDisk("kernel.bin", false, 0, 9);
	disk.writeFileToDisk("kernel.bin", false, 0, 9);

	disk.makeVirtualDisk("boot.img");

	system("pause");
	return 0;
}