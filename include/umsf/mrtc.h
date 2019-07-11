#ifndef __SSA_UMSF_MRTC_H
#define __SSA_UMSF_MRTC_H
#include "publicres.h"
#include "mdi.h"
#include "rtdata.h"
#include "rtgroup.h"
#include "mloader.h"
#include "mserver.h"
#include "udefine.h"

namespace ssa
{
	//	ģ���ֶ���IOʱ����MRTC���͵���Ϣ��
#define tmC_APPLY_GROUP_IO	0x2100
	class tmApplyGroupIO : public xmMessage
	{
	public:
		tmApplyGroupIO(xmRuntimeGroup* pGroup) : m_pGroup(pGroup)
		{
		};
		tmApplyGroupIO(const tmApplyGroupIO& msg) : m_pGroup(msg.m_pGroup)
		{
		};
		virtual ~tmApplyGroupIO(void)
		{
		};
		virtual xmMessage* Clone(void) const
		{
			return new tmApplyGroupIO(*this);
		};
	public:
		xmRuntimeGroup* m_pGroup;
		xmDECLARE_MESSAGE_CLASS(tmC_APPLY_GROUP_IO);
	};
	xmDECLARE_MESSAGE_FUNC(tmApplyGroupIOFunc, tmApplyGroupIO);

	//	ģ���ֶ�����IOʱ����MRTC���͵���Ϣ��
#define tmC_APPLY_DATA_IO	0x2200
	class tmApplyDataIO : public xmMessage
	{
	public:
		tmApplyDataIO(xmRuntimeData* pData) : m_pData(pData)
		{
		};
		tmApplyDataIO(const tmApplyDataIO& msg) : m_pData(msg.m_pData)
		{
		};
		virtual ~tmApplyDataIO(void)
		{
		};
		virtual xmMessage* Clone(void) const
		{
			return new tmApplyDataIO(*this);
		};
	public:
		xmRuntimeData* m_pData;
		xmDECLARE_MESSAGE_CLASS(tmC_APPLY_DATA_IO);
	};
	xmDECLARE_MESSAGE_FUNC(tmApplyDataIOFunc, tmApplyDataIO);

	/*******************************************************************************
    �����ƣ�xmMrtc
    ��  �ܣ�����Model Runtime Context
    ˵  ����MRTC����ģ���ڷ�������п���ʹ�õ���Դ��
		    ÿһ��ģ�;�����һ��MRTC��ģ�����еĽ�������ͨ��MRTC��
    *******************************************************************************/
    class xmMrtc : public xmMsgHandler
    {
		friend xmTriggerScript;
		friend xmModelServer;
	public:
		//	strInstanceName������ΪNULLʱ����ʾ��ģ�ͽ���һ��ʵ����ʵ�����ƴ洢��MRM��
		//	�����NULL����ģ���ж��ʵ�������ʵ����������strInstanceName������������Ĳ�������
		//	����װ�ڸ����Ƶ���������
		//	bCombined������ʾ�Ƿ��ģ�͵�����ʵ��������װ��һ�����������ڡ�
		xmMrtc(xmPublicResource* pPubRes, const char* strModelName, xmMdi* pMdi, const char* strInstanceName);
		~xmMrtc(void);

		//	��һ������MDI��������ģ�����л���
		void Create();
		void Destroy();

