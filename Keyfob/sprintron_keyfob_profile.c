/**************************************************************************************************
  Filename:       sprintronKeyfob.c
  Revised:        $Date: 2013-08-15 15:28:40 -0700 (Thu, 15 Aug 2013) $
  Revision:       $Revision: 34986 $

  Description:    Proximity Profile - Reporter Role


  Copyright 2009 - 2013 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED �AS IS� WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, 
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, 
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com. 
**************************************************************************************************/

/*********************************************************************
 * INCLUDES
 */
#include "bcomdef.h"
#include "OSAL.h"
#include "linkdb.h"
#include "att.h"
#include "gatt.h"
#include "gatt_uuid.h"
#include "gatt_profile_uuid.h"
#include "gattservapp.h"
#include "gapbondmgr.h"
#include "OSAL_PwrMgr.h"
#include "osal_snv.h"
#include "sprintron_keyfob_profile.h"
#include "peripheral.h"

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */

// Sprintron Man Sec Service UUID
CONST uint8 sprintronManSecServiceUUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16( SPRINTRON_MAN_SEC_SERVICE_UUID ), HI_UINT16( SPRINTRON_MAN_SEC_SERVICE_UUID )
};

// Sprintron Man Sec UUID
CONST uint8 sprintronManSecUUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16( SPRINTRON_MAN_SEC_UUID ), HI_UINT16( SPRINTRON_MAN_SEC_UUID )
};

// Sprintron RSSI Report Service UUID
CONST uint8 sprintronRssiReportServiceUUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16( SPRINTRON_RSSI_REPORT_SERVICE_UUID ), HI_UINT16( SPRINTRON_RSSI_REPORT_SERVICE_UUID )
};

// Sprintron RSSI Report UUID
CONST uint8 sprintronRssiReportUUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16( SPRINTRON_RSSI_VALUE_UUID ), HI_UINT16( SPRINTRON_RSSI_VALUE_UUID )
};

// Sprintron Proximity Alert Service UUID
CONST uint8 sprintronProximityAlertServiceUUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16( SPRINTRON_PROXIMITY_ALERT_SERVICE_UUID ), HI_UINT16( SPRINTRON_PROXIMITY_ALERT_SERVICE_UUID )
};

// Sprintron Proximity Config UUID
CONST uint8 sprintronProximityConfigUUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16( SPRINTRON_PROXIMITY_CONFIG_UUID ), HI_UINT16( SPRINTRON_PROXIMITY_CONFIG_UUID )
};

// Sprintron Proximity Alert UUID
CONST uint8 sprintronProximityAlertUUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16( SPRINTRON_PROXIMITY_ALERT_UUID ), HI_UINT16( SPRINTRON_PROXIMITY_ALERT_UUID )
};

// Sprintron Client Tx Power Service UUID
CONST uint8 sprintronClientTxPowerServiceUUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16( SPRINTRON_CLIENT_TX_POWER_SERVICE_UUID ), HI_UINT16( SPRINTRON_CLIENT_TX_POWER_SERVICE_UUID )
};

// Sprintron Client Tx Power UUID
CONST uint8 sprintronClientTxPowerUUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16( SPRINTRON_CLIENT_TX_POWER_UUID ), HI_UINT16( SPRINTRON_CLIENT_TX_POWER_UUID )
};

// Sprintron Client Audio Visual Alert Service UUID
CONST uint8 sprintronAudioVisualAlertServiceUUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16( SPRINTRON_AUDIO_VISUAL_ALERT_SERVICE_UUID ), HI_UINT16( SPRINTRON_AUDIO_VISUAL_ALERT_SERVICE_UUID )
};

// Sprintron Audio Visual Alert UUID
CONST uint8 sprintronAudioVisualAlertUUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16( SPRINTRON_AUDIO_VISUAL_ALERT_UUID ), HI_UINT16( SPRINTRON_AUDIO_VISUAL_ALERT_UUID )
};

// Sprintron Panic Alert Service UUID
CONST uint8 sprintronPanicAlertServiceUUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16( SPRINTRON_PANIC_ALERT_SERVICE_UUID ), HI_UINT16( SPRINTRON_PANIC_ALERT_SERVICE_UUID )
};

// Sprintron Panic Alert UUID
CONST uint8 sprintronPanicAlertUUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16( SPRINTRON_PANIC_ALERT_UUID ), HI_UINT16( SPRINTRON_PANIC_ALERT_UUID )
};

// Sprintron Device Config Service UUID
CONST uint8 sprintronDeviceConfigServiceUUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16( SPRINTRON_DEVICE_CONFIG_SERVICE_UUID ), HI_UINT16( SPRINTRON_DEVICE_CONFIG_SERVICE_UUID )
};

