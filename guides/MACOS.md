# macOS setup and troubleshooting

ProtonectMAC uses the existing libfreenect2 CMake build. This guide collects the Mac-specific path in one place so the root README can stay short.

## Requirements

- Kinect for Windows v2 / Kinect v2 sensor with its external power/USB adapter
- A reliable USB 3.x connection
- Xcode Command Line Tools
- Homebrew packages: `cmake`, `pkg-config`, `libusb`, `glfw`, and `jpeg-turbo`

Install the command line tools if necessary:

```bash
xcode-select --install
```

Install dependencies:

```bash
brew update
brew install cmake pkg-config libusb glfw jpeg-turbo
```

## Recommended build

```bash
cmake -S . -B build \
  -DENABLE_CUDA=OFF \
  -DENABLE_VAAPI=OFF \
  -DENABLE_TEGRAJPEG=OFF

cmake --build build --parallel
```

Run the example:

```bash
./build/bin/Protonect
```

## If CMake cannot find Homebrew libraries

Homebrew normally exposes the required package metadata automatically. If a package cannot be found, verify the prefixes first:

```bash
brew --prefix libusb
brew --prefix glfw
brew --prefix jpeg-turbo
pkg-config --modversion libusb-1.0
```

Apple Silicon Homebrew commonly installs under `/opt/homebrew`; Intel Homebrew commonly installs under `/usr/local`. Avoid hard-coding one prefix into the repository.

## OpenCL on newer macOS releases

OpenCL is deprecated by Apple and may be the least predictable optional path on newer systems. If configuration or runtime initialization fails, build without it:

```bash
cmake -S . -B build -DENABLE_OPENCL=OFF -DENABLE_CUDA=OFF -DENABLE_VAAPI=OFF -DENABLE_TEGRAJPEG=OFF
cmake --build build --parallel
```

The CPU/OpenGL paths remain available subject to their normal dependencies. The existing source also contains Apple VideoToolbox support for RGB/JPEG processing when the frameworks are detected.

## USB troubleshooting

Kinect v2 is demanding about USB transport. If the sensor is not enumerated or streams fail:

1. Connect the sensor through its powered Kinect adapter.
2. Prefer a direct USB 3.x port over a hub.
3. If using USB-C, try a different adapter/dock; advertised USB 3 support does not guarantee reliable isochronous behavior.
4. Disconnect other high-bandwidth devices from the same hub/controller.
5. Re-run Protonect with libusb debug logging when diagnosing enumeration/transfer failures.

Example:

```bash
LIBUSB_DEBUG=3 ./build/bin/Protonect
```

## Apple Silicon note

This source snapshot predates Apple Silicon. A successful native build therefore depends on whether all current dependencies and older source assumptions compile cleanly for arm64. If you hit architecture-specific source errors, record:

```bash
uname -a
cmake --version
clang --version
brew config
```

and include them in an issue. Do not silently mix x86_64 and arm64 Homebrew libraries in the same build tree.

## Clean rebuild

When switching architectures, dependency options, or compilers, remove the existing build directory instead of reusing cached CMake state:

```bash
rm -rf build
cmake -S . -B build -DENABLE_CUDA=OFF -DENABLE_VAAPI=OFF -DENABLE_TEGRAJPEG=OFF
cmake --build build --parallel
```
