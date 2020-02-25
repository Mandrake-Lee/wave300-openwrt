/******************************************************************************

                               Copyright (c) 2012
                            Lantiq Deutschland GmbH

  For licensing information, see the file 'LICENSE' in the root folder of
  this software module.

******************************************************************************/
/*
 * $Id$
 *
 * 
 *
 * Core module definitions
 *
 */
#ifndef __CORE_H__
#define __CORE_H__

/** 
*\file core.h 
*\brief Core module acting as mediator to organize all driver activities
*/

#include "mtlk_vap_manager.h"

struct nic;

#include "mtlkmib.h"

#include "addba.h"
#include "mcast.h"
#include "mtlkqos.h"


#include "mtlkflctrl.h"
#include "aocs.h"
#include "dfs.h"
#include "rod.h"
#include "stadb.h"
#include "wds.h" 

#ifdef MTCFG_RF_MANAGEMENT_MTLK
#include "mtlk_rfmgmt.h"
#endif
#include "mtlk_serializer.h"

#include "mtlk_core_iface.h"

#include "l2nat.h"
#include "mtlk_coc.h"
#ifdef MTCFG_PMCU_SUPPORT
#include "mtlk_pcoc.h"
#endif /*MTCFG_PMCU_SUPPORT*/
#include "scan.h"
#include "channels.h"
#include "mib_osdep.h"
#include "core_priv.h"
#include "mtlk_reflim.h"

#include "mtlk_wss.h"

// the sane amount of time dedicated to MAC to perform
// connection or BSS activation
#define CONNECT_TIMEOUT 10000 /* msec */
#define ASSOCIATE_FAILURE_TIMEOUT 3000 /* msec */

#define INVALID_DEACTIVATE_TIMESTAMP ((uint32)-1)

// amount of time - needed by firmware to send vap removal
// indication to the driver.
#define VAP_REMOVAL_TIMEOUT 10000 /* msec */
enum ts_priorities {
  TS_PRIORITY_BE,
  TS_PRIORITY_BG,
  TS_PRIORITY_VIDEO,
  TS_PRIORITY_VOICE,
  TS_PRIORITY_LAST
};

/* U-APSD */
#define UAPSD_ENABLED_DEFAULT TRUE

/***************************************************/

typedef struct _wme_class_cfg_t
{
  uint32 cwmin;
  uint32 cwmax;
  uint32 aifsn;
  uint32 txop;
} wme_class_cfg_t;

typedef struct _wme_cfg_t
{
  wme_class_cfg_t wme_class[NTS_PRIORITIES];
} wme_cfg_t;

typedef struct _mtlk_core_cfg_t
{
  mtlk_addba_cfg_t              addba;
  wme_cfg_t                     wme_bss;
  wme_cfg_t                     wme_ap;
  BOOL                          is_hidden_ssid;
} mtlk_core_cfg_t;

#define LOG_LOCAL_GID   GID_CORE
#define LOG_LOCAL_FID   0

