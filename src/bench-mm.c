/*-****************************************************************************/
/*-                                                                           */
/*-            Copyright (c) 2013 by SOCware Inc.                             */
/*-                                                                           */
/*-  This software is copyrighted by and is the sole property of SOCware, Inc.*/
/*-  All rights, title, ownership, or other interests in the software remain  */
/*-  the property of SOCware, Inc. The source code is for FREE short-term     */
/*-  evaluation, educational or non-commercial research only. Any commercial  */
/*-  application may only be used in accordance with the corresponding license*/
/*-  agreement. Any unauthorized use, duplication, transmission, distribution,*/
/*-  or disclosure of this software is expressly forbidden.                   */
/*-                                                                           */
/*-  Knowledge of the source code may NOT be used to develop a similar product*/
/*-                                                                           */
/*-  This Copyright notice may not be removed or modified without prior       */
/*-  written consent of SOCware, Inc.                                         */
/*-                                                                           */
/*-  SOCWare, Inc. reserves the right to modify this software                 */
/*-  without notice.                                                          */
/*-                                                                           */
/*-             socware.help@gmail.com                                        */
/*-             http://socware.net                                            */
/*-                                                                           */
/*-****************************************************************************/
#include <string.h>
#include "plt.h"
#include "_soc.h"

void *a00100008;
void *a00100058;
void *a001000a8;
void *a001003b8;
void *a001003e8;
void *a00100458;
void *a001004a8;
void *a00100cb8;
void *a00100de8;
void *a00100e38;
void *a00104e48;
void *a001057f8;
void *a00105828;
void *a00105958;
void *a001059a8;
void *a001069b8;
void *a00106a08;
void *a0010ca18;
void *a0010ca68;
void *a0010d278;
void *a0010d290;
void *a0010d2a8;
void *a0010d2c0;
void *a0010d2f0;
void *a0010d320;
void *a0010d330;
void *a0010d330;
void *a0010d408;
void *a0010d478;
void *a0010d738;
void *a0010dd40;
void *a0010d4a8;
void *a0010d4a8;
void *a0010e0f8;
void *a0010e108;
void *a0010e118;
void *a0010e148;
void *a0010e148;
void *a0010d998;
void *a0010d9c8;
void *a0010d890;
void *a0010dd40;
void *a0010da50;
void *a0010d748;
void *a0010e118;
void *a0010e0a8;
void *a0010da28;
void *a0010e118;
void *a0010e150;
void *a0010e150;
void *a0010da28;
void *a0010e118;
void *a0010da28;
void *a0010e148;
void *a0010e278;
void *a0010e368;
void *a0010e4a8;
void *a0010da38;
void *a0010da28;
void *a0010da28;
void *a0010e0a8;
void *a0010e148;
void *a0010dd40;
void *a0010e168;
void *a0010dd40;
void *a0010e168;
void *a0010dd40;
void *a0010e168;
void *a0010dd40;
void *a0010e168;
void *a0010dd40;
void *a0010e168;
void *a0010dd40;
void *a0010e168;
void *a0010e168;
void *a0010e198;
void *a0010e168;
void *a0010e198;
void *a0010e118;
void *a0010ddf8;
void *a0010e118;
void *a0010e190;
void *a0010e190;
void *a0010dd40;
void *a0010e190;
void *a0010dd40;
void *a0010e190;
void *a0010e168;
void *a0010e118;
void *a0010e168;
void *a0010e168;
void *a0010dd40;
void *a0010e1f0;
void *a0010dd40;
void *a0010e1f0;
void *a0010e1f0;
void *a0010e278;
void *a0010e278;
void *a0010e1f0;
void *a0010e168;
void *a0010e168;
void *a0010e168;
void *a0010e168;
void *a0010e228;
void *a0010e278;
void *a0010e278;
void *a0010e228;
void *a0010e228;
void *a0010e298;
void *a0010e298;
void *a0010e228;
void *a0010e228;
void *a0010e278;
void *a0010e228;
void *a0010e278;
void *a0010e228;
void *a0010e278;
void *a0010e228;
void *a0010e278;
void *a0010e228;
void *a0010e278;
void *a0010e228;
void *a0010e278;
void *a0010e118;
void *a0010e118;
void *a0010e118;
void *a0010e168;
void *a0010e168;
void *a0010e198;
void *a0010e168;
void *a0010e118;
void *a0010e118;
void *a0010e198;
void *a0010e168;
void *a0010e1d8;
void *a0010e168;
void *a0010e1d8;
void *a0010e118;
void *a0010ddf8;
void *a0010e118;
void *a0010e118;
void *a0010e118;
void *a0010e118;
void *a0010e0d0;
void *a0010e118;
void *a0010e118;
void *a0010ddf8;
void *a0010e118;

