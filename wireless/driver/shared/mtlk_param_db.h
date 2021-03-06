/******************************************************************************

                               Copyright (c) 2012
                            Lantiq Deutschland GmbH

  For licensing information, see the file 'LICENSE' in the root folder of
  this software module.

******************************************************************************/
#ifndef __MTLK_PARAM_DB_H__
#define __MTLK_PARAM_DB_H__

#include "mtlkdfdefs.h"
#include "mtlk_card_types.h"

#define   MTLK_IDEFS_ON
#include "mtlkidefs.h"

#define LOG_LOCAL_GID  GID_PDB
#define LOG_LOCAL_FID  0

/** 
*\file mtlk_param_db.h 

*\brief Parameter database that should serve different modules in the driver

*\defgroup PARAM_DB Parameter database
*\{

   Parameter DB used as a container for driver's parameters. Default values are loaded during initialization and
   API is provided to access (set\get) the parameters. Currently three types of parameters supported - integers, strings and binary.

   There are two main usage scenarios for the param db:
     -# Fast parameter accessor functions
       - Handle to parameter should be retrieved using open function
       - Fast access to parameters, will locks over parameter only
     -# Regular accessor functions
       - There is additional DB lock when using regular functions.
      # Each module should define its own parameters and include the pointer to the array of mtlk_pdb_initial_value in mtlk_pdb_initial_values array in mtlk_param_db_def.c


*/