typedef enum
{
  MTLK_CORE_CNT_PACKETS_SENT,
  MTLK_CORE_CNT_PACKETS_RECEIVED,
  MTLK_CORE_CNT_BYTES_SENT,
  MTLK_CORE_CNT_BYTES_RECEIVED,
  MTLK_CORE_CNT_UNICAST_PACKETS_SENT,
  MTLK_CORE_CNT_UNICAST_PACKETS_RECEIVED,
  MTLK_CORE_CNT_MULTICAST_PACKETS_SENT,
  MTLK_CORE_CNT_MULTICAST_PACKETS_RECEIVED,
  MTLK_CORE_CNT_BROADCAST_PACKETS_SENT,
  MTLK_CORE_CNT_BROADCAST_PACKETS_RECEIVED,

/* minimal statistic */
#if (!(MTLK_MTIDL_WLAN_STAT_FULL))
  MTLK_CORE_CNT_LAST,
#endif /* MTLK_MTIDL_WLAN_STAT_FULL */

  MTLK_CORE_CNT_TX_PACKETS_DISCARDED_FW,
  MTLK_CORE_CNT_RX_PACKETS_DISCARDED_DRV_TOO_OLD,
  MTLK_CORE_CNT_RX_PACKETS_DISCARDED_DRV_DUPLICATE,
  MTLK_CORE_CNT_TX_PACKETS_DISCARDED_NO_PEERS,
  MTLK_CORE_CNT_TX_PACKETS_DISCARDED_DRV_ACM,
  MTLK_CORE_CNT_TX_PACKETS_DISCARDED_EAPOL_CLONED,
  MTLK_CORE_CNT_TX_PACKETS_DISCARDED_DRV_UNKNOWN_DESTINATION_DIRECTED,
  MTLK_CORE_CNT_TX_PACKETS_DISCARDED_DRV_UNKNOWN_DESTINATION_MCAST,
  MTLK_CORE_CNT_TX_PACKETS_DISCARDED_DRV_NO_RESOURCES,
  MTLK_CORE_CNT_TX_PACKETS_DISCARDED_SQ_OVERFLOW,
  MTLK_CORE_CNT_TX_PACKETS_DISCARDED_EAPOL_FILTER,
  MTLK_CORE_CNT_TX_PACKETS_DISCARDED_DROP_ALL_FILTER,
  MTLK_CORE_CNT_TX_PACKETS_DISCARDED_TX_QUEUE_OVERFLOW,
  MTLK_CORE_CNT_802_1X_PACKETS_RECEIVED,
  MTLK_CORE_CNT_802_1X_PACKETS_SENT,
  MTLK_CORE_CNT_PAIRWISE_MIC_FAILURE_PACKETS,
  MTLK_CORE_CNT_GROUP_MIC_FAILURE_PACKETS,
  MTLK_CORE_CNT_UNICAST_REPLAYED_PACKETS,
  MTLK_CORE_CNT_MULTICAST_REPLAYED_PACKETS,
  MTLK_CORE_CNT_FWD_RX_PACKETS,
  MTLK_CORE_CNT_FWD_RX_BYTES,
  MTLK_CORE_CNT_MULTICAST_BYTES_SENT,
  MTLK_CORE_CNT_MULTICAST_BYTES_RECEIVED,
  MTLK_CORE_CNT_BROADCAST_BYTES_SENT,
  MTLK_CORE_CNT_BROADCAST_BYTES_RECEIVED,
  MTLK_CORE_CNT_DAT_FRAMES_RECEIVED,
  MTLK_CORE_CNT_CTL_FRAMES_RECEIVED,
  MTLK_CORE_CNT_MAN_FRAMES_RECEIVED,
  MTLK_CORE_CNT_COEX_EL_RECEIVED,
  MTLK_CORE_CNT_COEX_EL_SCAN_EXEMPTION_REQUESTED,
  MTLK_CORE_CNT_COEX_EL_SCAN_EXEMPTION_GRANTED,
  MTLK_CORE_CNT_COEX_EL_SCAN_EXEMPTION_GRANT_CANCELLED,
  MTLK_CORE_CNT_CHANNEL_SWITCH_20_TO_40,
  MTLK_CORE_CNT_CHANNEL_SWITCH_40_TO_20,
  MTLK_CORE_CNT_CHANNEL_SWITCH_40_TO_40,
  MTLK_CORE_CNT_AGGR_ACTIVE,
  MTLK_CORE_CNT_REORD_ACTIVE,
  MTLK_CORE_CNT_SQ_DPCS_SCHEDULED,
  MTLK_CORE_CNT_SQ_DPCS_ARRIVED,
  MTLK_CORE_CNT_RX_ADDBA_REQ_RECEIVED,
  MTLK_CORE_CNT_RX_ADDBA_RES_CFMD_FAIL,
  MTLK_CORE_CNT_RX_ADDBA_RES_CFMD_SUCCESS,
  MTLK_CORE_CNT_RX_ADDBA_RES_LOST,
  MTLK_CORE_CNT_RX_ADDBA_RES_NEGATIVE_SENT,
  MTLK_CORE_CNT_RX_ADDBA_RES_NOT_CFMD,
  MTLK_CORE_CNT_RX_ADDBA_RES_POSITIVE_SENT,
  MTLK_CORE_CNT_RX_ADDBA_RES_REACHED,
  MTLK_CORE_CNT_RX_ADDBA_RES_RETRANSMISSIONS,
  MTLK_CORE_CNT_RX_BAR_WITHOUT_REORDERING,
  MTLK_CORE_CNT_RX_AGGR_PKT_WITHOUT_REORDERING,
  MTLK_CORE_CNT_RX_DELBA_REQ_CFMD_FAIL,
  MTLK_CORE_CNT_RX_DELBA_REQ_CFMD_SUCCESS,
  MTLK_CORE_CNT_RX_DELBA_REQ_LOST,
  MTLK_CORE_CNT_RX_DELBA_REQ_NOT_CFMD,
  MTLK_CORE_CNT_RX_DELBA_REQ_RCV,
  MTLK_CORE_CNT_RX_DELBA_REQ_REACHED,
  MTLK_CORE_CNT_RX_DELBA_REQ_RETRANSMISSIONS,
  MTLK_CORE_CNT_RX_DELBA_REQ_SENT,
  MTLK_CORE_CNT_RX_DELBA_SENT_BY_TIMEOUT,
  MTLK_CORE_CNT_TX_ACK_ON_BAR_DETECTED,
  MTLK_CORE_CNT_TX_ADDBA_REQ_CFMD_FAIL,
  MTLK_CORE_CNT_TX_ADDBA_REQ_CFMD_SUCCESS,
  MTLK_CORE_CNT_TX_ADDBA_REQ_NOT_CFMD,
  MTLK_CORE_CNT_TX_ADDBA_REQ_SENT,
  MTLK_CORE_CNT_TX_ADDBA_RES_RCV_NEGATIVE,
  MTLK_CORE_CNT_TX_ADDBA_RES_RCV_POSITIVE,
  MTLK_CORE_CNT_TX_ADDBA_RES_TIMEOUT,
  MTLK_CORE_CNT_TX_CLOSE_AGGR_CFMD_FAIL,
  MTLK_CORE_CNT_TX_CLOSE_AGGR_CFMD_SUCCESS,
  MTLK_CORE_CNT_TX_CLOSE_AGGR_NOT_CFMD,
  MTLK_CORE_CNT_TX_CLOSE_AGGR_SENT,
  MTLK_CORE_CNT_TX_DELBA_REQ_CFMD_FAIL,
  MTLK_CORE_CNT_TX_DELBA_REQ_CFMD_SUCCESS,
  MTLK_CORE_CNT_TX_DELBA_REQ_LOST,
  MTLK_CORE_CNT_TX_DELBA_REQ_NOT_CFMD,
  MTLK_CORE_CNT_TX_DELBA_REQ_RCV,
  MTLK_CORE_CNT_TX_DELBA_REQ_REACHED,
  MTLK_CORE_CNT_TX_DELBA_REQ_RETRANSMISSIONS,
  MTLK_CORE_CNT_TX_DELBA_REQ_SENT,
  MTLK_CORE_CNT_TX_OPEN_AGGR_CFMD_FAIL,
  MTLK_CORE_CNT_TX_OPEN_AGGR_CFMD_SUCCESS,
  MTLK_CORE_CNT_TX_OPEN_AGGR_NOT_CFMD,
  MTLK_CORE_CNT_TX_OPEN_AGGR_SENT,

/* DEBUG statistic */
#if MTLK_MTIDL_WLAN_STAT_FULL
  MTLK_CORE_CNT_LAST
#endif /* MTLK_MTIDL_WLAN_STAT_FULL */

} mtlk_core_wss_cnt_id_e;

