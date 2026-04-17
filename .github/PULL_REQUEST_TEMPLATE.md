# Pull Request Checklist

✅ **ALL ITEMS REQUIRED BEFORE MERGE**

## RAM Verification
- [ ] No runtime RAM increase on any platform
- [ ] `vicetest verify` passes locally for all targets
- [ ] VICE memory dump comparison attached
- [ ] Map file analysis included

## Changes
- [ ] Description of change provided
- [ ] No feature creep
- [ ] No new globals or buffers allocated
- [ ] Existing buffers reused where possible

## Build
- [ ] All 5 platforms build successfully
- [ ] No compiler warnings introduced

## Notes
PRG file size increases are permitted and expected.
Only runtime RAM footprint is enforced.