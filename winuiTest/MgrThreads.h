#pragma once

#include <mutex>
#include "WorkThread.h"
#include "Job.h"

namespace winrt::winuiTest::implementation
{
	constexpr DWORD MAX_NUM_THREADS = 32;

	typedef class CMgrThreads	MGRTHREADS, * LPMGRTHREADS;

	class CMgrThreads
	{
	public:
		// Disable the copy constructor because of singleton mode.
		CMgrThreads(const CMgrThreads &) = delete;
		// Disable the assignment operator because of singleton mode.
		CMgrThreads &operator=(const CMgrThreads &) = delete;

		//CRITICAL_SECTION	m_cs;	

		volatile bool	m_bExit;

		/// <summary>
		/// Create all threads in the thread pool.
		/// </summary>
		void	createAllWorkThreads ( );

		/// <summary>
		/// Get and remove the job at the head of the job list.
		/// Return nullptr if the job list is empty.
		/// </summary>
		LPJOB	getJob ( );

		/// <summary>
		/// Append a job to the tail of the job list.
		/// One of the thread in the thread pool will execute it.
		/// </summary>
		void	addJob ( LPJOB pJob );

		/// <summary>
		/// Use this factory methord to get the sole instance of CMgrThreads.
		/// </summary>
		static LPMGRTHREADS getMgr();

		static void shutdown();

	protected:
		/// <summary>
		/// Size of the thread pool, should not exceed MAX_NUM_THREADS.
		/// </summary>
		DWORD m_nThreads;

		/// <summary>
		/// Thread Pool
		/// </summary>
		LPWORKTHREAD	m_lstThreads [ MAX_NUM_THREADS ];

		/// <summary>
		/// Header of job linked list
		/// </summary>
		LPJOB	m_lstJob_header;

		/// <summary>
		/// Tailer of job linked list
		/// </summary>
		LPJOB	m_lstJob_tailer;

		// Set the constructor to private because of singleton mode.
		CMgrThreads();

		// If you want to release the sole instance, please call CMgrThreads::shutdown()
		virtual ~CMgrThreads();

	private:
		/// <summary>
		/// Pointer to the sole instance.
		/// </summary>
		static LPMGRTHREADS pMgrThreads;
		static std::mutex mtx;
	};
}


