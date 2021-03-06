/*************************************************************************************
* Copyright (C) 2013-2015, Cypress Semiconductor Corporation. All rights reserved.    
*                                                                                     
* This software, including source code, documentation and related                     
* materials ( "Software" ), is owned by Cypress Semiconductor                         
* Corporation ( "Cypress" ) and is protected by and subject to worldwide              
* patent protection (United States and foreign), United States copyright              
* laws and international treaty provisions. Therefore, you may use this               
* Software only as provided in the license agreement accompanying the                 
* software package from which you obtained this Software ( "EULA" ).                  
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,             
* non-transferable license to copy, modify, and compile the                           
* Software source code solely for use in connection with Cypress's                    
* integrated circuit products. Any reproduction, modification, translation,           
* compilation, or representation of this Software except as specified                 
* above is prohibited without the express written permission of Cypress.              
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO                                
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,                                
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED                                        
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A                                     
* PARTICULAR PURPOSE. Cypress reserves the right to make                              
* changes to the Software without notice. Cypress does not assume any                 
* liability arising out of the application or use of the Software or any              
* product or circuit described in the Software. Cypress does not                      
* authorize its products for use in any products where a malfunction or               
* failure of the Cypress product may reasonably be expected to result in              
* significant property damage, injury or death ( "High Risk Product" ). By            
* including Cypress's product in a High Risk Product, the manufacturer                
* of such system or application assumes all risk of such use and in doing             
* so agrees to indemnify Cypress against all liability.                               
*/
/******************************************************************************/
/** \file rc.h
 **
 ** Headerfile for Remote Control functions
 **  
 ** History:
 **   - 2015-02-05  1.0  KXi  First version for FM universal PDL.
 **
 ******************************************************************************/

#ifndef __RC_H__
#define __RC_H__

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "mcu.h"
#include "pdl_user.h"

#if (defined(PDL_PERIPHERAL_RC_ACTIVE))

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif
  
