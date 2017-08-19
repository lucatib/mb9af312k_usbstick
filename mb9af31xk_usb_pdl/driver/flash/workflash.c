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
/** \file workflash.c
 **
 ** A detailed description is available at 
 ** @link WorkFlashGroup Flash Module description @endlink
 **
 ** History:
 **   - 2015-01-20 1.0  KXi First version for FM Universal PDL.
 **
 ******************************************************************************/
/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "workflash.h"

#if defined(PDL_PERIPHERAL_WORK_FLASH_ACTIVE) 

/**
 ******************************************************************************
 ** \addtogroup WorkFlashGroup
 ******************************************************************************/
//@{   
   
/*!
 ******************************************************************************
 ** \brief Read a half word data from Flash
 ** \param addr Pointer to read data address
 ******************************************************************************
 */
#define Flash_Read(addr)        *(volatile uint16_t*)((uint32_t)(addr))

/*!
 ******************************************************************************
 ** \brief Wirte a half word data into Flash
 ** \param addr Pointer to read data address
 ** \param data Write data
 ******************************************************************************
 */
#define Flash_Write(addr, data) *(volatile uint16_t*)((uint32_t)(addr)) = ( uint16_t)(data)

/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/
static uint8_t WFlash_CheckToggle( uint16_t* pAddr );
static void WFlash_ReadResetCmd(uint16_t* pu16ResetSecAddr);

/*!
 ******************************************************************************
 ** \brief Issue read/reset command
 **
 ** \param pu16ResetSecAddr address of reset sector  
 **
 ** \return None
 **
 ******************************************************************************
 */
static void WFlash_ReadResetCmd(uint16_t* pu16ResetSecAddr)
{
    uint8_t  u8Dummy;

    /*  issue read/reset command    */
    Flash_Write(0x0000u, 0xF0u) ;
    u8Dummy = Flash_Read(pu16ResetSecAddr) ;
    if(u8Dummy)  /* avoid warning */  
        ;
    return ;
}

/*!
 ******************************************************************************
 ** \brief Flash chip erase       
 **
 ** \return Operation status
 ** \retval Ok                     Chip erase successfully done.
 ** \retval ErrorInvalidParameter  If one of following conditions are met:
 **                                - automatic algorithm of flash memory execution abnormally
 **
 ******************************************************************************
 */
en_result_t WFlash_ChipErase(void)
{
    en_result_t emRetValue = Ok;
#if (PDL_MCU_CORE != PDL_FM0P_CORE)    
    uint8_t  u8Dummy;
    FM_WORKFLASH_IF->WFASZR = 0x00u;
    u8Dummy = FM_WORKFLASH_IF->WFASZR;
    if(u8Dummy) ;
#endif        
    Flash_Write((WFLASH_CODE1 | WFLASH_BASE_ADDR), 0x00AAu);
    Flash_Write((WFLASH_CODE2 | WFLASH_BASE_ADDR), 0x0055u);
    Flash_Write((WFLASH_CODE1 | WFLASH_BASE_ADDR), 0x0080u);
    Flash_Write((WFLASH_CODE1 | WFLASH_BASE_ADDR), 0x00AAu);
    Flash_Write((WFLASH_CODE2| WFLASH_BASE_ADDR), 0x0055u);
    Flash_Write((WFLASH_CODE1 | WFLASH_BASE_ADDR), 0x0010u);

     /*  if execution result of the automatic algorithm of flash memory is abnormally completed  */
    if( WFLASH_CHK_TOGG_ABNORMAL == WFlash_CheckToggle((uint16_t*)WFLASH_BASE_ADDR) )
    {
        /*  sending the read/reset command to the reset sector  */
        WFlash_ReadResetCmd((uint16_t*)WFLASH_BASE_ADDR) ;

        /*  return flash operation abnormally   */
        emRetValue  = ErrorInvalidParameter ;
    }
    
    /*  CPU ROM mode setting    */
#if (PDL_MCU_CORE != PDL_FM0P_CORE) 
        FM_WORKFLASH_IF->WFASZR = 0x01u; 
        u8Dummy = FM_WORKFLASH_IF->WFASZR;
#endif

    return emRetValue;
}

/*!
 ******************************************************************************
 ** \brief Flash sector erase       
 **
 ** \param pu16SecAddr address of flash sector  
 **
 ** \return Operation status
 ** \retval Ok                     Chip erase successfully done.
 ** \retval ErrorInvalidParameter  If one of following conditions are met:
 **                                - automatic algorithm of flash memory execution abnormally
 **
 ******************************************************************************
 */ 
