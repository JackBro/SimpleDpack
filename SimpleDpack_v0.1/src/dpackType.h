#include <Windows.h>
#include "lzma\lzmalib.h"
/*
	dpack types and structures
*/
#ifndef _DPACKTYPE_H
#define _DPACKTYPE_H
#define MAX_DPACKSECTNUM 16//����pack��������
typedef struct _DLZMA_HEADER
{
	DWORD dwRawDataSize;//ԭʼ���ݳߴ�(������ͷ)
	DWORD dwDataSize;//ѹ��������ݴ�С
	char outProps[LZMA_PROPS_SIZE];//ԭʼlzma���ļ�ͷ
}DLZMA_HEADER,*PDLZMA_HEADER;//�˴���Χ���������dpack��lzmaͷ

typedef struct _ORIGION_INDEX32   //Դ������ȥ����Ϣ���˽ṹΪ���ı�ʾ����ַȫ��rva
{
	DWORD dwImageBase;			//Դ�����ַ
	DWORD dwOepRva;				//ԭ����rva���
	DWORD dwExportRva;		    //���������Ϣ
	DWORD dwExportSize;
	DWORD dwImportRva;			//�������Ϣ
	DWORD dwImportSize;
	DWORD dwResourceRva;		//��ԴĿ¼
	DWORD dwResourceSize;
	DWORD dwRelocRva;			//�ض�λ����Ϣ
	DWORD dwRelocSize;
	DWORD dwTlsRva;			//tls��Ϣ
	DWORD dwTlsSize;
}ORIGION_INDEX32,*PORIGION_INDEX32;

typedef struct _TRANS_INDEX //Դ��Ϣ��任����Ϣ��������
{
	//���費����4g
	DWORD dwOrigion_rva;
	DWORD dwOrigion_size;
	DWORD dwTrans_rva;
	DWORD dwTrans_size;
}TRANS_INDEX,*PTRANS_INDEX;

typedef struct _DPACK_DETAIL32//DPACK�任��ϸ��Ϣ
{
	PVOID extre;
}DPACK_DETAIL32,*PDPACK_DETAIL32;

typedef struct _DPACK_OUT32//dll�������Ϣ
{
	PVOID extre;
}DPACK_OUT32,*PDPACK_OUT32;

typedef struct _DPACK_HDADER32//DPACK�任ͷ
{
	DWORD dpackOepVa;								//�ǵ���ڣ��ŵ�һ��Ԫ�ط����ʼ����
	ORIGION_INDEX32 origin_index;					//ԭʼpe��һЩ��Ϣ
	WORD trans_num;									//�任�������������MAX_DPACKSECTNUM����
	TRANS_INDEX trans_index[MAX_DPACKSECTNUM];		//�任��������
	DPACK_DETAIL32 detail;							//pack����ϸ��Ϣ
	DPACK_OUT32 out;								//��������dll��һЩ��Ϣ
	PVOID extre;									//������Ϣ������֮����չ
}DPACK_HDADER32,*PDPACK_HDADER32;
#endif