/* Value IDs */
typedef enum {
  PARAM_DB_CORE_BRIDGE_MODE = 0, /*!< Core Hot-Path (H-P) parameter  */
  PARAM_DB_CORE_AP_FORWARDING,   /*!< Core H-P parameter  */
  PARAM_DB_CORE_MAC_ADDR,        /*!< Core H-P parameter  */
  PARAM_DB_CORE_RELIABLE_MCAST,  /*!< Core H-P parameter - Enable/disable Reliable Multicast */
  PARAM_DB_CORE_BSSID,           /*!< Core H-P parameter - BSSID */

  PARAM_DB_CORE_COEX_CFG,                  /*!< Core parameter  */
  PARAM_DB_CORE_STA_FORCE_SPECTRUM_MODE,   /*!< Core parameter  */
  PARAM_DB_CORE_PROG_MODEL_SPECTRUM_MODE,  /*!< Core parameter  */
  PARAM_DB_CORE_SELECTED_SPECTRUM_MODE,    /*!< Core parameter. Spectrum mode selected by driver's logic (AOCS, Coex)  */
  PARAM_DB_CORE_USER_SPECTRUM_MODE,        /*!< Core parameter. Spectrum mode selected by user (for AP only) */
  PARAM_DB_CORE_SELECTED_BONDING_MODE,     /*!< Core parameter. Bonding mode selected by driver's logic */
  PARAM_DB_CORE_USER_BONDING_MODE,         /*!< Core parameter. Bonding mode selected by user (for AP only) */
  PARAM_DB_CORE_UP_RESCAN_EXEMPTION_TIME,  /*!< Core parameter time in sec of initial re-scan examption */
  PARAM_DB_CORE_CHANNEL_CFG,               /*!< Core parameter configured channel */
  PARAM_DB_CORE_CHANNEL_CUR,               /*!< Core parameter current channel*/
  PARAM_DB_CORE_POWER_SELECTION,   /*!< Core parameter  */
  PARAM_DB_CORE_RA_PROTECTION,   /*!< Core parameter  */
  PARAM_DB_CORE_FORCE_NCB,   /*!< Core parameter  */
  PARAM_DB_CORE_N_RATE_BO_QAM16,
  PARAM_DB_CORE_N_RATE_BO_QAM64_2_3,
  PARAM_DB_CORE_N_RATE_BO_QAM64_3_4,
  PARAM_DB_CORE_N_RATE_BO_QAM64_5_6,
  PARAM_DB_CORE_DEBUG_TPC,         /*!< Core parameter - Debug TPC */
  PARAM_DB_CORE_MAC_SOFT_RESET_ENABLE, /*!< Core parameter - MAC reset control: automatically on MAC assert/exception*/
  PARAM_DB_CORE_COUNTRY_CODE,   /*!< Core parameter - Country code*/
  PARAM_DB_CORE_DOT11D_ENABLED, /*!< Core parameter - Enable/disable .11d extension */
  PARAM_DB_CORE_BASIC_RATE_SET, /*!< Core parameter - Basic rate set */
  PARAM_DB_CORE_SUPPORTED_RATE_SET, /*!< Core parameter - Supported rate set */
  PARAM_DB_CORE_EXTENDED_RATE_SET, /*!< Core parameter - Extended Supported rate set */
  PARAM_DB_CORE_LEGACY_FORCED_RATE_SET,  /*!< Core parameter - Legacy forced rate set */
  PARAM_DB_CORE_HT_FORCED_RATE_SET, /*!< Core parameter - HT forced rate set */
  PARAM_DB_CORE_AGG_RATE_LIMIT_MODE,    /*!< Core parameter - Aggregation Rate Limit mode */
  PARAM_DB_CORE_AGG_RATE_LIMIT_MAXRATE, /*!< Core parameter - Aggregation Rate Limit max rate */
  PARAM_DB_CORE_RX_HIGH_THRESHOLD,      /*!< Core parameter - RX High Reception Threshold */
  PARAM_DB_CORE_RX_DUTY_CYCLE_ONTIME,   /*!< Core parameter - RX Duty Cycle onTime */
  PARAM_DB_CORE_RX_DUTY_CYCLE_OFFTIME,  /*!< Core parameter - RX Duty Cycle offTime */
  PARAM_DB_CORE_CCA_THRESHOLD,      /*!< Core parameter - CCA Threshold */
  PARAM_DB_CORE_MAC_WATCHDOG_TIMER_TIMEOUT_MS, /*!< Core parameter - set timeout for MAC watchdog message sending */
  PARAM_DB_CORE_MAC_WATCHDOG_TIMER_PERIOD_MS,  /*!< Core parameter - set MAC watchdog checking timer period */
  PARAM_DB_CORE_NICK_NAME,      /*!< Core parameter - IW Nick name */
  PARAM_DB_CORE_ESSID,          /*!< Core parameter - BSSID */
  PARAM_DB_CORE_NET_MODE_CFG,   /*!< Core parameter - configured Network mode*/
  PARAM_DB_CORE_NET_MODE_CUR,   /*!< Core parameter - current Network mode*/
  PARAM_DB_CORE_FREQ_BAND_CFG,   /*!< Core parameter - configured Frequency band*/
  PARAM_DB_CORE_FREQ_BAND_CUR,   /*!< Core parameter - current Frequency band*/
  PARAM_DB_CORE_IS_HT_CFG,       /*!< Core parameter - configured HT mode*/
  PARAM_DB_CORE_IS_HT_CUR,       /*!< Core parameter - current HT mode*/
  PARAM_DB_CORE_L2NAT_AGING_TIMEOUT,  /*!< Core parameter - L2NAT alignment timeout */
  PARAM_DB_CORE_SHORT_PREAMBLE,  /*!< Core MIB parameter - short preamble option is implemented*/
  PARAM_DB_CORE_TX_POWER,        /*!< Core MIB parameter - current transmission power*/
  PARAM_DB_CORE_SHORT_CYCLIC_PREFIX_RX,     /*!< Core MIB parameter - use short cyclic prefix*/
  PARAM_DB_CORE_SHORT_CYCLIC_PREFIX_TX,     /*!< Core MIB parameter - use short cyclic prefix*/
  PARAM_DB_CORE_SHORT_CYCLIC_PREFIX_RATE31, /*!< Core MIB parameter - use short cyclic prefix*/
  PARAM_DB_CORE_CALIBRATION_ALGO_MASK,  /*!< Core MIB parameter - calibration mask*/
  PARAM_DB_CORE_ONLINE_ACM,     /*!< Core MIB parameter - online algo calibration mask*/
  PARAM_DB_CORE_SHORT_SLOT_TIME, /*!< Core MIB parameter - use short slot time*/
  PARAM_DB_CORE_SM_ENABLE,      /*!< Core MIB parameter - channel announcement enabled*/
  PARAM_DB_CORE_TX_ANTENNAS,    /*!< Core MIB parameter - transmission antenna list*/
  PARAM_DB_CORE_RX_ANTENNAS,    /*!< Core MIB parameter - reception antenna list*/

  PARAM_DB_CORE_ACL_MODE,       /*!< MIB_ACL_MODE */
  PARAM_DB_CORE_STBC,           /*!< MIB_USE_SPACE_TIME_BLOCK_CODE */
  PARAM_DB_CORE_TWO_ANT_TX_ENABLE, /*!< MIB_TWO_ANTENNA_TRANSMISSION_ENABLE */
  PARAM_DB_CORE_AMPDU_MAXLEN,   /*!< MIB_RECEIVE_AMPDU_MAX_LENGTH */
  PARAM_DB_CORE_RTS_THRESH,     /*!< MIB_RTS_THRESHOLD */
  PARAM_DB_CORE_ADVANCED_CODING,/*!< MIB_ADVANCED_CODING_SUPPORTED */
  PARAM_DB_CORE_OFDM_PROTECTION,/*!< MIB_OFDM_PROTECTION_METHOD */
  PARAM_DB_CORE_HT_PROTECTION,  /*!< MIB_HT_PROTECTION_METHOD */
  PARAM_DB_CORE_OVERLAPPING_PROT,/*!<MIB_OVERLAPPING_PROTECTION_ENABLE */
  PARAM_DB_CORE_LONG_RETRY_LIMIT,/*!<MIB_LONG_RETRY_LIMIT */
  PARAM_DB_CORE_SHORT_RETRY_LIMIT,/*!<MIB_SHORT_RETRY_LIMIT */
  PARAM_DB_CORE_MSDU_LIFETIME,  /*!< MIB_TX_MSDU_LIFETIME */
  PARAM_DB_CORE_BEACON_PERIOD,  /*!< MIB_BEACON_PERIOD */
  PARAM_DB_CORE_DTIM_PERIOD,    /*!< MIB_DTIM_PERIOD */
  PARAM_DB_CORE_DISC_ON_NACKS,  /*!< MIB_DISCONNECT_ON_NACKS_ENABLE */
  PARAM_DB_CORE_POWER_LIMIT,    /*!< UM_MAN_CHANGE_TX_POWER_LIMIT_REQ */
  PARAM_DB_CORE_POWER_LIMIT_11B_BOOST,     /*!< UM_MAN_CHANGE_TX_POWER_LIMIT_REQ */
  PARAM_DB_CORE_POWER_LIMIT_BPSK_BOOST,    /*!< UM_MAN_CHANGE_TX_POWER_LIMIT_REQ */
  PARAM_DB_CORE_POWER_LIMIT_AUTO_RESPONCE, /*!< UM_MAN_CHANGE_TX_POWER_LIMIT_REQ */
  PARAM_DB_CORE_LNA_GAIN,       /*!< UM_MAN_SET_EXT_LNA_PARAMS_REQ */

  /* 802.11w begin */
  PARAM_DB_CORE_PMF_ACTIVATED,
  PARAM_DB_CORE_PMF_REQUIRED,
  PARAM_DB_CORE_SAQ_RETR_TMOUT,
  PARAM_DB_CORE_SAQ_MAX_TMOUT,
  /* 802.11w end */

  PARAM_DB_CORE_CUR_TX_ANTENNAS,    /*!< MIB_CURRENT_TX_ANTENNA */
  PARAM_DB_CORE_DISC_ON_NACKS_WGHT, /*!< MIB_DISCONNECT_ON_NACKS_WEIGHT */
  PARAM_DB_CORE_LONG_PREAMB_MC,     /*!< MIB_USE_LONG_PREAMBLE_FOR_MULTICAST */
  PARAM_DB_CORE_CB_BINS_PER_SYMB,   /*!< MIB_CB_DATABINS_PER_SYMBOL */

  /* Interference Detection */
  PARAM_DB_INTERFDET_MODE,                            /*!< interference enabled or disabled */
  PARAM_DB_INTERFDET_20MHZ_DETECTION_THRESHOLD,       /*!< detection threshold for driver in 20MHz, Auto, or Coex mode */
  PARAM_DB_INTERFDET_20MHZ_NOTIFICATION_THRESHOLD,    /*!< notification threshold for firmwarte in 20MHz, Auto, or Coex mode */
  PARAM_DB_INTERFDET_40MHZ_DETECTION_THRESHOLD,       /*!< detection threshold for driver */
  PARAM_DB_INTERFDET_40MHZ_NOTIFICATION_THRESHOLD,    /*!< notification threshold for firmware */
  PARAM_DB_INTERFDET_SCAN_NOISE_THRESHOLD,            /*!< noise threshold for scan, dB - for comparing channel noise levels */
  PARAM_DB_INTERFDET_SCAN_MINIMUM_NOISE,              /*!< scan minimum noise, dB */
  PARAM_DB_INTERFDET_ACTIVE_POLLING_TIMEOUT,          /*!< polling timeout for active state */
  PARAM_DB_INTERFDET_SHORT_SCAN_POLLING_TIMEOUT,      /*!< polling timeout for restricted channels scan */
  PARAM_DB_INTERFDET_LONG_SCAN_POLLING_TIMEOUT,       /*!< polling timeout for unrestricted channels scan */
  PARAM_DB_INTERFDET_ACTIVE_NOTIFICATION_TIMEOUT,     /*!< notification timeout in active state */
  PARAM_DB_INTERFDET_SHORT_SCAN_NOTIFICATION_TIMEOUT, /*!< notification timeout for restricted channels scan */
  PARAM_DB_INTERFDET_LONG_SCAN_NOTIFICATION_TIMEOUT,  /*!< notification timeout for unrestricted channels scan */

  PARAM_DB_FW_LED_GPIO_DISABLE_TESTBUS, /*!< Mirror of FW's LED GPIO CFG: UMI_CONFIG_GPIO.uDisableTestbus */
  PARAM_DB_FW_LED_GPIO_ACTIVE_GPIOs,    /*!< Mirror of FW's LED GPIO CFG: UMI_CONFIG_GPIO.uActiveGpios    */
  PARAM_DB_FW_LED_GPIO_LED_POLARITY,    /*!< Mirror of FW's LED GPIO CFG: UMI_CONFIG_GPIO.bLedPolarity    */

  PARAM_DB_FW_LED_STATE_BASEB_LED,      /*!< Mirror of FW's LED STATE: UMI_SET_LED_REQ.u8BasebLed */
  PARAM_DB_FW_LED_STATE_LED_STATE,      /*!< Mirror of FW's LED STATE: UMI_SET_LED_REQ.u8LedStatus */

  PARAM_DB_CONSECUTIVE_11B_TH,
  PARAM_DB_CONSECUTIVE_11N_TH,

  PARAM_DB_11B_ANTSEL_RATE,
  PARAM_DB_11B_ANTSEL_RXANT,
  PARAM_DB_11B_ANTSEL_TXANT,

  PARAM_DB_CORE_STA_LIMIT_MIN,
  PARAM_DB_CORE_STA_LIMIT_MAX,

  PARAM_DB_FW_MC_PS_MAX_FSDUS,

#ifdef MTLK_PDB_UNIT_TEST
  PARAM_DB_MODULE_A_TEST_STRING,
  PARAM_DB_MODULE_A_TEST_INT1,
  PARAM_DB_MODULE_A_TEST_INT2,
  PARAM_DB_MODULE_A_TEST_BINARY,
  PARAM_DB_MODULE_B_TEST_INT1,
  PARAM_DB_MODULE_B_TEST_STRING,
#endif /* MTLK_PDB_UNIT_TEST */

  /* DFS params */
  PARAM_DB_DFS_RADAR_DETECTION,
  PARAM_DB_DFS_SM_REQUIRED,

  PARAM_DB_LAST_VALUE_ID, /*!< Last parameter ID */
} mtlk_pdb_id_t;/*!< \Enum of the parameters IDs. When adding parameter - extend this enum */

