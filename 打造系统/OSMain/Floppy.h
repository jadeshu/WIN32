#ifndef __FLOPPY_H__
#define __FLOPPY_H__

#include <map>
#include <vector>
using namespace std;

enum /*class */MAGNETIC_HEAD {
	MAGNETIC_HEAD_0,	// ����0
	MAGNETIC_HEAD_1		// ����1
};

// ��vector�洢���鷳�������ά����
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
	MAGNETIC_HEAD magneticHead = MAGNETIC_HEAD::MAGNETIC_HEAD_0;  // ���� Ĭ��0��
	int current_cylinder = 0;	// ��ǰ�ŵ���
	int current_sector = 0;		// ��ǰ������

	static const int SECTOR_SIZE = 512;   // ������С
	static const int CYLINDER_COUNT = 80; // 80������
	static const int SECTORS_COUNT = 18;	 // һ�ŵ���18������

	map<MAGNETIC_HEAD, vector<vector<char*>>> floppy_map;
};

#endif