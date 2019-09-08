/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "pred_controller_header.h"
#include "xil_io.h"
#include "xparameters.h"
#include "xpredictive_controller.h"
#include "xtime_l.h"


XPredictive_controller predictive_ctrl;
XPredictive_controller_Config *predictive_ctrl_ptr;



int main()
{
    init_platform();
    int status;
    float x_kk[4];
    double x_kk_d[4];
    float y_ref_kk[2*Nh];
    float u_kk[3*Nh];
    float y_hat[6*Nh*Nh];
    float r_hat[2*4*Nh];
    float v_mul_h_inv[9*Nh*Nh];
    float v_gen[9*Nh*Nh];
    float h_hat_inv[9*Nh*Nh];
    float u_opt[3*Nh]={};
    XTime tStart,tEnd;



    // look up the device config

    predictive_ctrl_ptr=XPredictive_controller_LookupConfig(XPAR_PREDICTIVE_CONTROLLER_0_DEVICE_ID);
    if(!predictive_ctrl_ptr){
    	xil_printf("ERROR: Lookup of acclerator configuration failed.\n\r");
    	return XST_FAILURE;
    }

    // Initialize the device

    status=XPredictive_controller_CfgInitialize(&predictive_ctrl,predictive_ctrl_ptr);
    if (status != XST_SUCCESS)
    {
    	xil_printf("Error could not initialize accelerator.\n\r");
    	exit(-1);

    }

    unsigned int* Mem_start=(unsigned int*)XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR;
    unsigned int *flag_mem_address=Mem_start+4+2*Nh+3*Nh+6*Nh*Nh+8*Nh+9*Nh*Nh+9*Nh*Nh+9*Nh*Nh;
    flag_mem_address[0]=1;




   offline(x_kk_d,y_ref_kk,u_kk,y_hat,r_hat,v_mul_h_inv,v_gen,h_hat_inv);


   printf("Hello World\n\r");
   printf("Added this line in try branch");

   printf("\n Nh is %d \n",Nh);

   XPredictive_controller_Set_X_KK_src(&predictive_ctrl,Mem_start);
   //XPredictive_controller_Set_X_KK_src(&predictive_ctrl,XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR);
   XPredictive_controller_Set_Y_REF_KK_src(&predictive_ctrl,Mem_start+4);
   XPredictive_controller_Set_U_KK_src(&predictive_ctrl,Mem_start+4+2*Nh);
   XPredictive_controller_Set_Y_HAT_src(&predictive_ctrl,Mem_start+4+2*Nh+3*Nh);
   XPredictive_controller_Set_R_HAT_src(&predictive_ctrl,Mem_start+4+2*Nh+3*Nh+6*Nh*Nh);
   XPredictive_controller_Set_V_MUL_H_INV_src(&predictive_ctrl,Mem_start+4+2*Nh+3*Nh+6*Nh*Nh+8*Nh);
   XPredictive_controller_Set_V_GEN_src(&predictive_ctrl,Mem_start+4+2*Nh+3*Nh+6*Nh*Nh+8*Nh+9*Nh*Nh);
   XPredictive_controller_Set_H_HAT_INV_src(&predictive_ctrl,Mem_start+4+2*Nh+3*Nh+6*Nh*Nh+8*Nh+9*Nh*Nh+9*Nh*Nh);
   XPredictive_controller_Set_flag(&predictive_ctrl,Mem_start+4+2*Nh+3*Nh+6*Nh*Nh+8*Nh+9*Nh*Nh+9*Nh*Nh+9*Nh*Nh);
   XPredictive_controller_Set_out_r(&predictive_ctrl,Mem_start+4+2*Nh+3*Nh+6*Nh*Nh+8*Nh+9*Nh*Nh+9*Nh*Nh+9*Nh*Nh+1);



   memory_write_offline(y_hat,r_hat,v_mul_h_inv,v_gen,h_hat_inv,Mem_start);

   printf("%d : %.2f,%.2f,%.2f, %.2f,%.2f,%.2f, %.2f,%.2f,%.2f, %.2f,%.2f,%.2f,\n",1,u_opt[0],u_opt[1],u_opt[2],u_opt[3],u_opt[4],u_opt[5],u_opt[6],
   u_opt[7],u_opt[8],u_opt[9],u_opt[10],u_opt[11]);
   printf("%d :  %.6f, %.6f, %.6f, %.6f",1,x_kk_d[0],x_kk_d[1],x_kk_d[2],x_kk_d[3]);

for (int loop=2;loop<=10;loop++){

if (loop>2)
	{flag_mem_address[0]=0;}

   y_ref(x_kk_d,y_ref_kk);
   double_to_float(x_kk_d,x_kk);

for (int i=0;i<3*Nh;i++)
{
	u_kk[i]=u_opt[i];

}
/*
printf("\n%d : %.2f,%.2f,%.2f, %.2f,%.2f,%.2f, %.2f,%.2f,%.2f, %.2f,%.2f,%.2f,\n",1,u_opt[0],u_opt[1],u_opt[2],u_opt[3],u_opt[4],u_opt[5],u_opt[6],
u_opt[7],u_opt[8],u_opt[9],u_opt[10],u_opt[11]);
printf("\n%d :  %.6f, %.6f, %.6f, %.6f\n",1,x_kk[0],x_kk[1],x_kk[2],x_kk[3]);
printf("\n%d :  %.6f, %.6f, %.6f, %.6f  %.6f, %.6f, %.6f, %.6f\n",2,y_ref_kk[0],y_ref_kk[1],y_ref_kk[2],y_ref_kk[3],y_ref_kk[4],y_ref_kk[5],y_ref_kk[6],y_ref_kk[7]);

*/

memory_write_online(x_kk,y_ref_kk,u_kk,Mem_start);




//xil_printf(" Starting predictive controller \n\r");

XPredictive_controller_Start(&predictive_ctrl);
XTime_GetTime((XTime*)&tStart);
while(!XPredictive_controller_IsDone(&predictive_ctrl));
XTime_GetTime((XTime*)&tEnd);
//xil_printf(" I think its done and output is \n\r");
//print_memory(Mem_start);

//printf ("\n Output took %11d clock cycles.\n",2*(tEnd-tStart));
//printf ("Output took %.2f us.\n", 1.0*(tEnd-tStart)/(COUNTS_PER_SECOND/1000000));

///////

memory_read(u_opt,Mem_start);

state_space_model(u_opt,x_kk_d);

double_to_float(x_kk_d,x_kk);

//if (loop >=900){
printf("\n%d :  %.6f, %.6f, %.6f, %.6f  %.6f, %.6f, %.6f, %.6f\n",loop,y_ref_kk[0],y_ref_kk[1],y_ref_kk[2],y_ref_kk[3],y_ref_kk[4],y_ref_kk[5],y_ref_kk[6],y_ref_kk[7]);
printf("%d : %.2f,%.2f,%.2f, %.2f,%.2f,%.2f, %.2f,%.2f,%.2f, %.2f,%.2f,%.2f,\n",loop,u_opt[0],u_opt[1],u_opt[2],u_opt[3],u_opt[4],u_opt[5],u_opt[6],
u_opt[7],u_opt[8],u_opt[9],u_opt[10],u_opt[11]);
printf("%d :  %.6f, %.6f, %.6f, %.6f\n",loop,x_kk[0],x_kk[1],x_kk[2],x_kk[3]);
printf ("%d : %.2f us.",loop, 1.0*(tEnd-tStart)/(COUNTS_PER_SECOND/1000000));
//}

}

    cleanup_platform();
    return 0;
}


