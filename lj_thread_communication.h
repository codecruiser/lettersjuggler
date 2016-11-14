/**
 * Letters Juggler 
 *  
 * Version: 0.1 (pre-Alpha version)
 * 
 * Content: LJThreadCommunication Class
 * 
 * Description: The class is a frame for handling 
 * 				the pipe communication between keyboard thread
 * 				and window thread
 * 
 * Author: Zbigniew Szczepanski
 * 
 * TODO: there is a lot of issues which need to be addressed here
 */

#ifndef LJ_THREAD_COMMUNICATION_H
#define LJ_THREAD_COMMUNICATION_H

class LjThreadCommunication
{
	protected:
		int read_pend;
		int write_pend;
		
		virtual bool setPipeEnds(int, int) = 0;
		virtual bool pipeWrite() = 0;
		virtual bool pipeRead() = 0;
};

#endif
