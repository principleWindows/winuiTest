#pragma once

namespace winrt::winuiTest::implementation
{
	typedef	class CJob	JOB, * LPJOB;

	class CJob
	{
	public:
		virtual void	doJob ( ){ }
		virtual void	showResult ( winrt::hstring& strResult ) { }

		CJob ( );
		~CJob ( );

		bool	m_bDone;

		LPJOB	pNext;
	};

}