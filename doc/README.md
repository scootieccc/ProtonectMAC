# Compile and execute development version

## With CUDA
* Edit ```CMakeLists.txt``` to assign ```CMAKE_CUDA_ARCHITECTURES``` in accordance with NVidia card.

```
cd
mkdir Programs && cd Programs
git clone https://github.com/NVIDIA/cuda-samples.git
export CUDA_SAMPLES_HOME=$HOME/Programs/cuda-samples

git clone https://github.com/blackzafiro/libfreenect2.git
cd ~/Programs/libfreenect2
mkdir buildcudadev && cd buildcudadev
cmake .. -DCMAKE_CUDA_FLAGS=-I\ $CUDA_SAMPLES_HOME/Common -DCMAKE_INSTALL_PREFIX=$HOME/freenect2cudadev
```

Para la Lenovo ideapad Y700 hay que apagar VAAPI:
```
cmake .. -DENABLE_VAAPPI=OFF -DCMAKE_CUDA_FLAGS=-I\ $CUDA_SAMPLES_HOME/Common -DCMAKE_INSTALL_PREFIX=$HOME/freenect2cudadev
```

To find the libraries:

```
export FREENECT_INSTALL_DIR=$HOME/freenect2cudadev
export FREENECT_COMPILE_DIR=$HOME/Programs/libfreenect2/buildcudadev
export LD_LIBRARY_PATH=$FREENECT_INSTALL_DIR/lib:$LD_LIBRARY_PATH
export PATH=$FREENECT_COMPILE_DIR/bin:$PATH
```

Test cuda buffer access with:

```
Protonect cudaccess
```


## Permissions for Kinect

```
sudo cp ../platform/linux/udev/90-kinect2.rules /etc/udev/rules.d/
```

Replug Kinect after copying file.


