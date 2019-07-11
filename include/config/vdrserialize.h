#pragma once

#ifndef __VDR_SERIALIZE_H
#define __VDR_SERIALIZE_H

#include "../base/base.h"
#include "../vdr/vdr.h"
#include "vdrconfig.h"
using namespace ssa;

/**
*  VDR�û����л�. ��VDR�е�������Ϣ���棬�����Դ������лָ�VDR��
*/
class xmCONFIG_EXPORT xmVDRSerialize
{
public:
	xmVDRSerialize();
	~xmVDRSerialize();

public:
	/**
	* ����VDR������Ϣ������Ҫ��һ��VDR���ӡ�
	* @param pVdr ��ָ�����ӵ�VDRָ�롣
	* @param dsName ��Ҫ��������ݼ����֣����Զ�����ݼ����֡�
	* @param fileName �����ļ������֡�
	*/
	bool  SaveDataSetSnapshots(xmVDR* pVdr, std::vector<std::string> dsName, const char* fileName);
	/**
	* �ָ�VDR������Ϣ������Ҫ��һ��VDR���ӡ�
	* @param pVdr ��ָ�����ӵ�VDRָ�롣
	* @param fileName �����ļ������֡�
	*/
	bool  RestoreDataSetSnapshots(xmVDR* pVdr, const char* fileName);
};

#endif // !__VDR_SERIALIZE_H

