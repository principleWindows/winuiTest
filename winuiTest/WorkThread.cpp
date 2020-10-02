#include "pch.h"
#include "WorkThread.h"
#include "MgrThreads.h"

using namespace winrt;
using namespace winuiTest;
using namespace winuiTest::implementation;

DWORD  WINAPI ThreadProc ( LPVOID lpParam )
{
	LPWORKTHREAD	pThis	= (LPWORKTHREAD) lpParam;

	pThis->loopWork ( );

	return	pThis->m_dwReturn;
}

void CWorkThread::loopWork ( )
{
	while ( !m_pMgr->m_bExit )
	{
		LPJOB	pJob;
		
		pJob	= m_pMgr->getJob ( );

		if ( pJob == nullptr )
		{
			::Sleep ( 200 );
			continue;
		}

		pJob->doJob ( );
	}
	
	m_bExited	= true;
}

CWorkThread::CWorkThread ( )
{
	pNext	= nullptr;

	m_pMgr	= CMgrThreads::getMgr ( );

	m_bExited	= false;

	m_hThread	= CreateThread ( NULL, 0, ThreadProc, this, 0, 0 );
}

CWorkThread::~CWorkThread()
{
	
}
