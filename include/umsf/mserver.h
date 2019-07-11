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
		系统服务
		*******************************************************************************/
		//	输出日志信息
		virtual void Log(xmLog::ELogLevel eLevel, const char* strContent);


		/*******************************************************************************
		仿真系统信息
		*******************************************************************************/
		//	获取仿真状态，开始，结束，冻结，解冻、快飞、回放
		virtual unsigned int GetSimulateState(void) const;
		//	获取当前仿真倍速
		virtual int GetSimulateSpeed(void) const;
		//	获取当前由服务器统一的系统时间，单位：取决于系统
		virtual time_t GetSystemTime(void) const;
		//	获取当前网络节拍数，单位：节拍个数
		virtual size_t GetClickCount(void) const;
		//	获取每个网络节拍的时间，由仿真系统决定，单位：毫秒
		virtual unsigned int GetClickCycle(void) const;
		//	获取模型配置的驱动周期，此时间，不一定是模型实际驱动时间。单位：毫秒
		virtual unsigned int GetDriveCycle(void) const;
		//	获取每个驱动周期的实际节拍数，GetClickCycle() × GetDriveClick() = 实际驱动时间，单位：节拍数。
		virtual unsigned int GetDriveClick(void) const;


		/*******************************************************************************
		使用MRTC资源
		*******************************************************************************/
		//	获取模型实例名称
		virtual const xmString& InstanceName(void) const;

		//	获取和设置组的激活状态
		virtual bool  GetGroupEnabled(const xmString& strGroupName);
		virtual xmRet SetGroupEnabled(const xmString& strGroupName, bool bIsEnabled);

		//	供模型使用的数据访问接口，strDataPath参数，为数据的模型名称，也可以用符号“.”直接访问
		//	结构化数据中的属性，如:"天宫状态.位置信息.X轴"
		//	对于输入数据，如果模型改变其数值，当进行Input更新时，会被系统数据改变
		virtual xmValue InnerData(const xmString& strDataPath) const;
		virtual xmValue InnerData(size_t uIndex) const;
		virtual xmValue InputData(const xmString& strDataPath) const;
		virtual xmValue InputData(size_t uIndex) const;
		virtual xmValue OutputData(const xmString& strDataPath) const;
		virtual xmValue OutputData(size_t uIndex) const;
		virtual xmValue ModelData(const xmString& strDataPath, xmEIOType& ioType) const;
		virtual xmValue ModelData(const xmString& strDataPath) const;

		//	缓存使用接口保护
		virtual xmRWLock& InnerCacheLock(void);
		virtual xmRWLock& InputCacheLock(void);
		virtual xmRWLock& OutputCacheLock(void);

		//	模型申请进行IO，不受任何限制。IO为异步执行
		//	申请IO时，只能指定数据组或者数据，不能指定到数据属性
		virtual xmRet ApplyGroupIO(const xmString& strGroupName);
		virtual xmRet ApplyDataInput(const xmString& strDataName);
		virtual xmRet ApplyDataOutput(const xmString& strDataName);

		//	模型手动进行IO，不受任何限制。IO为同步执行
		//	手动IO时，只能指定数据组或者数据，不能指定到数据属性
		virtual xmRet ManualGroupIO(const xmString& strGroupName, bool bLockData = false);
		virtual xmRet ManualDataInput(const xmString& strDataName, bool bLockData = false);
		virtual xmRet ManualDataOutput(const xmString& strDataName, bool bLockData = false);

		/*******************************************************************************
		数据遍历
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

