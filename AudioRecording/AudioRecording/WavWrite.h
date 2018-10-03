//-----------------------------------------------------------------------------
// Файл:		WavWrite.h
//
// Описание:	Файл заголовка класса CWaveSoundWrite
//
//-----------------------------------------------------------------------------
#ifndef WAVE_WRITE_H
#define WAVE_WRITE_H
#include "windows.h"
#include <mmsystem.h>


//-----------------------------------------------------------------------------
// Имя:			Класс CWaveSoundWrite
// Описание:	Класс, осуществляющий запись аудио информации в файл
//-----------------------------------------------------------------------------
class CWaveSoundWrite
{
public:
	HMMIO	m_hmmioOut;			// Мультимедийный дескриптор файла
	MMCKINFO m_ckOut;			// Инфоромация о вложенном блоке формата RIFF
	MMCKINFO m_ckOutRIFF;		// Используется при открытии аудио файла
	MMIOINFO m_mmioinfoOut;

	CWaveSoundWrite();
	~CWaveSoundWrite();

	HRESULT Open(LPTSTR, WAVEFORMATEX*);
	HRESULT Reset();
	HRESULT Write(UINT, BYTE*, UINT*);
	HRESULT Close(DWORD);

};

#endif WAVE_WRITE_H



