/*******************************************************************************
* File Name: main.c
*
* Version: 1.10
*
* Description:
*  This is source code for the Digital Utility example project.
*
* The project demonstrates sample uses of four of the Digital Utility
* components.
* 
********************************************************************************
* Copyright 2012-2013, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <project.h>

uint32 filteredCount = 0u;   /* # of filtered transitions of input pin 'SW' */


CY_ISR(debouncedInt_Handler)
{
	/* Debouncer status reg is cleared through read and filtered count incremented*/
	filteredCount++;
} 

int main()
{
     /* Interrupt handler for switch and debounced switch */
    debounced_Int_StartEx(debouncedInt_Handler);
    
     /* Clears pending interrupt */    
    debounced_Int_ClearPending();
    
    /* printer UART */
    PRINTER_A_Start();
    
    /* screen UART */
    screen_Start();
    for(;;)
    {
        /* Enable global interrupts. */
	    CyGlobalIntEnable; 
        if (filteredCount == 10)
            filteredCount = 0;
    }
}

/* [] END OF FILE */
