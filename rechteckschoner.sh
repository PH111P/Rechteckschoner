#!/bin/sh

# Use the script in this file to bring life to your desktop!

/home/philip/Projects/Rechteckschoner/rechteckschoner -w 1366 -h 768 -d 8 -b 3 -c 4 -e 0 -g 1 -b 2 -o /home/philip/Projects/Rechteckschoner/ -i			#init call, generate .tmp
feh  --bg-scale '/home/philip/Projects/Rechteckschoner/rechteckschoner.png'

while true; do
	sleep 2s
	/home/philip/Projects/Rechteckschoner/rechteckschoner -w 1366 -h 768 -d 8 -b 3 -c 4 -e 0 -g 1 -b 2 -r -t /home/philip/Projects/Rechteckschoner/.tmp -o  /home/philip/Projects/Rechteckschoner/	#use generated tmp and change only parts
	feh  --bg-scale '/home/philip/Projects/Rechteckschoner/rechteckschoner.png'
	
	sleep 30s
	/home/philip/Projects/Rechteckschoner/rechteckschoner -w 1366 -h 768 -d 8 -b 3 -c 4 -e 0 -g 1 -b 2 -i -t /home/philip/Projects/Rechteckschoner/.tmp -o /home/philip/Projects/Rechteckschoner/	
	feh  --bg-scale '/home/philip/Projects/Rechteckschoner/rechteckschoner.png'
done
