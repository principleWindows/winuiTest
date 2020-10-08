#pragma once

namespace winrt::winuiTest::implementation
{
	typedef class CWorkThread	WORKTHREAD, * LPWORKTHREAD;

	class CMgrThreads;
	class CWorkThread
	{
	public:
		void	loopWork ( );

		CWorkThread::CWorkThread(CMgrThreads *m_pMgr);
		CWorkThread::~CWorkThread ( );

		HANDLE	m_hThread;

		LPWORKTHREAD	pNext;

		bool	m_bExited;

		DWORD	m_dwReturn;

		CMgrThreads *	m_pMgr;
	};
}