/*
 *
 * flag_mem_address[0]=0;
XPredictive_controller_Set_out_r(&predictive_ctrl,Mem_start+4+2*Nh+3*Nh+6*Nh*Nh+8*Nh+9*Nh*Nh+9*Nh*Nh+9*Nh*Nh+13);

xil_printf(" Starting again predictive controller \n\r");

XPredictive_controller_Start(&predictive_ctrl);
XTime_GetTime((XTime*)&tStart);
while(!XPredictive_controller_IsDone(&predictive_ctrl));
XTime_GetTime((XTime*)&tEnd);
xil_printf(" I think its done and output is \n\r");

printf("\n Uopt is  \n",Nh);

unsigned int *u_opt_2_mem_address=Mem_start+4+2*Nh+3*Nh+6*Nh*Nh+8*Nh+9*Nh*Nh+9*Nh*Nh+9*Nh*Nh+13;

for (int i=0;i<3*Nh;i++){
	//printf("\n x[%d] = %f \t & address is %x",i,u32_to_float(Xil_In32(x_kk_mem_address+i)),(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+4*i));
	printf("\n u_opt[%d] = %f \t & address is %x",i,u32_to_float(u_opt_2_mem_address[i]),&(u_opt_2_mem_address[i]));
}



printf ("\n Output took %11d clock cycles.\n",2*(tEnd-tStart));
printf ("Output took %.2f us.\n", 1.0*(tEnd-tStart)/(COUNTS_PER_SECOND/1000000));*/
