#ifndef _OFX_PD
#define _OFX_PD

#include "ofConstants.h"

#include <z_libpd.h>
#include "ofxPdListener.h"

#ifndef HAVE_UNISTD_H
#pragma warning You need to define HAVE_UNISTD_H in your project build settings!
#endif

///
///	a Pure Data instance
///
/// derive this class and implement the callback functions
///
///	references:	http://gitorious.org/pdlib/pages/Libpd
///
class ofxPd {
	
	public :

		ofxPd();
		virtual ~ofxPd();
        
        /// initialize resources
		bool init(const int numInChannels, const int numOutChannels, 
					const int sampleRate);
        
        /// clear resources
        void clear();
		
		/// add to the pd search path
		void addToSearchPath(const string& path);
		
		/// clear the current pd search path
		void clearSearchPath();
		
		/// open a patch, take a absolute or relative path (in data folder)
		void openPatch(const string& patch);
		
		/// close a patch, takes the patch's basename (filename without extension)
		void closePatch(const string& name);
		
		// turn on/off digital signal processing
		void dspOn();
		void dspOff();
		
		/// send messages to pd
		void sendFloat(const string& messageName, float value);
		void sendBang(const string& messageName);	
		void sendMidiNote(int channel, int noteNum, int velocity);
		void sendMidiControlChange(int channel, int ctlNum, int value);
		void sendMidiBend(int channel, int value);
		void sendMidiProgramChange(int channel, int program);
		void sendMidiPolyTouch(int channel, int noteNum, int value);
		void sendMidiAfterTouch(int channel, int value);
		
		/// add message source names to receive to
		void bind(const string& source);
		void unbind(const string& source);
		
		/// add listener to receieve events
		void addListener(ofxPdListener *listener);
		
		/// get the pd blocksize of pd (sample length per channel)
		static int getBlocksize();
		
		/// audio in/out callbacks
		/// the libpd processing is done in the audioOut callback
		virtual void audioIn(float * input, int bufferSize, int nChannels);
		virtual void audioOut(float * output, int bufferSize, int nChannels);
		
    private:
	
		bool bPdInited;						///< is pd inited?

		int sampleRate;						///< the audio sample rate
		int numInChannels, numOutChannels;	///< number of channels in/out
		float *inputBuffer;  				///< interleaved input audio buffer
		
		// libpd static callback functions
		static void _print(const char* s);
				
		static void _bang(const char* source);
		static void _float(const char* source, float value);
		static void _symbol(const char* source, const char* symbol);
		static void _list(const char* source, int argc, t_atom* argv); 
		static void _message(const char* source, const char *symbol,
												int argc, t_atom *argv);

		static void _noteon(int channel, int pitch, int velocity);
		static void _controlchange(int channel, int controller, int val);
		static void _programchange(int channel, int program);
		static void _pitchbend(int channel, int val);
		static void _aftertouch(int channel, int val);
		static void _polyaftertouch(int channel, int pitch, int val);
		static void _midibyte(int port, int byte);
};

#endif
