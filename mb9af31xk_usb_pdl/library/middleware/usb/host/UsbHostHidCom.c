/*******************************************************************************
* Copyright (C) 2013-2016, Cypress Semiconductor Corporation or a              *
* subsidiary of Cypress Semiconductor Corporation.  All rights reserved.       *
*                                                                              *
* This software, including source code, documentation and related              *
* materials ("Software"), is owned by Cypress Semiconductor Corporation or     *
* one of its subsidiaries ("Cypress") and is protected by and subject to       *
* worldwide patent protection (United States and foreign), United States       *
* copyright laws and international treaty provisions. Therefore, you may use   *
* this Software only as provided in the license agreement accompanying the     *
* software package from which you obtained this Software ("EULA").             *
*                                                                              *
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,     *
* non-transferable license to copy, modify, and compile the                    *
* Software source code solely for use in connection with Cypress's             *
* integrated circuit products.  Any reproduction, modification, translation,   *
* compilation, or representation of this Software except as specified          *
* above is prohibited without the express written permission of Cypress.       *
*                                                                              *
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO                         *
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,                         *
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED                                 *
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A                              *
* PARTICULAR PURPOSE. Cypress reserves the right to make                       *
* changes to the Software without notice. Cypress does not assume any          *
* liability arising out of the application or use of the Software or any       *
* product or circuit described in the Software. Cypress does not               *
* authorize its products for use in any products where a malfunction or        *
* failure of the Cypress product may reasonably be expected to result in       *
* significant property damage, injury or death ("High Risk Product"). By       *
* including Cypress's product in a High Risk Product, the manufacturer         *
* of such system or application assumes all risk of such use and in doing      *
* so agrees to indemnify Cypress against all liability.                        *
*******************************************************************************/
/******************************************************************************/
/** \file UsbHostHidCom.c
 **
 ** Part of FSEU USB Host Driver Module for use with Fujitsu HID Com Device
 **
 ** A detailed description is available at 
 ** @link UsbHostHidComGroup USB Host HID Com Module description @endlink
 **
 ** History:
 **   - 2012-07-18    1.0  MSc  First version 
 **   - 2013-10-14    1.1  MSc  PDL support added
 **   - 2014-09-03    1.2  MSc  Deinit routine fixed
 **                             Switched to dynamic driver registering
 **   - 2015-05-04    1.3  MSCH deinitialization added after unsuccessful init   
 **   - 2015-07-21    1.4  MSCH correct initialization for all variables added
 **   - 2015-09-04    1.5  MSCH Usb_WaitHook() added
 *****************************************************************************/


/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/

#include "usbhosthidcom.h"

#if ((FM_PERIPHERAL_USB_HOST_ENABLED == ON) && (USBHOSTHIDCOM_ENABLED == ON))
#include "usbhostclasssupervisor.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/


/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/

static stc_host_endpoint_t *EndpointOUT;
static stc_host_endpoint_t *EndpointIN;
static uint8_t        u8EndpointIN, u8EndpointOUT;
static uint16_t       u16MaxPackageSizeIN, u16MaxPackageSizeOUT;
static volatile boolean_t bDataSent = FALSE;
static volatile boolean_t bDataSending = FALSE;
static volatile boolean_t bDataReceived = FALSE;
static stc_usbn_t* pstcUsbHandle = NULL;
volatile static uint8_t        u8Status = 0;
void (*UsbHostHidComDataSentHandler)(void) = 0;
void (*UsbHostHidComDataReceivedHandler)(uint8_t* pu8Buffer) = 0;

static uint8_t pu8DataReceived[64];

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

static void DataReceivedHandler(stc_usbn_t* pstcUsb);
static void DataSentHandler(stc_usbn_t* pstcUsb);

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/*****************************************************************************/
/* START Driver Setup                                                        */
/*****************************************************************************/

static const stc_usbhostclasssupervisor_usbclassdriver_t stcDriverSetup = {
    UsbHostHidCom_InitHandler,   //pfnInitClassDriver           deinitialization callback of class driver
    UsbHostHidCom_DeinitHandler, //pfnDeinitClassDriver         initialization callback of class driver
    8021,                        //u16IdVendor                  match vendor ID
    12,                          //u16IdProduct                 match product ID
    0,                           //u8MatchDeviceClass           match device class
    0,                           //u8MatchDeviceSubClass        match device subclass
    0,                           //u8MatchDeviceProtocol        match device protocol
    0,                           //u8MatchInterfaceClass        match interface class
    0,                           //u8MatchInterfaceSubClass     match interface subclass
    0,                           //u8MatchInterfaceProtocol     match interface protocoll
    0,                           //u8Reserved                   reserved for back compatible reasons since UsbClassSupervisor V2.2    
    NULL,                        //pfnDeviceConfigured          device configured callback of class driver
    NULL,                        //pfnPeriodicTaskMs            periodic ms callback for class driver
    NULL,                        //pfnIsActive                  driver is active callback for class driver
};

