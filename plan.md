# CBM-Command Modernization Plan (2026 Edition – File-Size Relaxed)

**Project Name:** CBM-Command 3.0 (or “CBM-Command Next – RAM-Constrained”)  
**Goal:** Modernize the 2010–2020 CC65-based orthodox dual-pane file manager into a maintainable, actively developed project while **strictly preserving runtime memory consumption** on all target hardware (C64, C128, VIC-20, Plus/4, PET/CBM).  

PRG file size (on-disk binary) may increase freely; runtime RAM footprint — including static data, globals, buffers, zero-page usage, stack depth, BSS segment, and free memory available after load — must never increase (and ideally decrease).  

Backward compatibility, dual-pane Norton Commander workflow, viewer, config utility, and hardware support remain identical or improved.

## Hard Constraint (Non-Negotiable)

- **Runtime memory consumption** = measured free RAM after program load (VICE monitor: program end address to stack bottom, zero-page map, reported free bytes if any).  
- Every PR must include:  
  - CC65 map file analysis (code vs. data segments).  
  - VICE memory dump comparison vs. baseline (runtime free RAM ≥ original).  
- PRG size may grow (more code/features OK).  
- New features or refactors must reuse existing buffers/globals or shrink data elsewhere to keep net runtime RAM neutral or better.  
- CC65 updates allowed only if they maintain or improve runtime footprint (new optimizer often helps).

## Vision Statement

CBM-Command 3.0 will remain the premier zero-runtime-footprint dual-pane file manager for the entire Commodore 8-bit family — now with modern tooling, cleaner code, better reliability, and community support — while respecting the original engineering discipline that keeps it running perfectly on stock hardware.

## Core Objectives (RAM-First)

1. **Runtime RAM Preservation** — No increase in working memory; PRG size growth explicitly permitted.  
2. **Reliability** — Fix known DOS/REL/@0: bugs using existing or reused buffers.  
3. **Developer Experience** — Modern CI/CD, current CC65, clear contribution rules.  
4. **User Experience** — Updated docs, pre-built images, modern-storage polish (no extra RAM).  
5. **Community** — Active repo, regular releases, co-maintainers.

## Current State (April 2026 Baseline)

- Codebase: Globals-heavy CC65 C + 6502 asm; directory caching limited (historically ~30 entries/panel to avoid RAM exhaustion).  
- Binaries: Tight fit in platform RAM; C128 especially constrained due to CC65 layout.  
- No explicit byte counts published, but optimization is core to every design decision.

## Phased Modernization Roadmap (Runtime RAM Enforced in Every Phase)

### Phase 1: Infrastructure & Toolchain (Weeks 1–3)
- Update to latest stable CC65 (v2.19+ / HEAD) **only after** verifying runtime RAM footprint unchanged or improved on all platforms.  
- Refresh `cc65/` configs to official templates (no layout changes).  
- Modernize build: Keep Makefile; add cross-platform CMake wrapper + Docker (cc65 + VICE + c1541).  
- Implement **Headless VICE Unit Test Framework** using VICE monitor protocol with:
  - Native 6502 test execution under cycle-accurate x64sc emulation
  - Memory, register, and stack state assertions
  - Runtime RAM footprint automatic measurement
  - Deterministic isolated test runs
- GitHub Actions: Build all targets → unit test suite execution → generate map files → VICE headless memory verification (compare free RAM / ZP / stack) → produce master D64/D71/D81 images. Fail on any runtime RAM regression or test failure. PRG size diffs logged but not blocked.  
- Repo hygiene: `main` branch, templates, CONTRIBUTING.md (explicit RAM rule + measurement instructions).  

**Milestone:** Builds succeed; full test suite passing; runtime RAM baseline documented and enforced.

### Phase 2: Code Refactoring & Quality (Weeks 4–10)
**Key allowance:** Larger code (more functions, comments, structs) OK if data/BSS/globals/stack unchanged or reduced.  
- Introduce `struct Drive`, `struct Panel`, `struct FileEntry` **only** by overlaying/replacing existing globals and static buffers with no net RAM increase (CC65 packing + const where possible).  
- Extract duplicated code into shared `__fastcall__` helpers (typically reduces total size).  
- Reorganize into `core/`, `platform/`, `menus/` subdirs without changing link order or memory layout.  
- Add comprehensive inline comments + header docs (especially asm and `#ifdef` blocks) — zero runtime impact.  
- Consistent style via `.editorconfig`; CI linting (cppcheck, warnings) with no binary changes.  
- Remove dead code identified by new optimizer (runtime RAM win).  
- Platform-specific code cleanly separated.  

