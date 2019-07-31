/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

uint32 filteredCount;   /* # of filtered transitions of input pin 'SW' */
uint8 divider;
char8 charDivider[9];
uint16 charVolume [6];
uint8 sale_number[6];
uint8 sale_number_copy[6];
uint16 charVolumeCopy [6];
uint8 int_salenumber;
uint8 DecVol;
uint8 shift_number[6];
uint8 int_shiftnumber;
uint8 PrintVol;

/*
*********************************************************************************************************
*
*                            Var SCREENS
*          
*********************************************************************************************************
*/
uint8 touch1[20];

/*
*********************************************************************************************************
*
*                            Estructura dispensador
*          
*********************************************************************************************************
*/

struct position{
    uint8 dir;                      //Direccion
    uint8 totalsNozzle[4][2][5];   //Totales Manguera: [0-3] // [0]=Volumen [1]=Dinero // [8 ó 12 - 4 ó 5]
    uint8 ppuNozzle[4][3];         //PPU autorizados [Manguera 0-3][Datos]
    uint8 moneySale[4];            //Venta de Dinero vendido
    uint8 volumeSale[5];           //Venta de Volumen vendido
    uint8 ppuSale[14];              //Venta de PPU vendido
    uint8 productSale;              //Venta de Producto vendido
    uint8 states[5];                //Estados a Gbr
    uint8 MepsanStore[50];          //Datos Mepsan por posición    
    uint8 ProcessedPPU[4][6];
    uint8 msn_plate[8];             //placa vehiculo por lado
    uint8 MepRequest;
    uint8 Nozzle;
    uint8 km[7];
    uint8 Copy;
    
};

struct pump{
   struct position a;
   struct position b;
   struct position c;
   struct position d;
};

struct pump side;       //lado del surtidor

/* [] END OF FILE */
