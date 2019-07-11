#ifndef __SSA_VDR_SERVICE_H
#define __SSA_VDR_SERVICE_H

#include "datacenter.h"
#include "sessioncenter.h"
#include "sensmsghandler.h"
#include "logiclayer.h"
#include "iservice.h"
#include "isyncproxy.h"
#include "defs.h"

namespace ssa
{
	class xmService : public xmIService
	{
	public:
		xmService();

		void               SetCommProxy(xmICommProxy* pCommProxy) { m_pCommProxy = pCommProxy; };
		xmICommProxy*      GetCommProxy() { return m_pCommProxy; };
		xmVDRAttr*         GetVDRAttr();
		//�����Ƿ��������ͨ������
		bool               IsCommOK();
		//�ж��Ƿ��ʼ�����
		bool               IsValid();
		//ֹͣ����
		void               StopSessions(bool isDel = false);
		//�رշ�����Դ
		void               Close();

		//Ѱ�����������µ�VDRID��
		int                AskNewestID();

		int                AddNode(const xmNode& nd);
		int                RemoveNode(const std::string& strNodeName);
		int                AddDataSet(const xmDataSet& ds);
		int                RemoveDataSet(const std::string& strName);
		//��Node�����ݼ���������
		int                Link(const std::string& strNodeName, const std::string& strDataSetName);
		//��Node�����ݼ��Ͽ�
		int                UnLink(const std::string& strNodeName, const std::string& strDataSetName);
		int                AddData(const xmData& data);
		int                RemoveData(const std::string& strName);

		//�ӷ�������ȡ�ж������ݼ�
		int                FetchDataSetInfo();

		//�������ݼ�����ͬ������
		int                FetchDataInfo(const std::string& strDataSetName = "");
		//ͬ�����ݽṹ��Ϣ
		int                FetchStructInfo();

		//�����Ҫ���������½��ڴ��ʱ��ʹuIsLocal=0�����ֻ�ǽ��������ڴ�ʹ��uIsLocal=1��
		int                BuildMemory(const std::string& strDataSetName, unsigned char uIsLocal = 1);
		//����ʱ���źţ��������Ϊͬ������
		int                TickSignal(int nTickTime, int nSyncCycles);

		//��ϵͳ״̬���й���
		int                SwitchSystemState(xmESystemState es);
		//�ڲ������ڴ�֮��ͬ��
		bool               SyncMemory(const char* strDataSet);

		//�ֶ�ͬ�������źţ����������һ������Ҫ�ϴ��µ����ݣ�ͬʱ��ȡ�µ��ڴ����ݣ�һ�����������ȡ�������˵����ݡ�
	    int                SyncContent(const std::string& strDataSetName, xmESyncDirection am , bool bUseRTE);
		int                Paste2Bulletin(const char* strSender, const char* strTopic, const char* pBuf, unsigned int uLength);
		int                MCast2Nodes(const char* strFromNode, const std::vector<std::string>& vToNodeName, const char* pBuf, unsigned int uLength);
		//�����ݰ��ַ�����
		int                Dispatch(const char* pBuf, int nLen);
		//ֻ�ڸտ�ʼ�����Ựʱʹ�á�
		int                DispatchWithWaitTime(const xmPacket& pkt, xmByteBuffer& wParam, int waitTime = 0);
		int                DispatchWithoutWaitTime(const xmPacket& pkt);

		void               CreateSessionGroup(std::string strName);
		void               CreateGlobalSingleSessions();
		xmSessionCenter*   GetSessionCenter() { return &m_SessionCenter; };
		xmSensMSGHandler*  GetSensMSGHandler() { return &m_SensMSGHandler; };
		xmDataCenter*      GetDataCenter() { return &m_DataCenter; };

		bool               IsCurrentAttachedValid(std::string strCurrentAttachedName);
		bool               IsAttached(const std::string& strDataSetName);
		void               AddAttached(const xmDataSet& ds);
		void               RemoveAttached(const std::string& strDataSetName);
		void               ClearAttached();
		std::map<std::string, xmDataSet>&      GetAttchedDataSet();


		bool               IsAuthorized(const std::string& ndName);
		void               AddAuthorized(const xmNode& nd);
		void               RemoveAuthorized(const std::string& ndName);
		void               ClearAuthorized();
		std::map<std::string, xmNode>&         GetAuthorizedNode();

		void               SetWaitTime(long nTime = xmMAX_WAITING_TIME);
		long               GetWaitTime();

		xmLogicLayer*      GetLogicLayer() { return &m_LogicLayer; };
		void               SetSyncProxy(xmISyncProxy* pSyncProxy);
		xmISyncProxy*      GetSyncProxy() { return m_pSyncProxy; };

		void               BeginSync();
		void               DoSync();
		void               EndSync();

		long long          GetTimeStamp() {return m_lTimeStamp;};

	public:
		typedef enum __tagServiceState
		{
			xmESS_NOTHING = 0,
			xmESS_STARTING,		//	
			xmESS_MAX,
		} xmEServiceState;
		//�����жϷ��������Ƿ������µ�ID����
		bool               m_isGetNewestID;
		//ϵͳ��״̬
		xmESystemState     m_eSystemState;

		long long          m_lTimeStamp;

	private:
		void               CreateSingleSession(int nSessionID);
		xmSession *        GetSession(int nSessionID, std::string strName, bool bUseMultiSessions);
		int                Post2MSGQ(const xmPacket& pkt);

	private:
		//���ڱ�֤ds��ʼ�����̵�״̬�����ʹ��״̬����
		xmEServiceState    m_State;
		//�����ǰ��������ָ�����Ǹ����ݼ��Ͻ��в���
		std::map<std::string, xmDataSet>      m_mapAttchedDataSet;
		std::map<std::string, xmNode>         m_mapAuthorizedNode;

		xmDataCenter       m_DataCenter;
		xmSessionCenter    m_SessionCenter;
		xmLogicLayer       m_LogicLayer;
		xmSensMSGHandler   m_SensMSGHandler;

		typedef std::map<int, xmSession*>  SessionRegistry;
		SessionRegistry    m_SessionRegistry;
		xmICommProxy*      m_pCommProxy;
		xmISyncProxy*      m_pSyncProxy;

		xmMutex            m_LocalMutex;
		xmMutex            m_GlobalMutex;
		xmMutex            m_LogMutex;
		xmMutex            m_SyncMutex;

		long               m_nWaitTime;
	};
}

#endif