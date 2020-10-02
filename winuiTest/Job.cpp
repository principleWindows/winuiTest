#include "pch.h"
#include "Job.h"

using namespace winrt;
using namespace winuiTest;
using namespace winuiTest::implementation;

CJob::CJob ( )
{
	pNext	= nullptr;

	m_bDone	= false;
}

CJob::~CJob ( )
{
}
