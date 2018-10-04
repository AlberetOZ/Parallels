
#include "pch.h"
#include "includes.h"


int main()
{
	unsigned int PTS = Take_seconds();
	NUMPTS = PTS*ONE_SECOND_MEMORY;
	waveIn = new short int[NUMPTS];

	WAVEFORMATEX pFormat;
	
	assert(!WaveFormatex_Setting(pFormat));

	HWAVEIN hWaveIn;
	WAVEHDR waveInHdr;

	waveInOpen(&hWaveIn, WAVE_MAPPER, &pFormat, 0L, 0L, WAVE_FORMAT_DIRECT);

	assert(!WaveInHeader_Preparation(waveInHdr));

	waveInPrepareHeader(hWaveIn, &waveInHdr, sizeof(WAVEHDR));

	waveInAddBuffer(hWaveIn, &waveInHdr, sizeof(WAVEHDR));


	waveInStart(hWaveIn);


	// Wait until finished recording
	for (; (waveInUnprepareHeader(hWaveIn, &waveInHdr, sizeof(WAVEHDR)) == WAVERR_STILLPLAYING);) {}
	
	waveInClose(hWaveIn);

	std::cout << "Record " << PTS << " seconds\n";


	HWAVEOUT hWaveOut;
	WAVEHDR WaveOutHdr;

	waveOutOpen(&hWaveOut, WAVE_MAPPER, &pFormat, 0, 0, WAVE_FORMAT_DIRECT);
	
	assert(!WaveOutHeader_Preparation(WaveOutHdr));

	waveOutPrepareHeader(hWaveOut, &WaveOutHdr, sizeof(WAVEHDR));

	waveOutSetVolume(hWaveOut, MAX_VOLUM);

	waveOutWrite(hWaveOut, &WaveOutHdr, sizeof(WAVEHDR));

	Sleep(PTS*MILISECONDS);

	waveOutClose(hWaveOut);


	//сохраняем записанный файл

	//???

	delete waveIn;
	return NULL;
}

