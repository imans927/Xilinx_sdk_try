/*
 * float_to_u32.c
 *
 *  Created on: 27.06.2019
 *      Author: ga85piw
 */


	unsigned int float_to_u32(float value)
	{
		unsigned int result;
		union float_bytes{
			float fl;
			unsigned int U;
		} data;

		data.fl=value;
		result=data.U;

		return result;
	}
