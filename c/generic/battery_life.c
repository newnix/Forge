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

void
man3_example(void);

int
main(void){
	/* This is where the magic happens */
	print_battery();
	/* (void)fprintf(stdout,"running example code from `man 3 sysctl` \n"); */
	return 0;
}

void
print_battery(void){
	/* pass the required data to the sysctl interface and create a string to print */
/*	const char *battery_life = "hw.acpi.battery.time";
	const char *battery_pct = "hw.acpi.battery.life";
	int mib[4];
	size_t batt_min, batt_pct;
	sysctlnametomib(battery_life, min_remaining_mib, &batt_min);
	sysctlnametomib(battery_pct, pctl_remaining_mib, &batt_pct);
*/

	/* using syntax similar from the sysctl man page */
	unsigned long int i, mib[4], value, mib2;
	size_t len, len2;

	/* this should get the mib we want to make the sumsequent calls even faster */
	len = 4;
	if ( sysctlnametomib("hw.acpi.battery.life", mib2, &len) == -1 ) 
		perror("sysctl");
	(void)fprintf(stdout,"sysctlnametomib(\"hw.acpi.battery.life\", mib, &len) returned the following data\n&len = %lu\n",len);
	/*for (i = 0; i < 4; i++) {
		(void)fprintf(stdout,"mib[%d] = %lu\n",i,mib[i]);
	}*/
	if (sysctl(mib2, &len, NULL, &len, NULL, 0) == -1) {
		perror("sysctl");
		(void)fprintf(stderr,"ERROR: could not retrieve data for OID \"hw.acpi.battery_life\"\n");
	}
	else if (len > 0) {
		(void)fprintf(stdout,"hw.acpi.battery.life = %lu\n", value);
	}

	/* attempt to get the information through sysctlbyname() instead */
	mib2 = 0;
	len2 = 0;
	if (sysctlbyname("hw.acpi.battery.life",NULL, NULL, mib2, &len2) == 0){
		(void)fprintf(stdout,"sysctlbyname returned the following:\nmib2 = %lu\nlen2 = %lu\n",mib2,len2);
	}
	else {
		perror("sysctl");
		(void)fprintf(stderr,"could not get the data requested, dumping values...\n");
		(void)fprintf(stderr,"mib2 = %lu\nlen2 = %lu\n", mib2,len2);
	}
}

void
man3_example(void) {
	/* 
	 * this is the example taken from the sysctl page in manual section 3 
	 * I'm using it to help understand the use of the sysctl interface, since
	 * the function print_battery() above seems to be using data that's not usable
	 */
	int i, mib[4];
	size_t len;
	struct kinfo_proc *kp;

	/* filling out the first three components of the mib */
	len = 4;
	sysctlnametomib("kern.proc.pid",mib,&len);

	/* fetch and print entries for pids < 100 */
	for (i = 0; i < 100; i++) { 
		mib[3] = 1;
		len = sizeof(kp);
		if (sysctl(mib, 4, &kp, &len, NULL, 0) == -1)
			perror("sysctl");
		else if (len > 0) 
			/* printkproc(&kp); */
			(void)fprintf(stdout,"Captured %d, %s, %lu", mib, &kp, &len);
	}
}