/* Statistic ALLOWED flags */
#define MTLK_CORE_CNT_TX_PACKETS_DISCARDED_FW_ALLOWED                               MTLK_WWSS_WLAN_STAT_ID_TX_PACKETS_DISCARDED_FW_ALLOWED
#define MTLK_CORE_CNT_RX_PACKETS_DISCARDED_DRV_TOO_OLD_ALLOWED                      MTLK_WWSS_WLAN_STAT_ID_RX_PACKETS_DISCARDED_DRV_TOO_OLD_ALLOWED
#define MTLK_CORE_CNT_RX_PACKETS_DISCARDED_DRV_DUPLICATE_ALLOWED                    MTLK_WWSS_WLAN_STAT_ID_RX_PACKETS_DISCARDED_DRV_DUPLICATE_ALLOWED
#define MTLK_CORE_CNT_PACKETS_SENT_ALLOWED                                          MTLK_WWSS_WLAN_STAT_ID_PACKETS_SENT_ALLOWED
#define MTLK_CORE_CNT_TX_PACKETS_DISCARDED_NO_PEERS_ALLOWED                         MTLK_WWSS_WLAN_STAT_ID_TX_PACKETS_DISCARDED_DRV_NO_PEERS_ALLOWED
#define MTLK_CORE_CNT_TX_PACKETS_DISCARDED_DRV_ACM_ALLOWED                          MTLK_WWSS_WLAN_STAT_ID_TX_PACKETS_DISCARDED_DRV_ACM_ALLOWED
#define MTLK_CORE_CNT_TX_PACKETS_DISCARDED_EAPOL_CLONED_ALLOWED                     MTLK_WWSS_WLAN_STAT_ID_TX_PACKETS_DISCARDED_DRV_EAPOL_CLONED_ALLOWED
#define MTLK_CORE_CNT_TX_PACKETS_DISCARDED_DRV_UNKNOWN_DESTINATION_DIRECTED_ALLOWED MTLK_WWSS_WLAN_STAT_ID_TX_PACKETS_DISCARDED_DRV_UNKNOWN_DESTINATION_DIRECTED_ALLOWED
#define MTLK_CORE_CNT_TX_PACKETS_DISCARDED_DRV_UNKNOWN_DESTINATION_MCAST_ALLOWED    MTLK_WWSS_WLAN_STAT_ID_TX_PACKETS_DISCARDED_DRV_UNKNOWN_DESTINATION_MCAST_ALLOWED
#define MTLK_CORE_CNT_TX_PACKETS_DISCARDED_DRV_NO_RESOURCES_ALLOWED                 MTLK_WWSS_WLAN_STAT_ID_TX_PACKETS_DISCARDED_DRV_NO_RESOURCES_ALLOWED
#define MTLK_CORE_CNT_TX_PACKETS_DISCARDED_SQ_OVERFLOW_ALLOWED                      MTLK_WWSS_WLAN_STAT_ID_TX_PACKETS_DISCARDED_DRV_SQ_OVERFLOW_ALLOWED
#define MTLK_CORE_CNT_TX_PACKETS_DISCARDED_EAPOL_FILTER_ALLOWED                     MTLK_WWSS_WLAN_STAT_ID_TX_PACKETS_DISCARDED_DRV_EAPOL_FILTER_ALLOWED
#define MTLK_CORE_CNT_TX_PACKETS_DISCARDED_DROP_ALL_FILTER_ALLOWED                  MTLK_WWSS_WLAN_STAT_ID_TX_PACKETS_DISCARDED_DRV_DROP_ALL_FILTER_ALLOWED
#define MTLK_CORE_CNT_TX_PACKETS_DISCARDED_TX_QUEUE_OVERFLOW_ALLOWED                MTLK_WWSS_WLAN_STAT_ID_TX_PACKETS_DISCARDED_DRV_TX_QUEUE_OVERFLOW_ALLOWED
#define MTLK_CORE_CNT_PACKETS_RECEIVED_ALLOWED                                      MTLK_WWSS_WLAN_STAT_ID_PACKETS_RECEIVED_ALLOWED
#define MTLK_CORE_CNT_802_1X_PACKETS_RECEIVED_ALLOWED                               MTLK_WWSS_WLAN_STAT_ID_802_1X_PACKETS_RECEIVED_ALLOWED
#define MTLK_CORE_CNT_802_1X_PACKETS_SENT_ALLOWED                                   MTLK_WWSS_WLAN_STAT_ID_802_1X_PACKETS_SENT_ALLOWED
#define MTLK_CORE_CNT_BYTES_RECEIVED_ALLOWED                                        MTLK_WWSS_WLAN_STAT_ID_BYTES_RECEIVED_ALLOWED
#define MTLK_CORE_CNT_BYTES_SENT_ALLOWED                                            MTLK_WWSS_WLAN_STAT_ID_BYTES_SENT_ALLOWED
#define MTLK_CORE_CNT_PAIRWISE_MIC_FAILURE_PACKETS_ALLOWED                          MTLK_WWSS_WLAN_STAT_ID_PAIRWISE_MIC_FAILURE_PACKETS_ALLOWED
#define MTLK_CORE_CNT_GROUP_MIC_FAILURE_PACKETS_ALLOWED                             MTLK_WWSS_WLAN_STAT_ID_GROUP_MIC_FAILURE_PACKETS_ALLOWED
#define MTLK_CORE_CNT_UNICAST_REPLAYED_PACKETS_ALLOWED                              MTLK_WWSS_WLAN_STAT_ID_UNICAST_REPLAYED_PACKETS_ALLOWED
#define MTLK_CORE_CNT_MULTICAST_REPLAYED_PACKETS_ALLOWED                            MTLK_WWSS_WLAN_STAT_ID_MULTICAST_REPLAYED_PACKETS_ALLOWED
#define MTLK_CORE_CNT_FWD_RX_PACKETS_ALLOWED                                        MTLK_WWSS_WLAN_STAT_ID_FWD_RX_PACKETS_ALLOWED
#define MTLK_CORE_CNT_FWD_RX_BYTES_ALLOWED                                          MTLK_WWSS_WLAN_STAT_ID_FWD_RX_BYTES_ALLOWED
#define MTLK_CORE_CNT_UNICAST_PACKETS_SENT_ALLOWED                                  MTLK_WWSS_WLAN_STAT_ID_UNICAST_PACKETS_SENT_ALLOWED
#define MTLK_CORE_CNT_UNICAST_PACKETS_RECEIVED_ALLOWED                              MTLK_WWSS_WLAN_STAT_ID_UNICAST_PACKETS_RECEIVED_ALLOWED
#define MTLK_CORE_CNT_MULTICAST_PACKETS_SENT_ALLOWED                                MTLK_WWSS_WLAN_STAT_ID_MULTICAST_PACKETS_SENT_ALLOWED
#define MTLK_CORE_CNT_MULTICAST_PACKETS_RECEIVED_ALLOWED                            MTLK_WWSS_WLAN_STAT_ID_MULTICAST_PACKETS_RECEIVED_ALLOWED
#define MTLK_CORE_CNT_BROADCAST_PACKETS_SENT_ALLOWED                                MTLK_WWSS_WLAN_STAT_ID_BROADCAST_PACKETS_SENT_ALLOWED
#define MTLK_CORE_CNT_BROADCAST_PACKETS_RECEIVED_ALLOWED                            MTLK_WWSS_WLAN_STAT_ID_BROADCAST_PACKETS_RECEIVED_ALLOWED
#define MTLK_CORE_CNT_MULTICAST_BYTES_SENT_ALLOWED                                  MTLK_WWSS_WLAN_STAT_ID_MULTICAST_BYTES_SENT_ALLOWED
#define MTLK_CORE_CNT_MULTICAST_BYTES_RECEIVED_ALLOWED                              MTLK_WWSS_WLAN_STAT_ID_MULTICAST_BYTES_RECEIVED_ALLOWED
#define MTLK_CORE_CNT_BROADCAST_BYTES_SENT_ALLOWED                                  MTLK_WWSS_WLAN_STAT_ID_BROADCAST_BYTES_SENT_ALLOWED
#define MTLK_CORE_CNT_BROADCAST_BYTES_RECEIVED_ALLOWED                              MTLK_WWSS_WLAN_STAT_ID_BROADCAST_BYTES_RECEIVED_ALLOWED
#define MTLK_CORE_CNT_DAT_FRAMES_RECEIVED_ALLOWED                                   MTLK_WWSS_WLAN_STAT_ID_DAT_FRAMES_RECEIVED_ALLOWED
#define MTLK_CORE_CNT_CTL_FRAMES_RECEIVED_ALLOWED                                   MTLK_WWSS_WLAN_STAT_ID_CTL_FRAMES_RECEIVED_ALLOWED
#define MTLK_CORE_CNT_MAN_FRAMES_RECEIVED_ALLOWED                                   MTLK_WWSS_WLAN_STAT_ID_MAN_FRAMES_RECEIVED_ALLOWED

