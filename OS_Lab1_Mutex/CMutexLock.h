#pragma once

class CMutexLock									// �����, ���������� � ������������� ������
{
  HANDLE m_mutex;
  CMutexLock(const CMutexLock&);					// ��������� �����������
  CMutexLock& operator=(const CMutexLock&);
public:
  CMutexLock(HANDLE mutex): m_mutex(mutex)			// �������� ������ ��� ��������������� �������
  {
    const DWORD res = WaitForSingleObject(m_mutex, INFINITE);		
    assert(res == WAIT_OBJECT_0);					//���������� ���������, ���� ������� � ���������� ���������
  }
 ~CMutexLock()										 // ����������� ������ ��� �������� �������
  {
    const BOOL res = ReleaseMutex(m_mutex);
    assert(res);									//�������� �� ���������� ������������
  }
};
