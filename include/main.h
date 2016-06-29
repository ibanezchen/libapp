#ifndef MAIN0620
#define MAIN0620

#include "plt-wifi.h"

#define xstr(s) str(s)

#define str(s) #s

typedef int (*main_f) (int argc, char **argv);

/// \param netcfg 0 for dhcp, or netcfg[0]=ip, netcfg[1]=mask, netcfg[2]=gateway,
///	all in ascii.
typedef struct {
	int argc;
	char **argv;
	wifi_auth_t auth;
	char *ssid;
	char *passwd;
	char **mac;
	char **netcfg;
	main_f mf;
} main_t;

main_t *main_new(int argc, char **argv,
		 wifi_auth_t auth,
		 char *wifi_ssid,
		 char *wifi_passwd, char **mac, char **netcfg, main_f f);

#endif