/**
 ******************************************************************************
 ** \defgroup RcGroup HDMI-CEC/Remote Control Reception/Transmission (RC)
 **
 ** Provided functions of RC module:
 ** - Rc_Rx_Sircs_Init()
 ** - Rc_Rx_Sircs_DeInit()
 ** - Rc_Rx_Sircs_EnableRx()
 ** - Rc_Rx_Sircs_DisableRx()
 ** - Rc_Rx_Sircs_EnableIrq()
 ** - Rc_Rx_Sircs_DisableIrq()  
 ** - Rc_Rx_Sircs_GetIrqFlag()
 ** - Rc_Rx_Sircs_ClrIrqFlag()
 ** - Rc_Rx_Sircs_ReadData()
 ** - Rc_Rx_Nec_Init()
 ** - Rc_Rx_Nec_DeInit()
 ** - Rc_Rx_Nec_EnableRx()
 ** - Rc_Rx_Nec_DisableRx()
 ** - Rc_Rx_Nec_GetIrqFlag()
 ** - Rc_Rx_Nec_ClrIrqFlag()
 ** - Rc_Rx_Nec_EnableIrq()
 ** - Rc_Rx_Nec_DisableIrq()    
 ** - Rc_Rx_Nec_ReadData()
 ** - Rc_Rx_Cec_Init()
 ** - Rc_Rx_Cec_DeInit()
 ** - Rc_Rx_Cec_EnableRx()
 ** - Rc_Rx_Cec_DisableRx()
 ** - Rc_Rx_Cec_GetIrqFlag()
 ** - Rc_Rx_Cec_ClrIrqFlag()
 ** - Rc_Rx_Cec_EnableIrq()
 ** - Rc_Rx_Cec_DisableIrq()    
 ** - Rc_Rx_Cec_ReadData()
 ** - Rc_Tx_Cec_Init()
 ** - Rc_Tx_Cec_DeInit()
 ** - Rc_Tx_Cec_EnableTx()
 ** - Rc_Tx_Cec_DisableTx()   
 ** - Rc_Tx_Cec_GetIrqFlag()
 ** - Rc_Tx_Cec_ClrIrqFlag()
 ** - Rc_Tx_GetAckCycleValue()   
 ** - Rc_Tx_Cec_EnableIrq()
 ** - Rc_Tx_Cec_DisableIrq()
 ** - Rc_Tx_Cec_WriteData()
 ** - Rc_Tx_Cec_SendDataPolling()
 **
 ** Remote Control Reception supports three modes:
 ** - SIRCS mode
 ** - NEC mode
 ** - HDMI-CEC mode
 **
 ** Remote Control transmission only supports HDMI-CEC mode.  
 **
 ** <b> SIRCS mode of Remote Control Reception: </b>
 **  
 ** Rc_Rx_Sircs_Init() configures the Remote Control to SIRCS mode and
 ** Rc_Rx_Sircs_DeInit() reset the Remote Control. 
 **
 ** Rc_Rx_Sircs_EnableRx() enables reception of SIRCS mode in Remote Control 
 ** Reception. Rc_Rx_Sircs_DisableRx() disables reception of SIRCS mode. 
 **
 ** Rc_Rx_Sircs_GetIrqFlag() gets the interrupt flag of SIRCS mode. And 
 ** Rc_Rx_Sircs_ClrIrqFlag() clears the interrupt flag of SIRCS mode.
 **
 ** Interrupts can be configured in Rc_Rx_Sircs_Init() first, after initialization,
 ** Rc_Rx_Sircs_EnableIrq() enables interrupt of SIRCS mode and 
 ** Rc_Rx_Sircs_DisableIrq() disables interrupt of SIRCS mode.   
 **
 ** Rc_Rx_Sircs_ReadData() reads the data received in SIRCS mode.
 **
 ** <b> NEC mode of Remote Control Reception: </b> 
 **  
 ** Rc_Rx_Nec_Init() configures the Remote Control to NEC mode and
 ** Rc_Rx_Nec_DeInit() reset the Remote Control. 
 **
 ** Rc_Rx_Nec_EnableRx() enables reception of NEC mode in Remote Control 
 ** Reception. Rc_Rx_Nec_DisableRx() disables reception of NEC mode. 
 **
 ** Rc_Rx_Nec_GetIrqFlag() gets the interrupt flag of NEC mode. And 
 ** Rc_Rx_Nec_ClrIrqFlag() clears the interrupt flag of NEC mode.
 **
 ** Rc_Rx_Nec_ReadData() reads the data received in NEC mode.  
 **
 ** Interrupts can be configured in Rc_Rx_Nec_Init() first, after initialization,
 ** Rc_Rx_Nec_EnableIrq() enables interrupt of NEC mode and 
 ** Rc_Rx_Nec_DisableIrq() disables interrupt of NEC mode.  
 **   
 ** <b> CEC mode of Remote Control Reception: </b>  
 **  
 ** Rc_Rx_Cec_Init() configures the Remote Control to CEC mode and
 ** Rc_Rx_Cec_DeInit() reset the Remote Control. 
 **
 ** Rc_Rx_Cec_EnableRx() enables reception of CEC mode in Remote Control 
 ** Reception. Rc_Rx_Cec_DisableRx() disables reception of CEC mode. 
 **
 ** Rc_Rx_Cec_GetIrqFlag() gets the interrupt flag of CEC mode. And 
 ** Rc_Rx_Cec_ClrIrqFlag() clears the interrupt flag of CEC mode.
 **
 ** Interrupts can be configured in Rc_Rx_Cec_Init() first, after initialization,
 ** Rc_Rx_Cec_EnableIrq() enables interrupt of CEC RX mode and 
 ** Rc_Rx_Cec_DisableIrq() disables interrupt of CEC RX mode.  
 **   
 ** Rc_Rx_Cec_ReadData() reads the data received in CEC mode.
 **
 ** <b> CEC mode of Remote Control Transmission: </b>
 **  
 ** Rc_Tx_Cec_Init() configures the Remote Control Transmission to CEC mode and
 ** Rc_Tx_Cec_DeInit() reset the Remote Control Transmission. 
 **
 ** Rc_Tx_Cec_EnableTx() enables trasmission of CEC mode in Remote Control 
 ** trasmission. Rc_Rx_Cec_DisableTx() disables trasmission of CEC mode. 
 **
 ** Rc_Rx_Cec_GetIrqFlag() gets the interrupt flag of CEC mode. And 
 ** Rc_Rx_Cec_ClrIrqFlag() clears the interrupt flag of CEC mode. 
 **
 ** Interrupts can be configured in Rc_Tx_Cec_Init() first, after initialization,
 ** Rc_Rx_Cec_EnableIrq() enables interrupt of CEC TX mode and 
 ** Rc_Rx_Cec_DisableIrq() disables interrupt of CEC TX mode.    
 **
 ** Rc_Tx_GetAckCycleValue() gets the ACK cycle value in CEC TX mode.
 **
 ** Rc_Tx_Cec_WriteData() writes data specified with parameter to data buffer
 ** CEC TX mode.
 **
 ** Rc_Tx_Cec_SendDataPolling() is a high level API, which can write a data 
 ** frame with CEC format using polling mode.
 **  
 ******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/
#define stc_rcn_t   FM_HDMICEC_TypeDef 
#define RC0 (*((volatile stc_rcn_t *) FM_HDMICEC0_BASE))
#define RC1 (*((volatile stc_rcn_t *) FM_HDMICEC1_BASE))
  
#define RC_INSTANCE_COUNT                                \
        (uint8_t)(PDL_PERIPHERAL_ENABLE_RC0 == PDL_ON) + \
        (uint8_t)(PDL_PERIPHERAL_ENABLE_RC1 == PDL_ON)

/******************************************************************************/
/* Global type definitions                                                    */
/******************************************************************************/
/**
 ******************************************************************************
 ** \brief RC mode setting
 ******************************************************************************/
