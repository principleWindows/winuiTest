#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

#include "MgrThreads.h"
#include "LoopStride.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::winuiTest;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::winuiTest::implementation
{
	MainPage::MainPage()
	{
		InitializeComponent();
	}

    MainPage::~MainPage ( )
    {
        CMgrThreads::shutdown();
    }

    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainPage::doJobsButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        if (job1 == nullptr && job2 == nullptr && job3 == nullptr)
        {
            job1 = std::make_unique<CLoopStride>(CLoopStride::Job_1);
            job2 = std::make_unique<CLoopStride>(CLoopStride::Job_2);
            job3 = std::make_unique<CLoopStride>(CLoopStride::Job_3);

            CMgrThreads::getMgr()->addJob(job1.get());
            CMgrThreads::getMgr()->addJob(job2.get());
            CMgrThreads::getMgr()->addJob(job3.get());

            resultTxt().Text(L"Three jobs begin to run.\nClick \"show result\" later to view results.");
            doJobsButton().IsEnabled(false);
            showResultButton().IsEnabled(true);
        }
    }

    void MainPage::showResultButton_Click(IInspectable const& /*sender*/, RoutedEventArgs const& /*e*/)
    {
        if (job1 != nullptr && job2 != nullptr && job3 != nullptr)
        {
            if (job1->m_bDone && job2->m_bDone && job3->m_bDone)
            {
                hstring result1 = job1->showResult();
                hstring result2 = job2->showResult();
                hstring result3 = job3->showResult();

                resultTxt().Text(L"[Result of Job1]\n" + result1 + L"\n\n[Result of Job2]\n" + result2 + L"\n\n[Result of Job3]\n" + result3);

                job1.release();
                job2.release();
                job3.release();

                showResultButton().IsEnabled(false);
                doJobsButton().IsEnabled(true);
            }
            else
            {
                resultTxt().Text(L"Not finished! Please click the button latter.");
            }
        }
    }
}
