#!/bin/sh

# This is a version for cron

./rechteckschoner -w 1366 -h 768 -d 12 -b 3 -c 3 -t .tmp -o ./ 	#use generated tmp and change only parts
feh  --bg-scale './rechteckschoner.png' 