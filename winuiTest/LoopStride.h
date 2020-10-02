#pragma once
#include "Job.h"

namespace winrt::winuiTest::implementation
{

    // investigate loop stride and cache line
    class CLoopStride :
        public CJob
    {
	public:
		virtual void	doJob ( );
		virtual void	showResult ( winrt::hstring& strResult );

        void    doJob_2 ( );
        void    doJob_3 ( );

        DWORD   m_dwCnt_1;
        DWORD   m_dwCnt_2;

        CLoopStride ( );
		~CLoopStride ( );
    };

}