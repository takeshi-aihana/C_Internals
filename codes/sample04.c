/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 *  gcc-4.8 -m32 -S sample04.c -o sample04.s
 *
 *  $Id: sample04.c $
 *  $Lastupdate: 2020/06/05 14:43:10 $
 */
/*
 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
 *--------+---------+---------+---------+---------X---------+---------+---------+---------+---------X
 */

void fun()
{
	int a = 4;
	int b = 8;
	int c = a | b;
	int d = b & c;
}