typedef enum en_rc_mode
{
    RcSircsMode         = 0u,  ///< SIRCS mode
    RcSettingProh       = 1u,  ///< Setting Prohibited
    RcNecMode           = 2u,  ///< NEC/Association for electric home appliance mode
    RcCecMode           = 3u,  ///< HDIM-CEC mode  
} en_rc_mode_t;

/**
 ******************************************************************************
 ** \brief RC CLK
 ******************************************************************************/
typedef enum en_rc_src_clk
{
    RcPeripheralClk      = 0u,  ///< Use peripheral clock as Remoter Control clock
    RcSubClk             = 1u,  ///< Use sub clock as Remoter Control clock
} en_rc_src_clk_t;
 
/**
 ******************************************************************************
 ** \brief RC threshold type
 ******************************************************************************/
typedef enum en_rc_threshold_type
{
    RcThresholdType0     = 0u,  ///< RC threshold type 0
    RcThresholdType1     = 1u,  ///< RC threshold type 1
} en_rc_threshold_type_t;
 
/**
 ******************************************************************************
 ** \brief RC overflow type
 ******************************************************************************/
typedef enum en_rc_overflow
{
    RcOverflow128Cycle   = 0u,  ///< An overflow will occur after the counter counted 128 clocks.
    RcOverflow256Cycle   = 1u,  ///< An overflow will occur after the counter counted 256 clocks.
} en_rc_overflow_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Receiver address structure
 ******************************************************************************/
typedef struct stc_rc_rx_addr
{
    uint8_t  u8Addr1;         ///< RC receiver address 1
    uint8_t  u8Addr2;         ///< RC receiver address 2
}stc_rc_rx_addr_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Receiver SIRCS mode interrupt enable structure
 ******************************************************************************/
typedef struct stc_rc_rx_sircs_irq_en
{
    boolean_t  bRcRxSircsStartIrq;                   ///< SIRCS mode start bit detection interrupt
    boolean_t  bRcRxSircsAckIrq;                     ///< SIRCS mode ACK detection interrupt
    boolean_t  bRcRxSircsCntOvfIrq;                  ///< SIRCS mode RX counter overflow interrupt
    
}stc_rc_rx_sircs_irq_en_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Receiver SIRCS mode interrupt selection enumeration
 ******************************************************************************/
typedef enum en_rc_rx_sircs_irq_sel
{
    RcRxSircsStartIrq  = 0u,    ///< SIRCS mode start bit detection interrupt
    RcRxSircsAckIrq    = 1u,    ///< SIRCS mode ACK detection interrupt
    RcRxSircsCntOvfIrq = 2u,    ///< SIRCS mode RX counter overflow interrupt     
    
}en_rc_rx_sircs_irq_sel_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Receiver SIRCS mode interrupt callback function
 ******************************************************************************/
typedef struct stc_rc_rx_sircs_irq_cb
{
    func_ptr_t  pfnRcRxSircsStartIrqCb;              ///< Callback function pointer of SIRCS start interrupt
    func_ptr_t  pfnRcRxSircsAckIrqCb;                ///< Callback function pointer of SIRCS ACK interrupt
    func_ptr_t  pfnRcRxSircsCntOvfIrqCb;             ///< Callback function pointer of SIRCS counter overflow interrupt   
}stc_rc_rx_sircs_irq_cb_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Receiver NEC mode interrupt enable structure
 ******************************************************************************/