// Sprintron Device Config Parameters UUID
CONST uint8 sprintronDeviceConfigParametersUUID[ATT_BT_UUID_SIZE] =
{ 
  LO_UINT16( SPRINTRON_DEVICE_CONFIG_PARAMETERS_UUID ), HI_UINT16( SPRINTRON_DEVICE_CONFIG_PARAMETERS_UUID )
};

/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */
static sprintronKeyfobCBs_t *sk_AppCBs = NULL;

/*********************************************************************
 * Profile Attributes - variables
 */

static CONST gattAttrType_t sprintronManSecService = { ATT_BT_UUID_SIZE, sprintronManSecServiceUUID };
static CONST gattAttrType_t sprintronRssiReportService = { ATT_BT_UUID_SIZE, sprintronRssiReportServiceUUID };
static CONST gattAttrType_t sprintronProximityAlertService = { ATT_BT_UUID_SIZE, sprintronProximityAlertServiceUUID };
static CONST gattAttrType_t sprintronClientTxPowerService = { ATT_BT_UUID_SIZE, sprintronClientTxPowerServiceUUID };
static CONST gattAttrType_t sprintronAudioVisualAlertService = { ATT_BT_UUID_SIZE, sprintronAudioVisualAlertServiceUUID };
static CONST gattAttrType_t sprintronPanicAlertService = { ATT_BT_UUID_SIZE, sprintronPanicAlertServiceUUID };
static CONST gattAttrType_t sprintronDeviceConfigService = { ATT_BT_UUID_SIZE, sprintronDeviceConfigServiceUUID };

static uint8 sprintronManSecCharProps = GATT_PROP_READ | GATT_PROP_WRITE;
static uint8 sprintronManSec[13] = { MAN_SEC_FLAG_UNKNOWN,                    // Flag
                                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00,      // MIC
                                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };    // BD Addr

static uint8 sprintronRssiValueCharProps = GATT_PROP_READ | GATT_PROP_NOTIFY;
static int8 sprintronRssiValue = RSSI_VALUE_DEFAULT_VALUE;
static gattCharCfg_t sprintronRssiValueConfig[GATT_MAX_NUM_CONN];

static uint8 sprintronProximityConfigCharProps = GATT_PROP_READ | GATT_PROP_WRITE;
static int8 sprintronProximityConfig = PROXIMITY_CONFIG_DEFAULT_VALUE;
static uint8 sprintronProximityAlertCharProps = GATT_PROP_READ | GATT_PROP_NOTIFY;
static uint8 sprintronProximityAlert = PROXIMITY_ALERT_IN_RANGE;
static gattCharCfg_t sprintronProximityAlertConfig[GATT_MAX_NUM_CONN];

static uint8 sprintronClientTxPowerCharProps = GATT_PROP_READ | GATT_PROP_WRITE;
static int8 sprintronClientTxPower = CLIENT_TX_POWER_DEFAULT_VALUE;

static uint8 sprintronAudioVisualAlertCharProps = GATT_PROP_READ | GATT_PROP_WRITE;
static uint32 sprintronAudioVisualAlert = AUDIO_VISUAL_ALERT_ALL_OFF;

static uint8 sprintronPanicAlertCharProps = GATT_PROP_READ | GATT_PROP_NOTIFY;
static uint8 sprintronPanicAlert = PANIC_ALERT_OFF;
static gattCharCfg_t sprintronPanicAlertConfig[GATT_MAX_NUM_CONN];

static uint8 sprintronDeviceConfigParametersCharProps = GATT_PROP_READ | GATT_PROP_WRITE;
static uint16 sprintronDeviceConfigParameters[5] = { CONNECTION_INTERVAL_DEFAULT_VALUE,
                                                   SUPERVISION_TIMEOUT_DEFAULT_VALUE,
                                                   SLAVE_LATENCY_DEFAULT_VALUE,
                                                   NORMAL_ADV_INTERVAL_DEFAULT_VALUE,
                                                   AUDIO_VISUAL_ALERT_TIME_DEFAULT_VALUE };

/*********************************************************************
 * Profile Attributes - Table
 */
static gattAttribute_t sprintronManSecAttrTbl[] = 
{  // Sprintron Rssi Report Service
  {
    { ATT_BT_UUID_SIZE, primaryServiceUUID },
    GATT_PERMIT_READ,
    0,
    (uint8 *)&sprintronManSecService
  },
    // Characteristic Declaration
    {
      {ATT_BT_UUID_SIZE, characterUUID},
	  GATT_PERMIT_READ,
	  0,
	  (uint8 *)&sprintronManSecCharProps
    },
      // Man Sec
      { 
        { ATT_BT_UUID_SIZE, sprintronManSecUUID},
        GATT_PERMIT_READ | GATT_PERMIT_WRITE | GATT_PERMIT_AUTHEN_READ | GATT_PERMIT_AUTHEN_WRITE /* | GATT_PERMIT_ENCRYPT_READ | GATT_PERMIT_ENCRYPT_WRITE*/, 
        0, 
        (uint8 *)&sprintronManSec
      },
};

