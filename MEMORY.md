# CBM-Command Runtime Memory Baselines

Official runtime RAM footprints measured after program initialization.
These values are enforced on every PR. No increases permitted.

| Platform | Free RAM at startup | Stack size | Zero Page used |
|----------|---------------------|------------|----------------|
| C64      | 1147 bytes          | 1024 bytes | 12 bytes       |
| C128     |  983 bytes          | 1024 bytes | 12 bytes       |
| PET      | 1536 bytes          | 1024 bytes | 12 bytes       |
| VIC-20   |  768 bytes          |  512 bytes | 12 bytes       |
| Plus/4   | 1280 bytes          | 1024 bytes | 12 bytes       |

## Measurement Procedure

1. Load program in VICE x64sc / x128 / xpet / xvic / xplus4
2. Execute to main menu entry point `0x080d`
3. Measure memory from end of program to stack bottom
4. Subtract stack allocation
5. Result = free user RAM available

All measurements are automated via `vice-test-runner`. CI will fail any PR that reduces free RAM on any platform.