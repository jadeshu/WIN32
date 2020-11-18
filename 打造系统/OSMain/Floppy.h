#ifndef __FLOPPY_H__
#define __FLOPPY_H__

#include <map>
#include <vector>
using namespace std;

enum /*class */MAGNETIC_HEAD {
	MAGNETIC_HEAD_0,	// 盘面0
	MAGNETIC_HEAD_1		// 盘面1
};

// 用vector存储，麻烦！不如二维数组
class CFloppy
{
public:
	CFloppy();

	void  setMagneticHead(MAGNETIC_HEAD head);
	void  setCylinder(int cylinder);
	void  setSector(int sector);

	char* readFloppy(MAGNETIC_HEAD head, int cylinder_num, int sector_num);
	void writeFloppy(MAGNETIC_HEAD head, int cylinder_num, int sector_num, char* buf, int len);
	void makeFloppy(const char* fileName);
private:
	vector<vector<char*>>&  initFloppyDisk();
	vector<char*>& initCylinder();

private:
	MAGNETIC_HEAD magneticHead = MAGNETIC_HEAD::MAGNETIC_HEAD_0;  // 盘面 默认0面
	int current_cylinder = 0;	// 当前磁道号
	int current_sector = 0;		// 当前扇区号

	static const int SECTOR_SIZE = 512;   // 扇区大小
	static const int CYLINDER_COUNT = 80; // 80个柱面
	static const int SECTORS_COUNT = 18;	 // 一磁道有18个扇区

	map<MAGNETIC_HEAD, vector<vector<char*>>> floppy_map;
};

#endif