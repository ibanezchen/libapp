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
#ifdef _EXE_

#include "main.h"
#include "plt.h"

SCANF_FLOAT;

PRINTF_FLOAT;

int iperf_main(int argc, char **argv);

///> go 0 -c <ip> -p 2501 -l 8k
int main(int argc, char **argv)
{
	core_init();
	main_new(argc, argv,
		 WIFI_WPA_PSK_WPA2_PSK, xstr(WIFI_SSID), xstr(WIFI_PASSWD),
		 0, 0, iperf_main);
	core_start();
	return 0;
}
#endif
