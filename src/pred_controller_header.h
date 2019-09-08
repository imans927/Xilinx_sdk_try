/*
 * pred_controller_header.h
 *
 *  Created on: 27.06.2019
 *      Author: ga85piw
 */

#ifndef SRC_PRED_CONTROLLER_HEADER_H_
#define SRC_PRED_CONTROLLER_HEADER_H_



#define Nh 4
#define we 1
#define ts 0.007853981633
#define N_out 2

void offline(double *x_kk,float *y_ref_kk,float *u_kk,float *y_hat,float *r_hat, float *v_mul_h_inv, float *v_gen,float *h_hat_inv);
void memory_write_offline(float *y_hat,float *r_hat,float *v_mul_h_inv, float *v_gen,float *h_hat_inv,unsigned int* Mem_start);
void memory_write_online(float *x_kk,float *y_ref_kk,float *u_kk,unsigned int* Mem_start);
void memory_read(float *u_opt,unsigned int* Mem_start);
void print_memory(unsigned int* Mem_start);
void y_ref(double *x_kk_minus_1, float *y_ref_kk);
void state_space_model(float *u_opt,double *x_kk_d);
//void print_memory(unsigned int* Mem_start,float *y_hat,float *r_hat);
unsigned int float_to_u32(float value);
float u32_to_float(unsigned int value);
void double_to_float(double *x_kk_d,float *x_kk);



#define y_hat_row 2*Nh
#define y_hat_col 3*Nh

#define r_hat_row 2*Nh
#define r_hat_col 4

#define v_mul_h_inv_row 3*Nh
#define v_mul_h_inv_col 3*Nh

#define v_gen_row 3*Nh
#define v_gen_col 3*Nh

#define h_hat_inv_row 3*Nh
#define h_hat_inv_col 3*Nh


#define Y_Hat(p,q)			(y_hat_mem_address[p*y_hat_col +q])
#define R_Hat(p,q)			(r_hat_mem_address[p*r_hat_col +q])
#define V_Mul_H_Inv(p,q)	(v_mul_h_inv_mem_address[p*v_mul_h_inv_col +q])
#define V_Gen(p,q)			(v_gen_mem_address[p*v_gen_col +q])
#define H_Hat_Inv(p,q)		(h_hat_inv_mem_address[p*h_hat_inv_col +q])







#endif /* SRC_PRED_CONTROLLER_HEADER_H_ */
