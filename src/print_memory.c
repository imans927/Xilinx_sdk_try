/*
 * print_memory.c
 *
 *  Created on: 28.06.2019
 *      Author: ga85piw
 */

#include "pred_controller_header.h"
#include "stdio.h"



void print_memory(unsigned int* Mem_start)
{

	unsigned int *x_kk_mem_address=Mem_start;
	unsigned int *y_ref_kk_mem_address=Mem_start+4;
	unsigned int *u_kk_mem_address=Mem_start+4+2*Nh;
	unsigned int *y_hat_mem_address=Mem_start+4+2*Nh+3*Nh;
	unsigned int *r_hat_mem_address=Mem_start+4+2*Nh+3*Nh+6*Nh*Nh;
	unsigned int *v_mul_h_inv_mem_address=Mem_start+4+2*Nh+3*Nh+6*Nh*Nh+8*Nh;
	unsigned int *v_gen_mem_address=Mem_start+4+2*Nh+3*Nh+6*Nh*Nh+8*Nh+9*Nh*Nh;
	unsigned int *h_hat_inv_mem_address=Mem_start+4+2*Nh+3*Nh+6*Nh*Nh+8*Nh+9*Nh*Nh+9*Nh*Nh;
	unsigned int *u_opt_mem_address=Mem_start+4+2*Nh+3*Nh+6*Nh*Nh+8*Nh+9*Nh*Nh+9*Nh*Nh+9*Nh*Nh+1;



	printf("\n In print memory Function  \n",Nh);

	for (int i=0;i<4;i++){
		//printf("\n x[%d] = %f \t & address is %x",i,u32_to_float(Xil_In32(x_kk_mem_address+i)),(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+4*i));
		printf("\n x_kk[%d] = %f \t & address is %x",i,u32_to_float(x_kk_mem_address[i]),&(x_kk_mem_address[i]));
	}

	printf("\n");

	for (int i=0;i<2*Nh;i++){
		//printf("\n x[%d] = %f \t & address is %x",i,u32_to_float(Xil_In32(x_kk_mem_address+i)),(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+4*i));
		printf("\n y_ref_kk[%d] = %f \t & address is %x",i,u32_to_float(y_ref_kk_mem_address[i]),&(y_ref_kk_mem_address[i]));
	}

	printf("\n");

	for (int i=0;i<3*Nh;i++){
		//printf("\n x[%d] = %f \t & address is %x",i,u32_to_float(Xil_In32(x_kk_mem_address+i)),(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+4*i));
		printf("\n u_kk[%d] = %f \t & address is %x",i,u32_to_float(u_kk_mem_address[i]),&(u_kk_mem_address[i]));
	}
	///////////////////////////////
	/*

	printf("\n y_hat 4th row and last col is");

	for (int i=0;i<3*Nh;i++){
		//printf("\n x[%d] = %f \t & address is %x",i,u32_to_float(Xil_In32(x_kk_mem_address+i)),(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+4*i));
		printf("\n y_hat[3][%d] = %f \t & address is %x",i,u32_to_float(Y_Hat(3,i)),&(Y_Hat(3,i)));
	}

	printf("\n");

	for (int i=0;i<2*Nh;i++){
		//printf("\n x[%d] = %f \t & address is %x",i,u32_to_float(Xil_In32(x_kk_mem_address+i)),(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+4*i));
		printf("\n y_hat[%d][12] = %f \t & address is %x",i,u32_to_float(Y_Hat(i,3*Nh-1)),&(Y_Hat(i,3*Nh-1)));
	}
	/////////////////////////////

	printf("\n r_hat last row and 3rd col is");

	for (int i=0;i<4;i++){
		//printf("\n x[%d] = %f \t & address is %x",i,u32_to_float(Xil_In32(x_kk_mem_address+i)),(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+4*i));
		printf(" \n r_hat[8][%d] = %f & address is %x   ",i,u32_to_float(R_Hat(7,i)),&(R_Hat(7,i)));
	}

	printf("\n");

	for (int i=0;i<2*Nh;i++){
		//printf("\n x[%d] = %f \t & address is %x",i,u32_to_float(Xil_In32(x_kk_mem_address+i)),(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+4*i));
		printf("\n r_hat[%d][3] = %f \t & address is %x   ",i,u32_to_float(R_Hat(i,2)),&(R_Hat(i,2)));
	}

	//////////////////

	printf("\n v_mul_h_inv 6th row and last col is");

	for (int i=0;i<3*Nh;i++){
		//printf("\n x[%d] = %f \t & address is %x",i,u32_to_float(Xil_In32(x_kk_mem_address+i)),(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+4*i));
		printf(" \n V_Mul_H_Inv[6][%d] = %f & address is %x   ",i,u32_to_float(V_Mul_H_Inv(5,i)),&(V_Mul_H_Inv(5,i)));
	}
	printf("\n");

	for (int i=0;i<3*Nh;i++){
		//printf("\n x[%d] = %f \t & address is %x",i,u32_to_float(Xil_In32(x_kk_mem_address+i)),(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+4*i));
		printf("\n V_Mul_H_Inv[%d][12] = %f \t & address is %x   ",i,u32_to_float(V_Mul_H_Inv(i,11)),&(V_Mul_H_Inv(i,11)));
	}

	//////////////////

	printf("\n v_gen_mem 5th row and last col is");

	for (int i=0;i<3*Nh;i++){
		//printf("\n x[%d] = %f \t & address is %x",i,u32_to_float(Xil_In32(x_kk_mem_address+i)),(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+4*i));
		printf(" \n v_gen[5][%d] = %f & address is %x   ",i,u32_to_float(V_Gen(4,i)),&(V_Gen(4,i)));
	}

	printf("\n");

	for (int i=0;i<3*Nh;i++){
		//printf("\n x[%d] = %f \t & address is %x",i,u32_to_float(Xil_In32(x_kk_mem_address+i)),(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+4*i));
		printf("\n v_gen[%d][12] = %f \t & address is %x   ",i,u32_to_float(V_Gen(i,11)),&(V_Gen(i,11)));
	}


	//////////////////

	printf("\n H_Hat_Inv last row and last col is");

	for (int i=0;i<3*Nh;i++){
		//printf("\n x[%d] = %f \t & address is %x",i,u32_to_float(Xil_In32(x_kk_mem_address+i)),(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+4*i));
		printf(" \n h_hat_Inv[12][%d] = %f & address is %x   ",i,u32_to_float(H_Hat_Inv(11,i)),&(H_Hat_Inv(11,i)));
	}

	printf("\n");

	for (int i=0;i<3*Nh;i++){
		//printf("\n x[%d] = %f \t & address is %x",i,u32_to_float(Xil_In32(x_kk_mem_address+i)),(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+4*i));
		printf("\n h_hat_Inv[%d][12] = %f \t & address is %x   ",i,u32_to_float(H_Hat_Inv(i,11)),&(H_Hat_Inv(i,11)));
	}
*/

	printf("\n Uopt is  \n",Nh);

	for (int i=0;i<3*Nh;i++){
		//printf("\n x[%d] = %f \t & address is %x",i,u32_to_float(Xil_In32(x_kk_mem_address+i)),(XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR+4*i));
		printf("\n u_opt[%d] = %f \t & address is %x",i,u32_to_float(u_opt_mem_address[i]),&(u_opt_mem_address[i]));
	}



}
