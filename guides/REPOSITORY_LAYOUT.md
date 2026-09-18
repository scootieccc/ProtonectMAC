# Repository layout

The cleanup strategy for ProtonectMAC is deliberately conservative: simplify the repository around the source tree instead of moving build-sensitive files for cosmetic reasons.

## Canonical structure

```text
ProtonectMAC/
├── .github/             GitHub issue/PR templates
├── assets/
│   └── branding/        Project logo and icon
├── cmake_modules/       Custom CMake modules
├── depends/             Dependency helpers and notices
├── doc/                 Doxygen input used by CMake
├── examples/            Protonect and viewer examples
├── guides/              Human-facing project documentation
├── include/             Public/internal headers
├── platform/            Platform-specific support
├── src/                 Library implementation and shaders
├── tools/               Auxiliary utilities
├── CMakeLists.txt       Top-level build definition
└── README.md            Project entry point
```

## Why core folders were not renamed

The source snapshot has direct CMake references to paths such as `include/`, `src/`, `doc/`, `examples/`, and `tools/`. Renaming them solely to make the tree look different would create a large, low-value patch and increase the chance of broken includes, packaging rules, documentation generation, or downstream scripts.

The optimized structure therefore adds only two top-level concepts:

- `assets/` for repository-facing visual identity.
- `guides/` for human documentation that should not be confused with `doc/`, which is the Doxygen build input.

## Generated documentation

Generated API HTML belongs on `gh-pages`, not in the source branch. The source branch should contain only the Doxygen configuration/input needed to regenerate it.

The current repository still uses `gh-pages` for historical generated documentation. `master` is the canonical source branch.

## Future cleanup candidates

If the project is actively modernized rather than preserved as a historical snapshot, do these as separate, testable changes:

1. Modernize the minimum CMake version and target-based dependency wiring.
2. Add macOS CI for Intel/arm64-compatible dependency configurations.
3. Decide whether legacy Windows/Linux helper scripts still belong in this Mac-focused mirror.
4. Regenerate `gh-pages` from CI instead of editing generated HTML directly.
5. Change the repository default branch from `gh-pages` to the canonical source branch in GitHub repository settings.

Keeping those tasks separate makes regressions easier to isolate and keeps this cleanup reviewable.
