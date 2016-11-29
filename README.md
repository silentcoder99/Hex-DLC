# Hex-DLC
Deep learning software designed to play the game hex as found [here](http://retroverse.github.io/Hex/)

This is a server and a client designed to generate weights for a Neuron network to play the game of Hex.

## Building
To build this you will need CMake and Boost.

Once you have cloned the repository, update the websockets submodule

```bash
git submodule init
git submodule update
```

Then create a directory called build and run CMake in that directory

```bash
mkdir build
cd build
cmake ..
```

Then compile and run!
