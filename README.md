# PSU_zappy_2019

The zappy is a project which aims to create a server in C and create our own protocol that will communicate with the client that have their own graphical interface. We have choosen to do our graphical interface with unity.

## To begin

Clone this repository and follow the instructions.

### Prerequisite

 - gcc
 - make

### Installation

 - make

## Start it!

To use the server and the client make sure that the port given in parameters is open in your network.

### WARNING
On some systems (it's the case for Fedora), you may need to open the port 4243 TCP for example in the firewall settings. To do this, use the following command.

    firewall-cmd --zone=public --add-port=4243/tcp

### Usage
If you want to see the usage of a command just try to execute the zappy_server or zappy_ai with the -h flag

### 1/The server

First of all execute the server with some arguments for example:

    ./zappy_server -p 4242 -x 10 -y 10 -n team1 team2 -c 12 -f 50

So here the server will be launch on the port 4242 with a map size of 10 by 10 and two teams (here team1 and team2), these two teams will accept maximum 12 clients and the server have a frequency of 50.

### 2/The graphical interface

Now that the server is launch you can have a graphical interface made with unity on Linux or on Windows

To launch it on Linux:

    ./Linux_Release/Zappy_Linux_Release/Zappy.x84_64
    
or on Windows:

    Windows_Release/Zappy_Windows_Release/Zappy.exe

On the game just play and add your localhost for example 127.0.0.1 if it's on the same computer than the server and the port with the one you launch the game (the one you use after the -p)

Now you have the server that is ready to accept new players and your graphical interface that is ready to receive the information from the server.

### 3/The Clients

Now to make the game run you have to connect a few clients, there are IA, they will work by themselves, their goal is to pick up the items that are on the ground and to evolve to the level 8 thanks to these items the fastest, they can't evolve solo to the level 8, they must be at least 6 in the same team
So you have to launch at least 6 IA to see the end of the game, but if you want to make two team compete you will need at least 12 IA.
To launch one IA you must do:

    ./zappy_ai -p <the port you renseign for the server> -n <the name of the team you want this IA to be>
    
and here it is, you should now see an astronaut that appear on the graphical interface.

## Versions

**Dernière version stable :** 1.0

## Auteurs

* **Alexandre Malaquin** _alias_ [@Monfred156](https://github.com/Monfred156)
* **Emilien Delevoye** _alias_ [@Emilien-Delevoye](https://github.com/Emilien-Delevoye)
* **William Petitprez** _alias_ [@Zorivac](https://github.com/Zorivac)
* **Cyprien Ricque** _alias_ [@Cyprien-Ricque](https://github.com/Cyprien-Ricque)
* **Paul Surrans** _alias_ [@PaulSrrs](https://github.com/PaulSrrs)
