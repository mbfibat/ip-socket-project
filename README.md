# ip-socket-project

Install TGUI and SFML:
```bash 
sudo apt-get update
sudo apt-get install libsfml-dev libx11-dev libgl1-mesa-dev libfreetype6-dev libjpeg-dev libudev-dev cmake
```
Download TGUI 0.9.5 from: https://github.com/texus/TGUI/archive/v0.9.5.zip, extract, go into the directory, then:
```bash
cmake -S . -B build
cmake --build build -j$(grep -c ^processor /proc/cpuinfo)
sudo cmake --install build
```

Build project:
```bash
./build.sh
```

Run client:
```bash
./run_client.sh
```

Run server:
```bash
./run_server.sh
```
