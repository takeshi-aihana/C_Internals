/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 *  gcc-4.8 -m32 -S sample10.c -o sample10.s
 *
 *  $Id: sample10.c $
 *  $Lastupdate: 2020/06/08 15:30:39 $
 */
/*
 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
 *--------+---------+---------+---------+---------X---------+---------+---------+---------+---------X
 */

// これはグローバル宣言
int globalVar[5];

void f(void)
{
	int b;
	int localArr[5];

	globalVar[2] = 12;
	localArr[0] = 3;
	localArr[4] = 18;
	b = localArr[4];
}