static int cnt;

static mut_t tcm_mut;

static inline void *__malloc(unsigned sz, int line)
{
	void *p = heap_alloc(&plt_tcm, sz);
	if (!p) {
		printf("line: %d\n", line);
		while (1) ;
	}
	cnt++;
	return p;
}

#define _malloc(_sz)	__malloc(_sz, __LINE__)

static inline void _free(void *p)
{
	cnt++;
	heap_free(&plt_tcm, p);
}

int bench_mm(void)
{
	cnt = 0;
	mut_init(&tcm_mut);
	heap_init(&plt_tcm, (unsigned *)BASE_TCM, 0x10000, &tcm_mut);
	a00100008 = _malloc(68);
	a00100058 = _malloc(68);
	a001000a8 = _malloc(775);
	a001003b8 = _malloc(40);
	a001003e8 = _malloc(100);
	a00100458 = _malloc(68);
	a001004a8 = _malloc(2055);
	a00100cb8 = _malloc(292);
	a00100de8 = _malloc(68);
	a00100e38 = _malloc(16384);
	a00104e48 = _malloc(2468);
	a001057f8 = _malloc(40);
	a00105828 = _malloc(292);
	a00105958 = _malloc(68);
	a001059a8 = _malloc(4103);
	a001069b8 = _malloc(68);
	a00106a08 = _malloc(24583);
	a0010ca18 = _malloc(68);
	a0010ca68 = _malloc(2055);
	a0010d278 = _malloc(12);
	a0010d290 = _malloc(12);
	a0010d2a8 = _malloc(12);
	a0010d2c0 = _malloc(40);
	a0010d2f0 = _malloc(40);
	a0010d320 = _malloc(2);
	a0010d330 = _malloc(40);
	_free(a0010d330);
	a0010d408 = _malloc(100);
	a0010d478 = _malloc(40);
	a0010d738 = _malloc(7);
	a0010dd40 = _malloc(7);
	_free(a0010d4a8);
	a0010d4a8 = _malloc(8);
	a0010e0f8 = _malloc(8);
	a0010e108 = _malloc(8);
	a0010e118 = _malloc(40);
	a0010e148 = _malloc(40);
	_free(a0010e148);
	_free(a0010d998);
	_free(a0010d9c8);
	_free(a0010d890);
	_free(a0010dd40);
	_free(a0010da50);
	_free(a0010d748);
	_free(a0010e118);
	_free(a0010e0a8);
	a0010da28 = _malloc(46);
	a0010e118 = _malloc(47);
	a0010e150 = _malloc(40);
	_free(a0010e150);
	_free(a0010da28);
	a0010e118 = _malloc(40);
	_free(a0010da28);
	_free(a0010e148);
	_free(a0010e278);
	_free(a0010e368);
	_free(a0010e4a8);
	_free(a0010da38);
	_free(a0010da28);
	a0010da28 = _malloc(28);
	a0010e0a8 = _malloc(26);
	a0010e148 = _malloc(22);
	a0010dd40 = _malloc(2);
	a0010e168 = _malloc(40);
	_free(a0010dd40);
	_free(a0010e168);
	a0010dd40 = _malloc(3);
	a0010e168 = _malloc(40);
	_free(a0010dd40);
	_free(a0010e168);
	a0010dd40 = _malloc(3);
	a0010e168 = _malloc(40);
	_free(a0010dd40);
	_free(a0010e168);
	a0010e168 = _malloc(35);
	a0010e198 = _malloc(40);
	_free(a0010e168);
	_free(a0010e198);
	_free(a0010e118);
	_free(a0010ddf8);
	a0010e118 = _malloc(40);
	a0010e190 = _malloc(40);
	_free(a0010e190);
	a0010dd40 = _malloc(2);
	a0010e190 = _malloc(40);
	_free(a0010dd40);
	_free(a0010e190);
	_free(a0010e168);
	_free(a0010e118);
	_free(a0010e168);
	a0010e168 = _malloc(121);
	a0010dd40 = _malloc(2);
	a0010e1f0 = _malloc(40);
	_free(a0010dd40);
	_free(a0010e1f0);
	a0010e1f0 = _malloc(121);
	a0010e278 = _malloc(135);
	_free(a0010e278);
	_free(a0010e1f0);
	_free(a0010e168);
	a0010e168 = _malloc(40);
	_free(a0010e168);
	a0010e168 = _malloc(179);
	a0010e228 = _malloc(72);
	a0010e278 = _malloc(176);
	_free(a0010e278);
	_free(a0010e228);
	a0010e228 = _malloc(99);
	a0010e298 = _malloc(113);
	_free(a0010e298);
	_free(a0010e228);
	a0010e228 = _malloc(65);
	a0010e278 = _malloc(40);
	_free(a0010e228);
	_free(a0010e278);
	a0010e228 = _malloc(65);
	a0010e278 = _malloc(40);
	_free(a0010e228);
	_free(a0010e278);
	a0010e228 = _malloc(65);
	a0010e278 = _malloc(40);
	_free(a0010e228);
	_free(a0010e278);
	_free(a0010e118);
	a0010e118 = _malloc(40);
	_free(a0010e118);
	_free(a0010e168);
	a0010e168 = _malloc(40);
	a0010e198 = _malloc(40);
	_free(a0010e168);
	_free(a0010e118);
	a0010e118 = _malloc(40);
	_free(a0010e198);
	a0010e168 = _malloc(100);
	a0010e1d8 = _malloc(40);
	_free(a0010e168);
	_free(a0010e1d8);
	_free(a0010e118);
	_free(a0010ddf8);
	a0010e118 = _malloc(40);
	_free(a0010e118);
	a0010e118 = _malloc(40);
	_free(a0010e118);
	_free(a0010e0d0);
	a0010e118 = _malloc(40);
	_free(a0010e118);
	_free(a0010ddf8);
	a0010e118 = _malloc(40);
	return cnt;
}