en_result_t WFlash_SectorErase(uint16_t* pu16SecAddr)
{
    en_result_t emRetValue = Ok;
#if (PDL_MCU_CORE != PDL_FM0P_CORE)   
    uint8_t  u8Dummy;
#endif
#if (PDL_MCU_CORE != PDL_FM0P_CORE)    
    FM_WORKFLASH_IF->WFASZR = 0x00u;
    u8Dummy = FM_WORKFLASH_IF->WFASZR;
    if(u8Dummy) ;
#endif
       
        Flash_Write((WFLASH_CODE1 | WFLASH_BASE_ADDR), 0x00AAu);
        Flash_Write((WFLASH_CODE2 | WFLASH_BASE_ADDR), 0x0055u);
        Flash_Write((WFLASH_CODE1 | WFLASH_BASE_ADDR), 0x0080u);
        Flash_Write((WFLASH_CODE1 | WFLASH_BASE_ADDR), 0x00AAu);
        Flash_Write((WFLASH_CODE2 | WFLASH_BASE_ADDR), 0x0055u);
        Flash_Write(pu16SecAddr, 0x0030u);

         /*  if execution result of the automatic algorithm of flash memory is abnormally completed  */
        if( WFLASH_CHK_TOGG_ABNORMAL == WFlash_CheckToggle(pu16SecAddr) )
        {
            /*  sending the read/reset command to the reset sector  */
            WFlash_ReadResetCmd(pu16SecAddr) ;

            /*  return flash operation abnormally   */
            emRetValue  = ErrorInvalidParameter ;
        }

        /*  CPU ROM mode setting    */
#if (PDL_MCU_CORE != PDL_FM0P_CORE) 
        FM_WORKFLASH_IF->WFASZR = 0x01u; 
        u8Dummy = FM_WORKFLASH_IF->WFASZR;
#endif
    return emRetValue;
}

/*!
 ******************************************************************************
 ** \brief Flash word write with ECC  
 **
 ** \param pu32WriteAddr address of flash data
 ** \param pu32WriteData pointer to write data
 ** \param u32Size data size, 1 indicates 1 16-bit data, always set it to even
 **
 ** \return Operation status
 ** \retval Ok                     Chip erase successfully done.
 ** \retval ErrorInvalidParameter  If one of following conditions are met:
 **                                - automatic algorithm of flash memory execution abnormally
 **
 ******************************************************************************
 */ 
en_result_t WFlash_WriteData32Bit(uint32_t*  pu32WriteAddr, 
                                  uint32_t* pu32WriteData, 
                                  uint32_t u32Size)
{
    uint16_t *pAddr, *pData;
    en_result_t emRetValue = Ok;
    uint32_t   u32Cnt;
#if (PDL_MCU_CORE != PDL_FM0P_CORE)   
    uint8_t  u8Dummy;
#endif
    pAddr = (uint16_t*)pu32WriteAddr;
    pData = (uint16_t*)pu32WriteData;    
    /*  CPU programming mode setting    */
#if (PDL_MCU_CORE != PDL_FM0P_CORE)    
    FM_WORKFLASH_IF->WFASZR = 0x00u;
    u8Dummy = FM_WORKFLASH_IF->WFASZR;
    if(u8Dummy) ;
#endif
        
        for(u32Cnt=u32Size*sizeof(uint16_t);u32Cnt;u32Cnt--)
        {
            /*  issue write command   */
            Flash_Write((WFLASH_CODE1 | WFLASH_BASE_ADDR), 0x00AAu) ;
            Flash_Write((WFLASH_CODE2 | WFLASH_BASE_ADDR), 0x0055u) ;
            Flash_Write((WFLASH_CODE1 | WFLASH_BASE_ADDR), 0x00A0u) ;
            Flash_Write((uint32_t)pAddr, (uint16_t)*pData);
            
            /*  execution result of the automatic algorithm of flash memory is abnormally complete or verify error  */
            if(( WFLASH_CHK_TOGG_ABNORMAL == WFlash_CheckToggle(pAddr) ) ||
              ( Flash_Read((uint32_t)pAddr) != (uint16_t)*pData))
            {
                /*  issue read/reset command to reset sector    */
                WFlash_ReadResetCmd(pAddr) ;
    
                /*  return flash operation abnormally   */
                emRetValue  = ErrorInvalidParameter ;
            }      
            /* Prepare next h-word write */
            pAddr++;
            pData++; 
        }
        
        /*  CPU ROM mode setting    */
#if (PDL_MCU_CORE != PDL_FM0P_CORE) 
        FM_WORKFLASH_IF->WFASZR = 0x01u; 
        u8Dummy = FM_WORKFLASH_IF->WFASZR;
#endif
    return emRetValue ;
}
/*!
 ******************************************************************************
 ** \brief Flash half-word write with ECC  
 **
 ** \param pu16WriteAddr address of flash data
 ** \param pu16WriteData pointer to write data
 ** \param u32Size data size, 1 indicates 1 16-bit data, always set it to even
 **
 ** \return Operation status
 ** \retval Ok                     Chip erase successfully done.
 ** \retval ErrorInvalidParameter  If one of following conditions are met:
 **                                - automatic algorithm of flash memory execution abnormally
 **
 ******************************************************************************
 */ 
