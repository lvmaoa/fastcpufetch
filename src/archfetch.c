#define _POSIX_C_SOURCE 200809L

#include "color.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>

char *username, *osname, *shellname, *de, *kver;
long utH, utM;

void *kernel() {
	static struct utsname uName;
	uname(&uName);
	kver = uName.release;
	return NULL;
}

void *uptime() {
	struct sysinfo sInfo;
	sysinfo(&sInfo);
	int t = sInfo.uptime;
	utH = (t % 86400)/3600;
	utM =  (t % 3600)/60;
	return NULL;
}

void *user() {
	char hostname[HOST_NAME_MAX + 1];
	gethostname(hostname, HOST_NAME_MAX + 1);
	username = strcat(getenv("USER"),"@");
	username = strcat(username, hostname);
	return NULL;
}

void *shell() {
	shellname = getenv("SHELL");
	return NULL;
}

void *desktop() {
	de = getenv("DESKTOP_SESSION");
	return NULL;
}

void *os() {
	static struct utsname uName;
	uname(&uName);
	osname = uName.nodename;
	osname[0] = osname[0] - 32;
	return NULL;
}

int main() {
	struct utsname sysInfo;
	uname(&sysInfo);
	pthread_t threads[6];

	pthread_create(&threads[0], NULL, user, NULL);
	pthread_create(&threads[1], NULL, os, NULL);
	pthread_create(&threads[2], NULL, kernel, NULL);
	pthread_create(&threads[3], NULL, uptime, NULL);
	pthread_create(&threads[4], NULL, shell, NULL);
	pthread_create(&threads[5], NULL, desktop, NULL);

	pthread_join(threads[0], NULL);
	/* os function must be run to get info.col1 */
	pthread_join(threads[1], NULL);
	printf("%s\n","");
	printf("%s    %s%s%s\n", BLUE "      /\\      ", "   USER ", WHITE, username);
	printf("%s    %s%s%s\n", BLUE "     /  \\     ", "     OS ", WHITE, osname);
	pthread_join(threads[2], NULL);
	printf("%s    %s%s%s\n", BLUE "    /\\   \\   ", "  KERNEL ", WHITE, kver);
	pthread_join(threads[3], NULL);
	printf("%s    %s%s%ldh %ldm\n", BLUE "   /      \\   ", " UPTIME ", WHITE, utH,utM);
	pthread_join(threads[4], NULL);
	printf("%s    %s%s%s\n", BLUE "  /   ,,   \\  ", "  SHELL ", WHITE, shellname);
	printf("%s    %s%s%s\n", BLUE " /   |  |  -\\ ", "     DE ", WHITE, de);
	printf("%s    %s%s%s\n", BLUE "/_-''    ''-_\\", "   PKGS ", WHITE, "Not Supported");
	printf("%s\n", "");

	pthread_join(threads[5], NULL);
	//int r=system("cat /etc/os-release");
	return 0;
}
