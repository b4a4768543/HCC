#include "stdafx.h"

#include <windows.h>
#include "glee.h"
#include "inputStl.h"
#include <iostream>
#include <string>
#include <tchar.h>
#include <ctime>
#include <thread>
#include <Dsound.h>

#include "gl/shared/gltools.h"	// OpenGL toolkit
#include "gl/shared/glframe.h"   // OpenGL Frame class
#include "gl/shared/math3d.h"
#include <math.h>
//MCI
#include "mmsystem.h"//导入声音头文件 
#pragma comment(lib,"winmm.lib")//导入声音头文件库 
#include<stdio.h>
//
#pragma comment(lib, "dsound.lib" )
#pragma comment(lib, "GLee.lib" )
#pragma comment(lib, "Winmm.lib") 
#pragma warning( disable : 4996 )  //讀tga檔時，fopen發生錯誤C4996，使用此忽略

using namespace std;
//音檔
const char *sound[89] = { "0", "sound/C1.WAV", "sound/C2.WAV", "sound/C3.WAV", "sound/C4.WAV", "sound/C5.WAV", "sound/C6.WAV", "sound/C7.WAV", "sound/C8.WAV",
"sound/#C1.WAV", "sound/#C2.WAV", "sound/#C3.WAV", "sound/#C4.WAV", "sound/#C5.WAV", "sound/#C6.WAV", "sound/#C7.WAV",
"sound/D1.WAV", "sound/D2.WAV", "sound/D3.WAV", "sound/D4.WAV", "sound/D5.WAV", "sound/D6.WAV", "sound/D7.WAV",
"sound/#D1.WAV", "sound/#D2.WAV", "sound/#D3.WAV", "sound/#D4.WAV", "sound/#D5.WAV", "sound/#D6.WAV", "sound/#D7.WAV",
"sound/E1.WAV", "sound/E2.WAV", "sound/E3.WAV", "sound/E4.WAV", "sound/E5.WAV", "sound/E6.WAV", "sound/E7.WAV",
"sound/F1.WAV", "sound/F2.WAV", "sound/F3.WAV", "sound/F4.WAV", "sound/F5.WAV", "sound/F6.WAV", "sound/F7.WAV",
"sound/#F1.WAV", "sound/#F2.WAV", "sound/#F3.WAV", "sound/#F4.WAV", "sound/#F5.WAV", "sound/#F6.WAV", "sound/#F7.WAV",
"sound/G1.WAV", "sound/G2.WAV", "sound/G3.WAV", "sound/G4.WAV", "sound/G5.WAV", "sound/G6.WAV", "sound/G7.WAV",
"sound/#G1.WAV", "sound/#G2.WAV", "sound/#G3.WAV", "sound/#G4.WAV", "sound/#G5.WAV", "sound/#G6.WAV", "sound/#G7.WAV",
"sound/A0.WAV", "sound/A1.WAV", "sound/A2.WAV", "sound/A3.WAV", "sound/A4.WAV", "sound/A5.WAV", "sound/A6.WAV", "sound/A7.WAV",
"sound/#A0.WAV", "sound/#A1.WAV", "sound/#A2.WAV", "sound/#A3.WAV", "sound/#A4.WAV", "sound/#A5.WAV", "sound/#A6.WAV", "sound/#A7.WAV",
"sound/B0.WAV", "sound/B1.WAV", "sound/B2.WAV", "sound/B3.WAV", "sound/B4.WAV", "sound/B5.WAV", "sound/B6.WAV", "sound/B7.WAV" };
void PlayMp3();
//紀錄按鍵狀態之變數
int i[90] = { 0 };
int ipress[90] = { 0 };
//sound
thread *pitch[900];		
int pitch_count[900];
//VBO information
unsigned int VBO_index_part1[2], VBO_index_part2[2], VBO_index_part3[2], VBO_index_part4[2], VBO_index_part5[2];
unsigned int VBO_index_do[2], VBO_index_re[2], VBO_index_mi[2], VBO_index_fa[2], VBO_index_so[2], VBO_index_la[2], VBO_index_si[2], VBO_index_plus[2], VBO_index_do_ex[2], VBO_index_la_ex[2];
unsigned int VBO_index_main1[2], VBO_index_main2[2], VBO_index_main3[2], VBO_index_main4[2] ;
unsigned int VBO_index_load1[2], VBO_index_load2[2], VBO_index_load3[2], VBO_index_load4[2], VBO_index_load5[2] ;

float *VBOv[24] = { 0 }, *VBOn[24] = { 0 };
// 讀取STL檔
int nTriangles[24] = { 0 };
float cent[24][3] = { 0 };

//鍵盤按鍵操控的零件
STriangle* triArray_part1 = LoadStlBinary("model/part1.STL", nTriangles[0]);           //讀取手
STriangle* triArray_part2 = LoadStlBinary("model/part2.STL", nTriangles[1]);           //讀取釘子
STriangle* triArray_part4 = LoadStlBinary("model/part4.STL", nTriangles[3]);         //讀取桌子
STriangle* triArray_part5 = LoadStlBinary("model/part5.STL", nTriangles[4]);             //讀取袋子
//鍵盤按鍵
STriangle* triArray_do = LoadStlBinary("model/do.STL", nTriangles[5]);             //讀取袋子
STriangle* triArray_re = LoadStlBinary("model/re.STL", nTriangles[6]);             //讀取袋子
STriangle* triArray_mi = LoadStlBinary("model/mi.STL", nTriangles[7]);             //讀取袋子
STriangle* triArray_fa = LoadStlBinary("model/fa.STL", nTriangles[8]);             //讀取袋子
STriangle* triArray_so = LoadStlBinary("model/so.STL", nTriangles[9]);             //讀取袋子
STriangle* triArray_la = LoadStlBinary("model/la.STL", nTriangles[10]);             //讀取袋子
STriangle* triArray_si = LoadStlBinary("model/si.STL", nTriangles[11]);             //讀取袋子
STriangle* triArray_plus = LoadStlBinary("model/plus.STL", nTriangles[12]);             //讀取袋子
STriangle* triArray_do_ex = LoadStlBinary("model/do_ex.STL", nTriangles[13]);             //讀取袋子
STriangle* triArray_la_ex = LoadStlBinary("model/la_ex.STL", nTriangles[14]);             //讀取袋子
//鋼琴本體
STriangle* triArray_main1 = LoadStlBinary("model/main1.STL", nTriangles[15]);             //讀取袋子
STriangle* triArray_main2 = LoadStlBinary("model/main2.STL", nTriangles[16]);             //讀取袋子
STriangle* triArray_main3 = LoadStlBinary("model/main3.STL", nTriangles[17]);             //讀取袋子
STriangle* triArray_main4 = LoadStlBinary("model/main4.STL", nTriangles[18]);             //讀取袋子
//延音踏板零件
STriangle* triArray_load1 = LoadStlBinary("model/load1.STL", nTriangles[19]);             //讀取袋子
STriangle* triArray_load2 = LoadStlBinary("model/load2.STL", nTriangles[20]);             //讀取袋子
STriangle* triArray_load3 = LoadStlBinary("model/load3.STL", nTriangles[21]);             //讀取袋子
STriangle* triArray_load4 = LoadStlBinary("model/load4.STL", nTriangles[22]);             //讀取袋子
STriangle* triArray_load5 = LoadStlBinary("model/load5.STL", nTriangles[23]);             //讀取袋子

GLfloat pos[] = { 0.0f, 0.0f, 3000.0f, 1.0f };
GLfloat fNoLight[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat spot[] = { 0.0f, 0.0f, -1.0f };               //設定觀察者看的方向

//自轉角度
GLfloat xsRot = 0.0f;
GLfloat doRot[9] = { 0.0f }, reRot[9] = { 0.0f }, miRot[9] = { 0.0f }, faRot[9] = { 0.0f }, soRot[9] = { 0.0f }, laRot[9] = { 0.0f }, siRot[9] = { 0.0f }, plusRot[9][6] = { 0.0f };
GLfloat part5_doRot[9] = { 0.0f }, part5_reRot[9] = { 0.0f }, part5_miRot[9] = { 0.0f }, part5_faRot[9] = { 0.0f }, part5_soRot[9] = { 0.0f }, part5_laRot[9] = { 0.0f }, part5_siRot[9] = { 0.0f }, part5_plusRot[9][6] = { 0.0f };
GLfloat load_Rot[3] = { 0.0f };
//公轉角度
GLfloat xaRot = 0.0f;
GLfloat yaRot = 0.0f;
//伸縮視角參數
GLfloat translate = 0.0f;
//分解、合成鋼琴參數
GLfloat tran[2] = { 0 }, tran_i[2] = { 0 };
//貼圖參數
GLuint textures[9];
GLbyte *pBytes;
GLint iWidth = 0, iHeight = 0, iComponents = 0;
GLenum eFormat;
const char *szTextureFiles[7] = { " ", "image/gold.tga", "image/wood.tga", "image/CU.tga", "image/melt.tga", "image/black.tga", "image/wood.tga"};

//display
#define display_piano 301
#define ndisplay_piano 302
#define display_button 303
#define ndisplay_button 304
#define display_load 305
#define ndisplay_load 306
#define piano_break 307
#define piano_combine 308
#define stop 310
#define play_music1 311
#define play_music2 312
#define play_music3 313
#define reset 314
int idisplay_piano = display_piano;
int idisplay_button = display_button;
int idisplay_load = display_load;
int ipiano_break_combine = piano_combine;
int iplaymusic = reset;

//按鍵按下
#define press_C1 1
#define press_C2 2
#define press_C3 3
#define press_C4 4
#define press_C5 5
#define press_C6 6
#define press_C7 7
#define press_C8 8

#define press_C1P 9
#define press_C2P 10
#define press_C3P 11
#define press_C4P 12
#define press_C5P 13
#define press_C6P 14
#define press_C7P 15

#define press_D1 16
#define press_D2 17
#define press_D3 18
#define press_D4 19
#define press_D5 20
#define press_D6 21
#define press_D7 22

#define press_D1P 23
#define press_D2P 24
#define press_D3P 25
#define press_D4P 26
#define press_D5P 27
#define press_D6P 28
#define press_D7P 29

#define press_E1 30
#define press_E2 31
#define press_E3 32
#define press_E4 33
#define press_E5 34
#define press_E6 35
#define press_E7 36

#define press_F1 37
#define press_F2 38
#define press_F3 39
#define press_F4 40
#define press_F5 41
#define press_F6 42
#define press_F7 43

#define press_F1P 44
#define press_F2P 45
#define press_F3P 46
#define press_F4P 47
#define press_F5P 48
#define press_F6P 49
#define press_F7P 50

#define press_G1 51
#define press_G2 52
#define press_G3 53
#define press_G4 54
#define press_G5 55
#define press_G6 56
#define press_G7 57

#define press_G1P 58
#define press_G2P 59
#define press_G3P 60
#define press_G4P 61
#define press_G5P 62
#define press_G6P 63
#define press_G7P 64

#define press_A0 65
#define press_A1 66
#define press_A2 67
#define press_A3 68
#define press_A4 69
#define press_A5 70
#define press_A6 71
#define press_A7 72

#define press_A0P 73
#define press_A1P 74
#define press_A2P 75
#define press_A3P 76
#define press_A4P 77
#define press_A5P 78
#define press_A6P 79
#define press_A7P 80

#define press_B0 81
#define press_B1 82
#define press_B2 83
#define press_B3 84
#define press_B4 85
#define press_B5 86
#define press_B6 87
#define press_B7 88


//按鍵放開
#define ease_C1 101
#define ease_C2 102
#define ease_C3 103
#define ease_C4 104
#define ease_C5 105
#define ease_C6 106
#define ease_C7 107
#define ease_C8 108

#define ease_C1P 109
#define ease_C2P 110
#define ease_C3P 111
#define ease_C4P 112
#define ease_C5P 113
#define ease_C6P 114
#define ease_C7P 115

#define ease_D1 116
#define ease_D2 117
#define ease_D3 118
#define ease_D4 119
#define ease_D5 120
#define ease_D6 121
#define ease_D7 122

#define ease_D1P 123
#define ease_D2P 124
#define ease_D3P 125
#define ease_D4P 126
#define ease_D5P 127
#define ease_D6P 128
#define ease_D7P 129

#define ease_E1 130
#define ease_E2 131
#define ease_E3 132
#define ease_E4 133
#define ease_E5 134
#define ease_E6 135
#define ease_E7 136

#define ease_F1 137
#define ease_F2 138
#define ease_F3 139
#define ease_F4 140
#define ease_F5 141
#define ease_F6 142
#define ease_F7 143

#define ease_F1P 144
#define ease_F2P 145
#define ease_F3P 146
#define ease_F4P 147
#define ease_F5P 148
#define ease_F6P 149
#define ease_F7P 150

#define ease_G1 151
#define ease_G2 152
#define ease_G3 153
#define ease_G4 154
#define ease_G5 155
#define ease_G6 156
#define ease_G7 157

#define ease_G1P 158
#define ease_G2P 159
#define ease_G3P 160
#define ease_G4P 161
#define ease_G5P 162
#define ease_G6P 163
#define ease_G7P 164

#define ease_A0 165
#define ease_A1 166
#define ease_A2 167
#define ease_A3 168
#define ease_A4 169
#define ease_A5 170
#define ease_A6 171
#define ease_A7 172

#define ease_A0P 173
#define ease_A1P 174
#define ease_A2P 175
#define ease_A3P 176
#define ease_A4P 177
#define ease_A5P 178
#define ease_A6P 179
#define ease_A7P 180

#define ease_B0 181
#define ease_B1 182
#define ease_B2 183
#define ease_B3 184
#define ease_B4 185
#define ease_B5 186
#define ease_B6 187
#define ease_B7 188


//load TGA
#pragma pack(1)
typedef struct
{
	GLbyte	identsize;              // Size of ID field that follows header (0)
	GLbyte	colorMapType;           // 0 = None, 1 = paletted
	GLbyte	imageType;              // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
	unsigned short	colorMapStart;          // First colour map entry
	unsigned short	colorMapLength;         // Number of colors
	unsigned char 	colorMapBits;   // bits per palette entry
	unsigned short	xstart;                 // image x origin
	unsigned short	ystart;                 // image y origin
	unsigned short	width;                  // width in pixels
	unsigned short	height;                 // height in pixels
	GLbyte	bits;                   // bits per pixel (8 16, 24, 32)
	GLbyte	descriptor;             // image descriptor
} TGAHEADER;
#pragma pack(8)

GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
{
	FILE *pFile;			// File pointer
	TGAHEADER tgaHeader;		// TGA file header
	unsigned long lImageSize;		// Size in bytes of image
	short sDepth;			// Pixel depth;
	GLbyte	*pBits = NULL;          // Pointer to bits

	// Default/Failed values
	*iWidth = 0;
	*iHeight = 0;
	*eFormat = GL_BGR_EXT;
	*iComponents = GL_RGB8;

	// Attempt to open the fil
	pFile = fopen(szFileName, "rb");
	if (pFile == NULL)
		return NULL;

	// Read in header (binary)
	fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);

	// Do byte swap for big vs little endian
#ifdef __APPLE__
	LITTLE_ENDIAN_WORD(&tgaHeader.colorMapStart);
	LITTLE_ENDIAN_WORD(&tgaHeader.colorMapLength);
	LITTLE_ENDIAN_WORD(&tgaHeader.xstart);
	LITTLE_ENDIAN_WORD(&tgaHeader.ystart);
	LITTLE_ENDIAN_WORD(&tgaHeader.width);
	LITTLE_ENDIAN_WORD(&tgaHeader.height);
#endif

	// Get width, height, and depth of texture
	*iWidth = tgaHeader.width;
	*iHeight = tgaHeader.height;
	sDepth = tgaHeader.bits / 8;

	// Put some validity checks here. Very simply, I only understand
	// or care about 8, 24, or 32 bit targa's.
	if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
		return NULL;

	// Calculate size of image buffer
	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

	// Allocate memory and check for success
	pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
	if (pBits == NULL)
		return NULL;

	// Read in the bits
	// Check for read error. This should catch RLE or other 
	// weird formats that I don't want to recognize
	if (fread(pBits, lImageSize, 1, pFile) != 1)
	{
		free(pBits);
		return NULL;
	}

	// Set OpenGL format expected
	switch (sDepth)
	{
	case 3:     // Most likely case
		*eFormat = GL_BGR_EXT;
		*iComponents = GL_RGB8;
		break;
	case 4:
		*eFormat = GL_BGRA_EXT;
		*iComponents = GL_RGBA8;
		break;
	case 1:
		*eFormat = GL_LUMINANCE;
		*iComponents = GL_LUMINANCE8;
		break;
	};


	// Done with File
	fclose(pFile);

	// Return pointer to image data
	return pBits;
}