#define MTLK_CORE_CNT_COEX_EL_RECEIVED_ALLOWED                                      MTLK_WWSS_WLAN_STAT_ID_NOF_COEX_EL_RECEIVED_ALLOWED
#define MTLK_CORE_CNT_COEX_EL_SCAN_EXEMPTION_REQUESTED_ALLOWED                      MTLK_WWSS_WLAN_STAT_ID_NOF_COEX_EL_SCAN_EXEMPTION_REQUESTED_ALLOWED
#define MTLK_CORE_CNT_COEX_EL_SCAN_EXEMPTION_GRANTED_ALLOWED                        MTLK_WWSS_WLAN_STAT_ID_NOF_COEX_EL_SCAN_EXEMPTION_GRANTED_ALLOWED
#define MTLK_CORE_CNT_COEX_EL_SCAN_EXEMPTION_GRANT_CANCELLED_ALLOWED                MTLK_WWSS_WLAN_STAT_ID_NOF_COEX_EL_SCAN_EXEMPTION_GRANT_CANCELLED_ALLOWED
#define MTLK_CORE_CNT_CHANNEL_SWITCH_20_TO_40_ALLOWED                               MTLK_WWSS_WLAN_STAT_ID_NOF_CHANNEL_SWITCH_20_TO_40_ALLOWED
#define MTLK_CORE_CNT_CHANNEL_SWITCH_40_TO_20_ALLOWED                               MTLK_WWSS_WLAN_STAT_ID_NOF_CHANNEL_SWITCH_40_TO_20_ALLOWED
#define MTLK_CORE_CNT_CHANNEL_SWITCH_40_TO_40_ALLOWED                               MTLK_WWSS_WLAN_STAT_ID_NOF_CHANNEL_SWITCH_40_TO_40_ALLOWED