en_result_t WFlash_WriteData16Bit(uint16_t*  pu16WriteAddr, 
                                  uint16_t* pu16WriteData, 
                                  uint32_t u32Size)
{
    en_result_t emRetValue = Ok;
    uint32_t   u32Cnt;
#if (PDL_MCU_CORE != PDL_FM0P_CORE)   
    uint8_t  u8Dummy;
#endif

        /*  CPU programming mode setting    */
#if (PDL_MCU_CORE != PDL_FM0P_CORE)    
    FM_WORKFLASH_IF->WFASZR = 0x00u;
    u8Dummy = FM_WORKFLASH_IF->WFASZR;
    if(u8Dummy) ;
#endif
        
        for(u32Cnt=u32Size;u32Cnt;u32Cnt--)
        {
            /*  issue write command   */
            Flash_Write((WFLASH_CODE1 | WFLASH_BASE_ADDR), 0x00AA) ;
            Flash_Write((WFLASH_CODE2 | WFLASH_BASE_ADDR), 0x0055) ;
            Flash_Write((WFLASH_CODE1 | WFLASH_BASE_ADDR), 0x00A0) ;
            Flash_Write(pu16WriteAddr, (uint16_t)*pu16WriteData);
            
            /*  execution result of the automatic algorithm of flash memory is abnormally complete or verify error  */
            if(( WFLASH_CHK_TOGG_ABNORMAL == WFlash_CheckToggle(pu16WriteAddr) ) ||
              ( Flash_Read(pu16WriteAddr) != *pu16WriteData))
            {
                /*  issue read/reset command to reset sector    */
                WFlash_ReadResetCmd(pu16WriteAddr) ;
    
                /*  return flash operation abnormally   */
                emRetValue  = ErrorInvalidParameter ;
            }      
            /* Prepare next h-word write */
            pu16WriteAddr++;
            pu16WriteData++; 
        }
        
        /*  CPU ROM mode setting    */
#if (PDL_MCU_CORE != PDL_FM0P_CORE) 
        FM_WORKFLASH_IF->WFASZR = 0x01u; 
        u8Dummy = FM_WORKFLASH_IF->WFASZR;
#endif
    return emRetValue ;
}
/*!
 ******************************************************************************
 ** \brief automatic algorithm of flash memory execution 
 **
 ** \param pu16Addr address of flash data
 **
 ** \return Operation status
 ** \retval MFLASH_RET_OK
 ** \retval MFLASH_RET_ABNORMAL
 ** \retval MFLASH_RET_INVALID_PARA
 **
 ******************************************************************************
 */
static uint8_t WFlash_CheckToggle( uint16_t* pu16Addr )
{
    uint16_t   u16SequenceFlag1, u16SequenceFlag2 ;  /*  hardware sequence flag */
    uint8_t   u8RetValue  = WFLASH_CHK_TOGG_NORMAL ;

    /* set hardware sequence flag */
    u16SequenceFlag1 = Flash_Read(pu16Addr) ;
    u16SequenceFlag2 = Flash_Read(pu16Addr) ;
    /*  if automatic algorithm is executing */
    while(WFLASH_CHK_TOGG_MASK == (( u16SequenceFlag1 ^ u16SequenceFlag2) & WFLASH_CHK_TOGG_MASK))
    {
        /*  if exceeds the timing limit */
        if(WFLASH_CHK_TLOV_MASK == ( u16SequenceFlag1 & WFLASH_CHK_TLOV_MASK ) )
        {
            /* set hardware sequence flag */
            u16SequenceFlag1 = Flash_Read(pu16Addr) ;
            u16SequenceFlag2 = Flash_Read(pu16Addr) ;

            /*  if automatic algorithm is executing */
            if(WFLASH_CHK_TOGG_MASK == (( u16SequenceFlag1 ^ u16SequenceFlag2) & WFLASH_CHK_TOGG_MASK))
            {
                /*  abnormally complete */
                u8RetValue  = WFLASH_CHK_TOGG_ABNORMAL ;

                break;
            }
        }

        /* set hardware sequence flag */
        u16SequenceFlag1 = Flash_Read(pu16Addr) ;
        u16SequenceFlag2 = Flash_Read(pu16Addr) ;
    }

    return u8RetValue ;
}

//@}

#endif

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/