# Antwoordenboekjes

Dit is een website waar ik antwoordenboekjes op zet.

De documenten staan niet op github, alleen de code

## Libraries

MuPDF:

- Go to the [releases page](https://mupdf.com/releases/index.html)
- Download the latest tar.gz file
- Install all necessary dependencies (debian example):

  ```sh
  sudo apt-get install build-essential cmake zlib1g-dev libfreetype6-dev libjpeg-dev libopenjp2-7-dev libcairo2-dev libturbojpeg0-dev pkg-config libglu1-mesa-dev libx11-dev libxi-dev libxrandr-dev
  ```

- Extract the file using `tar -xf <file>` compile using `make` and `make install`

Crow:

- Download and install the deb file from the [releases page](https://github.com/CrowCpp/Crow/releases/)

## Running the server

```sh
# Install all libraries first

git clone https://github.com/tygoee/antwoordenboekjes
cd antwoordenboekjes
cmake .
make
./server.out
```
