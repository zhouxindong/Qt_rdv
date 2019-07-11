/******************************************************************************/
/** @file manager.h
@brief
	定义xmManager类。
@author 邓华 dehxya@163.com
@par 所属模块
	umsf
@par 相关文件
	manager.cpp
@see ssa::xmUMSF
@copyright (C), 2011-2022, Gonna. All rights reserved.
*******************************************************************************/
#ifndef __SSA_UMSF_MANAGER_H
#define __SSA_UMSF_MANAGER_H
#include "mrm.h"
#include "publicres.h"

namespace ssa
{
	class xmUMSF;
	class xmManager : public xmMsgHandler
	{
		friend xmUMSF;
	public:
		xmISystem* System() const
		{
			return m_pPublicRes->System();
		}
		xmINode* Node()
		{
			return m_pPublicRes->Node();
		}

		xmClickTriggerContainer* ClickTrigger()
		{
			return m_pPublicRes->m_pClickTriggerContainer;
		}
		size_t ClickTriggerCount()
		{
			return m_pPublicRes->m_pClickTriggerContainer->GetTriggerCount();
		}
		void ClickTriggerInfo(size_t uPos, unsigned int& uTriggerCycle, unsigned int& uTriggerClick, const char*& strModelName, const char*& strInstanceName, const char*& strGroupName)
		{
			const xmTrigger* pTrigger = m_pPublicRes->m_pClickTriggerContainer->GetTrigger(uPos);
			uTriggerCycle = m_pPublicRes->m_pClickTriggerContainer->GetTriggerCycle(uPos);
			uTriggerClick = m_pPublicRes->m_pClickTriggerContainer->GetTriggerClick(uPos);
			strModelName = pTrigger->m_strModelName;
			strInstanceName = pTrigger->m_strInstanceName;
			strGroupName = pTrigger->m_strGroupName;
		}

		xmEventTriggerContainer* EventTrigger()
		{
			return m_pPublicRes->m_pEventTriggerContainer;
		}
		size_t EventTriggerCount()
		{
			return m_pPublicRes->m_pEventTriggerContainer->GetTriggerCount();
		}
		void EventTriggerInfo(size_t uPos, xmString& strEvent, const char*& strModelName, const char*& strInstanceName, const char*& strGroupName, xmString& strParamValue)
		{
			const xmTrigger* pTrigger = m_pPublicRes->m_pEventTriggerContainer->GetTrigger(uPos);
			strEvent = pTrigger->PrintTrigger();
			strModelName = pTrigger->m_strModelName;
			strInstanceName = pTrigger->m_strInstanceName;
			strGroupName = pTrigger->m_strGroupName;
			strParamValue = pTrigger->PrintParam();
		}


		size_t DataTriggerCount()
		{
			return m_pPublicRes->m_vDataTriggerContainer.size();
		}
		xmDataTriggerContainer* DataTrigger(size_t uPos)
		{
			return m_pPublicRes->m_vDataTriggerContainer[uPos]->second;
		}
		void DataTriggerInfo(size_t uPos, const char*& strDataModelName, const char*& strDataMatchName, const char*& strModelName, const char*& strInstanceName, const char*& strGroupName, xmString& strParamValue)
		{
			xmDataTriggerContainer* pDataTriggerContainer = m_pPublicRes->m_vDataTriggerContainer[uPos]->second;
			const xmTrigger* pTrigger = pDataTriggerContainer->GetTrigger();

			strDataModelName = pDataTriggerContainer->GetDataName();
			strDataMatchName = pDataTriggerContainer->GetMatchName();
			xmAssert(m_pPublicRes->m_vDataTriggerContainer[uPos]->first == strDataMatchName);
			strModelName = pTrigger->m_strModelName;
			strInstanceName = pTrigger->m_strInstanceName;
			strGroupName = pTrigger->m_strGroupName;
			strParamValue = pTrigger->PrintParam();
		}

		//	遍历MRM
		size_t ModelCount() const
		{
			return m_mapMrm.size();
		}
		xmMrm* Mrm(size_t uIndex)
		{
			if (uIndex >= m_vMrm.size())
			{
				return NULL;
			}
			return m_vMrm[uIndex]->second;
		}
		xmMrm* Mrm(const xmString& strModelName)
		{
			t_MrmMap::iterator pos = m_mapMrm.find(strModelName);
			if (pos == m_mapMrm.end())
			{
				return NULL;
			}
			return pos->second;
		}

		//	启动工作负载统计
		void StartWLS(unsigned int uTime)
		{
			StartWorkLoadStatistics(uTime, (xmThreadw::OnWLSDoneFunc)__log_WLS, this);
		}
		//	回调函数执行时间统计
		xmRet ExecuteTimeStatistics(xmEManagerFunction eFunc, bool bDo)
		{
			if (eFunc == MF_ALL)
			{
				for (size_t i = 0; i < MF_ALL; i++)
				{
					m_bExecuteTime[i] = bDo;
				}
			}
			else if (eFunc != MF_ERROR)
			{
				m_bExecuteTime[eFunc] = bDo;
			}
			else
			{
				return xmE_FAIL;
			}
			return xmE_SUCCESS;
		}
		double ExecuteTime(xmEManagerFunction eFunc)
		{
			return (eFunc == MF_ALL || eFunc == MF_ERROR) ? 0.0 : m_fExecuteTime[eFunc];
		}
		//	整个UMSF中所有消息队列长度统计
		size_t TotalMsgCount() const;
	private:
		//	模型消息响应的处理时间，单位：毫秒
		xmCALC_RUNTIME(MANAGER_ETS);
		bool   m_bExecuteTime[MF_ALL];
		double m_fExecuteTime[MF_ALL];
		//	记录消息响应函数执行耗时
		void __log_ETS(const xmString& strFunction)
		{
			xmLog::info("Manager", "%s execute time %.3fms.",
				strFunction.String(),
				xmRUN_TIME(MANAGER_ETS));
		}
		static void __log_WLS(double fWLPrecent, void* pParam)
		{
			xmLog::info("Manager", "Work load %.2f%% pre second.", ((xmMsgHandler*)pParam)->WorkLoad());
		}
		void __log_level_config(size_t uTargetID, void* configField);
	private:
		//	仅供xmUMSF使用
		xmManager(void);
		~xmManager(void);

