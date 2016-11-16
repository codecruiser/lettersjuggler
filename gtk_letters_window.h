/**
 * Letters Juggler 
 *  
 * Version: 0.1 (pre-Alpha version)
 * 
 * Content: LjGtkLettersWindow class header 
 * 
 * Description: displays GTK window with letters to be chosen
 * 
 * Author: Zbigniew Szczepanski
 * 
 * TODO: there is a lot of issues which need to be addressed here
 * 			and I am aware of
 */
#ifndef LJ_GTK_LETTERS_WINDOW_H
#define LJ_GTK_LETTERS_WINDOW_H
#include <iostream>
#include <thread> 
#include <gtk/gtk.h>

#include "lj_thread_communication.h"

class LjGtkLettersWindow: public LjThreadCommunication
{
	FILE *spr;
	FILE *spw;
	GtkWidget *window;
	GtkWidget *menu;
	GtkWidget *menu_bar;
	GtkWidget *root_menu;
	GtkWidget *menu_items;
	GtkWidget *vbox;
	GtkWidget *button;
	char lastread;
		
	public:
		LjGtkLettersWindow(int , char **);
		~LjGtkLettersWindow();
		GtkWidget *getMainWindow();
		void init();
		static void destroy(GtkWidget *widget, gpointer data);
		bool setPipeEnds(int, int);
		bool pipeWrite(char);
		bool pipeRead();
		static void startRead(LjGtkLettersWindow*);
	
	void showWin();
	void hideWin(GtkButton* button, gpointer func_data);
};

#endif
