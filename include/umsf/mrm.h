/*******************************************************************************
Copyright (C), 2011-2022, ACC12. All rights reserved.
模 块 名：xmumsf
文 件 名：mrm.h
相关文件：无
文件版本: 5.0
功能概述：
多 线 程：不适用
异常安全：不适用
详细说明：
备注信息：无
--------------------------------------------------------------------------------
修改记录：
	日期	        版本        修改人        联系方式
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
	类名称：xmMrm
	功  能：Model Running Manager
	说  明：负责模型和VDR之间的数据、类匹配，在VDR中注册类和数据，驱动模型计算和数据IO
	*******************************************************************************/
	class xmMrm
	{
	public:
		//	model_config为：model.config/ROOT/MODEL字段
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


		//	获取模型实例数量
		size_t InstanceCount() const
		{
			return m_vModelInstance.size();
		}
		//	获取模型实例
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


		//	下面函数是对所有实例都进行相同的操作
		//	获取模型驱动节拍数
		//	通过模型配置文件中的驱动周期设置和系统节拍周期计算得出
		unsigned int GetDriveClick() const
		{
			return m_uDriveClick;
		}
		//	控制命令响应
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

		//	启动本模型全部实例
		void ReadyToGo(void)
		{
			for (size_t i = 0; i < m_vModelInstance.size(); i++)
			{
				m_vModelInstance[i]->second->Resume();
			}
		}
		//	用于将一个Message分发给不同的模型实例
		void DispatchMsg(const xmMessage& aMessage)
		{
			for (size_t i=0; i<m_vModelInstance.size(); i++)
			{
				m_vModelInstance[i]->second->PostMsg(aMessage);
			}
		}

	private:
		xmPublicResource* const m_pPublicRes;

		//	模型名称
		xmString m_strModelName;
		//	模型描述信息
		xmString m_strModelDes;

		//	模型运行的静态接口，由分析模型的XML数据文件获得
		xmMdi* m_pMdi;

		//	驱动节拍数，单位：节拍数
		unsigned int m_uDriveClick;

		//	模型实例，一个模型类可以生成多个模型实例
		typedef std::pair<std::map<xmString, xmPtr<xmMrtc> >::iterator, bool> t_cModelMapInsertResult;
		std::map<xmString, xmPtr<xmMrtc> > m_mapModelInstance;
		std::vector<std::map<xmString, xmPtr<xmMrtc> >::iterator> m_vModelInstance;
		//	根据<INSTANCE>字段内容，创建一个模型实例，并添加到MRM列表中
		void _AddInstance(const xmString& strModelFile, tinyxml2::XMLElement* instance);
		void _MatchData(xmMrtc* pMrtc, tinyxml2::XMLElement* data_match, bool bAutoType = true, xmEIOType ioType = IOT_INNER);
	};
}
#endif	//	__SSA_UMSF_MRM_H