		void Initialize(const char* strUmsfConfigFile, const char* strModelConfigFile);
		void Release();

	private:
		//	管理MRM
		typedef std::map<xmString, xmPtr<xmMrm> > t_MrmMap;
		typedef std::map<xmString, xmPtr<xmMrm> >::iterator t_MrmMapIterator;
		typedef std::pair<t_MrmMapIterator, bool> t_MrmMapInsertResult;
		//	管理MRTC
		typedef std::map<xmString, xmMrtc*> t_MrtcMap;
		typedef std::map<xmString, xmMrtc*>::iterator t_MrtcMapIterator;
		typedef std::pair<t_MrtcMapIterator, bool> t_MrtcMapInsertResult;
		//	管理数据
		typedef std::multimap<xmString, xmPtr<xmDataTriggerContainer> >::iterator t_DataTriggerMapIter;


		//	模型运行管理器（Model Running Manager）表，一个模型类对应一个MRM
		t_MrmMap m_mapMrm;
		std::vector<t_MrmMapIterator> m_vMrm;
		//	模型运行时环境（Model Runtime Context）表，一个模型实例对应一个MRTC
		t_MrtcMap m_mapMrtc;
		std::vector<t_MrtcMapIterator> m_vMrtc;
		//	记录所有注册到仿真系统中的输出数据
		//	key表示数据名称或组合后的数据名称
		//	value表示该数据的类型，如果为空，表示该数据由MRTC直接注册，否则表示经过组合后的数据类型
		std::map<xmString, xmPtr<xmClass> > m_mapSystemData;

		//	UMSF运行中的公共资源
		//	包括仿真系统访问接口、触发器、预处理器
		xmPublicResource* m_pPublicRes;

		//	记录日志目标
		std::vector<size_t> m_vLogTarget;

		//	操作消息队列时的保护
		mutable xmMutex m_MsgHandleMutex;

		void _LoadUmsfConfig(const char* strUmsfConfigFile);
		void _LoadModelConfig(const char* strModelConfigFile);
		//	加载一个PACKAGE配置信息
		//	mapInstance是目前尚未使用的实例列表
		//	PACKAGE是xml对象
		//	strPath是这个PACKAGE的数据路径
		//	packageName：输出参数，表示这个Package的名称
		//	packageValue：输出参数，表示这个Package的数值
		//	返回数值的类指针
		xmClass* _LoadPackage(
			std::map<xmString, xmMrtc*>& mapInstance, 
			std::map<xmString, std::vector<xmString>>& mapInstanceData,
			tinyxml2::XMLElement* PACKAGE,
			const xmString& strPath, 
			xmString& packageName, 
			xmValue& packageValue);
		//	如果vData不为NULL，其中记录的数据均已在记录中删除
		//	返回NULL，表示不组合，vData如果为NULL，表示使用所有输出数据，否则表示使用vData中指定的输出数据
		xmClass* _LoadUsing(
			std::map<xmString, xmMrtc*>& mapInstance, 
			std::map<xmString, std::vector<xmString>>& mapInstanceData,
			tinyxml2::XMLElement* USING,
			xmMrtc*& pMrtc,						//	实例指针
			std::vector<xmString>& usingData,	//	使用的数据
			xmString& strCombineName,			//	组合名称
			xmValue& combineValue				//	组合数值
		);
		//	1、检查数据是否重复
		//	2、仿真系统中注册数据
		//	3、记录输出数据
		void iSystem_RegisterData(const xmString& strDataName, const xmValue& aValue, xmClass* pClass, const xmString& strAttribute = NULL);
		//	生成路径
		xmString _MakePath(const xmString& strPathHead, const xmString& strPathTail);

		//	仿真系统消息响应
		void __OnWorldClick(const smWorldClick& aMsg);
		void __OnDataUpdate(const smDataUpdate& aMsg);
		void __OnCtrlCommand(const smCtrlCommand& aMsg);
		void __OnSystemEvent(const smSystemEvent& aMsg);
		void __OnBulletinGet(const smBulletinGet& aMsg);
		void __OnMessageGet(const smMessageGet& aMsg);
		void OnWorldClick(const smWorldClick& aMsg);
		void OnDataUpdate(const smDataUpdate& aMsg);
		void OnCtrlCommand(const smCtrlCommand& aMsg);
		void OnSystemEvent(const smSystemEvent& aMsg);
		void OnBulletinGet(const smBulletinGet& aMsg);
		void OnMessageGet(const smMessageGet& aMsg);
		xmCREATE_MESSAGE_MAP(xmManager);
	};
}
#endif	//	__SSA_UMSF_MANAGER_H