/*******************************************************************************
* File Name: GlitchClk.h
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

#if !defined(CY_CLOCK_GlitchClk_H)
#define CY_CLOCK_GlitchClk_H

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

void GlitchClk_Start(void) ;
void GlitchClk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void GlitchClk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void GlitchClk_StandbyPower(uint8 state) ;
void GlitchClk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 GlitchClk_GetDividerRegister(void) ;
void GlitchClk_SetModeRegister(uint8 modeBitMask) ;
void GlitchClk_ClearModeRegister(uint8 modeBitMask) ;
uint8 GlitchClk_GetModeRegister(void) ;
void GlitchClk_SetSourceRegister(uint8 clkSource) ;
uint8 GlitchClk_GetSourceRegister(void) ;
#if defined(GlitchClk__CFG3)
void GlitchClk_SetPhaseRegister(uint8 clkPhase) ;
uint8 GlitchClk_GetPhaseRegister(void) ;
#endif /* defined(GlitchClk__CFG3) */

#define GlitchClk_Enable()                       GlitchClk_Start()
#define GlitchClk_Disable()                      GlitchClk_Stop()
#define GlitchClk_SetDivider(clkDivider)         GlitchClk_SetDividerRegister(clkDivider, 1u)
#define GlitchClk_SetDividerValue(clkDivider)    GlitchClk_SetDividerRegister((clkDivider) - 1u, 1u)
#define GlitchClk_SetMode(clkMode)               GlitchClk_SetModeRegister(clkMode)
#define GlitchClk_SetSource(clkSource)           GlitchClk_SetSourceRegister(clkSource)
#if defined(GlitchClk__CFG3)
#define GlitchClk_SetPhase(clkPhase)             GlitchClk_SetPhaseRegister(clkPhase)
#define GlitchClk_SetPhaseValue(clkPhase)        GlitchClk_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(GlitchClk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define GlitchClk_CLKEN              (* (reg8 *) GlitchClk__PM_ACT_CFG)
#define GlitchClk_CLKEN_PTR          ((reg8 *) GlitchClk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define GlitchClk_CLKSTBY            (* (reg8 *) GlitchClk__PM_STBY_CFG)
#define GlitchClk_CLKSTBY_PTR        ((reg8 *) GlitchClk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define GlitchClk_DIV_LSB            (* (reg8 *) GlitchClk__CFG0)
#define GlitchClk_DIV_LSB_PTR        ((reg8 *) GlitchClk__CFG0)
#define GlitchClk_DIV_PTR            ((reg16 *) GlitchClk__CFG0)

/* Clock MSB divider configuration register. */
#define GlitchClk_DIV_MSB            (* (reg8 *) GlitchClk__CFG1)
#define GlitchClk_DIV_MSB_PTR        ((reg8 *) GlitchClk__CFG1)

/* Mode and source configuration register */
#define GlitchClk_MOD_SRC            (* (reg8 *) GlitchClk__CFG2)
#define GlitchClk_MOD_SRC_PTR        ((reg8 *) GlitchClk__CFG2)

#if defined(GlitchClk__CFG3)
/* Analog clock phase configuration register */
#define GlitchClk_PHASE              (* (reg8 *) GlitchClk__CFG3)
#define GlitchClk_PHASE_PTR          ((reg8 *) GlitchClk__CFG3)
#endif /* defined(GlitchClk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define GlitchClk_CLKEN_MASK         GlitchClk__PM_ACT_MSK
#define GlitchClk_CLKSTBY_MASK       GlitchClk__PM_STBY_MSK

/* CFG2 field masks */
#define GlitchClk_SRC_SEL_MSK        GlitchClk__CFG2_SRC_SEL_MASK
#define GlitchClk_MODE_MASK          (~(GlitchClk_SRC_SEL_MSK))

#if defined(GlitchClk__CFG3)
/* CFG3 phase mask */
#define GlitchClk_PHASE_MASK         GlitchClk__CFG3_PHASE_DLY_MASK
#endif /* defined(GlitchClk__CFG3) */

#endif /* CY_CLOCK_GlitchClk_H */


/* [] END OF FILE */
