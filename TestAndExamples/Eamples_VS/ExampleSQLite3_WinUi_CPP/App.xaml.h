#pragma once

#include "App.xaml.g.h"

namespace winrt::ExampleSQLite3_WinUi_CPP::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

    private:
        winrt::Microsoft::UI::Xaml::Window window{ nullptr };
    };
}
