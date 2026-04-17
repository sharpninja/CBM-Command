# Source Tree Layout

## Directories
| Directory | Purpose |
|---|---|
| `core/` | Globals, initialization, configuration, main loop |
| `ui/` | Screen drawing, input, menus, viewer |
| `menus/` | Individual menu implementations |
| `drivers/` | Drive I/O, directory listing, DOS commands |
| `platform/` | Platform specific code and hardware support |

## Link Order
Link order is preserved exactly as original to maintain memory layout. No changes are permitted to link order without full RAM verification.