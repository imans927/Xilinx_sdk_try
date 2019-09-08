/*
 * memorz_read.c
 *
 *  Created on: 08.07.2019
 *      Author: ga85piw
 */
#include "pred_controller_header.h"

void memory_read(float *u_opt,unsigned int* Mem_start){


	unsigned int *u_opt_mem_address=Mem_start+4+2*Nh+3*Nh+6*Nh*Nh+8*Nh+9*Nh*Nh+9*Nh*Nh+9*Nh*Nh+1;

    for (int i=0;i<3*Nh;i++){
    	u_opt[i]=u32_to_float(u_opt_mem_address[i]);
    }



}
