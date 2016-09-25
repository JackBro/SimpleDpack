#include <Windows.h>
#ifndef _PEINFO_H
#define _PEINFO_H
/*
	peinfo v0.1
	coded by devseed
	the base class
	in order to adapter other os I won't us system api directly too much(excet loadlibrary)
*/
typedef struct _RELOCOFFSET
{
	WORD offset : 12;			//ƫ��ֵ
	WORD type	: 4;			//�ض�λ����(��ʽ)
}RELOCOFFSET,*PRELOCOFFSET;
class CPEinfo
{
	public:
		//�ļ�����
		static DWORD getFileSize(char *path);
		static DWORD readFile(char *path,LPBYTE pFileBuf,DWORD size=0);//��ͷ���ļ���sizeΪҪ������(0��ȡȫ��)�����ض�ȡ�ֽ������ŵ�pFileBuf��
		static int isPe(LPBYTE  pFileBuf);
		static int isPe(char *path);
		static DWORD toAlignment(DWORD num,DWORD align);

	protected:
		//����exe�ļ�������4g
		bool m_isMemAlign;//�����pe�ļ��Ƿ�Ϊ�ڴ���룬��ʱֻд�ڴ����ɡ���
		bool m_isMemAlloc;//�Ƿ��ڴ�Ϊ�˴������
		char					m_strFilePath[MAX_PATH]; //PE�ļ�·��
		LPBYTE					m_pFileBuf;			//PE�ļ�������
		DWORD					m_dwFileBufSize;	//PE�ļ���������С
		LPBYTE					m_pOverlayBuf;		//PE�������ݻ���������memalign�����·��䣬����ָ����Ӧλ�ã�û��ΪNULL
		DWORD					m_dwOverlayBufSize;	//PE�������ݴ�С
		
	public:
		CPEinfo()
		{
			iniValue();
		}
		virtual ~CPEinfo()
		{
			closePeFile();
			releaseFileBuf();
		}
		CPEinfo(const CPEinfo &pe32);
		//PE�ļ���������(�麯��)
		virtual DWORD openPeFile(char *path,bool isMemAlign=true)=0;		//��pe�ļ���isMemAlign=1���ڴ淽ʽ����
		virtual DWORD savePeFile(char *path)=0;								//���滺����pe�ļ�
		virtual int isPe()=0;								//�ж��ļ��Ƿ�Ϊ��Чpe�ļ�(-1��dos,-2��pe,010b:32exe,020b:64exe)
		virtual int getPeIndex()=0;								//���pe�ļ���Ϣ����

		
		virtual void iniValue();						//������������ֵ
		virtual int attachPeBuf(LPBYTE pFileBuf,DWORD dwFileBufSize,
						bool isCopyMem=true,bool isMemAlign=true,
						LPBYTE pOverlayBuf=NULL,DWORD dwOverLayBufSize=0);//�����ⲿ��pe����
		virtual int closePeFile();								//�ر�pe�ļ�
		virtual int releaseFileBuf();							//�ͷ��ļ��Ļ�����
		virtual int releaseOverlayBuf();						//�ͷ�overlay���ֻ�����
		virtual int releaseAllBuf();							//�ͷ�ȫ��������

		
		//��ȡ��˽�б���
		bool isMemAlign() const;								//true�ڴ���룬false�ļ�����
		bool isMemAlloc() const;								//�ڴ��Ƿ�Ϊnew������
		const char* const getFilePath() const;
		LPBYTE getFileBuf() const;
		DWORD getFileBufSize() const;
		LPBYTE getOverlayBuf() const;
		DWORD getOverlayBufSize() const;
};
#endif