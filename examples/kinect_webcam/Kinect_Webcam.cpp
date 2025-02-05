#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <errno.h>
#include <string.h>
#include <opencv2/opencv.hpp>
#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/registration.h>
#include <libfreenect2/packet_pipeline.h>
#include <libfreenect2/logger.h>

bool protonect_shutdown = false;
int v4l2_fd = -1;

void sigint_handler(int s)
{
  protonect_shutdown = true;
}

bool init_v4l2_device(const char *device, int width, int height)
{
  v4l2_fd = open(device, O_WRONLY);
  if (v4l2_fd < 0)
  {
    std::cerr << "Error opening v4l2loopback device: " << strerror(errno) << std::endl;
    return false;
  }

  struct v4l2_format v4l2_fmt;
  memset(&v4l2_fmt, 0, sizeof(v4l2_fmt));
  v4l2_fmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
  v4l2_fmt.fmt.pix.width = width;
  v4l2_fmt.fmt.pix.height = height;
  v4l2_fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_BGR24;
  v4l2_fmt.fmt.pix.sizeimage = width * height * 3;
  v4l2_fmt.fmt.pix.field = V4L2_FIELD_NONE;

  if (ioctl(v4l2_fd, VIDIOC_S_FMT, &v4l2_fmt) < 0)
  {
    std::cerr << "Error setting v4l2 format: " << strerror(errno) << std::endl;
    close(v4l2_fd);
    v4l2_fd = -1;
    return false;
  }

  return true;
}

void write_frame_to_v4l2(unsigned char *rgb_data, int width, int height)
{
  if (v4l2_fd < 0)
    return;

  cv::Mat frame(height, width, CV_8UC4, rgb_data);
  cv::Mat bgr_frame;
  cv::cvtColor(frame, bgr_frame, cv::COLOR_BGRA2BGR);

  write(v4l2_fd, bgr_frame.data, width * height * 3);
}

int main(int argc, char *argv[])
{
  libfreenect2::Freenect2 freenect2;
  libfreenect2::Freenect2Device *dev = nullptr;
  libfreenect2::PacketPipeline *pipeline = nullptr;

  if (!init_v4l2_device("/dev/video10", 1920, 1080))
  {
    std::cerr << "Failed to initialize v4l2loopback device" << std::endl;
    return -1;
  }

  if (freenect2.enumerateDevices() == 0)
  {
    std::cout << "No device connected!" << std::endl;
    return -1;
  }

  std::string serial = freenect2.getDefaultDeviceSerialNumber();

  dev = freenect2.openDevice(serial);

  if (dev == nullptr)
  {
    std::cout << "Failure opening device!" << std::endl;
    return -1;
  }

  signal(SIGINT, sigint_handler);

  libfreenect2::SyncMultiFrameListener listener(libfreenect2::Frame::Color);
  libfreenect2::FrameMap frames;

  dev->setColorFrameListener(&listener);

  if (!dev->start())
    return -1;

  std::cout << "Device serial: " << dev->getSerialNumber() << std::endl;
  std::cout << "Device firmware: " << dev->getFirmwareVersion() << std::endl;

  while (!protonect_shutdown)
  {
    if (!listener.waitForNewFrame(frames, 10 * 1000)) // 10 seconds
    {
      std::cout << "Timeout!" << std::endl;
      return -1;
    }
    libfreenect2::Frame *rgb = frames[libfreenect2::Frame::Color];

    write_frame_to_v4l2(rgb->data, rgb->width, rgb->height);

    listener.release(frames);
  }

  dev->stop();
  dev->close();
  close(v4l2_fd);
  return 0;
}
