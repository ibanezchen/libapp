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
#define _DBG 1
#define HC	1
#include <hcos/dbg.h>
#include <hcos/task.h>
#include <hcos/soc.h>
#include <lwip/netif.h>
#include <lwip/tcpip.h>
#include <lwip/sockets.h>
#include <lwip/netdb.h>

#include "term.h"
#include "plt.h"
#include "plt-wifi.h"
#include "main.h"

#include <string.h>

static void main_thread(void *p)
{
	main_t *m = (main_t *) p;
	int i;
	int argc = m->argc;
	char **argv = m->argv;
	char *ssid = m->ssid;
	char *pass = m->passwd;
	plt_init();
	if (m->mac)
		net_init(m->mac[0], m->mac[1], 0);
	else
		net_init(0);
	dbg("wifi=%s %s\r\n", ssid, pass);
	wifi_init(m->auth, ssid, pass);
	if (!m->netcfg)
		ip_dhcp();
	else
		ip_static(m->netcfg[0], m->netcfg[1], m->netcfg[1],
			  m->netcfg[2]);
	for (i = 0; i < argc; i++)
		dbg("argv[%d] = %s\r\n", i, argv[i]);
	i = m->mf(argc, argv);
	dbg("exit %d\n", i);
}

main_t *main_new(int argc, char **argv,
		 wifi_auth_t auth,
		 char *wifi_ssid,
		 char *wifi_passwd, char **mac, char **netcfg, main_f mf)
{
	main_t *m = core_alloc(sizeof(main_t), 2);
	m->argc = argc;
	m->argv = argv;
	m->auth = auth;
	m->ssid = wifi_ssid;
	m->passwd = wifi_passwd;
	m->mac = mac;
	m->netcfg = netcfg;
	m->mf = mf;
	task_new("main", main_thread, 8, 4096, -1, m);
	return m;
}