static stc_linked_list_item_t stcDriverSetupItem;

/**
 ******************************************************************************
 ** \brief Register driver at 
 ** @link UsbHostGroup USB Host Module @endlink
 **
 ******************************************************************************/
void UsbHostHidCom_RegisterDriver(void)
{
    UsbHostClassSupervisor_RegisterClassDriver((stc_usbhostclasssupervisor_usbclassdriver_t*)&stcDriverSetup,&stcDriverSetupItem);
}

/*****************************************************************************/
/* END Driver Setup                                                          */
/*****************************************************************************/


/**
 ******************************************************************************
 ** \brief RX callback
 **
 ** \param pstcUsb Pointer to USB instance
 **
 ******************************************************************************/
static void DataReceivedHandler(stc_usbn_t* pstcUsb)
{
    bDataReceived = TRUE;
    if (UsbHostHidComDataReceivedHandler != 0)
    {
        UsbHostHidComDataReceivedHandler(pu8DataReceived);
        bDataReceived = FALSE;
    }
}

/**
 ******************************************************************************
 ** \brief TX callback
 **
 ** \param pstcUsb Pointer to USB instance
 **
 ******************************************************************************/
static void DataSentHandler(stc_usbn_t* pstcUsb)
{
    bDataSent = TRUE;
    bDataSending = FALSE;
    if (UsbHostHidComDataSentHandler != 0)
    {
        UsbHostHidComDataSentHandler();
        bDataSent = FALSE;
    }
}

/**
 ******************************************************************************
 ** \brief Register TX callback
 **
 ** \param pfnDataSent Callback function
 **
 ******************************************************************************/
void UsbHostHidCom_SetDataSentHandler(pfn_usbhosthidcom_data_sent_t pfnDataSent)
{
    UsbHostHidComDataSentHandler = pfnDataSent;
}

/**
 ******************************************************************************
 ** \brief Register RX callback
 **
 ** \param pfnDataReceived Callback function
 **
 ******************************************************************************/
void UsbHostHidCom_SetDataReceivedHandler(pfn_usbhosthidcom_data_received_t pfnDataReceived)
{
    UsbHostHidComDataReceivedHandler = pfnDataReceived;
}

/**
 ******************************************************************************
 ** \brief Initiate data sending via IRQs
 **
 ** \param pu8Buffer Data to send (64 bytes)
 **
 ******************************************************************************/
void UsbHostHidCom_InitiateSending(uint8_t* pu8Buffer)
{
    bDataSent = FALSE;
    bDataSending = TRUE;
    UsbHost_TransferData(pstcUsbHandle,EndpointOUT,pu8Buffer, 64, DataSentHandler);
}

/**
 ******************************************************************************
 ** \brief Send data polled
 **
 ** \param pu8Buffer Data to send (64 bytes)
 **
 ******************************************************************************/
void UsbHostHidCom_SendPolled(uint8_t* pu8Buffer)
{
    bDataSent = FALSE;
    bDataSending = TRUE;
    UsbHost_TransferData(pstcUsbHandle,EndpointOUT,pu8Buffer, 64, DataSentHandler);
    while(bDataSent == FALSE)
    {
        Usb_WaitHook();
    }
}

/**
 ******************************************************************************
 ** \brief Receive data polled
 **
 ** \returns on success pointer to data, else NULL
 **
 ******************************************************************************/
uint8_t* UsbHostHidCom_ReceivePolled(void)
{
    while(bDataReceived == FALSE)
    {
        Usb_WaitHook();
    }
    bDataReceived = FALSE;
    return pu8DataReceived;
}

/**
 ******************************************************************************
 ** \brief Get status if data was sent
 **
 ** \returns TRUE, if data was sent
 **
 ******************************************************************************/
boolean_t UsbHostHidCom_IsSent(void)
{
    return bDataSent;
}

/**
 ******************************************************************************
 ** \brief Get status if data is still sending
 **
 ** \returns TRUE, if data is still sending
 **
 ******************************************************************************/
boolean_t UsbHostHidCom_IsSending(void)
{
    return bDataSending;
}

/**
 ******************************************************************************
 ** \brief Get status if data was received
 **
 ** \returns TRUE, if data was received
 **
 ******************************************************************************/
boolean_t UsbHostHidCom_IsReceived(void)
{
    return bDataReceived;
}


