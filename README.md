<p align="center">
  <img src="assets/branding/protonectmac-logo.svg" alt="ProtonectMAC" width="760">
</p>

<p align="center"><strong>Kinect v2 support for legacy Intel Macs — centered on macOS 10.15 Catalina and 2013 MacBook Pro-era hardware.</strong></p>

> **Compatibility target:** Intel (`x86_64`) Mac hardware running **macOS 10.15 Catalina**, with the **2013 MacBook Pro** as the reference use case. ProtonectMAC exists to keep Kinect v2 usable within the USB, driver, dependency, and operating-system constraints of that generation of Mac hardware.

## What is ProtonectMAC?

**ProtonectMAC** is a Mac-focused libfreenect2/Protonect repository built around a specific legacy-computing problem: using a **Kinect v2** on Intel MacBooks that are constrained to older macOS releases and older dependency/toolchain combinations.

The project is especially aimed at **2013 MacBook Pro hardware on macOS 10.15 Catalina**. Rather than treating that configuration as obsolete or incidental, ProtonectMAC documents it as the primary compatibility target.

The underlying driver source is based on **OpenKinect/libfreenect2** and provides RGB, infrared/depth transfer, and RGB/depth registration for Kinect v2-class hardware. ProtonectMAC preserves that upstream provenance while adding repository organization, branding, and guidance focused on legacy Intel Mac use.

### Scope

| Component | Target |
| --- | --- |
| CPU architecture | **Intel x86_64** |
| Primary OS | **macOS 10.15 Catalina** |
| Reference hardware | **2013 MacBook Pro** |
| Sensor | **Kinect v2 / Kinect for Windows v2** |
| Connection | **USB 3.x** via the powered Kinect adapter |
| Build system | CMake |
| Apple Silicon | **Not the primary target** |
| Current macOS releases | **Not the primary target** |

This repository is intentionally a **legacy compatibility project**, not a claim that the historical driver has been modernized for every current Mac configuration.

## Why this repository exists

A 2013 MacBook Pro can still be useful hardware, but using Kinect v2 on it means working inside several constraints at once:

- Intel-only hardware and an older macOS ceiling
- macOS 10.15 Catalina-era compiler and framework behavior
- dependency versions that may no longer match current package-manager defaults
- Kinect v2's strict USB 3.x bandwidth/isochronous-transfer requirements
- no reliance on Microsoft's Windows-only Kinect SDK stack

ProtonectMAC keeps the relevant libfreenect2 source, Protonect example, and Mac-specific setup information together so this exact class of machine remains practical to experiment with.

## Catalina quick start

### 1. Verify the Mac

```bash
sw_vers
uname -m
system_profiler SPHardwareDataType
```

The intended configuration reports **macOS 10.15.x** and **x86_64**.

### 2. Install build dependencies

You need CMake, pkg-config, libusb, GLFW, and optionally TurboJPEG. On an existing Catalina Homebrew setup, the package names are typically:

```bash
brew install cmake pkg-config libusb glfw jpeg-turbo
```

> Homebrew's current support policy and formula versions change over time. On Catalina, you may need versions compatible with the older OS rather than the newest available formulae.

### 3. Clone and build

```bash
git clone https://github.com/scootieccc/ProtonectMAC.git
cd ProtonectMAC

cmake -S . -B build \
  -DENABLE_CUDA=OFF \
  -DENABLE_VAAPI=OFF \
  -DENABLE_TEGRAJPEG=OFF

cmake --build build --parallel
```

### 4. Run Protonect

```bash
./build/bin/Protonect
```

If OpenCL creates configuration or runtime problems, rebuild with `-DENABLE_OPENCL=OFF` and use the CPU/OpenGL path instead.

For a more detailed setup and troubleshooting path, see **[guides/MACOS.md](guides/MACOS.md)** and **[guides/COMPATIBILITY.md](guides/COMPATIBILITY.md)**.

## Repository layout

The source tree is intentionally kept close to libfreenect2's working layout so CMake paths, includes, and historical assumptions are not broken just for cosmetic restructuring.

| Path | Purpose |
| --- | --- |
| `assets/branding/` | ProtonectMAC logo and visual assets |
| `cmake_modules/` | Custom CMake find/setup modules |
| `depends/` | Dependency helper scripts and third-party notices |
| `doc/` | Doxygen source/configuration |
| `examples/` | Protonect and viewer examples |
| `guides/` | Intel Mac, Catalina, compatibility, and repository guides |
| `include/` | Public and internal headers |
| `platform/` | Platform-specific support files |
| `src/` | Core libfreenect2 implementation |
| `tools/` | Auxiliary utilities and streamer/recorder tooling |

See **[guides/REPOSITORY_LAYOUT.md](guides/REPOSITORY_LAYOUT.md)** for the cleanup rationale.

## Branches

- **Source branch** — the actual project source and maintained repository presentation.
- **`gh-pages`** — generated Doxygen/API documentation and historical documentation assets.
- **`v0.1`** — historical version branch.

If GitHub opens a large collection of generated HTML files instead of this README, the repository is still using `gh-pages` as its default branch. The source branch should be configured as the repository default (preferably named `main`).

## Kinect v2 / USB notes

Kinect v2 is unusually demanding about USB transport:

- use the sensor's powered Kinect adapter;
- connect through a true USB 3.x path;
- prefer a direct MacBook Pro USB 3 port rather than a hub;
- disconnect other high-bandwidth devices while troubleshooting;
- virtual machines are generally a poor match for Kinect v2 isochronous USB traffic.

## Project status

ProtonectMAC contains a **historical libfreenect2 source snapshot**. Repository cleanup and documentation do not turn the underlying driver into a new implementation. The goal is to preserve and document a useful legacy Intel/Catalina configuration, particularly for 2013 MacBook Pro hardware.

## Upstream and attribution

Underlying driver project: **OpenKinect/libfreenect2**

- Upstream source: https://github.com/OpenKinect/libfreenect2
- Upstream API docs: https://openkinect.github.io/libfreenect2/
- Upstream troubleshooting: https://github.com/OpenKinect/libfreenect2/wiki/Troubleshooting

Original license files remain preserved as `APACHE20` and `GPL2`, with third-party dependency notices in `depends/LICENSES.txt`. The original libfreenect2 contributors retain attribution for the underlying driver implementation; ProtonectMAC branding and repository-specific documentation are additions around that codebase.
