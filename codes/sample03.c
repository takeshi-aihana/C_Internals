/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 *  gcc-4.8 -m32 -S sample03.c -o sample03.s
 *
 *  $Id: sample03.c $
 *  $Lastupdate: 2020/06/04 17:27:45 $
 */
/*
 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
 *--------+---------+---------+---------+---------X---------+---------+---------+---------+---------X
 */

void fun()
{
	int a = 2;
	int b = 3;
	int c = 24;

	a = a + b;
	a = a + b * c;
}