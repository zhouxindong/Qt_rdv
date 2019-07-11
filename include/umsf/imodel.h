#ifndef __SSA_UMSF_IMODEL_H
#define __SSA_UMSF_IMODEL_H
#include "../base/base.h"
#include "idefine.h"
namespace ssa
{
	/*******************************************************************************
	*  ����ĺ����ڰ����û���DLL�е���ģ��
	*  һ��DLLֻ�ܴ���һ��ģ��
	*******************************************************************************/
#ifdef xmOS_WINDOWS
#define __MODEL_EXPORT_API __declspec(dllexport)
#else
#define __MODEL_EXPORT_API
#endif

#ifdef  __cplusplus
#define xmEXPORT_MODEL(Class)													\
    extern "C"																	\
    {																			\
    __MODEL_EXPORT_API ssa::xmIModel* CreateModel(ssa::xmIModelServer* pServer);\
    __MODEL_EXPORT_API void DestroyModel(ssa::xmIModel* pModel);				\
    }																			\
    __MODEL_EXPORT_API ssa::xmIModel* CreateModel(ssa::xmIModelServer* pServer)	\
    {																			\
		if (xmString(pServer->InterfaceVersion()) != xmIMODELSERVER_VERSION)	\
		{																		\
			return NULL;														\
		}																		\
		return new Class(pServer);												\
    }																			\
    __MODEL_EXPORT_API void DestroyModel(ssa::xmIModel* pModel)					\
    {																			\
        if(pModel != NULL)														\
        {																		\
            delete pModel;														\
        }																		\
    }
#else   // C Language
#define xmEXPORT_MODEL(Class)													\
    __MODEL_EXPORT_API ssa::xmIModel* CreateModel(ssa::xmIModelServer* pServer);\
    __MODEL_EXPORT_API void DestroyModel(ssa::xmIModel* pModel);				\
    __MODEL_EXPORT_API ssa::xmIModel* CreateModel(ssa::xmIModelServer* pServer)	\
    {																			\
		if (xmString(pServer->InterfaceVersion()) != xmIMODELSERVER_VERSION)	\
		{																		\
			return NULL;														\
		}																		\
		return new Class(pServer);												\
    }																			\
    __MODEL_EXPORT_API void DestroyModel(ssa::xmIModel* pModel)					\
    {																			\
        if(pModel != NULL)														\
        {																		\
            delete pModel;														\
        }																		\
    }
#endif  //  __cplusplus


	/******************************************************************************/
	/** @class xmIModelServer
	@brief
		xmIModelServer ������UMSF�ܹ�Ϊģ���ṩ�ķ���ӿڡ�
	*******************************************************************************/
#define xmIMODELSERVER_VERSION "V5.0.00_20190529"
	class xmIModelServer
	{
	public:
		virtual ~xmIModelServer() {};

	public:
		/*******************************************************************************
		ϵͳ����
		*******************************************************************************/
		//	�����־��Ϣ
		virtual void Log(xmLog::ELogLevel eLevel, const char* strContent) = 0;


		/*******************************************************************************
		����ϵͳ����
		*******************************************************************************/
		//	��ȡ����״̬
		virtual unsigned int GetSimulateState(void) const = 0;
		//	��ȡ��ǰ���汶��
		virtual int GetSimulateSpeed(void) const = 0;
		//	��ȡ��ǰ�ɷ�����ͳһ��ϵͳʱ�䣬��λ��ȡ����ϵͳ
		virtual time_t GetSystemTime(void) const = 0;
		//	��ȡ��ǰ�������������λ�����ĸ���
		virtual size_t GetClickCount(void) const = 0;
		//	��ȡÿ��������ĵ�ʱ�䣬�ɷ���ϵͳ��������λ������
		virtual unsigned int GetClickCycle(void) const = 0;
		//	��ȡģ�����õ��������ڣ���ʱ�䣬��һ����ģ��ʵ������ʱ�䡣��λ������
		virtual unsigned int GetDriveCycle(void) const = 0;
		//	��ȡÿ���������ڵ�ʵ�ʽ�������GetClickCycle() �� GetDriveClick() = ʵ������ʱ�䣬��λ����������
		virtual unsigned int GetDriveClick(void) const = 0;

		/*******************************************************************************
		ʵ������
		*******************************************************************************/
		//	��ȡģ��ʵ������
		virtual const xmString& InstanceName(void) const = 0;


		/*******************************************************************************
		���ݷ���
		*******************************************************************************/
		//	���ݱ���
		virtual size_t InnerDataCount(void) const = 0;
		virtual const xmString& InnerDataName(size_t uPos) const = 0;
		virtual const char* InnerDataAttr(size_t uPos, const char* strAttrName) const = 0;
		virtual const char* InnerDataAttr(const xmString& strDataName, const char* strAttrName) const = 0;

		virtual size_t InputDataCount(void) const = 0;
		virtual const xmString& InputDataName(size_t uPos) const = 0;
		virtual const char* InputDataAttr(size_t uPos, const char* strAttrName) const = 0;
		virtual const char* InputDataAttr(const xmString& strDataName, const char* strAttrName) const = 0;

		virtual size_t OutputDataCount(void) const = 0;
		virtual const xmString& OutputDataName(size_t uPos) const = 0;
		virtual const char* OutputDataAttr(size_t uPos, const char* strAttrName) const = 0;
		virtual const char* OutputDataAttr(const xmString& strDataName, const char* strAttrName) const = 0;

