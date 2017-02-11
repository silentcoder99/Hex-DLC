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

## Docker
A container for this project can be found at `hazelfire/hex-dlc` run the container with
```bash
docker run -d --name hexdlc -p 20046:20046 hazelfire/hex-dlc
```

## Interacting with the server
The client can be called as follows:

```bash
HexDLCClient <serverIP> <command> [<arguments>]
```

The current command are:

- `champ` Returns the current champion's weights
- `stop` Halts the server
- `genCount` Returns the current generation number
- `setGenCount <number>` Sets the generation count to the given number
- `population` Returns the entire current population
- `setPopulation` Sets the population from into STDIN 
- `runTime` Returns the time it takes to evolve a single generation in seconds
- `getMatch` Returns a printout of a match running on the server

## Using the bots
The Bot.hex file can read weights given to it and play on [retroverse's](https://github.com/retroverse) Hex [Site](http://ewanb.me/Hex/). To use a player from the server, get a champ and paste the comma seperated values into the array named championWeights and remove the final comma, then paste it into the site and run the bot!

