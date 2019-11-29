#pragma once

class CAutoEvent
{
	HANDLE e_h_event;								// дескриптор создаваемого события
	CAutoEvent(const CAutoEvent&);					// запрет копирования
	CAutoEvent& operator=(const CAutoEvent&);
 public:
	CAutoEvent()
	{
		e_h_event = CreateEvent(NULL, TRUE, FALSE, NULL);		//создаем событиек
		assert(e_h_event);								//заваливаем программу, если событие не создано
	}
	~CAutoEvent() { CloseHandle(e_h_event); }			//деструктор закрывает событие
	HANDLE get() { return e_h_event; }					//метод получения дескриптора события
};