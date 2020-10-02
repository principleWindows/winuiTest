#pragma once

#include "WorkThread.h"
#include "Job.h"

namespace winrt::winuiTest::implementation
{
#define	MAX_NUM_THREADS	32

	typedef class CMgrThreads	MGRTHREADS, * LPMGRTHREADS;

	class CMgrThreads
	{
	public:
		CMgrThreads();
		~CMgrThreads();

		CRITICAL_SECTION	m_cs;

		volatile bool	m_bExit;

		static	LPMGRTHREADS	getMgr ( );

		void	createAllWorkThreads ( );

		LPJOB	getJob ( );
		void	addJob ( LPJOB pJob );

	protected:
		DWORD		m_nThreads;	// should not exceed MAX_NUM_THREADS

		LPWORKTHREAD	m_lstThreads [ MAX_NUM_THREADS ];

		LPJOB	m_lstJob_header;
		LPJOB	m_lstJob_tailer;

		static	LPMGRTHREADS	m_pMgrThreads;
	};
}


