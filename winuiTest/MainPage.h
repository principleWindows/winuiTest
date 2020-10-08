#pragma once

#include <memory>
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

        void doJobsButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void showResultButton_Click(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& e);

        std::unique_ptr<CJob> job1, job2, job3;
    };
}

namespace winrt::winuiTest::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
