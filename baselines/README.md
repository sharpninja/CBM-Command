# RAM Baselines

These are official runtime RAM footprint signatures.
These files are automatically verified on every PR.

**DO NOT MODIFY WITHOUT FULL VERIFICATION**

All baselines captured using:
```
vicetest capture baselines/c64.json build/cbmcommand.c64.prg 0x080d
```

CI will fail any PR that reduces available RAM on any platform.
RAM improvements (higher free bytes) are permitted and encouraged.