		//	����������model.config�ļ��е�������Ϣ������ģ���������л���
		//	��1������ƥ����Ϣ
		typedef struct _tagMatchInfo
		{
			_tagMatchInfo() : m_eMatchTarget(DMT_NULL), m_strMatchName(NULL), m_strInitString(NULL), m_pProcessor(NULL) {};
			xmEDataMatchTarget m_eMatchTarget;	//	����ƥ��Ŀ��
			xmString m_strMatchName;	//	����ϵͳ�е�����
			xmString m_strInitString;	//	ģ�ͻ����еĳ�ʼֵ
			xmIProcessor* m_pProcessor;	//	Ԥ������
		}SMatchInfo;
		//	��������ƥ��
		//	�������ݵ�matchName����������·��
		//	������ݵ�matchNameֻ��������
		//	�ڲ�����ֻ��ƥ��pInitValue
		void SetDataMatch(xmRuntimeData* pData, const SMatchInfo& matchInfo);
		//	��2������������ݵ����·��
		//	pData������Ŀǰֻ֧��ʵ�����������·�����ã����Ӧ����ΪNULL��
		void SetDataPath(xmRuntimeData* pData, const char* strDataPath);
		//	���ָ���������ϵͳ�����ݣ���ģ�͵�������ݰ���˳����ϳ�һ���µ�xmClass�ṹ
		//	����SetDataMatchǰ����ú����������ͬ
		//	��������Ѿ���ƥ�䣬����ƥ�������ݽ������
		//	����ʹ��ԭʼ���ݽ������
		//	vDataʹ��ģ����������
		xmClass* GetCombineClass(const std::vector<xmString>& vData, xmValue& combineValue);
		//	��3��ע�ᴥ������ֻ������ƥ��֮�󣬲���ע�ᴥ��������Ϊ��Ϊ��������ģ����������
		//	������ϵͳƥ���б��ı�Ϊ��������
		size_t RegisterTrigger();

		//	����������ʹ�ø�MRTC��ģ��ʵ��
		void CreateInstance(const xmString& strModelFile, const xmString& strModelData);

		//	��ȡģ������
		inline const xmString& ModelName() const
		{
			return m_strModelName;
		}

		//	��ȡģ��ʵ������
		inline const xmString& InstanceName() const
		{
			return m_strInstanceName;
		}

		//	��ȡģ����������Ϣ
		size_t GetDataCount() const;
		size_t GetDataCount(xmEIOType ioType) const;
		xmRuntimeData* GetData(const xmString& strDataName);
		xmRuntimeData* GetData(xmEIOType ioType, size_t uIndex);
		xmRuntimeData* GetData(xmEIOType ioType, const xmString& strDataName);
		//	��ȡ������ֵ������������������ʱ����ʹ��MRTC��ԭ���ݽ��б���
		xmRet GetDataValue(xmRuntimeData* pData, xmValue& cacheValue);
		xmRet GetDataSystemValue(xmRuntimeData* pData, xmValue& systemValue);

		//	��ȡģ������Ϣ
		size_t GetGroupCount() const;
		xmRuntimeGroup* GetGroup(const xmString& strDataName);
		xmRuntimeGroup* GetGroup(size_t uIndex);

		//	��ӡ������Ϣ
		xmString PrintData(const xmRuntimeData* pData = NULL) const;
		xmString PrintGroup(const xmRuntimeGroup* pGroup = NULL) const;


		//	ģ�����ݷ���
		xmIModelServer& ModelServer()
		{
			return *m_pModelServer;
		}

		//	���л����Լ�
		xmRet Inspect(xmString& strError);

		//	������������ͳ��
		void StartWLS(unsigned int uTime)
		{
			StartWorkLoadStatistics(uTime, (xmThreadw::OnWLSDoneFunc)__log_WLS, this);
		}

		//	��Ϣ��Ӧ����ִ��ʱ��
		xmRet ExecuteTimeStatistics(xmEInstanceFunction eFunc, bool bDo)
		{
			if (eFunc == IF_ALL)
			{
				for (size_t i = 0; i < IF_ALL; i++)
				{
					m_bExecuteTime[i] = bDo;
				}
			}
			else if (eFunc != IF_ERROR)
			{
				m_bExecuteTime[eFunc] = bDo;
			}
			else
			{
				return xmE_FAIL;
			}
			return xmE_SUCCESS;
		}
		double ExecuteTime(xmEInstanceFunction eFunc)
		{
			return (eFunc == IF_ALL || eFunc == IF_ERROR) ? 0.0 : m_fExecuteTime[eFunc];
		}
	private:
		/*******************************************************************************
		�������� Trigger �� Manager ����Ϣ
		*******************************************************************************/
		void __OnWorldClick(const smWorldClick& aMsg);		
		void __OnCtrlCommand(const smCtrlCommand& aMsg);	
		void __OnTrigger(const tmTrigger& aMsg);			
		void __OnApplyGroupIO(const tmApplyGroupIO& aMsg);	
		void __OnApplyDataIO(const tmApplyDataIO& aMsg);	
		void OnWorldClick(const smWorldClick& aMsg);		
		void OnCtrlCommand(const smCtrlCommand& aMsg);		
		void OnTrigger(const tmTrigger& aMsg);				
		void OnApplyGroupIO(const tmApplyGroupIO& aMsg);	
		void OnApplyDataIO(const tmApplyDataIO& aMsg);		
		xmCREATE_MESSAGE_MAP(xmMrm);

