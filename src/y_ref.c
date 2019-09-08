/*
 * y_ref.c
 *
 *  Created on: 08.07.2019
 *      Author: ga85piw
 */

#include "pred_controller_header.h"
#include "stdio.h"
#include <math.h>

void y_ref(double *x_kk_minus_1, float *y_ref_kk){


	double phi_int;
	double phi;
	double delta_phi;
	double Phi_N[Nh];
	double p_dq_ab[2*Nh][2];
	double is_dq_ref[2]={0.388958805065727,0.927121420626787};
	double y_ref[2*Nh];
	//float y_ref_kk[2*Nh];

	delta_phi=ts/we;

	phi_int=we*ts;

	phi=atan2(x_kk_minus_1[3],x_kk_minus_1[2]);

	//printf("\n atan angle is  %.9f and phi ext is %.9f \n", float(phi),phi_ext);
	//phi=atan((-0.0296396)/(0.9131435));
	phi=phi+phi_int;
	//phi=phi_ext+phi_int;

	for (int i=0;i<Nh;i++){

		Phi_N[i]=phi+delta_phi*i;
		//printf ("Phi_N[%d]=%.9f",i,Phi_N[i]);

	}

	for (int i=0;i<2*Nh;i++){

		if (i<Nh){

			p_dq_ab[i][0]=cos(Phi_N[i]);
			p_dq_ab[i][1]=-1*sin(Phi_N[i]);

			//printf("\n %.9f\t%.9f",p_dq_ab[i][0],p_dq_ab[i][1]);
		}

		if (i>=Nh){

			p_dq_ab[i][0]=sin(Phi_N[i-Nh]);
			p_dq_ab[i][1]=cos(Phi_N[i-Nh]);

			//printf("\n %.9f\t%.9f",p_dq_ab[i][0],p_dq_ab[i][1]);
		}

	}

	/// y_ref=p_dq_ab*is_dq_ref
//printf("\n");
	for (int i=0;i<2*Nh;i++){

		y_ref[i]=p_dq_ab[i][0]*is_dq_ref[0]+p_dq_ab[i][1]*is_dq_ref[1];
		//printf ("   ty_ref[%d]=%.9f",i,y_ref[i]);

	}

// re arranging
		for (int i=0;i<Nh;i++){

			y_ref_kk[i*N_out]=y_ref[i];
			y_ref_kk[(i*N_out)+1]=y_ref[i+Nh];
		}

		printf("\n");
			for (int i=0;i<2*Nh;i++){
				//printf ("   y_ref_kk[%d]=%.9f",i,y_ref_kk[i]);
				//printf (" %.9f,",y_ref_kk[i]);

			}




	//printf("\n angle is  %.9f \n", float(phi));
	//printf("\n delta angle is  %.9f \n", float(delta_phi));

	//printf("%.3d,  %.5f, %.5f, %.5f, %.5f\n",0,x_kk_minus_1[0],x_kk_minus_1[1],x_kk_minus_1[2],x_kk_minus_1[3]);
}


