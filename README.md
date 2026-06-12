# SvT
A simple news reading application for SVT news which can be launched in the terminal.
#DEMO 
<video src="SvT/demo.mp4" width="320" height="240" controls></video>
# KOMPILERING
Man måste ha ncurses, libcurl och cjson installerat för att kunna kompilera

gcc application.c getpage.c -o texttv -lncurses -lcurl -lcjson
todo lägg till en make file