		//	��ģ��ʹ�õ����ݷ��ʽӿڣ�strDataPath������Ϊ���ݵ�ģ�����ƣ�Ҳ�����÷��š�.��ֱ�ӷ���
		//	�ṹ�������е����ԣ���:"�칬״̬.λ����Ϣ.X��"
		//	�����������ݣ����ģ�͸ı�����ֵ��������Input����ʱ���ᱻϵͳ���ݸı�
		virtual xmValue InnerData(size_t uIndex) const = 0;
		virtual xmValue InnerData(const xmString& strDataPath) const = 0;
		virtual xmValue InputData(size_t uIndex) const = 0;
		virtual xmValue InputData(const xmString& strDataPath) const = 0;
		virtual xmValue OutputData(size_t uIndex) const = 0;
		virtual xmValue OutputData(const xmString& strDataPath) const = 0;
		virtual xmValue ModelData(const xmString& strDataPath, xmEIOType& ioType) const = 0;
		virtual xmValue ModelData(const xmString& strDataPath) const = 0;

		//	����ʹ�ýӿڱ���
		//	�Ͻ���ģ�ͻص������У�������OnLoad��OnUnload��ʹ�����б����ӿ�
		//	����ģ�����߳̽��м���ʱ������Ҫʹ�����к��������ݽ��б�����
		virtual xmRWLock& InnerCacheLock(void) = 0;
		virtual xmRWLock& InputCacheLock(void) = 0;
		virtual xmRWLock& OutputCacheLock(void) = 0;


		/*******************************************************************************
		�����
		*******************************************************************************/
		//	�����
		virtual size_t GroupCount(void) const = 0;
		virtual const xmString& GroupName(size_t uPos) const = 0;
		virtual xmEIOType GroupType(size_t uPos) const = 0;
		virtual const char* GroupAttr(size_t uPos, const char* strAttrName) const = 0;
		virtual const char* GroupAttr(const xmString& strGroupName, const char* strAttrName) const = 0;
		virtual size_t GroupDataCount(size_t uPos) const = 0;
		virtual const xmString& GroupDataName(size_t uPos, size_t uIndex) const = 0;
		//	��ȡ��������ļ���״̬
		virtual bool  GetGroupEnabled(const xmString& strGroupName) = 0;
		virtual xmRet SetGroupEnabled(const xmString& strGroupName, bool bIsEnable) = 0;


		/*******************************************************************************
		����/������Ʒ���
		*******************************************************************************/
		//	ģ���������IO�������κ����ƣ�������ָ�����Ƿ�Ϊ��Ծ״̬��IOΪ�첽ִ��
		//	����IOʱ��ֻ��ָ��������������ݣ�����ָ������������
		virtual xmRet ApplyGroupIO(const xmString& strGroupName) = 0;
		virtual xmRet ApplyDataInput(const xmString& strDataName) = 0;
		virtual xmRet ApplyDataOutput(const xmString& strDataName) = 0;

		//	ģ���ֶ�����IO��û�н��������������������κ����ƣ�������ָ�����Ƿ�Ϊ��Ծ״̬��IOΪͬ��ִ��
		//	�ֶ�IOʱ��ֻ��ָ��������������ݣ�����ָ������������
		virtual xmRet ManualGroupIO(const xmString& strGroupName, bool bLockData = false) = 0;
		virtual xmRet ManualDataInput(const xmString& strDataName, bool bLockData = false) = 0;
		virtual xmRet ManualDataOutput(const xmString& strDataName, bool bLockData = false) = 0;

	public:
		//	xmIModelServer�ӿڰ汾
		//	�û�����Ҫ�޸ģ�������UMSF�Խӿڰ汾�ıȶ�
		virtual const char* InterfaceVersion(void) const { return xmIMODELSERVER_VERSION; };

	protected:
		xmIModelServer() {};
	};

#define xmIMODEL_VERSION "V5.0.00_20190412"
	class xmIModel : public xmUncopyable
	{
	public:
		xmIModel(xmIModelServer* pServer) : m_pServer(pServer) {};
		virtual ~xmIModel(void) {};

	public:
		virtual xmRet OnLoad(const char* strDataFile) { return xmE_SUCCESS; };
		virtual void OnUnload(void) {};
		virtual bool IsReady(void) = 0;

		//	���лص������������������UMSF������д����
		//	����������Ӧ�ص�����
		virtual void OnStart(void) {};
		virtual void OnFinish(void) {};
		virtual void OnFreeze(void) {};
		virtual void OnUnfreeze(void) {};
		virtual void OnSpeed(int nSpeed) {};
		virtual void OnCommand(const xmString& cmdName, const xmValue& cmdParam) {};

		//  �����ӿڻص�����
		virtual void OnDrive(unsigned long uClick) {};

		//	ģ�ͻ��������ϵͳ�������ݽ����Ļص�����
		virtual void OnPrepareGroupInput(const char* strGroupName) {};
		virtual void OnFinishGroupInput(const char* strGroupName, bool isDone) {};
		virtual void OnPrepareGroupOutput(const char* strGroupName) {};
		virtual void OnFinishGroupOutput(const char* strGroupName, bool isDone) {};
		virtual void OnApplyGroupIO(const char* strGroupName, bool isDone) {};
		virtual void OnApplyDataIO(const char* strDataName, bool isDone) {};

		//  ״̬��Ϣ
		virtual xmString GetVersion(void) { return NULL; };
		virtual int GetState(void) { return 0; };
		virtual int GetLastError(void) { return xmE_SUCCESS; };
		virtual xmString PrintLastError(void) { return NULL; };

	public:
		//	xmIModel�ӿڰ汾
		//	�û�����Ҫ�޸ģ�������UMSF�Խӿڰ汾�ıȶ�
		virtual const char* InterfaceVersion(void) const { return xmIMODEL_VERSION; };

	protected:
		xmIModelServer* Server() const
		{
			return m_pServer;
		}
	private:
		xmIModelServer* const m_pServer;
	};
}   //  namespace ssa
#endif  //  __SSA_UMSF_IMODEL_H