#ifdef CFG_BUDDY

#include <hcos/bm.h>

static bm_t *bm;

static inline void *__malloc2(unsigned sz, int line)
{
	void *p = _bm_alloc(sz, bm);
	if (!p) {
		printf("line: %d\n", line);
		while (1) ;
	}
	cnt++;
	return p;
}

#define _malloc2(_sz)	__malloc2(_sz, __LINE__)

static inline void _free2(void *p)
{
	cnt++;
	_bm_free(bm, p);
}

int bench_mm2(void)
{
	unsigned bo = 5;
	unsigned mo = 16;
	bm = _alloc(_bm_sz(bo, mo));
	_bm_init(bm, (void *)BASE_TCM, bo, mo);

	cnt = 0;
	a00100008 = _malloc2(68);
	a00100058 = _malloc2(68);
	a001000a8 = _malloc2(775);
	a001003b8 = _malloc2(40);
	a001003e8 = _malloc2(100);
	a00100458 = _malloc2(68);
	a001004a8 = _malloc2(2055);
	a00100cb8 = _malloc2(292);
	a00100de8 = _malloc2(68);
	a00100e38 = _malloc2(16384);
	a00104e48 = _malloc2(2468);
	a001057f8 = _malloc2(40);
	a00105828 = _malloc2(292);
	a00105958 = _malloc2(68);
	a001059a8 = _malloc2(4103);
	a001069b8 = _malloc2(68);
	a00106a08 = _malloc2(14583);
	a0010ca18 = _malloc2(68);
	a0010ca68 = _malloc2(2055);
	a0010d278 = _malloc2(12);
	a0010d290 = _malloc2(12);
	a0010d2a8 = _malloc2(12);
	a0010d2c0 = _malloc2(40);
	a0010d2f0 = _malloc2(40);
	a0010d320 = _malloc2(2);
	a0010d330 = _malloc2(40);
	_free2(a0010d330);
	a0010d408 = _malloc2(100);
	a0010d478 = _malloc2(40);
	a0010d738 = _malloc2(7);
	a0010dd40 = _malloc2(7);
	_free2(a0010d4a8);
	a0010d4a8 = _malloc2(8);
	a0010e0f8 = _malloc2(8);
	a0010e108 = _malloc2(8);
	a0010e118 = _malloc2(40);
	a0010e148 = _malloc2(40);
	_free2(a0010e148);
	_free2(a0010d998);
	_free2(a0010d9c8);
	_free2(a0010d890);
	_free2(a0010dd40);
	_free2(a0010da50);
	_free2(a0010d748);
	_free2(a0010e118);
	_free2(a0010e0a8);
	a0010da28 = _malloc2(46);
	a0010e118 = _malloc2(47);
	a0010e150 = _malloc2(40);
	_free2(a0010e150);
	_free2(a0010da28);
	a0010e118 = _malloc2(40);
	_free2(a0010da28);
	_free2(a0010e148);
	_free2(a0010e278);
	_free2(a0010e368);
	_free2(a0010e4a8);
	_free2(a0010da38);
	_free2(a0010da28);
	a0010da28 = _malloc2(28);
	a0010e0a8 = _malloc2(26);
	a0010e148 = _malloc2(22);
	a0010dd40 = _malloc2(2);
	a0010e168 = _malloc2(40);
	_free2(a0010dd40);
	_free2(a0010e168);
	a0010dd40 = _malloc2(3);
	a0010e168 = _malloc2(40);
	_free2(a0010dd40);
	_free2(a0010e168);
	a0010dd40 = _malloc2(3);
	a0010e168 = _malloc2(40);
	_free2(a0010dd40);
	_free2(a0010e168);
	a0010e168 = _malloc2(35);
	a0010e198 = _malloc2(40);
	_free2(a0010e168);
	_free2(a0010e198);
	_free2(a0010e118);
	_free2(a0010ddf8);
	a0010e118 = _malloc2(40);
	a0010e190 = _malloc2(40);
	_free2(a0010e190);
	a0010dd40 = _malloc2(2);
	a0010e190 = _malloc2(40);
	_free2(a0010dd40);
	_free2(a0010e190);
	_free2(a0010e168);
	_free2(a0010e118);
	_free2(a0010e168);
	a0010e168 = _malloc2(121);
	a0010dd40 = _malloc2(2);
	a0010e1f0 = _malloc2(40);
	_free2(a0010dd40);
	_free2(a0010e1f0);
	a0010e1f0 = _malloc2(121);
	a0010e278 = _malloc2(135);
	_free2(a0010e278);
	_free2(a0010e1f0);
	_free2(a0010e168);
	a0010e168 = _malloc2(40);
	_free2(a0010e168);
	a0010e168 = _malloc2(179);
	a0010e228 = _malloc2(72);
	a0010e278 = _malloc2(176);
	_free2(a0010e278);
	_free2(a0010e228);
	a0010e228 = _malloc2(99);
	a0010e298 = _malloc2(113);
	_free2(a0010e298);
	_free2(a0010e228);
	a0010e228 = _malloc2(65);
	a0010e278 = _malloc2(40);
	_free2(a0010e228);
	_free2(a0010e278);
	a0010e228 = _malloc2(65);
	a0010e278 = _malloc2(40);
	_free2(a0010e228);
	_free2(a0010e278);
	a0010e228 = _malloc2(65);
	a0010e278 = _malloc2(40);
	_free2(a0010e228);
	_free2(a0010e278);
	_free2(a0010e118);
	a0010e118 = _malloc2(40);
	_free2(a0010e118);
	_free2(a0010e168);
	a0010e168 = _malloc2(40);
	a0010e198 = _malloc2(40);
	_free2(a0010e168);
	_free2(a0010e118);
	a0010e118 = _malloc2(40);
	_free2(a0010e198);
	a0010e168 = _malloc2(100);
	a0010e1d8 = _malloc2(40);
	_free2(a0010e168);
	_free2(a0010e1d8);
	_free2(a0010e118);
	_free2(a0010ddf8);
	a0010e118 = _malloc2(40);
	_free2(a0010e118);
	a0010e118 = _malloc2(40);
	_free2(a0010e118);
	_free2(a0010e0d0);
	a0010e118 = _malloc2(40);
	_free2(a0010e118);
	_free2(a0010ddf8);
	a0010e118 = _malloc2(40);
	return cnt;
}
#endif
