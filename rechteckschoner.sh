#!/bin/sh

# Use the script in this file to bring life to your desktop!

/home/philip/Projects/Rechteckschoner/generate_cmds
/home/philip/Projects/Rechteckschoner/rechteckschoner -c 3 -q /home/philip/Projects/Rechteckschoner/.config -o /home/philip/Projects/Rechteckschoner/ -i 		#init call, generate .tmp
feh  --bg-scale '/home/philip/Projects/Rechteckschoner/rechteckschoner.png'

#cp /home/philip/Projects/Rechteckschoner/rechteckschoner.png `echo "/home/philip/Projects/Rechteckschoner/screens/$a.png"`

while true; do
    /home/philip/Projects/Rechteckschoner/generate_cmds
	sleep 2s
	/home/philip/Projects/Rechteckschoner/rechteckschoner -c 3 -q /home/philip/Projects/Rechteckschoner/.config -r -t /home/philip/Projects/Rechteckschoner/.tmp -o  /home/philip/Projects/Rechteckschoner/	#use generated tmp and change only parts
	feh  --bg-scale '/home/philip/Projects/Rechteckschoner/rechteckschoner.png'
    cp /home/philip/Projects/Rechteckschoner/rechteckschoner.png /home/philip/Desktop

    #cp /home/philip/Projects/Rechteckschoner/rechteckschoner.png `echo "/home/philip/Projects/Rechteckschoner/screens/$a.png"`
    sleep 58s
	/home/philip/Projects/Rechteckschoner/rechteckschoner -c 3 -q /home/philip/Projects/Rechteckschoner/.config -i -t /home/philip/Projects/Rechteckschoner/.tmp -o /home/philip/Projects/Rechteckschoner/
	feh  --bg-scale '/home/philip/Projects/Rechteckschoner/rechteckschoner.png'
    #cp /home/philip/Projects/Rechteckschoner/rechteckschoner.png `echo "/home/philip/Projects/Rechteckschoner/screens/$a.png"`
done
