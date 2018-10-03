
#include "pch.h"
#include "windows.h"
#include "mmsystem.h"
#include <iostream>
#include <string.h>
#include <assert.h>
#include <fstream>

#pragma comment(lib,"winmm.lib") 


const int NUMPTS = 16000 * 5;   // 5 second
int sampleRate = 16000;
short int waveIn[NUMPTS] = { 0 };


int main()
{
	WAVEFORMATEX pFormat;
	pFormat.wFormatTag = WAVE_FORMAT_PCM;     // simple, uncompressed format
	pFormat.nChannels = 1;                    //  1=mono, 2=stereo
	pFormat.wBitsPerSample = 16;              //  16 for high quality, 8 for telephone-grade
	pFormat.nSamplesPerSec = sampleRate;
	pFormat.nBlockAlign = 2;
	pFormat.nAvgBytesPerSec = sampleRate * pFormat.nChannels * pFormat.wBitsPerSample / 8;
	pFormat.nBlockAlign = pFormat.nChannels * pFormat.wBitsPerSample / 8;
	pFormat.cbSize = 0;

	HWAVEIN hWaveIn;
	WAVEHDR waveInHdr;

	waveInOpen(&hWaveIn, WAVE_MAPPER, &pFormat, 0L, 0L, WAVE_FORMAT_DIRECT);

	waveInHdr.lpData = (LPSTR)waveIn;
	waveInHdr.dwBufferLength = NUMPTS * 2;
	waveInHdr.dwBytesRecorded = 0;
	waveInHdr.dwUser = 0L;
	waveInHdr.dwFlags = 0L;
	waveInHdr.dwLoops = 0L;

	waveInPrepareHeader(hWaveIn, &waveInHdr, sizeof(WAVEHDR));

	waveInAddBuffer(hWaveIn, &waveInHdr, sizeof(WAVEHDR));


	waveInStart(hWaveIn);


	// Wait until finished recording
	do {} while (waveInUnprepareHeader(hWaveIn, &waveInHdr, sizeof(WAVEHDR)) == WAVERR_STILLPLAYING);
	
	//short int buf[NUMPTS];

	waveInClose(hWaveIn);


	HWAVEOUT hWaveOut;
	WAVEHDR WaveOutHdr;

	waveOutOpen(&hWaveOut, WAVE_MAPPER, &pFormat, 0L, 0L, WAVE_FORMAT_DIRECT);

	WaveOutHdr.lpData = (LPSTR)waveIn;
	WaveOutHdr.dwBufferLength = NUMPTS * 2;
	WaveOutHdr.dwBytesRecorded = 0;
	WaveOutHdr.dwUser = 0L;
	WaveOutHdr.dwFlags = 0L;
	WaveOutHdr.dwLoops = 1L;



	waveOutPrepareHeader(hWaveOut, &WaveOutHdr, sizeof(WAVEHDR));

	waveOutSetVolume(hWaveOut, 0xFFFFFFFF);

	waveOutWrite(hWaveOut, &WaveOutHdr, sizeof(WAVEHDR));

	Sleep(5000);

	waveOutClose(hWaveOut);

	//std::cout << waveIn[1433];

	//сохраняем записанный файл
	return 0;
}