#pragma once

class CMutexLock									// класс, занимающий и освобождающий мютекс
{
  HANDLE m_mutex;
  CMutexLock(const CMutexLock&);					// запрещаем копирование
  CMutexLock& operator=(const CMutexLock&);
public:
  CMutexLock(HANDLE mutex): m_mutex(mutex)			// занимаем мютекс при конструировании объекта
  {
    const DWORD res = WaitForSingleObject(m_mutex, INFINITE);		
    assert(res == WAIT_OBJECT_0);					//заваливаем программу, если мьютекс в сигнальном состоянии
  }
 ~CMutexLock()										 // освобождаем мютекс при удалении объекта
  {
    const BOOL res = ReleaseMutex(m_mutex);
    assert(res);									//проверка на успешность освобождения
  }
};
