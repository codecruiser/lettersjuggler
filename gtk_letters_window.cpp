/**
 * Letters Juggler 
 *  
 * Version: 0.1 (pre-Alpha version)
 * 
 * Content: LjGtkLettersWindow class methods 
 * 
 * Description: displays GTK window with letters to be chosen
 * 
 * Author: Zbigniew Szczepanski
 * 
 * TODO: there is a lot of issues which need to be addressed here
 * 			and I am aware of
 */
 
#include "gtk_letters_window.h"

/**
 * Constructor
 */
LjGtkLettersWindow::LjGtkLettersWindow(int argc, char **argv)
{
    char buf[128];
    int i;

    gtk_init (&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_usize(GTK_WIDGET (window), 200, 100);
    gtk_signal_connect(GTK_OBJECT (window), "delete_event",
                        (GtkSignalFunc) gtk_main_quit, NULL);
                        
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add(GTK_CONTAINER (window), vbox);
    gtk_widget_show(vbox);
    
    button = gtk_button_new_with_label ("press me");
    
    //gtk_signal_connect(GTK_OBJECT(button), "clicked", G_CALLBACK(this->showWin), NULL);
        
    gtk_box_pack_end (GTK_BOX (vbox), button, TRUE, TRUE, 2);
    
    gtk_widget_show(button);  
    
    gtk_window_set_decorated((GtkWindow *) window, FALSE);
    gtk_widget_show(window);
}

/**
 * Window Iniation
 */
void LjGtkLettersWindow::init()
{	
	bool check = true;
	int i = 0;
	printf("GTK STARTED");
	std::thread first(LjGtkLettersWindow::startRead, this);
	
	first.detach();	
	
	gtk_main();
}

/**
 * Shows main window
 */
void LjGtkLettersWindow::showWin()
{
	gtk_widget_show(window); 
}

/**
 * Hides main window
 */
void LjGtkLettersWindow::hideWin(GtkButton* button, gpointer func_data)
{
	gtk_widget_hide(window); 
}

/**
 * returns main window
 */
GtkWidget *LjGtkLettersWindow::getMainWindow()
{
	return window;
}

/**
 * On closing window
 */
void LjGtkLettersWindow::destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

/**
 * Setting pipe communication ends
 */
bool LjGtkLettersWindow::setPipeEnds(int rend, int wend)
{
	read_pend = rend;
	write_pend = wend;
	
	//close(write_pend);
	
	return true;
}

/**
 * Feedback to keyboard
 */
bool LjGtkLettersWindow::pipeWrite(char letter)
{
	write(write_pend, &letter, 1);
	return true;
}

/**
 * Reads signals from keyboard listener
 */
bool LjGtkLettersWindow::pipeRead()
{
	char str[80];
	int a;
	
	//gtk_widget_show_all(window);
	//gtk_widget_grab_focus(window);
	
	do {
		printf("*");
		a = read(read_pend, str, 80);
	} while(a < 1);
	
	printf("%c vs %c\n", lastread, str[0]);
	if(lastread != str[0])
	{
		lastread = str[0];
		printf("READ GTK!: %s\n", str);
	//gtk_widget_hide_all(window);
	
	}
	
	pipeRead();
	
	return true;	
}

/**
 * An intermediate to read signals from keyboard listener
 */
void LjGtkLettersWindow::startRead(LjGtkLettersWindow* lgw)
{
	lgw->lastread = '0';
	printf("AAA %d::\n", lgw->read_pend);
	lgw->pipeRead();
}

/**
 * destructor to clean all
 */
LjGtkLettersWindow::~LjGtkLettersWindow()
{
	gtk_main_quit();
}
