#ifndef CG_SAMPLE_STL_FILE_LOADER
#define CG_SAMPLE_STL_FILE_LOADER
#include <Windows.h>

struct STriangle
{
	float n[3], a[3], b[3], c[3],normal[3];
};

STriangle * LoadStlASCII(const char * pPathname, int & nTriangles);
STriangle * LoadStlBinary(const char * pPathname, int & nTriangles);

void gotoxy(int x, int y);  //cursor an gewuenschte position auf dem bildschirm setzen

#endif