/* Possible value types */
#define PARAM_DB_TYPE_INT     0x01    /*!< Integer type */
/*It's recommended to initialize STRING parameters
 * using maximum possible string length value + 1 (for zero)*/
#define PARAM_DB_TYPE_STRING  0x02    /*!< String type */
#define PARAM_DB_TYPE_BINARY  0x04    /*!< Binary type */
#define PARAM_DB_TYPE_MAC     0x08    /*!< Binary type */

/* Value flags */
#define PARAM_DB_VALUE_FLAG_NO_FLAG       0x00    /*!< No flags defined, should be used to avoid the usage of magic numbers */
#define PARAM_DB_VALUE_FLAG_READONLY      0x01    /*!< Read only - calling setters will cause assertion */
#define PARAM_DB_VALUE_FLAG_UNINITIALIZED 0x02    /*!< Parameter was uninitialized - calling accessors will cause assertion */

typedef uint32 mtlk_pdb_size_t;        /*!<  Parameter size type */

typedef const struct _mtlk_pdb_initial_value {
  uint32 id;                /*!< \private ID of the parameter */
  uint32 type;              /*!< \private Type of the parameter */
  uint32 flag;              /*!< \private Flags of the parameter */
  uint32 size;              /*!< \private Size of the parameter */
  const void * value;       /*!< \private Pointer to the memory holding parameters value */
}__MTLK_IDATA mtlk_pdb_initial_value; /*!<  Initial value - should be used only to define initial values of the parameters*/