typedef struct stc_rc_rx_nec_irq_en
{
    boolean_t  bRcRxNecStartIrq;                   ///< NEC mode start bit detection interrupt
    boolean_t  bRcRxNecAckIrq;                     ///< NEC mode ACK detection interrupt
    boolean_t  bRcRxNecCntOvfIrq;                  ///< NEC mode counter overflow interrupt  
    boolean_t  bRcRxNecRepeatCodeIrq;              ///< NEC mode repeat code interrupt  
    
} stc_rc_rx_nec_irq_en_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Receiver NEC mode interrupt selection enumeration
 ******************************************************************************/
typedef enum en_rc_rx_nec_irq_sel
{
    RcRxNecStartIrq  = 0u,                   ///< NEC mode start bit detection interrupt
    RcRxNecAckIrq    = 1u,                   ///< NEC mode ACK detection interrupt
    RcRxNecCntOvfIrq = 2u,                   ///< NEC mode counter overflow interrupt  
    RcRxNecRepeatCodeIrq = 3u,               ///< NEC mode repeat code interrupt  
    
} en_rc_rx_nec_irq_sel_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Receiver NEC mode interrupt callback functions
 ******************************************************************************/
typedef struct stc_rc_rx_nec_irq_cb
{
    func_ptr_t  pfnRcRxNecStartIrqCb;              ///< Callback function pointer of Nec start interrupt
    func_ptr_t  pfnRcRxNecAckIrqCb;                ///< Callback function pointer of Nec ACK interrupt
    func_ptr_t  pfnRcRxNecCntOvfIrqCb;             ///< Callback function pointer of Nec counter overflow interrupt   
    func_ptr_t  pfnRcRxNecRepeatCodeIrqCb;         ///< Callback function pointer of Nec repeat code interrupt   
    
}stc_rc_rx_nec_irq_cb_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Receiver CEC mode interrupt enable structure
 ******************************************************************************/
typedef struct stc_rc_rx_cec_irq_en
{
    boolean_t  bRcRxCecStartIrq;                   ///< CEC mode start bit detection interrupt
    boolean_t  bRcRxCecAckIrq;                     ///< CEC mode ACK detection interrupt
    boolean_t  bRcRxCecCntOvfIrq;                  ///< CEC mode counter overflow interrupt
    boolean_t  bRcRxCecMinDataIrq;                 ///< CEC mode Minimum data bit width violation detection 
    boolean_t  bRcRxCecMaxDataIrq;                 ///< CEC mode Maximum data bit width violation detection 
    
}stc_rc_rx_cec_irq_en_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Receiver CEC mode interrupt selection enumeration
 ******************************************************************************/
typedef enum en_rc_rx_cec_irq_sel
{
    RcRxCecStartIrq        = 0u,                  ///< CEC mode start bit detection interrupt
    RcRxCecAckIrq          = 1u,                  ///< CEC mode ACK detection interrupt
    RcRxCecCntOvfIrq       = 2u,                  ///< CEC mode counter overflow interrupt
    RcRxCecMinDataIrq      = 3u,                  ///< CEC mode Minimum data bit width violation detection 
    RcRxCecMaxDataIrq      = 4u,                  ///< CEC mode Maximum data bit width violation detection 
    
}en_rc_rx_cec_irq_sel_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Receiver CEC mode interrupt callback functions
 ******************************************************************************/
typedef struct stc_rc_rx_cec_irq_cb
{
    func_ptr_t  pfnRcRxCecStartIrqCb;              ///< Callback function pointer of CEC start interrupt
    func_ptr_t  pfnRcRxCecAckIrqCb;                ///< Callback function pointer of CEC ACK interrupt
    func_ptr_t  pfnRcRxCecCntOvfIrqCb;             ///< Callback function pointer of CEC count over interrupt   
    func_ptr_t  pfnRcRxCecMinDataIrqCb;            ///< Callback function pointer of CEC Minimum data interrupt
    func_ptr_t  pfnRcRxCecMaxDataIrqCb;            ///< Callback function pointer of CEC Maximum data interrupt   

}stc_rc_rx_cec_irq_cb_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Transmission data type
 ******************************************************************************/
typedef enum en_rc_txdata_type
{
    RcTxCecHeader       = 0u,  ///< Header block transmission
    RcTxCecData         = 1u,  ///< Data block
    RcTxCecPolling      = 2u,  ///< Header block transmission
    RcTxCecFinal        = 3u,  ///< Final data block
} en_rc_txdata_type_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Transmission interrupt selection
 ******************************************************************************/
