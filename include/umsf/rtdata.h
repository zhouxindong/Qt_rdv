#ifndef __SSA_UMSF_RTDATA_H
#define __SSA_UMSF_RTDATA_H
//#include "processor.h"
//#include "isystem.h"
#include "udefine.h"
#include "publicres.h"
namespace ssa
{
	//	��������ʱ��ģ�����ݣ�����ʱ���ݿ���Ҫ�����ϵͳ��ڵ����ݽ���ƥ��
	//	����ʱ���ݵ�IOֻ��������Ϊ��λ���������뵽���ԡ�
	class xmModelData;
	class xmRuntimeData
	{
	public:
		static xmRuntimeData* CreateRuntimeData(xmEIOType ioType, const xmModelData* pModelData);
		virtual ~xmRuntimeData() 
		{
		};

		//	����Buffer���ӣ�������ʹ�õ��ڴ���MRTC�еĻ�����������
		void SetLinkBuffer(void* pBuffer)
		{
			m_CacheValue.Link(pBuffer, true);
		}

		//	���ݶ���ģ�͵�����
		const xmString& DataName() const;
		//	��ȡ������ģ������XML�ļ��е�һ������
		const char* DataAttr(const char* strAttrName) const;
		//	���ݴ�С
		size_t DataSize() const
		{
			return m_CacheValue.Size();
		}
		//	������ģ�ͻ����е���ֵ������ֵ��ģ��ֱ���ܹ�������
		xmValue DataValue() const
		{
			return m_CacheValue.PropertyValue();
		}
		//	��ȡ��ʼֵ����ʼֵ�Ƕ���ģ�ͻ���ĳ�ʼֵ
		const xmValue& InitValue() const;
		//	���Ի��渴λ��ƥ��ֵ���踴λ
		void DataReset();

		//	ģ������ƥ��������
		const xmString& MatchName() const
		{
			return m_strMatchName;
		}
		xmEDataMatchTarget MatchTarget() const
		{
			return m_eMatchTarget;
		}

		//	ģ�������ڷ���ϵͳ�е�����·����ͨ����·���������ݶ�д
		const xmString& SystemPath() const
		{
			return m_strSystemPath;
		}
		//	ģ�������ڷ���ϵͳ�е���ֵ
		xmValue SystemValue() const
		{
			if (m_pSystemValue.IsNoNULL())
			{
				xmAssert(m_pProcessor != NULL);
				return m_pSystemValue->PropertyValue();
			}
			else
			{
				xmAssert(m_pProcessor == NULL);
				return m_CacheValue.PropertyValue();
			}
		}

		//	��������ƥ�䣬��ֻ��ƥ��һ�Ρ�ƥ�����ݰ������������ơ����͡���ʼֵ��Ԥ������������
		//	�������ݵ�matchName����������·��
		//	������ݵ�matchNameֻ��������
		//	�ڲ�����ֻ��ƥ��pInitValue
		void SetMatchInfo(xmEDataMatchTarget eMatchTarget, const xmString& matchName, const xmValue* pInitValue, xmIProcessor* pProcessor);
		//	�����������·����ֻ�������������
		void SetCombinePath(const xmString& combinePath);

		void DataIO(xmPublicResource* pPubRes)
		{
			if (m_pSystemValue.IsNoNULL())
			{
				DataIO(pPubRes, *m_pSystemValue, m_CacheValue);
			}
			else
			{
				DataIO(pPubRes, xmValue(), m_CacheValue);
			}
		}
		virtual void DataIO(xmPublicResource* pPubRes, xmValue& systemValue, xmValue& cacheValue) = 0;
		virtual xmEIOType IOType() const = 0;

		xmString PrintInfo() const;
		const xmString& PrintXml() const;
	protected:
		xmRuntimeData(const xmModelData* pModelData);


		//	������ģ���е�����
		const xmModelData* const m_pModelData;
		//	�����ڻ����е���ֵ
		xmValue m_CacheValue;
		//	ƥ���Ļ����еĳ�ʼֵ
		xmPtr<xmValue> m_pInitValue;

		//	������ƥ������������ϵͳ����·���ֱ�洢�����Լ򵥡����ٵ�ʵ�ֶ��·�����
		//	����ƥ��Ŀ��
		xmEDataMatchTarget m_eMatchTarget;
		//	ģ������ƥ�����ƣ�����ƥ�����Ƽ������·��������ϵͳ����·��
		xmString m_strMatchName;
		//	ģ������ƥ�䵽����ϵͳʱ��ƥ������Ĭ����ģ��������ͬ
		xmString m_strSystemPath;
		//	Ԥ����������Ԥ����������
		xmIProcessor* m_pProcessor;
		xmPtr<xmValue> m_pSystemValue;

		//	��װ�˶�Ԥ�������ͷ���ϵͳ��ʹ�ýӿ�
		//	���ִ�����׳��쳣
		void iProcessor_Model2System(const xmValue& modelValue, xmValue& systemValue);
		void iProcessor_System2Model(const xmValue& systemValue, xmValue& modelValue);
		void iSystem_GetValue(xmPublicResource* pPubRes, xmValue& dataValue);
		void iSystem_SetValue(xmPublicResource* pPubRes, const xmValue& dataValue);
		//	�˴������޷�ƥ�䡣��Ϊ�е���������ֱ��ʹ�õ��࣬�����滻�������������ʹ�õ��࣬���޷��滻��
		//	���ƥ�䣬ֻ��ͨ��Ԥ������
	};
}   //  namespace ssa
#endif  //  __SSA_UMSF_RTDATA_H