extern const mtlk_pdb_initial_value *mtlk_pdb_initial_values[];

#ifdef MTCFG_LINDRV_HW_PCIG3
extern const mtlk_pdb_initial_value *mtlk_pdb_initial_values_pcig3[];
#endif /* MTCFG_LINDRV_HW_PCIG3 */

#ifdef MTCFG_LINDRV_HW_PCIE
extern const mtlk_pdb_initial_value *mtlk_pdb_initial_values_pcie[];
#endif /* MTCFG_LINDRV_HW_PCIE */

#ifdef MTCFG_LINDRV_HW_AHBG35
extern const mtlk_pdb_initial_value *mtlk_pdb_initial_values_g35[];
#endif /* MTCFG_LINDRV_HW_AHBG35 */

typedef struct _private_mtlk_pdb_value_t
{
  mtlk_pdb_size_t size; /*!< \private Size of the parameter */
  uint32 flags;         /*!< \private Flags of the parameter */
  uint32 type;          /*!< \private Type of the parameter */
  mtlk_osal_spinlock_t param_lock;   /*!< \private Access lock for the parameter */
  mtlk_pdb_t * parent;               /*!< \private Pointer to parent param db object*/

  union {
    void * value_ptr;               /*!< \private Placeholder for the pointer to string or binary values*/
    mtlk_atomic_t value_int;        /*!< \private Placeholder for the integer values*/
  } value;

}__MTLK_IDATA mtlk_pdb_value_t; /*!<  Parameter db value (parameter) */

