#ifndef __SSA_UMSF_MDI_H
#define __SSA_UMSF_MDI_H
#include "tinyxml2/tinyxml2.h"
#include "mclass.h"
#include "mdata.h"
#include "mgroup.h"
#include "mtrigger.h"
#include "udefine.h"

namespace ssa
{
	/*******************************************************************************
    �����ƣ�xmMdi
    ��  �ܣ�����Model Declare Information
    ˵  ������MRM��������MRTCʹ�á�MDI����ÿ��ģ���������ļ��������ľ�̬��Ϣ������MDI�е���Ϣ��
	       ����ģ�������������йأ������ϵͳ�޹ء�
    *******************************************************************************/
	class xmMdi
    {
    public:
		typedef std::map<xmString, xmPtr<const xmModelClass> > t_ClassMap;
		typedef std::map<xmString, xmPtr<const xmModelClass> >::const_iterator t_ClassMapIterator;
		typedef std::pair<t_ClassMapIterator, bool> t_ClassMapInsertResult;

		typedef std::map<xmString, xmPtr<const xmModelData> > t_DataMap;
		typedef std::map<xmString, xmPtr<const xmModelData> >::const_iterator t_DataMapIterator;
		typedef std::pair<t_DataMapIterator, bool> t_DataMapInsertResult;
		typedef std::map<xmString, const xmModelData*> t_DataPtrMap;
		typedef std::map<xmString, const xmModelData*>::const_iterator t_DataPtrMapIterator;

		typedef std::map<xmString, xmPtr<const xmModelGroup> > t_GroupMap;
		typedef std::map<xmString, xmPtr<const xmModelGroup> >::const_iterator t_GroupMapIterator;
		typedef std::pair<t_GroupMapIterator, bool> t_GroupMapInsertResult;
		typedef std::map<xmString, const xmModelGroup*> t_GroupPtrMap;
		typedef std::map<xmString, const xmModelGroup*>::const_iterator t_GroupPtrMapIterator;

		xmMdi(const xmString& strModelName);
        ~xmMdi(void);
		//	����XML�ļ�
		//	strFileName��ģ�������ļ����ƣ���gnc.xml
		void LoadXML(const char* strFileName);
	public:
		/*******************************************************************************
		�� MRTC ʹ�õĽӿ�
		*******************************************************************************/
		//	ģ������
		const xmString& ModelName() const
		{
			return m_strModelName;
		}
		//	��ȡ��������
		unsigned int DriveCycle() const
		{
			return m_uDriveCycle;
		}
		//	��ȡ�ڲ������롢����������ݱ�
		const std::vector<t_DataPtrMapIterator>& InnerData() const
		{
			return m_vInnerData;
		}
		const std::vector<t_DataPtrMapIterator>& InputData() const
		{
			return m_vInputData;
		}
		const std::vector<t_DataPtrMapIterator>& OutputData() const
		{
			return m_vOutputData;
		}
		//	��ȡ���롢��������������
		const std::vector<t_GroupPtrMapIterator>& InputGroup() const
		{
			return m_vInputGroup;
		}
		const std::vector<t_GroupPtrMapIterator>& OutputGroup() const
		{
			return m_vOutputGroup;
		}
		//	��ȡģ�͵ĵ�������
		bool IsRespondStart() const
		{
			return m_bIsRespondStart;
		}
		bool IsRespondFreeze() const
		{
			return m_bIsRespondFreeze;
		}
		bool IsRespondSpeed() const
		{
			return m_bIsRespondSpeed;
		}

    public:
		/*******************************************************************************
		���Խӿ�
		*******************************************************************************/
		//	��ӡDRIVE_CYCLE�ֶ���Ϣ
		xmString PrintDriveCycle() const;
		//	��ӡCLASS_DECLARE�ֶ���Ϣ
		xmString PrintClassDeclare(const xmString& strClassName = NULL) const;
		//	��ӡDATA_DECLARE�ֶ���Ϣ
		xmString PrintDataDeclare(const xmString& strDataName = NULL) const;
		//	��ӡGROUP_DECLARE�ֶ���Ϣ
		xmString PrintGroupDeclare(const xmString& strGroupName = NULL) const;
		//	��ӡSCHEDULE_CONFIG�ֶ���Ϣ
		xmString PrintScheduleConfig() const;

