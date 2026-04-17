# Contributing to CBM-Command

## The Rule

**RUNTIME RAM FOOTPRINT MAY NEVER INCREASE ON ANY PLATFORM.**

This is non-negotiable. All other constraints are relaxed.

✅ **Permitted:**
- Larger PRG file on disk
- More functions
- More code
- Better comments
- Refactoring
- Bug fixes
- New features that reuse existing buffers

❌ **Forbidden:**
- Any change that reduces free RAM after program load
- New globals
- New static buffers
- Increased stack usage
- Additional zero page allocation

## Workflow

1. Fork the repository
2. Make your changes
3. Build all targets
4. Run RAM verification:
   ```
   cd vice-test-runner
   vicetest verify baselines/c64.json ../build/cbmcommand.c64.prg
   vicetest verify baselines/c128.json ../build/cbmcommand.c128.prg
   ```
5. Attach verification output to your PR
6. Submit PR with all checklist items completed

## Code Style

- 4 space indentation
- No tabs
- LF line endings
- ANSI C89
- CC65 extensions permitted
- All public functions require documentation

## CI

All PRs automatically run:
- Full build for all 5 platforms
- RAM footprint verification
- Static analysis

CI will fail immediately on any RAM regression.