typedef mtlk_pdb_value_t * mtlk_pdb_handle_t; /*!<  Parameter's handle*/


/*! Create param db object

    \return  mtlk_pdb_t*    Allocated param db object
*/
mtlk_pdb_t* __MTLK_IFUNC mtlk_pdb_create(mtlk_card_type_t hw_type);

/*! Deletes param db object with clean up

    \param  obj    Param db object to be deleted
*/

void __MTLK_IFUNC mtlk_pdb_delete (mtlk_pdb_t *obj);

/*! Retrieves the value of parameter of the integer type

    \param  obj     Param db object 
    \param  id      Parameter's ID

    \return value   parameter's value
*/
int __MTLK_IFUNC mtlk_pdb_get_int(mtlk_pdb_t* obj, mtlk_pdb_id_t id);

/*! Retrieves the value of parameter of the string type

    \param  obj     Param db object 
    \param  id      Parameter's ID
    \param  value   Pointer to variable that will receive parameter's value
    \param  size   Pointer to variable that will receive parameter's size, when calling the function should be set to the buffer size

    \return MTLK_ERR_OK   Parameter retrieved successfully
    \return MTLK_ERR_BUF_TOO_SMALL   Provided buffer is too small, size will be set to needed buffer size
*/
int __MTLK_IFUNC mtlk_pdb_get_string(mtlk_pdb_t* obj, mtlk_pdb_id_t id, char * value, mtlk_pdb_size_t * size);

/*! Retrieves the value of parameter of the binary type

    \param  obj     Param db object 
    \param  id      Parameter's ID
    \param  value   Pointer to variable that will receive parameter's value
    \param  size   Pointer to variable that will receive parameter's size, when calling the function should be set to the buffer size

    \return MTLK_ERR_OK   Parameter retrieved successfully
    \return MTLK_ERR_BUF_TOO_SMALL   Provided buffer is too small, size will be set to needed buffer size
*/
int __MTLK_IFUNC
mtlk_pdb_get_binary(mtlk_pdb_t* obj, mtlk_pdb_id_t id, void * buffer, mtlk_pdb_size_t * size);

/*! Retrieves the value of parameter of the MAC type

    \param  obj     Param db object
    \param  id      Parameter's ID
    \param  value   Pointer to variable that will receive MAC's value
*/
void __MTLK_IFUNC
mtlk_pdb_get_mac(mtlk_pdb_t* obj, mtlk_pdb_id_t id, void * mac);

/*! Sets the value of parameter of the integer type

    \param  obj     Param db object 
    \param  id      Parameter's ID
    \param  value   New parameter's value

*/
void __MTLK_IFUNC mtlk_pdb_set_int(mtlk_pdb_t* obj, mtlk_pdb_id_t id, uint32 value);

/*! Sets the value of parameter of the string type

    \param  obj     Param db object 
    \param  id      Parameter's ID
    \param  value   New parameter's value

    \return MTLK_ERR_OK   Parameter retrieved successfully
    \return MTLK_ERR_PARAMS   Zero size of the new value
    \return MTLK_ERR_NO_MEM   Memory allocation failed
*/
int __MTLK_IFUNC mtlk_pdb_set_string(mtlk_pdb_t* obj, mtlk_pdb_id_t id, const char * value);

/*! Sets the value of the parameter of the binary type

    \param  obj     Param db object 
    \param  id      Parameter's ID
    \param  value   New parameter's value

    \return MTLK_ERR_OK   Parameter retrieved successfully
    \return MTLK_ERR_PARAMS   Zero size of the new value
    \return MTLK_ERR_NO_MEM   Memory allocation failed
*/
int __MTLK_IFUNC
mtlk_pdb_set_binary(mtlk_pdb_t* obj, mtlk_pdb_id_t id, const void * buffer, mtlk_pdb_size_t size);

/*! Sets the value of the parameter of the MAC type

    \param  obj     Param db object
    \param  id      Parameter's ID
    \param  value   New MAC's value
*/
void __MTLK_IFUNC
mtlk_pdb_set_mac(mtlk_pdb_t* obj, mtlk_pdb_id_t id, const void *mac);

/* Fast access functions - work with mtlk_pdb_handle_t class*/

/*! Gets handle to parameter for fast access. All open handles should be closed using mtlk_pdb_close function

    \param  obj     Param db object 
    \param  id      Parameter's ID

    \return mtlk_pdb_handle_t   valid handle for the parameter
*/
mtlk_pdb_handle_t __MTLK_IFUNC mtlk_pdb_open(mtlk_pdb_t* obj, mtlk_pdb_id_t id);

/*! Parameter handle cleanup

\param  handle     Handle to parameter that was opened using mtlk_pdb_open

*/
void __MTLK_IFUNC mtlk_pdb_close(mtlk_pdb_handle_t handle);

