#include "PeInfo.hpp"
#ifndef _PEINFO32_H
#define _PEINFO32_H
/*
	peinfo32 v0.1
	coded by devseed
*/
#define PE32HBUF_SIZE 0X500 //PE32ͷ��󳤶�
typedef struct _INDEX_PE32	//PE��Ϣ������
{
	PDWORD					pdwImageSize;		//�����С
	PWORD					pwSectionNum;		//��������
	PDWORD					pdwHeaderSize;	//�ļ�ͷ��С
	PDWORD					pdwFileAlign;		//�ļ�����
	PDWORD					pdwMemAlign;		//�ڴ����
	PDWORD					pdwImageBase;		//�����ַ
		
	PDWORD					pdwCodeBaseRva;	//�����ַ
	PDWORD					pdwCodeSize;		//�����С
	PDWORD					pdwOepRva;			//OEP��ַ(rva)
	PDWORD					pdwIatBaseRva;		//IAT���ڶλ�ַ
	PDWORD					pdwIatSize;		//IAT���ڶδ�С
		
	PIMAGE_NT_HEADERS			pNtHeader;			//NTͷ
	PIMAGE_DATA_DIRECTORY		pDataDir;		        //����Ŀ¼
	PIMAGE_SECTION_HEADER		pSectionHeader;		//��һ��SECTION�ṹ��ָ��
	PIMAGE_EXPORT_DIRECTORY		pExportDir;		    //���������Ϣ
	PIMAGE_IMPORT_DESCRIPTOR	pImportDir;			//�������Ϣ
	PIMAGE_RESOURCE_DIRECTORY   pResourceDir;		    //��ԴĿ¼
	PIMAGE_BASE_RELOCATION		pRelocDir;			//�ض�λ����Ϣ
	PIMAGE_TLS_DIRECTORY32      pTlsDir;				//tls��Ϣ
	//��ʱ���룬.netʲô����ʱ������
}INDEX_PE32,*PINDEX_PE32;

class CPEinfo32:public CPEinfo//��¼pe��Ϣ����
{

	public:	
		//��̬�����������麯�����������ﲻ���ڻ�������
		static DWORD getPeMemSize(char *path);
		static DWORD getPeMemSize(LPBYTE pFileBuf);
		static DWORD getOverlaySize(char *path);
		static DWORD readOverlay(char *path,LPBYTE pOverlay);
		static DWORD addOverlay(char *path,LPBYTE pOverlay,DWORD size);
		static DWORD loadPeFile(char *path,
							LPBYTE pFileBuf,DWORD *FileBufSize,
							bool isMemAlign=false,
							LPBYTE pOverlayBuf=NULL,DWORD *OverlayBufSize=0);//ʧ�ܷ���0���ɹ����ض�ȡ���ֽ���
		static DWORD savePeFile(char *path,
							LPBYTE pFileBuf,DWORD FileBufSize,
							 bool isMemAlign=false,
							LPBYTE pOverlayBuf=NULL,DWORD OverlayBufSize=0);//ʧ�ܷ���0���ɹ�����д�����ֽ���
		static int getPeIndex(LPBYTE pFileBuf,PINDEX_PE32 peindex,bool isMemAlign=false);//����isPe��ֵ
		static int getPeIndex(char *path,PINDEX_PE32 peindex,bool isMemAlign=false);
		
		//������PE��Ϣ�Ĵ���
		static DWORD getOepRva(LPBYTE pFileBuf);//����Rva
		static DWORD setOepRva(LPBYTE pFileBuf,DWORD rva);//����ԭ����rva
		static DWORD rva2faddr(LPBYTE pFileBuf,DWORD rva);
		static DWORD faddr2rva(LPBYTE pFileBuf,DWORD faddr);
		static DWORD va2rva(LPBYTE pFileBuf,DWORD va);
		static DWORD rva2va(LPBYTE pFileBuf,DWORD rva);
		static DWORD faddr2va(LPBYTE pFileBuf,DWORD faddr);
		static DWORD va2faddr(LPBYTE pFileBuf,DWORD va);
		
		//�ļ���PE��Ϣ����	
		static DWORD getOepRva(char *path);
		static DWORD setOepRva(char *path,DWORD rva);
		static DWORD rva2faddr(char *path,DWORD rva);//rva��file offsetת������Ч����0
		static DWORD faddr2rva(char *path,DWORD faddr);
		static DWORD va2rva(char *path,DWORD va);
		static DWORD rva2va(char *path,DWORD rva);
		static DWORD faddr2va(char *path,DWORD faddr);
		static DWORD va2faddr(char *path,DWORD va);

	public:
		INDEX_PE32 m_pe32Index;

	public:
		//���캯�������������
		CPEinfo32();
		CPEinfo32(char *path,bool isMemAlign=true);
		CPEinfo32(LPBYTE pFileBuf,DWORD filesize,bool isCopyMem=false,bool isMemAlign=true);
		void copy(const CPEinfo32 &pe32,bool isCopyMem=true);//Ĭ�Ͽ�������
		CPEinfo32(const CPEinfo32 &pe32);
		CPEinfo32 &operator=(CPEinfo32 &pe32);
		
		//PE�ļ����������������������ĵ��û���ģ�
		DWORD openPeFile(char *path,bool isMemAlign=true);		//��pe�ļ���isMemAlign=1���ڴ淽ʽ����
		int attachPeBuf(LPBYTE pFileBuf,DWORD dwFileBufSize,
						bool isCopyMem=true,bool isMemAlign=true,
						LPBYTE pOverlayBuf=NULL,DWORD dwOverLayBufSize=0);//�����ⲿ��pe����
		DWORD savePeFile(char *path);								//���滺����pe�ļ�
		void iniValue();								//������������ֵ
		int isPe() ;										//�ж��ļ��Ƿ�Ϊ��Чpe�ļ�(-1��dos,-2��pe,010b:32exe,020b:64exe)
		int getPeIndex() ;								//���pe�ļ���Ϣ����
		DWORD getOepRva();
		DWORD setOepRva(DWORD rva);
		

		//��ַת��
		DWORD rva2faddr(DWORD rva) const;
		DWORD faddr2rva(DWORD faddr) const;
		DWORD va2rva(DWORD va) const;
		DWORD rva2va(DWORD rva) const;
		DWORD faddr2va(DWORD faddr) const;
		DWORD va2faddr(DWORD va) const;
};
#endif