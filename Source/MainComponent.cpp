/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
    setSize (600, 400);
    
    // Configure the format manager to read common audio file types.
    formatManager.registerBasicFormats();
    
    // Connect the transport source to the source player.
    sourcePlayer.setSource (&transportSource);
    
    // Connect the source player to the audio device.
    deviceManager.addAudioCallback (&sourcePlayer);
    
    // Initialize the device with basic settings (no inputs, two outputs).
    deviceManager.initialise (0, 2, nullptr, true);
    
    FileChooser chooser ("Select a Wave file to play...",
                         File::nonexistent,
                         "*");
    
    if (chooser.browseForFileToOpen()) {
        File file (chooser.getResult());
        
        // Create a reader from the selected file.
        readerSource = new ReversibleAudioFormatReaderSource (formatManager.createReaderFor (file), true);
        
        // Connect the reader to the transport source.
        transportSource.setSource (readerSource);
        
    }
    
    transportSource.start();
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff001F36));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Click to reverse", getLocalBounds(), Justification::centred, true);
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}


void 	MainContentComponent::mouseDown (const MouseEvent &event)
{
    readerSource->reverse();
}