		//	ģ����Ϣ��Ӧ�Ĵ���ʱ�䣬��λ������
		xmCALC_RUNTIME(MRTC_ETS);
		bool   m_bExecuteTime[IF_ALL];
		double m_fExecuteTime[IF_ALL];

	private:
		/*******************************************************************************
		��ģ��ʹ�õĽӿڣ���xmModelServer����
		*******************************************************************************/
		//	��¼ϵͳ��־
		inline void Log(xmLog::ELogLevel eLevel, const char* strContent)
		{
			xmString strTitle = xmStringUtil::Format("%s::%s", m_strModelName.String(), m_strInstanceName.String());
			xmLog::log(eLevel, strTitle, strContent);
		}

		//	��ȡ����״̬����ʼ�����������ᣬ�ⶳ����ɡ��ط�
		inline unsigned int GetSimulateState(void) const 
		{ 
			return m_pPublicRes->System()->GetSimulateState(); 
		};
		//	��ȡ��ǰ���汶��
		inline int GetSimulateSpeed(void) const 
		{ 
			return m_pPublicRes->System()->GetSimulateSpeed(); 
		};
		//	��ȡ��ǰ�ɷ�����ͳһ��ϵͳʱ�䣬��λ��ȡ����ϵͳ
		inline time_t GetSystemTime(void) const
		{
			return m_pPublicRes->System()->GetSystemTime();
		};
		//	��ȡ��ǰ�������������λ�����ĸ���
		inline size_t GetClickCount(void) const 
		{ 
			return m_pPublicRes->System()->GetClickCount(); 
		};
		//	��ȡÿ��������ĵ�ʱ�䣬�ɷ���ϵͳ��������λ������
		inline unsigned int GetClickCycle(void) const 
		{ 
			return m_pPublicRes->System()->GetClickCycle(); 
		};
		//	��ȡģ�����õ��������ڣ���ʱ�䣬��һ����ģ��ʵ������ʱ�䡣��λ������
		inline unsigned int GetDriveCycle(void) const 
		{ 
			return m_pMdi->DriveCycle(); 
		};
		//	��ȡÿ���������ڵ�ʵ�ʽ���������λ��������
		//	GetClickCycle() �� GetDriveClick() = ʵ������ʱ��
		inline unsigned int GetDriveClick(void) const
		{
			return m_uDriveClick;
		};

		//	���ݱ���
		//	����uPos��ʾ�ڼ�������
		size_t InnerDataCount(void) const
		{
			return m_vInnerData.size();
		};
		const xmString& InnerDataName(size_t uPos) const
		{
			return m_vInnerData[uPos]->first;
		};
		const char* InnerDataAttr(size_t uPos, const char* strAttrName) const
		{
			return m_vInnerData[uPos]->second->DataAttr(strAttrName);
		}
		const char* InnerDataAttr(const xmString& strDataName, const char* strAttrName) const
		{
			std::map<xmString, xmPtr<xmRuntimeData>>::const_iterator pos = m_mapInnerData.find(strDataName);
			return (pos == m_mapInnerData.end()) ? NULL : pos->second->DataAttr(strAttrName);
		}
		size_t InputDataCount(void) const
		{
			return m_vInputData.size();
		};
		const xmString& InputDataName(size_t uPos) const
		{
			return m_vInputData[uPos]->first;
		};
		const char* InputDataAttr(size_t uPos, const char* strAttrName) const
		{
			return m_vInputData[uPos]->second->DataAttr(strAttrName);
		}
		const char* InputDataAttr(const xmString& strDataName, const char* strAttrName) const
		{
			std::map<xmString, xmPtr<xmRuntimeData>>::const_iterator pos = m_mapInputData.find(strDataName);
			return (pos == m_mapInputData.end()) ? NULL : pos->second->DataAttr(strAttrName);
		}
		size_t OutputDataCount(void) const
		{
			return m_vOutputData.size();
		};
		const xmString& OutputDataName(size_t uPos) const
		{
			return m_vOutputData[uPos]->first;
		};
		const char* OutputDataAttr(size_t uPos, const char* strAttrName) const
		{
			return m_vOutputData[uPos]->second->DataAttr(strAttrName);
		}
		const char* OutputDataAttr(const xmString& strDataName, const char* strAttrName) const
		{
			std::map<xmString, xmPtr<xmRuntimeData>>::const_iterator pos = m_mapOutputData.find(strDataName);
			return (pos == m_mapOutputData.end()) ? NULL : pos->second->DataAttr(strAttrName);
		}