#define MTLK_CORE_CNT_AGGR_ACTIVE_ALLOWED                                           MTLK_WWSS_WLAN_STAT_ID_AGGR_ACTIVE_ALLOWED
#define MTLK_CORE_CNT_REORD_ACTIVE_ALLOWED                                          MTLK_WWSS_WLAN_STAT_ID_REORD_ACTIVE_ALLOWED
#define MTLK_CORE_CNT_SQ_DPCS_SCHEDULED_ALLOWED                                     MTLK_WWSS_WLAN_STAT_ID_SQ_DPCS_SCHEDULED_ALLOWED
#define MTLK_CORE_CNT_SQ_DPCS_ARRIVED_ALLOWED                                       MTLK_WWSS_WLAN_STAT_ID_SQ_DPCS_ARRIVED_ALLOWED
#define MTLK_CORE_CNT_RX_ADDBA_REQ_RECEIVED_ALLOWED                                 MTLK_WWSS_WLAN_STAT_ID_RX_ADDBA_REQ_RECEIVED_ALLOWED
#define MTLK_CORE_CNT_RX_ADDBA_RES_CFMD_FAIL_ALLOWED                                MTLK_WWSS_WLAN_STAT_ID_RX_ADDBA_RES_CFMD_FAIL_ALLOWED
#define MTLK_CORE_CNT_RX_ADDBA_RES_CFMD_SUCCESS_ALLOWED                             MTLK_WWSS_WLAN_STAT_ID_RX_ADDBA_RES_CFMD_SUCCESS_ALLOWED
#define MTLK_CORE_CNT_RX_ADDBA_RES_LOST_ALLOWED                                     MTLK_WWSS_WLAN_STAT_ID_RX_ADDBA_RES_LOST_ALLOWED
#define MTLK_CORE_CNT_RX_ADDBA_RES_NEGATIVE_SENT_ALLOWED                            MTLK_WWSS_WLAN_STAT_ID_RX_ADDBA_RES_NEGATIVE_SENT_ALLOWED
#define MTLK_CORE_CNT_RX_ADDBA_RES_NOT_CFMD_ALLOWED                                 MTLK_WWSS_WLAN_STAT_ID_RX_ADDBA_RES_NOT_CFMD_ALLOWED
#define MTLK_CORE_CNT_RX_ADDBA_RES_POSITIVE_SENT_ALLOWED                            MTLK_WWSS_WLAN_STAT_ID_RX_ADDBA_RES_POSITIVE_SENT_ALLOWED
#define MTLK_CORE_CNT_RX_ADDBA_RES_REACHED_ALLOWED                                  MTLK_WWSS_WLAN_STAT_ID_RX_ADDBA_RES_REACHED_ALLOWED
#define MTLK_CORE_CNT_RX_ADDBA_RES_RETRANSMISSIONS_ALLOWED                          MTLK_WWSS_WLAN_STAT_ID_RX_ADDBA_RES_RETRANSMISSIONS_ALLOWED
#define MTLK_CORE_CNT_RX_BAR_WITHOUT_REORDERING_ALLOWED                             MTLK_WWSS_WLAN_STAT_ID_RX_BAR_WITHOUT_REORDERING_ALLOWED
#define MTLK_CORE_CNT_RX_AGGR_PKT_WITHOUT_REORDERING_ALLOWED                        MTLK_WWSS_WLAN_STAT_ID_RX_AGGR_PKT_WITHOUT_REORDERING_ALLOWED
#define MTLK_CORE_CNT_RX_DELBA_REQ_CFMD_FAIL_ALLOWED                                MTLK_WWSS_WLAN_STAT_ID_RX_DELBA_REQ_CFMD_FAIL_ALLOWED
#define MTLK_CORE_CNT_RX_DELBA_REQ_CFMD_SUCCESS_ALLOWED                             MTLK_WWSS_WLAN_STAT_ID_RX_DELBA_REQ_CFMD_SUCCESS_ALLOWED
#define MTLK_CORE_CNT_RX_DELBA_REQ_LOST_ALLOWED                                     MTLK_WWSS_WLAN_STAT_ID_RX_DELBA_REQ_LOST_ALLOWED
#define MTLK_CORE_CNT_RX_DELBA_REQ_NOT_CFMD_ALLOWED                                 MTLK_WWSS_WLAN_STAT_ID_RX_DELBA_REQ_NOT_CFMD_ALLOWED
#define MTLK_CORE_CNT_RX_DELBA_REQ_RCV_ALLOWED                                      MTLK_WWSS_WLAN_STAT_ID_RX_DELBA_REQ_RCV_ALLOWED
#define MTLK_CORE_CNT_RX_DELBA_REQ_REACHED_ALLOWED                                  MTLK_WWSS_WLAN_STAT_ID_RX_DELBA_REQ_REACHED_ALLOWED
#define MTLK_CORE_CNT_RX_DELBA_REQ_RETRANSMISSIONS_ALLOWED                          MTLK_WWSS_WLAN_STAT_ID_RX_DELBA_REQ_RETRANSMISSIONS_ALLOWED
#define MTLK_CORE_CNT_RX_DELBA_REQ_SENT_ALLOWED                                     MTLK_WWSS_WLAN_STAT_ID_RX_DELBA_REQ_SENT_ALLOWED
#define MTLK_CORE_CNT_RX_DELBA_SENT_BY_TIMEOUT_ALLOWED                              MTLK_WWSS_WLAN_STAT_ID_RX_DELBA_SENT_BY_TIMEOUT_ALLOWED
#define MTLK_CORE_CNT_TX_ACK_ON_BAR_DETECTED_ALLOWED                                MTLK_WWSS_WLAN_STAT_ID_TX_ACK_ON_BAR_DETECTED_ALLOWED
#define MTLK_CORE_CNT_TX_ADDBA_REQ_CFMD_FAIL_ALLOWED                                MTLK_WWSS_WLAN_STAT_ID_TX_ADDBA_REQ_CFMD_FAIL_ALLOWED
#define MTLK_CORE_CNT_TX_ADDBA_REQ_CFMD_SUCCESS_ALLOWED                             MTLK_WWSS_WLAN_STAT_ID_TX_ADDBA_REQ_CFMD_SUCCESS_ALLOWED
#define MTLK_CORE_CNT_TX_ADDBA_REQ_NOT_CFMD_ALLOWED                                 MTLK_WWSS_WLAN_STAT_ID_TX_ADDBA_REQ_NOT_CFMD_ALLOWED
#define MTLK_CORE_CNT_TX_ADDBA_REQ_SENT_ALLOWED                                     MTLK_WWSS_WLAN_STAT_ID_TX_ADDBA_REQ_SENT_ALLOWED
#define MTLK_CORE_CNT_TX_ADDBA_RES_RCV_NEGATIVE_ALLOWED                             MTLK_WWSS_WLAN_STAT_ID_TX_ADDBA_RES_RCV_NEGATIVE_ALLOWED
#define MTLK_CORE_CNT_TX_ADDBA_RES_RCV_POSITIVE_ALLOWED                             MTLK_WWSS_WLAN_STAT_ID_TX_ADDBA_RES_RCV_POSITIVE_ALLOWED
#define MTLK_CORE_CNT_TX_ADDBA_RES_TIMEOUT_ALLOWED                                  MTLK_WWSS_WLAN_STAT_ID_TX_ADDBA_RES_TIMEOUT_ALLOWED
#define MTLK_CORE_CNT_TX_CLOSE_AGGR_CFMD_FAIL_ALLOWED                               MTLK_WWSS_WLAN_STAT_ID_TX_CLOSE_AGGR_CFMD_FAIL_ALLOWED
#define MTLK_CORE_CNT_TX_CLOSE_AGGR_CFMD_SUCCESS_ALLOWED                            MTLK_WWSS_WLAN_STAT_ID_TX_CLOSE_AGGR_CFMD_SUCCESS_ALLOWED
#define MTLK_CORE_CNT_TX_CLOSE_AGGR_NOT_CFMD_ALLOWED                                MTLK_WWSS_WLAN_STAT_ID_TX_CLOSE_AGGR_NOT_CFMD_ALLOWED
#define MTLK_CORE_CNT_TX_CLOSE_AGGR_SENT_ALLOWED                                    MTLK_WWSS_WLAN_STAT_ID_TX_CLOSE_AGGR_SENT_ALLOWED
#define MTLK_CORE_CNT_TX_DELBA_REQ_CFMD_FAIL_ALLOWED                                MTLK_WWSS_WLAN_STAT_ID_TX_DELBA_REQ_CFMD_FAIL_ALLOWED
#define MTLK_CORE_CNT_TX_DELBA_REQ_CFMD_SUCCESS_ALLOWED                             MTLK_WWSS_WLAN_STAT_ID_TX_DELBA_REQ_CFMD_SUCCESS_ALLOWED
#define MTLK_CORE_CNT_TX_DELBA_REQ_LOST_ALLOWED                                     MTLK_WWSS_WLAN_STAT_ID_TX_DELBA_REQ_LOST_ALLOWED
#define MTLK_CORE_CNT_TX_DELBA_REQ_NOT_CFMD_ALLOWED                                 MTLK_WWSS_WLAN_STAT_ID_TX_DELBA_REQ_NOT_CFMD_ALLOWED
#define MTLK_CORE_CNT_TX_DELBA_REQ_RCV_ALLOWED                                      MTLK_WWSS_WLAN_STAT_ID_TX_DELBA_REQ_RCV_ALLOWED
#define MTLK_CORE_CNT_TX_DELBA_REQ_REACHED_ALLOWED                                  MTLK_WWSS_WLAN_STAT_ID_TX_DELBA_REQ_REACHED_ALLOWED
#define MTLK_CORE_CNT_TX_DELBA_REQ_RETRANSMISSIONS_ALLOWED                          MTLK_WWSS_WLAN_STAT_ID_TX_DELBA_REQ_RETRANSMISSIONS_ALLOWED
#define MTLK_CORE_CNT_TX_DELBA_REQ_SENT_ALLOWED                                     MTLK_WWSS_WLAN_STAT_ID_TX_DELBA_REQ_SENT_ALLOWED
#define MTLK_CORE_CNT_TX_OPEN_AGGR_CFMD_FAIL_ALLOWED                                MTLK_WWSS_WLAN_STAT_ID_TX_OPEN_AGGR_CFMD_FAIL_ALLOWED
#define MTLK_CORE_CNT_TX_OPEN_AGGR_CFMD_SUCCESS_ALLOWED                             MTLK_WWSS_WLAN_STAT_ID_TX_OPEN_AGGR_CFMD_SUCCESS_ALLOWED
#define MTLK_CORE_CNT_TX_OPEN_AGGR_NOT_CFMD_ALLOWED                                 MTLK_WWSS_WLAN_STAT_ID_TX_OPEN_AGGR_NOT_CFMD_ALLOWED
#define MTLK_CORE_CNT_TX_OPEN_AGGR_SENT_ALLOWED                                     MTLK_WWSS_WLAN_STAT_ID_TX_OPEN_AGGR_SENT_ALLOWED