typedef enum en_rc_tx_cec_irq_sel
{
    RcTxCecBusErrorIrq       = 0u,  ///< Remoter Control CEC TX bus error interrupt 
    RcTxCecTransStausIrq     = 1u,  ///< Remoter Control CEC TX transfer status interrupt 
} en_rc_tx_cec_irq_sel_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Transmission interrupt enable structure
 ******************************************************************************/
typedef struct stc_rc_tx_cec_irq_en
{
    boolean_t bRcTxCecBusErrorIrq;  ///< Remoter Control CEC TX bus error interrupt
    boolean_t bRcTxCecStatusIrq;    ///< Remoter Control CEC TX status interrupt
    
} stc_rc_tx_cec_irq_en_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Transmission interrupt callback function
 ******************************************************************************/
typedef struct stc_rc_tx_irq_cb
{
    func_ptr_t  pfnRcTxIrqBusErrorCb;               ///< Callback function pointer of Bus error dection
    func_ptr_t  pfnRcTxIrqTxStatusCb;               ///< Callback function pointer of Transmisstion status 
}stc_rc_tx_cec_irq_cb_t;
/**
 ******************************************************************************
 ** \brief Intern data structure
 ******************************************************************************/
typedef struct stc_rc_intern_data
{
    func_ptr_t  pfnRcRxStartIrqCb;              ///< Callback function pointer of RC Start interrupt
    func_ptr_t  pfnRcRxCntOvfIrqCb;             ///< Callback function pointer of RC counter over interrupt   
    func_ptr_t  pfnRcRxEomCb;                   ///< Callback function pointer of End of transmit interrupt
    func_ptr_t  pfnRcRxAckIrqCb;                ///< Callback function pointer of ICU1 interrupt  
    func_ptr_t  pfnRcRxRepeatCodeIrqCb;         ///< Callback function pointer of repect code interrupt
    func_ptr_t  pfnRcRxMinDataIrqCb;            ///< Callback function pointer of minimum data interrupt
    func_ptr_t  pfnRcRxMaxDataIrqCb;            ///< Callback function pointer of maximum data interrupt 
    func_ptr_t  pfnRcTxIrqBusErrorCb;           ///< Callback function pointer of bus error interrupt
    func_ptr_t  pfnRcTxIrqStatusCb;             ///< Callback function pointer of status interrupt      
}stc_rc_intern_data_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Receiver SIRCS mode configuration
 ******************************************************************************/
typedef struct stc_rc_rx_sircs_config
{
    en_rc_src_clk_t         enSrcClk;                   ///< Source clock
    uint16_t                u16DivVal;                  ///< Clock division value
    en_rc_threshold_type_t  enThresholdType;            ///< Theshold type selection
    boolean_t               bAddrCmpEn;                 ///< TRUE: compare with address set in the address register, FALSE: don't compare with address set in the address register
    en_rc_overflow_t        enOverflowCycle;            ///< Overflow cycle count selection
    uint8_t                 u8StartBitWidth;            ///< Start bit width   
    uint8_t                 u8MinPulseWidth;            ///< Minimum pulse width setting
    uint8_t                 u8ThresholdWidth;           ///< Theshold width setting
    stc_rc_rx_addr_t        stcAddr;                    ///< Address setting which is used to compare with device address
#if (PDL_INTERRUPT_ENABLE_RC0 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_RC1 == PDL_ON)
    stc_rc_rx_sircs_irq_en_t*  pstcIrqEn;               ///< Pointer to interrupt request enable setting structure of RC with SIRCS mode  
    stc_rc_rx_sircs_irq_cb_t*  pstcIrqCb;               ///< Pointer to interrupt request callback functions structure of RC with SIRCS mode  
    boolean_t                  bTouchNvic;              ///< TRUE: enable NVIC, FALSE: don't enable NVIC
#endif
}stc_rc_rx_sircs_config_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Receiver NEC mode configuration
 ******************************************************************************/
