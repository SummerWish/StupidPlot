#pragma once

#include <windows.h>
#include <string>

#include <ui/event/event.h>

namespace StupidPlot
{
    namespace UI
    {
        namespace Event
        {
            class RawEvent : public Event
            {
            public:
                UINT        uMsg;
                WPARAM      wParam;
                LPARAM      lParam;

                RawEvent(UINT _uMsg, WPARAM _wParam, LPARAM _lParam) : Event(L"RawEvent")
                {
                    uMsg = _uMsg;
                    wParam = _wParam;
                    lParam = _lParam;
                }
            };
        }
    }
}