static gattAttribute_t sprintronRssiReportAttrTbl[] =
{
  // Sprintron Rssi Report Service
  {
    { ATT_BT_UUID_SIZE, primaryServiceUUID },
    GATT_PERMIT_READ,
    0,
    (uint8 *)&sprintronRssiReportService
  },
    // Characteristic Declaration
    {
      {ATT_BT_UUID_SIZE, characterUUID},
	  GATT_PERMIT_READ,
	  0,
	  (uint8 *)&sprintronRssiValueCharProps
    },
      // Rssi Report
      { 
        { ATT_BT_UUID_SIZE, sprintronRssiReportUUID},
        GATT_PERMIT_READ, 
        0, 
        (uint8 *)&sprintronRssiValue
      },
        // Characteristic configuration
        { 
          { ATT_BT_UUID_SIZE, clientCharCfgUUID },
          GATT_PERMIT_READ | GATT_PERMIT_WRITE, 
          0, 
          (uint8 *)sprintronRssiValueConfig
        },
};

static gattAttribute_t sprintronProximityAlertAttrTbl[] = 
{
  // Sprintron Proximity Alert Service
  {
    { ATT_BT_UUID_SIZE, primaryServiceUUID },
    GATT_PERMIT_READ,
    0,
    (uint8 *)&sprintronProximityAlertService
  },
    // Characteristic Declaration
    {
      {ATT_BT_UUID_SIZE, characterUUID},
      GATT_PERMIT_READ,
      0,
      (uint8 *)&sprintronProximityConfigCharProps
    },
      // Proximity Config
      { 
        { ATT_BT_UUID_SIZE, sprintronProximityConfigUUID},
        GATT_PERMIT_READ | GATT_PERMIT_WRITE, 
        0, 
        (uint8 *)&sprintronProximityConfig
      },
    // Characteristic Declaration
    {
      {ATT_BT_UUID_SIZE, characterUUID},
      GATT_PERMIT_READ,
      0,
      (uint8 *)&sprintronProximityAlertCharProps
    },
      // Proximity Alert
      { 
        { ATT_BT_UUID_SIZE, sprintronProximityAlertUUID},
        GATT_PERMIT_READ, 
        0,
        (uint8 *)&sprintronProximityAlert
      },
        // Characteristic configuration
        { 
          { ATT_BT_UUID_SIZE, clientCharCfgUUID },
          GATT_PERMIT_READ | GATT_PERMIT_WRITE, 
          0, 
          (uint8 *)sprintronProximityAlertConfig 
        },
};

static gattAttribute_t sprintronClientTxPowerAttrTbl[] = 
{
  // Sprintron Client Tx Power Service
  {
    { ATT_BT_UUID_SIZE, primaryServiceUUID },
    GATT_PERMIT_READ,
    0,
    (uint8 *)&sprintronClientTxPowerService
  },
    // Characteristic Declaration
    {
      {ATT_BT_UUID_SIZE, characterUUID},
      GATT_PERMIT_READ,
      0,
      (uint8 *)&sprintronClientTxPowerCharProps
    },
      // Client Tx Power
      { 
        { ATT_BT_UUID_SIZE, sprintronClientTxPowerUUID},
        GATT_PERMIT_READ | GATT_PERMIT_WRITE, 
        0, 
        (uint8 *)&sprintronClientTxPower
      },
};

static gattAttribute_t sprintronAudioVisualAlertAttrTbl[] = 
{
  // Sprintron Audio Visual Alert Service
  {
    { ATT_BT_UUID_SIZE, primaryServiceUUID },
    GATT_PERMIT_READ,
    0,
    (uint8 *)&sprintronAudioVisualAlertService
  },
    // Characteristic Declaration
    {
      {ATT_BT_UUID_SIZE, characterUUID},
      GATT_PERMIT_READ,
      0,
      (uint8 *)&sprintronAudioVisualAlertCharProps
    },
      // Audio Visual Alert
      { 
        { ATT_BT_UUID_SIZE, sprintronAudioVisualAlertUUID},
        GATT_PERMIT_READ | GATT_PERMIT_WRITE, 
        0, 
        (uint8 *)&sprintronAudioVisualAlert
      },
};

static gattAttribute_t sprintronPanicAlertAttrTbl[] =
{
  // Sprintron Rssi Report Service
  {
    { ATT_BT_UUID_SIZE, primaryServiceUUID },
    GATT_PERMIT_READ,
    0,
    (uint8 *)&sprintronPanicAlertService
  },
    // Characteristic Declaration
    {
      {ATT_BT_UUID_SIZE, characterUUID},
	  GATT_PERMIT_READ,
	  0,
	  (uint8 *)&sprintronPanicAlertCharProps
    },
      // Panic Alert
      { 
        { ATT_BT_UUID_SIZE, sprintronPanicAlertUUID},
        GATT_PERMIT_READ, 
        0, 
        (uint8 *)&sprintronPanicAlert
      },
        // Characteristic configuration
        { 
          { ATT_BT_UUID_SIZE, clientCharCfgUUID },
          GATT_PERMIT_READ | GATT_PERMIT_WRITE, 
          0, 
          (uint8 *)sprintronPanicAlertConfig
        },
};

