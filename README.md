# Hex-DLC
Deep learning software designed to play the game hex as found [here](http://retroverse.github.io/Hex/)

This is a server and a client designed to generate weights for a Neuron network to play the game of Hex.

## Building
### Building on your computer
To build this you will need [CMake](https://cmake.org/) and [Boost](http://www.boost.org/).

Once you have cloned the repository, update the websockets and xml submodule

```bash
git submodule init
git submodule update
```

Then create a directory and run CMake in that directory

```bash
mkdir build
cd build
cmake ..
```

Then compile and run!

### Building with Vagrant
If you are having trouble with the installation process above, or want to run the application inside a virtual machine, follow these steps.

Install [Vagrant](https://www.vagrantup.com) and [Virtualbox](https://www.virtualbox.org/wiki/Downloads)

Go into the installation directory and update the submodules

```bash
git submodule init
git submodule update
```

Make sure you are connected to the internet then create the virtual machine to run the application in.

```bash
vagrant up
```

You might want to grab a coffee at this point, this will take a while.

After it's done, ssh into the virtual machine.

```bash
vagrant ssh
```

Once inside, build the application

```bash
cmake /vagrant
make
```

Then you should have the two excecutable files! Run with

```bash
./Hex-DLCServer
./Hex-DLCClient
```
