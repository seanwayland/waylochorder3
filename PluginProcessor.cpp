/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;
//==============================================================================
WayloChorder3AudioProcessor::WayloChorder3AudioProcessor()

     //: AudioProcessorValueTreeState parameters(*this, nullptr);
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
     , parameters(*this, nullptr)
#endif

{
    

    for (int i = 0; i < 127 ; i++ ){
        playing[i]= 0;
    }

    parameters.state.addChild(makeChordValueTree("Cmaj", {60,64,67}), -1, nullptr);
    parameters.state.addChild(makeChordValueTree("Cmin", {60,63,67}), -1, nullptr);
    
   
}

WayloChorder3AudioProcessor::~WayloChorder3AudioProcessor()
{
}
/*
int playing[127]; // array to hold notes playing
int numChords; // num of chords in chord sequence
int numNotes ; // number of notes in a chord
int note; // a midi note value
int chordsPosition = 0; // pointer to postion in chord array
int midChan = 0;
int latchBool = 1;
 */


vector<int> chord;
vector< vector<int> > chords;

//==============================================================================


ValueTree WayloChorder3AudioProcessor::makeChordValueTree(String name, std::initializer_list<int> notes)
{
    ValueTree result(name);
    for (size_t i=0;i<notes.size();++i)
        result.setProperty("note_"+String(i), *(notes.begin()+i), nullptr);
    return result;
}

const String WayloChorder3AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WayloChorder3AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WayloChorder3AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WayloChorder3AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WayloChorder3AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WayloChorder3AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WayloChorder3AudioProcessor::getCurrentProgram()
{
    return 0;
}

void WayloChorder3AudioProcessor::setCurrentProgram (int index)
{
}

const String WayloChorder3AudioProcessor::getProgramName (int index)
{
    return {};
}

void WayloChorder3AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void WayloChorder3AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

}

void WayloChorder3AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WayloChorder3AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void WayloChorder3AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool WayloChorder3AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* WayloChorder3AudioProcessor::createEditor()
{
    return new WayloChorder3AudioProcessorEditor (*this);
}

//==============================================================================
void WayloChorder3AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void WayloChorder3AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WayloChorder3AudioProcessor();
}