/*! Tests parameter for set flags

    \param  handle     Handle to parameter that was opened using mtlk_pdb_open
    \param  flag     Flag(s) to test

    \return TRUE   Specified flag(s) are set.
    \return FALSE   Specified flag(s) are not set.
*/
static int __INLINE mtlk_pdb_is_param_flag_set(mtlk_pdb_handle_t handle, uint32 flag) {
  return !!(handle->flags & flag);
}

/*! Tests parameter to be of specific type

    \param  handle     Handle to parameter that was opened using mtlk_pdb_open

    \return TRUE   Parameter is of the specified type
    \return FALSE  Parameter is not of the specified type
*/
static int __INLINE mtlk_pdb_is_param_of_type(mtlk_pdb_handle_t handle, uint32 type) {
  return (handle->type == type);
}

/*! Fast get for integer parameters

    \param  handle  Handle to parameter that was opened using mtlk_pdb_open

    \return parameter's value
*/
static int __INLINE mtlk_pdb_fast_get_int(mtlk_pdb_handle_t handle) {
  MTLK_ASSERT(NULL != handle);
  MTLK_ASSERT(!mtlk_pdb_is_param_flag_set(handle, PARAM_DB_VALUE_FLAG_UNINITIALIZED));
  MTLK_ASSERT(mtlk_pdb_is_param_of_type(handle, PARAM_DB_TYPE_INT));

  return mtlk_osal_atomic_get(&handle->value.value_int);
}

/*! Fast get for string parameters

    \param  handle  Handle to parameter that was opened using mtlk_pdb_open
    \param  value   Pointer to variable that will receive string value
    \param  size    Pointer to variable that
                    will receive current maximum string size (including zero character),
                    when calling the function should be set to the value buffer size (including zero character)

    \return MTLK_ERR_OK  Parameter retrieved successfully
    \return MTLK_ERR_BUF_TOO_SMALL   Provided buffer is too small,
                                     size will be set to needed buffer size (including zero character)
*/
static int __INLINE mtlk_pdb_fast_get_string(mtlk_pdb_handle_t handle, char * value, mtlk_pdb_size_t * size) {
  int result = MTLK_ERR_OK;

  MTLK_ASSERT(NULL != handle);
  MTLK_ASSERT(NULL != value);
  MTLK_ASSERT(NULL != size);
  MTLK_ASSERT(!mtlk_pdb_is_param_flag_set(handle, PARAM_DB_VALUE_FLAG_UNINITIALIZED));
  MTLK_ASSERT(mtlk_pdb_is_param_of_type(handle, PARAM_DB_TYPE_STRING));

  mtlk_osal_lock_acquire(&handle->param_lock);

  /* size parameter is used just for checking here */
  if(*size < handle->size) {
    result = MTLK_ERR_BUF_TOO_SMALL;
    goto end;
  }

  strncpy(value, handle->value.value_ptr, (handle->size - 1));

end:
  *size = handle->size;
  mtlk_osal_lock_release(&handle->param_lock);

  return result;
}

/*! Fast compare  for binary parameters

    \param  handle  Handle to parameter that was opened using mtlk_pdb_open
    \param  buffer   Pointer to the buffer that will be compared with parameter
    \param  size   Size of the buffer that need comparison.

    \return <0      if parameter's buffer less than supplied buffer
    \return 0      if parameter's buffer identical to supplied buffer
    \return >0      if parameter's buffer greater than supplied buffer
*/
static int __INLINE mtlk_pdb_fast_cmp_binary(mtlk_pdb_handle_t handle, const void * buffer, mtlk_pdb_size_t size) {
  int result;

  MTLK_ASSERT(NULL != handle);
  MTLK_ASSERT(NULL != buffer);
  MTLK_ASSERT(0 != size);
  MTLK_ASSERT(!mtlk_pdb_is_param_flag_set(handle, PARAM_DB_VALUE_FLAG_UNINITIALIZED));
  MTLK_ASSERT(mtlk_pdb_is_param_of_type(handle, PARAM_DB_TYPE_BINARY));

  mtlk_osal_lock_acquire(&handle->param_lock);
  if (size != handle->size) {
    result = (int)(handle->size - size);
  }
  else {
    result = memcmp(handle->value.value_ptr, buffer, handle->size);
  }
  mtlk_osal_lock_release(&handle->param_lock);

  return result;
}


