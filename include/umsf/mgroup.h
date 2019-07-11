#ifndef __SSA_UMSF_MGROUP_H
#define __SSA_UMSF_MGROUP_H
#include "mtrigger.h"

namespace tinyxml2
{
	class XMLElement;
}
namespace ssa
{
	//	定义数据组描述
	class xmMdi;
	class xmModelGroup
	{
		friend xmMdi;
	public:
		xmModelGroup(tinyxml2::XMLElement* xmlElement) : m_pTrigger(NULL), m_bIsEnabled(true), m_xmlElement(xmlElement) {};
		virtual ~xmModelGroup() 
		{
			if (m_pTrigger != NULL)
			{
				delete m_pTrigger;
			}
		};
		const xmString& Name() const
		{
			return m_strName;
		}
		const char* Attribute(const char* strAttrName) const;

		const xmString& Data(size_t i) const
		{
			return m_DataList[i];
		}
		const std::vector<xmString>& DataList() const
		{
			return m_DataList;
		}
		const xmModelTrigger* Trigger() const
		{
			return m_pTrigger;
		}
		bool IsEnabled() const
		{
			return m_bIsEnabled;
		}

	public:
		const xmString& PrintXML() const;

	protected:
		xmString m_strName;
		std::vector<xmString> m_DataList;
		xmModelTrigger* m_pTrigger;
		bool m_bIsEnabled;

		tinyxml2::XMLElement* const m_xmlElement;	//	记录该数据组的XML元素
	private:
		mutable xmString m_strPrint;
	};
}   //  namespace ssa
#endif  //  __SSA_UMSF_MGROUP_H

