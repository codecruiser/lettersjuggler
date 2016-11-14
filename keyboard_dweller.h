/**
 * Letters Juggler 
 *  
 * Version: 0.1 (pre-Alpha version)
 * 
 * Content: KeyboardDweller class header 
 * 
 * Description: Listens to keyboard input
 * 
 * Author: Zbigniew Szczepanski
 * 
 * TODO: there is a lot of issues which need to be addressed here
 * 			and I am aware of
 */
 
#ifndef KEYBOARD_DWELLER_H
#define	KEYBOARD_DWELLER_H

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <set>
#include <iostream>

#include "lj_thread_communication.h"

using namespace std;

class KeyboardDweller: private LjThreadCommunication
{
	FILE *spw;
	FILE *spr;
	Display *display;
	set<int> keys;
	
	bool checkKeyPressed(const char* map, unsigned short key);
	
	public:
		KeyboardDweller();
		~KeyboardDweller();
		bool checkForKeys();
		void checkActionAssoc();
		void init();
		bool setPipeEnds(int, int);
		bool pipeWrite();
		bool pipeRead();
};

#endif
