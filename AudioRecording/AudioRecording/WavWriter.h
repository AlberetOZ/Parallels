
// �����, ����������� ��������� WAV �����.
class WAV
{
public:
	// WAV-������ ���������� � RIFF-���������:

	// �������� ������� "RIFF" � ASCII ���������
	// (0x52494646 � big-endian �������������)
	char chunkId[STRING_NUMBER_SYMBOLS_WAV];

	// 36 + subchunk2Size, ��� ����� �����:
	// 4 + (8 + subchunk1Size) + (8 + subchunk2Size)
	// ��� ���������� ������ �������, ������� � ���� �������.
	// ����� ������, ��� ������ ����� - 8, �� ����,
	// ��������� ���� chunkId � chunkSize.
	unsigned long chunkSize;

	// �������� ������� "WAVE"
	// (0x57415645 � big-endian �������������)
	char format[STRING_NUMBER_SYMBOLS_WAV];

	// ������ "WAVE" ������� �� ���� ����������: "fmt " � "data":
	// ���������� "fmt " ��������� ������ �������� ������:

	// �������� ������� "fmt "
	// (0x666d7420 � big-endian �������������)
	char subchunk1Id[STRING_NUMBER_SYMBOLS_WAV];

	// 16 ��� ������� PCM.
	// ��� ���������� ������ ����������, ������� � ���� �������.
	unsigned long subchunk1Size;

	// ����� ������
	// ��� PCM = 1 (�� ����, �������� �����������).
	// ��������, ������������ �� 1, ���������� ��������� ������ ������.
	unsigned short audioFormat;

	// ���������� �������. ���� = 1, ������ = 2 � �.�.
	unsigned short numChannels;

	// ������� �������������. 8000 ��, 44100 �� � �.�.
	unsigned long sampleRate;

	// sampleRate * numChannels * bitsPerSample/8
	unsigned long byteRate;

	// numChannels * bitsPerSample/8
	// ���������� ���� ��� ������ ������, ������� ��� ������.
	unsigned short blockAlign;

	// ��� ���������� "��������" ��� �������� ��������. 8 ���, 16 ��� � �.�.
	unsigned short bitsPerSample;

	// ���������� "data" �������� �����-������ � �� ������.

	// �������� ������� "data"
	// (0x64617461 � big-endian �������������)
	char subchunk2Id[STRING_NUMBER_SYMBOLS_WAV];

	// numSamples * numChannels * bitsPerSample/8
	// ���������� ���� � ������� ������.
	unsigned long subchunk2Size;
	
	// ����� ������� ��������������� Wav ������.
	const short int* waveData;

	WAV();													//	�����������
	WAV(const short int*, unsigned long);					// ����������� � �������
	~WAV();													//	����������

	int read(const short int*, unsigned long);			// ������ � �����
	int write(FILE*);						// ������ � ����
	int count();										// ������� byteRate, blockAlign, chunkSize
	//int strncpy(char*, const size_t, const char*);		// ����������� strncpy, ��� ��� ��������� ������ ��� \0
};

int WAV::count() {
	byteRate = sampleRate * numChannels * bitsPerSample / BYTE;
	blockAlign = numChannels * bitsPerSample / BYTE;
	chunkSize = NUMBER_SYMBOLS_WAV + (NUMBER_SYMBOLS_WAV + NUMBER_SYMBOLS_WAV + subchunk1Size) + (NUMBER_SYMBOLS_WAV + NUMBER_SYMBOLS_WAV + subchunk2Size);

	return 0;
}
/*
int WAV::strncpy(char* destination, const size_t size, const char* data) {
	assert(destination);
	assert(data);
	for (size_t step = 0; step < size; ++step)
	{
		destination[step] = data[step];

	}

	return 0;
}
*/

WAV::WAV()
{
	assert(!strcpy_s(chunkId, STRING_NUMBER_SYMBOLS_WAV, "RIFF"));
	assert(!strcpy_s(format, STRING_NUMBER_SYMBOLS_WAV, "WAVE"));
	assert(!strcpy_s(subchunk1Id, STRING_NUMBER_SYMBOLS_WAV, "fmt "));
	subchunk1Size = PCM_SUBCHUNK1SIZE;
	audioFormat = FORMAT_PCM;
	numChannels = MONO;
	sampleRate = DEFAULT_SAMPLE_RATE;
	bitsPerSample = DEFAULT_BITS_PER_SAMPLE;	
	assert(!strcpy_s(subchunk2Id, STRING_NUMBER_SYMBOLS_WAV, "data"));
	subchunk2Size = NULL;
	// ����� ������� ��������������� Wav ������.
	waveData = nullptr;

	assert(!WAV::count());

	


}


WAV::WAV(const short int* waveIn, unsigned long waveInSize)
{
	waveData = waveIn;

	assert(!strcpy_s(chunkId, STRING_NUMBER_SYMBOLS_WAV, "RIFF"));
	assert(!strcpy_s(format, STRING_NUMBER_SYMBOLS_WAV, "WAVE"));
	assert(!strcpy_s(subchunk1Id, STRING_NUMBER_SYMBOLS_WAV, "fmt "));
	subchunk1Size = PCM_SUBCHUNK1SIZE;
	audioFormat = FORMAT_PCM;
	numChannels = MONO;
	sampleRate = DEFAULT_SAMPLE_RATE;
	bitsPerSample = DEFAULT_BITS_PER_SAMPLE;
	assert(!strcpy_s(subchunk2Id, STRING_NUMBER_SYMBOLS_WAV, "data"));
	subchunk2Size = waveInSize;
	
	  
	assert(!WAV::count());
}

int WAV::read(const short int* waveIn, unsigned long waveInSize)
{
	waveData = waveIn;
	subchunk2Size = waveInSize;

	assert(!WAV::count());
	return 0;
}

int WAV::write(FILE* output) {

	fputs(chunkId, output);
	fputs((char*)&chunkSize, output);
	fputs(format, output);
	fputs(subchunk1Id, output);
	
	fputs((char*)&audioFormat, output);
	fputs((char*)&numChannels, output);
	fputs((char*)&sampleRate, output);
	fputs((char*)&byteRate, output);
	fputs((char*)&blockAlign, output);
	fputs((char*)&bitsPerSample, output);
	fputs(subchunk2Id, output);
	fputs((char*)&subchunk2Size, output);
	fwrite(waveData, subchunk2Size *sizeof(*waveData), 1, output);


	return 0;
}

WAV::~WAV() {

	// ��� ���������� ������ ��� ����� ������ ����������

}


