#!/bin/sh

## This is just to document how long builds took with a given number of jobs provided.
## It will also dump /etc/make.conf to display the settings being used, which may impact build times.
## This script was created on DragonFly BSD 4.8.1, other BSDs should be similar, but Linux will need an entirely different script.

## The script defaults to using ncpu
if [ -x /sbin/sysctl ]
then 
	buildjobs=$(sysctl -n hw.ncpu)
else 
	buildjobs=1
fi
logfile="sysbuild.log"
upload=0

run(){
	## actually do everything
	test_logfile
	echo -e "System build starting..\t$(date +%Y%m%d\ %H%M)" | tee -a ${logfile}
	echo -e "Buildworld starting..\t$(date +%Y%m%d\ %H%M)" | tee -a ${logfile}
	make -j ${buildjobs} buildworld -C /usr/src
	echo -e "Buildworld completed..\t$(date +%Y%m%d\ %H%M)" | tee -a ${logfile}
	echo -e "Buildkernel starting..\t$(date +%Y%m%d\ %H%M)" | tee -a ${logfile}
	make -j ${buildjobs} buildkernel -C /usr/src
	echo -e "Buildkernel completed..\t$(date +%Y%m%d\ %H%M)" | tee -a ${logfile}
	echo -e "Installkernel starting..\t$(date +%Y%m%d\ %H%M)" | tee -a ${logfile}
	make installkernel -C /usr/src
	echo -e "Installkernel completed..\t$(date +%Y%m%d\ %H%M)" | tee -a ${logfile}
	echo -e "Installworld starting..\t$(date +%Y%m%d\ %H%M)" | tee -a ${logfile}
	make installworld -C /usr/src
	echo -e "Installworld completed..\t$(date +%Y%m%d\ %H%M)" | tee -a ${logfile}

	## Special step on DragonFly to help prevent system breakage
	if [ `uname -s` = "DragonFly" ]
	then
		echo -e "Upgrade running..\t$(date +%Y%m%d\ %H%M)" | tee -a ${logfile}
		make upgrade  -C /usr/src
		echo -e "Upgrade completed..\t$(date +%Y%m%d\ %H%M)" | tee -a ${logfile}
	fi
	echo -e "System build completed!\t$(date +%Y%m%d\ %H%M)" | tee -a ${logfile}

	if [ $upload -ne 0 ]
	then 
		upload
	fi
	exit 0
}


test_logfile(){
	## verify that we can actually write to the given directory 
	touch ${logfile}; 
	if [ $? -ne 0 ] 
	then
		echo -e "ERR: can't write to ${logfile}"
		exit 2
	else 
		:>${logfile}
		cat /etc/make.conf >> ${logfile}
		echo -e "\t\t==================================================\t\t" >> ${logfile}
		echo -e "\t\t\tUSING\t\"-j${buildjobs}\" TO BUILD"
		echo -e "\t\t==================================================\t\t" >> ${logfile}
	fi
}

usage(){
	## Help information
	echo -e "sysbuild.sh: record times for system builds"
	echo -e "\t-h\tThis message"
	echo -e "\t-j\tBuild jobs passed to make, defaults to the number of cpus (current setting: ${buildjobs})"
	echo -e "\t-f\tSet custom logfile, defaults to ${logfile}"
	echo -e "\t-u\tUpload resulting file to ix.io (requires curl)"
	exit 0
}

upload(){
	## Upload the resulting file contents to ix.io for easy sharing
	cat ${logfile} | curl -F 'f:1=<-' ix.io
}

while getopts ":h?j:f:u:" opt;
do 
	case $opt in
		h)
			usage;
		;;
		j)
			buildjobs="$OPTARG"
		;;
		f)
			logfile="$OPTARG"
		;;
		u)
			upload=1;
		;;
		\?)
			usage;
		;;
	esac
done

## now run the thing
run
