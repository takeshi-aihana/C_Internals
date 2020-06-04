/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 *  gcc-4.8 -Wall -g3 sample01.c -o do-sample01
 * 
 *  gcc-4.8 -m32 -S sample01.c -o sample01.s
 *
 *  $Id: sample01.c $
 *  $Lastupdate: 2020/06/03 13:49:09 $
 */
/*
 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
 *--------+---------+---------+---------+---------X---------+---------+---------+---------+---------X
 */

int globalVar;

void main()
{
	globalVar = 10;
}
