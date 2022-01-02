#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef GETHARDWARE_H
#define GETHARDWARE_H

    typedef char* (*getCPUNameFunc)();
    typedef char* (*getCPUTemperatureFunc)();
    typedef char* (*getCPUClockFunc)();
    typedef char* (*getCPULoadFunc)();
    typedef char* (*getCPUPowerFunc)();
    typedef char* (*getMainBoardFunc)();
    typedef char* (*getPCNameFunc)();
    typedef char* (*getSuperIOFunc)();
    typedef char* (*getIOVoltageFunc)();
    typedef char* (*getIOTemperatureFunc)();
    typedef char* (*getIOFanFunc)();
    typedef char* (*getIOFanControlFunc)();
    typedef char* (*getNvidiaGPUNameFunc)();
    typedef char* (*getNvidiaGPUClockFunc)();
    typedef char* (*getNvidiaGPUTemperatureFunc)();
    typedef char* (*getNvidiaGPULoadFunc)();
    typedef char* (*getNvidiaGPUControlFunc)();
    typedef char* (*getNvidiaGPUDataFunc)();
    typedef char* (*getAtiGPUNameFunc)();
    typedef char* (*getAtiGPUClockFunc)();
    typedef char* (*getAtiGPUTemperatureFunc)();
    typedef char* (*getAtiGPULoadFunc)();
    typedef char* (*getAtiGPUControlFunc)();
    typedef char* (*getAtiGPUVoltageFunc)();
    typedef char* (*getHDDNameFunc)();
    typedef char* (*getHDDTemperatureFunc)();
    typedef char* (*getHDDLoadFunc)();
    typedef char* (*getHDDDataFunc)();

    typedef char* (*getHDDInfoFunc)();
    typedef char* (*getCPUInfoFunc)();
    typedef char* (*getIOInfoFunc)();
    typedef char* (*getAtiGPUInfoFunc)();
    typedef char* (*getNvidiaGPUInfoFunc)();

    getCPUNameFunc getCPUName;
    getCPUTemperatureFunc getCPUTemperature;
    getCPUClockFunc getCPUClock;
    getCPULoadFunc getCPULoad;
    getCPUPowerFunc getCPUPower;
    getMainBoardFunc getMainBoard;
    getPCNameFunc getPCName;
    getSuperIOFunc getSuperIO;
    getIOVoltageFunc getIOVoltage;
    getIOTemperatureFunc getIOTemperature;
    getIOFanFunc getIOFan;
    getIOFanControlFunc getIOFanControl;
    getNvidiaGPUNameFunc getNvidiaGPUName;
    getNvidiaGPUClockFunc getNvidiaGPUClock;
    getNvidiaGPUTemperatureFunc getNvidiaGPUTemperature;
    getNvidiaGPULoadFunc getNvidiaGPULoad;
    getNvidiaGPUControlFunc getNvidiaGPUControl;
    getNvidiaGPUDataFunc getNvidiaGPUData;
    getAtiGPUNameFunc getAtiGPUName;
    getAtiGPUClockFunc getAtiGPUClock;
    getAtiGPUTemperatureFunc getAtiGPUTemperature;
    getAtiGPULoadFunc getAtiGPULoad;
    getAtiGPUControlFunc getAtiGPUControl;
    getAtiGPUVoltageFunc getAtiGPUVoltage;
    getHDDNameFunc getHDDName;
    getHDDTemperatureFunc getHDDTemperature;
    getHDDLoadFunc getHDDLoad;
    getHDDDataFunc getHDDData;

    getHDDInfoFunc getHDDInfo;
    getCPUInfoFunc getCPUInfo;
    getAtiGPUInfoFunc getAtiGPUInfo;
    getNvidiaGPUInfoFunc getNvidiaGPUInfo;
    getIOInfoFunc getIOInfo;

#endif // GETHARDWARE_H

