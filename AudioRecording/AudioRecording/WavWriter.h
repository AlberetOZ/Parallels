
// Класс, описывающий заголовок WAV файла.
class WAV
{
public:
	// WAV-формат начинается с RIFF-заголовка:

	// Содержит символы "RIFF" в ASCII кодировке
	// (0x52494646 в big-endian представлении)
	char chunkId[STRING_NUMBER_SYMBOLS_WAV];

	// 36 + subchunk2Size, или более точно:
	// 4 + (8 + subchunk1Size) + (8 + subchunk2Size)
	// Это оставшийся размер цепочки, начиная с этой позиции.
	// Иначе говоря, это размер файла - 8, то есть,
	// исключены поля chunkId и chunkSize.
	unsigned long chunkSize;

	// Содержит символы "WAVE"
	// (0x57415645 в big-endian представлении)
	char format[STRING_NUMBER_SYMBOLS_WAV];

	// Формат "WAVE" состоит из двух подцепочек: "fmt " и "data":
	// Подцепочка "fmt " описывает формат звуковых данных:

	// Содержит символы "fmt "
	// (0x666d7420 в big-endian представлении)
	char subchunk1Id[STRING_NUMBER_SYMBOLS_WAV];

	// 16 для формата PCM.
	// Это оставшийся размер подцепочки, начиная с этой позиции.
	unsigned long subchunk1Size;

	// Аудио формат
	// Для PCM = 1 (то есть, Линейное квантование).
	// Значения, отличающиеся от 1, обозначают некоторый формат сжатия.
	unsigned short audioFormat;

	// Количество каналов. Моно = 1, Стерео = 2 и т.д.
	unsigned short numChannels;

	// Частота дискретизации. 8000 Гц, 44100 Гц и т.д.
	unsigned long sampleRate;

	// sampleRate * numChannels * bitsPerSample/8
	unsigned long byteRate;

	// numChannels * bitsPerSample/8
	// Количество байт для одного сэмпла, включая все каналы.
	unsigned short blockAlign;

	// Так называемая "глубиная" или точность звучания. 8 бит, 16 бит и т.д.
	unsigned short bitsPerSample;

	// Подцепочка "data" содержит аудио-данные и их размер.

	// Содержит символы "data"
	// (0x64617461 в big-endian представлении)
	char subchunk2Id[STRING_NUMBER_SYMBOLS_WAV];

	// numSamples * numChannels * bitsPerSample/8
	// Количество байт в области данных.
	unsigned long subchunk2Size;
	
	// Далее следуют непосредственно Wav данные.
	const short int* waveData;

	WAV();													//	конструктор
	WAV(const short int*, unsigned long);					// конструктор с данными
	~WAV();													//	деструктор

	int read(const short int*, unsigned long);			// данные в класс
	int write(FILE*);						// данные в файл
	int count();										// считает byteRate, blockAlign, chunkSize
	//int strncpy(char*, const size_t, const char*);		// собственная strncpy, так как требуется работа без \0
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
	// Далее следуют непосредственно Wav данные.
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

	// при дальнейщей работе тут будет полный деструктор

}