// private statistic counters
struct priv_stats {
  // TX consecutive dropped packets counter
  uint32 tx_cons_drop_cnt;

  // Maximum number of packets dropped consecutively
  uint32 tx_max_cons_drop;

  // Applicable only to STA:
  uint32 sta_session_rx_packets; // Packets received in this session
  uint32 sta_session_tx_packets; // Packets transmitted in this session

  // Dropped Tx packets counters per priority queue
  uint32 ac_dropped_counter[NTS_PRIORITIES];
  uint32 ac_rx_counter[NTS_PRIORITIES];
  uint32 ac_tx_counter[NTS_PRIORITIES];

  // AP forwarding statistics
  uint32 fwd_tx_packets;
  uint32 fwd_tx_bytes;
  uint32 fwd_dropped;

  // Reliable Multicast statistics
  uint32 rmcast_dropped;

  // Used Tx packets per priority queue
  uint32 ac_used_counter[NTS_PRIORITIES];

  // Received BAR frames
  uint32 bars_cnt;

  //trasmitted broadcast/non-reliable multicast packets
  uint32 tx_bcast_nrmcast;

  //number of disconnections
  uint32 num_disconnects;

  /* number of Rx : Wrong nwid/essid */
  uint32 discard_nwi;

  /* Missed beacons/superframe */
  uint32 missed_beacon;

  unsigned long tx_overruns;      /*!< total tx queue overruns */
};

typedef struct {
  uint32 stat[STAT_TOTAL_NUMBER];
} mtlk_mac_stats_t;

/* core to DF UI interface*/
typedef struct _mtlk_core_general_stats_t {
  struct priv_stats   core_priv_stats;
  mtlk_mac_stats_t mac_stat;
  uint32  tx_msdus_free;
  uint32  tx_msdus_usage_peak;
  uint32  bist_check_passed;
  uint16  net_state;
  uint8   max_rssi;
  uint8   noise;
  uint8   channel_load;
  unsigned char bssid[ETH_ALEN];
  uint32  txmm_sent;
  uint32  txmm_cfmd;
  uint32  txmm_peak;
  uint32  txdm_sent;
  uint32  txdm_cfmd;
  uint32  txdm_peak;
  uint32  fw_logger_packets_processed;
  uint32  fw_logger_packets_dropped;

  uint32  tx_packets;       /*!< total packets transmitted */
  uint32  tx_bytes;         /*!< total bytes transmitted */
  uint32  rx_packets;       /*!< total packets received */
  uint32  rx_bytes;         /*!< total bytes received */

  uint32  pairwise_mic_failure_packets;
  uint32  group_mic_failure_packets;
  uint32  unicast_replayed_packets;
  uint32  multicast_replayed_packets;

  uint32  fwd_rx_packets;
  uint32  fwd_rx_bytes;

  // Received data, control and management 802.11 frames from MAC
  uint32 rx_dat_frames;
  uint32 rx_ctl_frames;
  uint32 rx_man_frames;
} mtlk_core_general_stats_t;

