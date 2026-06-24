cmake_minimum_required(VERSION 3.20)
project(CleanQuake CXX)

# Set standard C++ flags
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add SDL definition
add_compile_definitions(SDL)

# Fetch SDL2
include(FetchContent)
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.3
)
# Disable unnecessary SDL2 features for faster build
set(SDL_TEST OFF CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SDL2)

# Gather source files
set(CORE_SRCS
    src/cd_sdl.cpp
    src/chase.cpp
    src/cl_demo.cpp
    src/cl_input.cpp
    src/cl_main.cpp
    src/cl_parse.cpp
    src/cl_tent.cpp
    src/cmd.cpp
    src/common.cpp
    src/console.cpp
    src/crc.cpp
    src/cvar.cpp
    src/d_edge.cpp
    src/d_fill.cpp
    src/d_init.cpp
    src/d_modech.cpp
    src/d_part.cpp
    src/d_polyse.cpp
    src/d_scan.cpp
    src/d_sky.cpp
    src/d_sprite.cpp
    src/d_surf.cpp
    src/d_vars.cpp
    src/d_zpoint.cpp
    src/draw.cpp
    src/host.cpp
    src/host_cmd.cpp
    src/keys.cpp
    src/mathlib.cpp
    src/menu.cpp
    src/model.cpp
    src/net_bsd.cpp
    src/net_dgrm.cpp
    src/net_loop.cpp
    src/net_main.cpp
    src/net_udp.cpp
    src/net_vcr.cpp
    src/pr_cmds.cpp
    src/pr_edict.cpp
    src/pr_exec.cpp
    src/r_aclip.cpp
    src/r_alias.cpp
    src/r_bsp.cpp
    src/r_draw.cpp
    src/r_edge.cpp
    src/r_efrag.cpp
    src/r_light.cpp
    src/r_main.cpp
    src/r_misc.cpp
    src/r_part.cpp
    src/r_sky.cpp
    src/r_sprite.cpp
    src/r_surf.cpp
    src/r_vars.cpp
    src/sbar.cpp
    src/screen.cpp
    src/snd_dma.cpp
    src/snd_mem.cpp
    src/snd_mix.cpp
    src/snd_sdl.cpp
    src/sv_main.cpp
    src/sv_move.cpp
    src/sv_phys.cpp
    src/sv_user.cpp
    src/sys_sdl.cpp
    src/vid_sdl.cpp
    src/view.cpp
    src/wad.cpp
    src/world.cpp
    src/zone.cpp
)

add_executable(clean-quake ${CORE_SRCS})

target_include_directories(clean-quake PRIVATE src)

# Link SDL2 and Windows libraries
target_link_libraries(clean-quake PRIVATE SDL2main SDL2-static ws2_32 winmm)

# Suppress some old C warnings for cleaner output
if(MSVC)
    # Compiler flags
    target_compile_options(clean-quake PRIVATE 
        /W4          # Crank up warning level to catch unused variables/parameters
        /Gy          # Function-level linking (allows linker to discard individual functions)
        /Gw          # Optimize global data (allows linker to discard unused globals)
        # Keep your existing suppressions for now so you aren't overwhelmed
        /wd4996 /wd4244 /wd4113 /wd4047 /wd4024
    )
    
    # Linker flags
    target_link_options(clean-quake PRIVATE 
        /OPT:REF     # Tell the linker to eliminate unreferenced functions and data
        /VERBOSE:REF # Tell the linker to print out exactly what it deleted
    )
else()
    # Compiler flags
    target_compile_options(clean-quake PRIVATE 
        -Wall -Wextra -Wunused      # Maximum warnings for unused variables/functions
        -ffunction-sections         # Place each function in its own section
        -fdata-sections             # Place each data item in its own section
        -Wno-write-strings          # Keep your existing suppression
    )
    
    # Linker flags
    if(APPLE)
        # macOS uses a different linker that doesn't support --gc-sections
        target_link_options(clean-quake PRIVATE 
            -Wl,-dead_strip         # Strip dead code on macOS
            -Wl,-why_live,main      # (Optional) Map analysis if needed later
        )
    else()
        # GCC/Clang on Linux/MinGW
        target_link_options(clean-quake PRIVATE 
            -Wl,--gc-sections       # Garbage collect empty sections (dead code)
            -Wl,-print-gc-sections  # Print everything the linker throws away
        )
    endif()
endif()
