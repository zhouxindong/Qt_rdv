/*******************************************************************************
Copyright (C), 2011-2022, ACC12. All rights reserved.
ģ �� ����xmumsf
�� �� ����mrm.h
����ļ�����
�ļ��汾: 5.0
���ܸ�����
�� �� �̣�������
�쳣��ȫ��������
��ϸ˵����
��ע��Ϣ����
--------------------------------------------------------------------------------
�޸ļ�¼��
	����	        �汾        �޸���        ��ϵ��ʽ
*******************************************************************************/
#ifndef __SSA_UMSF_MRM_H
#define __SSA_UMSF_MRM_H
#include "publicres.h"
#include "mdi.h"
#include "mrtc.h"
#include "tinyxml2/tinyxml2.h"
#include "udefine.h"

namespace ssa
{
	/*******************************************************************************
	�����ƣ�xmMrm
	��  �ܣ�Model Running Manager
	˵  ��������ģ�ͺ�VDR֮������ݡ���ƥ�䣬��VDR��ע��������ݣ�����ģ�ͼ��������IO
	*******************************************************************************/
	class xmMrm
	{
	public:
		//	model_configΪ��model.config/ROOT/MODEL�ֶ�
		xmMrm(xmPublicResource* pPubRes);
		virtual ~xmMrm();

	public:
		void Load(tinyxml2::XMLElement* model_config);
		void Unload();

		const xmString& ModelName() const
		{
			return m_strModelName;
		}

		const xmMdi* Mdi() const
		{
			return m_pMdi;
		}


		//	��ȡģ��ʵ������
		size_t InstanceCount() const
		{
			return m_vModelInstance.size();
		}
		//	��ȡģ��ʵ��
		xmMrtc* Mrtc(size_t uIndex)
		{
			if (uIndex >= m_vModelInstance.size())
			{
				return NULL;
			}
			return m_vModelInstance[uIndex]->second;
		}
		xmMrtc* Mrtc(const xmString& strInstanceName)
		{
			std::map<xmString, xmPtr<xmMrtc> >::iterator pos = m_mapModelInstance.find(strInstanceName);
			if (pos == m_mapModelInstance.end())
			{
				return NULL;
			}
			return pos->second;
		}


		//	���溯���Ƕ�����ʵ����������ͬ�Ĳ���
		//	��ȡģ������������
		//	ͨ��ģ�������ļ��е������������ú�ϵͳ�������ڼ���ó�
		unsigned int GetDriveClick() const
		{
			return m_uDriveClick;
		}
		//	����������Ӧ
		bool IsRespondStart() const
		{
			return m_pMdi->IsRespondStart();
		}
		bool IsRespondFreeze() const
		{
			return m_pMdi->IsRespondFreeze();
		}
		bool IsRespondSpeed() const
		{
			return m_pMdi->IsRespondSpeed();
		}

		//	������ģ��ȫ��ʵ��
		void ReadyToGo(void)
		{
			for (size_t i = 0; i < m_vModelInstance.size(); i++)
			{
				m_vModelInstance[i]->second->Resume();
			}
		}
		//	���ڽ�һ��Message�ַ�����ͬ��ģ��ʵ��
		void DispatchMsg(const xmMessage& aMessage)
		{
			for (size_t i=0; i<m_vModelInstance.size(); i++)
			{
				m_vModelInstance[i]->second->PostMsg(aMessage);
			}
		}

	private:
		xmPublicResource* const m_pPublicRes;

		//	ģ������
		xmString m_strModelName;
		//	ģ��������Ϣ
		xmString m_strModelDes;

		//	ģ�����еľ�̬�ӿڣ��ɷ���ģ�͵�XML�����ļ����
		xmMdi* m_pMdi;

		//	��������������λ��������
		unsigned int m_uDriveClick;

		//	ģ��ʵ����һ��ģ����������ɶ��ģ��ʵ��
		typedef std::pair<std::map<xmString, xmPtr<xmMrtc> >::iterator, bool> t_cModelMapInsertResult;
		std::map<xmString, xmPtr<xmMrtc> > m_mapModelInstance;
		std::vector<std::map<xmString, xmPtr<xmMrtc> >::iterator> m_vModelInstance;
		//	����<INSTANCE>�ֶ����ݣ�����һ��ģ��ʵ��������ӵ�MRM�б���
		void _AddInstance(const xmString& strModelFile, tinyxml2::XMLElement* instance);
		void _MatchData(xmMrtc* pMrtc, tinyxml2::XMLElement* data_match, bool bAutoType = true, xmEIOType ioType = IOT_INNER);
	};
}
#endif	//	__SSA_UMSF_MRM_H