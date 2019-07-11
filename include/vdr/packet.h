#ifndef __SSA_VDR__PACKET_H
#define __SSA_VDR__PACKET_H
#pragma once

#include "export.h"
#include "../../include/base/base.h"
#include "../../include/base/socket.h"
#include "packetcodes.h"
#include "vdrattr.h"
#include "bytebuffer.h"

namespace ssa
{
	typedef enum __tagBuffType
	{
		xmEBT_NOTHING = 0,
		xmEBT_DATASET,		//	
		xmEBT_DATA,		//	
		xmEBT_MULTIDATA,    //	
		xmEBT_VALUE,	//
		xmEBT_SESSION,
		xmEBT_BULLETIN,
		xmEBT_LOG,
		xmEBT_MAX,
	} xmEBuffType;

	typedef enum __tagSendDirection
	{
		xmESD_OUT = 0,
		xmESD_IN,		 //	
	} xmESendDirection;

#pragma pack(1)
	//�������ʶ���ݵ�Դ��ַ��Ŀ���ַ
	union uAddr
	{
		sockaddr_in Sock;             //ʹ�������ַ��ʶ
		int         No;               //ʹ�����кű�ʶ
		char        Name[14]/* = { 0 }*/; //ʹ�����ֱ�ʶ
	};

	struct xmHead
	{
	public:
		//VDR���к�
		unsigned short   m_uVDRID  = 0x6B42;
		//������
		unsigned short   m_uRegion;
		//���ݰ�����
		unsigned short   m_uPackCode = xmEPackCodes::xmPACK_NOTHING;
		//�ظ�����
		unsigned short   m_eRspCode;
		//������������ͻ��˻���˫���
		unsigned char    m_ePackTarget = xmEEndpointType::xmEET_SERVER;
		//ʱ���
		long long        m_lTimeStamp;
		//�Ƿ���Ҫʹ��ID��Ϊ�˵����ĻỰ�����Ƕಥ��
		//��Ҫ���ڿ��������Ƿ�ֻ�з����ߴ�����1��ʾֻ�з����ߴ�����0��ʾ�������ն˴���
		unsigned char    m_bUseFlowSeq;
		//��������Ҫ�����������򣬻�����Ҫ���Ƶȴ�ʱ���ʱ��ʹ��
		unsigned int     m_uFlowSeq;
		//ʹ���Ǹ��Ự������
		unsigned short   m_uSessionID;      // = xmESessionType::xmEST_LOGIN;
		//�����ⷢ�ͣ�����������Ϣ����
		unsigned char    m_sendDir = xmESendDirection::xmESD_OUT;
		//���ݰ����ȣ���������ͷ�ĳ���
		unsigned int     m_uLength;
		//��������,xmEBT_DATASET,xmEBT_DATA,xmEBT_MULTIDATA,xmEBT_VALUE,xmEBT_SESSION,xmEBT_BULLETIN,xmEBT_LOG,xmEBT_MAX
		unsigned char    m_btType;
		//��Դ
		uAddr            m_srcAddr;
		//Ŀ��
		uAddr            m_disAddr;
		//���Ǹ��汾����Ϣ������������ͬ�����汾
		unsigned short   m_nVersion;
	};
#pragma pack ()  

	class xmPacket
	{
	public:
		xmPacket() {};
		xmPacket(const xmPacket& pkt) 
		{
			m_pktHead = pkt.m_pktHead;
			m_dynBuf = pkt.m_dynBuf;
		};

		virtual ~xmPacket();

		virtual void  Destroy();

		//�����ݰ�д������
		virtual void  WriteData(unsigned char* in, unsigned int nSize) {};
		//�ӽ����ݴ��Ϊ�������ݱ���
		virtual unsigned int   Encode(unsigned char* out) = 0;
		//�����ݱ����н�������
		virtual void  Decode(unsigned char* in, unsigned int nSize)= 0;

	public:
		xmHead           m_pktHead;
		xmByteBuffer     m_dynBuf;
	};

};

#endif