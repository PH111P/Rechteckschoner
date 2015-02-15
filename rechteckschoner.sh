#!/bin/sh

# Use the script in this file to bring life to your desktop!

/home/philip/Projects/Rechteckschoner/generate_cmds
/home/philip/Projects/Rechteckschoner/rechteckschoner -c 4 -q /home/philip/Projects/Rechteckschoner/.config -o /home/philip/Projects/Rechteckschoner/ -i			#init call, generate .tmp
feh  --bg-scale '/home/philip/Projects/Rechteckschoner/rechteckschoner.png'

while true; do
    /home/philip/Projects/Rechteckschoner/generate_cmds
	#sleep 2s
	/home/philip/Projects/Rechteckschoner/rechteckschoner -c 4 -q /home/philip/Projects/Rechteckschoner/.config -r -t /home/philip/Projects/Rechteckschoner/.tmp -o  /home/philip/Projects/Rechteckschoner/	#use generated tmp and change only parts
	feh  --bg-scale '/home/philip/Projects/Rechteckschoner/rechteckschoner.png'
	
	sleep 30s
	/home/philip/Projects/Rechteckschoner/rechteckschoner -c 4 -q /home/philip/Projects/Rechteckschoner/.config -i -t /home/philip/Projects/Rechteckschoner/.tmp -o /home/philip/Projects/Rechteckschoner/	
	feh  --bg-scale '/home/philip/Projects/Rechteckschoner/rechteckschoner.png'
done
