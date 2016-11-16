/**
 * Letters Juggler 
 *  
 * Version: 0.1 (pre-Alpha version)
 * 
 * Description: The programm is a keyboard listener which main task is 
 * 				to handle a multinational characters while writing 
 * 				multilanguage documents.
 * 				In this version it is intended to display window with 
 * 				national chars to be chosen depending on keyboard input.
 * 				At the same time both window with national characters
 * 				and keyboard input listener part need to be independent.
 * 				
 * 
 * Author: Zbigniew Szczepanski
 * 
 * TODO: there is a lot of issues which need to be addressed here
 * 			and I am aware of them
 */
 
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

#include "keyboard_dweller.h"
#include "gtk_letters_window.h"
 
using namespace std;

void daemonization(bool stdouts)
{
	pid_t sid;
	
	umask(0);

	/**
	 * New session starts
	 */
	sid = setsid();

	if(sid < 0)
	{
		cerr << "Couldn't start new session" << endl;
		exit(EXIT_FAILURE);
	}

	chdir("/");

	//no to the standard communication
	if(!stdouts)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
}

/**
 * Keyboard deamon to check for keys 
 */
void keyboardDeamon(int& pipe_rend, int& pipe_wend)
{	
	daemonization(true);
		
	KeyboardDweller *kd = new KeyboardDweller;
	
	kd->setPipeEnds(pipe_rend, pipe_wend);
		
	//kd->pipeWrite();
	//kd->pipeRead();
	
	kd->init();
	
	cout << "Keyboard dweller started!" << endl;
}

/**
 * GTK Window deamon to display window when necessery
 */
void windowDeamon(int &argc, char **&argv, int& pipe_rend, int& pipe_wend)
{
	daemonization(true);
	
	LjGtkLettersWindow *lglw = new LjGtkLettersWindow(argc, argv);
	
	lglw->setPipeEnds(pipe_rend, pipe_wend);
	
	//lglw->pipeWrite();
	//lglw->pipeRead();
	
	cout << "Trying to init!" << endl;
	
	lglw->init();
	
	cout << "GTK Window started!" << endl;
}

/**
 * Starts the programm and forks for daemons
 */
int main(int argc, char **argv)
{	
	pid_t fid, fid_kbd, fid_gtk;
	int pipe_sid_holder[2];
	
	pipe(pipe_sid_holder);
	
	//first fork
	fid_kbd = fork();
	
	if(fid_kbd < 0)
	{
		cerr << "Couldn't fork proccess" << endl;
		exit(EXIT_FAILURE);
	}
		
	if(fid_kbd > 0)
	{
		fid_gtk = fork();
		
		if(fid_gtk < 0)
		{
			cerr << "Couldn't fork proccess" << endl;
			exit(EXIT_FAILURE);
		}
		
		if(fid_gtk == 0)
		{
			cout << "Keyboard forked!" << endl;
			
			keyboardDeamon(pipe_sid_holder[0], pipe_sid_holder[1]);
		}
		else
		{			
			cout << "All done!" << endl;
		}
	} 
	else
	{
		cout << "GTK Window forked!" << endl;
		
		windowDeamon(argc, argv, pipe_sid_holder[0], pipe_sid_holder[1]);
	}
		
	return 0;
}