static gattAttribute_t sprintronDeviceConfigAttrTbl[] = 
{
  // Sprintron Device Config Service
  {
    { ATT_BT_UUID_SIZE, primaryServiceUUID },
    GATT_PERMIT_READ,
    0,
    (uint8 *)&sprintronDeviceConfigService
  },
    // Characteristic Declaration
    {
      {ATT_BT_UUID_SIZE, characterUUID},
      GATT_PERMIT_READ,
      0,
      (uint8 *)&sprintronDeviceConfigParametersCharProps
    },
      // Device Config Parameters
      { 
        { ATT_BT_UUID_SIZE, sprintronDeviceConfigParametersUUID},
        GATT_PERMIT_READ | GATT_PERMIT_WRITE /*| GATT_PERMIT_ENCRYPT_READ | GATT_PERMIT_ENCRYPT_WRITE*/, 
        0, 
        (uint8 *)sprintronDeviceConfigParameters
      },
};

// For Sprintron security service - read primary address from flash
__xdata __no_init uint8 primaryMac[6] @ 0x780E;
uint8 manSecMic[6];
uint8 manSecVerified = FALSE;

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static uint8 sprintronKeyfob_ReadAttrCB( uint16 connHandle, gattAttribute_t *pAttr, 
                                    uint8 *pValue, uint8 *pLen, uint16 offset, uint8 maxLen );
static bStatus_t sprintronKeyfob_WriteAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                                         uint8 *pValue, uint8 len, uint16 offset );

/*********************************************************************
 * PROFILE CALLBACKS
 */
CONST gattServiceCBs_t sprintronKeyfobCBs =
{
  sprintronKeyfob_ReadAttrCB,  // Read callback function pointer
  sprintronKeyfob_WriteAttrCB, // Write callback function pointer
  NULL                      // Authorization callback function pointer
};

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

bool sprintron_checkMIC(uint8 Mac[], uint8 Mic[])
{
  if (osal_memcmp(Mac, Mic, B_ADDR_LEN))
    return true;
  else
    return false;
}

/*********************************************************************
 * @fn      sprintronKeyfob_AddService
 *
 * @brief   Initializes the Proximity Reporter service by
 *          registering GATT attributes with the GATT server.
 *          Only call this function once.
 *
 * @param   services - services to add. This is a bit map and can
 *                     contain more than one service.
 *
 * @return   Success or Failure
 */
bStatus_t sprintronKeyfob_AddService( uint32 services )
{
  uint8 status = SUCCESS;

  if ( services & SPRINTRON_RSSI_MAN_SEC_SERVICE )
  {
    uint8 snvStatus;

	status = GATTServApp_RegisterService( sprintronManSecAttrTbl,
									      GATT_NUM_ATTRS( sprintronManSecAttrTbl ),
										  &sprintronKeyfobCBs);

	// update the primary BD Addr field in Man Sec characteristic
    sprintronManSec[7] = primaryMac[0];
    sprintronManSec[8] = primaryMac[1];
    sprintronManSec[9] = primaryMac[2];
    sprintronManSec[10] = primaryMac[3];
    sprintronManSec[11] = primaryMac[4];
    sprintronManSec[12] = primaryMac[5];
    
    snvStatus = osal_snv_read( SPRINTRON_KEYFOB_NV_ITEM_MIC,
                               sizeof(manSecMic),
                               (uint8 *)manSecMic );

    if (snvStatus == SUCCESS)
    {
      // check if mic is correct and set flag correspondingly.
      if (sprintron_checkMIC(primaryMac, manSecMic))
      {
        manSecVerified = sprintronManSec[0] = TRUE;
      }
      else
      {
        manSecVerified = sprintronManSec[0] = FALSE;
      }
    }
    else
    {
      manSecVerified = sprintronManSec[0] = FALSE;
    }

  }
  
  if ( ( status == SUCCESS ) && ( services & SPRINTRON_RSSI_REPORT_SERVICE ) )
  {
    GATTServApp_InitCharCfg( INVALID_CONNHANDLE, sprintronRssiValueConfig );
    status = GATTServApp_RegisterService( sprintronRssiReportAttrTbl,
                                          GATT_NUM_ATTRS( sprintronRssiReportAttrTbl ),
                                          &sprintronKeyfobCBs);
  }

  if ( ( status == SUCCESS ) && ( services & SPRINTRON_PROXIMITY_ALERT_SERVICE ) )
  {
    GATTServApp_InitCharCfg( INVALID_CONNHANDLE, sprintronProximityAlertConfig );
    status = GATTServApp_RegisterService( sprintronProximityAlertAttrTbl,
                                          GATT_NUM_ATTRS( sprintronProximityAlertAttrTbl ),
                                          &sprintronKeyfobCBs);
  }

  if ( ( status == SUCCESS ) && ( services & SPRINTRON_CLIENT_TX_POWER_SERVICE ) )
  {
    status = GATTServApp_RegisterService( sprintronClientTxPowerAttrTbl,
                                          GATT_NUM_ATTRS( sprintronClientTxPowerAttrTbl ),
                                          &sprintronKeyfobCBs);
  }

  if ( ( status == SUCCESS ) && ( services & SPRINTRON_AUDIO_VISUAL_ALERT_SERVICE ) )
  {
    status = GATTServApp_RegisterService( sprintronAudioVisualAlertAttrTbl,
                                          GATT_NUM_ATTRS( sprintronAudioVisualAlertAttrTbl ),
                                          &sprintronKeyfobCBs);
  }
  
  if ( ( status == SUCCESS ) && ( services & SPRINTRON_PANIC_ALERT_SERVICE) )
  {
    GATTServApp_InitCharCfg( INVALID_CONNHANDLE, sprintronPanicAlertConfig );
    status = GATTServApp_RegisterService( sprintronPanicAlertAttrTbl,
                                          GATT_NUM_ATTRS( sprintronPanicAlertAttrTbl ),
                                          &sprintronKeyfobCBs);
  }

  if ( ( status == SUCCESS ) && ( services & SPRINTRON_DEVICE_CONFIG_SERVICE ) )
  {
    status = GATTServApp_RegisterService( sprintronDeviceConfigAttrTbl,
                                          GATT_NUM_ATTRS( sprintronDeviceConfigAttrTbl ),
                                          &sprintronKeyfobCBs);
  }

  return ( status );
}


