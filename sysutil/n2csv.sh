#!/bin/sh 

## Copyright (c) 2017-2018, Exile Heavy Industries
## All rights reserved.
## 
## Redistribution and use in source and binary forms, with or without
## modification, are permitted (subject to the limitations in the disclaimer
## below) provided that the following conditions are met:
## 
## * Redistributions of source code must retain the above copyright notice, this
##   list of conditions and the following disclaimer.
## 
## * Redistributions in binary form must reproduce the above copyright notice,
##   this list of conditions and the following disclaimer in the documentation
##   and/or other materials provided with the distribution.
## 
## * Neither the name of the copyright holder nor the names of its contributors may be used
##   to endorse or promote products derived from this software without specific
##   prior written permission.
## 
## NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS
## LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
## "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
## THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
## ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
## LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
## CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
## GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
## HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
## LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
## OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
## DAMAGE.

## Ideally simplistic script to take a nagios host monitoring file 
## and turn it into a CSV. Currently no plans to strip out duplicates
## but who knows, might be simple enough to add in a pass to do that.

## set up some variables 
ignore_comments=true # default to stripping out comments in the process
important_regexp='(host_name|alias|address)' # regex string to determine what fields are important
indir=""
infile_extension="cfg"
outdir=""
outfile="nagios_hosts.csv"
record_separator=","
tools="awk mkdir paste rm sed touch"

## Delete the existing data in the output file ## 
clean_oldfile() {
  if [ -f ${outdir}/$outfile ]
  then
    :>${outdir}/$outfile
  fi
}

## Ensure the system even has the tools we need
depcheck() {
	echo -e "Checking system for required tools..."
	for tool in ${tools} 
	do
		if [ -x `which $tool` ] 
		then
			:
		else
			echo -e "Required utility $tool not found in \$PATH!\nBailing out..."
			exit 3
		fi
	done
	deps_good=true
}

## Ensure that the directory locations exist and 
## are usable for the user running this script
envcheck() {
	echo -e "Validating runtime arguments..."
  ## I'm sure there's a better way to check this
  ## but for the sake of getting it done quickly, 
  ## I'm using a battery of if/elif tests, should
  ## a test fail, simply call exit and print an error
  ## message for the user to fix the problem

  if [ -d "${outdir}" ]
  then
    touch "${outdir}/test" 
    if [ $? -eq 0 ]
    then
      rm -xPf "${outdir}/test"
    else 
      echo -e "Cannot write to ${outdir}!"
      exit 3 
    fi
  else
    mkdir -pm 770 "${outdir}"
    if [ $? -ne 0 ]
    then
      echo -e "Cannot create ${outdir}"
      exit 3
    fi
  fi
  if [ -d "${indir}" ] 
  then
    :
  else
    echo -e "${indir} does not exist!"
    exit 3
  fi

  env_good=true
}

## Start converting files
nagios_convert() {
  for conffile in ${indir}/*.${infile_extension}
  do
      echo -e "Reading $conffile"
      echo -e "--------------------------------------------------\n$conffile\n--------------------------------------------------" >> ${outdir}/${outfile}
      if [ ignore_comments ]
      then
        sed -i.bak -u -e '/#/d' $conffile
      fi
        awk "/${important_regexp}/ {print \$2\"${record_separator}\"}" $conffile | paste - - - >> ${outdir}/${outfile}
  done
}

## Modify the regexp depending on if -c is used
remove_comments() {
  ## It should be possible to do this in a better manner
  ## but I don't have time to debug alternative means right now
  regexpbase='([^#])'
  new_regexp="$regexpbase${important_regexp}"
  important_regexp="${new_regexp}"
}

run_help() {
	echo -e "Tool to convert nagios configuration files into a CSV format"
  echo -e "\t-c\tInclude commented out lines"
  echo -e "\t-C\tClean (erase) the old output file, if it exists"
  echo -e "\t-d\tOutput directory"
  echo -e "\t-e\tExtension for the input files"
  echo -e "\t-f\tOutput file"
  echo -e "\t-h\tThis help"
  echo -e "\t-i\tInput directory"
  echo -e "\t-r\tRegular expression to get the important fields (Default: ${important_regexp})\n\t\tUses the awk regex engine"
  echo -e "\t-s\tRecord separator for the output file"
}

### MAIN() ###
while getopts ":cCd:e:f:hi:o:r:s:" opt
do
	case $opt in 
		c)
			ignore_comments=false
			;;
    C)
      clean_oldfile
      ;;
		d)
			outdir="${OPTARG}"
			;;
		e)
			infile_extension="${OPTARG}"
			;;
		f)
			outfile="${OPTARG}"
			;;
		h)
			run_help
			exit 0
			;;
		i)
			indir="${OPTARG}"
			;;
		r)
			important_regexp="${OPTARG}"
			;;
		s)
			record_separator="${OPTARG}"
			;;
		\?)
			run_help
			exit 0
			;;
	esac
done

depcheck
if [ deps_good ]
then
  envcheck
  if [ env_good ]
  then
    nagios_convert
  fi
fi
