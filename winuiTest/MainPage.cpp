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
    MainPage::MainPage ( )
    {
        InitializeComponent();

        m_pJob  = nullptr;

        m_pMgr  = CMgrThreads::getMgr ( );
        m_pMgr->createAllWorkThreads ( );
    }

    MainPage::~MainPage ( )
    {
        delete  CMgrThreads::getMgr ( );
    }

    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainPage::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
        myLabel().Label(L"yes!");

        if ( m_pJob != nullptr )    delete  m_pJob;
        m_pJob    = new CLoopStride;

        m_pMgr->addJob ( m_pJob );
    }

    void MainPage::Button2_Click(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& /*e*/)
    {
        winrt::hstring   strResult;

        myButton().Content(box_value(L"button2 Clicked"));

        if ( m_pJob != nullptr )    return;

        if ( !m_pJob->m_bDone )
        {
            myLabel().Label(L"Not finished!");

            return;
        }

        m_pJob->showResult ( strResult );

        myLabel().Label(strResult);
    }
}
