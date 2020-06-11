/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 *  gcc-4.8 -m32 -O0 -S sample16.c -o sample16.s
 *
 *  $Id: sample16.c $
 *  $Lastupdate: 2020/06/11 17:54:55 $
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

struct data_struct global_data;

int main(void)
{
	struct data_struct local_data;
	global_data.a = 10;
	global_data.b = 15;

	local_data.a = 25;
	local_data.b = 20;

	return 0;
}
