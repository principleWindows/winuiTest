#include "pch.h"
#include "MgrThreads.h"

using namespace winrt;
using namespace winuiTest;
using namespace winuiTest::implementation;

LPMGRTHREADS	CMgrThreads::m_pMgrThreads = nullptr;

LPMGRTHREADS CMgrThreads::getMgr ( )
{
	if ( m_pMgrThreads == nullptr )
	{
		m_pMgrThreads = new CMgrThreads;
	}

	return	m_pMgrThreads;
}

CMgrThreads::CMgrThreads()
{
	m_bExit	= false;

	InitializeCriticalSection ( &m_cs );

	SYSTEM_INFO		sysInfo;

	GetSystemInfo ( &sysInfo );

	m_nThreads	= sysInfo.dwNumberOfProcessors;

	if ( MAX_NUM_THREADS < m_nThreads )
		m_nThreads	= MAX_NUM_THREADS;

	m_lstJob_header	= nullptr;
	m_lstJob_tailer	= nullptr;

//	the following line conflict with singleton
//	createAllWorkThreads ( );
}

CMgrThreads::~CMgrThreads()
{
	LPWORKTHREAD	pThread;

	m_bExit	= true;

	// wait 4 all work threads exit
	for ( DWORD i = 0; i < m_nThreads; i++ )
	{
		pThread	= m_lstThreads [ i ];

		if ( pThread == nullptr )	continue;

		while ( !pThread->m_bExited )	::Sleep ( 200 );

		CloseHandle ( pThread->m_hThread );

		delete	pThread;
	}

	m_pMgrThreads	= nullptr;
}

void CMgrThreads::createAllWorkThreads ( )
{
	LPWORKTHREAD	pThread;

	for ( DWORD i = 0; i < m_nThreads; i++ )
	{
		pThread	= new CWorkThread;

		pThread->m_dwReturn	= i + 700;

		m_lstThreads [ i ]	= pThread;
	}
}

void CMgrThreads::addJob ( LPJOB pJob )
{
	assert ( pJob != nullptr);

	pJob->pNext	= nullptr;

	::EnterCriticalSection ( &m_cs );

	if ( m_lstJob_header == nullptr )
	{
		m_lstJob_header	= pJob;
		m_lstJob_tailer	= pJob;

		::LeaveCriticalSection ( &m_cs );

		return;
	}

	m_lstJob_tailer->pNext	= pJob;
	m_lstJob_tailer			= pJob;

	::LeaveCriticalSection ( &m_cs );
}

LPJOB CMgrThreads::getJob ( )
{
	LPJOB	pJob	= nullptr;

	::EnterCriticalSection ( &m_cs );

	if ( m_lstJob_header == nullptr )
	{
		::LeaveCriticalSection ( &m_cs );
		return	pJob;
	}

	pJob	= m_lstJob_header;

	m_lstJob_header	= pJob->pNext;

	if ( m_lstJob_header == nullptr )	m_lstJob_tailer	= nullptr;

	::LeaveCriticalSection ( &m_cs );

	return	pJob;
}