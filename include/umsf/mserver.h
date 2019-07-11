#ifndef __SSA_UMSF_MSERVER_H
#define __SSA_UMSF_MSERVER_H
#include "imodel.h"

namespace ssa
{
	class xmMrtc;
	class xmModelServer : public xmIModelServer
    {
	public:
		xmModelServer(xmMrtc* pMrtc) : m_pMrtc(pMrtc) {};
		virtual ~xmModelServer() {};

	public:
		/*******************************************************************************
		ϵͳ����
		*******************************************************************************/
		//	�����־��Ϣ
		virtual void Log(xmLog::ELogLevel eLevel, const char* strContent);


		/*******************************************************************************
		����ϵͳ��Ϣ
		*******************************************************************************/
		//	��ȡ����״̬����ʼ�����������ᣬ�ⶳ����ɡ��ط�
		virtual unsigned int GetSimulateState(void) const;
		//	��ȡ��ǰ���汶��
		virtual int GetSimulateSpeed(void) const;
		//	��ȡ��ǰ�ɷ�����ͳһ��ϵͳʱ�䣬��λ��ȡ����ϵͳ
		virtual time_t GetSystemTime(void) const;
		//	��ȡ��ǰ�������������λ�����ĸ���
		virtual size_t GetClickCount(void) const;
		//	��ȡÿ��������ĵ�ʱ�䣬�ɷ���ϵͳ��������λ������
		virtual unsigned int GetClickCycle(void) const;
		//	��ȡģ�����õ��������ڣ���ʱ�䣬��һ����ģ��ʵ������ʱ�䡣��λ������
		virtual unsigned int GetDriveCycle(void) const;
		//	��ȡÿ���������ڵ�ʵ�ʽ�������GetClickCycle() �� GetDriveClick() = ʵ������ʱ�䣬��λ����������
		virtual unsigned int GetDriveClick(void) const;


		/*******************************************************************************
		ʹ��MRTC��Դ
		*******************************************************************************/
		//	��ȡģ��ʵ������
		virtual const xmString& InstanceName(void) const;

		//	��ȡ��������ļ���״̬
		virtual bool  GetGroupEnabled(const xmString& strGroupName);
		virtual xmRet SetGroupEnabled(const xmString& strGroupName, bool bIsEnabled);

		//	��ģ��ʹ�õ����ݷ��ʽӿڣ�strDataPath������Ϊ���ݵ�ģ�����ƣ�Ҳ�����÷��š�.��ֱ�ӷ���
		//	�ṹ�������е����ԣ���:"�칬״̬.λ����Ϣ.X��"
		//	�����������ݣ����ģ�͸ı�����ֵ��������Input����ʱ���ᱻϵͳ���ݸı�
		virtual xmValue InnerData(const xmString& strDataPath) const;
		virtual xmValue InnerData(size_t uIndex) const;
		virtual xmValue InputData(const xmString& strDataPath) const;
		virtual xmValue InputData(size_t uIndex) const;
		virtual xmValue OutputData(const xmString& strDataPath) const;
		virtual xmValue OutputData(size_t uIndex) const;
		virtual xmValue ModelData(const xmString& strDataPath, xmEIOType& ioType) const;
		virtual xmValue ModelData(const xmString& strDataPath) const;

		//	����ʹ�ýӿڱ���
		virtual xmRWLock& InnerCacheLock(void);
		virtual xmRWLock& InputCacheLock(void);
		virtual xmRWLock& OutputCacheLock(void);

		//	ģ���������IO�������κ����ơ�IOΪ�첽ִ��
		//	����IOʱ��ֻ��ָ��������������ݣ�����ָ������������
		virtual xmRet ApplyGroupIO(const xmString& strGroupName);
		virtual xmRet ApplyDataInput(const xmString& strDataName);
		virtual xmRet ApplyDataOutput(const xmString& strDataName);

		//	ģ���ֶ�����IO�������κ����ơ�IOΪͬ��ִ��
		//	�ֶ�IOʱ��ֻ��ָ��������������ݣ�����ָ������������
		virtual xmRet ManualGroupIO(const xmString& strGroupName, bool bLockData = false);
		virtual xmRet ManualDataInput(const xmString& strDataName, bool bLockData = false);
		virtual xmRet ManualDataOutput(const xmString& strDataName, bool bLockData = false);

		/*******************************************************************************
		���ݱ���
		*******************************************************************************/
		virtual size_t InnerDataCount(void) const;
		virtual const xmString& InnerDataName(size_t uPos) const;
		virtual const char* InnerDataAttr(size_t uPos, const char* strAttrName) const;
		virtual const char* InnerDataAttr(const xmString& strDataName, const char* strAttrName) const;

		virtual size_t InputDataCount(void) const;
		virtual const xmString& InputDataName(size_t uPos) const;
		virtual const char* InputDataAttr(size_t uPos, const char* strAttrName) const;
		virtual const char* InputDataAttr(const xmString& strDataName, const char* strAttrName) const;

		virtual size_t OutputDataCount(void) const;
		virtual const xmString& OutputDataName(size_t uPos) const;
		virtual const char* OutputDataAttr(size_t uPos, const char* strAttrName) const;
		virtual const char* OutputDataAttr(const xmString& strDataName, const char* strAttrName) const;

		virtual size_t GroupCount(void) const;
		virtual const xmString& GroupName(size_t uPos) const;
		virtual const char* GroupAttr(size_t uPos, const char* strAttrName) const;
		virtual const char* GroupAttr(const xmString& strGroupName, const char* strAttrName) const;

		virtual xmEIOType GroupType(size_t uPos) const;
		virtual size_t GroupDataCount(size_t uPos) const;
		virtual const xmString& GroupDataName(size_t uPos, size_t uIndex) const;
	private:
		xmMrtc* const m_pMrtc;
	};
}   //  namespace ssa
#endif  //  __SSA_UMSF_MSERVER_H

