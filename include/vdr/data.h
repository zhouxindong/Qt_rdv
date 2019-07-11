#pragma once
#ifndef __SSA_VDR_DATA_H
#define __SSA_VDR_DATA_H

#include "export.h"
#include "../../include/base/base.h"
#include "bytebuffer.h"
#include "defs.h"

namespace ssa
{
#pragma pack(1)
	/**
	*  ��������������Ϣ��
	*/
	struct xmDataAttr
	{
	public:
		//���ݵ����ֲ��ܳ���16������
		//char            m_strName[xmENameLenth::xmENL_DATA];
		/**
		* �������͡�
		*/
		unsigned char   m_dtType = xmEDataType::xmDT_UNKNOWN;
		/**
		* ����������
		*/
		unsigned short  m_uRegion = 0;
		/**
		* �������ݼ���
		*/
		unsigned int    m_uDataSetID = 0;
		/**
		* ���ȣ�ͨ�������˫�����Ѿ����á�
		*/
		unsigned int    m_uSize = 8;
		/**
		* ��λʱ�䡣
		*/
		unsigned int    m_uResetTime = 0xFFFFFFFF;
		/**
		* �Ƿ���Թ���
		* ϵͳʹ�ã��û�ʹ��ʱ���ùܡ�
		*/
		bool            m_bShared = false;
		/**
		* ����ȫ��ID��
		* ϵͳʹ�ã��û�ʹ��ʱ���ùܡ�
		*/
		unsigned int    m_uGlobalID = 0;
		/**
		* �����ڲ�ʹ��ID��
		* ϵͳʹ�ã��û�ʹ��ʱ���ùܡ�
		*/
		unsigned int    m_uInnerID = 0;
		/**
		* �Ƿ�������Զ�������Դ��
		* ��Ҫ�ӷ�����������Դ���ǿͻ����ƶ���1��ʾ�Զ����䡣
		*/
		unsigned int    m_uAutoAlloc = 1;
	};
#pragma pack()

	class xmTypeSize
	{
	public:
		static unsigned int GetLength(xmEDataType et)
		{
			switch (et)
			{
				//  xmDT_UNKNOWN = 0,	/**< δ֪���� */
				//  xmDT_CHAR = 1,
				//	xmDT_INT8 = 1,	/**< 8λ���� */
				//	xmDT_UINT8,		/**< �޷���8Ϊ���� */
			case xmDT_INT8:
			case xmDT_UINT8:
				return sizeof(char);
				break;
				//	xmDT_INT16,		/**< 16λ���� */
				//	xmDT_UINT16,	/**< �޷���16λ���� */
			case xmDT_INT16:
			case xmDT_UINT16:
				return sizeof(short);
				break;
				//	xmDT_INT32,		/**< 32λ���� */
				//	xmDT_UINT32,	/**< �޷���32λ���� */
				//	xmDT_FLOAT,		/**< ������ */
			case xmDT_INT32:
			case xmDT_UINT32:
				return sizeof(__int32);
				break;
			case xmDT_FLOAT:
				return sizeof(float);
				break;
				//	xmDT_INT64,		/**< 64λ���� */
				//	xmDT_UINT64,	/**< �޷���64λ���� */
				//	xmDT_DOUBLE,	/**< ˫���ȸ����� */
			case xmDT_INT64:
			case xmDT_UINT64:
				return sizeof(__int64);
				break;
			case xmDT_DOUBLE:
				return sizeof(double);
				break;
				//	xmDT_STRING,	/**< ��0��β���ַ��� */
				//	xmDT_BUFFER,	/**< �ڴ������ */
				//					//		xmDT_BOOL,	
				//	xmDT_STRUCT,	/**< �ṹ���������� */
				//	xmDT_CLASS,	    /**< �ṹ���������� */
				//	xmDT_MAX		/**< �ṹ���������� */
			default:
				return 0;
				break;
			}
		}
	};