/**
 ******************************************************************************
 ** \brief Called from USB Host Class Supervisor to initialize this driver
 **
 ** \param pstcUsb USB handle
 **
 ** \param pu8Configuration configuration data
 **
 ** \param u32Length data length
 **
 ** \returns TRUE on success
 **
 ******************************************************************************/
boolean_t UsbHostHidCom_InitHandler(stc_usbn_t* pstcUsb, uint8_t* pu8Configuration, uint32_t u32Length)
{
    uint8_t* pu8Buffer;
    uint8_t u8NumberOfInterfaces;
    uint8_t u8NumberOfEndpoints;
    uint8_t u8EndpointNumber;
    uint8_t u8InterfaceNumber;
    if (pstcUsbHandle != NULL)
    {
        return FALSE;
    }
    pstcUsbHandle = pstcUsb;
    bDataSent = FALSE;
    bDataSending = FALSE;
    bDataReceived = FALSE;
    
    EndpointOUT = NULL;
    EndpointIN = NULL;
    u8EndpointIN = 0;
    u8EndpointOUT = 0;
    u16MaxPackageSizeIN = 0;
    u16MaxPackageSizeOUT = 0;
    u8Status = 0;

    u8NumberOfInterfaces=pu8Configuration[4];
    for(u8InterfaceNumber=0;u8InterfaceNumber < u8NumberOfInterfaces;u8InterfaceNumber++)
    {
        pu8Buffer = UsbHost_GetUsbInterfaceDescriptor(pu8Configuration,u32Length,u8InterfaceNumber);
        if (pu8Buffer == 0)
        {
            UsbHostHidCom_DeinitHandler(pstcUsb);
            return FALSE;
        }
        u8NumberOfEndpoints = pu8Buffer[4];
        
        if ((pu8Buffer[5] == 0x03) && (pu8Buffer[6] == 0x00) && (pu8Buffer[7] == 0x0)) //Class & SubClass & Protocol
        {
            for(u8EndpointNumber=1;u8EndpointNumber<=u8NumberOfEndpoints;u8EndpointNumber++)
            {
                pu8Buffer = UsbHost_GetUsbEndpointDescriptor(pu8Configuration,u32Length,u8InterfaceNumber,u8EndpointNumber);
                if (pu8Buffer[2] & USB_IN_DIRECTION)
                {
                    u8EndpointIN = pu8Buffer[2];
                    u16MaxPackageSizeIN = (uint16_t)(pu8Buffer[4] + (pu8Buffer[5] << 8));
                }
                else
                {
                    u8EndpointOUT = pu8Buffer[2];
                    u16MaxPackageSizeOUT = (uint16_t)(pu8Buffer[4] + (pu8Buffer[5] << 8));
                }
                if ((u8EndpointIN != 0) && (u8EndpointOUT != 0))
                {
                    break;
                }
            }
            if ((u8EndpointIN == 0) && (u8EndpointOUT == 0))
            {
                UsbHostHidCom_DeinitHandler(pstcUsb);
                return FALSE;
            }

            
            UsbHost_AddHostEndpoint(pstcUsbHandle,&EndpointOUT,u8EndpointOUT,u16MaxPackageSizeOUT,10,DataSentHandler);
            UsbHost_AddHostEndpoint(pstcUsbHandle,&EndpointIN,u8EndpointIN,u16MaxPackageSizeIN,10,DataReceivedHandler);
            EndpointIN->pu8Buffer = pu8DataReceived;
            EndpointIN->u32DataSize = 64; 
            break;
        }
    }
    if ((u8EndpointIN == 0) || (u8EndpointOUT == 0))
    {
        UsbHostHidCom_DeinitHandler(pstcUsb);
        return FALSE;
    }       
    return TRUE;               
}

/**
 ******************************************************************************
 ** \brief Called from USB Host Class Supervisor to deinitialize this driver
 **
 ** \param pstcUsb USB handle
 **
 ** \returns TRUE on success
 **
 ******************************************************************************/
boolean_t UsbHostHidCom_DeinitHandler(stc_usbn_t* pstcUsb)
{
    if (pstcUsb == pstcUsbHandle)
    {
        pstcUsbHandle = NULL;
        bDataSent = FALSE;
        bDataSending = FALSE;
        bDataReceived = FALSE;
        u8Status = 0;
        return TRUE;
    }
    return FALSE;
}

/**
 ******************************************************************************
 ** \brief Returns if the driver is active
 **
 ** \returns TRUE if it is active
 **
 ******************************************************************************/
boolean_t UsbHostHidCom_DriverActive(void)
{
    return (pstcUsbHandle != NULL);
}

#endif /* ((FM_PERIPHERAL_USB_HOST_ENABLED == ON) && (USBHOSTHIDCOM_ENABLED == ON)) */

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
