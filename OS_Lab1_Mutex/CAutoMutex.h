#pragma once

class CAutoMutex							// класс, создающий и удал€ющий мьютекс
{
  HANDLE m_h_mutex;							// дескриптор создаваемого мютекса
  CAutoMutex(const CAutoMutex&);				// запрет копировани€
  CAutoMutex& operator=(const CAutoMutex&);
 public:
  CAutoMutex()
  {
    m_h_mutex = CreateMutex(NULL, FALSE, NULL);		//создаем мьютекс
	assert(m_h_mutex);								//заваливаем программу, если мьютекс не создан
  }
  ~CAutoMutex() { CloseHandle(m_h_mutex); }			//деструктор закрывает мьютекс
  HANDLE get() { return m_h_mutex; }				//метод получени€ дескриптора мьютекса
};