typedef struct stc_rc_rx_nec_config
{
    en_rc_src_clk_t         enSrcClk;                ///< Source clock
    uint16_t                u16DivVal;               ///< Clock division value
    en_rc_threshold_type_t  enThresholdType;         ///< Theshold type selection
    boolean_t               bAddrCmpEn;              ///< TRUE: compare with address set in the address register, FALSE: don't compare with address set in the address register
    en_rc_overflow_t        enOverflowCycle;         ///< Overflow cycle count selection
    uint8_t                 u8StartBitWidth;         ///< Start bit width     
    uint8_t                 u8MinPulseWidth;         ///< Minimum pulse width setting
    uint8_t                 u8ThresholdWidth;        ///< Theshold width setting
    uint8_t                 u8RepeatWidth;           ///< Repeat code width setting
    stc_rc_rx_addr_t        stcAddr;                 ///< Address setting which is used to compare with device address
#if (PDL_INTERRUPT_ENABLE_RC0 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_RC1 == PDL_ON)
    stc_rc_rx_nec_irq_en_t*  pstcIrqEn;            ///< Pointer to interrupt request enable setting structure of RC with NEC mode  
    stc_rc_rx_nec_irq_cb_t*  pstcIrqCb;            ///< Pointer to interrupt request callback functions structure of RC with NEC mode 
    boolean_t                bTouchNvic;           ///< TRUE: enable NVIC, FALSE: don't enable NVIC 
#endif
}stc_rc_rx_nec_config_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Receiver CEC mode configuration
 ******************************************************************************/
typedef struct stc_rc_rx_cec_config
{
    en_rc_src_clk_t         enSrcClk;               ///< Source clock
    uint16_t                u16DivVal;              ///< Clock division value
    en_rc_threshold_type_t  enThresholdType;        ///< Theshold type selection
    en_rc_overflow_t        enOverflowCycle;        ///< Overflow cycle count selection
    boolean_t               bAddrCmpEn;             ///< TRUE: compare with address set in the address register, FALSE: don't compare with address set in the address register
    boolean_t               bMinDataBitDetect;      ///< TRUE : Enable minimum data bit detection, FALSE: Disable minimum data bit detection
    boolean_t               bMaxDataBitDetect;      ///< TRUE : Enable maximum data bit detection, FALSE: Disable maximum data bit detection
    boolean_t               bBusErrorPulseOutput;   ///< TRUE : Enable Bus error pulse detection, FALSE: Disable Bus error detection
    uint8_t                 u8StartBitWidth;        ///< Start bit width        
    uint8_t                 u8MinPulseWidth;        ///< Minimum pulse width setting
    uint8_t                 u8ThresholdWidth;       ///< Theshold width setting
    uint8_t                 u8MinDataWidth;         ///< Minimum data width setting
    uint8_t                 u8MaxDataWidth;         ///< Maximum data width setting
    stc_rc_rx_addr_t        stcAddr;                ///< Address setting which is used to compare with device address
#if (PDL_INTERRUPT_ENABLE_RC0 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_RC1 == PDL_ON)
    stc_rc_rx_cec_irq_en_t*  pstcIrqEn;            ///< Pointer to interrupt request enable setting structure of RC with CEC mode  
    stc_rc_rx_cec_irq_cb_t*  pstcIrqCb;            ///< Pointer to interrupt request callback functions structure of RC with CEC mode  
    boolean_t                bTouchNvic;           ///< TRUE: enable NVIC, FALSE: don't enable NVIC
#endif
}stc_rc_rx_cec_config_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Receiver SIRCS data format
 ******************************************************************************/
typedef struct rc_rx_sircs_data
{
    uint8_t u8Command;          ///< SIRCS command
    uint8_t u8DeviceAddress;    ///< SIRCS Device address (5-bit)
    uint8_t u8Data0;            ///< SIRCS data 0 (3-bit)
    uint8_t u8Data1;            ///< SIRCS data 1 (5-bit)
    
}rc_rx_sircs_data_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Receiver NEC data format
 ******************************************************************************/
typedef struct rc_rx_nec_data
{
    uint16_t u16CustomCode;       ///< NEC custom code
    uint8_t u8Data0;              ///< NEC data code 0
    uint8_t u8Data1;              ///< NEC data code 1
    
}rc_rx_nec_data_t;

/**
 ******************************************************************************
 ** \brief Remoter Control Receiver CEC mode configuration
 ******************************************************************************/
typedef struct stc_rc_tx_cec_config
{
    en_rc_src_clk_t         enSrcClk;                ///< Source clock
    uint16_t                u16DivVal;               ///< Clock division value
    uint8_t u8FreeCycle;                        ///< Signal free time setting bits (0~15)
#if (PDL_INTERRUPT_ENABLE_RC0 == PDL_ON) || \
    (PDL_INTERRUPT_ENABLE_RC1 == PDL_ON)    
    stc_rc_tx_cec_irq_en_t*     pstcIrqEn;            ///< Pointer to interrupt request enable setting structure of RC with Tx mode  
    stc_rc_tx_cec_irq_cb_t*     pstcIrqCb;            ///< Pointer to interrupt request callback functions structure of RC with Tx mode 
    boolean_t                   bTouchNvic;           ///< TRUE: enable NVIC, FALSE: don't enable NVIC
#endif
}stc_rc_tx_cec_config_t;