	private:
		//	����ʱ��
		int LoadDRIVE_CYCLE(tinyxml2::XMLElement* root);
		//	����CLASS����
		size_t LoadCLASS_DECLARE(tinyxml2::XMLElement* root);
		//	����DATA����
		size_t LoadDATA_DECLARE(tinyxml2::XMLElement* root);
		//	����GROUP����
		size_t LoadGROUP_DECLARE(tinyxml2::XMLElement* root);
		//	�����Ƿ�ɹ�
		xmRet LoadSCHEDULE_CONFIG(tinyxml2::XMLElement* root);

	private:
		//	����CLASS_DECLARE/CLASS/PROPERTY
		//	������һ��PROPERTY�ֶ����ڵĸ��ֶΣ����һ��ʹ�á�{}��������Class����JSON�ַ�������������˳�ʼֵ�������һ��
		//	ʹ�á�{}�������ĳ�ʼֵJSON�ַ��������δ�����ʼֵ����strInitJson���䡣
		void _LoadSTRUCT(tinyxml2::XMLElement* property_field, xmString& strClassJson, xmString& strInitJson);
		
		//	����DATA_DECLARE/*_DATA/DATA
		size_t _LoadDATA(tinyxml2::XMLElement* root, t_DataPtrMap& mapData, std::vector<t_DataPtrMapIterator>& vData);

		//	����GROUP_DECLARE/*_GROUP/GROUP
		size_t _LoadGROUP(tinyxml2::XMLElement* root, const t_DataPtrMap& mapData, t_GroupPtrMap& mapGroup, std::vector<t_GroupPtrMapIterator>& vGroup);

		//	����GROUP_DECLARE/*_GROUP/GROUP/TRIGGER
		xmModelTrigger* _LoadGROUP_TRIGGER(tinyxml2::XMLElement* root);

		//	����GROUP_DECLARE/*_GROUP/GROUP/DATA
		size_t _LoadGROUP_DATA(tinyxml2::XMLElement* root, std::vector<xmString>& vDataList, const t_DataPtrMap& mapData);

	private:
		tinyxml2::XMLDocument m_xmlDoc;

		const xmString m_strModelName;
		/*******************************************************************************
		XML������Ϣ
		*******************************************************************************/
		//	DRIVE_CYCLE�ֶ�
		unsigned int m_uDriveCycle;	//	��λΪ����

		//	CLASS_DECLARE�ֶ�
		t_ClassMap m_mapClassDeclare;
		std::vector<t_ClassMapIterator> m_vClassDeclare;
		//	��¼���������У������ݶ�����һ���������������
		//	keyΪ���������ƣ�valueΪ������ָ��
		t_ClassMap m_mapAnonymousClass;

		//	DATA_DECLARE�ֶΣ�ȫ��������Ϣ
		t_DataMap m_mapDataDeclare;
		std::vector<t_DataMapIterator> m_vDataDeclare;
		t_DataPtrMap m_mapInnerData;		//	��д���ڲ����ݣ�ָ����INPUT_GROUP��OUT_GROUP������������
		t_DataPtrMap m_mapInputData;		//	ֻ����������������
		t_DataPtrMap m_mapOutputData;		//	��д�������������
		std::vector<t_DataPtrMapIterator> m_vInnerData;
		std::vector<t_DataPtrMapIterator> m_vInputData;
		std::vector<t_DataPtrMapIterator> m_vOutputData;

		//	GROUP_DECLARE�ֶΣ�ȫ������IO������Ϣ
		t_GroupMap m_mapGroupDeclare;
		std::vector<t_GroupMapIterator> m_vGroupDeclare;
		t_GroupPtrMap m_mapInputGroup;		//	����������
		t_GroupPtrMap m_mapOutputGroup;		//	���������
		std::vector<t_GroupPtrMapIterator> m_vInputGroup;
		std::vector<t_GroupPtrMapIterator> m_vOutputGroup;

		//	SCHEDULE_CONFIG�ֶΣ�����ģ�͵ĵ�����Ϣ
		bool m_bIsRespondStart;
		bool m_bIsRespondFreeze;
		bool m_bIsRespondSpeed;
	};
}
#endif  //  __SSA_UMSF_MDI_H

