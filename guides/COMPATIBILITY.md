# Compatibility target

ProtonectMAC is a **legacy Intel Mac compatibility project** centered on keeping Kinect v2 usable on hardware and software combinations that modern tooling increasingly leaves behind.

## Primary target

| Area | Target |
| --- | --- |
| CPU | Intel x86_64 |
| Reference Mac | 2013 MacBook Pro |
| macOS | 10.15 Catalina |
| Sensor | Kinect v2 / Kinect for Windows v2 |
| USB | USB 3.x through the powered Kinect adapter |
| Driver base | libfreenect2 |
| Example application | Protonect |

## What “supported” means here

The repository is organized and documented around this specific configuration. It does not mean every possible 2013 MacBook Pro, USB controller state, Homebrew package revision, or Catalina point release has been exhaustively validated.

The purpose is to preserve a practical path for machines with these constraints:

- Intel-only CPU architecture
- macOS 10.15 Catalina-era frameworks and compiler behavior
- aging package-manager support
- strict Kinect v2 USB 3.x transport requirements
- no dependency on Microsoft's Windows Kinect SDK

## Secondary / unverified configurations

These may work, but they are not the project's main compatibility promise:

- other Intel Macs on Catalina
- Intel Macs on nearby macOS releases
- newer Intel MacBook Pro generations
- Apple Silicon through native or translated builds
- current macOS releases

Treat successful results on those systems as additional compatibility rather than the baseline target.

## Known limitations

- Kinect v1 / Xbox 360 Kinect is not the target device.
- USB 2 is insufficient for Kinect v2 streaming.
- OpenCL behavior can be fragile because Apple deprecated OpenCL before the Catalina era ended.
- current Homebrew formulae may no longer install cleanly on Catalina.
- this repository contains a historical libfreenect2 source snapshot, not a ground-up modern driver rewrite.

## Reporting results

When reporting success or failure, include:

```bash
sw_vers
uname -m
system_profiler SPHardwareDataType
system_profiler SPUSBDataType
cmake --version
clang --version
brew config
```

Also note the exact MacBook Pro model/year, Kinect adapter used, whether the sensor was connected directly or through a hub, and which CMake feature flags were enabled.
