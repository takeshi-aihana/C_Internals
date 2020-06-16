/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 *  gcc-4.8 -m32 -O0 sample22.c -o test-sample22
 *
 *  $Id: sample22.c $
 *  $Lastupdate: 2020/06/16 15:09:52 $
 */
/*
 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
 *--------+---------+---------+---------+---------X---------+---------+---------+---------+---------X
 */

void __attribute__((section ("MySegment")))
fun(void)
{
}

int main (void)
{
	fun();
	return 0;
}
