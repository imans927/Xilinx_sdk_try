/*
 * u32_to_float.c
 *
 *  Created on: 27.06.2019
 *      Author: ga85piw
 */


	float u32_to_float(unsigned int value)
	{
		float result;
		union float_bytes{
			float fl;
			unsigned int U;
		} data;

		data.U=value;
		result=data.fl;

		return result;
	}