/// Enumeration to define an index for each enabled RC instance
typedef enum en_rc_instance_index
{
  #if (PDL_PERIPHERAL_ENABLE_RC0 == PDL_ON)
    RcInstanceIndexRc0,
  #endif
  #if (PDL_PERIPHERAL_ENABLE_RC1 == PDL_ON)
    RcInstanceIndexRc1,
  #endif
    RcInstanceIndexMax
} en_rc_instance_index_t;

/// RC instance data type
typedef struct stc_rc_instance_data
{
  volatile stc_rcn_t*  pstcInstance;  ///< pointer to registers of an instance
  stc_rc_intern_data_t stcInternData; ///< module internal data of instance
} stc_rc_instance_data_t;

/******************************************************************************/
/* Global variable definitions ('extern')                                     */
/******************************************************************************/ 
 extern stc_rc_instance_data_t m_astcRcInstanceDataLut[RC_INSTANCE_COUNT];
/******************************************************************************/
/* Global function prototypes (definition in C source)                        */
/******************************************************************************/

/* Remote Control Reception SIRCS mode */
en_result_t Rc_Rx_Sircs_Init(volatile stc_rcn_t *pstcRc,
                             stc_rc_rx_sircs_config_t *pstcRcSircsConfig);
en_result_t Rc_Rx_Sircs_DeInit(volatile stc_rcn_t *pstcRc, boolean_t bTouchNvic);
en_result_t Rc_Rx_Sircs_EnableRx(volatile stc_rcn_t *pstcRc);
en_result_t Rc_Rx_Sircs_DisableRx(volatile stc_rcn_t *pstcRc);

#if (PDL_INTERRUPT_ENABLE_RC0 == PDL_ON) ||\
    (PDL_INTERRUPT_ENABLE_RC1 == PDL_ON)
en_result_t Rc_Rx_Sircs_EnableIrq(volatile stc_rcn_t *pstcRc, 
                                  en_rc_rx_sircs_irq_sel_t enIrqSel);
en_result_t Rc_Rx_Sircs_DisableIrq(volatile stc_rcn_t *pstcRc, 
                                   en_rc_rx_sircs_irq_sel_t enIrqSel);
#endif
boolean_t Rc_Rx_Sircs_GetIrqFlag(volatile stc_rcn_t *pstcRc, 
                                 en_rc_rx_sircs_irq_sel_t enIrqSel);
en_result_t Rc_Rx_Sircs_ClrIrqFlag(volatile stc_rcn_t *pstcRc, 
                                   en_rc_rx_sircs_irq_sel_t enIrqSel);
en_result_t Rc_Rx_Sircs_ReadData(volatile stc_rcn_t *pstcRc, 
                                 rc_rx_sircs_data_t* pstcData);

/* Remote Control Reception NEC mode */
en_result_t Rc_Rx_Nec_Init(volatile stc_rcn_t *pstcRc,
                           stc_rc_rx_nec_config_t *pstcRcNecConfig);
en_result_t Rc_Rx_Nec_DeInit(volatile stc_rcn_t *pstcRc, boolean_t bTouchNvic);
en_result_t Rc_Rx_Nec_EnableRx(volatile stc_rcn_t *pstcRc);
en_result_t Rc_Rx_Nec_DisableRx(volatile stc_rcn_t *pstcRc);
#if (PDL_INTERRUPT_ENABLE_RC0 == PDL_ON) ||\
    (PDL_INTERRUPT_ENABLE_RC1 == PDL_ON)
en_result_t Rc_Rx_Nec_EnableIrq(volatile stc_rcn_t *pstcRc, 
                                en_rc_rx_nec_irq_sel_t enIrqSel);
en_result_t Rc_Rx_Nec_DisableIrq(volatile stc_rcn_t *pstcRc, 
                                 en_rc_rx_nec_irq_sel_t enIrqSel);
#endif
boolean_t Rc_Rx_Nec_GetIrqFlag(volatile stc_rcn_t *pstcRc, 
                               en_rc_rx_nec_irq_sel_t enIrqSel);
en_result_t Rc_Rx_Nec_ClrIrqFlag(volatile stc_rcn_t *pstcRc, 
                                 en_rc_rx_nec_irq_sel_t enIrqSel);
