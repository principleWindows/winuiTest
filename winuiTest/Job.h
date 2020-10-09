#pragma once

namespace winrt::winuiTest::implementation
{
	typedef	class CJob	JOB, * LPJOB;

	class CJob
	{
	public:
		virtual void doJob() = 0;
		virtual winrt::hstring showResult() = 0;

		CJob ( );
		virtual ~CJob ( );

		bool	m_bDone;

		LPJOB	pNext;
	};

}