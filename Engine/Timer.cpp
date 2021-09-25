#include "pch.h"
#include "Timer.h"

CTimer::CTimer(void)
	: m_fDeltaTime(0.f)
	, m_CpuTick {}
	, m_BeginTime {}
	, m_EndTime {}
{
}

CTimer::~CTimer(void)
{
}

HRESULT CTimer::Ready_Timer(void)
{
	QueryPerformanceCounter(&m_BeginTime);
	QueryPerformanceCounter(&m_EndTime);
	QueryPerformanceFrequency(&m_CpuTick);

	return S_OK;
}

void CTimer::Update_Timer(void)
{
	QueryPerformanceFrequency(&m_CpuTick);
	QueryPerformanceCounter(&m_EndTime);
	m_fDeltaTime = float(m_EndTime.QuadPart - m_BeginTime.QuadPart) / m_CpuTick.QuadPart;

	m_BeginTime.QuadPart = m_EndTime.QuadPart;
}
