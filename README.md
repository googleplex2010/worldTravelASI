# World Travel ASI Fork

   Fork of [WorldTravelTeam/ASI](https://github.com/WorldTravelTeam/ASI) with fixes for GTA V build 3751+ (April 2026).

   The original mod was discontinued in January 2025. This fork applies fixes
   needed to keep the mod working with newer game builds.

   ## Changes from upstream

   - **`WorldTravelPatches/src/PopZones.h`**: Loosened pattern 2's jump-distance
     byte from `EB 5F` to `EB ?` for GTA V build 3751+. Rockstar inserted ~4 bytes
     of code in the branch target between the original and current build, shifting
     the jump distance.
   - **`WorldTravelPatches/src/PopZones.h`**: Added per-pattern diagnostic logging
     using `sprintf_s`-based message formatting (the bundled spdlog version's `{}`
     placeholders fail silently). Each pattern now logs match count and patch result.
   - **`WorldTravelPatches/src/PopZones.h`**: Replaced fail-fast assertions with
     graceful logging and skip behavior. A broken pattern no longer kills the entire
     init thread, so subsequent patches still install.
   - **`WorldTravel/src/Minimap.cpp`**: Same diagnostic + graceful-failure treatment
     applied to both minimap pattern hooks.

   ## Known issues (not fixed)

   - **Live HUD minimap renders transparent in Liberty City.** Pause map is fine.
     Cause: the `v_fakelibertycity` interior trigger present in the January 2025
     binary release was removed from the May 2025 source. Restoring requires
     reverse-engineering the original binary's use of that string and reimplementing
     the missing function.
   - **LSPDFR logs "No game zone found" warnings at LC coordinates.** Cause: GTA V's
     named-zone system appears to be hardcoded in the executable; LCPP includes no
     named-zone metadata for Liberty City. Fix would require an ASI-level hook on
     `GAMEPLAY::GET_NAME_OF_ZONE` to map LC coordinates to zone codes from
     popzone.ipl. Cosmetic-only impact.

   ## Building

   1. Open `WorldTravelPatches/src/WorldTravelPatches.sln` (or
      `WorldTravel/src/WorldTravel.sln`) in Visual Studio 2022
   2. Right-click solution → Retarget Solution → pick installed Windows SDK
   3. Set configuration to Release / x64
   4. Build (Ctrl+Shift+B)
   5. Output ASI lands in `bin/x64/Release/`
