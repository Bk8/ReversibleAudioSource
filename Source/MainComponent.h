/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

class ReversibleAudioFormatReaderSource: public AudioFormatReaderSource
{
    
public:
    ReversibleAudioFormatReaderSource(AudioFormatReader* sourceReader, bool deleteReaderWhenThisIsDeleted)
    :AudioFormatReaderSource (sourceReader,  deleteReaderWhenThisIsDeleted)
    {
        reader.	setNonOwned(sourceReader);
        
    }
    
    void getNextAudioBlock (const AudioSourceChannelInfo& info) override
    {
        if (info.numSamples > 0)
        {
            blockSize= info.numSamples;
            if(reversed)
            {
                const int64 start = nextPlayPos;
                
                reader->read (info.buffer, info.startSample,
                              info.numSamples, start, true, true);
                info.buffer->reverse(info.startSample, info.numSamples);
                nextPlayPos-=info.numSamples;
            }
            else
            {
                const int64 start = nextPlayPos;
                
                reader->read (info.buffer, info.startSample,
                              info.numSamples, start, true, true);
                nextPlayPos += info.numSamples;
                
                
            }
        }
        
        
    }
    
    void reverse()
    {
        if(reversed)
            reversed=false;
        else
        {
            nextPlayPos-=blockSize;
            reversed=true;
        }
    }
    
    
private:
    //==============================================================================
    OptionalScopedPointer<AudioFormatReader> reader;
    
    int64 volatile nextPlayPos=0;
    bool volatile reversed=false;
    int64 blockSize;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReversibleAudioFormatReaderSource)
    
};
class MainContentComponent   : public Component
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&) override;
    void resized() override;
    void mouseDown (const MouseEvent &event) override;
    
    AudioDeviceManager deviceManager; // Interfaces with the audio hardware.
    AudioFormatManager formatManager; // Helps read audio file data.
    ScopedPointer<ReversibleAudioFormatReaderSource> readerSource; // Reads the audio data.
    AudioTransportSource transportSource; // Manages the playback of the audio file.
    AudioSourcePlayer sourcePlayer; // Reads data from the transport source to the audio device.

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