/*! Fast get for binary parameters

    \param  handle  Handle to parameter that was opened using mtlk_pdb_open
    \param  buffer   Pointer to variable that will receive parameter's value
    \param  size   Pointer to variable that will receive parameter's size, when calling the function should be set to the buffer size

    \return MTLK_ERR_OK  Parameter retrieved successfully
    \return MTLK_ERR_BUF_TOO_SMALL   Provided buffer is too small, size will be set to needed buffer size
*/
static int __INLINE mtlk_pdb_fast_get_binary(mtlk_pdb_handle_t handle, void * buffer, mtlk_pdb_size_t * size) {
  int result = MTLK_ERR_OK;

  MTLK_ASSERT(NULL != handle);
  MTLK_ASSERT(NULL != buffer);
  MTLK_ASSERT(NULL != size);
  MTLK_ASSERT(!mtlk_pdb_is_param_flag_set(handle, PARAM_DB_VALUE_FLAG_UNINITIALIZED));
  MTLK_ASSERT(mtlk_pdb_is_param_of_type(handle, PARAM_DB_TYPE_BINARY));

  mtlk_osal_lock_acquire(&handle->param_lock);

  if(*size < handle->size) {
    result = MTLK_ERR_BUF_TOO_SMALL;
    *size = handle->size;
    goto end;
  }

  memcpy(buffer, handle->value.value_ptr, handle->size);
  *size = handle->size;

end:
  mtlk_osal_lock_release(&handle->param_lock);

  return result;
}

/*! Fast sets the value of parameter of the integer type

    \param  handle  Handle to parameter that was opened using mtlk_pdb_open
    \param  value   New parameter's value

    \return MTLK_ERR_OK   Parameter retrieved successfully
*/
static void __INLINE mtlk_pdb_fast_set_int(mtlk_pdb_handle_t handle, uint32 value) {
  MTLK_ASSERT(NULL != handle);
  MTLK_ASSERT(!mtlk_pdb_is_param_flag_set(handle, PARAM_DB_VALUE_FLAG_UNINITIALIZED));
  MTLK_ASSERT(!mtlk_pdb_is_param_flag_set(handle, PARAM_DB_VALUE_FLAG_READONLY));
  MTLK_ASSERT(mtlk_pdb_is_param_of_type(handle, PARAM_DB_TYPE_INT));

  mtlk_osal_atomic_set(&handle->value.value_int, value);
}


/*! Fast sets the value of parameter of the string type

    \param  handle  Handle to parameter that was opened using mtlk_pdb_open
    \param  value   New parameter's value

    \return MTLK_ERR_OK   Parameter retrieved successfully
    \return MTLK_ERR_PARAMS   Zero size of the new value
    \return MTLK_ERR_NO_MEM   Memory allocation failed
*/
static int __INLINE mtlk_pdb_fast_set_string(mtlk_pdb_handle_t handle, const char * value) {
  int result = MTLK_ERR_OK;
  int size;

  MTLK_ASSERT(NULL != handle);
  MTLK_ASSERT(NULL != value);
  MTLK_ASSERT(!mtlk_pdb_is_param_flag_set(handle, PARAM_DB_VALUE_FLAG_UNINITIALIZED));
  MTLK_ASSERT(!mtlk_pdb_is_param_flag_set(handle, PARAM_DB_VALUE_FLAG_READONLY));
  MTLK_ASSERT(mtlk_pdb_is_param_of_type(handle, PARAM_DB_TYPE_STRING));
  MTLK_ASSERT(mtlk_pdb_is_param_of_type(handle, PARAM_DB_TYPE_STRING));

  size = strlen(value);

  mtlk_osal_lock_acquire(&handle->param_lock);

  if (size > (handle->size - 1)) {    /* if current string buffer size is enough, do not reallocate memory */
    /* first try to allocate memory, only then release the existing buffer */
    char * temp_str_ptr = (char *)mtlk_osal_mem_alloc(size + 1, MTLK_MEM_TAG_PARAM_DB);

    if(!temp_str_ptr) {
      result = MTLK_ERR_NO_MEM;
      goto end;
    }

    if(handle->value.value_ptr) {
      mtlk_osal_mem_free(handle->value.value_ptr);
    }

    handle->value.value_ptr = temp_str_ptr;
    handle->size = size + 1;
  }

  strncpy(handle->value.value_ptr, value, (handle->size - 1));


end:
  mtlk_osal_lock_release(&handle->param_lock);

  return result;
}

