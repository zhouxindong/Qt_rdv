#pragma once
#ifndef __SSA_VDR_ISERVICE_H
#define __SSA_VDR_ISERVICE_H

//#include "icommproxy.h"

namespace ssa
{
	class xmICommProxy;
	class xmISyncProxy;
	class xmVDR_EXPORT xmIService
	{
	public:
		xmIService() {};
		virtual ~xmIService() {};
		virtual void               SetCommProxy(xmICommProxy* pCommProxy) = 0;
		virtual xmICommProxy*      GetCommProxy() { return 0; };
		virtual void               SetSyncProxy(xmISyncProxy* pSyncProxy) {};
		virtual xmISyncProxy*      GetSyncProxy() { return 0; };

		virtual xmVDRAttr*         GetVDRAttr() = 0;
		//�����Ƿ��������ͨ������
		virtual bool               IsCommOK() = 0;
		//�ж��Ƿ��ʼ�����
		virtual bool               IsValid() = 0;
		//�����Ự
		virtual void               CreateSessionGroup(std::string strName) = 0;
		virtual void               CreateGlobalSingleSessions() = 0;
		//ֹͣ�Ự
		virtual void               StopSessions(bool isDel = false) = 0;
		//�رշ�����Դ
		virtual void               Close() = 0;

		//�����ݰ��ַ�����
		virtual int                Dispatch(const char* pBuf, int nLen) = 0;
		//ֻ�ڸտ�ʼ�����Ựʱʹ�á�
		virtual int                DispatchWithWaitTime(const xmPacket& pkt, xmByteBuffer& wParam, int waitTime = 0) = 0;
		virtual int                DispatchWithoutWaitTime(const xmPacket& pkt) = 0;

		virtual void               BeginSync() {};
		virtual void               DoSync() {};
		virtual void               EndSync() {};

		virtual long long          GetTimeStamp() = 0;
	};
}

#endif