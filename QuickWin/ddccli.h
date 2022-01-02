#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef DDCCLI_H
#define DDCCLI_H

/*

Copyright (c) 2018 Matt Hensman <m@matt.tf>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include "HighLevelMonitorConfigurationAPI.h"
#include "PhysicalMonitorEnumerationAPI.h"
#include <Windows.h>
#include <WinUser.h>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <array>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <iterator>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <QString>
#include <QDebug>

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "dxva2.lib")

namespace ddccli{
    using namespace std;
    struct MonitorBrightness {
        unsigned long maximumBrightness;
        unsigned long currentBrightness;
    };

    struct MonitorContrast {
        unsigned long maximumContrast;
        unsigned long currentContrast;
    };

    struct MonitorInfo {
        QString name;
        HANDLE handle;
    };

    std::vector<MonitorInfo> handles;

    void populateHandlesMap()
    {
        // Cleanup
        if (!handles.empty()) {
            for (auto const& handle : handles) {
                DestroyPhysicalMonitor(handle.handle);
            }
            handles.clear();
        }

        struct Monitor {
            HMONITOR handle;
            std::vector<HANDLE> physicalHandles;
        };

        auto monitorEnumProc = [](HMONITOR hMonitor,
                                  HDC hdcMonitor,
                                  LPRECT lprcMonitor,
                                  LPARAM dwData) -> BOOL {
            auto monitors = reinterpret_cast<std::vector<struct Monitor>*>(dwData);
            monitors->push_back({ hMonitor, {} });
            return TRUE;
        };
        std::vector<struct Monitor> monitors;

        EnumDisplayMonitors(
          NULL, NULL, monitorEnumProc, reinterpret_cast<LPARAM>(&monitors));
        // Get physical monitor handles
        for (auto& monitor : monitors) {
            DWORD numPhysicalMonitors;
            LPPHYSICAL_MONITOR physicalMonitors = NULL;
            if (!GetNumberOfPhysicalMonitorsFromHMONITOR(monitor.handle,
                                                         &numPhysicalMonitors)) {
                //throw std::runtime_error("Failed to get physical monitor count.");
                exit(EXIT_FAILURE);
            }

            physicalMonitors = new PHYSICAL_MONITOR[numPhysicalMonitors];
            if (physicalMonitors == NULL) {
                //throw std::runtime_error(
                //  "Failed to allocate physical monitor array");
            }

            if (!GetPhysicalMonitorsFromHMONITOR(
                  monitor.handle, numPhysicalMonitors, physicalMonitors)) {
                //throw std::runtime_error("Failed to get physical monitors.");
            }

            for (DWORD i = 0; i <= numPhysicalMonitors; i++) {
                monitor.physicalHandles.push_back(
                  physicalMonitors[(numPhysicalMonitors == 1 ? 0 : i)]
                    .hPhysicalMonitor);
            }

            delete[] physicalMonitors;
        }


        DISPLAY_DEVICE adapterDev;
        adapterDev.cb = sizeof(DISPLAY_DEVICE);

        // Loop through adapters
        int adapterDevIndex = 0;
        while (EnumDisplayDevices(NULL, adapterDevIndex++, &adapterDev, 0)) {
            DISPLAY_DEVICE displayDev;
            displayDev.cb = sizeof(DISPLAY_DEVICE);

            // Loop through displays (with device ID) on each adapter
            int displayDevIndex = 0;
            while (EnumDisplayDevices(adapterDev.DeviceName,
                                      displayDevIndex++,
                                      &displayDev,
                                      EDD_GET_DEVICE_INTERFACE_NAME)) {

                // Check valid target
                if (!(displayDev.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)
                    || displayDev.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER) {
                    continue;
                }

                for (auto const& monitor : monitors) {
                    MONITORINFOEX monitorInfo;
                    monitorInfo.cbSize = sizeof(MONITORINFOEX);
                    GetMonitorInfo(monitor.handle, &monitorInfo);

                    for (size_t i = 0; i < monitor.physicalHandles.size(); i++) {
                        /**
                         * Re-create DISPLAY_DEVICE.DeviceName with
                         * MONITORINFOEX.szDevice and monitor index.
                         */

                        QString monitorName = QString::fromWCharArray(monitorInfo.szDevice) + QString("\\Monitor") + QString::number(i);
                        QString deviceName = QString::fromWCharArray(displayDev.DeviceName);

                        // Match and store against device ID
                        if (monitorName == deviceName) {
                            MonitorInfo mi;
                            mi.name = QString::fromWCharArray(displayDev.DeviceID);
                            mi.handle = monitor.physicalHandles[i];
                            handles.push_back(mi);
                            break;
                        }
                    }
                }
            }
        }
    }

    MonitorBrightness getMonitorBrightness(HANDLE hMonitor)
    {
        DWORD minimumBrightness;
        DWORD maximumBrightness;
        DWORD currentBrightness;

        MonitorBrightness brightness ;

        if (!GetMonitorBrightness(hMonitor,
                                  &minimumBrightness,
                                  &currentBrightness,
                                  &maximumBrightness)) {
            brightness = {
                static_cast<unsigned long>(0),
                static_cast<unsigned long>(0)
            };
            //throw std::runtime_error("failed to get monitor brightness");
        }
        else{
            brightness = {
                static_cast<unsigned long>(maximumBrightness),
                static_cast<unsigned long>(currentBrightness)
            };
        }

        return brightness;
    }

    MonitorContrast getMonitorContrast(HANDLE hMonitor)
    {
        DWORD minimumContrast;
        DWORD maximumContrast;
        DWORD currentContrast;

        MonitorContrast contrast;

        if (!GetMonitorContrast(
              hMonitor, &minimumContrast, &currentContrast, &maximumContrast)) {
            contrast = { static_cast<unsigned long>(0),
                         static_cast<unsigned long>(0) };
            //throw std::runtime_error("failed to get monitor contrast");
        }
        else{
            contrast = { static_cast<unsigned long>(maximumContrast),
                         static_cast<unsigned long>(currentContrast) };
        }

        return contrast;
    }

    void setMonitorBrightness(HANDLE hMonitor, unsigned long level)
    {
        auto brightness = getMonitorBrightness(hMonitor);

        if (level > brightness.maximumBrightness) {
            qDebug()<<"brightness level exceeds maximum";
            //throw std::runtime_error("brightness level exceeds maximum");
        }

        if (!SetMonitorBrightness(hMonitor, static_cast<DWORD>(level))) {
            qDebug()<<"failed to set monitor brightness";
            //throw std::runtime_error("failed to set monitor brightness");
        }
    }

    void setMonitorContrast(HANDLE hMonitor, unsigned long level)
    {
        auto contrast = getMonitorContrast(hMonitor);

        if (level > contrast.maximumContrast) {
            qDebug()<<"contrast level exceeds maximum";
            //throw std::runtime_error("contrast level exceeds maximum");
        }

        if (!SetMonitorContrast(hMonitor, static_cast<DWORD>(level))) {
            qDebug()<<"failed to set monitor contrast";
            //throw std::runtime_error("failed to set monitor contrast");
        }
    }

}

#endif // DDCCLI_H
