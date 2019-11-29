#pragma once

class CAutoEvent
{
	HANDLE e_h_event;								// ���������� ������������ �������
	CAutoEvent(const CAutoEvent&);					// ������ �����������
	CAutoEvent& operator=(const CAutoEvent&);
 public:
	CAutoEvent()
	{
		e_h_event = CreateEvent(NULL, TRUE, FALSE, NULL);		//������� ��������
		assert(e_h_event);								//���������� ���������, ���� ������� �� �������
	}
	~CAutoEvent() { CloseHandle(e_h_event); }			//���������� ��������� �������
	HANDLE get() { return e_h_event; }					//����� ��������� ����������� �������
};