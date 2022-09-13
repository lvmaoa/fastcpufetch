#define _POSIX_C_SOURCE 200809L

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sched.h>
#include <pthread.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <sys/utsname.h>

#include "color.h"

char *username, *osname, *shellname, *de, *kver, *arg;
long utH, utM;
int sys;

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
	utH = (t % 86400) / 3600;
	utM = (t % 3600) / 60;
	return NULL;
}

void *cpu() {
	FILE *cpu = fopen("/proc/cpuinfo", "rb");
    char ch;
    int w = 0;
    arg = malloc(100 * sizeof(char));
    for (int i = 0; i < 16; ++i)
    {
        if (fscanf(cpu, "%s", arg)) {

        } else {
            printf("Cannot read");
        }
        if (i == 15)
        {
            ch = getc(cpu);
            while (ch != '\n')
            {
                arg[w] = ch;
                ch = getc(cpu);
                ++w;
                if (ch == 'M') {
                    sys = 1;
                } else if (ch == 'I') {
                    sys = 2;
                }
            }
            break;
        }
    }
    fclose(cpu);

    return NULL;
}

void *user() {
	char hostname[HOST_NAME_MAX + 1];
	gethostname(hostname, HOST_NAME_MAX + 1);
	username = strcat(getenv("USER"), "@");
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
	pthread_t threads[7];

	pthread_create(&threads[0], NULL, user, NULL);
	pthread_create(&threads[1], NULL, os, NULL);
	pthread_create(&threads[2], NULL, cpu, NULL);
    pthread_create(&threads[3], NULL, kernel, NULL);
	pthread_create(&threads[4], NULL, uptime, NULL);
	pthread_create(&threads[5], NULL, shell, NULL);
	pthread_create(&threads[6], NULL, desktop, NULL);

	pthread_join(threads[0], NULL);

	pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);

	// Only supports amd for now
	if (sys == 1) {
		printf("%s\n", RED "   ______   __       __  _______  ");
		printf("%s    %s%s%s\n",        RED "  /      \\ |  \\     /  \\|       \\ ", "   USER ", WHITE, username);
		printf("%s    %s%s%s\n",        RED " |  $$$$$$\\| $$\\   /  $$| $$$$$$$\\", "     OS ", WHITE, osname);
		printf("%s    %s%s%s\n",        RED " | $$__| $$| $$$\\ /  $$$| $$  | $$", " KERNEL ", WHITE, kver);
		pthread_join(threads[3], NULL);
		printf("%s    %s%s%ldh %ldm\n", RED " | $$    $$| $$$$\\  $$$$| $$  | $$", " UPTIME ", WHITE, utH, utM);
		pthread_join(threads[4], NULL);
		printf("%s    %s%s%s\n",        RED " | $$$$$$$$| $$\\$$ $$ $$| $$  | $$", "  SHELL ", WHITE, shellname);
		printf("%s    %s%s%s\n",        RED " | $$  | $$| $$ \\$$$| $$| $$__/ $$", "     DE ", WHITE, de);
		printf("%s    %s%s%s\n",        RED " | $$  | $$| $$  \\$ | $$| $$    $$", "    CPU ", WHITE, &arg[1]);
		printf(RED "%s\n", "  \\$$   \\$$ \\$$      \\$$ \\$$$$$$$ \n");
    } else if (sys == 2){
		printf("%s\n", BLUE "  ______  __    __  ________  ________  __       ");
		printf("%s    %s%s%s\n",        BLUE " |      \\|  \\  |  \\|        \\|        \\|  \\      ", "   USER ", WHITE, username);
		printf("%s    %s%s%s\n",        BLUE "  \\$$$$$$| $$\\ | $$ \\$$$$$$$$| $$$$$$$$| $$      ", "     OS ", WHITE, osname);
		pthread_join(threads[2], NULL);
		printf("%s    %s%s%s\n",        BLUE "   | $$  | $$$\\| $$   | $$   | $$__    | $$      ", "  KERNEL ", WHITE, kver);
		pthread_join(threads[3], NULL);
		printf("%s    %s%s%ldh %ldm\n", BLUE "   | $$  | $$$$\\ $$   | $$   | $$  \\   | $$      ", " UPTIME ", WHITE, utH, utM);
		pthread_join(threads[4], NULL);
		printf("%s    %s%s%s\n",        BLUE "   | $$  | $$\\$$ $$   | $$   | $$$$$   | $$      ", "  SHELL ", WHITE, shellname);
		printf("%s    %s%s%s\n",        BLUE "  _| $$_ | $$ \\$$$$   | $$   | $$_____ | $$_____ ", "     DE ", WHITE, de);
		printf("%s    %s%s%s\n",        BLUE " |   $$ \\| $$  \\$$$   | $$   | $$     \\| $$     \\", "    CPU ", WHITE, &arg[1]);
		printf("%s\n", BLUE "  \\$$$$$$ \\$$   \\$$    \\$$    \\$$$$$$$$ \\$$$$$$$$\n");
	} else {
		printf("%s    %s%s%s\n",        WHITE "", "   USER ", WHITE, username);
		printf("%s    %s%s%s\n",        WHITE "", "     OS ", WHITE, osname);
		pthread_join(threads[2], NULL);
		printf("%s    %s%s%s\n",        WHITE "", "  KERNEL ", WHITE, kver);
		pthread_join(threads[3], NULL);
		printf("%s    %s%s%ldh %ldm\n", WHITE "", " UPTIME ", WHITE, utH, utM);
		pthread_join(threads[4], NULL);
		printf("%s    %s%s%s\n",        WHITE "", "  SHELL ", WHITE, shellname);
		printf("%s    %s%s%s\n",        WHITE "", "     DE ", WHITE, de);
		printf("%s    %s%s%s\n",        WHITE "", "    CPU ", WHITE, &arg[1]);
		printf("%s\n", "");
	}


    free(arg);
	pthread_join(threads[5], NULL);
	return 0;
}