		//	��ģ��ʹ�õ����ݷ��ʽӿڣ�strDataPath������Ϊ���ݵ�ģ�����ƣ�Ҳ�����÷��š�.��ֱ�ӷ���
		//	�ṹ�������е����ԣ���:"�칬״̬.λ����Ϣ.X��"
		//	�����������ݣ����ģ�͸ı�����ֵ��������Input����ʱ���ᱻϵͳ���ݸı�
		//	����uPos��ʾ�ڼ�������
		inline xmValue InnerData(const xmString& strDataPath) const
		{
			return _FindValue(m_mapInnerData, strDataPath);
		}
		inline xmValue InnerData(size_t uPos) const
		{
			return m_vInnerData[uPos]->second->DataValue().PropertyValue();
		}
		inline xmValue InputData(const xmString& strDataPath) const
		{
			return _FindValue(m_mapInputData, strDataPath);
		}
		inline xmValue InputData(size_t uPos) const
		{
			return m_vInputData[uPos]->second->DataValue().PropertyValue();
		}
		inline xmValue OutputData(const xmString& strDataPath) const
		{
			return _FindValue(m_mapOutputData, strDataPath);
		}
		inline xmValue OutputData(size_t uPos) const
		{
			return m_vOutputData[uPos]->second->DataValue().PropertyValue();
		}
		//	��ģ��ʹ�õ����ݷ��ʽӿڣ��������ڲ������롢������ݣ�����ͬ��
		inline xmValue ModelData(const xmString& strDataPath, xmEIOType& ioType) const
		{
			return _FindValue(strDataPath, ioType);
		}
		inline xmValue ModelData(const xmString& strDataPath) const
		{
			xmEIOType ioType;
			return ModelData(strDataPath, ioType);
		}

		//	�����
		//	����uPos��ʾ�ڼ����飬����uIndex��ʾ���еڼ�������
		size_t GroupCount(void) const
		{
			return m_vGroup.size();
		};
		const xmString& GroupName(size_t uPos) const
		{
			return m_vGroup[uPos]->first;
		};
		xmEIOType GroupType(size_t uPos) const
		{
			return m_vGroup[uPos]->second->IOType();
		};
		const char* GroupAttr(size_t uPos, const char* strAttrName) const
		{
			return m_vGroup[uPos]->second->Attribute(strAttrName);
		}
		const char* GroupAttr(const xmString& strGroupName, const char* strAttrName) const
		{
			std::map<xmString, xmPtr<xmRuntimeGroup>>::const_iterator pos = m_mapGroup.find(strGroupName);
			return (pos == m_mapGroup.end()) ? NULL : pos->second->Attribute(strAttrName);
		}
		size_t GroupDataCount(size_t uPos) const
		{
			return m_vGroup[uPos]->second->m_DataList.size();
		};
		const xmString& GroupDataName(size_t uPos, size_t uIndex) const
		{
			return m_vGroup[uPos]->second->m_DataList[uIndex]->DataName();
		};
		//	��ȡ�������������״̬
		bool  GetGroupEnabled(const xmString& strGroupName)
		{
			xmRuntimeGroup* pGroup = _FindGroup(m_mapGroup, strGroupName);
			if (pGroup == NULL)
			{
				return false;
			}
			return pGroup->IsEnabled();
		}
		xmRet SetGroupEnabled(const xmString& strGroupName, bool bIsEnabled)
		{
			xmRuntimeGroup* pGroup = _FindGroup(m_mapGroup, strGroupName);
			if (pGroup == NULL)
			{
				return xmE_FAIL;
			}
			pGroup->SetEnabled(bIsEnabled);
			return xmE_SUCCESS;
		}

