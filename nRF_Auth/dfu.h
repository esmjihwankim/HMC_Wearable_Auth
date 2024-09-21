#ifndef _DFU_H
#define _DFU_H


#include <stdbool.h>

/* Power Related */
#include "nrf_power.h" 
#include "nrf_pwr_mgmt.h"

/* Bluetooth Related */
//#include "bluetooth.h"

/* DFU Specific */ 
#include "nrf_dfu_ble_svci_bond_sharing.h" 
#include "nrf_svci_async_function.h"
#include "nrf_svci_async_handler.h" 
#include "ble_dfu.h" 
#include "nrf_bootloader_info.h" 

#include "peer_manager_types.h"
#include "peer_manager_handler.h"
#include "fds.h"


/* Definitions for DFU */ 
#define SEC_PARAM_BOND                  1                                           /**< Perform bonding. */
#define SEC_PARAM_MITM                  0                                           /**< Man In The Middle protection not required. */
#define SEC_PARAM_LESC                  0                                           /**< LE Secure Connections not enabled. */
#define SEC_PARAM_KEYPRESS              0                                           /**< Keypress notifications not enabled. */
#define SEC_PARAM_IO_CAPABILITIES       BLE_GAP_IO_CAPS_NONE                        /**< No I/O capabilities. */
#define SEC_PARAM_OOB                   0                                           /**< Out Of Band data not available. */
#define SEC_PARAM_MIN_KEY_SIZE          7                                           /**< Minimum encryption key size. */
#define SEC_PARAM_MAX_KEY_SIZE          16                                          /**< Maximum encryption key size. */

void peer_manager_init();
void ble_dfu_evt_handler(ble_dfu_buttonless_evt_type_t event);




#endif