/*
 *  test_libecc - Copyright 2009 Slide, Inc.
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation; either version 2 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307 USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glib.h>

#include "libecc.h"


/**
 * __test_verify() will test the ecc_verify() function to comply with the transcript
 * from the original SECCURE site:
 *
 * $ seccure-sign
 * Assuming curve p160.
 * Enter private key: my private key
 * Go ahead and type your message ...
 * This message will be signed
 * ^D
 * Signature: $HPI?t(I*1vAYsl$|%21WXND=6Br*[>k(OR9B!GOwHqL0s+3Uq
 *
 * $ seccure-verify '8W;>i^H0qi|J&$coR5MFpR*Vn' '$HPI?t(I*1vAYsl$|%21WXND=6Br*[>k(OR9B!GOwHqL0s+3Uq'  
 * Go ahead and type your message ...
 * This message will be signed
 * ^D
 * Signature successfully verified!
 */
void __test_verify()
{
	char *data = "This message will be signed";
	char *signature = "$HPI?t(I*1vAYsl$|%21WXND=6Br*[>k(OR9B!GOwHqL0s+3Uq";
	ECC_KeyPair kp = ecc_new_keypair();
	kp->priv = "my private key";
	kp->pub = "8W;>i^H0qi|J&$coR5MFpR*Vn";

	g_assert(ecc_verify(data, signature, kp));
}


/**
 * __test_new_keypair() will test ecc_new_keypair() and make sure it generates an
 * allocated, but empty ::ECC_KeyPair object
 */
void __test_new_keypair()
{
	ECC_KeyPair kp = ecc_new_keypair();

	g_assert(kp != NULL);
	g_assert(kp->priv == NULL);
	g_assert(kp->pub == NULL);

	free(kp);
}

int main(int argc, char **argv)
{
	g_test_init(&argc, &argv, NULL);

	g_test_add_func("/libecc/ecc_new_keypair", __test_new_keypair);
	g_test_add_func("/libecc/ecc_verify", __test_verify);

	return g_test_run();
}