		//	ģ���������IO�������κ����ơ�IOΪ�첽ִ��
		//	����IOʱ��ֻ��ָ��������������ݣ�����ָ������������
		xmRet ApplyGroupIO(const xmString& strGroupName);
		xmRet ApplyDataInput(const xmString& strDataName);
		xmRet ApplyDataOutput(const xmString& strDataName);
		//	ģ���ֶ�����IO�������κ����ơ�IOΪͬ��ִ��
		//	�ֶ�IOʱ��ֻ��ָ��������������ݣ�����ָ������������
		xmRet ManualGroupIO(const xmString& strGroupName, bool bLockData = false);
		xmRet ManualDataInput(const xmString& strDataName, bool bLockData = false);
		xmRet ManualDataOutput(const xmString& strDataName, bool bLockData = false);

	private:
		//	����ģ�͵Ļص�������Ҫ���л��汣�����쳣����
		//	���ִ����ֻ����¼����־�У����ж�UMSF����
		xmRet iModel_OnLoad(const char* strDataFile);
		void iModel_OnUnload(void);
		bool iModel_IsReady(void);
		void iModel_OnDrive(unsigned long uClick);
		//	���лص������������������UMSF������д����
		//	����������Ӧ�ص�����
		void iModel_OnStart(void);
		void iModel_OnFinish(void);
		void iModel_OnFreeze(void);
		void iModel_OnUnfreeze(void);
		void iModel_OnSpeed(int nSpeed);
		void iModel_OnCommand(const xmString& cmdName, const xmValue& cmdParam);
		void iModel_OnPrepareGroupInput(const char* strGroupName);
		void iModel_OnFinishGroupInput(const char* strGroupName, bool isDone);
		void iModel_OnPrepareGroupOutput(const char* strGroupName);
		void iModel_OnFinishGroupOutput(const char* strGroupName, bool isDone);
		void iModel_OnApplyGroupIO(const char* strGroupName, bool isDone);
		void iModel_OnApplyDataIO(const char* strDataName, bool isDone);

	private:
		//	������Դ
		xmPublicResource* const m_pPublicRes;
		//	Ϊģ���ṩ�ķ���ӿ�
		xmModelServer* m_pModelServer;

		//	ģ������
		const xmString m_strModelName;
		//	ģ��������Ϣ
		xmMdi* const m_pMdi;
		//	ģ������ʵ��������
		xmModelLoader* m_pModelLoader;


		//	ʵ������
		const xmString m_strInstanceName;
		//	��ǰ�������������ʵʱ�������������
		unsigned int m_uClickCount;
		//	ģ�������Ľ�����
		unsigned int m_uDriveClick;

		//	���ڲ������롢��������¼ģ������
		//	�����������е�key����ָģ��ʹ�õ���������
		xmBuffer m_InnerCache;
		xmBuffer m_InputCache;
		xmBuffer m_OutputCache;
		std::map<xmString, xmPtr<xmRuntimeData> > m_mapInnerData;
		std::map<xmString, xmPtr<xmRuntimeData> > m_mapInputData;
		std::map<xmString, xmPtr<xmRuntimeData> > m_mapOutputData;
		std::vector<std::map<xmString, xmPtr<xmRuntimeData>>::iterator> m_vInnerData;
		std::vector<std::map<xmString, xmPtr<xmRuntimeData>>::iterator> m_vInputData;
		std::vector<std::map<xmString, xmPtr<xmRuntimeData>>::iterator> m_vOutputData;
		//	��¼ģ��ʹ�õ�ȫ������
		std::map<xmString, xmRuntimeData*> m_mapModelData;

		//	���ݻ�����ʹ�û���Ķ�д������������ʱ���ݵ�ֵ���ڴ����ݻ�����
		mutable xmRWLock m_InnerCacheLock;
		mutable xmRWLock m_InputCacheLock;
		mutable xmRWLock m_OutputCacheLock;

