

#pragma comment(lib,"winmm.lib") 


int NUMPTS = 0;
const static unsigned int sampleRate = ONE_SECOND_MEMORY;
short int* waveIn = nullptr;

unsigned int Take_seconds()
{
	unsigned int PTS = 0;
	std::cout << "How many seconds to record?\n";
	std::cin >> PTS;
	assert(PTS);
	return PTS;

}

int WaveFormatex_Setting(WAVEFORMATEX& pFormat)
{
	pFormat.wFormatTag = WAVE_FORMAT_PCM;     // simple, uncompressed format
	pFormat.nChannels = 1;                    //  1=mono, 2=stereo
	pFormat.wBitsPerSample = 16;              //  16 for high quality, 8 for telephone-grade
	pFormat.nSamplesPerSec = sampleRate;
	pFormat.nBlockAlign = 2;
	pFormat.nAvgBytesPerSec = sampleRate * pFormat.nChannels * pFormat.wBitsPerSample / 8;
	pFormat.nBlockAlign = pFormat.nChannels * pFormat.wBitsPerSample / 8;
	pFormat.cbSize = 0;


	return NULL;
}

int WaveInHeader_Preparation(WAVEHDR& waveInHdr)
{

	waveInHdr.lpData = (LPSTR)waveIn;
	waveInHdr.dwBufferLength = NUMPTS * 2;
	waveInHdr.dwBytesRecorded = 0;
	waveInHdr.dwUser = 0L;
	waveInHdr.dwFlags = 0L;
	waveInHdr.dwLoops = 0L;


	return NULL;
}

int WaveOutHeader_Preparation(WAVEHDR& WaveOutHdr)
{

	WaveOutHdr.lpData = (LPSTR)waveIn;
	WaveOutHdr.dwBufferLength = NUMPTS * 2;
	WaveOutHdr.dwBytesRecorded = 0;
	WaveOutHdr.dwUser = 0;
	WaveOutHdr.dwFlags = 0;
	WaveOutHdr.dwLoops = 1;

	return NULL;

}