	/**
	*  ����������Ϣ��
	*  ����UDP���籨�ĳ���65535���ƣ���Ҫ�û���֤ÿ��data���л���Ĵ�СӦ����60k���ֽ����ڡ�
	*  �������ȷ���Ƿ񳬹�60k������ʹ�ú���EncodeSize�����жϡ�
	*/
	class xmVDR_EXPORT xmData
	{
	public:
		xmData(void);
		xmData(const char* name);
		xmData(const xmData& data);
		virtual ~xmData(void);

		/**
		* �Ⱥ����ء�
		*/
		void operator=(const xmData& b);
		/**
		* �����������ԡ�
		* @param strName �������֡�
		* @param eType �������͡�
		* @param uRegion ������
		* @param dataSetID �������ϡ�
		* @param nSize ���ȡ�
		* @param pInitBuf ��ʼֵ��������ַ��
		* @param uResetTime ��λʱ�䡣
		* @return Ϊ�ա�
		*/
		void SetAttr(const char* strName, xmEDataType eType, unsigned short uRegion, unsigned int dataSetID, unsigned int nSize , char* pInitBuf = 0, unsigned int uResetTime = 0xFFFFFFFF);
		/**
		* �����������ԡ�
		* @param strName �������֡�
		* @param eType �ṹ��Value�������͡�
		* @param uRegion ������
		* @param dataSetID �������ϡ�
		* @param uResetTime ��λʱ�䡣
		* @return Ϊ�ա�
		*/
		void SetAttr(const char* strName, const xmValue& eType, unsigned short uRegion, unsigned int dataSetID, unsigned int uResetTime = 0xFFFFFFFF);
		/**
		* �����������ԡ�
		* @param strName �������֡�
		* @param dAttr �������������ṹ��Ϣ��
		* @param pInitBuf ��ʼֵ��������ַ��
		* @return Ϊ�ա�
		*/
		void SetAttr(const char* strName, const xmDataAttr& dAttr, char* pInitBuf = 0);
		/**
		* �����������ԡ�
		* @param strName �������֡�
		* @param dAttr �������������ṹ��Ϣ��
		* @param eType �ṹ��Value�������͡�
		* @return Ϊ�ա�
		*/
		void SetAttr(const char* strName, const xmDataAttr& dAttr, const xmValue& eType);
		/**
		* �����������ԡ�
		* @param dAttr �������������ṹ��Ϣ��
		* @param pInitBuf ��ʼֵ��������ַ��
		* @return Ϊ�ա�
		*/
		void SetAttr(const xmDataAttr& dAttr, char* pInitBuf = 0);
		/**
		* �����������ԡ�
		* @param dAttr �������������ṹ��Ϣ��
		* @param eType �ṹ��Value�������͡�
		* @return Ϊ�ա�
		*/
		void SetAttr(const xmDataAttr& dAttr, const xmValue& eType);
		/**
		* �����������ԡ�
		* @param strName �������֡�
		* @return Ϊ�ա�
		*/
		void SetName(const char* strName);
		/**
		* ��ȡ����������Ϣ�����ĳ��ȡ�
		* @return ������Ϣ�����ĳ��ȡ�
		*/
		int  EncodeSize();

	public:
		/**
		* �������֡�
		* ��������ΪӦ���ṩһ�������Ƴ��ȵ����֡�
		*/
		std::string     m_strName;
		/**
		* ���ݻ������ԡ�
		*/
		xmDataAttr      m_Attr;
		/**
		* ��ʼֵ��
		*/
		xmByteBuffer    m_dynInitValue;
		/**
		* ������Ϣ��
		* ���������������ݵ���ϸ��Ϣ��Ŀǰ��Ҫ�������ݽṹ����Ϣ��������
		*/
		xmByteBuffer    m_dynDescribe;
		/**
		* ���ݵİ汾��
		* ���������и��µ�ʱ��ʹ�á�
		*/
		byte            m_nVersion;
	};
}

#endif