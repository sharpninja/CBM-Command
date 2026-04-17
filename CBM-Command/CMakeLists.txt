cmake_minimum_required(VERSION 3.25)
project(CBM-Command C ASM)

# CC65 Toolchain Configuration
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR 6502)

find_program(CC65_CL65 cl65)
find_program(CC65_CA65 ca65)
find_program(CC65_AR65 ar65)
find_program(CC65_RANLIB ranlib65)

if(NOT CC65_CL65)
    message(FATAL_ERROR "cl65 not found. Install CC65 toolchain.")
endif()

set(CMAKE_C_COMPILER ${CC65_CL65})
set(CMAKE_ASM_COMPILER ${CC65_CA65})
set(CMAKE_AR ${CC65_AR65})
set(CMAKE_RANLIB ${CC65_RANLIB})

# Platform Targets
set(PLATFORMS c64 c128 pet plus4 vic20)

# Common Sources
set(CONFIG_SOURCES
    src/core/Configuration.c
    src/core/ConfigurationManager.c
    src/core/globalInput.c
    src/core/globals.c
    src/ui/screen.c
)

set(MAIN_SOURCES
    src/core/CBM-Command.c
    src/core/CBM-REL.c
    src/core/builtStamp.c
    src/menus/CommandMenu.c
    src/menus/DriveMenu.c
    src/menus/FileMenu.c
    src/menus/OptionMenu.c
    src/drivers/drives.c
    src/ui/input.c
    src/ui/menus.c
    src/ui/screen.c
    src/ui/Viewer.c
)

set(ASM_COMMON
    res/common/driveRoutines.s
    cc65/common/_printf.s
)

set(LIB_SOURCES
    cc65/common/strcat.s
    cc65/cbm/cbm_dir.c
    cc65/cbm/cbm_open.s
    cc65/cbm/cbm_read.s
    cc65/cbm/cclear.s
    cc65/cbm/chline.s
    cc65/cbm/cvline.s
    cc65/conio/cputs.s
    cc65/conio/callgoto.s
)

# Build flags
set(CMAKE_C_FLAGS "-Or -Wl -D__STACKSIZE__=$$400")

# Per platform build
foreach(PLATFORM ${PLATFORMS})
    string(TOUPPER ${PLATFORM} PLATFORM_UPPER)

    add_executable(cbmcommand_${PLATFORM} ${MAIN_SOURCES} ${ASM_COMMON} res/${PLATFORM}/PlatformSpecific.s)
    set_target_properties(cbmcommand_${PLATFORM} PROPERTIES COMPILE_FLAGS "-t ${PLATFORM}")
    set_target_properties(cbmcommand_${PLATFORM} PROPERTIES OUTPUT_NAME "cbmcommand.${PLATFORM}")

    add_executable(cbmcmdcfg_${PLATFORM} ${CONFIG_SOURCES} res/${PLATFORM}/PlatformSpecific.s)
    set_target_properties(cbmcmdcfg_${PLATFORM} PROPERTIES COMPILE_FLAGS "-t ${PLATFORM}")
    set_target_properties(cbmcmdcfg_${PLATFORM} PROPERTIES OUTPUT_NAME "cbmcmdcfg.${PLATFORM}")
endforeach()

# PET has 40/80 column variants
add_executable(cbmcommand_pet80 ${MAIN_SOURCES} ${ASM_COMMON} res/pet/PlatformSpecific.s)
set_target_properties(cbmcommand_pet80 PROPERTIES COMPILE_FLAGS "-t pet -D_PET80_")
set_target_properties(cbmcommand_pet80 PROPERTIES OUTPUT_NAME "cbmcommand.pet80")

add_executable(cbmcmdcfg_pet80 ${CONFIG_SOURCES} res/pet/PlatformSpecific.s)
set_target_properties(cbmcmdcfg_pet80 PROPERTIES COMPILE_FLAGS "-t pet -D_PET80_")
set_target_properties(cbmcmdcfg_pet80 PROPERTIES OUTPUT_NAME "cbmcmdcfg.pet80")

# D64/D80 Image targets
add_custom_target(D64 DEPENDS cbmcommand_c64 cbmcommand_c128 cbmcommand_vic20 cbmcommand_plus4)
add_custom_target(D80 DEPENDS cbmcommand_c64 cbmcommand_c128 cbmcommand_vic20 cbmcommand_plus4 cbmcommand_pet cbmcommand_pet80)