

#pragma comment(lib,"winmm.lib") 


unsigned long NUMPTS = NULL;
const static unsigned int sampleRate = ONE_SECOND_MEMORY;
short int* waveIn = nullptr;

unsigned int Take_seconds()
{
	unsigned int PTS = NULL;
	std::cout << "How many seconds to record?\n";
	std::cin >> PTS;
	assert(PTS);
	return PTS;

}

int WaveFormatex_Setting(WAVEFORMATEX& pFormat)
{
	pFormat.wFormatTag = WAVE_FORMAT_PCM;					 // simple, uncompressed format
	pFormat.nChannels = MONO;								 //  1=mono, 2=stereo
	pFormat.wBitsPerSample = PCM_SUBCHUNK1SIZE;              //  16 for high quality, 8 for telephone-grade
	pFormat.nSamplesPerSec = sampleRate;
	pFormat.nBlockAlign = DEFAULT_NBLOCKALIGN;
	pFormat.nAvgBytesPerSec = sampleRate * pFormat.nChannels * pFormat.wBitsPerSample / BYTE;
	pFormat.nBlockAlign = pFormat.nChannels * pFormat.wBitsPerSample / BYTE;
	pFormat.cbSize = NULL;


	return NULL;
}

int WaveInHeader_Preparation(WAVEHDR& waveInHdr)
{

	waveInHdr.lpData = (LPSTR)waveIn;
	waveInHdr.dwBufferLength = NUMPTS + NUMPTS;				//
	waveInHdr.dwBytesRecorded = NULL;
	waveInHdr.dwUser = NULL;
	waveInHdr.dwFlags = NULL;
	waveInHdr.dwLoops = NULL;


	return NULL;
}

int WaveOutHeader_Preparation(WAVEHDR& WaveOutHdr)
{

	WaveOutHdr.lpData = (LPSTR)waveIn;
	WaveOutHdr.dwBufferLength = NUMPTS + NUMPTS;
	WaveOutHdr.dwBytesRecorded = NULL;
	WaveOutHdr.dwUser = NULL;
	WaveOutHdr.dwFlags = NULL;
	WaveOutHdr.dwLoops = OUTPUT_LOOP;

	return NULL;

}