struct nic;

#define UMI_WPS_IE_NUM  5

struct nic_slow_ctx {
  struct nic *nic;
  sta_db stadb;
  hst_db hstdb;
  
  /* WDS peers manager */
  wds_t wds_mng;

  // configuration
  mtlk_core_cfg_t cfg;

  tx_limit_t  tx_limits;

  struct mtlk_scan   scan;
  scan_cache_t       cache; 

  /* actual BSS data */
  bss_data_t         bss_data;

  /* spectrum of the last loaded programming model */
  uint8              last_pm_spectrum;
  /* frequency of the last loaded programming model */
  uint8              last_pm_freq;

  // ADDBA-related
  mtlk_addba_t      addba;
  mtlk_reflim_t     addba_lim_reord;
  mtlk_reflim_t     addba_lim_aggr;

  /*AP - always 11h only
    STA - always 11h, if dot11d_active is set, use 11d table
  */
  //11h-related
  mtlk_dot11h_t* dot11h;

  /* aocs-related */
  mtlk_aocs_t *aocs;

  // 802.11i (security) stuff
  UMI_RSN_IE rsnie;
  uint8 default_key;
  uint8 wep_enabled;
  uint8 peerAPs_key_idx;    /* WEP key index for Peer APs (0 - disabled) */
  MIB_WEP_DEF_KEYS wep_keys;
  uint8 wps_in_progress;

  // features
  uint8 is_tkip;

  mtlk_coc_t  *coc_mngmt;
#ifdef MTCFG_PMCU_SUPPORT
  mtlk_pcoc_t *pcoc_mngmt;
#endif /*MTCFG_PMCU_SUPPORT*/

#ifdef MTLK_DEBUG_CHARIOT_OOO
  uint16 seq_prev_sent[NTS_PRIORITIES];
#endif

  mtlk_osal_timer_t mac_watchdog_timer;
  uint8 channel_load;
  uint8 noise;
  /* ACL white/black list */
  IEEE_ADDR acl[MAX_ADDRESSES_IN_ACL];
  IEEE_ADDR acl_mask[MAX_ADDRESSES_IN_ACL];

  // This event arises when MAC sends either UMI_CONNECTED (STA)
  // or UMI_BSS_CREATED (AP)
  // Thread, that performs connection/bss_creation, waits for this event before returning.
  // If no such event arises - connect/bss_create process has failed and error
  // is reported to the caller.
  mtlk_osal_event_t connect_event;

  // This event arises when MAC sends MC_MAN_VAP_WAS_REMOVED_IND
  // Thread, that performs VAP deactivation, waits for this event
  mtlk_osal_event_t vap_removed_event;

  mtlk_serializer_t serializer;

  mtlk_irbd_handle_t *stat_irb_handle;

  int mac_stuck_detected_by_sw;

  uint32 deactivate_ts;
  mtlk_osal_timestamp_t last_arp_probe;

  /* Gen IE configuration */
  uint16 gen_ie_len[UMI_WPS_IE_NUM];
  uint8 gen_ie[UMI_WPS_IE_NUM][UMI_MAX_GENERIC_IE_SIZE];

  MTLK_DECLARE_INIT_STATUS;
  MTLK_DECLARE_START_STATUS;
};

struct _mtlk_20_40_coexistence_sm;

typedef struct _mtlk_dut_handlers_t mtlk_dut_handlers_t;

typedef struct _mtlk_dut_core_t
{
  mtlk_dut_handlers_t *dut_handlers;
  mtlk_irbd_handle_t  *dut_start_handle;
  mtlk_irbd_handle_t  *dut_stop_handle;

  MTLK_DECLARE_START_STATUS;
} mtlk_dut_core_t;

int __MTLK_IFUNC mtlk_dut_core_register(mtlk_core_t *core);
void __MTLK_IFUNC mtlk_dut_core_unregister(mtlk_core_t *core);

struct nic {
  mtlk_l2nat_t l2nat;
  struct nic_slow_ctx *slow_ctx;

  struct priv_stats pstats;

  /* MBSS instance ID  - it is assigned by the hypervisor and should be used when communicating with HAL*/
  mtlk_vap_handle_t   vap_handle;

  // reliable multicast context
  mcast_ctx mcast;

  int net_state;

  mtlk_osal_spinlock_t net_state_lock;
  BOOL  is_stopping;
  BOOL  is_iface_stopping;
  BOOL  is_stopped;
  BOOL  aocs_started;

  // 802.11i (security) stuff
  u8 group_cipher;
  u8 group_rsc[4][6]; // Replay Sequence Counters per key index
  int16 authentication;
  uint8 rsn_enabled;

  /* 802.11w IGTK */
  uint16 igtk_cipher;
  uint16 igtk_key_len;
  uint8  igtk_key[2][UMI_RSN_TK1_LEN + UMI_RSN_TK2_LEN];

  /* Flow control object, singleton in Master core */
  mtlk_flctrl_t *hw_tx_flctrl;

  /* Flow control id, per-core */
  mtlk_handle_t flctrl_id;

  /* send queue struct for shared packet scheduler */
  struct _mtlk_sq_t         *sq;

  /* tasklet for "flushing" shared SendQueue on wake */
  struct tasklet_struct     *sq_flush_tasklet;

  BOOL                      uapsd_enabled;

  uint8                     uapsd_max_sp;

  /* broadcast queue per VAP */
  mtlk_sq_peer_ctx_t        sq_broadcast_ctx;

  /* Number of STAs in PS mode */
  mtlk_atomic_t             stas_in_ps_mode;

  /* bands which have already been CB-scanned */
  uint8                     cb_scanned_bands;
#define CB_SCANNED_2_4  0x1
#define CB_SCANNED_5_2  0x2

  struct mtlk_qos           qos;

