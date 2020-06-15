/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 *  gcc-4.8 -m32 -O0 sample19.c -o test-sample19
 *
 *  $Id: sample19.c $
 *  $Lastupdate: 2020/06/15 17:17:15 $
 */
/*
 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
 *--------+---------+---------+---------+---------X---------+---------+---------+---------+---------X
 */

void asm_fun();
extern int asm_var;

int x;

void
main (void)
{
	asm_fun();

	asm_var++;
}
