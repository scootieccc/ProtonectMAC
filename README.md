<p align="center">
  <img src="assets/branding/protonectmac-logo.svg" alt="ProtonectMAC" width="760">
</p>

<p align="center"><strong>A cleaner, macOS-first home for Protonect and libfreenect2 Kinect v2 tooling.</strong></p>

> **Project status:** this repository contains a historical libfreenect2 source snapshot. The cleanup here improves organization, onboarding, and macOS documentation without pretending the underlying driver is a new implementation. Compatibility with current macOS releases, Apple Silicon, USB controllers, and Homebrew packages can vary.

## What is ProtonectMAC?

ProtonectMAC packages the familiar **Protonect** example and the underlying **libfreenect2** Kinect v2 driver source in a repository that is easier to understand from a Mac user's point of view.

The source supports RGB, infrared/depth transfer, and RGB/depth registration for **Kinect for Windows v2 / Kinect v2** hardware. It does **not** target Kinect v1 / Xbox 360 Kinect devices.

The driver code originates from the OpenKinect `libfreenect2` project. ProtonectMAC keeps that provenance visible while giving this repository its own focused documentation and branding.

## macOS quick start

### 1. Install build dependencies

```bash
brew update
brew install cmake pkg-config libusb glfw jpeg-turbo
```

### 2. Clone and build

```bash
git clone https://github.com/scootieccc/ProtonectMAC.git
cd ProtonectMAC
git checkout master

cmake -S . -B build \
  -DENABLE_CUDA=OFF \
  -DENABLE_VAAPI=OFF \
  -DENABLE_TEGRAJPEG=OFF

cmake --build build --parallel
```

### 3. Run Protonect

```bash
./build/bin/Protonect
```

If OpenCL causes configuration or runtime trouble on a newer macOS installation, rebuild with `-DENABLE_OPENCL=OFF`. VideoToolbox support is detected by the existing CMake configuration on Apple platforms.

For troubleshooting and Apple Silicon notes, see **[guides/MACOS.md](guides/MACOS.md)**.

## Repository layout

The build-sensitive source tree is intentionally kept conventional instead of being rearranged cosmetically:

| Path | Purpose |
| --- | --- |
| `assets/branding/` | ProtonectMAC logo and visual assets |
| `cmake_modules/` | Custom CMake find/setup modules |
| `depends/` | Dependency helper scripts and third-party notices |
| `doc/` | Doxygen source/configuration used by the build |
| `examples/` | Protonect and viewer examples |
| `guides/` | Human-facing setup and repository documentation |
| `include/` | Public and internal headers |
| `platform/` | Platform-specific support files |
| `src/` | Core libfreenect2 implementation |
| `tools/` | Auxiliary utilities, including streamer/recorder tooling |

See **[guides/REPOSITORY_LAYOUT.md](guides/REPOSITORY_LAYOUT.md)** for the cleanup rationale.

## Branches

- **`master`** — source code and the maintained repository presentation.
- **`gh-pages`** — generated Doxygen/API documentation and historical documentation assets.
- **`v0.1`** — historical version branch.

The repository was originally configured with `gh-pages` as its default branch. If GitHub opens generated HTML first, switch to `master` for the actual source tree.

## Hardware notes

- Kinect v2 requires a working **USB 3.x** connection; USB 2 is not sufficient.
- USB controller/adapter behavior matters. Hubs and some USB-C adapters can introduce problems even when their advertised bandwidth is high enough.
- Virtual machines are generally a poor fit for Kinect v2 isochronous USB traffic.

## Upstream project and documentation

The underlying driver is based on **OpenKinect/libfreenect2**:

- Upstream source: https://github.com/OpenKinect/libfreenect2
- Upstream API docs: https://openkinect.github.io/libfreenect2/
- Upstream troubleshooting: https://github.com/OpenKinect/libfreenect2/wiki/Troubleshooting

For new driver fixes or platform support, compare behavior with upstream before treating a ProtonectMAC-specific issue as a libfreenect2 regression.

## Licensing and attribution

Original license files are preserved in this repository as `APACHE20` and `GPL2`. Third-party dependency notices are preserved in `depends/LICENSES.txt`.

The libfreenect2 project and its original contributors retain attribution for the underlying driver implementation. ProtonectMAC branding and repository-specific documentation are organizational additions around that codebase.
