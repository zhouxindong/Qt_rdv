#pragma once

#ifndef __VDR_CONFIG_H
#define __VDR_CONFIG_H

#include "configglobal.h"
#include "../base/base.h"
#include "../vdr/vdr.h"
using namespace ssa;

#include <vector>
typedef std::vector<xmData> DataAttrVector;

typedef struct __tagDataSetAttrItem {
	std::string dsName;
	struct xmDataSetAttr dsAttr;
	DataAttrVector vecDataAttr;
} DataSetAttrItem;
typedef std::vector<DataSetAttrItem*> DSAttrITemVector;
typedef std::vector<std::string> VdrNameVector;

class xmCONFIG_EXPORT xmVDRConfig
{
public:
	xmVDRConfig();
	~xmVDRConfig();

public:	
	xmEVDRCommProxyType Open(std::string vdrFile);
	bool GetLanVDRAttr(xmMCastVDRAttr& vdrAttr);
	bool GetLocalVDRAttr(xmLocalVDRAttr& vdrAttr);
	bool GetDSAItemVector(DSAttrITemVector& dsaiVector);
	void ReleaseDSAItemVector(DSAttrITemVector& dsaiVector);
	bool GetApDataSet(std::string& strName);
	bool GetApSensDatas(VdrNameVector& vecNames);
	void Save(std::string saveFile, std::string apName, VdrNameVector& senstives, DSAttrITemVector& datasets, xmLocalVDRAttr& vdratts);
	void Save(std::string saveFile, std::string apName, VdrNameVector& senstives, DSAttrITemVector& datasets, xmMCastVDRAttr& vdratts);
private:
	void* rootVPtr;
	void* m_readerPtr;

	bool GetCommType(xmEVDRCommProxyType& commType);
	xmEVDRCommProxyType Convert2CommType(std::string& commString);
	xmEEndpointType Convert2EPType(std::string& epString);
	xmESystemState Convert2SysState(std::string& sysstateString);
	xmLocalVDRAttr::xmETBMType Convert2TBMType(std::string& tbmString);
	xmEDataSetType Convert2DataSetType(std::string& dstString);
	xmEDataType Convert2DataType(std::string& dtString);
	std::string Convert2String(xmEDataType dt);
	std::string Convert2String(xmEDataSetType dst);
	std::string Convert2String(xmLocalVDRAttr::xmETBMType tbmt);
	std::string Convert2String(xmESystemState ss);
	std::string Convert2String(xmEEndpointType ept);
	std::string Convert2String(xmEVDRCommProxyType cpt);

	bool GetDataAttr(void* dtValuePtr, struct xmData& dataAttr);
	bool GetDataAttrVector(void* daVecValuePtr, DataAttrVector& dsVec);
};

#endif // !__VDR_CONFIG_H

