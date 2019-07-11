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
		//测试是否与服务器通信正常
		bool               IsCommOK();
		//判断是否初始化完毕
		bool               IsValid();
		//停止服务
		void               StopSessions(bool isDel = false);
		//关闭服务资源
		void               Close();

		//寻找区域内最新的VDRID号
		int                AskNewestID();

		int                AddNode(const xmNode& nd);
		int                RemoveNode(const std::string& strNodeName);
		int                AddDataSet(const xmDataSet& ds);
		int                RemoveDataSet(const std::string& strName);
		//将Node和数据集连接起来
		int                Link(const std::string& strNodeName, const std::string& strDataSetName);
		//将Node和数据集断开
		int                UnLink(const std::string& strNodeName, const std::string& strDataSetName);
		int                AddData(const xmData& data);
		int                RemoveData(const std::string& strName);

		//从服务器获取有多少数据集
		int                FetchDataSetInfo();

		//按照数据集名字同步数据
		int                FetchDataInfo(const std::string& strDataSetName = "");
		//同步数据结构信息
		int                FetchStructInfo();

		//如果需要服务器端新建内存的时候使uIsLocal=0，如果只是建立本地内存使用uIsLocal=1；
		int                BuildMemory(const std::string& strDataSetName, unsigned char uIsLocal = 1);
		//发起时间信号，输入参数为同步周期
		int                TickSignal(int nTickTime, int nSyncCycles);

		//对系统状态进行管理
		int                SwitchSystemState(xmESystemState es);
		//内部两个内存之间同步
		bool               SyncMemory(const char* strDataSet);

		//手动同步触发信号，两种情况，一种是需要上传新的数据，同时获取新的内存数据，一种情况仅仅获取服务器端的数据。
	    int                SyncContent(const std::string& strDataSetName, xmESyncDirection am , bool bUseRTE);
		int                Paste2Bulletin(const char* strSender, const char* strTopic, const char* pBuf, unsigned int uLength);
		int                MCast2Nodes(const char* strFromNode, const std::vector<std::string>& vToNodeName, const char* pBuf, unsigned int uLength);
		//将数据包分发处理
		int                Dispatch(const char* pBuf, int nLen);
		//只在刚开始建立会话时使用。
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
		//用于判断服务器端是否有最新的ID返回
		bool               m_isGetNewestID;
		//系统的状态
		xmESystemState     m_eSystemState;

		long long          m_lTimeStamp;

	private:
		void               CreateSingleSession(int nSessionID);
		xmSession *        GetSession(int nSessionID, std::string strName, bool bUseMultiSessions);
		int                Post2MSGQ(const xmPacket& pkt);

	private:
		//用于保证ds初始化过程的状态，最好使用状态机。
		xmEServiceState    m_State;
		//这个当前的名字是指依托那个数据集合进行操作
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