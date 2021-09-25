#pragma once
class CTimer
{
public:
	CTimer(void);
	~CTimer(void);

public:
	float		Get_DeltaTime(void) { return m_fDeltaTime; }

public:
	HRESULT		Ready_Timer(void);
	void		Update_Timer(void);

private:
	LARGE_INTEGER	m_CpuTick;
	LARGE_INTEGER	m_BeginTime;
	LARGE_INTEGER	m_EndTime;
	float			m_fDeltaTime;
};

