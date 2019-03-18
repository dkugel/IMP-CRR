/*******************************************************************************
* File Name: SRegClk.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_SRegClk_H)
#define CY_CLOCK_SRegClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void SRegClk_Start(void) ;
void SRegClk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void SRegClk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void SRegClk_StandbyPower(uint8 state) ;
void SRegClk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 SRegClk_GetDividerRegister(void) ;
void SRegClk_SetModeRegister(uint8 modeBitMask) ;
void SRegClk_ClearModeRegister(uint8 modeBitMask) ;
uint8 SRegClk_GetModeRegister(void) ;
void SRegClk_SetSourceRegister(uint8 clkSource) ;
uint8 SRegClk_GetSourceRegister(void) ;
#if defined(SRegClk__CFG3)
void SRegClk_SetPhaseRegister(uint8 clkPhase) ;
uint8 SRegClk_GetPhaseRegister(void) ;
#endif /* defined(SRegClk__CFG3) */

#define SRegClk_Enable()                       SRegClk_Start()
#define SRegClk_Disable()                      SRegClk_Stop()
#define SRegClk_SetDivider(clkDivider)         SRegClk_SetDividerRegister(clkDivider, 1u)
#define SRegClk_SetDividerValue(clkDivider)    SRegClk_SetDividerRegister((clkDivider) - 1u, 1u)
#define SRegClk_SetMode(clkMode)               SRegClk_SetModeRegister(clkMode)
#define SRegClk_SetSource(clkSource)           SRegClk_SetSourceRegister(clkSource)
#if defined(SRegClk__CFG3)
#define SRegClk_SetPhase(clkPhase)             SRegClk_SetPhaseRegister(clkPhase)
#define SRegClk_SetPhaseValue(clkPhase)        SRegClk_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(SRegClk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define SRegClk_CLKEN              (* (reg8 *) SRegClk__PM_ACT_CFG)
#define SRegClk_CLKEN_PTR          ((reg8 *) SRegClk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define SRegClk_CLKSTBY            (* (reg8 *) SRegClk__PM_STBY_CFG)
#define SRegClk_CLKSTBY_PTR        ((reg8 *) SRegClk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define SRegClk_DIV_LSB            (* (reg8 *) SRegClk__CFG0)
#define SRegClk_DIV_LSB_PTR        ((reg8 *) SRegClk__CFG0)
#define SRegClk_DIV_PTR            ((reg16 *) SRegClk__CFG0)

/* Clock MSB divider configuration register. */
#define SRegClk_DIV_MSB            (* (reg8 *) SRegClk__CFG1)
#define SRegClk_DIV_MSB_PTR        ((reg8 *) SRegClk__CFG1)

/* Mode and source configuration register */
#define SRegClk_MOD_SRC            (* (reg8 *) SRegClk__CFG2)
#define SRegClk_MOD_SRC_PTR        ((reg8 *) SRegClk__CFG2)

#if defined(SRegClk__CFG3)
/* Analog clock phase configuration register */
#define SRegClk_PHASE              (* (reg8 *) SRegClk__CFG3)
#define SRegClk_PHASE_PTR          ((reg8 *) SRegClk__CFG3)
#endif /* defined(SRegClk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define SRegClk_CLKEN_MASK         SRegClk__PM_ACT_MSK
#define SRegClk_CLKSTBY_MASK       SRegClk__PM_STBY_MSK

/* CFG2 field masks */
#define SRegClk_SRC_SEL_MSK        SRegClk__CFG2_SRC_SEL_MASK
#define SRegClk_MODE_MASK          (~(SRegClk_SRC_SEL_MSK))

#if defined(SRegClk__CFG3)
/* CFG3 phase mask */
#define SRegClk_PHASE_MASK         SRegClk__CFG3_PHASE_DLY_MASK
#endif /* defined(SRegClk__CFG3) */

#endif /* CY_CLOCK_SRegClk_H */


/* [] END OF FILE */
