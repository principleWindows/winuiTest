#include "pch.h"
#include "MgrThreads.h"

using namespace winrt;
using namespace winuiTest;
using namespace winuiTest::implementation;

LPMGRTHREADS CMgrThreads::pMgrThreads = nullptr;
std::mutex CMgrThreads::mtx;

LPMGRTHREADS CMgrThreads::getMgr()
{
	std::lock_guard<std::mutex> locker(mtx);
	if (pMgrThreads == nullptr)
		pMgrThreads = new CMgrThreads();
	return	pMgrThreads;
}

void CMgrThreads::shutdown()
{
	std::lock_guard<std::mutex> locker(mtx);
	if (CMgrThreads::pMgrThreads != nullptr)
		delete pMgrThreads;
}

CMgrThreads::CMgrThreads()
{
	m_bExit	= false;

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	m_nThreads = sysInfo.dwNumberOfProcessors;
	if (MAX_NUM_THREADS < m_nThreads)
		m_nThreads = MAX_NUM_THREADS;

	m_lstJob_header	= nullptr;
	m_lstJob_tailer	= nullptr;

	createAllWorkThreads();
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
}

void CMgrThreads::createAllWorkThreads ( )
{
	LPWORKTHREAD	pThread;

	for ( DWORD i = 0; i < m_nThreads; i++ )
	{
		pThread	= new CWorkThread(this);

		pThread->m_dwReturn	= i + 700;

		m_lstThreads [ i ]	= pThread;
	}
}

void CMgrThreads::addJob ( LPJOB pJob )
{
	assert ( pJob != nullptr);

	pJob->pNext	= nullptr;

	std::lock_guard<std::mutex> locker(mtx);

	if ( m_lstJob_header == nullptr )
	{
		m_lstJob_header	= pJob;
		m_lstJob_tailer	= pJob;
		return;
	}

	m_lstJob_tailer->pNext	= pJob;
	m_lstJob_tailer			= pJob;
}

LPJOB CMgrThreads::getJob ( )
{
	LPJOB	pJob	= nullptr;

	std::lock_guard<std::mutex> locker(mtx);

	if (m_lstJob_header == nullptr)
		return pJob;

	pJob	= m_lstJob_header;

	m_lstJob_header	= pJob->pNext;

	if (m_lstJob_header == nullptr)
		m_lstJob_tailer = nullptr;

	return	pJob;
}