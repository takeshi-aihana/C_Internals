/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 *  gcc-4.8 -m32 -O0 -S sample17.c -o sample17.s
 *
 *  $Id: sample17.c $
 *  $Lastupdate: 2020/06/12 15:09:06 $
 */
/*
 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
 *--------+---------+---------+---------+---------X---------+---------+---------+---------+---------X
 */
#include <stdio.h>
#include <stdlib.h>

struct data_struct
{
	char a;
	int b;
};

struct data_struct_packed_01
{
	char a;
	int b;
}__attribute__((packed));

struct data_struct_packed_02
{
	char a;
	int b __attribute__((packed));
};


int main (void)
{
	struct data_struct local_data;
	struct data_struct_packed_01 local_data_01;
	struct data_struct_packed_02 local_data_02;
	
	printf ("total size of struct = %d\n", (int) sizeof(local_data));
	printf ("total size of struct = %d\n", (int) sizeof(local_data_01));
	printf ("total size of struct = %d\n", (int) sizeof(local_data_02));
	
	return 0;
}
