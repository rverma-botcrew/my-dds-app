# CycloneDDS Installation
First we need to clone and build the Core CycloneDDS
```
cd ~
git clone https://github.com/eclipse-cyclonedds/cyclonedds.git
cd cyclonedds
git checkout releases/0.10.x
rm -rf build
mkdir build && cd build
```
Now since we want CycloneDDS system-wide it is suggested to installed a user defined directory doing is safer as it does not ask for root privileges.
```
export CYCLONE_INSTALL=$HOME/dds-install         # core C library prefix
cmake -DCMAKE_INSTALL_PREFIX=$CYCLONE_INSTALL \
      -DBUILD_IDLC=ON \
      -DBUILD_EXAMPLES=ON \
      -DBUILD_DDSPERF=ON .. 

make -j$(nproc)
make install
```
Now we need to source the Path to our CycloneDDS so that it does use the one from ROS2
```
export PATH=$CYCLONE_INSTALL/bin:$PATH
export LD_LIBRARY_PATH=$CYCLONE_INSTALL/lib:$LD_LIBRARY_PATH
```
Check using
```
which idlc
```
Test installation as below(Requires the flag -DBUILD_EXAMPLES=ON )
```
cd ~/cyclonedds/build/bin
# In first terminal
./HelloworldPublisher

# In second terminal
./HellowworldSubscriber
```

Next we need to build the C++ wrapper for the CycloneDDS
```
cd ~
git clone https://github.com/eclipse-cyclonedds/cyclonedds-cxx.git
cd cyclonedds-cxx
git checkout releases/0.10.x
mkdir build && cd build
```
Again we need the wrapper to be system wide but without messing with the root
```
export CXX_INSTALL=$HOME/dds-cxx-install         # C++ wrapper prefix
cmake -DCMAKE_INSTALL_PREFIX=$CXX_INSTALL \
      -DCMAKE_PREFIX_PATH="$CYCLONE_INSTALL" \
      -DBUILD_EXAMPLES=ON ..

make -j$(nproc)
make install
```

Lets test if the wrapper is installed correctly
```
cd ~/cyclonedds-cxx/build/bin
# In first terminal
./ddscxxHelloworldPublisher

# In second terminal
./ddscxxHelloworldSubscriber
```
