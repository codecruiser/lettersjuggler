/**
 * Letters Juggler 
 *  
 * Version: 0.1 (pre-Alpha version)
 * 
 * Content: KeyboardDweller class methods 
 * 
 * Description: Listens to keyboard input
 * 
 * Author: Zbigniew Szczepanski
 * 
 * TODO: there is a lot of issues which need to be addressed here
 * 			and I am aware of
 */
#include "keyboard_dweller.h"

/**
 * Constructor.
 */
KeyboardDweller::KeyboardDweller()
{
	display = XOpenDisplay(0);
}

/**
 * Returns true if given key is pressed
 */
bool KeyboardDweller::checkKeyPressed(const char* map, unsigned short key)
{
	/**
	 * Checks key number against key map
	 */
    return (map[key / 8] & (1 << (key % 8))) != 0;
}

/**
 * Loop task  checking for keys
 */
bool KeyboardDweller::checkForKeys()
{
    char keymap[32];    
    unsigned int microseconds = 100000;
    bool pressed = false;
    
    XQueryKeymap(display, keymap);
    
    keys.clear();
    
    for(unsigned short keyp = 0; keyp < 256; keyp++)
    {
		bool isPressed = checkKeyPressed(keymap, keyp);
		
        if (isPressed)
        {
			cout << keyp;
			
			keys.insert(keyp);
			
			pressed = true;
		}
    }
    
    if(pressed == true)
    {
		cout << endl;
		checkActionAssoc();
	}
    
	usleep(microseconds);
	
    return true;
}

/**
 * Keaboard listener init. Loop to check keys.
 */
void KeyboardDweller::init()
{	
	while(1) {
		checkForKeys();
	}
}

/**
 * Checks if particular keys were pressed
 * and sends signal 
 */
void KeyboardDweller::checkActionAssoc()
{
	if((keys.find(32) != keys.end()) 
		&& (keys.find(50) != keys.end()) 
		&& (keys.find(108) != keys.end()))
	{
		//cout << "HURAAAAA!!!" << endl;
		pipeWrite();
	}
}

/**
 * Sets pipe ends
 */
bool KeyboardDweller::setPipeEnds(int rend, int wend)
{
	read_pend = rend;
	write_pend = wend;
	
	//close(read_pend);
	
	return true;
}

/**
 * Writes a signal to window
 */
bool KeyboardDweller::pipeWrite()
{
	//fprintf(spw, "hello GTK!\n");
	//printf("Write KBD!");
	write(write_pend, "AAAAA", 5);
	//printf("Written!");
	return true;
}

/**
 * Reads feedback from window.
 */
bool KeyboardDweller::pipeRead()
{
	char str[80];
	int a;
	do {
		a = read(read_pend, str, 80);
	} while(a < 1);
	
	printf("READ KBD! %s:", str);
	return true;
}

/**
 * Destructor. Cleans before exit.
 */
KeyboardDweller::~KeyboardDweller()
{
	keys.clear();
	close(read_pend);
	close(write_pend);
}