		//	m_mapGroup��¼����IO����Ϣ������keyΪ������valueΪ�����
		std::map<xmString, xmPtr<xmRuntimeGroup> > m_mapGroup;
		std::vector<std::map<xmString, xmPtr<xmRuntimeGroup>>::iterator> m_vGroup;
		//	m_mapDataTriggerGroup��¼����ʹ�����ݴ�����������Ϣ��keyΪ��������ModelName��valueΪ�����
		std::multimap<xmString, xmRuntimeGroup*> m_mapDataTriggerGroup;


		size_t _InitData(const std::vector<xmMdi::t_DataPtrMapIterator>& vInitData, std::map<xmString, xmPtr<xmRuntimeData> >& mapData, xmBuffer& cache, xmEIOType iot);

		void _InitGroup(const xmModelGroup* pModelGroup, std::map<xmString, xmPtr<xmRuntimeData> >& mapData, xmRuntimeGroup* pGroup);

		xmRet _GroupIO(xmRuntimeGroup* pGroup, bool bLockData = true);
		xmRet _DataIO(xmRuntimeData* pData, bool bLockData = true);

		//	�������ģ�����ƣ���ȡ���������ʱ����
		static xmRuntimeGroup* _FindGroup(std::map<xmString, xmPtr<xmRuntimeGroup> >& mapGroup, const xmString& strGroupName);
		//	��ָ�����������ݱ��У��������ݵ�ģ�����ƺ�����·������ȡ�����ݵ�����ʱ��ֵ
		static xmValue _FindValue(const std::map<xmString, xmPtr<xmRuntimeData> >& mapData, const xmString& strDataPath);
		xmValue _FindValue(const xmString& strDataPath, xmEIOType& ioType) const;

		//	��¼MRTC����ģ��ʵ���ӿں�������
		void __log_error_iModel(const xmString& strFunction, int nErrorID, const char* strErrorMsg)
		{
			xmString strTitle = xmStringUtil::Format("%s::%s", m_strModelName.String(),	m_strInstanceName.String());
			xmLog::error(strTitle, "Call model interface %s failed(%d): %s",
				strFunction.String(),
				nErrorID,
				strErrorMsg);
		}
		//	��¼ģ��������IO����
		void __log_error_GroupIO(xmRuntimeGroup* pGroup, int nErrorID, const char* strErrorMsg)
		{
			xmString strTitle = xmStringUtil::Format("%s::%s", m_strModelName.String(), m_strInstanceName.String());
			xmLog::error(strTitle, "Group %s %s failed(%d): %s",
				pGroup->ModelGroup().Name().String(),
				pGroup->IOType() == IOT_INPUT ? "input" : "output",
				nErrorID,
				strErrorMsg);
		}
		//	��¼ģ������IO����
		void __log_error_DataIO(xmRuntimeData* pData, int nErrorID, const char* strErrorMsg)
		{
			xmString strTitle = xmStringUtil::Format("%s::%s", m_strModelName.String(), m_strInstanceName.String());
			xmLog::error(strTitle, "Data %s/%s %s failed(%d): %s",
				pData->DataName().String(),
				pData->SystemPath().String(),
				pData->IOType() == IOT_INPUT ? "input" : "output",
				nErrorID,
				strErrorMsg);
		}
		//	��¼MRTC��Ϣ��Ӧ����ִ�к�ʱ
		void __log_ETS(const xmString& strFunction)
		{
			xmString strTitle = xmStringUtil::Format("%s::%s", m_strModelName.String(), m_strInstanceName.String());
			xmLog::info(strTitle, "%s execute time %.3fms.",
				strFunction.String(),
				xmRUN_TIME(MRTC_ETS));
		}
		static void __log_WLS(double fWLPrecent, void* pParam)
		{
			xmMrtc* pMrtc = (xmMrtc*)pParam;
			xmString strTitle = xmStringUtil::Format("%s::%s", pMrtc->m_strModelName.String(), pMrtc->m_strInstanceName.String());
			xmLog::info(strTitle, "Work load %.2f%% pre second.", pMrtc->WorkLoad());
		}
	};
}   //  namespace ssa
#endif  //  __SSA_UMSF_MRTC_H