//讀取模型檔
void InitVBO_part1(void)
{
	if (triArray_part1)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[0]; i++)
		{
			//a
			if (triArray_part1[i].a[0] < min[0])
				min[0] = triArray_part1[i].a[0];
			else if (triArray_part1[i].a[0] > max[0])
				max[0] = triArray_part1[i].a[0];

			if (triArray_part1[i].a[1] < min[1])
				min[1] = triArray_part1[i].a[1];
			else if (triArray_part1[i].a[1] > max[1])
				max[1] = triArray_part1[i].a[1];

			if (triArray_part1[i].a[2] < min[2])
				min[2] = triArray_part1[i].a[2];
			else if (triArray_part1[i].a[2] > max[2])
				max[2] = triArray_part1[i].a[2];

			//b
			if (triArray_part1[i].b[0] < min[0])
				min[0] = triArray_part1[i].b[0];
			else if (triArray_part1[i].b[0] > max[0])
				max[0] = triArray_part1[i].b[0];

			if (triArray_part1[i].b[1] < min[1])
				min[1] = triArray_part1[i].b[1];
			else if (triArray_part1[i].b[1] > max[1])
				max[1] = triArray_part1[i].b[1];

			if (triArray_part1[i].b[2] < min[2])
				min[2] = triArray_part1[i].b[2];
			else if (triArray_part1[i].b[2] > max[2])
				max[2] = triArray_part1[i].b[2];

			//c
			if (triArray_part1[i].c[0] < min[0])
				min[0] = triArray_part1[i].c[0];
			else if (triArray_part1[i].c[0] > max[0])
				max[0] = triArray_part1[i].c[0];

			if (triArray_part1[i].c[1] < min[1])
				min[1] = triArray_part1[i].c[1];
			else if (triArray_part1[i].c[1] > max[1])
				max[1] = triArray_part1[i].c[1];

			if (triArray_part1[i].c[2] < min[2])
				min[2] = triArray_part1[i].c[2];
			else if (triArray_part1[i].c[2] > max[2])
				max[2] = triArray_part1[i].c[2];
		}
		cent[0][0] = (-min[2] - max[2]) / 2.0f;
		cent[0][1] = (min[1] + max[1]) / 2.0f;
		cent[0][2] = (min[0] + max[0]) / 2.0f;
	}


	VBOv[0] = new float[nTriangles[0] * 9];
	VBOn[0] = new float[nTriangles[0] * 9];
	int i;

	for (i = 0; i<nTriangles[0]; i++)
	{

		VBOv[0][i * 9 + 0] = -triArray_part1[i].a[2];
		VBOv[0][i * 9 + 1] = triArray_part1[i].a[1];
		VBOv[0][i * 9 + 2] = triArray_part1[i].a[0];

		VBOv[0][i * 9 + 3] = -triArray_part1[i].b[2];
		VBOv[0][i * 9 + 4] = triArray_part1[i].b[1];
		VBOv[0][i * 9 + 5] = triArray_part1[i].b[0];

		VBOv[0][i * 9 + 6] = -triArray_part1[i].c[2];
		VBOv[0][i * 9 + 7] = triArray_part1[i].c[1];
		VBOv[0][i * 9 + 8] = triArray_part1[i].c[0];



		VBOn[0][i * 9 + 0] = -triArray_part1[i].n[2];
		VBOn[0][i * 9 + 1] = triArray_part1[i].n[1];
		VBOn[0][i * 9 + 2] = triArray_part1[i].n[0];

		VBOn[0][i * 9 + 3] = -triArray_part1[i].n[2];
		VBOn[0][i * 9 + 4] = triArray_part1[i].n[1];
		VBOn[0][i * 9 + 5] = triArray_part1[i].n[0];

		VBOn[0][i * 9 + 6] = -triArray_part1[i].n[2];
		VBOn[0][i * 9 + 7] = triArray_part1[i].n[1];
		VBOn[0][i * 9 + 8] = triArray_part1[i].n[0];


	}



	glGenBuffers(2, VBO_index_part1);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[0] * 9 * sizeof(float), VBOv[0], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[0] * 9 * sizeof(float), VBOn[0], GL_STATIC_DRAW);



}
void InitVBO_part2(void)
{
	if (triArray_part2)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[1]; i++)
		{
			//a
			if (triArray_part2[i].a[0] < min[0])
				min[0] = triArray_part2[i].a[0];
			else if (triArray_part2[i].a[0] > max[0])
				max[0] = triArray_part2[i].a[0];

			if (triArray_part2[i].a[1] < min[1])
				min[1] = triArray_part2[i].a[1];
			else if (triArray_part2[i].a[1] > max[1])
				max[1] = triArray_part2[i].a[1];

			if (triArray_part2[i].a[2] < min[2])
				min[2] = triArray_part2[i].a[2];
			else if (triArray_part2[i].a[2] > max[2])
				max[2] = triArray_part2[i].a[2];

			//b
			if (triArray_part2[i].b[0] < min[0])
				min[0] = triArray_part2[i].b[0];
			else if (triArray_part2[i].b[0] > max[0])
				max[0] = triArray_part2[i].b[0];

			if (triArray_part2[i].b[1] < min[1])
				min[1] = triArray_part2[i].b[1];
			else if (triArray_part2[i].b[1] > max[1])
				max[1] = triArray_part2[i].b[1];

			if (triArray_part2[i].b[2] < min[2])
				min[2] = triArray_part2[i].b[2];
			else if (triArray_part2[i].b[2] > max[2])
				max[2] = triArray_part2[i].b[2];

			//c
			if (triArray_part2[i].c[0] < min[0])
				min[0] = triArray_part2[i].c[0];
			else if (triArray_part2[i].c[0] > max[0])
				max[0] = triArray_part2[i].c[0];

			if (triArray_part2[i].c[1] < min[1])
				min[1] = triArray_part2[i].c[1];
			else if (triArray_part2[i].c[1] > max[1])
				max[1] = triArray_part2[i].c[1];

			if (triArray_part2[i].c[2] < min[2])
				min[2] = triArray_part2[i].c[2];
			else if (triArray_part2[i].c[2] > max[2])
				max[2] = triArray_part2[i].c[2];
		}
		cent[1][0] = (min[0] + max[0]) / 2.0f;
		cent[1][1] = (min[1] + max[1]) / 2.0f;
		cent[1][2] = (min[2] + max[2]) / 2.0f;


	}


	VBOv[1] = new float[nTriangles[1] * 9];
	VBOn[1] = new float[nTriangles[1] * 9];
	int i;


	for (i = 0; i<nTriangles[1]; i++)
	{

		VBOv[1][i * 9 + 0] = triArray_part2[i].a[0];
		VBOv[1][i * 9 + 1] = triArray_part2[i].a[1];
		VBOv[1][i * 9 + 2] = triArray_part2[i].a[2];

		VBOv[1][i * 9 + 3] = triArray_part2[i].b[0];
		VBOv[1][i * 9 + 4] = triArray_part2[i].b[1];
		VBOv[1][i * 9 + 5] = triArray_part2[i].b[2];

		VBOv[1][i * 9 + 6] = triArray_part2[i].c[0];
		VBOv[1][i * 9 + 7] = triArray_part2[i].c[1];
		VBOv[1][i * 9 + 8] = triArray_part2[i].c[2];



		VBOn[1][i * 9 + 0] = triArray_part2[i].n[0];
		VBOn[1][i * 9 + 1] = triArray_part2[i].n[1];
		VBOn[1][i * 9 + 2] = triArray_part2[i].n[2];

		VBOn[1][i * 9 + 3] = triArray_part2[i].n[0];
		VBOn[1][i * 9 + 4] = triArray_part2[i].n[1];
		VBOn[1][i * 9 + 5] = triArray_part2[i].n[2];

		VBOn[1][i * 9 + 6] = triArray_part2[i].n[0];
		VBOn[1][i * 9 + 7] = triArray_part2[i].n[1];
		VBOn[1][i * 9 + 8] = triArray_part2[i].n[2];


	}



	glGenBuffers(2, VBO_index_part2);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[1] * 9 * sizeof(float), VBOv[1], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[1] * 9 * sizeof(float), VBOn[1], GL_STATIC_DRAW);



}
void InitVBO_part4(void)
{
	if (triArray_part4)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[3]; i++)
		{
			//a
			if (triArray_part4[i].a[0] < min[0])
				min[0] = triArray_part4[i].a[0];
			else if (triArray_part4[i].a[0] > max[0])
				max[0] = triArray_part4[i].a[0];

			if (triArray_part4[i].a[1] < min[1])
				min[1] = triArray_part4[i].a[1];
			else if (triArray_part4[i].a[1] > max[1])
				max[1] = triArray_part4[i].a[1];

			if (triArray_part4[i].a[2] < min[2])
				min[2] = triArray_part4[i].a[2];
			else if (triArray_part4[i].a[2] > max[2])
				max[2] = triArray_part4[i].a[2];

			//b
			if (triArray_part4[i].b[0] < min[0])
				min[0] = triArray_part4[i].b[0];
			else if (triArray_part4[i].b[0] > max[0])
				max[0] = triArray_part4[i].b[0];

			if (triArray_part4[i].b[1] < min[1])
				min[1] = triArray_part4[i].b[1];
			else if (triArray_part4[i].b[1] > max[1])
				max[1] = triArray_part4[i].b[1];

			if (triArray_part4[i].b[2] < min[2])
				min[2] = triArray_part4[i].b[2];
			else if (triArray_part4[i].b[2] > max[2])
				max[2] = triArray_part4[i].b[2];

			//c
			if (triArray_part4[i].c[0] < min[0])
				min[0] = triArray_part4[i].c[0];
			else if (triArray_part4[i].c[0] > max[0])
				max[0] = triArray_part4[i].c[0];

			if (triArray_part4[i].c[1] < min[1])
				min[1] = triArray_part4[i].c[1];
			else if (triArray_part4[i].c[1] > max[1])
				max[1] = triArray_part4[i].c[1];

			if (triArray_part4[i].c[2] < min[2])
				min[2] = triArray_part4[i].c[2];
			else if (triArray_part4[i].c[2] > max[2])
				max[2] = triArray_part4[i].c[2];
		}
		cent[3][0] = (min[0] + max[0]) / 2.0f;
		cent[3][1] = (min[1] + max[1]) / 2.0f;
		cent[3][2] = (min[2] + max[2]) / 2.0f;


	}

	VBOv[3] = new float[nTriangles[3] * 9];
	VBOn[3] = new float[nTriangles[3] * 9];
	int i;


	for (i = 0; i<nTriangles[3]; i++)
	{

		VBOv[3][i * 9 + 0] = triArray_part4[i].a[0];
		VBOv[3][i * 9 + 1] = triArray_part4[i].a[1];
		VBOv[3][i * 9 + 2] = triArray_part4[i].a[2];

		VBOv[3][i * 9 + 3] = triArray_part4[i].b[0];
		VBOv[3][i * 9 + 4] = triArray_part4[i].b[1];
		VBOv[3][i * 9 + 5] = triArray_part4[i].b[2];

		VBOv[3][i * 9 + 6] = triArray_part4[i].c[0];
		VBOv[3][i * 9 + 7] = triArray_part4[i].c[1];
		VBOv[3][i * 9 + 8] = triArray_part4[i].c[2];



		VBOn[3][i * 9 + 0] = triArray_part4[i].n[0];
		VBOn[3][i * 9 + 1] = triArray_part4[i].n[1];
		VBOn[3][i * 9 + 2] = triArray_part4[i].n[2];

		VBOn[3][i * 9 + 3] = triArray_part4[i].n[0];
		VBOn[3][i * 9 + 4] = triArray_part4[i].n[1];
		VBOn[3][i * 9 + 5] = triArray_part4[i].n[2];

		VBOn[3][i * 9 + 6] = triArray_part4[i].n[0];
		VBOn[3][i * 9 + 7] = triArray_part4[i].n[1];
		VBOn[3][i * 9 + 8] = triArray_part4[i].n[2];


	}



	glGenBuffers(2, VBO_index_part4);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part4[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[3] * 9 * sizeof(float), VBOv[3], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part4[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[3] * 9 * sizeof(float), VBOn[3], GL_STATIC_DRAW);



}
void InitVBO_part5(void)
{
	if (triArray_part5)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[4]; i++)
		{
			//a
			if (triArray_part5[i].a[0] < min[0])
				min[0] = triArray_part5[i].a[0];
			else if (triArray_part5[i].a[0] > max[0])
				max[0] = triArray_part5[i].a[0];

			if (triArray_part5[i].a[1] < min[1])
				min[1] = triArray_part5[i].a[1];
			else if (triArray_part5[i].a[1] > max[1])
				max[1] = triArray_part5[i].a[1];

			if (triArray_part5[i].a[2] < min[2])
				min[2] = triArray_part5[i].a[2];
			else if (triArray_part5[i].a[2] > max[2])
				max[2] = triArray_part5[i].a[2];

			//b
			if (triArray_part5[i].b[0] < min[0])
				min[0] = triArray_part5[i].b[0];
			else if (triArray_part5[i].b[0] > max[0])
				max[0] = triArray_part5[i].b[0];

			if (triArray_part5[i].b[1] < min[1])
				min[1] = triArray_part5[i].b[1];
			else if (triArray_part5[i].b[1] > max[1])
				max[1] = triArray_part5[i].b[1];

			if (triArray_part5[i].b[2] < min[2])
				min[2] = triArray_part5[i].b[2];
			else if (triArray_part5[i].b[2] > max[2])
				max[2] = triArray_part5[i].b[2];

			//c
			if (triArray_part5[i].c[0] < min[0])
				min[0] = triArray_part5[i].c[0];
			else if (triArray_part5[i].c[0] > max[0])
				max[0] = triArray_part5[i].c[0];

			if (triArray_part5[i].c[1] < min[1])
				min[1] = triArray_part5[i].c[1];
			else if (triArray_part5[i].c[1] > max[1])
				max[1] = triArray_part5[i].c[1];

			if (triArray_part5[i].c[2] < min[2])
				min[2] = triArray_part5[i].c[2];
			else if (triArray_part5[i].c[2] > max[2])
				max[2] = triArray_part5[i].c[2];
		}
		cent[4][0] = (min[0] + max[0]) / 2.0f;
		cent[4][1] = (min[1] + max[1]) / 2.0f;
		cent[4][2] = (min[2] + max[2]) / 2.0f;


	}



	VBOv[4] = new float[nTriangles[4] * 9];
	VBOn[4] = new float[nTriangles[4] * 9];
	int i;


	for (i = 0; i<nTriangles[4]; i++)
	{

		VBOv[4][i * 9 + 0] = -triArray_part5[i].a[0];
		VBOv[4][i * 9 + 1] = triArray_part5[i].a[1];
		VBOv[4][i * 9 + 2] = -triArray_part5[i].a[2];

		VBOv[4][i * 9 + 3] = -triArray_part5[i].b[0];
		VBOv[4][i * 9 + 4] = triArray_part5[i].b[1];
		VBOv[4][i * 9 + 5] = -triArray_part5[i].b[2];

		VBOv[4][i * 9 + 6] = -triArray_part5[i].c[0];
		VBOv[4][i * 9 + 7] = triArray_part5[i].c[1];
		VBOv[4][i * 9 + 8] = -triArray_part5[i].c[2];



		VBOn[4][i * 9 + 0] = -triArray_part5[i].n[0];
		VBOn[4][i * 9 + 1] = triArray_part5[i].n[1];
		VBOn[4][i * 9 + 2] = -triArray_part5[i].n[2];

		VBOn[4][i * 9 + 3] = -triArray_part5[i].n[0];
		VBOn[4][i * 9 + 4] = triArray_part5[i].n[1];
		VBOn[4][i * 9 + 5] = -triArray_part5[i].n[2];

		VBOn[4][i * 9 + 6] = -triArray_part5[i].n[0];
		VBOn[4][i * 9 + 7] = triArray_part5[i].n[1];
		VBOn[4][i * 9 + 8] = -triArray_part5[i].n[2];


	}



	glGenBuffers(2, VBO_index_part5);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[4] * 9 * sizeof(float), VBOv[4], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[4] * 9 * sizeof(float), VBOn[4], GL_STATIC_DRAW);



}
void InitVBO_do(void)
{
	if (triArray_do)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[5]; i++)
		{
			//a
			if (triArray_do[i].a[0] < min[0])
				min[0] = triArray_do[i].a[0];
			else if (triArray_do[i].a[0] > max[0])
				max[0] = triArray_do[i].a[0];

			if (triArray_do[i].a[1] < min[1])
				min[1] = triArray_do[i].a[1];
			else if (triArray_do[i].a[1] > max[1])
				max[1] = triArray_do[i].a[1];

			if (triArray_do[i].a[2] < min[2])
				min[2] = triArray_do[i].a[2];
			else if (triArray_do[i].a[2] > max[2])
				max[2] = triArray_do[i].a[2];

			//b
			if (triArray_do[i].b[0] < min[0])
				min[0] = triArray_do[i].b[0];
			else if (triArray_do[i].b[0] > max[0])
				max[0] = triArray_do[i].b[0];

			if (triArray_do[i].b[1] < min[1])
				min[1] = triArray_do[i].b[1];
			else if (triArray_do[i].b[1] > max[1])
				max[1] = triArray_do[i].b[1];

			if (triArray_do[i].b[2] < min[2])
				min[2] = triArray_do[i].b[2];
			else if (triArray_do[i].b[2] > max[2])
				max[2] = triArray_do[i].b[2];

			//c
			if (triArray_do[i].c[0] < min[0])
				min[0] = triArray_do[i].c[0];
			else if (triArray_do[i].c[0] > max[0])
				max[0] = triArray_do[i].c[0];

			if (triArray_do[i].c[1] < min[1])
				min[1] = triArray_do[i].c[1];
			else if (triArray_do[i].c[1] > max[1])
				max[1] = triArray_do[i].c[1];

			if (triArray_do[i].c[2] < min[2])
				min[2] = triArray_do[i].c[2];
			else if (triArray_do[i].c[2] > max[2])
				max[2] = triArray_do[i].c[2];
		}
		cent[5][0] = (min[2] - max[2]) / 2.0f;
		cent[5][1] = (min[1] + max[1]) / 2.0f;
		cent[5][2] = (min[0] + max[0]) / 2.0f;


	}



	VBOv[5] = new float[nTriangles[5] * 9];
	VBOn[5] = new float[nTriangles[5] * 9];
	int i;


	for (i = 0; i<nTriangles[5]; i++)
	{

		VBOv[5][i * 9 + 0] = -triArray_do[i].a[2]; // -300
		VBOv[5][i * 9 + 1] = triArray_do[i].a[1];//-17.5
		VBOv[5][i * 9 + 2] = triArray_do[i].a[0];//+15.5

		VBOv[5][i * 9 + 3] = -triArray_do[i].b[2];
		VBOv[5][i * 9 + 4] = triArray_do[i].b[1] ;
		VBOv[5][i * 9 + 5] = triArray_do[i].b[0];

		VBOv[5][i * 9 + 6] = -triArray_do[i].c[2];
		VBOv[5][i * 9 + 7] = triArray_do[i].c[1];
		VBOv[5][i * 9 + 8] = triArray_do[i].c[0];



		VBOn[5][i * 9 + 0] = -triArray_do[i].n[2];
		VBOn[5][i * 9 + 1] = triArray_do[i].n[1];
		VBOn[5][i * 9 + 2] = triArray_do[i].n[0];

		VBOn[5][i * 9 + 3] = -triArray_do[i].n[2];
		VBOn[5][i * 9 + 4] = triArray_do[i].n[1];
		VBOn[5][i * 9 + 5] = triArray_do[i].n[0];

		VBOn[5][i * 9 + 6] = -triArray_do[i].n[2];
		VBOn[5][i * 9 + 7] = triArray_do[i].n[1];
		VBOn[5][i * 9 + 8] = triArray_do[i].n[0];


	}



	glGenBuffers(2, VBO_index_do);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_do[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[5] * 9 * sizeof(float), VBOv[5], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_do[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[5] * 9 * sizeof(float), VBOn[5], GL_STATIC_DRAW);



}
void InitVBO_re(void)
{
	if (triArray_re)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[6]; i++)
		{
			//a
			if (triArray_re[i].a[0] < min[0])
				min[0] = triArray_re[i].a[0];
			else if (triArray_re[i].a[0] > max[0])
				max[0] = triArray_re[i].a[0];

			if (triArray_re[i].a[1] < min[1])
				min[1] = triArray_re[i].a[1];
			else if (triArray_re[i].a[1] > max[1])
				max[1] = triArray_re[i].a[1];

			if (triArray_re[i].a[2] < min[2])
				min[2] = triArray_re[i].a[2];
			else if (triArray_re[i].a[2] > max[2])
				max[2] = triArray_re[i].a[2];

			//b
			if (triArray_re[i].b[0] < min[0])
				min[0] = triArray_re[i].b[0];
			else if (triArray_re[i].b[0] > max[0])
				max[0] = triArray_re[i].b[0];

			if (triArray_re[i].b[1] < min[1])
				min[1] = triArray_re[i].b[1];
			else if (triArray_re[i].b[1] > max[1])
				max[1] = triArray_re[i].b[1];

			if (triArray_re[i].b[2] < min[2])
				min[2] = triArray_re[i].b[2];
			else if (triArray_re[i].b[2] > max[2])
				max[2] = triArray_re[i].b[2];

			//c
			if (triArray_re[i].c[0] < min[0])
				min[0] = triArray_re[i].c[0];
			else if (triArray_re[i].c[0] > max[0])
				max[0] = triArray_re[i].c[0];

			if (triArray_re[i].c[1] < min[1])
				min[1] = triArray_re[i].c[1];
			else if (triArray_re[i].c[1] > max[1])
				max[1] = triArray_re[i].c[1];

			if (triArray_re[i].c[2] < min[2])
				min[2] = triArray_re[i].c[2];
			else if (triArray_re[i].c[2] > max[2])
				max[2] = triArray_re[i].c[2];
		}
		cent[6][0] = (min[2] - max[2]) / 2.0f;
		cent[6][1] = (min[1] + max[1]) / 2.0f;
		cent[6][2] = (min[0] + max[0]) / 2.0f;

	}




	VBOv[6] = new float[nTriangles[6] * 9];
	VBOn[6] = new float[nTriangles[6] * 9];
	int i;


	for (i = 0; i<nTriangles[6]; i++)
	{

		VBOv[6][i * 9 + 0] = -triArray_re[i].a[2]; // -300
		VBOv[6][i * 9 + 1] = triArray_re[i].a[1];//-17.5
		VBOv[6][i * 9 + 2] = triArray_re[i].a[0];//+15.5

		VBOv[6][i * 9 + 3] = -triArray_re[i].b[2];
		VBOv[6][i * 9 + 4] = triArray_re[i].b[1];
		VBOv[6][i * 9 + 5] = triArray_re[i].b[0];

		VBOv[6][i * 9 + 6] = -triArray_re[i].c[2];
		VBOv[6][i * 9 + 7] = triArray_re[i].c[1];
		VBOv[6][i * 9 + 8] = triArray_re[i].c[0];



		VBOn[6][i * 9 + 0] = -triArray_re[i].n[2];
		VBOn[6][i * 9 + 1] = triArray_re[i].n[1];
		VBOn[6][i * 9 + 2] = triArray_re[i].n[0];

		VBOn[6][i * 9 + 3] = -triArray_re[i].n[2];
		VBOn[6][i * 9 + 4] = triArray_re[i].n[1];
		VBOn[6][i * 9 + 5] = triArray_re[i].n[0];

		VBOn[6][i * 9 + 6] = -triArray_re[i].n[2];
		VBOn[6][i * 9 + 7] = triArray_re[i].n[1];
		VBOn[6][i * 9 + 8] = triArray_re[i].n[0];


	}



	glGenBuffers(2, VBO_index_re);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_re[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[6] * 9 * sizeof(float), VBOv[6], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_re[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[6] * 9 * sizeof(float), VBOn[6], GL_STATIC_DRAW);



}
void InitVBO_mi(void)
{
	if (triArray_mi)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[7]; i++)
		{
			//a
			if (triArray_mi[i].a[0] < min[0])
				min[0] = triArray_mi[i].a[0];
			else if (triArray_mi[i].a[0] > max[0])
				max[0] = triArray_mi[i].a[0];

			if (triArray_mi[i].a[1] < min[1])
				min[1] = triArray_mi[i].a[1];
			else if (triArray_mi[i].a[1] > max[1])
				max[1] = triArray_mi[i].a[1];

			if (triArray_mi[i].a[2] < min[2])
				min[2] = triArray_mi[i].a[2];
			else if (triArray_mi[i].a[2] > max[2])
				max[2] = triArray_mi[i].a[2];

			//b
			if (triArray_mi[i].b[0] < min[0])
				min[0] = triArray_mi[i].b[0];
			else if (triArray_mi[i].b[0] > max[0])
				max[0] = triArray_mi[i].b[0];

			if (triArray_mi[i].b[1] < min[1])
				min[1] = triArray_mi[i].b[1];
			else if (triArray_mi[i].b[1] > max[1])
				max[1] = triArray_mi[i].b[1];

			if (triArray_mi[i].b[2] < min[2])
				min[2] = triArray_mi[i].b[2];
			else if (triArray_mi[i].b[2] > max[2])
				max[2] = triArray_mi[i].b[2];

			//c
			if (triArray_mi[i].c[0] < min[0])
				min[0] = triArray_mi[i].c[0];
			else if (triArray_mi[i].c[0] > max[0])
				max[0] = triArray_mi[i].c[0];

			if (triArray_mi[i].c[1] < min[1])
				min[1] = triArray_mi[i].c[1];
			else if (triArray_mi[i].c[1] > max[1])
				max[1] = triArray_mi[i].c[1];

			if (triArray_mi[i].c[2] < min[2])
				min[2] = triArray_mi[i].c[2];
			else if (triArray_mi[i].c[2] > max[2])
				max[2] = triArray_mi[i].c[2];
		}
		cent[7][0] = (min[2] - max[2]) / 2.0f;
		cent[7][1] = (min[1] + max[1]) / 2.0f;
		cent[7][2] = (min[0] + max[0]) / 2.0f;


	}



	VBOv[7] = new float[nTriangles[7] * 9];
	VBOn[7] = new float[nTriangles[7] * 9];
	int i;


	for (i = 0; i<nTriangles[7]; i++)
	{

		VBOv[7][i * 9 + 0] = -triArray_mi[i].a[2]; // -300
		VBOv[7][i * 9 + 1] = triArray_mi[i].a[1];//-17.5
		VBOv[7][i * 9 + 2] = triArray_mi[i].a[0];//+15.5

		VBOv[7][i * 9 + 3] = -triArray_mi[i].b[2];
		VBOv[7][i * 9 + 4] = triArray_mi[i].b[1];
		VBOv[7][i * 9 + 5] = triArray_mi[i].b[0];

		VBOv[7][i * 9 + 6] = -triArray_mi[i].c[2];
		VBOv[7][i * 9 + 7] = triArray_mi[i].c[1];
		VBOv[7][i * 9 + 8] = triArray_mi[i].c[0];



		VBOn[7][i * 9 + 0] = -triArray_mi[i].n[2];
		VBOn[7][i * 9 + 1] = triArray_mi[i].n[1];
		VBOn[7][i * 9 + 2] = triArray_mi[i].n[0];

		VBOn[7][i * 9 + 3] = -triArray_mi[i].n[2];
		VBOn[7][i * 9 + 4] = triArray_mi[i].n[1];
		VBOn[7][i * 9 + 5] = triArray_mi[i].n[0];

		VBOn[7][i * 9 + 6] = -triArray_mi[i].n[2];
		VBOn[7][i * 9 + 7] = triArray_mi[i].n[1];
		VBOn[7][i * 9 + 8] = triArray_mi[i].n[0];


	}



	glGenBuffers(2, VBO_index_mi);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_mi[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[7] * 9 * sizeof(float), VBOv[7], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_mi[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[7] * 9 * sizeof(float), VBOn[7], GL_STATIC_DRAW);



}
void InitVBO_fa(void)
{
	if (triArray_fa)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[8]; i++)
		{
			//a
			if (triArray_fa[i].a[0] < min[0])
				min[0] = triArray_fa[i].a[0];
			else if (triArray_fa[i].a[0] > max[0])
				max[0] = triArray_fa[i].a[0];

			if (triArray_fa[i].a[1] < min[1])
				min[1] = triArray_fa[i].a[1];
			else if (triArray_fa[i].a[1] > max[1])
				max[1] = triArray_fa[i].a[1];

			if (triArray_fa[i].a[2] < min[2])
				min[2] = triArray_fa[i].a[2];
			else if (triArray_fa[i].a[2] > max[2])
				max[2] = triArray_fa[i].a[2];

			//b
			if (triArray_fa[i].b[0] < min[0])
				min[0] = triArray_fa[i].b[0];
			else if (triArray_fa[i].b[0] > max[0])
				max[0] = triArray_fa[i].b[0];

			if (triArray_fa[i].b[1] < min[1])
				min[1] = triArray_fa[i].b[1];
			else if (triArray_fa[i].b[1] > max[1])
				max[1] = triArray_fa[i].b[1];

			if (triArray_fa[i].b[2] < min[2])
				min[2] = triArray_fa[i].b[2];
			else if (triArray_fa[i].b[2] > max[2])
				max[2] = triArray_fa[i].b[2];

			//c
			if (triArray_fa[i].c[0] < min[0])
				min[0] = triArray_fa[i].c[0];
			else if (triArray_fa[i].c[0] > max[0])
				max[0] = triArray_fa[i].c[0];

			if (triArray_fa[i].c[1] < min[1])
				min[1] = triArray_fa[i].c[1];
			else if (triArray_fa[i].c[1] > max[1])
				max[1] = triArray_fa[i].c[1];

			if (triArray_fa[i].c[2] < min[2])
				min[2] = triArray_fa[i].c[2];
			else if (triArray_fa[i].c[2] > max[2])
				max[2] = triArray_fa[i].c[2];
		}
		cent[8][0] = (min[2] - max[2]) / 2.0f;
		cent[8][1] = (min[1] + max[1]) / 2.0f;
		cent[8][2] = (min[0] + max[0]) / 2.0f;


	}



	VBOv[8] = new float[nTriangles[8] * 9];
	VBOn[8] = new float[nTriangles[8] * 9];
	int i;


	for (i = 0; i<nTriangles[8]; i++)
	{

		VBOv[8][i * 9 + 0] = -triArray_fa[i].a[2]; // -300
		VBOv[8][i * 9 + 1] = triArray_fa[i].a[1];//-17.5
		VBOv[8][i * 9 + 2] = triArray_fa[i].a[0];//+15.5

		VBOv[8][i * 9 + 3] = -triArray_fa[i].b[2];
		VBOv[8][i * 9 + 4] = triArray_fa[i].b[1];
		VBOv[8][i * 9 + 5] = triArray_fa[i].b[0];

		VBOv[8][i * 9 + 6] = -triArray_fa[i].c[2];
		VBOv[8][i * 9 + 7] = triArray_fa[i].c[1];
		VBOv[8][i * 9 + 8] = triArray_fa[i].c[0];



		VBOn[8][i * 9 + 0] = -triArray_fa[i].n[2];
		VBOn[8][i * 9 + 1] = triArray_fa[i].n[1];
		VBOn[8][i * 9 + 2] = triArray_fa[i].n[0];

		VBOn[8][i * 9 + 3] = -triArray_fa[i].n[2];
		VBOn[8][i * 9 + 4] = triArray_fa[i].n[1];
		VBOn[8][i * 9 + 5] = triArray_fa[i].n[0];

		VBOn[8][i * 9 + 6] = -triArray_fa[i].n[2];
		VBOn[8][i * 9 + 7] = triArray_fa[i].n[1];
		VBOn[8][i * 9 + 8] = triArray_fa[i].n[0];


	}



	glGenBuffers(2, VBO_index_fa);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_fa[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[8] * 9 * sizeof(float), VBOv[8], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_fa[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[8] * 9 * sizeof(float), VBOn[8], GL_STATIC_DRAW);



}
void InitVBO_so(void)
{
	if (triArray_so)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[9]; i++)
		{
			//a
			if (triArray_so[i].a[0] < min[0])
				min[0] = triArray_so[i].a[0];
			else if (triArray_so[i].a[0] > max[0])
				max[0] = triArray_so[i].a[0];

			if (triArray_so[i].a[1] < min[1])
				min[1] = triArray_so[i].a[1];
			else if (triArray_so[i].a[1] > max[1])
				max[1] = triArray_so[i].a[1];

			if (triArray_so[i].a[2] < min[2])
				min[2] = triArray_so[i].a[2];
			else if (triArray_so[i].a[2] > max[2])
				max[2] = triArray_so[i].a[2];

			//b
			if (triArray_so[i].b[0] < min[0])
				min[0] = triArray_so[i].b[0];
			else if (triArray_so[i].b[0] > max[0])
				max[0] = triArray_so[i].b[0];

			if (triArray_so[i].b[1] < min[1])
				min[1] = triArray_so[i].b[1];
			else if (triArray_so[i].b[1] > max[1])
				max[1] = triArray_so[i].b[1];

			if (triArray_so[i].b[2] < min[2])
				min[2] = triArray_so[i].b[2];
			else if (triArray_so[i].b[2] > max[2])
				max[2] = triArray_so[i].b[2];

			//c
			if (triArray_so[i].c[0] < min[0])
				min[0] = triArray_so[i].c[0];
			else if (triArray_so[i].c[0] > max[0])
				max[0] = triArray_so[i].c[0];

			if (triArray_so[i].c[1] < min[1])
				min[1] = triArray_so[i].c[1];
			else if (triArray_so[i].c[1] > max[1])
				max[1] = triArray_so[i].c[1];

			if (triArray_so[i].c[2] < min[2])
				min[2] = triArray_so[i].c[2];
			else if (triArray_so[i].c[2] > max[2])
				max[2] = triArray_so[i].c[2];
		}
		cent[9][0] = (min[2] - max[2]) / 2.0f;
		cent[9][1] = (min[1] + max[1]) / 2.0f;
		cent[9][2] = (min[0] + max[0]) / 2.0f;


	}



	VBOv[9] = new float[nTriangles[9] * 9];
	VBOn[9] = new float[nTriangles[9] * 9];
	int i;


	for (i = 0; i<nTriangles[9]; i++)
	{

		VBOv[9][i * 9 + 0] = -triArray_so[i].a[2]; // -300
		VBOv[9][i * 9 + 1] = triArray_so[i].a[1];//-17.5
		VBOv[9][i * 9 + 2] = triArray_so[i].a[0];//+15.5

		VBOv[9][i * 9 + 3] = -triArray_so[i].b[2];
		VBOv[9][i * 9 + 4] = triArray_so[i].b[1];
		VBOv[9][i * 9 + 5] = triArray_so[i].b[0];

		VBOv[9][i * 9 + 6] = -triArray_so[i].c[2];
		VBOv[9][i * 9 + 7] = triArray_so[i].c[1];
		VBOv[9][i * 9 + 8] = triArray_so[i].c[0];



		VBOn[9][i * 9 + 0] = -triArray_so[i].n[2];
		VBOn[9][i * 9 + 1] = triArray_so[i].n[1];
		VBOn[9][i * 9 + 2] = triArray_so[i].n[0];

		VBOn[9][i * 9 + 3] = -triArray_so[i].n[2];
		VBOn[9][i * 9 + 4] = triArray_so[i].n[1];
		VBOn[9][i * 9 + 5] = triArray_so[i].n[0];

		VBOn[9][i * 9 + 6] = -triArray_so[i].n[2];
		VBOn[9][i * 9 + 7] = triArray_so[i].n[1];
		VBOn[9][i * 9 + 8] = triArray_so[i].n[0];


	}



	glGenBuffers(2, VBO_index_so);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_so[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[9] * 9 * sizeof(float), VBOv[9], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_so[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[9] * 9 * sizeof(float), VBOn[9], GL_STATIC_DRAW);



}
void InitVBO_la(void)
{
	if (triArray_la)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[10]; i++)
		{
			//a
			if (triArray_la[i].a[0] < min[0])
				min[0] = triArray_la[i].a[0];
			else if (triArray_la[i].a[0] > max[0])
				max[0] = triArray_la[i].a[0];

			if (triArray_la[i].a[1] < min[1])
				min[1] = triArray_la[i].a[1];
			else if (triArray_la[i].a[1] > max[1])
				max[1] = triArray_la[i].a[1];

			if (triArray_la[i].a[2] < min[2])
				min[2] = triArray_la[i].a[2];
			else if (triArray_la[i].a[2] > max[2])
				max[2] = triArray_la[i].a[2];

			//b
			if (triArray_la[i].b[0] < min[0])
				min[0] = triArray_la[i].b[0];
			else if (triArray_la[i].b[0] > max[0])
				max[0] = triArray_la[i].b[0];

			if (triArray_la[i].b[1] < min[1])
				min[1] = triArray_la[i].b[1];
			else if (triArray_la[i].b[1] > max[1])
				max[1] = triArray_la[i].b[1];

			if (triArray_la[i].b[2] < min[2])
				min[2] = triArray_la[i].b[2];
			else if (triArray_la[i].b[2] > max[2])
				max[2] = triArray_la[i].b[2];

			//c
			if (triArray_la[i].c[0] < min[0])
				min[0] = triArray_la[i].c[0];
			else if (triArray_la[i].c[0] > max[0])
				max[0] = triArray_la[i].c[0];

			if (triArray_la[i].c[1] < min[1])
				min[1] = triArray_la[i].c[1];
			else if (triArray_la[i].c[1] > max[1])
				max[1] = triArray_la[i].c[1];

			if (triArray_la[i].c[2] < min[2])
				min[2] = triArray_la[i].c[2];
			else if (triArray_la[i].c[2] > max[2])
				max[2] = triArray_la[i].c[2];
		}
		cent[10][0] = (min[2] - max[2]) / 2.0f;
		cent[10][1] = (min[1] + max[1]) / 2.0f;
		cent[10][2] = (min[0] + max[0]) / 2.0f;


	}



	VBOv[10] = new float[nTriangles[10] * 9];
	VBOn[10] = new float[nTriangles[10] * 9];
	int i;


	for (i = 0; i<nTriangles[10]; i++)
	{

		VBOv[10][i * 9 + 0] = -triArray_la[i].a[2]; // -300
		VBOv[10][i * 9 + 1] = triArray_la[i].a[1];//-17.5
		VBOv[10][i * 9 + 2] = triArray_la[i].a[0];//+15.5

		VBOv[10][i * 9 + 3] = -triArray_la[i].b[2];
		VBOv[10][i * 9 + 4] = triArray_la[i].b[1];
		VBOv[10][i * 9 + 5] = triArray_la[i].b[0];

		VBOv[10][i * 9 + 6] = -triArray_la[i].c[2];
		VBOv[10][i * 9 + 7] = triArray_la[i].c[1];
		VBOv[10][i * 9 + 8] = triArray_la[i].c[0];



		VBOn[10][i * 9 + 0] = -triArray_la[i].n[2];
		VBOn[10][i * 9 + 1] = triArray_la[i].n[1];
		VBOn[10][i * 9 + 2] = triArray_la[i].n[0];

		VBOn[10][i * 9 + 3] = -triArray_la[i].n[2];
		VBOn[10][i * 9 + 4] = triArray_la[i].n[1];
		VBOn[10][i * 9 + 5] = triArray_la[i].n[0];

		VBOn[10][i * 9 + 6] = -triArray_la[i].n[2];
		VBOn[10][i * 9 + 7] = triArray_la[i].n[1];
		VBOn[10][i * 9 + 8] = triArray_la[i].n[0];


	}



	glGenBuffers(2, VBO_index_la);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_la[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[10] * 9 * sizeof(float), VBOv[10], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_la[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[10] * 9 * sizeof(float), VBOn[10], GL_STATIC_DRAW);



}
void InitVBO_si(void)
{
	if (triArray_si)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[11]; i++)
		{
			//a
			if (triArray_si[i].a[0] < min[0])
				min[0] = triArray_si[i].a[0];
			else if (triArray_si[i].a[0] > max[0])
				max[0] = triArray_si[i].a[0];

			if (triArray_si[i].a[1] < min[1])
				min[1] = triArray_si[i].a[1];
			else if (triArray_si[i].a[1] > max[1])
				max[1] = triArray_si[i].a[1];

			if (triArray_si[i].a[2] < min[2])
				min[2] = triArray_si[i].a[2];
			else if (triArray_si[i].a[2] > max[2])
				max[2] = triArray_si[i].a[2];

			//b
			if (triArray_si[i].b[0] < min[0])
				min[0] = triArray_si[i].b[0];
			else if (triArray_si[i].b[0] > max[0])
				max[0] = triArray_si[i].b[0];

			if (triArray_si[i].b[1] < min[1])
				min[1] = triArray_si[i].b[1];
			else if (triArray_si[i].b[1] > max[1])
				max[1] = triArray_si[i].b[1];

			if (triArray_si[i].b[2] < min[2])
				min[2] = triArray_si[i].b[2];
			else if (triArray_si[i].b[2] > max[2])
				max[2] = triArray_si[i].b[2];

			//c
			if (triArray_si[i].c[0] < min[0])
				min[0] = triArray_si[i].c[0];
			else if (triArray_si[i].c[0] > max[0])
				max[0] = triArray_si[i].c[0];

			if (triArray_si[i].c[1] < min[1])
				min[1] = triArray_si[i].c[1];
			else if (triArray_si[i].c[1] > max[1])
				max[1] = triArray_si[i].c[1];

			if (triArray_si[i].c[2] < min[2])
				min[2] = triArray_si[i].c[2];
			else if (triArray_si[i].c[2] > max[2])
				max[2] = triArray_si[i].c[2];
		}
		cent[11][0] = (min[2] - max[2]) / 2.0f;
		cent[11][1] = (min[1] + max[1]) / 2.0f;
		cent[11][2] = (min[0] + max[0]) / 2.0f;

	}



	VBOv[11] = new float[nTriangles[11] * 9];
	VBOn[11] = new float[nTriangles[11] * 9];
	int i;


	for (i = 0; i<nTriangles[11]; i++)
	{

		VBOv[11][i * 9 + 0] = -triArray_si[i].a[2]; // -300
		VBOv[11][i * 9 + 1] = triArray_si[i].a[1];//-17.5
		VBOv[11][i * 9 + 2] = triArray_si[i].a[0];//+15.5

		VBOv[11][i * 9 + 3] = -triArray_si[i].b[2];
		VBOv[11][i * 9 + 4] = triArray_si[i].b[1];
		VBOv[11][i * 9 + 5] = triArray_si[i].b[0];

		VBOv[11][i * 9 + 6] = -triArray_si[i].c[2];
		VBOv[11][i * 9 + 7] = triArray_si[i].c[1];
		VBOv[11][i * 9 + 8] = triArray_si[i].c[0];



		VBOn[11][i * 9 + 0] = -triArray_si[i].n[2];
		VBOn[11][i * 9 + 1] = triArray_si[i].n[1];
		VBOn[11][i * 9 + 2] = triArray_si[i].n[0];

		VBOn[11][i * 9 + 3] = -triArray_si[i].n[2];
		VBOn[11][i * 9 + 4] = triArray_si[i].n[1];
		VBOn[11][i * 9 + 5] = triArray_si[i].n[0];

		VBOn[11][i * 9 + 6] = -triArray_si[i].n[2];
		VBOn[11][i * 9 + 7] = triArray_si[i].n[1];
		VBOn[11][i * 9 + 8] = triArray_si[i].n[0];


	}



	glGenBuffers(2, VBO_index_si);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_si[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[11] * 9 * sizeof(float), VBOv[11], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_si[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[11] * 9 * sizeof(float), VBOn[11], GL_STATIC_DRAW);



}
void InitVBO_plus(void)
{
	if (triArray_plus)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[12]; i++)
		{
			//a
			if (triArray_plus[i].a[0] < min[0])
				min[0] = triArray_plus[i].a[0];
			else if (triArray_plus[i].a[0] > max[0])
				max[0] = triArray_plus[i].a[0];

			if (triArray_plus[i].a[1] < min[1])
				min[1] = triArray_plus[i].a[1];
			else if (triArray_plus[i].a[1] > max[1])
				max[1] = triArray_plus[i].a[1];

			if (triArray_plus[i].a[2] < min[2])
				min[2] = triArray_plus[i].a[2];
			else if (triArray_plus[i].a[2] > max[2])
				max[2] = triArray_plus[i].a[2];

			//b
			if (triArray_plus[i].b[0] < min[0])
				min[0] = triArray_plus[i].b[0];
			else if (triArray_plus[i].b[0] > max[0])
				max[0] = triArray_plus[i].b[0];

			if (triArray_plus[i].b[1] < min[1])
				min[1] = triArray_plus[i].b[1];
			else if (triArray_plus[i].b[1] > max[1])
				max[1] = triArray_plus[i].b[1];

			if (triArray_plus[i].b[2] < min[2])
				min[2] = triArray_plus[i].b[2];
			else if (triArray_plus[i].b[2] > max[2])
				max[2] = triArray_plus[i].b[2];

			//c
			if (triArray_plus[i].c[0] < min[0])
				min[0] = triArray_plus[i].c[0];
			else if (triArray_plus[i].c[0] > max[0])
				max[0] = triArray_plus[i].c[0];

			if (triArray_plus[i].c[1] < min[1])
				min[1] = triArray_plus[i].c[1];
			else if (triArray_plus[i].c[1] > max[1])
				max[1] = triArray_plus[i].c[1];

			if (triArray_plus[i].c[2] < min[2])
				min[2] = triArray_plus[i].c[2];
			else if (triArray_plus[i].c[2] > max[2])
				max[2] = triArray_plus[i].c[2];
		}
		cent[12][0] = (min[2] - max[2]) / 2.0f;
		cent[12][1] = (min[1] + max[1]) / 2.0f;
		cent[12][2] = (min[0] + max[0]) / 2.0f;

	}


	VBOv[12] = new float[nTriangles[12] * 9];
	VBOn[12] = new float[nTriangles[12] * 9];
	int i;


	for (i = 0; i<nTriangles[12]; i++)
	{

		VBOv[12][i * 9 + 0] = -triArray_plus[i].a[2]; // -300
		VBOv[12][i * 9 + 1] = triArray_plus[i].a[1];//-17.5
		VBOv[12][i * 9 + 2] = triArray_plus[i].a[0];//+15.5

		VBOv[12][i * 9 + 3] = -triArray_plus[i].b[2];
		VBOv[12][i * 9 + 4] = triArray_plus[i].b[1];
		VBOv[12][i * 9 + 5] = triArray_plus[i].b[0];

		VBOv[12][i * 9 + 6] = -triArray_plus[i].c[2];
		VBOv[12][i * 9 + 7] = triArray_plus[i].c[1];
		VBOv[12][i * 9 + 8] = triArray_plus[i].c[0];



		VBOn[12][i * 9 + 0] = -triArray_plus[i].n[2];
		VBOn[12][i * 9 + 1] = triArray_plus[i].n[1];
		VBOn[12][i * 9 + 2] = triArray_plus[i].n[0];

		VBOn[12][i * 9 + 3] = -triArray_plus[i].n[2];
		VBOn[12][i * 9 + 4] = triArray_plus[i].n[1];
		VBOn[12][i * 9 + 5] = triArray_plus[i].n[0];

		VBOn[12][i * 9 + 6] = -triArray_plus[i].n[2];
		VBOn[12][i * 9 + 7] = triArray_plus[i].n[1];
		VBOn[12][i * 9 + 8] = triArray_plus[i].n[0];


	}



	glGenBuffers(2, VBO_index_plus);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_plus[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[12] * 9 * sizeof(float), VBOv[12], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_plus[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[12] * 9 * sizeof(float), VBOn[12], GL_STATIC_DRAW);



}
void InitVBO_do_ex(void)
{
	if (triArray_do_ex)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[13]; i++)
		{
			//a
			if (triArray_do_ex[i].a[0] < min[0])
				min[0] = triArray_do_ex[i].a[0];
			else if (triArray_do_ex[i].a[0] > max[0])
				max[0] = triArray_do_ex[i].a[0];

			if (triArray_do_ex[i].a[1] < min[1])
				min[1] = triArray_do_ex[i].a[1];
			else if (triArray_do_ex[i].a[1] > max[1])
				max[1] = triArray_do_ex[i].a[1];

			if (triArray_do_ex[i].a[2] < min[2])
				min[2] = triArray_do_ex[i].a[2];
			else if (triArray_do_ex[i].a[2] > max[2])
				max[2] = triArray_do_ex[i].a[2];

			//b
			if (triArray_do_ex[i].b[0] < min[0])
				min[0] = triArray_do_ex[i].b[0];
			else if (triArray_do_ex[i].b[0] > max[0])
				max[0] = triArray_do_ex[i].b[0];

			if (triArray_do_ex[i].b[1] < min[1])
				min[1] = triArray_do_ex[i].b[1];
			else if (triArray_do_ex[i].b[1] > max[1])
				max[1] = triArray_do_ex[i].b[1];

			if (triArray_do_ex[i].b[2] < min[2])
				min[2] = triArray_do_ex[i].b[2];
			else if (triArray_do_ex[i].b[2] > max[2])
				max[2] = triArray_do_ex[i].b[2];

			//c
			if (triArray_do_ex[i].c[0] < min[0])
				min[0] = triArray_do_ex[i].c[0];
			else if (triArray_do_ex[i].c[0] > max[0])
				max[0] = triArray_do_ex[i].c[0];

			if (triArray_do_ex[i].c[1] < min[1])
				min[1] = triArray_do_ex[i].c[1];
			else if (triArray_do_ex[i].c[1] > max[1])
				max[1] = triArray_do_ex[i].c[1];

			if (triArray_do_ex[i].c[2] < min[2])
				min[2] = triArray_do_ex[i].c[2];
			else if (triArray_do_ex[i].c[2] > max[2])
				max[2] = triArray_do_ex[i].c[2];
		}
		cent[13][0] = (min[2] - max[2]) / 2.0f;
		cent[13][1] = (min[1] + max[1]) / 2.0f;
		cent[13][2] = (min[0] + max[0]) / 2.0f;

	}


	VBOv[13] = new float[nTriangles[13] * 9];
	VBOn[13] = new float[nTriangles[13] * 9];
	int i;


	for (i = 0; i<nTriangles[13]; i++)
	{

		VBOv[13][i * 9 + 0] = -triArray_do_ex[i].a[2]; // -300
		VBOv[13][i * 9 + 1] = triArray_do_ex[i].a[1];//-17.5
		VBOv[13][i * 9 + 2] = triArray_do_ex[i].a[0];//+15.5

		VBOv[13][i * 9 + 3] = -triArray_do_ex[i].b[2];
		VBOv[13][i * 9 + 4] = triArray_do_ex[i].b[1];
		VBOv[13][i * 9 + 5] = triArray_do_ex[i].b[0];

		VBOv[13][i * 9 + 6] = -triArray_do_ex[i].c[2];
		VBOv[13][i * 9 + 7] = triArray_do_ex[i].c[1];
		VBOv[13][i * 9 + 8] = triArray_do_ex[i].c[0];



		VBOn[13][i * 9 + 0] = -triArray_do_ex[i].n[2];
		VBOn[13][i * 9 + 1] = triArray_do_ex[i].n[1];
		VBOn[13][i * 9 + 2] = triArray_do_ex[i].n[0];

		VBOn[13][i * 9 + 3] = -triArray_do_ex[i].n[2];
		VBOn[13][i * 9 + 4] = triArray_do_ex[i].n[1];
		VBOn[13][i * 9 + 5] = triArray_do_ex[i].n[0];

		VBOn[13][i * 9 + 6] = -triArray_do_ex[i].n[2];
		VBOn[13][i * 9 + 7] = triArray_do_ex[i].n[1];
		VBOn[13][i * 9 + 8] = triArray_do_ex[i].n[0];


	}



	glGenBuffers(2, VBO_index_do_ex);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_do_ex[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[13] * 9 * sizeof(float), VBOv[13], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_do_ex[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[13] * 9 * sizeof(float), VBOn[13], GL_STATIC_DRAW);



}
void InitVBO_la_ex(void)
{
	if (triArray_la_ex)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[14]; i++)
		{
			//a
			if (triArray_la_ex[i].a[0] < min[0])
				min[0] = triArray_la_ex[i].a[0];
			else if (triArray_la_ex[i].a[0] > max[0])
				max[0] = triArray_la_ex[i].a[0];

			if (triArray_la_ex[i].a[1] < min[1])
				min[1] = triArray_la_ex[i].a[1];
			else if (triArray_la_ex[i].a[1] > max[1])
				max[1] = triArray_la_ex[i].a[1];

			if (triArray_la_ex[i].a[2] < min[2])
				min[2] = triArray_la_ex[i].a[2];
			else if (triArray_la_ex[i].a[2] > max[2])
				max[2] = triArray_la_ex[i].a[2];

			//b
			if (triArray_la_ex[i].b[0] < min[0])
				min[0] = triArray_la_ex[i].b[0];
			else if (triArray_la_ex[i].b[0] > max[0])
				max[0] = triArray_la_ex[i].b[0];

			if (triArray_la_ex[i].b[1] < min[1])
				min[1] = triArray_la_ex[i].b[1];
			else if (triArray_la_ex[i].b[1] > max[1])
				max[1] = triArray_la_ex[i].b[1];

			if (triArray_la_ex[i].b[2] < min[2])
				min[2] = triArray_la_ex[i].b[2];
			else if (triArray_la_ex[i].b[2] > max[2])
				max[2] = triArray_la_ex[i].b[2];

			//c
			if (triArray_la_ex[i].c[0] < min[0])
				min[0] = triArray_la_ex[i].c[0];
			else if (triArray_la_ex[i].c[0] > max[0])
				max[0] = triArray_la_ex[i].c[0];

			if (triArray_la_ex[i].c[1] < min[1])
				min[1] = triArray_la_ex[i].c[1];
			else if (triArray_la_ex[i].c[1] > max[1])
				max[1] = triArray_la_ex[i].c[1];

			if (triArray_la_ex[i].c[2] < min[2])
				min[2] = triArray_la_ex[i].c[2];
			else if (triArray_la_ex[i].c[2] > max[2])
				max[2] = triArray_la_ex[i].c[2];
		}
		cent[14][0] = (min[2] - max[2]) / 2.0f;
		cent[14][1] = (min[1] + max[1]) / 2.0f;
		cent[14][2] = (min[0] + max[0]) / 2.0f;

	}



	VBOv[14] = new float[nTriangles[14] * 9];
	VBOn[14] = new float[nTriangles[14] * 9];
	int i;


	for (i = 0; i<nTriangles[14]; i++)
	{

		VBOv[14][i * 9 + 0] = -triArray_la_ex[i].a[2]; // -300
		VBOv[14][i * 9 + 1] = triArray_la_ex[i].a[1];//-17.5
		VBOv[14][i * 9 + 2] = triArray_la_ex[i].a[0];//+15.5

		VBOv[14][i * 9 + 3] = -triArray_la_ex[i].b[2];
		VBOv[14][i * 9 + 4] = triArray_la_ex[i].b[1];
		VBOv[14][i * 9 + 5] = triArray_la_ex[i].b[0];

		VBOv[14][i * 9 + 6] = -triArray_la_ex[i].c[2];
		VBOv[14][i * 9 + 7] = triArray_la_ex[i].c[1];
		VBOv[14][i * 9 + 8] = triArray_la_ex[i].c[0];



		VBOn[14][i * 9 + 0] = -triArray_la_ex[i].n[2];
		VBOn[14][i * 9 + 1] = triArray_la_ex[i].n[1];
		VBOn[14][i * 9 + 2] = triArray_la_ex[i].n[0];

		VBOn[14][i * 9 + 3] = -triArray_la_ex[i].n[2];
		VBOn[14][i * 9 + 4] = triArray_la_ex[i].n[1];
		VBOn[14][i * 9 + 5] = triArray_la_ex[i].n[0];

		VBOn[14][i * 9 + 6] = -triArray_la_ex[i].n[2];
		VBOn[14][i * 9 + 7] = triArray_la_ex[i].n[1];
		VBOn[14][i * 9 + 8] = triArray_la_ex[i].n[0];


	}



	glGenBuffers(2, VBO_index_la_ex);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_la_ex[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[14] * 9 * sizeof(float), VBOv[14], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_la_ex[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[14] * 9 * sizeof(float), VBOn[14], GL_STATIC_DRAW);



}
void InitVBO_main1(void)
{
	if (triArray_main1)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[15]; i++)
		{
			//a
			if (triArray_main1[i].a[0] < min[0])
				min[0] = triArray_main1[i].a[0];
			else if (triArray_main1[i].a[0] > max[0])
				max[0] = triArray_main1[i].a[0];

			if (triArray_main1[i].a[1] < min[1])
				min[1] = triArray_main1[i].a[1];
			else if (triArray_main1[i].a[1] > max[1])
				max[1] = triArray_main1[i].a[1];

			if (triArray_main1[i].a[2] < min[2])
				min[2] = triArray_main1[i].a[2];
			else if (triArray_main1[i].a[2] > max[2])
				max[2] = triArray_main1[i].a[2];

			//b
			if (triArray_main1[i].b[0] < min[0])
				min[0] = triArray_main1[i].b[0];
			else if (triArray_main1[i].b[0] > max[0])
				max[0] = triArray_main1[i].b[0];

			if (triArray_main1[i].b[1] < min[1])
				min[1] = triArray_main1[i].b[1];
			else if (triArray_main1[i].b[1] > max[1])
				max[1] = triArray_main1[i].b[1];

			if (triArray_main1[i].b[2] < min[2])
				min[2] = triArray_main1[i].b[2];
			else if (triArray_main1[i].b[2] > max[2])
				max[2] = triArray_main1[i].b[2];

			//c
			if (triArray_main1[i].c[0] < min[0])
				min[0] = triArray_main1[i].c[0];
			else if (triArray_main1[i].c[0] > max[0])
				max[0] = triArray_main1[i].c[0];

			if (triArray_main1[i].c[1] < min[1])
				min[1] = triArray_main1[i].c[1];
			else if (triArray_main1[i].c[1] > max[1])
				max[1] = triArray_main1[i].c[1];

			if (triArray_main1[i].c[2] < min[2])
				min[2] = triArray_main1[i].c[2];
			else if (triArray_main1[i].c[2] > max[2])
				max[2] = triArray_main1[i].c[2];
		}
		cent[15][0] = (min[0] + max[0]) / 2.0f;
		cent[15][1] = (min[1] + max[1]) / 2.0f;
		cent[15][2] = (min[2] + max[2]) / 2.0f;
	}


	VBOv[15] = new float[nTriangles[15] * 9];
	VBOn[15] = new float[nTriangles[15] * 9];
	int i;


	for (i = 0; i<nTriangles[15]; i++)
	{

		VBOv[15][i * 9 + 0] = triArray_main1[i].a[0]; // -300
		VBOv[15][i * 9 + 1] = triArray_main1[i].a[1];//-17.5
		VBOv[15][i * 9 + 2] = triArray_main1[i].a[2];//+15.5

		VBOv[15][i * 9 + 3] = triArray_main1[i].b[0];
		VBOv[15][i * 9 + 4] = triArray_main1[i].b[1];
		VBOv[15][i * 9 + 5] = triArray_main1[i].b[2];

		VBOv[15][i * 9 + 6] = triArray_main1[i].c[0];
		VBOv[15][i * 9 + 7] = triArray_main1[i].c[1];
		VBOv[15][i * 9 + 8] = triArray_main1[i].c[2];



		VBOn[15][i * 9 + 0] = triArray_main1[i].n[0];
		VBOn[15][i * 9 + 1] = triArray_main1[i].n[1];
		VBOn[15][i * 9 + 2] = triArray_main1[i].n[2];

		VBOn[15][i * 9 + 3] = triArray_main1[i].n[0];
		VBOn[15][i * 9 + 4] = triArray_main1[i].n[1];
		VBOn[15][i * 9 + 5] = triArray_main1[i].n[2];

		VBOn[15][i * 9 + 6] = triArray_main1[i].n[0];
		VBOn[15][i * 9 + 7] = triArray_main1[i].n[1];
		VBOn[15][i * 9 + 8] = triArray_main1[i].n[2];


	}



	glGenBuffers(2, VBO_index_main1);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_main1[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[15] * 9 * sizeof(float), VBOv[15], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_main1[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[15] * 9 * sizeof(float), VBOn[15], GL_STATIC_DRAW);



}
void InitVBO_main2(void)
{
	if (triArray_main2)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[16]; i++)
		{
			//a
			if (triArray_main2[i].a[0] < min[0])
				min[0] = triArray_main2[i].a[0];
			else if (triArray_main2[i].a[0] > max[0])
				max[0] = triArray_main2[i].a[0];

			if (triArray_main2[i].a[1] < min[1])
				min[1] = triArray_main2[i].a[1];
			else if (triArray_main2[i].a[1] > max[1])
				max[1] = triArray_main2[i].a[1];

			if (triArray_main2[i].a[2] < min[2])
				min[2] = triArray_main2[i].a[2];
			else if (triArray_main2[i].a[2] > max[2])
				max[2] = triArray_main2[i].a[2];

			//b
			if (triArray_main2[i].b[0] < min[0])
				min[0] = triArray_main2[i].b[0];
			else if (triArray_main2[i].b[0] > max[0])
				max[0] = triArray_main2[i].b[0];

			if (triArray_main2[i].b[1] < min[1])
				min[1] = triArray_main2[i].b[1];
			else if (triArray_main2[i].b[1] > max[1])
				max[1] = triArray_main2[i].b[1];

			if (triArray_main2[i].b[2] < min[2])
				min[2] = triArray_main2[i].b[2];
			else if (triArray_main2[i].b[2] > max[2])
				max[2] = triArray_main2[i].b[2];

			//c
			if (triArray_main2[i].c[0] < min[0])
				min[0] = triArray_main2[i].c[0];
			else if (triArray_main2[i].c[0] > max[0])
				max[0] = triArray_main2[i].c[0];

			if (triArray_main2[i].c[1] < min[1])
				min[1] = triArray_main2[i].c[1];
			else if (triArray_main2[i].c[1] > max[1])
				max[1] = triArray_main2[i].c[1];

			if (triArray_main2[i].c[2] < min[2])
				min[2] = triArray_main2[i].c[2];
			else if (triArray_main2[i].c[2] > max[2])
				max[2] = triArray_main2[i].c[2];
		}
		cent[16][0] = (min[0] + max[0]) / 2.0f;
		cent[16][1] = (min[1] + max[1]) / 2.0f;
		cent[16][2] = (min[2] + max[2]) / 2.0f;

	}



	VBOv[16] = new float[nTriangles[16] * 9];
	VBOn[16] = new float[nTriangles[16] * 9];
	int i;


	for (i = 0; i<nTriangles[16]; i++)
	{

		VBOv[16][i * 9 + 0] = triArray_main2[i].a[0]; // -300
		VBOv[16][i * 9 + 1] = triArray_main2[i].a[1];//-17.5
		VBOv[16][i * 9 + 2] = triArray_main2[i].a[2];//+15.5

		VBOv[16][i * 9 + 3] = triArray_main2[i].b[0];
		VBOv[16][i * 9 + 4] = triArray_main2[i].b[1];
		VBOv[16][i * 9 + 5] = triArray_main2[i].b[2];

		VBOv[16][i * 9 + 6] = triArray_main2[i].c[0];
		VBOv[16][i * 9 + 7] = triArray_main2[i].c[1];
		VBOv[16][i * 9 + 8] = triArray_main2[i].c[2];



		VBOn[16][i * 9 + 0] = triArray_main2[i].n[0];
		VBOn[16][i * 9 + 1] = triArray_main2[i].n[1];
		VBOn[16][i * 9 + 2] = triArray_main2[i].n[2];

		VBOn[16][i * 9 + 3] = triArray_main2[i].n[0];
		VBOn[16][i * 9 + 4] = triArray_main2[i].n[1];
		VBOn[16][i * 9 + 5] = triArray_main2[i].n[2];

		VBOn[16][i * 9 + 6] = triArray_main2[i].n[0];
		VBOn[16][i * 9 + 7] = triArray_main2[i].n[1];
		VBOn[16][i * 9 + 8] = triArray_main2[i].n[2];


	}



	glGenBuffers(2, VBO_index_main2);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_main2[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[16] * 9 * sizeof(float), VBOv[16], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_main2[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[16] * 9 * sizeof(float), VBOn[16], GL_STATIC_DRAW);



}
void InitVBO_main3(void)
{
	if (triArray_main3)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[17]; i++)
		{
			//a
			if (triArray_main3[i].a[0] < min[0])
				min[0] = triArray_main3[i].a[0];
			else if (triArray_main3[i].a[0] > max[0])
				max[0] = triArray_main3[i].a[0];

			if (triArray_main3[i].a[1] < min[1])
				min[1] = triArray_main3[i].a[1];
			else if (triArray_main3[i].a[1] > max[1])
				max[1] = triArray_main3[i].a[1];

			if (triArray_main3[i].a[2] < min[2])
				min[2] = triArray_main3[i].a[2];
			else if (triArray_main3[i].a[2] > max[2])
				max[2] = triArray_main3[i].a[2];

			//b
			if (triArray_main3[i].b[0] < min[0])
				min[0] = triArray_main3[i].b[0];
			else if (triArray_main3[i].b[0] > max[0])
				max[0] = triArray_main3[i].b[0];

			if (triArray_main3[i].b[1] < min[1])
				min[1] = triArray_main3[i].b[1];
			else if (triArray_main3[i].b[1] > max[1])
				max[1] = triArray_main3[i].b[1];

			if (triArray_main3[i].b[2] < min[2])
				min[2] = triArray_main3[i].b[2];
			else if (triArray_main3[i].b[2] > max[2])
				max[2] = triArray_main3[i].b[2];

			//c
			if (triArray_main3[i].c[0] < min[0])
				min[0] = triArray_main3[i].c[0];
			else if (triArray_main3[i].c[0] > max[0])
				max[0] = triArray_main3[i].c[0];

			if (triArray_main3[i].c[1] < min[1])
				min[1] = triArray_main3[i].c[1];
			else if (triArray_main3[i].c[1] > max[1])
				max[1] = triArray_main3[i].c[1];

			if (triArray_main3[i].c[2] < min[2])
				min[2] = triArray_main3[i].c[2];
			else if (triArray_main3[i].c[2] > max[2])
				max[2] = triArray_main3[i].c[2];
		}
		cent[17][0] = (min[0] + max[0]) / 2.0f;
		cent[17][1] = (min[1] + max[1]) / 2.0f;
		cent[17][2] = (min[2] + max[2]) / 2.0f;

	}


	VBOv[17] = new float[nTriangles[17] * 9];
	VBOn[17] = new float[nTriangles[17] * 9];
	int i;


	for (i = 0; i<nTriangles[17]; i++)
	{

		VBOv[17][i * 9 + 0] = triArray_main3[i].a[0]; // -300
		VBOv[17][i * 9 + 1] = triArray_main3[i].a[1];//-17.5
		VBOv[17][i * 9 + 2] = triArray_main3[i].a[2];//+15.5

		VBOv[17][i * 9 + 3] = triArray_main3[i].b[0];
		VBOv[17][i * 9 + 4] = triArray_main3[i].b[1];
		VBOv[17][i * 9 + 5] = triArray_main3[i].b[2];

		VBOv[17][i * 9 + 6] = triArray_main3[i].c[0];
		VBOv[17][i * 9 + 7] = triArray_main3[i].c[1];
		VBOv[17][i * 9 + 8] = triArray_main3[i].c[2];



		VBOn[17][i * 9 + 0] = triArray_main3[i].n[0];
		VBOn[17][i * 9 + 1] = triArray_main3[i].n[1];
		VBOn[17][i * 9 + 2] = triArray_main3[i].n[2];

		VBOn[17][i * 9 + 3] = triArray_main3[i].n[0];
		VBOn[17][i * 9 + 4] = triArray_main3[i].n[1];
		VBOn[17][i * 9 + 5] = triArray_main3[i].n[2];

		VBOn[17][i * 9 + 6] = triArray_main3[i].n[0];
		VBOn[17][i * 9 + 7] = triArray_main3[i].n[1];
		VBOn[17][i * 9 + 8] = triArray_main3[i].n[2];


	}



	glGenBuffers(2, VBO_index_main3);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_main3[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[17] * 9 * sizeof(float), VBOv[17], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_main3[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[17] * 9 * sizeof(float), VBOn[17], GL_STATIC_DRAW);



}
void InitVBO_main4(void)
{
	if (triArray_main4)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[18]; i++)
		{
			//a
			if (triArray_main4[i].a[0] < min[0])
				min[0] = triArray_main4[i].a[0];
			else if (triArray_main4[i].a[0] > max[0])
				max[0] = triArray_main4[i].a[0];

			if (triArray_main4[i].a[1] < min[1])
				min[1] = triArray_main4[i].a[1];
			else if (triArray_main4[i].a[1] > max[1])
				max[1] = triArray_main4[i].a[1];

			if (triArray_main4[i].a[2] < min[2])
				min[2] = triArray_main4[i].a[2];
			else if (triArray_main4[i].a[2] > max[2])
				max[2] = triArray_main4[i].a[2];

			//b
			if (triArray_main4[i].b[0] < min[0])
				min[0] = triArray_main4[i].b[0];
			else if (triArray_main4[i].b[0] > max[0])
				max[0] = triArray_main4[i].b[0];

			if (triArray_main4[i].b[1] < min[1])
				min[1] = triArray_main4[i].b[1];
			else if (triArray_main4[i].b[1] > max[1])
				max[1] = triArray_main4[i].b[1];

			if (triArray_main4[i].b[2] < min[2])
				min[2] = triArray_main4[i].b[2];
			else if (triArray_main4[i].b[2] > max[2])
				max[2] = triArray_main4[i].b[2];

			//c
			if (triArray_main4[i].c[0] < min[0])
				min[0] = triArray_main4[i].c[0];
			else if (triArray_main4[i].c[0] > max[0])
				max[0] = triArray_main4[i].c[0];

			if (triArray_main4[i].c[1] < min[1])
				min[1] = triArray_main4[i].c[1];
			else if (triArray_main4[i].c[1] > max[1])
				max[1] = triArray_main4[i].c[1];

			if (triArray_main4[i].c[2] < min[2])
				min[2] = triArray_main4[i].c[2];
			else if (triArray_main4[i].c[2] > max[2])
				max[2] = triArray_main4[i].c[2];
		}
		cent[18][0] = (min[0] + max[0]) / 2.0f;
		cent[18][1] = (min[1] + max[1]) / 2.0f;
		cent[18][2] = (min[2] + max[2]) / 2.0f;

	}



	VBOv[18] = new float[nTriangles[18] * 9];
	VBOn[18] = new float[nTriangles[18] * 9];
	int i;


	for (i = 0; i<nTriangles[18]; i++)
	{

		VBOv[18][i * 9 + 0] = triArray_main4[i].a[0]; // -300
		VBOv[18][i * 9 + 1] = triArray_main4[i].a[1];//-17.5
		VBOv[18][i * 9 + 2] = triArray_main4[i].a[2];//+15.5

		VBOv[18][i * 9 + 3] = triArray_main4[i].b[0];
		VBOv[18][i * 9 + 4] = triArray_main4[i].b[1];
		VBOv[18][i * 9 + 5] = triArray_main4[i].b[2];

		VBOv[18][i * 9 + 6] = triArray_main4[i].c[0];
		VBOv[18][i * 9 + 7] = triArray_main4[i].c[1];
		VBOv[18][i * 9 + 8] = triArray_main4[i].c[2];



		VBOn[18][i * 9 + 0] = triArray_main4[i].n[0];
		VBOn[18][i * 9 + 1] = triArray_main4[i].n[1];
		VBOn[18][i * 9 + 2] = triArray_main4[i].n[2];

		VBOn[18][i * 9 + 3] = triArray_main4[i].n[0];
		VBOn[18][i * 9 + 4] = triArray_main4[i].n[1];
		VBOn[18][i * 9 + 5] = triArray_main4[i].n[2];

		VBOn[18][i * 9 + 6] = triArray_main4[i].n[0];
		VBOn[18][i * 9 + 7] = triArray_main4[i].n[1];
		VBOn[18][i * 9 + 8] = triArray_main4[i].n[2];


	}



	glGenBuffers(2, VBO_index_main4);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_main4[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[18] * 9 * sizeof(float), VBOv[18], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_main4[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[18] * 9 * sizeof(float), VBOn[18], GL_STATIC_DRAW);



}
void InitVBO_load1(void)
{
	if (triArray_load1)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[19]; i++)
		{
			//a
			if (triArray_load1[i].a[0] < min[0])
				min[0] = triArray_load1[i].a[0];
			else if (triArray_load1[i].a[0] > max[0])
				max[0] = triArray_load1[i].a[0];

			if (triArray_load1[i].a[1] < min[1])
				min[1] = triArray_load1[i].a[1];
			else if (triArray_load1[i].a[1] > max[1])
				max[1] = triArray_load1[i].a[1];

			if (triArray_load1[i].a[2] < min[2])
				min[2] = triArray_load1[i].a[2];
			else if (triArray_load1[i].a[2] > max[2])
				max[2] = triArray_load1[i].a[2];

			//b
			if (triArray_load1[i].b[0] < min[0])
				min[0] = triArray_load1[i].b[0];
			else if (triArray_load1[i].b[0] > max[0])
				max[0] = triArray_load1[i].b[0];

			if (triArray_load1[i].b[1] < min[1])
				min[1] = triArray_load1[i].b[1];
			else if (triArray_load1[i].b[1] > max[1])
				max[1] = triArray_load1[i].b[1];

			if (triArray_load1[i].b[2] < min[2])
				min[2] = triArray_load1[i].b[2];
			else if (triArray_load1[i].b[2] > max[2])
				max[2] = triArray_load1[i].b[2];

			//c
			if (triArray_load1[i].c[0] < min[0])
				min[0] = triArray_load1[i].c[0];
			else if (triArray_load1[i].c[0] > max[0])
				max[0] = triArray_load1[i].c[0];

			if (triArray_load1[i].c[1] < min[1])
				min[1] = triArray_load1[i].c[1];
			else if (triArray_load1[i].c[1] > max[1])
				max[1] = triArray_load1[i].c[1];

			if (triArray_load1[i].c[2] < min[2])
				min[2] = triArray_load1[i].c[2];
			else if (triArray_load1[i].c[2] > max[2])
				max[2] = triArray_load1[i].c[2];
		}
		cent[19][0] = (min[0] + max[0]) / 2.0f;
		cent[19][1] = (min[1] + max[1]) / 2.0f;
		cent[19][2] = (min[2] + max[2]) / 2.0f;
	}



	VBOv[19] = new float[nTriangles[19] * 9];
	VBOn[19] = new float[nTriangles[19] * 9];
	int i;


	for (i = 0; i<nTriangles[19]; i++)
	{

		VBOv[19][i * 9 + 0] = triArray_load1[i].a[0]; // -300
		VBOv[19][i * 9 + 1] = triArray_load1[i].a[1];//-17.5
		VBOv[19][i * 9 + 2] = triArray_load1[i].a[2];//+15.5

		VBOv[19][i * 9 + 3] = triArray_load1[i].b[0];
		VBOv[19][i * 9 + 4] = triArray_load1[i].b[1];
		VBOv[19][i * 9 + 5] = triArray_load1[i].b[2];

		VBOv[19][i * 9 + 6] = triArray_load1[i].c[0];
		VBOv[19][i * 9 + 7] = triArray_load1[i].c[1];
		VBOv[19][i * 9 + 8] = triArray_load1[i].c[2];



		VBOn[19][i * 9 + 0] = triArray_load1[i].n[0];
		VBOn[19][i * 9 + 1] = triArray_load1[i].n[1];
		VBOn[19][i * 9 + 2] = triArray_load1[i].n[2];

		VBOn[19][i * 9 + 3] = triArray_load1[i].n[0];
		VBOn[19][i * 9 + 4] = triArray_load1[i].n[1];
		VBOn[19][i * 9 + 5] = triArray_load1[i].n[2];

		VBOn[19][i * 9 + 6] = triArray_load1[i].n[0];
		VBOn[19][i * 9 + 7] = triArray_load1[i].n[1];
		VBOn[19][i * 9 + 8] = triArray_load1[i].n[2];


	}



	glGenBuffers(2, VBO_index_load1);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load1[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[19] * 9 * sizeof(float), VBOv[19], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load1[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[19] * 9 * sizeof(float), VBOn[19], GL_STATIC_DRAW);



}
void InitVBO_load2(void)
{
	if (triArray_load2)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[20]; i++)
		{
			//a
			if (triArray_load2[i].a[0] < min[0])
				min[0] = triArray_load2[i].a[0];
			else if (triArray_load2[i].a[0] > max[0])
				max[0] = triArray_load2[i].a[0];

			if (triArray_load2[i].a[1] < min[1])
				min[1] = triArray_load2[i].a[1];
			else if (triArray_load2[i].a[1] > max[1])
				max[1] = triArray_load2[i].a[1];

			if (triArray_load2[i].a[2] < min[2])
				min[2] = triArray_load2[i].a[2];
			else if (triArray_load2[i].a[2] > max[2])
				max[2] = triArray_load2[i].a[2];

			//b
			if (triArray_load2[i].b[0] < min[0])
				min[0] = triArray_load2[i].b[0];
			else if (triArray_load2[i].b[0] > max[0])
				max[0] = triArray_load2[i].b[0];

			if (triArray_load2[i].b[1] < min[1])
				min[1] = triArray_load2[i].b[1];
			else if (triArray_load2[i].b[1] > max[1])
				max[1] = triArray_load2[i].b[1];

			if (triArray_load2[i].b[2] < min[2])
				min[2] = triArray_load2[i].b[2];
			else if (triArray_load2[i].b[2] > max[2])
				max[2] = triArray_load2[i].b[2];

			//c
			if (triArray_load2[i].c[0] < min[0])
				min[0] = triArray_load2[i].c[0];
			else if (triArray_load2[i].c[0] > max[0])
				max[0] = triArray_load2[i].c[0];

			if (triArray_load2[i].c[1] < min[1])
				min[1] = triArray_load2[i].c[1];
			else if (triArray_load2[i].c[1] > max[1])
				max[1] = triArray_load2[i].c[1];

			if (triArray_load2[i].c[2] < min[2])
				min[2] = triArray_load2[i].c[2];
			else if (triArray_load2[i].c[2] > max[2])
				max[2] = triArray_load2[i].c[2];
		}
		cent[20][0] = (min[0] + max[0]) / 2.0f;
		cent[20][1] = (min[1] + max[1]) / 2.0f;
		cent[20][2] = (min[2] + max[2]) / 2.0f;

	}



	VBOv[20] = new float[nTriangles[20] * 9];
	VBOn[20] = new float[nTriangles[20] * 9];
	int i;


	for (i = 0; i<nTriangles[20]; i++)
	{

		VBOv[20][i * 9 + 0] = triArray_load2[i].a[0]; // -300
		VBOv[20][i * 9 + 1] = triArray_load2[i].a[1];//-17.5
		VBOv[20][i * 9 + 2] = triArray_load2[i].a[2];//+15.5

		VBOv[20][i * 9 + 3] = triArray_load2[i].b[0];
		VBOv[20][i * 9 + 4] = triArray_load2[i].b[1];
		VBOv[20][i * 9 + 5] = triArray_load2[i].b[2];

		VBOv[20][i * 9 + 6] = triArray_load2[i].c[0];
		VBOv[20][i * 9 + 7] = triArray_load2[i].c[1];
		VBOv[20][i * 9 + 8] = triArray_load2[i].c[2];



		VBOn[20][i * 9 + 0] = triArray_load2[i].n[0];
		VBOn[20][i * 9 + 1] = triArray_load2[i].n[1];
		VBOn[20][i * 9 + 2] = triArray_load2[i].n[2];

		VBOn[20][i * 9 + 3] = triArray_load2[i].n[0];
		VBOn[20][i * 9 + 4] = triArray_load2[i].n[1];
		VBOn[20][i * 9 + 5] = triArray_load2[i].n[2];

		VBOn[20][i * 9 + 6] = triArray_load2[i].n[0];
		VBOn[20][i * 9 + 7] = triArray_load2[i].n[1];
		VBOn[20][i * 9 + 8] = triArray_load2[i].n[2];


	}



	glGenBuffers(2, VBO_index_load2);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load2[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[20] * 9 * sizeof(float), VBOv[20], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load2[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[20] * 9 * sizeof(float), VBOn[20], GL_STATIC_DRAW);



}
void InitVBO_load3(void)
{
	if (triArray_load3)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[21]; i++)
		{
			//a
			if (triArray_load3[i].a[0] < min[0])
				min[0] = triArray_load3[i].a[0];
			else if (triArray_load3[i].a[0] > max[0])
				max[0] = triArray_load3[i].a[0];

			if (triArray_load3[i].a[1] < min[1])
				min[1] = triArray_load3[i].a[1];
			else if (triArray_load3[i].a[1] > max[1])
				max[1] = triArray_load3[i].a[1];

			if (triArray_load3[i].a[2] < min[2])
				min[2] = triArray_load3[i].a[2];
			else if (triArray_load3[i].a[2] > max[2])
				max[2] = triArray_load3[i].a[2];

			//b
			if (triArray_load3[i].b[0] < min[0])
				min[0] = triArray_load3[i].b[0];
			else if (triArray_load3[i].b[0] > max[0])
				max[0] = triArray_load3[i].b[0];

			if (triArray_load3[i].b[1] < min[1])
				min[1] = triArray_load3[i].b[1];
			else if (triArray_load3[i].b[1] > max[1])
				max[1] = triArray_load3[i].b[1];

			if (triArray_load3[i].b[2] < min[2])
				min[2] = triArray_load3[i].b[2];
			else if (triArray_load3[i].b[2] > max[2])
				max[2] = triArray_load3[i].b[2];

			//c
			if (triArray_load3[i].c[0] < min[0])
				min[0] = triArray_load3[i].c[0];
			else if (triArray_load3[i].c[0] > max[0])
				max[0] = triArray_load3[i].c[0];

			if (triArray_load3[i].c[1] < min[1])
				min[1] = triArray_load3[i].c[1];
			else if (triArray_load3[i].c[1] > max[1])
				max[1] = triArray_load3[i].c[1];

			if (triArray_load3[i].c[2] < min[2])
				min[2] = triArray_load3[i].c[2];
			else if (triArray_load3[i].c[2] > max[2])
				max[2] = triArray_load3[i].c[2];
		}
		cent[21][0] = (min[0] + max[0]) / 2.0f;
		cent[21][1] = (min[1] + max[1]) / 2.0f;
		cent[21][2] = (min[2] + max[2]) / 2.0f;

	}


	VBOv[21] = new float[nTriangles[21] * 9];
	VBOn[21] = new float[nTriangles[21] * 9];
	int i;


	for (i = 0; i<nTriangles[21]; i++)
	{

		VBOv[21][i * 9 + 0] = triArray_load3[i].a[0]; // -300
		VBOv[21][i * 9 + 1] = triArray_load3[i].a[1];//-17.5
		VBOv[21][i * 9 + 2] = triArray_load3[i].a[2];//+15.5

		VBOv[21][i * 9 + 3] = triArray_load3[i].b[0];
		VBOv[21][i * 9 + 4] = triArray_load3[i].b[1];
		VBOv[21][i * 9 + 5] = triArray_load3[i].b[2];

		VBOv[21][i * 9 + 6] = triArray_load3[i].c[0];
		VBOv[21][i * 9 + 7] = triArray_load3[i].c[1];
		VBOv[21][i * 9 + 8] = triArray_load3[i].c[2];



		VBOn[21][i * 9 + 0] = triArray_load3[i].n[0];
		VBOn[21][i * 9 + 1] = triArray_load3[i].n[1];
		VBOn[21][i * 9 + 2] = triArray_load3[i].n[2];

		VBOn[21][i * 9 + 3] = triArray_load3[i].n[0];
		VBOn[21][i * 9 + 4] = triArray_load3[i].n[1];
		VBOn[21][i * 9 + 5] = triArray_load3[i].n[2];

		VBOn[21][i * 9 + 6] = triArray_load3[i].n[0];
		VBOn[21][i * 9 + 7] = triArray_load3[i].n[1];
		VBOn[21][i * 9 + 8] = triArray_load3[i].n[2];


	}



	glGenBuffers(2, VBO_index_load3);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load3[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[21] * 9 * sizeof(float), VBOv[21], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load3[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[21] * 9 * sizeof(float), VBOn[21], GL_STATIC_DRAW);



}
void InitVBO_load4(void)
{
	if (triArray_load4)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[22]; i++)
		{
			//a
			if (triArray_load4[i].a[0] < min[0])
				min[0] = triArray_load4[i].a[0];
			else if (triArray_load4[i].a[0] > max[0])
				max[0] = triArray_load4[i].a[0];

			if (triArray_load4[i].a[1] < min[1])
				min[1] = triArray_load4[i].a[1];
			else if (triArray_load4[i].a[1] > max[1])
				max[1] = triArray_load4[i].a[1];

			if (triArray_load4[i].a[2] < min[2])
				min[2] = triArray_load4[i].a[2];
			else if (triArray_load4[i].a[2] > max[2])
				max[2] = triArray_load4[i].a[2];

			//b
			if (triArray_load4[i].b[0] < min[0])
				min[0] = triArray_load4[i].b[0];
			else if (triArray_load4[i].b[0] > max[0])
				max[0] = triArray_load4[i].b[0];

			if (triArray_load4[i].b[1] < min[1])
				min[1] = triArray_load4[i].b[1];
			else if (triArray_load4[i].b[1] > max[1])
				max[1] = triArray_load4[i].b[1];

			if (triArray_load4[i].b[2] < min[2])
				min[2] = triArray_load4[i].b[2];
			else if (triArray_load4[i].b[2] > max[2])
				max[2] = triArray_load4[i].b[2];

			//c
			if (triArray_load4[i].c[0] < min[0])
				min[0] = triArray_load4[i].c[0];
			else if (triArray_load4[i].c[0] > max[0])
				max[0] = triArray_load4[i].c[0];

			if (triArray_load4[i].c[1] < min[1])
				min[1] = triArray_load4[i].c[1];
			else if (triArray_load4[i].c[1] > max[1])
				max[1] = triArray_load4[i].c[1];

			if (triArray_load4[i].c[2] < min[2])
				min[2] = triArray_load4[i].c[2];
			else if (triArray_load4[i].c[2] > max[2])
				max[2] = triArray_load4[i].c[2];
		}
		cent[22][0] = (min[0] + max[0]) / 2.0f;
		cent[22][1] = (min[1] + max[1]) / 2.0f;
		cent[22][2] = (min[2] + max[2]) / 2.0f;
	}


	VBOv[22] = new float[nTriangles[22] * 9];
	VBOn[22] = new float[nTriangles[22] * 9];
	int i;


	for (i = 0; i<nTriangles[22]; i++)
	{

		VBOv[22][i * 9 + 0] = triArray_load4[i].a[0]; // -300
		VBOv[22][i * 9 + 1] = triArray_load4[i].a[1];//-17.5
		VBOv[22][i * 9 + 2] = triArray_load4[i].a[2];//+15.5

		VBOv[22][i * 9 + 3] = triArray_load4[i].b[0];
		VBOv[22][i * 9 + 4] = triArray_load4[i].b[1];
		VBOv[22][i * 9 + 5] = triArray_load4[i].b[2];

		VBOv[22][i * 9 + 6] = triArray_load4[i].c[0];
		VBOv[22][i * 9 + 7] = triArray_load4[i].c[1];
		VBOv[22][i * 9 + 8] = triArray_load4[i].c[2];



		VBOn[22][i * 9 + 0] = triArray_load4[i].n[0];
		VBOn[22][i * 9 + 1] = triArray_load4[i].n[1];
		VBOn[22][i * 9 + 2] = triArray_load4[i].n[2];

		VBOn[22][i * 9 + 3] = triArray_load4[i].n[0];
		VBOn[22][i * 9 + 4] = triArray_load4[i].n[1];
		VBOn[22][i * 9 + 5] = triArray_load4[i].n[2];

		VBOn[22][i * 9 + 6] = triArray_load4[i].n[0];
		VBOn[22][i * 9 + 7] = triArray_load4[i].n[1];
		VBOn[22][i * 9 + 8] = triArray_load4[i].n[2];


	}



	glGenBuffers(2, VBO_index_load4);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load4[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[22] * 9 * sizeof(float), VBOv[22], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load4[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[22] * 9 * sizeof(float), VBOn[22], GL_STATIC_DRAW);



}
void InitVBO_load5(void)
{
	if (triArray_load5)
	{
		float min[3] = { 1e7, 1e7, 1e7 };
		float max[3] = { -1e7, -1e7, -1e7 };
		for (int i = 0; i < nTriangles[23]; i++)
		{
			//a
			if (triArray_load5[i].a[0] < min[0])
				min[0] = triArray_load5[i].a[0];
			else if (triArray_load5[i].a[0] > max[0])
				max[0] = triArray_load5[i].a[0];

			if (triArray_load5[i].a[1] < min[1])
				min[1] = triArray_load5[i].a[1];
			else if (triArray_load5[i].a[1] > max[1])
				max[1] = triArray_load5[i].a[1];

			if (triArray_load5[i].a[2] < min[2])
				min[2] = triArray_load5[i].a[2];
			else if (triArray_load5[i].a[2] > max[2])
				max[2] = triArray_load5[i].a[2];

			//b
			if (triArray_load5[i].b[0] < min[0])
				min[0] = triArray_load5[i].b[0];
			else if (triArray_load5[i].b[0] > max[0])
				max[0] = triArray_load5[i].b[0];

			if (triArray_load5[i].b[1] < min[1])
				min[1] = triArray_load5[i].b[1];
			else if (triArray_load5[i].b[1] > max[1])
				max[1] = triArray_load5[i].b[1];

			if (triArray_load5[i].b[2] < min[2])
				min[2] = triArray_load5[i].b[2];
			else if (triArray_load5[i].b[2] > max[2])
				max[2] = triArray_load5[i].b[2];

			//c
			if (triArray_load5[i].c[0] < min[0])
				min[0] = triArray_load5[i].c[0];
			else if (triArray_load5[i].c[0] > max[0])
				max[0] = triArray_load5[i].c[0];

			if (triArray_load5[i].c[1] < min[1])
				min[1] = triArray_load5[i].c[1];
			else if (triArray_load5[i].c[1] > max[1])
				max[1] = triArray_load5[i].c[1];

			if (triArray_load5[i].c[2] < min[2])
				min[2] = triArray_load5[i].c[2];
			else if (triArray_load5[i].c[2] > max[2])
				max[2] = triArray_load5[i].c[2];
		}
		cent[23][0] = (min[0] + max[0]) / 2.0f;
		cent[23][1] = (min[1] + max[1]) / 2.0f;
		cent[23][2] = (min[2] + max[2]) / 2.0f;

	}


	VBOv[23] = new float[nTriangles[23] * 9];
	VBOn[23] = new float[nTriangles[23] * 9];
	int i;


	for (i = 0; i<nTriangles[23]; i++)
	{

		VBOv[23][i * 9 + 0] = triArray_load5[i].a[0]; // -300
		VBOv[23][i * 9 + 1] = triArray_load5[i].a[1];//-17.5
		VBOv[23][i * 9 + 2] = triArray_load5[i].a[2];//+15.5

		VBOv[23][i * 9 + 3] = triArray_load5[i].b[0];
		VBOv[23][i * 9 + 4] = triArray_load5[i].b[1];
		VBOv[23][i * 9 + 5] = triArray_load5[i].b[2];

		VBOv[23][i * 9 + 6] = triArray_load5[i].c[0];
		VBOv[23][i * 9 + 7] = triArray_load5[i].c[1];
		VBOv[23][i * 9 + 8] = triArray_load5[i].c[2];



		VBOn[23][i * 9 + 0] = triArray_load5[i].n[0];
		VBOn[23][i * 9 + 1] = triArray_load5[i].n[1];
		VBOn[23][i * 9 + 2] = triArray_load5[i].n[2];

		VBOn[23][i * 9 + 3] = triArray_load5[i].n[0];
		VBOn[23][i * 9 + 4] = triArray_load5[i].n[1];
		VBOn[23][i * 9 + 5] = triArray_load5[i].n[2];

		VBOn[23][i * 9 + 6] = triArray_load5[i].n[0];
		VBOn[23][i * 9 + 7] = triArray_load5[i].n[1];
		VBOn[23][i * 9 + 8] = triArray_load5[i].n[2];


	}



	glGenBuffers(2, VBO_index_load5);

	// Vertex

	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load5[0]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[23] * 9 * sizeof(float), VBOv[23], GL_STATIC_DRAW);

	Sleep(200);
	// Normal
	glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load5[1]);
	glBufferData(GL_ARRAY_BUFFER, nTriangles[23] * 9 * sizeof(float), VBOn[23], GL_STATIC_DRAW);



}