/*! Fast sets the value of parameter of the binary type

    \param  handle  Handle to parameter that was opened using mtlk_pdb_open
    \param  value   New parameter's value
    \param  size    Size of the new parameter's value

    \return MTLK_ERR_OK   Parameter retrieved successfully
    \return MTLK_ERR_PARAMS   Zero size of the new value
    \return MTLK_ERR_NO_MEM   Memory allocation failed
*/
static int __INLINE mtlk_pdb_fast_set_binary(mtlk_pdb_handle_t handle, const void * buffer, mtlk_pdb_size_t size) {
  int result = MTLK_ERR_OK;
  MTLK_ASSERT(NULL != handle);
  MTLK_ASSERT(NULL != buffer);

  MTLK_ASSERT(!mtlk_pdb_is_param_flag_set(handle, PARAM_DB_VALUE_FLAG_UNINITIALIZED));
  MTLK_ASSERT(!mtlk_pdb_is_param_flag_set(handle, PARAM_DB_VALUE_FLAG_READONLY));
  MTLK_ASSERT(mtlk_pdb_is_param_of_type(handle, PARAM_DB_TYPE_BINARY));

  if(!size) {
    return MTLK_ERR_PARAMS;
  }

  mtlk_osal_lock_acquire(&handle->param_lock);

  if(size != handle->size) {    /* if same size, do not reallocate memory */
    /* first try to allocate memory, only then release the existing buffer */
    uint8 * temp_ptr =  (uint8 *)mtlk_osal_mem_alloc(size, MTLK_MEM_TAG_PARAM_DB);

    if(!temp_ptr) {
      result = MTLK_ERR_NO_MEM;
      goto end;
    }

    if(handle->value.value_ptr) {
      mtlk_osal_mem_free(handle->value.value_ptr);
    }
    handle->value.value_ptr = temp_ptr;
  }

  memcpy(handle->value.value_ptr, buffer, size);
  handle->size = size;

end:
  mtlk_osal_lock_release(&handle->param_lock);

  return result;
}

/*! Fast get for mac parameters

    \param  handle  Handle to parameter that was opened using mtlk_pdb_open
    \param  buffer   Pointer to variable that will receive parameter's value

*/
static void __INLINE mtlk_pdb_fast_get_mac(mtlk_pdb_handle_t handle, void * buffer) {
  MTLK_ASSERT(NULL != handle);
  MTLK_ASSERT(NULL != buffer);
  MTLK_ASSERT(!mtlk_pdb_is_param_flag_set(handle, PARAM_DB_VALUE_FLAG_UNINITIALIZED));
  MTLK_ASSERT(mtlk_pdb_is_param_of_type(handle, PARAM_DB_TYPE_MAC));

  mtlk_osal_lock_acquire(&handle->param_lock);
  memcpy(buffer, handle->value.value_ptr, handle->size);
  mtlk_osal_lock_release(&handle->param_lock);
}


/*! Fast sets the value of parameter of the mac type
    As the size of mac is known we can optimize accessor function

    \param  handle  Handle to parameter that was opened using mtlk_pdb_open
    \param  value   New parameter's value
*/
static void __INLINE mtlk_pdb_fast_set_mac(mtlk_pdb_handle_t handle, const void * buffer) {
  MTLK_ASSERT(NULL != handle);
  MTLK_ASSERT(NULL != buffer);

  MTLK_ASSERT(!mtlk_pdb_is_param_flag_set(handle, PARAM_DB_VALUE_FLAG_UNINITIALIZED));
  MTLK_ASSERT(!mtlk_pdb_is_param_flag_set(handle, PARAM_DB_VALUE_FLAG_READONLY));
  MTLK_ASSERT(mtlk_pdb_is_param_of_type(handle, PARAM_DB_TYPE_MAC));


  mtlk_osal_lock_acquire(&handle->param_lock);
  memcpy(handle->value.value_ptr, buffer, ETH_ALEN);
  mtlk_osal_lock_release(&handle->param_lock);
}

/*! Fast compare  for mac parameters

    \param  handle  Handle to parameter that was opened using mtlk_pdb_open
    \param  buffer   Pointer to the buffer that will be compared with parameter
    \param  size   Size of the buffer that need comparison.

    \return <0      if parameter's buffer less than supplied buffer
    \return 0      if parameter's buffer identical to supplied buffer
    \return >0      if parameter's buffer greater than supplied buffer
*/
static int __INLINE mtlk_pdb_fast_cmp_mac(mtlk_pdb_handle_t handle, const void * buffer) {
  int result;

  MTLK_ASSERT(NULL != handle);
  MTLK_ASSERT(NULL != buffer);
  MTLK_ASSERT(!mtlk_pdb_is_param_flag_set(handle, PARAM_DB_VALUE_FLAG_UNINITIALIZED));
  MTLK_ASSERT(mtlk_pdb_is_param_of_type(handle, PARAM_DB_TYPE_MAC));

  mtlk_osal_lock_acquire(&handle->param_lock);
  result = memcmp(handle->value.value_ptr, buffer, handle->size);
  mtlk_osal_lock_release(&handle->param_lock);

  return result;
}


/*! Runs different tests with current module's functions. MTLK_PDB_UNIT_TEST should be defined to enable the compilation of functioning function

    \param  obj  Initialized parameter db object to test

    \return MTLK_ERR_xxx   According to test case
*/
int __MTLK_IFUNC mtlk_pdb_unit_test(mtlk_pdb_t* obj);

#undef LOG_LOCAL_GID
#undef LOG_LOCAL_FID

#define   MTLK_IDEFS_OFF
#include "mtlkidefs.h"

#endif /* __MTLK_PARAM_DB_H__ */
