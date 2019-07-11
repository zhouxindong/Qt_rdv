#ifndef __SSA_VDR_ICOMMPROXY_H
#define __SSA_VDR_ICOMMPROXY_H
#include "export.h"
#include "packet.h"
#include "vdrattr.h"
#include "iservice.h"
#include "iproxy.h"

namespace ssa
{
	class xmVDR_EXPORT xmICommProxy : public xmIProxy
	{
	public:
		xmICommProxy() :m_pService(0) {};
		virtual ~xmICommProxy(){};

		virtual bool                Initialize(void*) = 0;
		virtual xmVDRAttr*          GetVDRAttr() =0;
		virtual xmEVDRCommProxyType GetCommProxyType()= 0;
		virtual int                 GetProxyID() { return GetCommProxyType(); };
		virtual bool                Close() = 0;
		//�������������
		virtual int                 Start() = 0;
		//���ͱ�����VDR����
		virtual bool                Send(const xmPacket& pkt)  = 0;
		virtual void                SetService(xmIService* pService);
		virtual xmIService*         GetService();
		//�յ����ģ����зַ�����
		virtual int                 Recv(char* buf, int nLen);

	private:
		xmIService*                 m_pService;
	};
}

#endif //__SSA_VDR_ICOMMPROXY_H