//繪圖函式
void Draw_load1(int x)
{
	glPushMatrix();
	{
		
		glPushMatrix();
		{
			//平移
			glTranslatef(350 - 70 + 30, -680, -60);
			//自轉
			glRotatef( 180, 0.0f, 1.0f, 0.0f); //(-x, y , -z)
			glRotatef( - 90, 1.0f, 0.0f, 0.0f); //(-x, z , y)
			glRotatef(load_Rot[x] , 0.0f, 1.0f, 0.0f); //(-x, y , -z)
			//改變座標原點
			glTranslatef(-cent[19][0], -cent[19][1], -cent[19][2]); 

			glColor3ub(210, 210, 210);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load1[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load1[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[19] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
	}
	glPopMatrix();

}
void Draw_load2(int x)
{
	glPushMatrix();
	{

		glPushMatrix();
		{
			//平移
			glTranslatef(350 - 155, -450 + 17.5 - load_Rot[x] * 125.0f / 180.0f * 3.14159f, -60);
			//自轉
			//glRotatef(load_Rot[x], 0.0f, 1.0f, 0.0f); //(-x, y , -z)
			//改變座標原點
			glTranslatef(-cent[20][0], -cent[20][1], -cent[20][2]); 

			glColor3ub(210, 210, 210);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load2[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load2[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[20] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void Draw_load3(int x)
{
	glPushMatrix();
	{

		glPushMatrix();
		{
			//平移
			glTranslatef(-270, -195-2.5, -170+120);
			//自轉
			glRotatef(-load_Rot[x] *125/465, 0.0f, 0.0f, 1.0f);
			glRotatef(180, 0.0f, 1.0f, 0.0f); //(-x, y , -z)
			//改變座標原點
			glTranslatef(-cent[21][0] -225, -cent[21][1] +57.5, -cent[21][2]-75); 

			glColor3ub(210, 210, 210);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load3[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load3[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[21] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void Draw_load4(int x, int y)
{
	glPushMatrix();
	{

		glPushMatrix();
		{
			//平移
			glTranslatef(-10 - 187, 16 - 55 - 2.5, 5);
			//自轉
			glRotatef(-load_Rot[x] * 125.0f / 20.0f + 180.0f - y * 360 / 30, 0.0f, 0.0f, 1.0f);
			//改變座標原點
			glTranslatef(-cent[22][0] - 20, -cent[22][1], -cent[22][2]);

			glColor3ub(210, 210, 210);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load4[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load4[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[22] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void Draw_load5(int x)
{
	glPushMatrix();
	{

		glPushMatrix();
		{
			//平移
			glTranslatef(10 - 192.5 + load_Rot[x]/2, -16 + (-load_Rot[x] * 100.0f / 180.0f * 3.141549f) + 67.5f, 5);
			//自轉
			//glRotatef(xsRot + 90, 1.0f, 0.0f, 0.0f);
			//改變座標原點
			glTranslatef(-cent[23][0], -cent[23][1], -cent[23][2]); 

			glColor3ub(94, 38, 18);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load5[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_load5[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[23] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void Draw_do(int x)
{
	glPushMatrix();
	{
		//平移
		glTranslatef(10, -16, 546 - 7*23*x + 7*23);
		glPushMatrix();
		{
			if (load_Rot[0] == 0)
				Draw_load4(0, doRot[x]);
			else
				Draw_load4(0, 0);
		}
		glPopMatrix();
		glPushMatrix();
		{
			if (load_Rot[0]==0)
				glTranslatef(0, -doRot[x] *260/45, 0);
			Draw_load5(0);
		}
		glPopMatrix();

		glPushMatrix();
		{
			//平移
			glTranslatef(-70.5, 0, 5);
			//自轉
			glRotatef(-doRot[x] * 109.54 / 69.64, 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[0][0] + 56.5), -cent[0][1] + 16.5, -cent[0][2]); //改變座標原點

			glColor3ub(255, 231, 199);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[0] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			//畫part2
			glPushMatrix();
			{
				glTranslatef(-935, 26, 5);
				//自轉
				glRotatef(doRot[x] * 109.54 / 69.64 * 2 + 10, 0.0f, 0.0f, 1.0f);

				glTranslatef(-cent[1][0] + 17, -cent[1][1] + 26.5, -cent[1][2]); //x -z y

				glColor3ub(128, 128, 128);

				//以VBO畫三角網格
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);
				// Vertex
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[0]);
				glVertexPointer(3, GL_FLOAT, 0, 0);
				// Normal
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[1]);
				glNormalPointer(GL_FLOAT, 0, 0);

				glDrawArrays(GL_TRIANGLES, 0, nTriangles[1] * 3);

				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_NORMAL_ARRAY);
			}
			glPopMatrix();
		}
		glPopMatrix();
		//畫part5
		glPushMatrix();
		{
			glTranslatef(47, 68 + 5, 13.5);
			glRotatef(doRot[x] * 11 + 23.19 + part5_doRot[x], 0.0f, 0.0f, 1.0f);

			glTranslatef(-cent[4][0] + 109.5, -cent[4][1] + 23, -cent[4][2]);

			glColor3ub(128, 128, 128);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[4] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
		//畫do
		glPushMatrix();
		{
			//平移
			glTranslatef(100, -45.5, 5);
			//自轉
			glRotatef(doRot[x], 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[5][0] + 15), (-cent[5][1] + 20), -cent[5][2] - 5); //改原點

			glColor3ub(255, 255, 255);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_do[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_do[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[5] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void Draw_re(int x)
{
	glPushMatrix();
	{
		//平移
		glTranslatef(10, -16, 518 - 7 * 23 * x + 7 * 23);
		glPushMatrix();
		{
			if (load_Rot[0] == 0)
				Draw_load4(0, reRot[x]);
			else
				Draw_load4(0, 0);
		}
		glPopMatrix();
		glPushMatrix();
		{
			if (load_Rot[0] == 0)
			glTranslatef(0, -reRot[x] * 260 / 45, 0);
			Draw_load5(0);
		}
		glPopMatrix();

		glPushMatrix();
		{
			//平移
			glTranslatef(-70.5, 0, 5);
			//自轉
			glRotatef(-reRot[x] * 109.54 / 69.64, 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[0][0] + 56.5), -cent[0][1] + 16.5, -cent[0][2]); //改變座標原點

			glColor3ub(255, 231, 199);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[0] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			//畫part2
			glPushMatrix();
			{
				glTranslatef(-935, 26, 5);
				//自轉
				glRotatef(reRot[x] * 109.54 / 69.64 * 2 + 10, 0.0f, 0.0f, 1.0f);
				//改原點
				glTranslatef(-cent[1][0] + 17, -cent[1][1] + 26.5, -cent[1][2]); //x -z y

				glColor3ub(128, 128, 128);

				//以VBO畫三角網格
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);
				// Vertex
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[0]);
				glVertexPointer(3, GL_FLOAT, 0, 0);
				// Normal
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[1]);
				glNormalPointer(GL_FLOAT, 0, 0);

				glDrawArrays(GL_TRIANGLES, 0, nTriangles[1] * 3);

				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_NORMAL_ARRAY);
			}
			glPopMatrix();
		}
		glPopMatrix();
		//畫part5
		glPushMatrix();
		{
			glTranslatef(47, 68 + 5, 13.5);
			glRotatef(reRot[x] * 11 + 23.19 + part5_reRot[x], 0.0f, 0.0f, 1.0f);

			glTranslatef(-cent[4][0] + 109.5, -cent[4][1] + 23, -cent[4][2]);

			glColor3ub(128, 128, 128);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[4] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
		//畫re
		glPushMatrix();
		{
			//平移
			glTranslatef(100, -45.5, 5);
			//自轉
			glRotatef(reRot[x], 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[6][0] + 15), (-cent[6][1] + 20), -cent[6][2] ); //改原點

			glColor3ub(255, 255, 255);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_re[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_re[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[6] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void Draw_mi(int x)
{
	glPushMatrix();
	{
		//平移
		glTranslatef(10, -16, 490 - 7 * 23 * x + 7 * 23);
		glPushMatrix();
		{
			if (load_Rot[0] == 0)
				Draw_load4(0, miRot[x]);
			else
				Draw_load4(0, 0);
		}
		glPopMatrix();
		glPushMatrix();
		{
			if (load_Rot[0] == 0)
			glTranslatef(0, -miRot[x] * 260 / 45, 0);
			Draw_load5(0);
		}
		glPopMatrix();

		glPushMatrix();
		{
			//平移
			glTranslatef(-70.5, 0, 5);
			//自轉
			glRotatef(-miRot[x] * 109.54 / 69.64, 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[0][0] + 56.5), -cent[0][1] + 16.5, -cent[0][2] ); //改變座標原點

			glColor3ub(255, 231, 199);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[0] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			//畫part2
			glPushMatrix();
			{
				glTranslatef(-935, 26, 5);
				//自轉
				glRotatef(miRot[x] * 109.54 / 69.64 * 2 + 10, 0.0f, 0.0f, 1.0f);
				//改原點
				glTranslatef(-cent[1][0] + 17, -cent[1][1] + 26.5, -cent[1][2]); //x -z y

				glColor3ub(128, 128, 128);

				//以VBO畫三角網格
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);
				// Vertex
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[0]);
				glVertexPointer(3, GL_FLOAT, 0, 0);
				// Normal
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[1]);
				glNormalPointer(GL_FLOAT, 0, 0);

				glDrawArrays(GL_TRIANGLES, 0, nTriangles[1] * 3);

				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_NORMAL_ARRAY);
			}
			glPopMatrix();
		}
		glPopMatrix();
		//畫part5
		glPushMatrix();
		{
			glTranslatef(47, 68 + 5, 13.5);
			glRotatef(miRot[x] * 11 + 23.19 + part5_miRot[x], 0.0f, 0.0f, 1.0f);

			glTranslatef(-cent[4][0] + 109.5, -cent[4][1] + 23, -cent[4][2]);

			glColor3ub(128, 128, 128);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[4] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
		//畫mi
		glPushMatrix();
		{
			//平移
			glTranslatef(100, -45.5, 5);
			//自轉
			glRotatef(miRot[x], 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[7][0] + 15), (-cent[7][1] + 20), -cent[7][2]+5); //改原點

			glColor3ub(255, 255, 255);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_mi[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_mi[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[7] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void Draw_fa(int x)
{
	glPushMatrix();
	{
		//平移
		glTranslatef(10, -16, 477 - 7 * 23 * x + 7 * 23);
		glPushMatrix();
		{
			if (load_Rot[0] == 0)
				Draw_load4(0, faRot[x]);
			else
				Draw_load4(0, 0);
		}
		glPopMatrix();
		glPushMatrix();
		{
			if (load_Rot[0] == 0)
			glTranslatef(0, -faRot[x] * 260 / 45, 0);
			Draw_load5(0);
		}
		glPopMatrix();

		glPushMatrix();
		{
			//平移
			glTranslatef(-70.5, 0, 5);
			//自轉
			glRotatef(-faRot[x] * 109.54 / 69.64, 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[0][0] + 56.5), -cent[0][1] + 16.5, -cent[0][2]); //改變座標原點

			glColor3ub(255, 231, 199);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[0] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			//畫part2
			glPushMatrix();
			{
				glTranslatef(-935, 26, 5);
				//自轉
				glRotatef(faRot[x] * 109.54 / 69.64 * 2 + 10, 0.0f, 0.0f, 1.0f);
				//改原點
				glTranslatef(-cent[1][0] + 17, -cent[1][1] + 26.5, -cent[1][2]); //x -z y

				glColor3ub(128, 128, 128);

				//以VBO畫三角網格
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);
				// Vertex
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[0]);
				glVertexPointer(3, GL_FLOAT, 0, 0);
				// Normal
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[1]);
				glNormalPointer(GL_FLOAT, 0, 0);

				glDrawArrays(GL_TRIANGLES, 0, nTriangles[1] * 3);

				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_NORMAL_ARRAY);
			}
			glPopMatrix();
		}
		glPopMatrix();
		//畫part5
		glPushMatrix();
		{
			glTranslatef(47, 68 + 5, 13.5);
			glRotatef(faRot[x] * 11 + 23.19 + part5_faRot[x], 0.0f, 0.0f, 1.0f);

			glTranslatef(-cent[4][0] + 109.5, -cent[4][1] + 23, -cent[4][2]);

			glColor3ub(128, 128, 128);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[4] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
		//畫re
		glPushMatrix();
		{
			//平移
			glTranslatef(100, -45.5, 5);
			//自轉
			glRotatef(faRot[x], 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[8][0] + 15), (-cent[8][1] + 20), -cent[8][2] -5); //改原點

			glColor3ub(255, 255, 255);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_fa[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_fa[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[8] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void Draw_so(int x)
{
	glPushMatrix();
	{
		//平移
		glTranslatef(10, -16, 451 - 7 * 23 * x + 7 * 23);
		glPushMatrix();
		{
			if (load_Rot[0] == 0)
				Draw_load4(0, soRot[x]);
			else
				Draw_load4(0, 0);
		}
		glPopMatrix();
		glPushMatrix();
		{
			if (load_Rot[0] == 0)
				glTranslatef(0, -soRot[x] * 260 / 45, 0);
			Draw_load5(0);
		}
		glPopMatrix();

		glPushMatrix();
		{
			//平移
			glTranslatef(-70.5, 0, 5);
			//自轉
			glRotatef(-soRot[x] * 109.54 / 69.64, 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[0][0] + 56.5), -cent[0][1] + 16.5, -cent[0][2]); //改變座標原點

			glColor3ub(255, 231, 199);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[0] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			//畫part2
			glPushMatrix();
			{
				glTranslatef(-935, 26, 5);
				//自轉
				glRotatef(soRot[x] * 109.54 / 69.64 * 2 + 10, 0.0f, 0.0f, 1.0f);
				//改原點
				glTranslatef(-cent[1][0] + 17, -cent[1][1] + 26.5, -cent[1][2]); //x -z y

				glColor3ub(128, 128, 128);

				//以VBO畫三角網格
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);
				// Vertex
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[0]);
				glVertexPointer(3, GL_FLOAT, 0, 0);
				// Normal
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[1]);
				glNormalPointer(GL_FLOAT, 0, 0);

				glDrawArrays(GL_TRIANGLES, 0, nTriangles[1] * 3);

				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_NORMAL_ARRAY);
			}
			glPopMatrix();
		}
		glPopMatrix();
		//畫part5
		glPushMatrix();
		{
			glTranslatef(47, 68 + 5, 13.5);

			glRotatef(soRot[x] * 11 + 23.19 + part5_soRot[x], 0.0f, 0.0f, 1.0f);

			glTranslatef(-cent[4][0] + 109.5, -cent[4][1] + 23, -cent[4][2]);

			glColor3ub(128, 128, 128);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[4] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
		//畫re
		glPushMatrix();
		{
			//平移
			glTranslatef(100, -45.5, 5);
			//自轉

			glRotatef(soRot[x], 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[9][0] + 15), (-cent[9][1] + 20), -cent[9][2] - 2); //改原點

			glColor3ub(255, 255, 255);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_so[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_so[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[9] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void Draw_la(int x)
{
	glPushMatrix();
	{
		//平移
		glTranslatef(10, -16, 424 - 7 * 23 * x + 7 * 23);
		glPushMatrix();
		{
			if (load_Rot[0] == 0)
				Draw_load4(0, laRot[x]);
			else
				Draw_load4(0, 0);
		}
		glPopMatrix();
		glPushMatrix();
		{
			if (load_Rot[0] == 0)
			glTranslatef(0, -laRot[x] * 260 / 45, 0);
			Draw_load5(0);
		}
		glPopMatrix();
		glPushMatrix();
		{
			//平移
			glTranslatef(-70.5, 0, 5);
			//自轉
			glRotatef(-laRot[x] * 109.54 / 69.64, 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[0][0] + 56.5), -cent[0][1] + 16.5, -cent[0][2]); //改變座標原點

			glColor3ub(255, 231, 199);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[0] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			//畫part2
			glPushMatrix();
			{
				glTranslatef(-935, 26, 5);
				//自轉

				glRotatef(laRot[x] * 109.54 / 69.64 * 2 + 10, 0.0f, 0.0f, 1.0f);
				//改原點
				glTranslatef(-cent[1][0] + 17, -cent[1][1] + 26.5, -cent[1][2]); //x -z y

				glColor3ub(128, 128, 128);

				//以VBO畫三角網格
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);
				// Vertex
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[0]);
				glVertexPointer(3, GL_FLOAT, 0, 0);
				// Normal
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[1]);
				glNormalPointer(GL_FLOAT, 0, 0);

				glDrawArrays(GL_TRIANGLES, 0, nTriangles[1] * 3);

				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_NORMAL_ARRAY);
			}
			glPopMatrix();
		}
		glPopMatrix();
		//畫part5
		glPushMatrix();
		{
			glTranslatef(47, 68 + 5, 13.5);

			glRotatef(laRot[x] * 11 + 23.19 + part5_laRot[x], 0.0f, 0.0f, 1.0f);

			glTranslatef(-cent[4][0] + 109.5, -cent[4][1] + 23, -cent[4][2]);

			glColor3ub(128, 128, 128);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[4] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
		//畫la
		glPushMatrix();
		{
			//平移
			glTranslatef(100, -45.5, 5);
			//自轉

			glRotatef(laRot[x], 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[10][0] + 15), (-cent[10][1] + 20), -cent[10][2] + 2); //改原點

			glColor3ub(255, 255, 255);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_la[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_la[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[10] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void Draw_si(int x)
{
	glPushMatrix();
	{
		//平移
		glTranslatef(10, -16, 559 - 7 * 23 * x );
		glPushMatrix();
		{
			if (load_Rot[0] == 0)
				Draw_load4(0, siRot[x]);
			else
				Draw_load4(0, 0);
		}
		glPopMatrix();
		glPushMatrix();
		{
			if (load_Rot[0] == 0)
			glTranslatef(0, -siRot[x] * 260 / 45, 0);
			Draw_load5(0);
		}
		glPopMatrix();
		glPushMatrix();
		{
			//平移
			glTranslatef(-70.5, 0, 5);
			//自轉
			glRotatef(-siRot[x] * 109.54 / 69.64, 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[0][0] + 56.5), -cent[0][1] + 16.5, -cent[0][2]); //改變座標原點

			glColor3ub(255, 231, 199);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[0] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			//畫part2
			glPushMatrix();
			{
				glTranslatef(-935, 26, 5);
				//自轉

				glRotatef(siRot[x] * 109.54 / 69.64 * 2 + 10, 0.0f, 0.0f, 1.0f);
				//改原點
				glTranslatef(-cent[1][0] + 17, -cent[1][1] + 26.5, -cent[1][2]); //x -z y

				glColor3ub(128, 128, 128);

				//以VBO畫三角網格
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);
				// Vertex
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[0]);
				glVertexPointer(3, GL_FLOAT, 0, 0);
				// Normal
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[1]);
				glNormalPointer(GL_FLOAT, 0, 0);

				glDrawArrays(GL_TRIANGLES, 0, nTriangles[1] * 3);

				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_NORMAL_ARRAY);
			}
			glPopMatrix();
		}
		glPopMatrix();
		//畫part5
		glPushMatrix();
		{
			glTranslatef(47, 68 + 5, 13.5);

			glRotatef(siRot[x] * 11 + 23.19 + part5_siRot[x], 0.0f, 0.0f, 1.0f);

			glTranslatef(-cent[4][0] + 109.5, -cent[4][1] + 23, -cent[4][2]);

			glColor3ub(128, 128, 128);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[4] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
		//畫si
		glPushMatrix();
		{
			//平移
			glTranslatef(100, -45.5, 5);
			//自轉

			glRotatef(siRot[x], 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[11][0] + 15), (-cent[11][1] + 20), -cent[11][2] +5); //改原點

			glColor3ub(255, 255, 255);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_si[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_si[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[11] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void Draw_plus(int x, int y)
{
	glPushMatrix();
	{
		//平移
		if (y <= 1)
			glTranslatef(10, -16, 532 - 7 * 23 * x - 28 * y + 7 * 23);
		else
			glTranslatef(10, -16, 532 - 7 * 23 * x - 28 * y + 7 * 23 -11);
		glPushMatrix();
		{
			if (load_Rot[0] == 0)
				Draw_load4(0, plusRot[x][y]);
			else
				Draw_load4(0, 0);
		}
		glPopMatrix();
		glPushMatrix();
		{
			if (load_Rot[0] == 0)
			glTranslatef(0, -plusRot[x][y] * 260 / 45, 0);
			Draw_load5(0);
		}
		glPopMatrix();

		glPushMatrix();
		{
			//平移
			glTranslatef(-70.5, 0, 5);
			//自轉
			glRotatef(-plusRot[x][y] * 109.54 / 69.64, 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[0][0] + 56.5), -cent[0][1] + 16.5, -cent[0][2]); //改變座標原點

			glColor3ub(255, 231, 199);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[0] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			//畫part2
			glPushMatrix();
			{
				glTranslatef(-935, 26, 5);
				//自轉
				glRotatef(plusRot[x][y] * 109.54 / 69.64 * 2 + 10, 0.0f, 0.0f, 1.0f);
				//改原點
				glTranslatef(-cent[1][0] + 17, -cent[1][1] + 26.5, -cent[1][2]); //x -z y

				glColor3ub(128, 128, 128);

				//以VBO畫三角網格
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);
				// Vertex
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[0]);
				glVertexPointer(3, GL_FLOAT, 0, 0);
				// Normal
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[1]);
				glNormalPointer(GL_FLOAT, 0, 0);

				glDrawArrays(GL_TRIANGLES, 0, nTriangles[1] * 3);

				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_NORMAL_ARRAY);
			}
			glPopMatrix();
		}
		glPopMatrix();
		//畫part5
		glPushMatrix();
		{
			glTranslatef(47, 68 + 5, 13.5);
			glRotatef(plusRot[x][y]*11 + 23.19 + part5_plusRot[x][y], 0.0f, 0.0f, 1.0f);
			glTranslatef(-cent[4][0] + 109.5, -cent[4][1] + 23, -cent[4][2]);

			glColor3ub(128, 128, 128);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[4] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
		//畫plus
		glPushMatrix();
		{
			//平移
			glTranslatef(100, -45.5, 5);
			//自轉

			glRotatef(plusRot[x][y], 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[12][0] +40), (-cent[12][1] + 20), -cent[12][2]); //改原點

			glColor3ub(0, 0, 0);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_plus[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_plus[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[12] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void Draw_do_ex()
{
	glPushMatrix();
	{
		//平移
		glTranslatef(10, -16, -581 );
		glPushMatrix();
		{
			if (load_Rot[0] == 0)
				Draw_load4(0, doRot[8]);
			else
				Draw_load4(0, 0);
		}
		glPopMatrix();
		glPushMatrix();
		{
			if (load_Rot[0] == 0)
			glTranslatef(0, -doRot[8] * 260 / 45, 0);
			Draw_load5(0);
		}
		glPopMatrix();

		glPushMatrix();
		{
			//平移
			glTranslatef(-70.5, 0, 5);
			//自轉
			glRotatef(-doRot[8]*109.54 / 69.64, 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[0][0] + 56.5), -cent[0][1] + 16.5, -cent[0][2]); //改變座標原點

			glColor3ub(255, 231, 199);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[0] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			//畫part2
			glPushMatrix();
			{
				glTranslatef(-935, 26, 5);
				//自轉

				glRotatef(doRot[8] * 109.54 / 69.64 * 2 + 10, 0.0f, 0.0f, 1.0f);

				glTranslatef(-cent[1][0] + 17, -cent[1][1] + 26.5, -cent[1][2]); //x -z y

				glColor3ub(128, 128, 128);

				//以VBO畫三角網格
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);
				// Vertex
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[0]);
				glVertexPointer(3, GL_FLOAT, 0, 0);
				// Normal
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[1]);
				glNormalPointer(GL_FLOAT, 0, 0);

				glDrawArrays(GL_TRIANGLES, 0, nTriangles[1] * 3);

				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_NORMAL_ARRAY);
			}
			glPopMatrix();
		}
		glPopMatrix();
		//畫part5
		glPushMatrix();
		{
			glTranslatef(47, 68 + 5, 13.5);
			glRotatef(doRot[8] * 11 + 23.19 + part5_doRot[8], 0.0f, 0.0f, 1.0f);

			glTranslatef(-cent[4][0] + 109.5, -cent[4][1] + 23, -cent[4][2]);

			glColor3ub(128, 128, 128);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[4] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
		//畫do
		glPushMatrix();
		{
			//平移
			glTranslatef(100, -45.5, 5);
			//自轉

			glRotatef(doRot[8], 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[13][0] + 15), (-cent[13][1] + 20), -cent[13][2] - 5); //改原點

			glColor3ub(255, 255, 255);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_do_ex[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_do_ex[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[13] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void Draw_la_ex()
{
	glPushMatrix();
	{
		//平移
		glTranslatef(10, -16, 585);
		glPushMatrix();
		{
			if (load_Rot[0] == 0)
				Draw_load4(0, laRot[8]);
			else
				Draw_load4(0, 0);
		}
		glPopMatrix();
		glPushMatrix();
		{
			if (load_Rot[0] == 0)
			glTranslatef(0, -laRot[8] * 260 / 45, 0);
			Draw_load5(0);
		}
		glPopMatrix();

		glPushMatrix();
		{
			//平移
			glTranslatef(-70.5, 0, 5);
			//自轉
			glRotatef(-laRot[8]*109.54 / 69.64, 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[0][0] + 56.5), -cent[0][1] + 16.5, -cent[0][2]); //改變座標原點

			glColor3ub(255, 231, 199);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part1[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[0] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			//畫part2
			glPushMatrix();
			{
				glTranslatef(-935, 26, 5);
				//自轉

				glRotatef(laRot[8] * 109.54 / 69.64 * 2 + 10, 0.0f, 0.0f, 1.0f);
				//改原點
				glTranslatef(-cent[1][0] + 17, -cent[1][1] + 26.5, -cent[1][2]); //x -z y

				glColor3ub(128, 128, 128);

				//以VBO畫三角網格
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);
				// Vertex
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[0]);
				glVertexPointer(3, GL_FLOAT, 0, 0);
				// Normal
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part2[1]);
				glNormalPointer(GL_FLOAT, 0, 0);

				glDrawArrays(GL_TRIANGLES, 0, nTriangles[1] * 3);

				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_NORMAL_ARRAY);
			}
			glPopMatrix();
		}
		glPopMatrix();
		//畫part5
		glPushMatrix();
		{
			glTranslatef(47, 68 + 5, 13.5);

			glRotatef(laRot[8] * 11 + 23.19 + part5_laRot[8], 0.0f, 0.0f, 1.0f);

			glTranslatef(-cent[4][0] + 109.5, -cent[4][1] + 23, -cent[4][2]);

			glColor3ub(128, 128, 128);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part5[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[4] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
		//畫la
		glPushMatrix();
		{
			//平移
			glTranslatef(100, -45.5, 5);
			//自轉
			glRotatef(laRot[7], 0.0f, 0.0f, 1.0f);
			glTranslatef((-cent[14][0] + 15), (-cent[14][1] + 20), -cent[14][2] + 2); //改原點

			glColor3ub(255, 255, 255);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_la_ex[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_la_ex[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[14] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void Draw_main1()
{
	glPushMatrix();
	{
		//平移
		glTranslatef(-525-120 +2, 245, 5); 
		//自轉
		glRotatef( - 90, 1.0f, 0.0f, 0.0f);
		glRotatef( + 90, 0.0f, 0.0f, 1.0f);

		glTranslatef(-cent[15][0], -cent[15][1], -cent[15][2]); //改變座標原點

		glColor3ub(210, 210, 210);

		//以VBO畫三角網格
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		// Vertex
		glBindBuffer(GL_ARRAY_BUFFER, VBO_index_main1[0]);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		// Normal
		glBindBuffer(GL_ARRAY_BUFFER, VBO_index_main1[1]);
		glNormalPointer(GL_FLOAT, 0, 0);
		//glBindTexture(GL_TEXTURE_2D, textures[4]);
		glDrawArrays(GL_TRIANGLES, 0, nTriangles[15] * 3);
		//glBindTexture(GL_TEXTURE_2D, textures[0]);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
	glPopMatrix();

}
void Draw_main2()
{
	glPushMatrix();
	{
		glTranslatef(0, 0, 5);
		glPushMatrix();
		{
			//平移
			glTranslatef(-655 + 20, 110, 5);
			//自轉
			glRotatef(-90, 1.0f, 0.0f, 0.0f);
			glRotatef(+90, 0.0f, 0.0f, 1.0f);

			glTranslatef(-cent[16][0], -cent[16][1], -cent[16][2]); //改變座標原點

			glColor3ub(200, 200, 200);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);

			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_main2[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_main2[1]);
			glNormalPointer(GL_FLOAT, 0, 0);
			//
			float tempv[3][3];
			
			for (int i = 0; i < nTriangles[16]; i++)
			{

				tempv[0][0] = VBOv[16][i * 9 + 0], tempv[0][1] = VBOv[16][i * 9 + 1], tempv[0][2] = VBOv[16][i * 9 + 2];
				tempv[1][0] = VBOv[16][i * 9 + 3], tempv[1][1] = VBOv[16][i * 9 + 4], tempv[1][2] = VBOv[16][i * 9 + 5];
				tempv[2][0] = VBOv[16][i * 9 + 6], tempv[2][1] = VBOv[16][i * 9 + 7], tempv[2][2] = VBOv[16][i * 9 + 8];

				if (tempv[0][2]>19.9 && tempv[1][2]>19.9 && tempv[2][2]>20)
				{
					glBindTexture(GL_TEXTURE_2D, textures[4]); //melt
					glBegin(GL_TRIANGLES);
					glNormal3fv(VBOn[16]);

					glTexCoord2f(0.0f, 0.0f);
					glVertex3fv(tempv[0]);

					glTexCoord2f(0.0f, 1.0f);
					glVertex3fv(tempv[1]);

					glTexCoord2f(1.0f, 0.0f);
					glVertex3fv(tempv[2]);
					glEnd();
				}
				else if (tempv[0][2]>19 && tempv[1][2]>19 && tempv[2][2]>19 && tempv[0][2]<20 && tempv[1][2]<20 && tempv[2][2]<20)
				{
					glBindTexture(GL_TEXTURE_2D, textures[5]);//melt
					glBegin(GL_TRIANGLES);
					glNormal3fv(VBOn[16]);

					glTexCoord2f(0.0f, 0.0f);
					glVertex3fv(tempv[0]);

					glTexCoord2f(0.0f, 1.0f);
					glVertex3fv(tempv[1]);

					glTexCoord2f(1.0f, 0.0f);
					glVertex3fv(tempv[2]);
					glEnd();
				}
				else
				{
					glBindTexture(GL_TEXTURE_2D, textures[1]);//wood
					glBegin(GL_TRIANGLES);
					glNormal3fv(VBOn[16]);

					glTexCoord2f(0.0f, 0.0f);
					glVertex3fv(tempv[0]);

					glTexCoord2f(0.0f, 1.0f);
					glVertex3fv(tempv[1]);

					glTexCoord2f(1.0f, 0.0f);
					glVertex3fv(tempv[2]);
					glEnd();
				}
			}
			
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
	}
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, textures[0]);
}
void Draw_main3()
{
	glPushMatrix();
	{
		glTranslatef(175+30, 90 , 0);
		glPushMatrix();
		{
			//平移
			glTranslatef(-0, 0, 5);
			//自轉
			glRotatef(90, 0.0f, 1.0f, 0.0f);

			glTranslatef(-cent[17][0], -cent[17][1], -cent[17][2]); //改變座標原點

			glColor3ub(210, 210, 210);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_main3[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_main3[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[17] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
void Draw_main4()
{
	glPushMatrix();
	{
		glTranslatef(350-120, 0, 0);
		glPushMatrix();
		{
			//平移
			glTranslatef(-0, 0, 5);
			//自轉
			glRotatef( 90, 0.0f, 1.0f, 0.0f);
			glRotatef(xsRot +5, 1.0f, 0.0f, 0.0f);

			glTranslatef(-cent[18][0], -cent[18][1] + 110, -cent[18][2]+40); //改變座標原點

			glColor3ub(210, 210, 210);

			//以VBO畫三角網格
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			// Vertex
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_main4[0]);
			glVertexPointer(3, GL_FLOAT, 0, 0);
			// Normal
			glBindBuffer(GL_ARRAY_BUFFER, VBO_index_main4[1]);
			glNormalPointer(GL_FLOAT, 0, 0);

			glDrawArrays(GL_TRIANGLES, 0, nTriangles[18] * 3);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

//改變投影
void ChangeSize(int w, int h)
{
	GLfloat aspect;

	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspect = (GLfloat)w / (GLfloat)h;
	gluPerspective(60.0f, aspect, 1.0f, 6000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -1600.0f );
}
//將所有的物件繪製出來
void RenderScene(void)
{

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();                                   //因為讓光圓跟鑰匙分開旋轉，所以分兩個階段畫
	glEnable(GL_LIGHTING);                            //先畫上光源

	glDisable(GL_LIGHTING);                           //把燈光關掉再畫光源跟燈罩，否則也會出現亮點，這樣很怪
	glTranslatef(pos[0], pos[1], pos[2]);

	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot);

	glPopMatrix();


	//繪整體
	glPushMatrix();
	{
		//伸縮視角
		glTranslatef(0.0f, 0.0f, translate);
		//公轉
		glRotatef(xaRot + 20, 1.0f, 0.0f, 0.0f);
		glRotatef(yaRot - 100, 0.0f, 1.0f, 0.0f);
		if (idisplay_piano == display_piano)
		{//畫part4
			glPushMatrix();
			{
				glTranslatef(-cent[3][0], -cent[3][1], -cent[3][2]);

				glColor3ub(255, 211, 155);

				//以VBO畫三角網格
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);
				// Vertex
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part4[0]);
				glVertexPointer(3, GL_FLOAT, 0, 0);
				// Normal
				glBindBuffer(GL_ARRAY_BUFFER, VBO_index_part4[1]);
				glNormalPointer(GL_FLOAT, 0, 0);

				glDrawArrays(GL_TRIANGLES, 0, nTriangles[3] * 3);

				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_NORMAL_ARRAY);
			}
			glPopMatrix();
			//鋼琴本體
			glPushMatrix();
			{
				glTranslatef(tran[1], 0, 0);
				Draw_main1();
			}
			glPopMatrix();
			Draw_main2();
			glPushMatrix();
			{
				glTranslatef(0, tran[0], 0);
				Draw_main3();
				Draw_main4();
			}
			glPopMatrix();
		}
		//按鍵
		if (idisplay_button == ndisplay_button)
		{
			Draw_do(4);
			Draw_re(4);
			Draw_mi(4);
			Draw_fa(4);
			Draw_so(4);
			Draw_la(4);
			Draw_si(4);
			Draw_plus(4, 0);
			Draw_plus(4, 1);
			Draw_plus(4, 2);
			Draw_plus(4, 3);
			Draw_plus(4, 4);
		}
		else
		{
			for (int i = 1; i < 8; i++)
			{
				Draw_do(i);
				Draw_re(i);
				Draw_mi(i);
				Draw_fa(i);
				Draw_so(i);
				Draw_la(i);
				Draw_si(i);
				Draw_plus(i, 0);
				Draw_plus(i, 1);
				Draw_plus(i, 2);
				Draw_plus(i, 3);
				Draw_plus(i, 4);
			}
			Draw_si(0);
			Draw_plus(0, 4);
			Draw_do_ex();
			Draw_la_ex();
		}
		if (idisplay_load == display_load)
		{//踏板機構
			Draw_load1(0);
			Draw_load2(0);
			Draw_load3(0);
			glPushMatrix();
			{
				glTranslatef(0, 0, 65);
				Draw_load1(1);
				Draw_load2(1);
				glPushMatrix();
				{
					glTranslatef(0, 0, 65);
					Draw_load1(2);
					Draw_load2(2);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		
	}
	glPopMatrix();
	// Show the image
	glutSwapBuffers();
}
void SetupRC()
{
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 15.0f);           //設定光源角度與燈罩大致符合

	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	//

	

	glGenTextures(9, textures);
	for (int i = 0; i < 7; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]);

		pBytes = gltLoadTGA(szTextureFiles[i], &iWidth, &iHeight, &iComponents, &eFormat);

		gluBuild2DMipmaps(GL_TEXTURE_2D, iComponents, iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_CLIPMAP_LINEAR_SGIX);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		free(pBytes);
	}
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
	//
	InitVBO_part1();
	InitVBO_part2();
	InitVBO_part4();
	InitVBO_part5();

	InitVBO_do();
	InitVBO_re();
	InitVBO_mi();
	InitVBO_fa();
	InitVBO_so();
	InitVBO_la(); 
	InitVBO_si();
	InitVBO_plus();
	InitVBO_do_ex();
	InitVBO_la_ex();

	InitVBO_load1();
	InitVBO_load2();
	InitVBO_load3();
	InitVBO_load4();
	InitVBO_load5();

	InitVBO_main1();
	InitVBO_main2();
	InitVBO_main3();
	InitVBO_main4();

}
//選單控制
void ProcessMenu(int value)
{
	switch (value)
	{
	case 1:
		iplaymusic = stop;
		break;

	case 2:
		iplaymusic = play_music1;
		break;
	case 3:
		iplaymusic = play_music2;
		break;
	case 4:
		iplaymusic = play_music3;
		break;
	}

	// Trigger a redraw
	glutPostRedisplay();
}
//控制鍵
void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xaRot -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		xaRot += 5.0f;

	if (key == GLUT_KEY_LEFT)
		yaRot -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		yaRot += 5.0f;

	if (key == GLUT_KEY_PAGE_UP && load_Rot[0]<0)
		load_Rot[0] += 5.0f;

	if (key == GLUT_KEY_PAGE_DOWN && load_Rot[0] == 0) 
		load_Rot[0] -= 5.0f;
	//關閉/開啟 琴蓋
	if (key == GLUT_KEY_F1 && xsRot < 85)
		xsRot += 5.0f;

	if (key == GLUT_KEY_F2 && xsRot > 0)
		xsRot -= 5.0f;
	//分解/合成 鋼琴
	if (key == GLUT_KEY_F3)
		ipiano_break_combine = piano_break;

	if (key == GLUT_KEY_F4)
		ipiano_break_combine = piano_combine;
	//顯示/關閉 C4~B4其他按鍵
	if (key == GLUT_KEY_F5)
		idisplay_button = display_button;

	if (key == GLUT_KEY_F6)
		idisplay_button = ndisplay_button;
	//顯示/關閉 鋼琴本體
	if (key == GLUT_KEY_F7)
	{
		idisplay_load = display_load;
		idisplay_piano = display_piano;
	}
	if (key == GLUT_KEY_F8)
	{
		idisplay_load = display_load;
		idisplay_piano = ndisplay_piano;
	}
	//放大/縮小 視角
	if (key == GLUT_KEY_F9 )
		translate += 50.0f;

	if (key == GLUT_KEY_F10 )
		translate -= 50.0f;
	// Refresh the Window
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y)
{
	if (key == 'a')
		ipress[4] = press_C4;
	if (key == 'w')
		ipress[12] = press_C4P;
	if (key == 's')
		ipress[19] = press_D4;
	if (key == 'e')
		ipress[26] = press_D4P;
	if (key == 'd')
		ipress[33] = press_E4;
	if (key == 'f')
		ipress[40] = press_F4;
	if (key == 't')
		ipress[47] = press_F4P;
	if (key == 'g')
		ipress[54] = press_G4;
	if (key == 'y')
		ipress[61] = press_G4P;
	if (key == 'h')
		ipress[69] = press_A4;
	if (key == 'u')
		ipress[77] = press_A4P;
	if (key == 'j')
		ipress[85] = press_B4;

	if (idisplay_button == display_button)
	{
		if (key == 'z')
			ipress[5] = press_C5;
		if (key == 'x')
			ipress[20] = press_D5;
		if (key == 'c')
			ipress[34] = press_E5;
		if (key == 'v')
			ipress[41] = press_F5;
		if (key == 'b')
			ipress[55] = press_G5;
		if (key == 'n')
			ipress[70] = press_A5;
		if (key == 'm')
			ipress[86] = press_B5;
	}

}
void keyboardUp(unsigned char key, int x, int y)
{
	if (key == 'a' )
		ipress[4] = ease_C4;
	if (key == 'w')
		ipress[12] = ease_C4P;
	if (key == 's')
		ipress[19] = ease_D4;
	if (key == 'e')
		ipress[26] = ease_D4P;
	if (key == 'd')
		ipress[33] = ease_E4;
	if (key == 'f')
		ipress[40] = ease_F4;
	if (key == 't')
		ipress[47] = ease_F4P;
	if (key == 'g')
		ipress[54] = ease_G4;
	if (key == 'y')
		ipress[61] = ease_G4P;
	if (key == 'h')
		ipress[69] = ease_A4;
	if (key == 'u')
		ipress[77] = ease_A4P;
	if (key == 'j')
		ipress[85] = ease_B4;
	if (idisplay_button == display_button)
	{
		if (key == 'z')
			ipress[5] = ease_C5;
		if (key == 'x')
			ipress[20] = ease_D5;
		if (key == 'c')
			ipress[34] = ease_E5;
		if (key == 'v')
			ipress[41] = ease_F5;
		if (key == 'b')
			ipress[55] = ease_G5;
		if (key == 'n')
			ipress[70] = ease_A5;
		if (key == 'm')
			ipress[86] = ease_B5;
	}
}
//讀取音樂檔
void PlayMp3(LPCSTR music)
{
	char buf[128];
	char str[128] = { 0 };
	int i = 0;
	//use mciSendCommand 
	MCI_OPEN_PARMS mciOpen;
	MCIERROR mciError;
	//SetWindowText(NULL,"12345"); 
	mciOpen.lpstrDeviceType = "mpegvideo";
	mciOpen.lpstrElementName = music;
	mciError = mciSendCommand(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)&mciOpen);
	if (mciError)
	{
		mciGetErrorString(mciError, buf, 128);
		printf("send MCI_OPEN command failed:%s\n", buf);
		return;
	}
	UINT DeviceID = mciOpen.wDeviceID;
	MCI_PLAY_PARMS mciPlay;
	mciError = mciSendCommand(DeviceID, MCI_PLAY, 0, (DWORD)&mciPlay);
	if (mciError)
	{
		printf("send MCI_PLAY command failed\n");
		return;
	}
}

////////////////////////////樂譜//////////////////////////////////////
//使用二維矩陣紀錄
//[0][xxx]：紀錄要彈什麼音
//[1][xxx]：紀錄按鍵要按下多久
//music1 (天空之城) 樂譜
int k = 0, k1 = 0;
int music1[2][162] =  
{ {
	//1-4
	69, 85, 5, 85, 5, 34, 85, 33, 69, 54, 69, 5, 54,
	40, 33, 40, 33, 40, 5, 33, 5, 5, 5, 85, 47, 47, 85, 85,
	//5-8
	69, 85, 5, 85, 5, 34, 85, 33, 33, 69, 54, 69, 5, 54,
	33, 40, 5, 85, 5, 20, 34, 5, 5, 85, 69, 85, 61, 69,
	//9-12
	5, 20, 34, 20, 34, 55, 20, 54, 54, 5, 85, 5, 34, 34,
	69, 85, 5, 85, 5, 20, 5, 54, 54, 41, 34, 20, 5, 34,
	//13-16
	34, 70, 55, 34, 20, 5, 20, 5, 20, 55, 34,
	34, 70, 55, 34, 20, 5, 20, 5, 20, 85, 69,
	//17-20
	69, 85, 5, 85, 5, 34, 85, 33, 69, 54, 69, 5, 54,
	40, 33, 40, 33, 40, 5, 33, 5, 5, 5, 85, 47, 47, 85, 85,
	//21-24
	69, 85, 5, 85, 5, 34, 85, 33, 33, 69, 54, 69, 5, 54,
	33, 40, 5, 85, 5, 20, 34, 5, 5, 85, 69, 85, 61, 69,
	}
	,/////////////////////////////////////////////////////////
	{
		//1-4	
		6, 6, 18, 6, 12, 12, 24, 12, 18, 6, 12, 12, 24,
		8, 8, 18, 8, 12, 12, 24, 6, 6, 6, 18, 6, 12, 12, 24,
		//5-8
		6, 6, 18, 6, 12, 12, 24, 12, 12, 18, 6, 12, 12, 24,
		12, 12, 6, 12, 12, 12, 6, 18, 6, 6, 12, 12, 12, 36,
		//9-12
		6, 6, 18, 6, 12, 12, 24, 6, 6, 18, 6, 12, 12, 36,
		6, 6, 12, 6, 6, 12, 18, 6, 24, 12, 12, 12, 12, 84,
		//13-16
		12, 24, 24, 12, 6, 18, 12, 6, 12, 12, 36,
		12, 24, 24, 12, 6, 18, 12, 6, 12, 12, 36,
		//17-20
		6, 6, 18, 6, 12, 12, 24, 12, 18, 6, 12, 12, 24,
		6, 6, 18, 6, 12, 12, 24, 6, 6, 6, 18, 6, 12, 12, 24,
		//21-24
		6, 6, 18, 6, 12, 12, 24, 12, 12, 18, 6, 12, 12, 24,
		12, 12, 6, 12, 12, 12, 6, 18, 6, 6, 12, 12, 12, 36,
	}};
/////////////////////////////////////////////////////////////////////////////////////////
//music2 (楓之谷) 樂譜
int k2 = 0, k3 = 0; 
int music2[2][91] =  //右手譜
{ {
	// 1  (11)(11)=22
	0, 0, 0, 26, 40, 54, 0, 0, 54, 0, 0,
	0, 0, 0, 12, 40, 61, 0, 0, 61, 0, 0,
	// 2  (11)(8)=19
	0, 0, 0, 12, 40, 61, 0, 0, 61, 0, 0,
	0, 0, 0, 26, 40, 54, 40, 26,
	// 3  (13)(13)=26
	0, 0, 0, 26, 40, 54, 0, 61, 77, 27, 61, 77, 27,
	0, 0, 0, 12, 40, 61, 0, 27, 41, 62, 55, 41, 27,
	// 4  (11)(13)=24
	0, 0, 0, 26, 40, 61, 13, 5, 77, 61, 77,
	0, 0, 0, 26, 40, 54, 4, 76, 4, 12, 4, 12, 26
	}
	,/////////////////////////////////////////
	{
		// 1
		3, 3, 3, 7, 7, 7, 3, 7, 3, 7, 3,
		3, 3, 3, 7, 7, 7, 3, 7, 3, 7, 3,
		// 2
		3, 3, 3, 7, 7, 7, 3, 7, 3, 7, 3,
		3, 3, 3, 7, 7, 12, 7, 16,
		// 3
		3, 3, 3, 7, 7, 7, 3, 3, 3, 3, 3, 3, 3,
		3, 3, 3, 7, 7, 7, 3, 3, 3, 3, 3, 3, 3,
		// 4
		3, 3, 3, 7, 7, 3, 7, 3, 7, 7, 7,
		3, 3, 3, 7, 7, 7, 3, 3, 3, 3, 3, 3, 3,
	} };
///////////////////////////////////////////////////////////////////////////////
int k2_2 = 0, k3_2 = 0;
int music2_2[2][91] =  //左手譜
{ {
	// 1
	75, 25, 76, 0, 0, 0, 0, 0, 0, 0, 0,
	59, 11, 60, 0, 0, 0, 0, 0, 0, 0, 0,
	// 2
	59, 11, 60, 0, 0, 0, 0, 0, 0, 0, 0,
	75, 25, 76, 0, 0, 0, 0, 0,
	// 3
	75, 25, 76, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	59, 11, 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	// 4
	59, 25, 60, 0, 0, 0, 0, 0, 0, 0, 0,
	75, 25, 76, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	}
	,////////////////////////////////////////
	{
		// 1
		3, 3, 3, 7, 7, 7, 3, 7, 3, 7, 3,
		3, 3, 3, 7, 7, 7, 3, 7, 3, 7, 3,
		// 2
		3, 3, 3, 7, 7, 7, 3, 7, 3, 7, 3,
		3, 3, 3, 7, 7, 12, 7, 16,
		// 3
		3, 3, 3, 7, 7, 7, 3, 3, 3, 3, 3, 3, 3,
		3, 3, 3, 7, 7, 7, 3, 3, 3, 3, 3, 3, 3,
		// 4
		3, 3, 3, 7, 7, 3, 7, 3, 7, 7, 7,
		3, 3, 3, 7, 7, 7, 3, 3, 3, 3, 3, 3, 3,
	} };
/////////////////////////////////////////////////////////////////////////////////////////
//music3 (IB memory) 樂譜
int k4 = 0, k5 = 0;
int music3[2][48] =  //右手譜
{ {
	// 1
	0, 0, 0, 0, 0, 0,
	33, 0, 0, 0, 0, 0,
	33, 0, 0, 0, 0, 0,
	19, 0, 0, 0, 0, 0,
	// 2
	19, 0, 0, 0, 0, 0,
	4, 0, 0, 0, 0, 0,
	68, 0, 0, 0, 0, 0,
	84, 0, 0, 0, 0, 0,
	}
	,/////////////////////////////////////////
	{
		// 1
		14, 14, 14, 14, 14, 14,
		14, 14, 14, 14, 24, 4,
		14, 14, 14, 14, 14, 14,
		14, 14, 14, 14, 24, 4,
		// 2
		14, 14, 14, 14, 14, 14,
		14, 14, 14, 14, 24, 4,
		14, 14, 14, 14, 14, 14,
		14, 14, 14, 14, 24, 4,

	} };
///////////////////////////////////////////////////////////////////////////////
int k4_2 = 0, k5_2 = 0;
int music3_2[2][48] =  //左手譜
{ {
	// 1
	67, 32, 68, 84, 4, 19,
	59, 32, 60, 84, 33, 0,
	52, 32, 68, 84, 4, 33,
	45, 18, 46, 68, 19, 0,
	 // 2
	 38, 18, 68, 84, 4, 19,
	 31, 3, 32, 68, 4, 0,
	 24, 67, 3, 25, 68, 4,
	 31, 83, 32, 60, 33, 0
	}
	,////////////////////////////////////////
	{
		// 1
		14, 14, 14, 14, 14, 14,
		14, 14, 14, 14, 24, 4,
		14, 14, 14, 14, 14, 14,
		14, 14, 14, 14, 24, 4,
		// 2
		14, 14, 14, 14, 14, 14,
		14, 14, 14, 14, 24, 4,
		14, 14, 14, 14, 14, 14,
		14, 14, 14, 14, 24, 4,
	} };
/////////////////////////////////////////////////////////////////////////////////////////
////music3 (地下城) 樂譜
//int k4 = 0, k5 = 0;
//int music3[2][112] =
//{ {
//	 1
//	76, 40, 26, 76, 19, 19, 26,
//	0, 76, 26, 76, 19, 19, 26,
//	76, 40, 26, 76, 19, 19, 26,
//	0, 76, 26, 54, 40, 26, 40,
//	 2
//	76, 40, 26, 76, 19, 19, 26,
//	0, 76, 26, 76, 19, 19, 26,
//	76, 40, 26, 76, 19, 19, 26,
//	0, 76, 26, 54, 40, 26, 40,
//	 3
//	76, 40, 26, 76, 19, 19, 26,
//	0, 76, 26, 76, 19, 19, 26,
//	76, 40, 26, 76, 19, 19, 26,
//	0, 76, 26, 54, 40, 26, 40,
//	 4
//	76, 40, 26, 76, 19, 19, 26,
//	0, 76, 26, 76, 19, 19, 26,
//	76, 40, 26, 76, 19, 19, 26,
//	0, 76, 26, 54, 40, 26, 40,
//
//	}
//	,/////////////////////////////////////////
//	{
//		 1
//		14, 14, 14, 14, 21, 21, 14,
//		14, 14, 14, 14, 21, 21, 14,
//		14, 14, 14, 14, 21, 21, 14,
//		14, 14, 14, 14, 21, 21, 14,
//		 2
//		14, 14, 14, 14, 21, 21, 14,
//		14, 14, 14, 14, 21, 21, 14,
//		14, 14, 14, 14, 21, 21, 14,
//		14, 14, 14, 14, 21, 21, 14,
//		 3
//		14, 14, 14, 14, 21, 21, 14,
//		14, 14, 14, 14, 21, 21, 14,
//		14, 14, 14, 14, 21, 21, 14,
//		14, 14, 14, 14, 21, 21, 14,
//		 4
//		14, 14, 14, 14, 21, 21, 14,
//		14, 14, 14, 14, 21, 21, 14,
//		14, 14, 14, 14, 21, 21, 14,
//		14, 14, 14, 14, 21, 21, 14,
//
//	} };
///////////////////////////////////////////////////////////////////////////////
//int k4_2 = 0, k5_2 = 0;
//int music3_2[2][140] =
//{ {
//	 1
//	0, 25, 0, 25, 0, 25, 0, 25,
//	0, 25, 0, 25, 0, 25, 0, 25,
//	0, 25, 0, 25, 0, 25, 0, 25,
//	0, 25, 0, 25, 0, 25, 0, 25,
//	 2
//	0, 25, 0, 25, 0, 25, 0, 25,
//	0, 25, 0, 25, 0, 25, 0, 25,
//	0, 25, 0, 25, 0, 25, 0, 25,
//	0, 25, 0, 25, 0, 25, 0, 25,
//
//	 3
//	25, 67, 25, 0, 25, 0, 25,
//	0, 25, 0, 25, 0, 25, 0, 25,
//	0, 25, 0, 25, 0, 25, 0, 25,
//	0, 25, 0, 25, 0, 25, 0, 25,
//	 4
//	0, 25, 0, 25, 0, 25, 0, 25,
//	0, 25, 0, 25, 0, 25, 0, 25,
//	0, 25, 0, 25, 0, 25, 0, 25,
//	0, 25, 0, 25, 0, 25, 0, 25,
//	}
//	,////////////////////////////////////////
//	{
//		 1
//		14, 14, 14, 14, 14, 14, 14, 14,
//		14, 14, 14, 14, 14, 14, 14, 14,
//		14, 14, 14, 14, 14, 14, 14, 14,
//		14, 14, 14, 14, 14, 14, 14, 14,
//		 2
//		16, 16, 16, 16, 16, 16, 16, 16,
//		16, 16, 16, 16, 16, 16, 16, 16,
//		16, 16, 16, 16, 16, 16, 16, 16,
//		16, 16, 16, 16, 16, 16, 16, 16,
//	} };

//鋼琴自動彈奏
void stop_function()
{
	//回歸按鍵到ease
	ipress[music1[0][k]] = music1[0][k] + 100;
	ipress[music2[0][k2]] = music2[0][k2] + 100;
	ipress[music2_2[0][k2_2]] = music2_2[0][k2_2] + 100;
	//將記錄按鍵狀態的值歸零
	for (int j = 0; j < 90; j++)
	{
		i[j] = 0;
		ipress[j] = 0;
	}
	//將所有按鍵的角度歸零
	for (int j = 0; j < 9; j++)
	{
		doRot[j] = 0;
		reRot[j] = 0;
		miRot[j] = 0;
		faRot[j] = 0;
		soRot[j] = 0;
		laRot[j] = 0;
		siRot[j] = 0;
		part5_doRot[j] = 0;
		part5_reRot[j] = 0;
		part5_miRot[j] = 0;
		part5_faRot[j] = 0;
		part5_soRot[j] = 0;
		part5_laRot[j] = 0;
		part5_siRot[j] = 0;
		for (int z = 0; z < 6; z++)
		{
			plusRot[j][z] = 0;
			part5_plusRot[j][z] = 0;
		}
	}
	//將記錄樂譜狀態的變數歸零
	k = 0;
	k1 = 0;

	k2 = 0;
	k3 = 0;
	k2_2 = 0;
	k3_2 = 0;

	k4 = 0;
	k5 = 0;
	k4_2 = 0;
	k5_2 = 0;
}
void playmusic()
{
	// 1
	if (iplaymusic == play_music1 && k < 162)
	{
		//確認動態空間已刪除
		if (k4 != 0 || k2 != 0)
			stop_function();
		//判斷此按鍵要按下多久，並什麼時候該換下一個音
		if (music1[1][k] > k1)
		{
			ipress[music1[0][k]] = music1[0][k];
			k1++;
		}
		else //將按鍵放開，並將按鍵狀態歸零
		{
			ipress[music1[0][k]] = music1[0][k] + 100;
			if (music1[0][k] == music1[0][k + 1])
				i[music1[0][k]] = 0;
			k++; //播放下一個音
			k1 = 0;
		}
		if (k1 == 162)
			iplaymusic = stop;
	}
	//  2
	else if (iplaymusic == play_music2 && k2 < 91)
	{
		//確認動態空間已刪除
		if (k4 != 0 || k != 0)
			stop_function();
		//_right hand
		//判斷此按鍵要按下多久，並什麼時候該換下一個音
		if (music2[1][k2] > k3)
		{
			ipress[music2[0][k2]] = music2[0][k2];
			k3++;
		}
		else //將按鍵放開，並將按鍵狀態歸零
		{
			ipress[music2[0][k2]] = music2[0][k2] + 100;
			if (music2[0][k2] == music2[0][k2 + 1])
				i[music2[0][k2]] = 0;
			k2++;//播放下一個音
			k3 = 0;
		}
		//_left hand
		//判斷此按鍵要按下多久，並什麼時候該換下一個音
		if (music2_2[1][k2_2] > k3_2)
		{
			ipress[music2_2[0][k2_2]] = music2_2[0][k2_2];
			k3_2++;
		}
		else //將按鍵放開，並將按鍵狀態歸零
		{
			ipress[music2_2[0][k2_2]] = music2_2[0][k2_2] + 100;
			if (music2_2[0][k2_2] == music2_2[0][k2_2 + 1])
				i[music2_2[0][k2_2]] = 0;
			k2_2++;//播放下一個音
			k3_2 = 0;
		}
		if (k2 == 91)
			iplaymusic = stop;
	}
	//  3
	else if (iplaymusic == play_music3 && k4 < 48)
	{
		//確認動態空間已刪除
		if (k != 0 || k2 != 0)
			stop_function();
		//_right hand
		//判斷此按鍵要按下多久，並什麼時候該換下一個音
		if (music3[1][k4] > k5)
		{
			ipress[music3[0][k4]] = music3[0][k4];
			k5++;
		}
		else //將按鍵放開，並將按鍵狀態歸零
		{
			ipress[music3[0][k4]] = music3[0][k4] + 100;
			if (music3[0][k4] == music3[0][k4 + 1])
				i[music3[0][k4]] = 0;
			k4++;//播放下一個音
			k5 = 0;
		}
		//_left hand
		//判斷此按鍵要按下多久，並什麼時候該換下一個音
		if (music3_2[1][k4_2] > k5_2)
		{
			ipress[music3_2[0][k4_2]] = music3_2[0][k4_2];
			k5_2++;
		}
		else //將按鍵放開，並將按鍵狀態歸零
		{
			ipress[music3_2[0][k4_2]] = music3_2[0][k4_2] + 100;
			if (music3_2[0][k4_2] == music3_2[0][k4_2 + 1])
				i[music3_2[0][k4_2]] = 0;
			k4_2++;//播放下一個音
			k5_2 = 0;
		}
		if (k4 == 48)
			iplaymusic = stop;
	}

	// stop
	else if (iplaymusic == stop)
	{
		stop_function();
		iplaymusic = reset;
	}
	else
		iplaymusic = reset;
}

//時間函式
void play_sound(int j,int x)
{
	int temp = 0;
	PlayMp3(sound[x]);
	//Sleep(6000);
}
void play_time_function()  
{
	////////////////////////////////
	//C1
	if (ipress[4] == press_C1 && i[1] <= 4)
	{
		int x = i[1];
		doRot[1] = -1.3f* i[1] / 4;
		if(part5_doRot[1]>-4)
			part5_doRot[1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[1]++;
		if (i[1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 1);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[1] == ease_C1 && i[1] <= 5 && i[1]>0)
	{
		i[1]--;
		doRot[1] = -1.3f* i[1] / 4;
		part5_doRot[1] = 0;
	}
	//////////////////////////////////////////// 2
	//C2
	if (ipress[2] == press_C2 && i[2] <= 4)
	{
		int x = i[2];
		doRot[2] = -1.3f* i[2] / 4;
		part5_doRot[2] = -(8.0f * i[2] - 5.0f / 2 * pow(i[2], 2));
		i[2]++;
		if (i[2] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 2);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[2] == ease_C2 && i[2] <= 5 && i[2]>0)
	{
		i[2]--;
		doRot[2] = -1.3f* i[2] / 4;
		part5_doRot[2] = 0;
	}
	//C2P
	if (ipress[11 - 1] == press_C2P && i[11 - 1] <= 4)
	{
		int x = i[11 - 1];
		plusRot[3 - 1][0] = -1.3f* i[11 - 1] / 4;
		part5_plusRot[3 - 1][0] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[11 - 1]++;
		if (i[11 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 10);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[11 - 1] == ease_C2P && i[11 - 1] <= 5 && i[11 - 1]>0)
	{
		i[11 - 1]--;
		plusRot[3 - 1][0] = -1.3f* i[11 - 1] / 4;
		part5_plusRot[3 - 1][0] = 0;

	}
	//D2
	if (ipress[19 - 1 - 1] == press_D2 && i[19 - 1 - 1] <= 4)
	{
		int x = i[19 - 1 - 1];
		reRot[4 - 1 - 1] = -1.3f* i[19 - 1 - 1] / 4;
		part5_reRot[4 - 1 - 1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[19 - 1 - 1]++;
		if (i[19 - 1 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 18);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[19 - 1 - 1] == ease_D2 && i[19 - 1 - 1] <= 5 && i[19 - 1 - 1]>0)
	{
		i[19 - 1 - 1]--;
		reRot[4 - 1 - 1] = -1.3f* i[19 - 1 - 1] / 4;
		part5_reRot[4 - 1 - 1] = 0;
	}
	//D2P
	if (ipress[26 - 1 - 1] == press_D2P && i[26 - 1 - 1] <= 4)
	{
		int x = i[26 - 1 - 1];
		plusRot[4 - 1 - 1][1] = -1.3f* i[26 - 1 - 1] / 4;
		part5_plusRot[4 - 1 - 1][1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[26 - 1 - 1]++;
		if (i[26 - 1 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 24);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[26 - 1 - 1] == ease_D2P && i[26 - 1 - 1] <= 5 && i[26 - 1 - 1]>0)
	{
		i[26 - 1 - 1]--;
		plusRot[4 - 1 - 1][1] = -1.3f* i[26 - 1 - 1] / 4;
		part5_plusRot[4 - 1 - 1][1] = 0;
	}
	//E2
	if (ipress[33 - 1 - 1] == press_E2 && i[33 - 1 - 1] <= 4)
	{
		int x = i[33 - 1 - 1];
		miRot[4 - 1 - 1] = -1.3f* i[33 - 1 - 1] / 4;
		part5_miRot[4 - 1 - 1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[33 - 1 - 1]++;
		if (i[33 - 1 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 31);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[33 - 1 - 1] == ease_E2 && i[33 - 1 - 1] <= 5 && i[33 - 1 - 1]>0)
	{
		i[33 - 1 - 1]--;
		miRot[4 - 1 - 1] = -1.3f* i[33 - 1 - 1] / 4;
		part5_miRot[4 - 1 - 1] = 0;
	}
	//F2
	if (ipress[40 - 1 - 1] == press_F2 && i[40 - 1 - 1] <= 4)
	{
		int x = i[40 - 1 - 1];
		faRot[4 - 1 - 1] = -1.3f* i[40 - 1 - 1] / 4;
		part5_faRot[4 - 1 - 1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[40 - 1 - 1]++;
		if (i[40 - 1 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 38);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[40 - 1 - 1] == ease_F2 && i[40 - 1 - 1] <= 5 && i[40 - 1 - 1]>0)
	{
		i[40 - 1 - 1]--;
		faRot[4 - 1 - 1] = -1.3f* i[40 - 1 - 1] / 4;
		part5_faRot[4 - 1 - 1] = 0;
	}
	//F2P
	if (ipress[47 - 1 - 1] == press_F2P && i[47 - 1 - 1] <= 4)
	{
		int x = i[47 - 1 - 1];
		plusRot[4 - 1 - 1][2] = -1.3f* i[47 - 1 - 1] / 4;
		part5_plusRot[4 - 1 - 1][2] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[47 - 1 - 1]++;
		if (i[47 - 1 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 45);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[47 - 1 - 1] == ease_F2P && i[47 - 1 - 1] <= 5 && i[47 - 1 - 1]>0)
	{
		i[47 - 1 - 1]--;
		plusRot[4 - 1 - 1][2] = -1.3f* i[47 - 1 - 1] / 4;
		part5_plusRot[4 - 1 - 1][2] = 0;
	}
	//G2
	if (ipress[54 - 1 - 1] == press_G2 && i[54 - 1 - 1] <= 4)
	{
		int x = i[54 - 1 - 1];
		soRot[4 - 1 - 1] = -1.3f* i[54 - 1 - 1] / 4;
		part5_soRot[4 - 1 - 1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[54 - 1 - 1]++;
		if (i[54 - 1 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 52);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[54 - 1 - 1] == ease_G2 && i[54 - 1 - 1] <= 5 && i[54 - 1 - 1]>0)
	{
		i[54 - 1 - 1]--;
		soRot[4 - 1 - 1] = -1.3f* i[54 - 1 - 1] / 4;
		part5_soRot[4 - 1 - 1] = 0;
	}
	//G2P
	if (ipress[61 - 1 - 1] == press_G2P && i[61 - 1 - 1] <= 4)
	{
		int x = i[61 - 1 - 1];
		plusRot[4 - 1 - 1][3] = -1.3f* i[61 - 1 - 1] / 4;
		part5_plusRot[4 - 1 - 1][3] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[61 - 1 - 1]++;
		if (i[61 - 1 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 59);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[61 - 1 - 1] == ease_G2P && i[61 - 1 - 1] <= 5 && i[61 - 1 - 1]>0)
	{
		i[61 - 1 - 1]--;
		plusRot[4 - 1 - 1][3] = -1.3f* i[61 - 1 - 1] / 4;
		part5_plusRot[4 - 1 - 1][3] = 0;
	}
	//A2
	if (ipress[69 - 1 - 1] == press_A2 && i[69 - 1 - 1] <= 4)
	{
		int x = i[69 - 1 - 1];
		laRot[4 - 1 - 1] = -1.3f* i[69 - 1 - 1] / 4;
		part5_laRot[4 - 1 - 1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[69 - 1 - 1]++;
		if (i[69 - 1 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 67);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[69 - 1 - 1] == ease_A2 && i[69 - 1 - 1] <= 5 && i[69 - 1 - 1]>0)
	{
		i[69 - 1 - 1]--;
		laRot[4 - 1 - 1] = -1.3f* i[69 - 1 - 1] / 4;
		part5_laRot[4 - 1 - 1] = 0;
	}
	//A2P
	if (ipress[77 - 1 - 1] == press_A2P && i[77 - 1 - 1] <= 4)
	{
		int x = i[77 - 1 - 1];
		plusRot[4 - 1 - 1][4] = -1.3f* i[77 - 1 - 1] / 4;
		part5_plusRot[4 - 1 - 1][4] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[77 - 1 - 1]++;
		if (i[77 - 1 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 75);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[77 - 1 - 1] == ease_A2P && i[77 - 1 - 1] <= 5 && i[77 - 1 - 1]>0)
	{
		i[77 - 1 - 1]--;
		plusRot[4 - 1 - 1][4] = -1.3f* i[77 - 1 - 1] / 4;
		part5_plusRot[4 - 1 - 1][4] = 0;
	}
	//B2
	if (ipress[85 - 1 - 1] == press_B2 && i[85 - 1 - 1] <= 4)
	{
		int x = i[85 - 1 - 1];
		siRot[4 - 1 - 1] = -1.3f* i[85 - 1 - 1] / 4;
		part5_siRot[4 - 1 - 1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[85 - 1 - 1]++;
		if (i[85 - 1 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 83);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[85 - 1 - 1] == ease_B2 && i[85 - 1 - 1] <= 5 && i[85 - 1 - 1]>0)
	{
		i[85 - 1 - 1]--;
		siRot[4 - 1 - 1] = -1.3f* i[85 - 1 - 1] / 4;
		part5_siRot[4 - 1 - 1] = 0;
	}
	////////////////////////////////////////////////////////////
	//C3
	if (ipress[3] == press_C3 && i[3] <= 4)
	{
		doRot[3] = -1.3f* i[3] / 4;
		part5_doRot[3] = -(8.0f * i[3] - 5.0f / 2 * pow(i[3], 2));
		i[3]++;
		if (i[3] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 3);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[3] == ease_C3 && i[3] <= 5 && i[3]>0)
	{
		i[3]--;
		doRot[3] = -1.3f* i[3] / 4;
		part5_doRot[3] = 0;
	}
	//C3P
	if (ipress[11] == press_C3P && i[11] <= 4)
	{
		int x = i[11];
		plusRot[3][0] = -1.3f* i[11] / 4;
		part5_plusRot[3][0] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[11]++;
		if (i[11] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 11);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[11] == ease_C3P && i[11] <= 5 && i[11]>0)
	{
		i[11]--;
		plusRot[3][0] = -1.3f* i[11] / 4;
		part5_plusRot[3][0] = 0;

	}
	//D3
	if (ipress[19 - 1] == press_D3 && i[19 - 1] <= 4)
	{
		int x = i[19 - 1];
		reRot[4 - 1] = -1.3f* i[19 - 1] / 4;
		part5_reRot[4 - 1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[19 - 1]++;
		if (i[19 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 18);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[19 - 1] == ease_D3 && i[19 - 1] <= 5 && i[19 - 1]>0)
	{
		i[19 - 1]--;
		reRot[4 - 1] = -1.3f* i[19 - 1] / 4;
		part5_reRot[4 - 1] = 0;
	}
	//D3P
	if (ipress[26 - 1] == press_D3P && i[26 - 1] <= 4)
	{
		int x = i[26 - 1];
		plusRot[4 - 1][1] = -1.3f* i[26 - 1] / 4;
		part5_plusRot[4 - 1][1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[26 - 1]++;
		if (i[26 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 25);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[26 - 1] == ease_D3P && i[26 - 1] <= 5 && i[26 - 1]>0)
	{
		i[26 - 1]--;
		plusRot[4 - 1][1] = -1.3f* i[26 - 1] / 4;
		part5_plusRot[4 - 1][1] = 0;
	}
	//E3
	if (ipress[33 - 1] == press_E3 && i[33 - 1] <= 4)
	{
		int x = i[33 - 1];
		miRot[4 - 1] = -1.3f* i[33 - 1] / 4;
		part5_miRot[4 - 1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[33 - 1]++;
		if (i[33 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 32);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[33 - 1] == ease_E3 && i[33 - 1] <= 5 && i[33 - 1]>0)
	{
		i[33 - 1]--;
		miRot[4 - 1] = -1.3f* i[33 - 1] / 4;
		part5_miRot[4 - 1] = 0;
	}
	//F3
	if (ipress[40 - 1] == press_F3 && i[40 - 1] <= 4)
	{
		int x = i[40 - 1];
		faRot[4 - 1] = -1.3f* i[40 - 1] / 4;
		part5_faRot[4 - 1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[40 - 1]++;
		if (i[40 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 39);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[40 - 1] == ease_F3 && i[40 - 1] <= 5 && i[40 - 1]>0)
	{
		i[40 - 1]--;
		faRot[4 - 1] = -1.3f* i[40 - 1] / 4;
		part5_faRot[4 - 1] = 0;
	}
	//F3P
	if (ipress[47 - 1] == press_F3P && i[47 - 1] <= 4)
	{
		int x = i[47 - 1];
		plusRot[4 - 1][2] = -1.3f* i[47 - 1] / 4;
		part5_plusRot[4 - 1][2] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[47 - 1]++;
		if (i[47 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 46);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[47 - 1] == ease_F3P && i[47 - 1] <= 5 && i[47 - 1]>0)
	{
		i[47 - 1]--;
		plusRot[4 - 1][2] = -1.3f* i[47 - 1] / 4;
		part5_plusRot[4 - 1][2] = 0;
	}
	//G3
	if (ipress[54 - 1] == press_G3 && i[54 - 1] <= 4)
	{
		int x = i[54 - 1];
		soRot[4 - 1] = -1.3f* i[54 - 1] / 4;
		part5_soRot[4 - 1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[54 - 1]++;
		if (i[54 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 53);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[54 - 1] == ease_G3 && i[54 - 1] <= 5 && i[54 - 1]>0)
	{
		i[54 - 1]--;
		soRot[4 - 1] = -1.3f* i[54 - 1] / 4;
		part5_soRot[4 - 1] = 0;
	}
	//G3P
	if (ipress[61 - 1] == press_G3P && i[61 - 1] <= 4)
	{
		int x = i[61 - 1];
		plusRot[4 - 1][3] = -1.3f* i[61 - 1] / 4;
		part5_plusRot[4 - 1][3] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[61 - 1]++;
		if (i[61 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 60);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[61 - 1] == ease_G3P && i[61 - 1] <= 5 && i[61 - 1]>0)
	{
		i[61 - 1]--;
		plusRot[4 - 1][3] = -1.3f* i[61 - 1] / 4;
		part5_plusRot[4 - 1][3] = 0;
	}
	//A3
	if (ipress[69 - 1] == press_A3 && i[69 - 1] <= 4)
	{
		int x = i[69 - 1];
		laRot[4 - 1] = -1.3f* i[69 - 1] / 4;
		part5_laRot[4 - 1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[69 - 1]++;
		if (i[69 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 68);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[69 - 1] == ease_A3 && i[69 - 1] <= 5 && i[69 - 1]>0)
	{
		i[69 - 1]--;
		laRot[4 - 1] = -1.3f* i[69 - 1] / 4;
		part5_laRot[4 - 1] = 0;
	}
	//A3P
	if (ipress[77 - 1] == press_A3P && i[77 - 1] <= 4)
	{
		int x = i[77 - 1];
		plusRot[4 - 1][4] = -1.3f* i[77 - 1] / 4;
		part5_plusRot[4 - 1][4] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[77 - 1]++;
		if (i[77 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 76);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[77 - 1] == ease_A3P && i[77 - 1] <= 5 && i[77 - 1]>0)
	{
		i[77 - 1]--;
		plusRot[4 - 1][4] = -1.3f* i[77 - 1] / 4;
		part5_plusRot[4 - 1][4] = 0;
	}
	//B3
	if (ipress[85 - 1] == press_B3 && i[85 - 1] <= 4)
	{
		int x = i[85 - 1];
		siRot[4 - 1] = -1.3f* i[85 - 1] / 4;
		part5_siRot[4 - 1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[85 - 1]++;
		if (i[85 - 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 84);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[85 - 1] == ease_B3 && i[85 - 1] <= 5 && i[85 - 1]>0)
	{
		i[85 - 1]--;
		siRot[4 - 1] = -1.3f* i[85 - 1] / 4;
		part5_siRot[4 - 1] = 0;
	}
	/////////////////////////////////////////////////4
	//C4
	if (ipress[press_C4] == press_C4 && i[press_C4] <= 4)
	{
		int x = i[4];
		doRot[4] = -1.3f* i[press_C4] / 4;
		part5_doRot[4] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[press_C4]++;
		if (i[4] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 4);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[press_C4] == ease_C4 && i[press_C4] <= 5 && i[press_C4]>0)
	{
		i[press_C4]--;
		doRot[4] = -1.3f* i[press_C4] / 4;
		part5_doRot[4] = 0;
	}
	//C4P
	if (ipress[12] == press_C4P && i[12] <= 4)
	{
		int x = i[12];
		plusRot[4][0] = -1.3f* i[12] / 4;
		part5_plusRot[4][0] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[12]++;
		if (i[12] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 12);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[12] == ease_C4P && i[12] <= 5 && i[12]>0)
	{
		i[12]--;
		plusRot[4][0] = -1.3f* i[12] / 4;
		part5_plusRot[4][0] = 0;

	}
	//D4
	if (ipress[19] == press_D4 && i[19] <= 4)
	{
		int x = i[19];
		reRot[4] = -1.3f* i[19] / 4;
		part5_reRot[4] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[19]++;
		if (i[19] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 19);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[19] == ease_D4 && i[19] <= 5 && i[19]>0)
	{
		i[19]--;
		reRot[4] = -1.3f* i[19] / 4;
		part5_reRot[4] = 0;
	}
	//D4P
	if (ipress[26] == press_D4P && i[26] <= 4)
	{
		int x = i[26];
		plusRot[4][1] = -1.3f* i[26] / 4;
		part5_plusRot[4][1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[26]++;
		if (i[26] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 26);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[26] == ease_D4P && i[26] <= 5 && i[26]>0)
	{
		i[26]--;
		plusRot[4][1] = -1.3f* i[26] / 4;
		part5_plusRot[4][1] = 0;
	}
	//E4
	if (ipress[33] == press_E4 && i[33] <= 4)
	{
		int x = i[33];
		miRot[4] = -1.3f* i[33] / 4;
		part5_miRot[4] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[33]++;
		if (i[33] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 33);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[33] == ease_E4 && i[33] <= 5 && i[33]>0)
	{
		i[33]--;
		miRot[4] = -1.3f* i[33] / 4;
		part5_miRot[4] = 0;
	}
	//F4
	if (ipress[40] == press_F4 && i[40] <= 4)
	{
		int x = i[40];
		faRot[4] = -1.3f* i[40] / 4;
		part5_faRot[4] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[40]++;
		if (i[40] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 40);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[40] == ease_F4 && i[40] <= 5 && i[40]>0)
	{
		i[40]--;
		faRot[4] = -1.3f* i[40] / 4;
		part5_faRot[4] = 0;
	}
	//F4P
	if (ipress[47] == press_F4P && i[47] <= 4)
	{
		int x = i[47];
		plusRot[4][2] = -1.3f* i[47] / 4;
		part5_plusRot[4][2] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[47]++;
		if (i[47] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 47);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[47] == ease_F4P && i[47] <= 5 && i[47]>0)
	{
		i[47]--;
		plusRot[4][2] = -1.3f* i[47] / 4;
		part5_plusRot[4][2] = 0;
	}
	//G4
	if (ipress[54] == press_G4 && i[54] <= 4)
	{
		int x = i[54];
		soRot[4] = -1.3f* i[54] / 4;
		part5_soRot[4] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[54]++;
		if (i[54] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 54);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[54] == ease_G4 && i[54] <= 5 && i[54]>0)
	{
		i[54]--;
		soRot[4] = -1.3f* i[54] / 4;
		part5_soRot[4] = 0;
	}
	//G4P
	if (ipress[61] == press_G4P && i[61] <= 4)
	{
		int x = i[61];
		plusRot[4][3] = -1.3f* i[61] / 4;
		part5_plusRot[4][3] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[61]++;
		if (i[61] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 61);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[61] == ease_G4P && i[61] <= 5 && i[61]>0)
	{
		i[61]--;
		plusRot[4][3] = -1.3f* i[61] / 4;
		part5_plusRot[4][3] = 0;
	}
	//A4
	if (ipress[69] == press_A4 && i[69] <= 4)
	{
		int x = i[69];
		laRot[4] = -1.3f* i[69] / 4;
		part5_laRot[4] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[69]++;
		if (i[69] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 69);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[69] == ease_A4 && i[69] <= 5 && i[69]>0)
	{
		i[69]--;
		laRot[4] = -1.3f* i[69] / 4;
		part5_laRot[4] = 0;
	}
	//A4P
	if (ipress[77] == press_A4P && i[77] <= 4)
	{
		int x = i[77];
		plusRot[4][4] = -1.3f* i[77] / 4;
		part5_plusRot[4][4] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[77]++;
		if (i[77] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 77);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[77] == ease_A4P && i[77] <= 5 && i[77]>0)
	{
		i[77]--;
		plusRot[4][4] = -1.3f* i[77] / 4;
		part5_plusRot[4][4] = 0;
	}
	//B4
	if (ipress[85] == press_B4 && i[85] <= 4)
	{
		int x = i[85];
		siRot[4] = -1.3f* i[85] / 4;
		part5_siRot[4] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[85]++;
		if (i[85] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j , 85);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[85] == ease_B4 && i[85] <= 5 && i[85]>0)
	{
		i[85]--;
		siRot[4] = -1.3f* i[85] / 4;
		part5_siRot[4] = 0;
	}
	//////////////////////////////////////// 5
	//C5
	if (ipress[5] == press_C5 && i[5] <= 4)
	{
		int x = i[5];
		doRot[5] = -1.3f* i[5] / 4;
		part5_doRot[5] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[5]++;
		if (i[5] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 5);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[5] == ease_C5 && i[5] <= 5 && i[5]>0)
	{
		i[5]--;
		doRot[5] = -1.3f* i[5] / 4;
		part5_doRot[5] = 0;
	}
	//C5P
	if (ipress[13] == press_C5P && i[13] <= 4)
	{
		int x = i[13];
		plusRot[5][0] = -1.3f* i[13] / 4;
		part5_plusRot[5][0] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[13]++;
		if (i[13] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 13);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[13] == ease_C5P && i[13] <= 5 && i[13]>0)
	{
		i[13]--;
		plusRot[5][0] = -1.3f* i[13] / 4;
		part5_plusRot[5][0] = 0;

	}
	//D5
	if (ipress[20] == press_D5 && i[20] <= 4)
	{
		int x = i[20];
		reRot[5] = -1.3f* i[20] / 4;
		part5_reRot[5] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[20]++;
		if (i[20] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 20);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[20] == ease_D5 && i[20] <= 5 && i[20]>0)
	{
		i[20]--;
		reRot[5] = -1.3f* i[20] / 4;
		part5_reRot[5] = 0;
	}
	//D5P
	if (ipress[27] == press_D5P && i[27] <= 4)
	{
		int x = i[27];
		plusRot[5][1] = -1.3f* i[27] / 4;
		part5_plusRot[5][1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[27]++;
		if (i[27] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 27);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[27] == ease_D5P && i[27] <= 5 && i[27]>0)
	{
		i[27]--;
		plusRot[5][1] = -1.3f* i[27] / 4;
		part5_plusRot[5][1] = 0;
	}
	//E5
	if (ipress[34] == press_E5 && i[34] <= 4)
	{
		int x = i[34];
		miRot[5] = -1.3f* i[34] / 4;
		part5_miRot[5] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[34]++;
		if (i[34] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 34);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[34] == ease_E5 && i[34] <= 5 && i[34]>0)
	{
		i[34]--;
		miRot[5] = -1.3f* i[34] / 4;
		part5_miRot[5] = 0;
	}
	//F5
	if (ipress[41] == press_F5 && i[41] <= 4)
	{
		int x = i[41];
		faRot[5] = -1.3f* i[41] / 4;
		part5_faRot[5] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[41]++;
		if (i[41] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 41);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[41] == ease_F5 && i[41] <= 5 && i[41]>0)
	{
		i[41]--;
		faRot[5] = -1.3f* i[41] / 4;
		part5_faRot[5] = 0;
	}
	//F5P
	if (ipress[48] == press_F5P && i[48] <= 4)
	{
		int x = i[48];
		plusRot[5][2] = -1.3f* i[48] / 4;
		part5_plusRot[5][2] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[48]++;
		if (i[48] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 48);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[48] == ease_F5P && i[48] <= 5 && i[48]>0)
	{
		i[48]--;
		plusRot[5][2] = -1.3f* i[48] / 4;
		part5_plusRot[5][2] = 0;
	}
	//G5
	if (ipress[55] == press_G5 && i[55] <= 4)
	{
		int x = i[55];
		soRot[5] = -1.3f* i[55] / 4;
		part5_soRot[5] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[55]++;
		if (i[55] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 55);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[55] == ease_G5 && i[55] <= 5 && i[55]>0)
	{
		i[55]--;
		soRot[5] = -1.3f* i[55] / 4;
		part5_soRot[5] = 0;
	}
	//G5P
	if (ipress[62] == press_G5P && i[62] <= 4)
	{
		int x = i[62];
		plusRot[5][3] = -1.3f* i[62] / 4;
		part5_plusRot[5][3] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[62]++;
		if (i[62] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 62);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[62] == ease_G5P && i[62] <= 5 && i[62]>0)
	{
		i[62]--;
		plusRot[5][3] = -1.3f* i[62] / 4;
		part5_plusRot[5][3] = 0;
	}
	//A5
	if (ipress[70] == press_A5 && i[70] <= 4)
	{
		int x = i[70];
		laRot[5] = -1.3f* i[70] / 4;
		part5_laRot[5] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[70]++;
		if (i[70] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 70);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[70] == ease_A5 && i[70] <= 5 && i[70]>0)
	{
		i[70]--;
		laRot[5] = -1.3f* i[70] / 4;
		part5_laRot[5] = 0;
	}
	//A5P
	if (ipress[78] == press_A5P && i[78] <= 4)
	{
		int x = i[78];
		plusRot[5][4] = -1.3f* i[78] / 4;
		part5_plusRot[5][4] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[78]++;
		if (i[78] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 78);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[78] == ease_A5P && i[78] <= 5 && i[78]>0)
	{
		i[78]--;
		plusRot[5][4] = -1.3f* i[78] / 4;
		part5_plusRot[5][4] = 0;
	}
	//B5
	if (ipress[86] == press_B5 && i[86] <= 4)
	{
		int x = i[86];
		siRot[5] = -1.3f* i[86] / 4;
		part5_siRot[5] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[86]++;
		if (i[86] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 86);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[86] == ease_B5 && i[86] <= 5 && i[86]>0)
	{
		i[86]--;
		siRot[5] = -1.3f* i[86] / 4;
		part5_siRot[5] = 0;
	}
	//////////////////////////////////////////// 6
	//C6
	if (ipress[6] == press_C6 && i[6] <= 4)
	{
		int x = i[6];
		doRot[6] = -1.3f* i[6] / 4;
		part5_doRot[6] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[6]++;
		if (i[6] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 6);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[6] == ease_C6 && i[6] <= 5 && i[6]>0)
	{
		i[6]--;
		doRot[6] = -1.3f* i[6] / 4;
		part5_doRot[6] = 0;
	}
	//C6P
	if (ipress[13 + 1] == press_C6P && i[13 + 1] <= 4)
	{
		int x = i[13 + 1];
		plusRot[5 + 1][0] = -1.3f* i[13 + 1] / 4;
		part5_plusRot[5 + 1][0] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[13 + 1]++;
		if (i[13 + 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 14);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[13 + 1] == ease_C6P && i[13 + 1] <= 5 && i[13 + 1]>0)
	{
		i[13 + 1]--;
		plusRot[5 + 1][0] = -1.3f* i[13 + 1] / 4;
		part5_plusRot[5 + 1][0] = 0;

	}
	//D6
	if (ipress[20 + 1] == press_D6 && i[20 + 1] <= 4)
	{
		int x = i[20 + 1];
		reRot[5 + 1] = -1.3f* i[20 + 1] / 4;
		part5_reRot[5 + 1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[20 + 1]++;
		if (i[20 + 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 21);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[20 + 1] == ease_D6 && i[20 + 1] <= 5 && i[20 + 1]>0)
	{
		i[20 + 1]--;
		reRot[5 + 1] = -1.3f* i[20 + 1] / 4;
		part5_reRot[5 + 1] = 0;
	}
	//D6P
	if (ipress[27 + 1] == press_D6P && i[27 + 1] <= 4)
	{
		int x = i[27 + 1];
		plusRot[5 + 1][1] = -1.3f* i[27 + 1] / 4;
		part5_plusRot[5 + 1][1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[27 + 1]++;
		if (i[27 + 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 28);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[27 + 1] == ease_D6P && i[27 + 1] <= 5 && i[27 + 1]>0)
	{
		i[27 + 1]--;
		plusRot[5 + 1][1] = -1.3f* i[27 + 1] / 4;
		part5_plusRot[5 + 1][1] = 0;
	}
	//E6
	if (ipress[34 + 1] == press_E6 && i[34 + 1] <= 4)
	{
		int x = i[34 + 1];
		miRot[5 + 1] = -1.3f* i[34 + 1] / 4;
		part5_miRot[5 + 1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[34 + 1]++;
		if (i[34 + 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 35);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[34 + 1] == ease_E6 && i[34 + 1] <= 5 && i[34 + 1]>0)
	{
		i[34 + 1]--;
		miRot[5 + 1] = -1.3f* i[34 + 1] / 4;
		part5_miRot[5 + 1] = 0;
	}
	//F6
	if (ipress[41 + 1] == press_F6 && i[41 + 1] <= 4)
	{
		int x = i[41 + 1];
		faRot[5 + 1] = -1.3f* i[41 + 1] / 4;
		part5_faRot[5 + 1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[41 + 1]++;
		if (i[41 + 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 42);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[41 + 1] == ease_F6 && i[41 + 1] <= 5 && i[41 + 1]>0)
	{
		i[41 + 1]--;
		faRot[5 + 1] = -1.3f* i[41 + 1] / 4;
		part5_faRot[5 + 1] = 0;
	}
	//F6P
	if (ipress[48 + 1] == press_F6P && i[48 + 1] <= 4)
	{
		int x = i[48 + 1];
		plusRot[5 + 1][2] = -1.3f* i[48 + 1] / 4;
		part5_plusRot[5 + 1][2] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[48 + 1]++;
		if (i[48 + 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 49);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[48 + 1] == ease_F6P && i[48 + 1] <= 5 && i[48 + 1]>0)
	{
		i[48 + 1]--;
		plusRot[5 + 1][2] = -1.3f* i[48 + 1] / 4;
		part5_plusRot[5 + 1][2] = 0;
	}
	//G6
	if (ipress[55 + 1] == press_G6 && i[55 + 1] <= 4)
	{
		int x = i[55 + 1];
		soRot[5 + 1] = -1.3f* i[55 + 1] / 4;
		part5_soRot[5 + 1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[55 + 1]++;
		if (i[55 + 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 56);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[55 + 1] == ease_G6 && i[55 + 1] <= 5 && i[55 + 1]>0)
	{
		i[55 + 1]--;
		soRot[5 + 1] = -1.3f* i[55 + 1] / 4;
		part5_soRot[5 + 1] = 0;
	}
	//G6P
	if (ipress[62 + 1] == press_G6P && i[62 + 1] <= 4)
	{
		int x = i[62 + 1];
		plusRot[5 + 1][3] = -1.3f* i[62 + 1] / 4;
		part5_plusRot[5 + 1][3] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[62 + 1]++;
		if (i[62 + 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 63);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[62 + 1] == ease_G6P && i[62 + 1] <= 5 && i[62 + 1]>0)
	{
		i[62 + 1]--;
		plusRot[5 + 1][3] = -1.3f* i[62 + 1] / 4;
		part5_plusRot[5 + 1][3] = 0;
	}
	//A6
	if (ipress[70 + 1] == press_A6 && i[70 + 1] <= 4)
	{
		int x = i[70 + 1];
		laRot[5 + 1] = -1.3f* i[70 + 1] / 4;
		part5_laRot[5 + 1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[70 + 1]++;
		if (i[70 + 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 71);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[70 + 1] == ease_A6 && i[70 + 1] <= 5 && i[70 + 1]>0)
	{
		i[70 + 1]--;
		laRot[5 + 1] = -1.3f* i[70 + 1] / 4;
		part5_laRot[5 + 1] = 0;
	}
	//A6P
	if (ipress[78 + 1] == press_A6P && i[78 + 1] <= 4)
	{
		int x = i[78 + 1];
		plusRot[5 + 1][4] = -1.3f* i[78 + 1] / 4;
		part5_plusRot[5 + 1][4] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[78 + 1]++;
		if (i[78 + 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 79);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[78 + 1] == ease_A6P && i[78 + 1] <= 5 && i[78 + 1]>0)
	{
		i[78 + 1]--;
		plusRot[5 + 1][4] = -1.3f* i[78 + 1] / 4;
		part5_plusRot[5 + 1][4] = 0;
	}
	//B6
	if (ipress[86 + 1] == press_B6 && i[86 + 1] <= 4)
	{
		int x = i[86 + 1];
		siRot[5 + 1] = -1.3f* i[86 + 1] / 4;
		part5_siRot[5 + 1] = -(pow((x - 2.32), 3) - pow((x - 2.32), 2) + (-5)*(x - 2.32) + 6.5);
		i[86 + 1]++;
		if (i[86 + 1] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 87);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[86 + 1] == ease_B5 && i[86 + 1] <= 5 && i[86 + 1]>0)
	{
		i[86 + 1]--;
		siRot[5 + 1] = -1.3f* i[86 + 1] / 4;
		part5_siRot[5 + 1] = 0;
	}
	////////////////////////////////////////////7
	//C7
	if (ipress[7] == press_C7 && i[7] <= 4)
	{
		doRot[7] = -1.3f* i[7] / 4;
		part5_doRot[7] = -(8.0f * i[7] - 5.0f / 2 * pow(i[7], 2));
		i[7]++;
		if (i[7] == 1)
			for (int j = 0; j < 500; j++)
				if (pitch_count[j] == 0)
				{
			pitch[j] = new thread(play_sound, j, 7);//->detach; 
			pitch_count[j] = 1; break;
				}
	}
	if (ipress[7] == ease_C7 && i[7] <= 5 && i[7]>0)
	{
		i[7]--;
		doRot[7] = -1.3f* i[7] / 4;
		part5_doRot[7] = 0;
	}
}
void TimerFunc(int value)
{
	//刪掉動態空間	
	//Sleep(200);
	for (int j = 0; j < 500; j++)
	{
		if (pitch_count[j] == 1)
		{
			pitch[j]->join();
			pitch_count[j] = -1;
		}
		if (pitch_count[j] == -1)
		{
			//cout << pitch[j] << endl << j << endl;
			//delete pitch[j];
			pitch_count[j] = 0;
		}
	}

	play_time_function();
	//鋼琴解體
	if (ipiano_break_combine == piano_break)
	{
		if (tran_i[0] <= 30) //檔板
		{
			tran[0] = tran_i[0] * 10;
			tran_i[0]++;
		}
		else
			if (tran_i[1] >= -100)//鋼琴本體
			{
			tran[1] = tran_i[1] * 10;
			tran_i[1]--;
			}
	}
	if (ipiano_break_combine == piano_combine)
	{
		if (tran_i[1] < 0)//鋼琴本體
		{
			tran_i[1]++;
			tran[1] = tran_i[1] * 10;
		}
		else
			if (tran_i[0] > 0)//檔板
			{
			tran_i[0]--;
			tran[0] = tran_i[0] * 10;
			}
	}
	//
	playmusic();
	
	glutPostRedisplay();
	glutTimerFunc(10 , TimerFunc, 1);
}
void ShutdownRC(void)
{
	glDeleteTextures(9, textures);
}
int main(int argc, char* argv[])
{
	cout << "F1/F2：關閉/打開   琴蓋" << endl
		<< "F3/F4：分離/組合   鋼琴" << endl
		<< "F5/F6：顯示/不顯示 全部琴鍵" << endl
		<< "F7/F8：顯示/不顯示 鋼琴" << endl
		<< "F9/F10：放大/縮小  視角" << endl
		<< "Pagedown/Pageup：踩下/放開 延音踏板" << endl
		<< "方向鍵：旋轉視角" << endl
		<< "按鍵’asdfghj,zxcvbnm’：控制C4~B4跟C5~B5" << endl
		<< "右鍵選擇：" << endl
		<< "stop：停止自動彈奏" << endl
		<< "music1~3：選擇要自動彈奏的音樂" << endl;
	//繪出
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Piano");
	
	// Create the Menu
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("stop", 1);
	glutAddMenuEntry("music1", 2);
	glutAddMenuEntry("music2", 3);
	glutAddMenuEntry("music3", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);

	glutDisplayFunc(RenderScene);

	glutTimerFunc(10 , TimerFunc, 1);
	SetupRC();
	glutMainLoop();
	ShutdownRC();

	//
	for (int j = 0; j < 500; j++)
		if (pitch[j]->joinable())
			pitch[j]->join();
	//
	if (VBOv[0])
		delete[] VBOv[0];
	if (VBOn[0])
		delete[] VBOn[0];
	if (VBOv[1])
		delete[] VBOv[1];
	if (VBOn[1])
		delete[] VBOn[1];
	if (VBOv[2])
		delete[] VBOv[2];
	if (VBOn[2])
		delete[] VBOn[2];
	if (VBOv[3])
		delete[] VBOv[3];
	if (VBOn[3])
		delete[] VBOn[3];
	if (VBOv[4])
		delete[] VBOv[4];
	if (VBOn[4])
		delete[] VBOn[4];
	if (VBOv[5])
		delete[] VBOv[5];
	if (VBOn[5])
		delete[] VBOn[5];
	if (VBOv[6])
		delete[] VBOv[6];
	if (VBOn[6])
		delete[] VBOn[6];
	if (VBOv[7])
		delete[] VBOv[7];
	if (VBOn[7])
		delete[] VBOn[7];
	if (VBOv[8])
		delete[] VBOv[8];
	if (VBOn[8])
		delete[] VBOn[8];
	if (VBOv[9])
		delete[] VBOv[9];
	if (VBOn[9])
		delete[] VBOn[9];
	if (VBOv[10])
		delete[] VBOv[10];
	if (VBOn[10])
		delete[] VBOn[10];
	if (VBOv[11])
		delete[] VBOv[11];
	if (VBOn[11])
		delete[] VBOn[11];
	if (VBOv[12])
		delete[] VBOv[12];
	if (VBOn[12])
		delete[] VBOn[12];
	if (VBOv[13])
		delete[] VBOv[13];
	if (VBOn[13])
		delete[] VBOn[13];
	if (VBOv[14])
		delete[] VBOv[14];
	if (VBOn[14])
		delete[] VBOn[14];
	if (VBOv[15])
		delete[] VBOv[15];
	if (VBOn[15])
		delete[] VBOn[15];
	if (VBOv[16])
		delete[] VBOv[16];
	if (VBOn[16])
		delete[] VBOn[16];
	if (VBOv[17])
		delete[] VBOv[17];
	if (VBOn[17])
		delete[] VBOn[17];
	if (VBOv[18])
		delete[] VBOv[18];
	if (VBOn[18])
		delete[] VBOn[18];
	if (VBOv[19])
		delete[] VBOv[19];
	if (VBOn[19])
		delete[] VBOn[19];
	if (VBOv[20])
		delete[] VBOv[20];
	if (VBOn[20])
		delete[] VBOn[20];
	if (VBOv[21])
		delete[] VBOv[21];
	if (VBOn[21])
		delete[] VBOn[21]; 
	if (VBOv[22])
		delete[] VBOv[22];
	if (VBOn[22])
		delete[] VBOn[22];

	return 0;
}

