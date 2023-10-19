> **Note**  
> _Archived as I was thinking a bit big and didn't know this was gonna take so long. Also I don't think I would've ever put it online because of copyright issues :)_

# Antwoordenboekjes

Dit is een website waar ik antwoordenboekjes op zet.

De documenten staan niet op github, alleen de code

## Libraries

MuPDF **_Mupdf wasn't used, I planned to use it but hadn't yet implemented it_**: <s>

- Go to the [releases page](https://mupdf.com/releases/index.html)
- Download the latest tar.gz file
- Install all necessary dependencies (debian example):

  ```sh
  sudo apt-get install build-essential cmake zlib1g-dev libfreetype6-dev libjpeg-dev libopenjp2-7-dev libcairo2-dev libturbojpeg0-dev pkg-config libglu1-mesa-dev libx11-dev libxi-dev libxrandr-dev
  ```

- Extract the file using `tar -xf <file>`
- CD into the install directory
- Compile using `make` and `sudo make install` </s>

Crow:

- Download and install the deb file from the [releases page](https://github.com/CrowCpp/Crow/releases/)

## Running the server

```sh
# Install all libraries first

git clone https://github.com/tygoee/antwoordenboekjes
cd antwoordenboekjes
cmake .
make
cd server
./server.out
```
