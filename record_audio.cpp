#include <iostream>
#include <fstream>
#include <vector>
#include <portaudio.h>
#include <sndfile.h>

#define SAMPLE_RATE (44100)
#define FRAMES_PER_BUFFER (256)
#define NUM_CHANNELS (1)
#define SAMPLE_SIZE (sizeof(float))

// Callback function for PortAudio
static int recordCallback(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo,
                          PaStreamCallbackFlags statusFlags, void *userData)
{
    SNDFILE *file = static_cast<SNDFILE*>(userData);
    if (inputBuffer != nullptr) {
        sf_writef_float(file, static_cast<const float*>(inputBuffer), framesPerBuffer);
    }
    return paContinue;
}

int main() {
    PaError err;
    
    // Initialize PortAudio
    err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return -1;
    }

    // Open an audio file to write (WAV format)
    SF_INFO sfInfo;
    sfInfo.samplerate = SAMPLE_RATE;
    sfInfo.channels = NUM_CHANNELS;
    sfInfo.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
    SNDFILE *file = sf_open("output.wav", SFM_WRITE, &sfInfo);
    if (file == nullptr) {
        std::cerr << "Error opening file for writing: " << sf_strerror(file) << std::endl;
        return -1;
    }

    // Open the microphone input stream using PortAudio
    PaStream *stream;
    err = Pa_OpenDefaultStream(&stream, NUM_CHANNELS, 0, paFloat32, SAMPLE_RATE,
                               FRAMES_PER_BUFFER, recordCallback, file);
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return -1;
    }

    // Start recording
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        return -1;
    }

    std::cout << "Recording... Press Enter to stop." << std::endl;
    std::cin.get();

    // Stop and clean up
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
    sf_close(file);

    std::cout << "Recording saved to output.wav." << std::endl;
    return 0;
}