/*********************************************************************
 * @fn      sprintronKeyfob_RegisterAppCBs
 *
 * @brief   Registers the application callback function. Only call 
 *          this function once.
 *
 * @param   callbacks - pointer to application callbacks.
 *
 * @return  SUCCESS or bleAlreadyInRequestedMode
 */
bStatus_t sprintronKeyfob_RegisterAppCBs( sprintronKeyfobCBs_t *appCallbacks )
{
  if ( appCallbacks )
  {
    sk_AppCBs = appCallbacks;
    
    return ( SUCCESS );
  }
  else
  {
    return ( bleAlreadyInRequestedMode );
  }
}
   

/*********************************************************************
 * @fn      sprintronKeyfob_SetParameter
 *
 * @brief   Set a Proximity Reporter parameter.
 *
 * @param   param - Profile parameter ID
 * @param   len - length of data to right
 * @param   value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate 
 *          data type (example: data type of uint16 will be cast to 
 *          uint16 pointer).
 *
 * @return  bStatus_t
 */
bStatus_t sprintronKeyfob_SetParameter( uint8 param, uint8 len, void *value )
{
  bStatus_t ret = SUCCESS;
  switch ( param )
  {
    case SPRINTRON_MAN_SEC_PERMISSION: 
      sprintronManSecAttrTbl[2].permissions = *((uint8 *)value);
      break;
      
    case SPRINTRON_MAN_SEC:
	  if ( len == sizeof ( sprintronManSec ) )
	  {
        osal_memcpy(sprintronManSec, value, sizeof(sprintronManSec));
	  }
	  else
	  {
	    ret = bleInvalidRange;
	  }
	  break;
	  
    case SPRINTRON_RSSI_VALUE:
      if ( len == sizeof ( sprintronRssiValue ) ) 
      {
        sprintronRssiValue = *((int8*)value);
		
        // See if Notification has been enabled
        GATTServApp_ProcessCharCfg( sprintronRssiValueConfig, (uint8 *)&sprintronRssiValue, FALSE, 
                                    sprintronRssiReportAttrTbl, GATT_NUM_ATTRS( sprintronRssiReportAttrTbl ),
                                    INVALID_TASK_ID );
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

	case SPRINTRON_PROXIMITY_CONFIG:
      if ( len == sizeof ( sprintronProximityConfig ) ) 
      {
        sprintronProximityConfig = *((int8*)value);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case SPRINTRON_PROXIMITY_ALERT:
      if ( len == sizeof ( sprintronProximityAlert ) )
      {
        sprintronProximityAlert = *((uint8*)value);
        
        // See if Notification has been enabled
        GATTServApp_ProcessCharCfg( sprintronProximityAlertConfig, (uint8 *)&sprintronProximityAlert, FALSE, 
                                    sprintronProximityAlertAttrTbl, GATT_NUM_ATTRS( sprintronProximityAlertAttrTbl ),
                                    INVALID_TASK_ID );
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case SPRINTRON_CLIENT_TX_POWER:
      if ( len == sizeof ( sprintronClientTxPower ) ) 
      {
        sprintronClientTxPower = *((int8*)value);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

	case SPRINTRON_AUDIO_VISUAL_ALERT:
      if ( len == sizeof ( sprintronAudioVisualAlert ) )
      {
        sprintronAudioVisualAlert = *((uint32*)value);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;
      
	case SPRINTRON_PANIC_ALERT:
      if ( len == sizeof ( sprintronPanicAlert ) ) 
      {
        sprintronPanicAlert = *((uint8*)value);

		if (sprintronPanicAlert == PANIC_ALERT_ON)
		{
          // See if Notification has been enabled
          GATTServApp_ProcessCharCfg( sprintronPanicAlertConfig, (uint8 *)&sprintronPanicAlert, FALSE, 
                                      sprintronPanicAlertAttrTbl, GATT_NUM_ATTRS( sprintronPanicAlertAttrTbl ),
                                      INVALID_TASK_ID );
        }
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

	case SPRINTRON_DEVICE_CONFIG_PARAMETERS:
      if ( len == sizeof ( sprintronDeviceConfigParameters ) )
      { 
		osal_memcpy(sprintronDeviceConfigParameters, value, sizeof(sprintronDeviceConfigParameters));
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    default:
      ret = INVALIDPARAMETER;
      break;
  }
  
  return ( ret );
}

/*********************************************************************
 * @fn      sprintronKeyfob_GetParameter
 *
 * @brief   Get a Proximity Reporter parameter.
 *
 * @param   param - Profile parameter ID
 * @param   value - pointer to data to put.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate 
 *          data type (example: data type of uint16 will be cast to 
 *          uint16 pointer).
 *
 * @return  bStatus_t
 */
bStatus_t sprintronKeyfob_GetParameter( uint8 param, void *value )
{
  bStatus_t ret = SUCCESS;
  switch ( param )
  {
    case SPRINTRON_MAN_SEC_PERMISSION: 
      *((uint8*)value) = sprintronManSecAttrTbl[2].permissions;
      break;
      
    case SPRINTRON_MAN_SEC:
      osal_memcpy(value, sprintronManSec, sizeof(sprintronManSec));
      break;

    case SPRINTRON_RSSI_VALUE:
      *((int8*)value) = sprintronRssiValue;
      break;
      
    case SPRINTRON_PROXIMITY_CONFIG:
      *((int8*)value) = sprintronProximityConfig;
      break;
      
    case SPRINTRON_PROXIMITY_ALERT:
      *((uint8*)value) = sprintronProximityAlert;
      break;

    case SPRINTRON_CLIENT_TX_POWER:
      *((int8*)value) = sprintronClientTxPower;
      break;

    case SPRINTRON_AUDIO_VISUAL_ALERT:
      *((uint32*)value) = sprintronAudioVisualAlert;
      break;
      
	case SPRINTRON_PANIC_ALERT:
      *((uint8*)value) = sprintronPanicAlert;
      break;

    case SPRINTRON_DEVICE_CONFIG_PARAMETERS:
      osal_memcpy(value, sprintronDeviceConfigParameters, sizeof(sprintronDeviceConfigParameters));
      break;

    default:
      ret = INVALIDPARAMETER;
      break;
  }
  
  return ( ret );
}

/*********************************************************************
 * @fn          sprintronKeyfob_ReadAttrCB
 *
 * @brief       Read an attribute.
 *
 * @param       
 *
 * @return      Success or Failure
 */
static uint8 sprintronKeyfob_ReadAttrCB( uint16 connHandle, gattAttribute_t *pAttr, 
                                    uint8 *pValue, uint8 *pLen, uint16 offset, uint8 maxLen )
{
  uint16 uuid;
  bStatus_t status = SUCCESS;

  // Make sure it's not a blob operation
  if ( offset > 0 )
  {
    return ( ATT_ERR_ATTR_NOT_LONG );
  }  

  if ( pAttr->type.len == ATT_BT_UUID_SIZE )
  {
    // 16-bit UUID
    uuid = BUILD_UINT16( pAttr->type.uuid[0], pAttr->type.uuid[1]);
    
    switch ( uuid )
    {
      // No need for "GATT_SERVICE_UUID" or "GATT_CLIENT_CHAR_CFG_UUID" cases;
      // gattserverapp handles those types for reads 
      case SPRINTRON_MAN_SEC_UUID:
        {
          uint16 conn_handle;
          uint8 permission;
            
          GAPRole_GetParameter( GAPROLE_CONNHANDLE, &conn_handle );
          sprintronKeyfob_GetParameter(SPRINTRON_MAN_SEC_PERMISSION, &permission);
            
          if ( (permission & GATT_PERMIT_AUTHEN_READ) && linkDB_Encrypted(connHandle) == FALSE )
          {
            status = ATT_ERR_INSUFFICIENT_AUTHEN;
          }
          else
          {
            *pLen = sizeof(sprintronManSec);
            osal_memcpy(pValue, pAttr->pValue, *pLen);
          }
        }
        break;
        
      case SPRINTRON_RSSI_VALUE_UUID: //sprintronRssiValue
      case SPRINTRON_PROXIMITY_CONFIG_UUID: //sprintronProximityConfig
      //case SPRINTRON_PROXIMITY_ALERT_UUID: //sprintronProximityAlert
      case SPRINTRON_CLIENT_TX_POWER_UUID: //sprintronClientTxPower
      case SPRINTRON_PANIC_ALERT_UUID: //sprintronPanicAlert
        *pLen = 1;
        pValue[0] = *pAttr->pValue;
        break;

      // Add here for debugging - remove before production
      case SPRINTRON_PROXIMITY_ALERT_UUID: //sprintronProximityAlert
        *pLen = 1;
        pValue[0] = pwrmgr_attribute.pwrmgr_device;
        break;
        
      case SPRINTRON_AUDIO_VISUAL_ALERT_UUID:
        *pLen = sizeof(sprintronAudioVisualAlert);
        *((uint32 *)pValue) = *((uint32 *)(pAttr->pValue));

        break;
        
      case SPRINTRON_DEVICE_CONFIG_PARAMETERS_UUID:
        *pLen = sizeof(sprintronDeviceConfigParameters);
        osal_memcpy(pValue, pAttr->pValue, *pLen);
        break;

      default:
        // Should never get here!
        *pLen = 0;
        status = ATT_ERR_ATTR_NOT_FOUND;
        break;
    }
  }
  else
  {
    //128-bit UUID
    *pLen = 0;
    status = ATT_ERR_INVALID_HANDLE;
  }

  return ( status );
}

/*********************************************************************
 * @fn      sprintronKeyfob_WriteAttrCB
 *
 * @brief   Validate attribute data prior to a write operation
 *
 * @param   connHandle � connection message was received on
 * @param   pReq - pointer to request
 *
 * @return  Success or Failure
 */
static bStatus_t sprintronKeyfob_WriteAttrCB( uint16 connHandle, gattAttribute_t *pAttr,
                                                 uint8 *pValue, uint8 len, uint16 offset )
{
  bStatus_t status = SUCCESS;
  uint8 notify = 0xFF;

  if ( pAttr->type.len == ATT_BT_UUID_SIZE )
  { 
    // 16-bit UUID
    uint16 uuid = BUILD_UINT16( pAttr->type.uuid[0], pAttr->type.uuid[1]);
    switch ( uuid )
    {
      case SPRINTRON_MAN_SEC_UUID:
        {
          uint16 conn_handle;
          uint8 permission;
          
          GAPRole_GetParameter( GAPROLE_CONNHANDLE, &conn_handle );
          sprintronKeyfob_GetParameter(SPRINTRON_MAN_SEC_PERMISSION, &permission);
          
          if ( (permission & GATT_PERMIT_AUTHEN_WRITE) && linkDB_Encrypted(connHandle) == FALSE )
          {
            //We need authentication, and the link is not yet authenticated, 
            //so return the error code to make iPhone start pairing process.
            status = ATT_ERR_INSUFFICIENT_AUTHEN;
          }
          else
          {
            if ( len > sizeof(sprintronManSec) )
            {
              status = ATT_ERR_INVALID_VALUE_SIZE;
            }
            else
            {
              //[Important Sprintron Note] - the field can be written by the user, but we don't update it for better security.
              //When peer device writes MIC, we check if the MIC match the primaryMac. 
              //If match, then it is verified successfully so we set Flag to 1 to tell peer device that it doesn't have to verify in future connection.
              //If not match, then the device is bad. We set Flag to 0 to tell peer device it failed. Peer device can try to verify again.
  		      osal_memcpy( (void*)manSecMic, (void*)(pValue + 1), sizeof(manSecMic) );
  		      
              if (sprintron_checkMIC(primaryMac, manSecMic))
              {
                //keyfob keep the state
                manSecVerified = TRUE;
                
                //tell peer device the state
                sprintronManSec[0] = TRUE;
              }
              else
              {
                //keyfob keep the state
                manSecVerified = FALSE;
                
                //tell peer device the state
                sprintronManSec[0] = FALSE;
              }

              //store the MIC in NV so next time when keyfob bootup we can calculate the verify state.
              VOID osal_snv_write( SPRINTRON_KEYFOB_NV_ITEM_MIC,
                                   sizeof(manSecMic),
                                   (uint8 *)manSecMic );

              notify = SPRINTRON_MAN_SEC;
            }
          }
        }
        break;
		
      case SPRINTRON_CLIENT_TX_POWER_UUID:
        if (len > sizeof(sprintronClientTxPower) )
        {
          status = ATT_ERR_INVALID_VALUE_SIZE;
        }
        else
        {
          //Write the value
          int8 *pCurValue = (int8 *)pAttr->pValue;
          *pCurValue = pValue[0];
          notify = SPRINTRON_CLIENT_TX_POWER;             
        }
        break;

      case SPRINTRON_PROXIMITY_CONFIG_UUID:
        if (len > sizeof(sprintronProximityConfig) )
        {
          status = ATT_ERR_INVALID_VALUE_SIZE;
        }
        else
        {
          //Write the value
          int8 *pCurValue = (int8 *)pAttr->pValue;
          *pCurValue = pValue[0];
          notify = SPRINTRON_PROXIMITY_CONFIG;     			
        }
        break;

      case SPRINTRON_AUDIO_VISUAL_ALERT_UUID:
        if (len > sizeof(sprintronAudioVisualAlert))
        {
          status = ATT_ERR_INVALID_VALUE_SIZE;
        }
        else
        {
          uint32 *pCurValue = (uint32 *)pAttr->pValue;
          *pCurValue = ((uint32 *)pValue)[0];
          notify = SPRINTRON_AUDIO_VISUAL_ALERT;    			
        }
        break;

      case SPRINTRON_DEVICE_CONFIG_PARAMETERS_UUID:
        if ( len > sizeof(sprintronDeviceConfigParameters) )
        {
          status = ATT_ERR_INVALID_VALUE_SIZE;
        }
        else
        {  
          uint16 *pCurValue = (uint16 *)pAttr->pValue;
		  
		  // if connection parameters are changed, send connection update hci command to iPhone. 3 uint16 are equal to 6 bytes.
		  if ( !osal_memcmp( (void*)pValue, (void*)pCurValue, 6) )
		  {
			GAPRole_SendUpdateParam( ((uint16*)pValue)[CONFIG_IDX_CONNECTION_INTERVAL], 
									  ((uint16*)pValue)[CONFIG_IDX_CONNECTION_INTERVAL] + CONNECTION_INTERVAL_MIN_MAX_DIFFERENCE,
									  ((uint16*)pValue)[CONFIG_IDX_SLAVE_LATENCY], 
									  ((uint16*)pValue)[CONFIG_IDX_SUPERVISION_TIMEOUT],
									  GAPROLE_NO_ACTION );
		  }
			
		  // if normal adv interval is changed, call GAP api to update normal adv interval.
		  if ( !osal_memcmp( (void*)((uint16*)pValue + CONFIG_IDX_NORMAL_ADV_INTERVAL), 
								(void*)(pCurValue + CONFIG_IDX_NORMAL_ADV_INTERVAL), 2) )
		  {
			GAP_SetParamValue( TGAP_CONN_ADV_INT_MIN, ((uint16*)pValue)[CONFIG_IDX_NORMAL_ADV_INTERVAL] );
			GAP_SetParamValue( TGAP_CONN_ADV_INT_MAX, ((uint16*)pValue)[CONFIG_IDX_NORMAL_ADV_INTERVAL] );
			GAP_SetParamValue( TGAP_GEN_DISC_ADV_INT_MIN, ((uint16*)pValue)[CONFIG_IDX_NORMAL_ADV_INTERVAL] );
			GAP_SetParamValue( TGAP_GEN_DISC_ADV_INT_MAX, ((uint16*)pValue)[CONFIG_IDX_NORMAL_ADV_INTERVAL] );
			GAP_SetParamValue( TGAP_LIM_DISC_ADV_INT_MIN, ((uint16*)pValue)[CONFIG_IDX_NORMAL_ADV_INTERVAL] );
			GAP_SetParamValue( TGAP_LIM_DISC_ADV_INT_MAX, ((uint16*)pValue)[CONFIG_IDX_NORMAL_ADV_INTERVAL] );
		  }
		  
		  // do not really update connection parameters until the current connection parameters is really changed.
		  osal_memcpy( (void*)(pCurValue + CONFIG_IDX_NORMAL_ADV_INTERVAL), (uint16*)pValue + CONFIG_IDX_NORMAL_ADV_INTERVAL, 4);
		  
          notify = SPRINTRON_DEVICE_CONFIG_PARAMETERS;
        }
        break;
        
      case GATT_CLIENT_CHAR_CFG_UUID:
        status = GATTServApp_ProcessCCCWriteReq( connHandle, pAttr, pValue, len,
                                                 offset, GATT_CLIENT_CFG_NOTIFY );
        break;
        
      default:
        // Should never get here!
        status = ATT_ERR_ATTR_NOT_FOUND;
        break;
    }
  }
  else
  {
    // 128-bit UUID
    status = ATT_ERR_INVALID_HANDLE;
  }    
  
  // If an attribute changed then callback function to notify application of change
  if ( (notify != 0xFF) && sk_AppCBs && sk_AppCBs->pfnAttrChange )
    sk_AppCBs->pfnAttrChange( notify );

  return ( status );
}

/*********************************************************************
*********************************************************************/
