#include <string.h>
#include "capstone-3.0.4-win32\capstone.h"
#include "lzma\lzmalib.h"
#include "PeInfo32.hpp"
#include "DpackType.h"
#include "SimpleDpack.hpp"
#ifndef _SIMPLEDPACK32_H
#define _SIMPLEDPACK32_H
/*
	simpledpack packer for win32 exe
	determine that the data on memery unchanged
*/
typedef struct _DPACKSECT_INDEX32
{
	LPBYTE packBuf;
	DWORD  packBufSize;
	DWORD  srcRva;//������Ϊ0������ӵ����һ������
	DWORD  srcMemSize;
}DPACKSECT_INDEX32,*PDPACKSECT_INDEX32;
class CSimpleDpack32 :public CSimpleDpack
{
	protected:
		CPEinfo32 m_pe32;
		CPEinfo32 m_shellpe32;
		PDPACK_HDADER32 m_gShellHeader32;
		DWORD m_hShell;
		
		WORD m_dpackSectNum;
		DPACKSECT_INDEX32 m_dpackIndex[MAX_DPACKSECTNUM];
		
		WORD iniDpackIndex();//����ԭ��dpackIndex����
		WORD addDpackIndex(LPBYTE packBuf,DWORD packBufSize,DWORD srcRva=0,DWORD srcMemSize=0);//����dpack����
		DWORD sectProc(int type);	//���������
		DWORD shelldllProc(int type,char *dllpath);	//�������
		DWORD setShellReloc(LPBYTE pShellBuf, DWORD hShell,DWORD shellBaseRva);//����dll�ض�λ��Ϣ�����ظ���
		DWORD setShellIat(LPBYTE pShellBuf, DWORD hShell,DWORD shellBaseRva);//������ƫ����ɵ�dll iat����
	public:
		CSimpleDpack32()
		{
			iniValue();
		}
		CSimpleDpack32(char *path);
		~CSimpleDpack32()
		{
			release();
		}
		void iniValue();
		void release();
		
		DWORD loadPeFile(char *path);//����pe�ļ�������openPE()ֵ
		DWORD packPe(int type=0,char *dllpath="simpledpackshell32.dll");//�ӿǣ�ʧ�ܷ���0���ɹ�����pack���ݴ�С
		DWORD unpackPe(int type=0);//�ѿǣ�����ͬ�ϣ���ʱ��ʵ�֣�
		DWORD savePe(char *path);//ʧ�ܷ���0���ɹ������ļ���С
		CPEinfo32* getPe();
};

#endif