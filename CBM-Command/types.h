/**
 * Type definitions for existing memory layouts.
 * These structs overlay existing global buffers exactly.
 * NO NET RAM INCREASE PERMITTED.
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#pragma pack(push, 1)

/**
 * Drive state struct.
 * Overlays existing global drive buffer.
 * Memory layout matches exactly.
 */
struct Drive {
    uint8_t  number;
    uint8_t  type;
    uint16_t blocksFree;
    uint8_t  status[16];
    uint8_t  name[16];
    uint8_t  id[2];
};

/**
 * Directory entry.
 * Exact 32 byte CBM directory entry layout.
 */
struct FileEntry {
    uint8_t  nextTrack;
    uint8_t  nextSector;
    uint8_t  fileType;
    uint8_t  name[16];
    uint16_t blocks;
    uint8_t  reserved[12];
};

/**
 * Panel state.
 * Overlays existing panel buffers.
 */
struct Panel {
    uint8_t     currentDrive;
    uint16_t    entryCount;
    uint16_t    selectedIndex;
    uint16_t    scrollOffset;
    struct FileEntry entries[30];
};

#pragma pack(pop)

#endif /* TYPES_H */