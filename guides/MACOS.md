# macOS 10.15 Catalina setup and troubleshooting

ProtonectMAC is primarily aimed at **Intel (`x86_64`) Macs running macOS 10.15 Catalina**, with a **2013 MacBook Pro** as the reference hardware target.

This is a legacy-compatibility guide. It intentionally prioritizes that hardware/software combination instead of trying to describe every current Mac configuration.

## Intended configuration

- **Mac:** Intel-based MacBook Pro, especially 2013-era models
- **Operating system:** macOS 10.15 Catalina
- **Sensor:** Kinect v2 / Kinect for Windows v2
- **USB:** direct USB 3.x path through the powered Kinect adapter
- **Build system:** CMake

Confirm the machine before troubleshooting anything else:

```bash
sw_vers
uname -m
system_profiler SPHardwareDataType
system_profiler SPUSBDataType
```

The intended CPU architecture is `x86_64`.

## Requirements

- Kinect v2 sensor
- Kinect v2 external power/USB adapter
- working USB 3.x port/path
- Xcode Command Line Tools
- CMake
- pkg-config
- libusb
- GLFW
- TurboJPEG / jpeg-turbo when required by the selected pipeline

Install Apple's command-line tools if needed:

```bash
xcode-select --install
```

On an existing Catalina-compatible Homebrew installation, the dependency names are typically:

```bash
brew install cmake pkg-config libusb glfw jpeg-turbo
```

Homebrew changes over time. Catalina may no longer be supported by the newest package revisions, so the correct solution may be to use package versions that remain compatible with 10.15 rather than forcing current formulae onto the older OS.

## Recommended build

Start with optional non-Mac backends disabled:

```bash
cmake -S . -B build \
  -DENABLE_CUDA=OFF \
  -DENABLE_VAAPI=OFF \
  -DENABLE_TEGRAJPEG=OFF

cmake --build build --parallel
```

Run Protonect:

```bash
./build/bin/Protonect
```

## OpenCL on Catalina

The source includes OpenCL support, but OpenCL was already a deprecated Apple technology by the Catalina era. If the OpenCL pipeline creates configuration or runtime trouble, disable it:

```bash
rm -rf build
cmake -S . -B build \
  -DENABLE_OPENCL=OFF \
  -DENABLE_CUDA=OFF \
  -DENABLE_VAAPI=OFF \
  -DENABLE_TEGRAJPEG=OFF
cmake --build build --parallel
```

The CPU/OpenGL paths remain alternatives subject to their normal dependencies.

The existing CMake configuration also detects Apple's VideoToolbox framework for RGB/JPEG processing when available.

## USB 3 troubleshooting on a 2013 MacBook Pro

Kinect v2 depends heavily on stable USB 3.x isochronous transfers. On older MacBook Pro hardware, troubleshoot the USB path before assuming the driver is broken.

1. Use the Kinect sensor's powered external adapter.
2. Connect directly to a built-in USB 3 port when possible.
3. Avoid unpowered hubs.
4. Disconnect other high-bandwidth USB devices during testing.
5. Confirm the sensor appears in `system_profiler SPUSBDataType`.
6. Try the other built-in USB port if enumeration is inconsistent.
7. Re-run Protonect with libusb debug logging.

```bash
LIBUSB_DEBUG=3 ./build/bin/Protonect
```

## If CMake cannot find libraries

Intel Homebrew installations traditionally use `/usr/local`. Check the actual installed prefixes instead of assuming paths:

```bash
brew --prefix
brew --prefix libusb
brew --prefix glfw
brew --prefix jpeg-turbo
pkg-config --modversion libusb-1.0
```

Useful diagnostics:

```bash
cmake --version
clang --version
pkg-config --version
brew config
```

## Clean rebuilds matter

CMake caches detected libraries and feature flags. When changing package versions, compilers, or enabled pipelines, remove the old build directory first:

```bash
rm -rf build
cmake -S . -B build -DENABLE_CUDA=OFF -DENABLE_VAAPI=OFF -DENABLE_TEGRAJPEG=OFF
cmake --build build --parallel
```

## Apple Silicon and newer macOS

Apple Silicon and current macOS releases are **not the primary compatibility target** for ProtonectMAC. The source snapshot predates Apple Silicon, and current package-manager/toolchain behavior may differ substantially from Catalina-era Intel Macs.

That does not mean other systems can never work; it means this repository should not present them as validated targets without specific testing.

See [COMPATIBILITY.md](COMPATIBILITY.md) for the project's intended support matrix and limitations.
