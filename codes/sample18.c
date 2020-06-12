/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 *  gcc-4.8 -m32 -O0 -S sample18.c -o sample18.s
 *
 *  $Id: sample18.c $
 *  $Lastupdate: 2020/06/12 17:40:47 $
 */
/*
 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
 *--------+---------+---------+---------+---------X---------+---------+---------+---------+---------X
 */

struct data_struct
{
	int a;
	int b;
};

struct data_struct
fun(void)
{
	struct data_struct data;
	data.a = 20;
	data.b = 25;
	return data;
}

int main (void)
{
	struct data_struct local_data = fun();
	
	return 0;
}
