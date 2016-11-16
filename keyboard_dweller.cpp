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
	letters = {
		{24, 'q'},	{25, 'w'},	{26, 'e'},	{27, 'r'},	{28, 't'},
		{29, 'y'},	{30, 'u'},	{31, 'i'},	{32, 'o'},	{33, 'p'},
		{38, 'a'},	{39, 's'},	{40, 'd'},	{41, 'f'},	{42, 'g'},	
		{43, 'h'},	{44, 'j'},	{45, 'k'},	{46, 'l'},	
		{52, 'z'},	{53, 'x'},	{54, 'c'},	{55, 'v'},	{56, 'b'},	
		{57, 'n'},	{58, 'm'}
		};
	
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
			keys.insert(keyp);
			
			pressed = true;
		}
    }
    
    if(pressed == true)
    {
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
	bool shiftkey = false;
	
	//shoft pressed, uppercase
	if(keys.count(50) != 0)
		shiftkey = true;
		
	if(((shiftkey && keys.size() > 2)
		|| (!shiftkey && keys.size() > 1))
		&& keys.count(108) != 0)
	{
		for(unsigned short i = 24; i < 59; 
				i++, (i == 34)? i = 38 : ((i == 47)?i = 52:i=i))
		{
			if(keys.count(i) != 0 && letters[i] > 0)
			{
				if(shiftkey)
					cout << i << ":shift+" << letters[i] << endl;
				else
					cout << i << ":" << letters[i] << endl;
				
				pipeWrite(letters.at(i), shiftkey);
			}
		}
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
bool KeyboardDweller::pipeWrite(char letter, bool shiftkey)
{
	if(shiftkey)
		write(write_pend, strcat(&letter, "+"), 2);
	else
		write(write_pend, &letter, 1);
	
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

