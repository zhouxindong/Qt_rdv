#ifndef __SSA_UMSF_MDATA_H
#define __SSA_UMSF_MDATA_H
#include "mclass.h"

namespace tinyxml2
{
	class XMLElement;
}
namespace ssa
{
	class xmMdi;
	class xmModelData
	{
		friend xmMdi;
	public:
		xmModelData(tinyxml2::XMLElement* xmlElement) : m_pModelClass(NULL), m_pInitValue(NULL), m_xmlElement(xmlElement) {};
		~xmModelData()
		{
			if (m_pInitValue != NULL)
			{
				delete m_pInitValue;
			}
		};

		const xmString& Name() const
		{
			return m_strName;
		}
		size_t Size() const
		{
			return m_pInitValue->Size();
		}
		xmEDataType Type() const
		{
			return m_pInitValue->Type();
		}
		xmString TypeName() const
		{
			xmEDataType eType = Type();
			if (eType == xmDT_STRUCT)
			{
				return m_pModelClass->Name();
			}
			else if (eType == xmDT_BUFFER)
			{
				return xmStringUtil::Format("%d", m_pInitValue->Size());
			}
			else
			{
				return xmTypeName(Type());
			}
		}

		const xmValue& InitValue() const
		{
			return *m_pInitValue;
		}
		const char* Attribute(const char* strAttrName) const;


		const xmString& PrintXML() const;

	protected:
		xmString m_strName;					//	数据名称
		const xmModelClass* m_pModelClass;	//	记录类结构
		const xmValue* m_pInitValue;		//	使用上述结构的默认初始值

		tinyxml2::XMLElement* const m_xmlElement;	//	记录该数据的XML元素
	private:
		mutable xmString m_strPrint;
	};
}
#endif  //  __SSA_UMSF_MDATA_H

