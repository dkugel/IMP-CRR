/*******************************************************************************
* File Name: CounterClk.h
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

#if !defined(CY_CLOCK_CounterClk_H)
#define CY_CLOCK_CounterClk_H

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

void CounterClk_Start(void) ;
void CounterClk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void CounterClk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void CounterClk_StandbyPower(uint8 state) ;
void CounterClk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 CounterClk_GetDividerRegister(void) ;
void CounterClk_SetModeRegister(uint8 modeBitMask) ;
void CounterClk_ClearModeRegister(uint8 modeBitMask) ;
uint8 CounterClk_GetModeRegister(void) ;
void CounterClk_SetSourceRegister(uint8 clkSource) ;
uint8 CounterClk_GetSourceRegister(void) ;
#if defined(CounterClk__CFG3)
void CounterClk_SetPhaseRegister(uint8 clkPhase) ;
uint8 CounterClk_GetPhaseRegister(void) ;
#endif /* defined(CounterClk__CFG3) */

#define CounterClk_Enable()                       CounterClk_Start()
#define CounterClk_Disable()                      CounterClk_Stop()
#define CounterClk_SetDivider(clkDivider)         CounterClk_SetDividerRegister(clkDivider, 1u)
#define CounterClk_SetDividerValue(clkDivider)    CounterClk_SetDividerRegister((clkDivider) - 1u, 1u)
#define CounterClk_SetMode(clkMode)               CounterClk_SetModeRegister(clkMode)
#define CounterClk_SetSource(clkSource)           CounterClk_SetSourceRegister(clkSource)
#if defined(CounterClk__CFG3)
#define CounterClk_SetPhase(clkPhase)             CounterClk_SetPhaseRegister(clkPhase)
#define CounterClk_SetPhaseValue(clkPhase)        CounterClk_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(CounterClk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define CounterClk_CLKEN              (* (reg8 *) CounterClk__PM_ACT_CFG)
#define CounterClk_CLKEN_PTR          ((reg8 *) CounterClk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define CounterClk_CLKSTBY            (* (reg8 *) CounterClk__PM_STBY_CFG)
#define CounterClk_CLKSTBY_PTR        ((reg8 *) CounterClk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define CounterClk_DIV_LSB            (* (reg8 *) CounterClk__CFG0)
#define CounterClk_DIV_LSB_PTR        ((reg8 *) CounterClk__CFG0)
#define CounterClk_DIV_PTR            ((reg16 *) CounterClk__CFG0)

/* Clock MSB divider configuration register. */
#define CounterClk_DIV_MSB            (* (reg8 *) CounterClk__CFG1)
#define CounterClk_DIV_MSB_PTR        ((reg8 *) CounterClk__CFG1)

/* Mode and source configuration register */
#define CounterClk_MOD_SRC            (* (reg8 *) CounterClk__CFG2)
#define CounterClk_MOD_SRC_PTR        ((reg8 *) CounterClk__CFG2)

#if defined(CounterClk__CFG3)
/* Analog clock phase configuration register */
#define CounterClk_PHASE              (* (reg8 *) CounterClk__CFG3)
#define CounterClk_PHASE_PTR          ((reg8 *) CounterClk__CFG3)
#endif /* defined(CounterClk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define CounterClk_CLKEN_MASK         CounterClk__PM_ACT_MSK
#define CounterClk_CLKSTBY_MASK       CounterClk__PM_STBY_MSK

/* CFG2 field masks */
#define CounterClk_SRC_SEL_MSK        CounterClk__CFG2_SRC_SEL_MASK
#define CounterClk_MODE_MASK          (~(CounterClk_SRC_SEL_MSK))

#if defined(CounterClk__CFG3)
/* CFG3 phase mask */
#define CounterClk_PHASE_MASK         CounterClk__CFG3_PHASE_DLY_MASK
#endif /* defined(CounterClk__CFG3) */

#endif /* CY_CLOCK_CounterClk_H */


/* [] END OF FILE */
