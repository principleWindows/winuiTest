#pragma once

#include "MainPage.g.h"
#include "BgLabelControl.h"

namespace winrt::winuiTest::implementation
{
    class CMgrThreads;
    class CJob;
    struct MainPage : MainPageT<MainPage>
    {
        MainPage ( );
        ~MainPage ( );

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void Button2_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);

        CMgrThreads *   m_pMgr;
        CJob *          m_pJob;
    };
}

namespace winrt::winuiTest::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
