/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 *  gcc-4.8 -m32 -S sample06.c -o sample06.s
 *
 *  $Id: sample06.c $
 *  $Lastupdate: 2020/06/05 16:59:05 $
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

	switch (b) {
	case 2:
		a++;
		break;
	case 8:
		b++;
		break;
	default:
		d++;
		break;
	}
}
