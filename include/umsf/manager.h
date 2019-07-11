/******************************************************************************/
/** @file manager.h
@brief
	����xmManager�ࡣ
@author �˻� dehxya@163.com
@par ����ģ��
	umsf
@par ����ļ�
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

		//	����MRM
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

		//	������������ͳ��
		void StartWLS(unsigned int uTime)
		{
			StartWorkLoadStatistics(uTime, (xmThreadw::OnWLSDoneFunc)__log_WLS, this);
		}
		//	�ص�����ִ��ʱ��ͳ��
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
		//	����UMSF��������Ϣ���г���ͳ��
		size_t TotalMsgCount() const;
	private:
		//	ģ����Ϣ��Ӧ�Ĵ���ʱ�䣬��λ������
		xmCALC_RUNTIME(MANAGER_ETS);
		bool   m_bExecuteTime[MF_ALL];
		double m_fExecuteTime[MF_ALL];
		//	��¼��Ϣ��Ӧ����ִ�к�ʱ
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
		//	����xmUMSFʹ��
		xmManager(void);
		~xmManager(void);

		void Initialize(const char* strUmsfConfigFile, const char* strModelConfigFile);
		void Release();

	private:
		//	����MRM
		typedef std::map<xmString, xmPtr<xmMrm> > t_MrmMap;
		typedef std::map<xmString, xmPtr<xmMrm> >::iterator t_MrmMapIterator;
		typedef std::pair<t_MrmMapIterator, bool> t_MrmMapInsertResult;
		//	����MRTC
		typedef std::map<xmString, xmMrtc*> t_MrtcMap;
		typedef std::map<xmString, xmMrtc*>::iterator t_MrtcMapIterator;
		typedef std::pair<t_MrtcMapIterator, bool> t_MrtcMapInsertResult;
		//	��������
		typedef std::multimap<xmString, xmPtr<xmDataTriggerContainer> >::iterator t_DataTriggerMapIter;


		//	ģ�����й�������Model Running Manager����һ��ģ�����Ӧһ��MRM
		t_MrmMap m_mapMrm;
		std::vector<t_MrmMapIterator> m_vMrm;
		//	ģ������ʱ������Model Runtime Context����һ��ģ��ʵ����Ӧһ��MRTC
		t_MrtcMap m_mapMrtc;
		std::vector<t_MrtcMapIterator> m_vMrtc;
		//	��¼����ע�ᵽ����ϵͳ�е��������
		//	key��ʾ�������ƻ���Ϻ����������
		//	value��ʾ�����ݵ����ͣ����Ϊ�գ���ʾ��������MRTCֱ��ע�ᣬ�����ʾ������Ϻ����������
		std::map<xmString, xmPtr<xmClass> > m_mapSystemData;

		//	UMSF�����еĹ�����Դ
		//	��������ϵͳ���ʽӿڡ���������Ԥ������
		xmPublicResource* m_pPublicRes;

		//	��¼��־Ŀ��
		std::vector<size_t> m_vLogTarget;

		//	������Ϣ����ʱ�ı���
		mutable xmMutex m_MsgHandleMutex;

		void _LoadUmsfConfig(const char* strUmsfConfigFile);
		void _LoadModelConfig(const char* strModelConfigFile);
		//	����һ��PACKAGE������Ϣ
		//	mapInstance��Ŀǰ��δʹ�õ�ʵ���б�
		//	PACKAGE��xml����
		//	strPath�����PACKAGE������·��
		//	packageName�������������ʾ���Package������
		//	packageValue�������������ʾ���Package����ֵ
		//	������ֵ����ָ��
		xmClass* _LoadPackage(
			std::map<xmString, xmMrtc*>& mapInstance, 
			std::map<xmString, std::vector<xmString>>& mapInstanceData,
			tinyxml2::XMLElement* PACKAGE,
			const xmString& strPath, 
			xmString& packageName, 
			xmValue& packageValue);
		//	���vData��ΪNULL�����м�¼�����ݾ����ڼ�¼��ɾ��
		//	����NULL����ʾ����ϣ�vData���ΪNULL����ʾʹ������������ݣ������ʾʹ��vData��ָ�����������
		xmClass* _LoadUsing(
			std::map<xmString, xmMrtc*>& mapInstance, 
			std::map<xmString, std::vector<xmString>>& mapInstanceData,
			tinyxml2::XMLElement* USING,
			xmMrtc*& pMrtc,						//	ʵ��ָ��
			std::vector<xmString>& usingData,	//	ʹ�õ�����
			xmString& strCombineName,			//	�������
			xmValue& combineValue				//	�����ֵ
		);
		//	1����������Ƿ��ظ�
		//	2������ϵͳ��ע������
		//	3����¼�������
		void iSystem_RegisterData(const xmString& strDataName, const xmValue& aValue, xmClass* pClass, const xmString& strAttribute = NULL);
		//	����·��
		xmString _MakePath(const xmString& strPathHead, const xmString& strPathTail);

		//	����ϵͳ��Ϣ��Ӧ
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