  /* Should be set to activation result (Failed\Succeeded) before triggering nic->slow_ctx->connect_event*/
  BOOL activation_status;

#ifdef MTCFG_RF_MANAGEMENT_MTLK
  mtlk_rf_mgmt_t           *rf_mgmt;
#endif
  mtlk_txmm_msg_t           txmm_async_eeprom_msgs[MAX_NUM_TX_ANTENNAS]; /* must be moved to EEPROM module ASAP */

  mtlk_core_hot_path_param_handles_t  pdb_hot_path_handles;

  mtlk_wss_t               *wss;
  mtlk_wss_cntr_handle_t   *wss_hcntrs[MTLK_CORE_CNT_LAST];

  /* 20/40 state machine */
  struct _mtlk_20_40_coexistence_sm *coex_20_40_sm;

  /* Interference Detection */
  BOOL                      is_interfdet_enabled;

  mtlk_dut_core_t           dut_core;

  mtlk_atomic_t             is_mac_fatal_pending;

  uint32                    storedCalibrationChannelBitMap[CALIBR_BITMAP_SIZE];

  MTLK_DECLARE_INIT_STATUS;
  MTLK_DECLARE_INIT_LOOP(TXMM_EEPROM_ASYNC_MSGS_INIT);
  MTLK_DECLARE_START_STATUS;
};

typedef enum
  {
    CFG_INFRA_STATION,
    CFG_ADHOC_STATION,
    CFG_ACCESS_POINT,
    CFG_TEST_MAC,
    CFG_NUM_NET_TYPES
  } CFG_NETWORK_TYPE;

enum bridge_mode {
  BR_MODE_NONE        = 0,
  BR_MODE_WDS         = 1,
  BR_MODE_L2NAT       = 2,
  BR_MODE_MAC_CLONING = 3,
  BR_MODE_LAST
};

int mtlk_xmit (mtlk_core_t* core, struct sk_buff *skb);
void mtlk_record_xmit_err (struct nic *nic, struct sk_buff *skb);

int mtlk_detect_replay_or_sendup(mtlk_core_t* core, struct sk_buff *skb, u8 *rsn);

int mtlk_set_hw_state(mtlk_core_t *nic, int st);

mtlk_handle_t __MTLK_IFUNC mtlk_core_get_tx_limits_handle(mtlk_handle_t nic);

/* Size of this structure must be multiple of sizeof(void*) because   */
/* it is immediately followed by data of the request, and the data,   */
/* generally speaking, must be sizeof(void*)-aligned.                 */
/* There is corresponding assertion in the code.                      */
typedef struct __core_async_exec_t
{
  MTLK_DECLARE_OBJPOOL_CTX(objpool_ctx);

  mtlk_command_t        cmd;
  mtlk_handle_t         receiver;
  uint32                data_size;
  mtlk_core_task_func_t func;
  mtlk_user_request_t  *user_req;
  mtlk_vap_handle_t     vap_handle;
  mtlk_ability_id_t     ability_id;
} _core_async_exec_t;

static __INLINE BOOL
mtlk_is_dut_core_active (mtlk_core_t *core)
{
  MTLK_ASSERT(core != NULL);
  return ((core->dut_core.dut_handlers == NULL) ? FALSE : TRUE);
}

/* counters will be modified with checking ALLOWED option */
#define mtlk_core_inc_cnt(core, id)         { if (id##_ALLOWED) __mtlk_core_inc_cnt(core, id); }
#define mtlk_core_add_cnt(core, id, val)    { if (id##_ALLOWED) __mtlk_core_add_cnt(core, id, val); }

static __INLINE void
__mtlk_core_inc_cnt (mtlk_core_t       *core,
                   mtlk_core_wss_cnt_id_e cnt_id)
{
  MTLK_ASSERT(cnt_id >= 0 && cnt_id < MTLK_CORE_CNT_LAST);

  mtlk_wss_cntr_inc(core->wss_hcntrs[cnt_id]);
}

static __INLINE void
__mtlk_core_add_cnt (mtlk_core_t       *core,
                   mtlk_core_wss_cnt_id_e cnt_id,
                   uint32            val)
{
  MTLK_ASSERT(cnt_id >= 0 && cnt_id < MTLK_CORE_CNT_LAST);

  mtlk_wss_cntr_add(core->wss_hcntrs[cnt_id], val);
}


static __INLINE uint8 
mtlk_core_get_last_pm_spectrum(struct nic *nic)
{
  return nic->slow_ctx->last_pm_spectrum;
}

static __INLINE uint8
mtlk_core_get_last_pm_freq(struct nic *nic)
{
  return nic->slow_ctx->last_pm_freq;
}

static __INLINE BOOL
mtlk_core_scan_is_running(struct nic *nic)
{
  if (mtlk_scan_is_initialized(&nic->slow_ctx->scan)) {
    return mtlk_scan_is_running(&nic->slow_ctx->scan);
  }
  return FALSE;
}

mtlk_core_t * __MTLK_IFUNC
mtlk_core_get_master(mtlk_core_t *core);

static __INLINE void mtlk_core_set_coex_sm(mtlk_core_t *core, struct _mtlk_20_40_coexistence_sm *coex_sm)
{
  MTLK_ASSERT(mtlk_vap_is_master(core->vap_handle));
  core->coex_20_40_sm = coex_sm;
}

tx_limit_t* __MTLK_IFUNC
mtlk_core_get_tx_limits(mtlk_core_t *core);

int __MTLK_IFUNC mtlk_core_on_channel_switch_done(mtlk_vap_handle_t vap_handle,
                                                  uint16            primary_channel,
                                                  uint8             secondary_channel_offset,
                                                  uint16            reason);

BOOL __MTLK_IFUNC mtlk_core_is_connected(mtlk_core_t *core);
BOOL __MTLK_IFUNC mtlk_core_is_halted(mtlk_core_t *core);

uint32 __MTLK_IFUNC mtlk_core_get_max_stas_supported_by_fw(mtlk_core_t *nic);

int __MTLK_IFUNC mtlk_core_set_uapsd_max_sp(mtlk_core_t *core, uint8 uapsd_max_sp);

#undef LOG_LOCAL_GID
#undef LOG_LOCAL_FID

#endif

