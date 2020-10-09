#pragma once
#include "Job.h"

namespace winrt::winuiTest::implementation
{

	// investigate loop stride and cache line
	class CLoopStride : public CJob
	{
	public:
		enum WhichJob { Job_1, Job_2, Job_3 };

		CLoopStride();

		CLoopStride(WhichJob whichJob);

		virtual ~CLoopStride() override;

		virtual void doJob() override;

		virtual winrt::hstring showResult() override;

	private:
		void doJob_1();

		void doJob_2();

		/// <summary>
		/// Iterate a 1024*512 matrix by row and by column.
		/// After it finished, m_dwCnt_1 will be the time of iterating by row,
		/// and m_dwCnt_2 will be the time of iterating by column.
		/// </summary>
		void doJob_3();

		const WhichJob whichJob;
		DWORD   m_dwCnt_1;
		DWORD   m_dwCnt_2;

		static constexpr int row = 1024;
		static constexpr int col = 512;
		unsigned matrix[row][col]; // matrix is used in doJob_3
	};

}