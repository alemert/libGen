/******************************************************************************/
/*             l o g g e r   m q   m e s s a g e   c a t a l o g              */
/******************************************************************************/

#ifndef _LG_MQM_CAT_
#define _LG_MQM_CAT_

/******************************************************************************/
/*   I N C L U D E S                                                          */
/******************************************************************************/
// ---------------------------------------------------------
// system
// ---------------------------------------------------------

// ---------------------------------------------------------
// own 
// ---------------------------------------------------------

/******************************************************************************/
/*   D E F I N E S                                                            */
/******************************************************************************/
#define     LMQM_CRI_CALL         1100
#define LEV_LMQM_CRI_CALL         CRI
#define TXT_LMQM_CRI_CALL         "mq call %s failed with: %s"

#define     LMQM_ERR_CALL         1101
#define LEV_LMQM_ERR_CALL         ERR
#define TXT_LMQM_ERR_CALL         "mq call %s failed with: %s"

#define     LMQM_WAR_CALL         1102
#define LEV_LMQM_WAR_CALL         WAR
#define TXT_LMQM_WAR_CALL         "mq warning for call %s with: %s"

#define     LMQM_LOG_CALL         1103
#define LEV_LMQM_LOG_CALL         LOG
#define TXT_LMQM_LOG_CALL         "logging mq call %s with: %s"

#define     LMQM_INF_CALL         1104
#define LEV_LMQM_INF_CALL         INF
#define TXT_LMQM_INF_CALL         "logging mq call %s with: %s"

#define     LMQM_DBG_CALL         1105
#define LEV_LMQM_DBG_CALL         DBG
#define TXT_LMQM_DBG_CALL         "logging mq call %s with: %s"

#define     LMQM_UNKNOWN_DMP_STRUCT  1109
#define LEV_LMQM_UNKNOWN_DMP_STRUCT  ERR
#define TXT_LMQM_UNKNOWN_DMP_STRUCT  "unknown dump struct %4s"

#define     LMQM_QMGR_CONNECTED      1110
#define LEV_LMQM_QMGR_CONNECTED      LOG
#define TXT_LMQM_QMGR_CONNECTED      "connected to queue manager %30.30s"

#define     LMQM_Q_OPENED            1112
#define LEV_LMQM_Q_OPENED            LOG
#define TXT_LMQM_Q_OPENED            "queue %s opened"

#define     LMQM_UNKNOWN_QMGR        1113
#define LEV_LMQM_UNKNOWN_QMGR        ERR
#define TXT_LMQM_UNKNOWN_QMGR        "queue manager %s does not exists"

#define     LMQM_UNKNOWN_OBJECT      1114
#define LEV_LMQM_UNKNOWN_OBJECT      ERR
#define TXT_LMQM_UNKNOWN_OBJECT      "mq object %s does not exists"

#define     LMQM_QUEUE_EMPTY         1115
#define LEV_LMQM_QUEUE_EMPTY         WAR
#define TXT_LMQM_QUEUE_EMPTY         "no message found, queue %s is empty"

#define     LMQM_MSG_READ_CNT         1116
#define LEV_LMQM_MSG_READ_CNT         LOG
#define TXT_LMQM_MSG_READ_CNT         "%d messages read from queue %s"

#define     LMQM_INCR_MSG_BUFF      1120
#define LEV_LMQM_INCR_MSG_BUFF      INF
#define TXT_LMQM_INCR_MSG_BUFF      "increase message buffer for MQGET to %d byte"

#define     LMQM_ITEM_COUNT         1121
#define LEV_LMQM_ITEM_COUNT         DBG
#define TXT_LMQM_ITEM_COUNT         "bag item count %d"

#define     LMQM_ITEM_TYPE          1122
#define LEV_LMQM_ITEM_TYPE          DBG
#define TXT_LMQM_ITEM_TYPE          "bag item type %s"

#define     LMQM_LOG_NAME_INVALIDE  1130
#define LEV_LMQM_LOG_NAME_INVALIDE  CRI    
#define TXT_LMQM_LOG_NAME_INVALIDE  "transactional log file name invalide" 

#define     LMQM_LOG_NAME           1131
#define LEV_LMQM_LOG_NAME           LOG    
#define TXT_LMQM_LOG_NAME           "transactional log %s: %s"

#define     LMQM_ACTIVE_LOG          1132
#define LEV_LMQM_ACTIVE_LOG          LOG    
#define TXT_LMQM_ACTIVE_LOG          "transactional log %s is active"

#define     LMQM_INACTIVE_LOG        1132
#define LEV_LMQM_INACTIVE_LOG        LOG    
#define TXT_LMQM_INACTIVE_LOG        "transactional log %s is inactive"

#endif
