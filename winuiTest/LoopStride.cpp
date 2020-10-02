#include "pch.h"
#include "LoopStride.h"

using namespace winrt;
using namespace winuiTest;
using namespace winuiTest::implementation;

// https://manybutfinite.com/post/intel-cpu-caches/

void CLoopStride::doJob ( )
{
	DWORD	dwCnt;

	const int LEN	= 64 * 1024 * 1024;
	int* arr		= new int[LEN];

	m_dwCnt_1	= GetTickCount ( );

	for (int i = 0; i < LEN; i += 2) arr[i] *= i;

	m_dwCnt_2	= GetTickCount ( );
	m_dwCnt_1	= m_dwCnt_2 - m_dwCnt_1;

	for (int i = 0; i < LEN; i += 8) arr[i] *= i;

	m_dwCnt_2	= GetTickCount ( ) - m_dwCnt_2;

	m_bDone	= true;
}

CLoopStride::CLoopStride ( )
{
}

CLoopStride::~CLoopStride ( )
{
}

void CLoopStride::showResult ( winrt::hstring& strResult )
{
//	winrt::hstring	str;
//	std::string	str;

//	strResult	= to_hstring ( m_dwCnt_1 );
//	strResult	= view;
}

//#define	size	1, 16, 512, 1024
// STRIDE from 1 to 16
#define	STRIDE	4
void CLoopStride::doJob_2 ( )
{
	int		memory[65535];
	int		size = 512;

	m_dwCnt_2 = GetTickCount();

	for (int i = 0; i < 10000000; i++)	// ten millions iteration
	{
		for (int j = 0; j < size; j += STRIDE) // size * STRIDE
		{
			memory[j] += j;
		}
	}

	m_dwCnt_2 = GetTickCount() - m_dwCnt_2;

	m_bDone = true;
}

void CLoopStride::doJob_3 ( )
{
	const int row = 1024;
	const int col = 512;
	int matrix[row][col];

	DWORD	dwCnt;

	m_dwCnt_1 = GetTickCount();

	// 逐行遍历
	int sum_row=0;
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < col; c++) {
			sum_row += matrix[r][c];
		}
	}

	m_dwCnt_2 = GetTickCount();
	m_dwCnt_1 = m_dwCnt_2 - m_dwCnt_1;

	// 逐列遍历
	int sum_col=0;
	for (int c = 0; c < col; c++) {
		for (int r = 0; r < row; r++) {
			sum_col += matrix[r][c];
		}
	}

	m_dwCnt_2 = GetTickCount() - m_dwCnt_2;

	m_bDone = true;
}

