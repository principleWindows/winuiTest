#include "pch.h"
#include <algorithm>
#include "LoopStride.h"

using namespace winrt;
using namespace winuiTest;
using namespace winuiTest::implementation;

// https://manybutfinite.com/post/intel-cpu-caches/

void CLoopStride::doJob()
{
	if (whichJob == Job_1)
		doJob_1();
	else if (whichJob == Job_2)
		doJob_2();
	else
		doJob_3();
}

CLoopStride::CLoopStride()
	:whichJob(Job_1), m_dwCnt_1(0), m_dwCnt_2(0) {}

CLoopStride::CLoopStride(WhichJob whichJob)
	: whichJob(whichJob), m_dwCnt_1(0), m_dwCnt_2(0) {}


CLoopStride::~CLoopStride()
{
}

hstring CLoopStride::showResult()
{
	if (whichJob == Job_2)
		return L"time: " + to_hstring(uint32_t(m_dwCnt_2)) + L" ms";
	else
		return L"time1: " + to_hstring(uint32_t(m_dwCnt_1)) + L" ms"
		+ L"\ntime2: " + to_hstring(uint32_t(m_dwCnt_2)) + L" ms";
}

void CLoopStride::doJob_1()
{
	const int LEN = 64 * 1024 * 1024;
	unsigned *arr = new unsigned[LEN];
	std::fill_n(arr, LEN, 1);

	m_dwCnt_1 = GetTickCount();

	for (int i = 0; i < LEN; i += 2) arr[i] *= i;

	m_dwCnt_2 = GetTickCount();
	m_dwCnt_1 = m_dwCnt_2 - m_dwCnt_1;

	for (int i = 0; i < LEN; i += 8) arr[i] *= i;

	m_dwCnt_2 = GetTickCount() - m_dwCnt_2;

	m_bDone = true;
	delete[] arr;
}

//#define	size	1, 16, 512, 1024
// STRIDE from 1 to 16
#define	STRIDE	4
void CLoopStride::doJob_2()
{
	constexpr int LEN = 65535;
	unsigned *memory = new unsigned[LEN];
	std::fill_n(memory, LEN, 1);

	constexpr int size = 512;

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

void CLoopStride::doJob_3()
{
	std::fill_n(&matrix[0][0], row * col, 1);

	m_dwCnt_1 = GetTickCount();

	constexpr int iterTimes = 50;

	// 逐行遍历
	for (int t = 0; t < iterTimes; t++)
	{
		unsigned sum_row = 0;
		for (int r = 0; r < row; r++)
			for (int c = 0; c < col; c++)
				sum_row += matrix[r][c];
	}

	m_dwCnt_2 = GetTickCount();
	m_dwCnt_1 = m_dwCnt_2 - m_dwCnt_1;

	// 逐列遍历
	for (int t = 0; t < iterTimes; t++)
	{
		unsigned sum_col = 0;
		for (int c = 0; c < col; c++)
			for (int r = 0; r < row; r++)
				sum_col += matrix[r][c];
	}

	m_dwCnt_2 = GetTickCount() - m_dwCnt_2;

	m_bDone = true;
}

