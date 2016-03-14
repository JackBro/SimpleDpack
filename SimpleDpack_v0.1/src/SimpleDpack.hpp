#include <Windows.h>
#include "PeInfo.hpp"
extern "C" // c++������c����Ҫ����
{
#include "dpackType.h"
#include "dpackCode.h"
#include "dunpackCode.h"
}
#ifndef _SIMPLEDPACK_H
#define _SIMPLEDPACK_H
/*
	pack the pe file class
*/
class CSimpleDpack
{
	private:
		char m_strFilePath[MAX_PATH];
	protected:
		DWORD dlzmaPack(LPBYTE *dst,LPBYTE src,DWORD lzmasize,double maxmul=2.0);
	public:
		CSimpleDpack()
		{
			iniValue();
		}
		virtual ~CSimpleDpack(){}
		void iniValue();
		virtual	void release()=0;
		virtual DWORD loadPeFile(char *path)=0;//����pe�ļ�������isPE()ֵ
		virtual DWORD packPe(int type,char *dllpath)=0;//�ӿǣ�ʧ�ܷ���0���ɹ�����pack���ݴ�С
		virtual DWORD unpackPe(int type=0)=0;//�ѿǣ�����ͬ�ϣ���ʱ��ʵ�֣�
		virtual DWORD savePe(char *path)=0;//ʧ�ܷ���0���ɹ������ļ���С
		const char *getFilePath() const;
};
#endif