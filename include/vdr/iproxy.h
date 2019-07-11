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
	* 代理的编号，用户使用10000以上的编号。
	*/
	typedef enum __tagProxyUserID
	{
		xmEPUID_COMM_BEGAIN  = 0,     /**< 通信协议编码号起始ID。为了不重复定义，
									  各种类型的通信协议的ID与通信类型的定义一致，具体参见xmEVDRCommProxyType。 */
		xmEPUID_LOGIC_BEGAIN = 100,   /**< 事物处理协议编码号起始ID。 */
		xmEPUID_SENSMSGPROXY,         /**< 敏感消息的处理业务ID。*/
		xmEPUID_SYNC_LOGIC,           /**< 同步逻辑关系处理业务ID。*/

		xmEPUID_USER_BEGAIN  = 10000, /**< 用户自己定义的协议编码号起始ID。 */

	} xmEProxyUserID;

	//需要一个ID号作为工厂创建代理的标志，具体编号的分类参照xmEProxyUserID。
	virtual int  GetProxyID() = 0;
	virtual bool Initialize(void*) = 0;
	virtual bool IsValid() { return m_bValid; };
	virtual void SetValid(bool bValid) { m_bValid = bValid; };

private:
	bool         m_bValid;

};

#endif