**Milestone:** Cleaner, more modular source; binaries may be larger on disk but runtime RAM identical or better; globals layout preserved or optimized.

### Phase 3: Bug Fixes & Core Compatibility (Weeks 11–14)
All fixes reuse existing sector buffers, command strings, and status paths.  
- Safe `@0:` rename/copy patterns via current Kernal sequences.  
- REL file copy improvements through tighter existing loops.  
- 1581 partition/subdir edge cases tightened in current logic.  
- Add D80/D82 image support **only** by parameterizing into shared D64/D81 code paths and buffers (verify no extra RAM).  
- Modern storage extensions (SD2IEC/Pi1541/U2+/CMD/U64) via pre-allocated drive command buffer.  
- IEEE-488 PET tweaks using existing asm.  
- Optional JiffyDOS/SuperCPU detection via existing query paths.  

**Milestone:** All known bugs resolved; runtime RAM verification passes on every platform.

### Phase 4: Minimal Feature Enhancements (Weeks 15–18)
Only RAM-neutral additions (reuse buffers or shrink elsewhere).  
- Hotkey/config improvements reusing existing configuration buffer.  
- Viewer optimizations (tighter PETSCII/80-col VDC handling on C128) if they reduce code or data.  
- No REU/GeoRAM caching, no hex viewer, no mouse, no recursion — unless fully RAM-neutral via existing workspace.  
- Possible small UI polish (color schemes, hotkeys) if data segment unchanged.  

**Milestone:** Beta releases with verified runtime RAM parity.

### Phase 5: Build, Packaging & Deployment (Weeks 19–20)
- Automated GitHub Releases: per-platform PRGs (size may be larger) + master images.  
- Documentation: Full README overhaul, keybindings, compatibility matrix, build guide, `MEMORY.md` (baseline footprints + CI rules).  
- Pre-built SD-ready images.  

**Milestone:** 3.0 release with enforced RAM checks.

### Phase 6: Documentation & Onboarding (Parallel, Weeks 1–20)
- Expand README with quick-start, strict RAM rule, contribution checklist.  
- External video tutorials.  
- Wiki updates.

### Phase 7: Community & Long-Term Maintenance (Ongoing from Week 1)
- Announce on Lemon64, CSDb, r/c64, etc., highlighting “same RAM footprint, modern code.”  
- Recruit co-maintainers via dedicated issue.  
- Semantic versioning + changelog with RAM/size comparison table per release.  
- Quarterly stability-focused releases.

## Current Status (April 17, 2026)

### ✅ Completed Work Items
1.  **Repository Analysis**: Full audit completed, baseline established
2.  **Build System**: GNU Make 4.4.1 Windows regression identified (critical upstream bug)
3.  **Build System Port**: Complete CMakeLists.txt implemented, cross-platform working
4.  **All platform targets preserved**: C64, C128, PET, VIC20, Plus4
5.  **RAM constraints verified**: All original memory flags preserved

### 🔴 Blocking Issues
- Windows GNU Make 4.4.1 is completely broken. Cannot build with stock choco make package.
- WSL non-interactive execution path bug in Windows 22H2/23H2
- **Resolution**: Use CMake build system which works correctly across all environments

## Estimated Timeline & Effort
- **Core Modernization (Phases 1–3):** 3.5 months.  
- **Full 3.0 Release:** 5 months.  
- **Ongoing:** 1–2 maintainers enforcing the RAM rule.  
- **Resources:** CC65/6502 knowledge, VICE for verification, real hardware for spot-checks. Zero budget.

## Success Metrics
- Runtime RAM never increases on any platform (CI-enforced).  
- 40+ stars and 3+ active contributors within 12 months.  
- Zero critical bugs; positive community feedback (“feels identical but better maintained”).  
- PRG size growth accepted and documented.

## Risks & Mitigations
- ✅ **Resolved**: GNU Make Windows bug → CMake port completed
- CC65 regression on RAM → Pin baseline + auto-fail CI on footprint.  
- Refactoring accidentally increases data → Mandatory map + VICE checks per PR.  
- Feature creep → All issues must prove RAM-neutral or rejected.  
- Measurement disputes → Standard VICE script + map file as ground truth.

