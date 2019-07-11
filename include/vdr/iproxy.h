#pragma once
#ifndef __SSA_IPROXY_H
#define __SSA_IPROXY_H

class xmIProxy
{
public:
	xmIProxy() { m_bValid = true; };
	~xmIProxy() {};

public:
	/**
	* ����ı�ţ��û�ʹ��10000���ϵı�š�
	*/
	typedef enum __tagProxyUserID
	{
		xmEPUID_COMM_BEGAIN  = 0,     /**< ͨ��Э��������ʼID��Ϊ�˲��ظ����壬
									  �������͵�ͨ��Э���ID��ͨ�����͵Ķ���һ�£�����μ�xmEVDRCommProxyType�� */
		xmEPUID_LOGIC_BEGAIN = 100,   /**< ���ﴦ��Э��������ʼID�� */
		xmEPUID_SENSMSGPROXY,         /**< ������Ϣ�Ĵ���ҵ��ID��*/
		xmEPUID_SYNC_LOGIC,           /**< ͬ���߼���ϵ����ҵ��ID��*/

		xmEPUID_USER_BEGAIN  = 10000, /**< �û��Լ������Э��������ʼID�� */

	} xmEProxyUserID;

	//��Ҫһ��ID����Ϊ������������ı�־�������ŵķ������xmEProxyUserID��
	virtual int  GetProxyID() = 0;
	virtual bool Initialize(void*) = 0;
	virtual bool IsValid() { return m_bValid; };
	virtual void SetValid(bool bValid) { m_bValid = bValid; };

private:
	bool         m_bValid;

};

#endif
