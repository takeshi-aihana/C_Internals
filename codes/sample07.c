/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 *  gcc-4.8 -m32 -S sample07.c -o sample07.s
 *
 *  $Id: sample07.c $
 *  $Lastupdate: 2020/06/05 18:03:12 $
 */
/*
 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
 *--------+---------+---------+---------+---------X---------+---------+---------+---------+---------X
 */

void fun()
{
	int a = 4;
	int b = 8;
	int d = 0;

	while (b > a) {
		d = a + 2;
		b--;
	}
}
