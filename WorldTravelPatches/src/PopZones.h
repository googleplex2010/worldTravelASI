#pragma once
#include <cstdint>
#include <string>
#include <MinHook.h>
#include "Hooking.h"
#include "Hooking.Patterns.h"
#include "spdlog/spdlog.h"

class PopZones
{
public:
    static void Patch()
    {
        {
            spdlog::info("PopZones: trying pattern 1 (CommandGetZonePopSchedule)");
            auto p = hook::pattern("E8 ? ? ? ? 0F BE 40 06 EB 09 E8 ? ? ? ? 0F BE 40 05");
            size_t n = p.size();
            spdlog::info("PopZones: pattern 1 found {} matches", n);
            if (n != 1) { spdlog::error("PopZones: pattern 1 BROKEN, expected 1 match"); return; }
            uint8_t* location = p.get(0).get<uint8_t>(0);
            hook::put<uint8_t>(location + 6, 182);
            hook::put<uint8_t>(location + 17, 182);
            spdlog::info("PopZones: pattern 1 patched OK");
        }
        {
            spdlog::info("PopZones: trying pattern 2 (UpdateCurrZoneFromCoors A)");
            auto p = hook::pattern("0F BE 54 88 ? EB ? 41 B8 ? ? ? ? E8");
            size_t n = p.size();
            spdlog::info("PopZones: pattern 2 found {} matches", n);
            if (n != 1) { spdlog::error("PopZones: pattern 2 BROKEN, expected 1 match"); return; }
            uint8_t* location = p.get(0).get<uint8_t>(0);
            hook::put<uint8_t>(location + 1, 182);
            spdlog::info("PopZones: pattern 2 patched OK");
        }
        {
            spdlog::info("PopZones: trying pattern 3 (UpdateCurrZoneFromCoors B)");
            auto p = hook::pattern("0F BE 54 88 ? EB 02 8B D3 89 15");
            size_t n = p.size();
            spdlog::info("PopZones: pattern 3 found {} matches", n);
            if (n != 1) { spdlog::error("PopZones: pattern 3 BROKEN, expected 1 match"); return; }
            uint8_t* location = p.get(0).get<uint8_t>(0);
            hook::put<uint8_t>(location + 1, 182);
            spdlog::info("PopZones: pattern 3 patched OK");
        }
    }
};
