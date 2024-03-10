# Waveshare RP2040 Round Touch LCD 1.28"

Experiment with the RP2040 based board with a round 240x240 pixel display.

https://www.waveshare.com/rp2040-touch-lcd-1.28.htm

RP2040-Touch-LCD-1.28

24580

- Linux (tested on Ubuntu 18.04.1)
- C / C++
- Command line
- Pico SDK
- Docker (optional) 
- LVGL

## Installation

```console
cd <your projects folder>
git clone https://www.github.com/deshrike/pico-waveshare
cd pico-waveshare
git submudule update --init
```console

## Pico SDK

You can compile the Pico programs locally, or using a Docker image.

To compile locally, install the Pico SDK.

To use a Docker image, follow these steps:

```console
cd <your projects folder>
mkdir pico-waveshare
docker run -d -it --name pc1 --mount type=bind,source=${PWD},target=/home/dev lukstep/raspberry-pi-pico-sdk:latest
```

After a reboot, you will need to restart the container:

```console
docker start pc1
```

Connect to the Docker container:

```console
docker exec -it pc1 /bin/sh
```

Inside the Docker container:

```console
cd /home/dev/pico-waveshare
```

## Compiling

```console
cd /home/dev/pico-waveshare  (if using Docker)
cd <your projects folder>/pico-waveshare (if you have installed the Pico SDK locally)

cd cdjwatch/build
cmake ..
make
```

The build folder should now contain a file called cdjwatch.uf2.
Copy this file to the device.

Follow the same steps for the other examples: blink, canvastest and lvgltest.

