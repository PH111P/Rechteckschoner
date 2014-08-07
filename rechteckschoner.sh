#!/bin/sh

# Use the script in this file to bring life to your desktop!

/home/philip/Projects/Rechteckschoner/rechteckschoner -w 1366 -h 768 -d 12 -b 3 -c 3 -o /home/philip/Projects/Rechteckschoner/ -i			#init call, generate .tmp
feh  --bg-scale '/home/philip/Projects/Rechteckschoner/rechteckschoner.png'

while true; do
	sleep 2s
	/home/philip/Projects/Rechteckschoner/rechteckschoner -w 1366 -h 768 -d 12 -b 3 -c 3 -r -t /home/philip/Projects/Rechteckschoner/.tmp -o  /home/philip/Projects/Rechteckschoner/	#use generated tmp and change only parts
	feh  --bg-scale '/home/philip/Projects/Rechteckschoner/rechteckschoner.png'
	
	sleep 30s
	/home/philip/Projects/Rechteckschoner/rechteckschoner -w 1366 -h 768 -d 12 -b 3 -c 3 -i -t /home/philip/Projects/Rechteckschoner/.tmp -o /home/philip/Projects/Rechteckschoner/	
	feh  --bg-scale '/home/philip/Projects/Rechteckschoner/rechteckschoner.png'
done