en_result_t Rc_Rx_Nec_ReadData(volatile stc_rcn_t *pstcRc, 
                               rc_rx_nec_data_t* pstcData);

/* Remote Control Reception CEC mode */
en_result_t Rc_Rx_Cec_Init(volatile stc_rcn_t *pstcRc,
                           stc_rc_rx_cec_config_t *pstcRcCecConfig);
en_result_t Rc_Rx_Cec_DeInit(volatile stc_rcn_t *pstcRc, boolean_t bTouchNvic);
en_result_t Rc_Rx_Cec_EnableRx(volatile stc_rcn_t *pstcRc);
en_result_t Rc_Rx_Cec_DisableRx(volatile stc_rcn_t *pstcRc);

#if (PDL_INTERRUPT_ENABLE_RC0 == PDL_ON) ||\
    (PDL_INTERRUPT_ENABLE_RC1 == PDL_ON)
en_result_t Rc_Rx_Cec_EnableIrq(volatile stc_rcn_t *pstcRc, 
                                en_rc_rx_cec_irq_sel_t enIrqSel);
en_result_t Rc_Rx_Cec_DisableIrq(volatile stc_rcn_t *pstcRc, 
                                 en_rc_rx_cec_irq_sel_t enIrqSel);
#endif
boolean_t Rc_Rx_Cec_GetIrqFlag(volatile stc_rcn_t *pstcRc, 
                               en_rc_rx_cec_irq_sel_t enIrqSel);
en_result_t Rc_Rx_Cec_ClrIrqFlag(volatile stc_rcn_t *pstcRc, 
                                 en_rc_rx_cec_irq_sel_t enIrqSel);
uint8_t Rc_Rx_Cec_ReadData(volatile stc_rcn_t *pstcRc);
boolean_t Rc_Rx_Cec_GetEomState(volatile stc_rcn_t *pstcRc);
en_result_t Rc_Rx_Cec_ClrEomState(volatile stc_rcn_t *pstcRc);


/* Remote Control Transmission CEC mode */
en_result_t Rc_Tx_Cec_Init(volatile stc_rcn_t *pstcRc,
                           stc_rc_tx_cec_config_t *pstcRcCecConfig);
en_result_t Rc_Tx_Cec_DeInit(volatile stc_rcn_t *pstcRc, boolean_t bTouchNvic);
en_result_t Rc_Tx_Cec_EnableTx(volatile stc_rcn_t *pstcRc);
en_result_t Rc_Tx_Cec_DisableTx(volatile stc_rcn_t *pstcRc);

#if (PDL_INTERRUPT_ENABLE_RC0 == PDL_ON) ||\
    (PDL_INTERRUPT_ENABLE_RC1 == PDL_ON)
en_result_t Rc_Tx_Cec_EnableIrq(volatile stc_rcn_t *pstcRc, 
                                en_rc_tx_cec_irq_sel_t enIrqSel);
en_result_t Rc_Tx_Cec_DisableIrq(volatile stc_rcn_t *pstcRc, 
                                 en_rc_tx_cec_irq_sel_t enIrqSel);
#endif
boolean_t Rc_Tx_Cec_GetIrqFlag(volatile stc_rcn_t *pstcRc, 
                               en_rc_tx_cec_irq_sel_t enIrqSel);
en_result_t Rc_Tx_Cec_ClrIrqFlag(volatile stc_rcn_t *pstcRc, 
                                 en_rc_tx_cec_irq_sel_t enIrqSel);
boolean_t Rc_Tx_GetAckCycleValue(volatile stc_rcn_t *pstcRc);
en_result_t Rc_Tx_Cec_WriteData(volatile stc_rcn_t *pstcRc,
                                uint8_t u8Data,
                                en_rc_txdata_type_t enType);
en_result_t Rc_Tx_Cec_SendDataPolling( volatile stc_rcn_t *pstcRc,
                                       uint8_t u8Header,
                                       uint8_t* pu8Data,
                                       uint32_t u32Size);
#if (PDL_INTERRUPT_ENABLE_RC0 == PDL_ON) ||\
    (PDL_INTERRUPT_ENABLE_RC1 == PDL_ON)
/* RC IRQ */
void RcIrqHandler(volatile stc_rcn_t *pstcRc, 
                  stc_rc_intern_data_t* pstcRcInternData);
#endif     

//@} // RcGroup

#ifdef __cplusplus
}
#endif

#endif // #if (defined(PDL_PERIPHERAL_RC_ACTIVE))

#endif /* __RC_H__ */

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
