#pragma once

#ifndef __SSA_VDR_DEFS_H
#define __SSA_VDR_DEFS_H

namespace ssa
{
	/**
	*  节点权限类型，AP被授予权限类型。
	*/
	typedef enum __tagAPAuthority
	{
		xmEAPA_NOTHING = 0,     /**< 未定义。 */
		xmEAPA__OBSERVER,		/**< 观察。 */	
		xmEAPA__WORKER,		    /**< 工作。 */	
		xmEAPA__CONTROLLER,	    /**< 控制。 */	
		xmEAPA__GOD,			/**< 超级。 */	
		xmEAPA__MAX,
	} xmEAPAuthority;

	/**
	*  设置内存同步的方向。
	*/
	typedef enum __tagSyncDirection
	{
		xmESD_UNKOWN = 0,	        /**< 表示无意义方向。 */	
		xmESD_TOCLIENT,		        /**< 向某一个客户端单向。 */
		xmESD_TOCLIENTS,		    /**< 向客户端们单向。 */
		xmESD_OUTDIRBEGIN,	        /**< 表示向外方向模式开始。 */	
		xmESD_TOSERVER,		        /**< 向服务器单向。 */	
		xmESD_DOUBLEDIRECTION,		/**< 向双向。 */
		xmEAS_BROADCAST,		    /**< 直接向所有接收者广播。 */
	}xmESyncDirection;

	/**
	*  会话类型。
	*/
	typedef enum __tagSessionType
	{
		xmEST_LOGIN = 1,		    /**< 注册及系统初始化工程。 */	
		xmEST_TICK,		            /**< 时钟信号。 */

		xmEST_MULTISESSION_BEGAIN = 100,
		xmEST_VALSYNC,		        /**< 数值同步。 */
		xmEST_BULLETIN,             /**< 公告板消息。 */
		xmEST_PUBSUB,		        /**< 发布订阅。 */

		xmEST_ADMIN_BEGAIN = 200,
		xmEST_LOG,                  /**< 日志。 */
		xmEST_MAX,
	} xmESessionType;

#define xmMAX_PKG_LENGTH        64*1024     /**< 最大的数据包长度,为了适应网络UDP的长度要求。 */
#define xmMAX_SINGLE_DATA_VALUE_LENGTH 63*1024     /**< 每个数据对应值最大的长度，如果超出了，需要用户将数据自行分解处理。 */

#define xmMAX_DATASET_CABILITY  unsigned int(((unsigned int)0xFFFFFFFF/2) - 1 )     /**< 最多容纳的数据集合数。 */

#define xmMAX_WAITING_TIME      600000     /**< 问询时的最大等待时间，单位ms。 */

#define xmVERSION               000900      /**< 00大版本号 09中版本号 00小版本号。 */

}

#endif
