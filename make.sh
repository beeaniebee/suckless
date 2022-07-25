#!/bin/bash

if [ $EUID -ne 0 ]; then
	echo "This script must be run as root"
	exit
fi

case $1 in 
	"build")
		action="build"
		;;
	"")
		echo Assuming action "build"
	       	action="build"
		;;
	"install")
		action="install"
		;;
	*)
		echo 'Please pass either "build" or "install"'
		exit
		;;
	
esac

programs=("dwm" "st" "dwmblocks" "slock")

for program in ${programs[@]}
do
	pushd "$program" >/dev/null
	if [[ $action == "build" || $action == "install" ]]; then
		echo "Building $program"
		make clean >/dev/null
		make >/dev/null
	fi
	if [[ $action == "install" ]]; then
		echo "Installing $program"
		make install >/dev/null
	fi
	popd >/dev/null
done
