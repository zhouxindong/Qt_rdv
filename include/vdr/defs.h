#pragma once

#ifndef __SSA_VDR_DEFS_H
#define __SSA_VDR_DEFS_H

namespace ssa
{
	/**
	*  �ڵ�Ȩ�����ͣ�AP������Ȩ�����͡�
	*/
	typedef enum __tagAPAuthority
	{
		xmEAPA_NOTHING = 0,     /**< δ���塣 */
		xmEAPA__OBSERVER,		/**< �۲졣 */	
		xmEAPA__WORKER,		    /**< ������ */	
		xmEAPA__CONTROLLER,	    /**< ���ơ� */	
		xmEAPA__GOD,			/**< ������ */	
		xmEAPA__MAX,
	} xmEAPAuthority;

	/**
	*  �����ڴ�ͬ���ķ���
	*/
	typedef enum __tagSyncDirection
	{
		xmESD_UNKOWN = 0,	        /**< ��ʾ�����巽�� */	
		xmESD_TOCLIENT,		        /**< ��ĳһ���ͻ��˵��� */
		xmESD_TOCLIENTS,		    /**< ��ͻ����ǵ��� */
		xmESD_OUTDIRBEGIN,	        /**< ��ʾ���ⷽ��ģʽ��ʼ�� */	
		xmESD_TOSERVER,		        /**< ����������� */	
		xmESD_DOUBLEDIRECTION,		/**< ��˫�� */
		xmEAS_BROADCAST,		    /**< ֱ�������н����߹㲥�� */
	}xmESyncDirection;

	/**
	*  �Ự���͡�
	*/
	typedef enum __tagSessionType
	{
		xmEST_LOGIN = 1,		    /**< ע�ἰϵͳ��ʼ�����̡� */	
		xmEST_TICK,		            /**< ʱ���źš� */

		xmEST_MULTISESSION_BEGAIN = 100,
		xmEST_VALSYNC,		        /**< ��ֵͬ���� */
		xmEST_BULLETIN,             /**< �������Ϣ�� */
		xmEST_PUBSUB,		        /**< �������ġ� */

		xmEST_ADMIN_BEGAIN = 200,
		xmEST_LOG,                  /**< ��־�� */
		xmEST_MAX,
	} xmESessionType;

#define xmMAX_PKG_LENGTH        64*1024     /**< �������ݰ�����,Ϊ����Ӧ����UDP�ĳ���Ҫ�� */
#define xmMAX_SINGLE_DATA_VALUE_LENGTH 63*1024     /**< ÿ�����ݶ�Ӧֵ���ĳ��ȣ���������ˣ���Ҫ�û����������зֽ⴦�� */

#define xmMAX_DATASET_CABILITY  unsigned int(((unsigned int)0xFFFFFFFF/2) - 1 )     /**< ������ɵ����ݼ������� */

#define xmMAX_WAITING_TIME      600000     /**< ��ѯʱ�����ȴ�ʱ�䣬��λms�� */

#define xmVERSION               000900      /**< 00��汾�� 09�а汾�� 00С�汾�š� */

}

#endif
