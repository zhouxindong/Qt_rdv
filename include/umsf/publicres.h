/******************************************************************************/
/** @file publicres.h
@brief
	UMSF�����У���������Ԥ�������ȹ�����Դ��ʹ�ýӿڡ�
@author �˻� dehxya@163.com
@par ����ģ��
	umsf
@par ����ļ�
	publicres.cpp
@copyright (C), 2011-2022, Gonna. All rights reserved.
*******************************************************************************/
#ifndef __SSA_UMSF_PUBLICRES_H
#define __SSA_UMSF_PUBLICRES_H
#include "isystem.h"
#include "inode.h"
#include "trigger.h"
#include "processor.h"
#include "tinyxml2/tinyxml2.h"

namespace ssa
{
	class xmNodeScope : public xmINode
	{
	public:
		xmNodeScope() {};
		virtual ~xmNodeScope() {};

		virtual xmRet RegisterMsgHandler(xmMsgHandler* pHandler);
		virtual xmRet RegisterData(const xmString& strDataName, const xmValue& aValue, const xmString& strAttribute = NULL);
		virtual xmRet RegisterSensDate(const xmString& strDataPath);
		virtual xmRet GetValue(const xmString& dataPath, xmValue& dataValue);
		virtual xmRet SetValue(const xmString& dataPath, const xmValue& dataValue);
		virtual xmString PrintData(const xmString& strDataName = NULL);

		xmValue* FindData(const xmString strDataName);

	private:
		mutable xmMutex m_HandlerMutex;
		mutable xmMutex m_DataMutex;
		//	��Ϣ�����ӿ�
		std::vector<xmMsgHandler*> m_vHandler;
		//	���ݱ�
		std::map<xmString, xmPtr<xmValue>> m_mapData;
		//	��������·��
		std::multimap<xmString, xmString> m_mapSensitivePath;
	};


	class xmManager;
	class xmPublicResource
	{
		friend xmManager;
	public:
		//	����ϵͳ�ӿ�
		xmISystem* System()
		{
			return m_pSystem;
		}
		//	�ڵ�ӿ�
		xmINode* Node()
		{
			return m_pNodeScope;
		}

		//	ע�ᴥ����������UMSF���ô�����
		void RegisterTrigger(xmTrigger* pTrigger);
		//	ʹ��Ԥ�������ļ�·����ע��һ���µ�Ԥ��������������ļ��Ѿ��򿪣���ֱ�ӷ���
		//	���򣬴���������һ���µ�Ԥ��������
		xmIProcessor* RegisterProcessor(const xmString& strFilePath);

		//	��ȡһ��Ԫ�ص�ENABLE����
		bool IsENABLE(tinyxml2::XMLElement* element)
		{
			bool bIsEnabled = true;
			if (element != NULL)
			{
				element->QueryBoolAttribute("ENABLE", &bIsEnabled);
			}
			return bIsEnabled;
		}

	private:
		//	���к���ֻ����xmManager
		//	xmManager����������Դ�󣬹�����MRM��MRTC������ʹ��
		xmPublicResource(void);
		~xmPublicResource(void);

		//	Ԥ���ٹ�����Դ����Ҫ���д����������ٹ���
		void PreDestroy();

		//	���������ٷ���ϵͳ
		xmRet CreateSystem(const char* strInterfaceFile, const char* pProperty);
		void DestroySystem();

		//	���������ϵͳ/�ڵ���ע�����ݴ������е���������
		xmRet RegisterSensData();
		//	�����ϵͳ/�ڵ����ٴ�ע�����ݴ������е���������
		xmRet RetryRegisterSensData();

	private:
		//	����ϵͳ�ӿڣ�Ψһ��������ģ��ʹ��
		xmISystem* m_pSystem;
		//	����ϵͳ�������ؿ�
		xmLib m_SystemDll;
		typedef xmISystem* (*tCreateSystem)(const char* strConfig);
		typedef void(*tDestroySystem)(xmISystem* pSystem);
		tCreateSystem m_pfnCreateSystem;
		tDestroySystem m_pfnDestroySystem;

		//	���ؽڵ����ݿռ�
		xmPtr<xmNodeScope> m_pNodeScope;

		//	������
		xmPtr<xmClickTriggerContainer> m_pClickTriggerContainer;
		xmPtr<xmEventTriggerContainer> m_pEventTriggerContainer;
		//	��¼�������ݴ�������key�Ǵ���������������ϵͳ�е�����
		std::multimap<xmString, xmPtr<xmDataTriggerContainer> > m_mapDataTriggerContainer;
		std::vector<std::multimap<xmString, xmPtr<xmDataTriggerContainer>>::iterator> m_vDataTriggerContainer;
		//	��¼����ע��ʧ�ܵ����ݴ�����
		std::multimap<xmString, xmDataTriggerContainer*> m_mapPendingDataTriggerContainer;
		//	����Ԥ������
		std::map<xmString, xmIProcessor*> m_mapProcessor;
	};
}
#endif	//	__SSA_UMSF_MANAGER_H