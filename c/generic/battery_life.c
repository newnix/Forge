/* 
 * This program should only pull the battery life information from the sysctl interface
 * And return human-readable inforamation, with the end goal of being integrated into my dwmstatus patches
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sysctl.h>

/* 
 * Simple sysctl call examples:
 * int sysctl(const int *name, u_int namelen, void *oldp, size_t *oldlenp, const voice newp, size_t newlen);
 *
 * int sysctlbyname(const char *name, void *oldp, size_t *oldlenp, const void *newp, size_t newlen);
 *
 * int sysctlnametomib(const char *name, int *mibp, size_t *sizep);
 */

void
print_battery(void);

int
main(void){
	/* This is where the magic happens */
	(void)fprintf(stdout,"Attempting to grab data from `sysctl hw.acpi.battery.life`...\n");
	print_battery();
	return 0;
}

void
print_battery(void){
	/* pass the required data to the sysctl interface and create a string to print */

	/* using syntax similar from the sysctl man page */
	int mib[5], value;
	size_t len;

	/* this should get the mib we want to make the sumsequent calls even faster */
	len = 5;
	if ( sysctlnametomib("hw.acpi.battery.time", mib, &len) == -1 ) 
		perror("sysctl");

	if (sysctl(mib, len, &value, &len, NULL, 0) == -1) {
		perror("sysctl");
		(void)fprintf(stderr,"ERROR: could not retrieve data for OID \"hw.acpi.battery_life\"\n");
	}
	else if (len > 0) {
		(void)fprintf(stdout,"hw.acpi.battery.life = %d\n", value);
	}
}
