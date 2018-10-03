//-----------------------------------------------------------------------------
// ����:		WavWrite.h
//
// ��������:	���� ��������� ������ CWaveSoundWrite
//
//-----------------------------------------------------------------------------
#ifndef WAVE_WRITE_H
#define WAVE_WRITE_H
#include "windows.h"
#include <mmsystem.h>


//-----------------------------------------------------------------------------
// ���:			����� CWaveSoundWrite
// ��������:	�����, �������������� ������ ����� ���������� � ����
//-----------------------------------------------------------------------------
class CWaveSoundWrite
{
public:
	HMMIO	m_hmmioOut;			// �������������� ���������� �����
	MMCKINFO m_ckOut;			// ����������� � ��������� ����� ������� RIFF
	MMCKINFO m_ckOutRIFF;		// ������������ ��� �������� ����� �����
	MMIOINFO m_mmioinfoOut;

	CWaveSoundWrite();
	~CWaveSoundWrite();

	HRESULT Open(LPTSTR, WAVEFORMATEX*);
	HRESULT Reset();
	HRESULT Write(UINT, BYTE*, UINT*);
	HRESULT Close(DWORD);

};

#endif WAVE_WRITE_H



