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
#include <GVar.h>
#include <printer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




CY_ISR(debouncedInt_Handler)
{
	/* Debouncer status reg is cleared through read and filtered count incremented*/
	filteredCount++;
} 

int main()
{
    uint8 x;
    uint8 screenSize;
    uint8 screenValue;
     /* Interrupt handler for switch and debounced switch */
    debounced_Int_StartEx(debouncedInt_Handler);
    
     /* Clears pending interrupt */    
    debounced_Int_ClearPending();
    
    /* printer UART */
    PRINTER_A_Start();
    
    /* screen UART */
    screen_Start();
    
    EEPROM_1_Start();
    side.a.Copy = 0;
    if(EEPROM_1_ReadByte(0) == 0x5A){
        for(x=0;x<6;x++){
    		sale_number[x]=EEPROM_1_ReadByte(x);
    	}
    }else{
        EEPROM_1_WriteByte(0x5A,0);
        for(x=1;x<6;x++){
    		sale_number[x]='0';
    	}
    }
    int_salenumber=((sale_number[5]&0x0F)*10000)+((sale_number[4]&0x0F)*1000)+((sale_number[3]&0x0F)*100)+((sale_number[2]&0x0F)*10)+((sale_number[1]&0x0F));
    
    if(EEPROM_1_ReadByte(6) == 0x5A){
        for(x=0;x<6;x++){
    		shift_number[x+6]=EEPROM_1_ReadByte(x+6);
    	}
    }else{
        EEPROM_1_WriteByte(0x5A,6);
        for(x=1;x<6;x++){
    		shift_number[x+6]='0';
    	}
    }
    int_shiftnumber=((shift_number[5]&0x0F)*10000)+((shift_number[4]&0x0F)*1000)+((shift_number[3]&0x0F)*100)+((shift_number[2]&0x0F)*10)+((shift_number[1]&0x0F));
    
    side.a.dir = 0x00;
    screenValue = 0;
    divider = EEPROM_1_ReadByte(20);
    for(;;)
    {
        /* Enable global interrupts. */
	    CyGlobalIntEnable; 
        screenSize = screen_GetRxBufferSize();
        if(screenSize >= 5 ){
            for(uint8 LCDRx = 0; LCDRx < screenSize; LCDRx++){
                touch1[LCDRx] = screen_ReadRxData();
            }            
        }
        CyDelay(4);
        switch(touch1[8]){            
            case 0x1C:
        		screenValue = 0x0A;
        		for(uint8 LCDRx = 0; LCDRx < 20; LCDRx++){
        			touch1[LCDRx] = 0x00;
        		}	
                for(uint8 LCDRx = 0; LCDRx < 8; LCDRx++){
                    side.a.msn_plate[LCDRx] = 0x20;
                }
                PrintVol = 0;
                side.a.Copy = 0;
        	break;
            case 0x2C:
        		screenValue = 0x0B;
        		for(uint8 LCDRx = 0; LCDRx < 20; LCDRx++){
        			touch1[LCDRx] = 0x00;
        		}	
                for(uint8 LCDRx = 0; LCDRx < 5; LCDRx++){
                    side.a.volumeSale[LCDRx] = 0x20;
                }
                for(uint8 LCDRx = 0; LCDRx < 8; LCDRx++){
                    side.a.msn_plate[LCDRx] = 0x20;
                }
        	break;
            case 0x3C:
        		screenValue = 0x00;
        		for(uint8 LCDRx = 0; LCDRx < 20; LCDRx++){
        			touch1[LCDRx] = 0x00;
        		}	
                for(uint8 LCDRx = 0; LCDRx < 8; LCDRx++){
                    side.a.msn_plate[LCDRx] = 0x20;
                }
        	break;
            case 0x4C:
        		screenValue = 0xCD;
        		for(uint8 LCDRx = 0; LCDRx < 20; LCDRx++){
        			touch1[LCDRx] = 0x00;
        		}	
                for(uint8 LCDRx = 0; LCDRx < 8; LCDRx++){
                    charDivider[LCDRx] = 0x20;
                }
        	break;
            case 0x53:
                for(uint8 LCDRx = 0; LCDRx < 20; LCDRx++){
        			touch1[LCDRx] = 0x00;
        		}
                if(screenValue == 0xAC){
                    screenValue = 0;
                    side.a.Copy = 1;
                    PrintReceipt(side.a.dir);
                }
                
            break;
            case 0x4E: 
                for(uint8 LCDRx = 0; LCDRx < 20; LCDRx++){
        			touch1[LCDRx] = 0x00;
        		}
                screenValue = 0;
                side.a.Copy = 0;  
                filteredCount = 0;
                PrintVol = 0;
            break;
            case 0xDD:
                for(uint8 LCDRx = 0; LCDRx < 20; LCDRx++){
        			touch1[LCDRx] = 0x00;
        		}
                screenValue = 0;
                side.a.Copy = 0;  
                filteredCount = 0;
                PrintVol = 0;
            break;
        }
        if(touch1[3] == 0x83 && screenValue == 0x0A){       //Lectura de placa       
            for(uint8 LCDRx = 7; LCDRx < 15; LCDRx++){
                if((touch1[LCDRx] == 0x00) ||(touch1[LCDRx] == 0xFF))
                    break;
                if(touch1[LCDRx] > 96 && touch1[LCDRx] < 123){
                    side.a.msn_plate[LCDRx-7] = touch1[LCDRx]-0x20;                            
                }else{
                    side.a.msn_plate[LCDRx-7] = touch1[LCDRx];
                }
    		}
            for(uint8 LCDRx = 0; LCDRx < 20; LCDRx++){
    			touch1[LCDRx] = 0x00;
    		}
            PrintReceipt(side.a.dir);
            side.a.Copy = 1;
            screenValue =0xAC;
        }
        
        if(touch1[3] == 0x83 && screenValue == 0xCD){     //Lectura de divisor          
            for(uint8 LCDRx = 7; LCDRx < 15; LCDRx++){
                if((touch1[LCDRx] == 0x00) ||(touch1[LCDRx] == 0xFF))
                    break;
                if(touch1[LCDRx] > 96 && touch1[LCDRx] < 123){
                    charDivider[LCDRx-7] = touch1[LCDRx]-0x20;                            
                }else{
                    charDivider[LCDRx-7] = touch1[LCDRx];
                }
                charDivider[8] = 0x00;
                divider = atoi(charDivider);
    		}
            for(uint8 LCDRx = 0; LCDRx < 20; LCDRx++){
    			touch1[LCDRx] = 0x00;
    		}   
            EEPROM_1_WriteByte(divider,20);
            screenValue = 0x00;
        }
        
        if(touch1[3] == 0x83 && screenValue == 0x0B){     //Imprimir volumen          
            for(uint8 LCDRx = 7; LCDRx < 15; LCDRx++){
                if((touch1[LCDRx] == 0x00) ||(touch1[LCDRx] == 0xFF))
                    break;
                if(touch1[LCDRx] > 96 && touch1[LCDRx] < 123){
                    side.a.volumeSale[LCDRx-7] = touch1[LCDRx]-0x20;                            
                }else{
                    side.a.volumeSale[LCDRx-7] = touch1[LCDRx];
                }               
    		}
            for(uint8 LCDRx = 0; LCDRx < 20; LCDRx++){
    			touch1[LCDRx] = 0x00;
    		}          
            screenValue = 0x0A;
            PrintVol = 1;
            side.a.Copy = 0;
            //PrintReceipt(side.a.dir);
        }
        
    }
}

/* [] END OF FILE */
