/*******************************************************************************
* File Name: EdgeClk.h
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

#if !defined(CY_CLOCK_EdgeClk_H)
#define CY_CLOCK_EdgeClk_H

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

void EdgeClk_Start(void) ;
void EdgeClk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void EdgeClk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void EdgeClk_StandbyPower(uint8 state) ;
void EdgeClk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 EdgeClk_GetDividerRegister(void) ;
void EdgeClk_SetModeRegister(uint8 modeBitMask) ;
void EdgeClk_ClearModeRegister(uint8 modeBitMask) ;
uint8 EdgeClk_GetModeRegister(void) ;
void EdgeClk_SetSourceRegister(uint8 clkSource) ;
uint8 EdgeClk_GetSourceRegister(void) ;
#if defined(EdgeClk__CFG3)
void EdgeClk_SetPhaseRegister(uint8 clkPhase) ;
uint8 EdgeClk_GetPhaseRegister(void) ;
#endif /* defined(EdgeClk__CFG3) */

#define EdgeClk_Enable()                       EdgeClk_Start()
#define EdgeClk_Disable()                      EdgeClk_Stop()
#define EdgeClk_SetDivider(clkDivider)         EdgeClk_SetDividerRegister(clkDivider, 1u)
#define EdgeClk_SetDividerValue(clkDivider)    EdgeClk_SetDividerRegister((clkDivider) - 1u, 1u)
#define EdgeClk_SetMode(clkMode)               EdgeClk_SetModeRegister(clkMode)
#define EdgeClk_SetSource(clkSource)           EdgeClk_SetSourceRegister(clkSource)
#if defined(EdgeClk__CFG3)
#define EdgeClk_SetPhase(clkPhase)             EdgeClk_SetPhaseRegister(clkPhase)
#define EdgeClk_SetPhaseValue(clkPhase)        EdgeClk_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(EdgeClk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define EdgeClk_CLKEN              (* (reg8 *) EdgeClk__PM_ACT_CFG)
#define EdgeClk_CLKEN_PTR          ((reg8 *) EdgeClk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define EdgeClk_CLKSTBY            (* (reg8 *) EdgeClk__PM_STBY_CFG)
#define EdgeClk_CLKSTBY_PTR        ((reg8 *) EdgeClk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define EdgeClk_DIV_LSB            (* (reg8 *) EdgeClk__CFG0)
#define EdgeClk_DIV_LSB_PTR        ((reg8 *) EdgeClk__CFG0)
#define EdgeClk_DIV_PTR            ((reg16 *) EdgeClk__CFG0)

/* Clock MSB divider configuration register. */
#define EdgeClk_DIV_MSB            (* (reg8 *) EdgeClk__CFG1)
#define EdgeClk_DIV_MSB_PTR        ((reg8 *) EdgeClk__CFG1)

/* Mode and source configuration register */
#define EdgeClk_MOD_SRC            (* (reg8 *) EdgeClk__CFG2)
#define EdgeClk_MOD_SRC_PTR        ((reg8 *) EdgeClk__CFG2)

#if defined(EdgeClk__CFG3)
/* Analog clock phase configuration register */
#define EdgeClk_PHASE              (* (reg8 *) EdgeClk__CFG3)
#define EdgeClk_PHASE_PTR          ((reg8 *) EdgeClk__CFG3)
#endif /* defined(EdgeClk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define EdgeClk_CLKEN_MASK         EdgeClk__PM_ACT_MSK
#define EdgeClk_CLKSTBY_MASK       EdgeClk__PM_STBY_MSK

/* CFG2 field masks */
#define EdgeClk_SRC_SEL_MSK        EdgeClk__CFG2_SRC_SEL_MASK
#define EdgeClk_MODE_MASK          (~(EdgeClk_SRC_SEL_MSK))

#if defined(EdgeClk__CFG3)
/* CFG3 phase mask */
#define EdgeClk_PHASE_MASK         EdgeClk__CFG3_PHASE_DLY_MASK
#endif /* defined(EdgeClk__CFG3) */

#endif /* CY_CLOCK_EdgeClk_H */


/* [] END OF FILE */
