# nfc-amiibo-win

This is a tool for spoofing amiibo NFC tags using a PN532 NFC compatible reader/writer with [libnfc](http://nfc-tools.org/index.php/Libnfc).  
This is a fork of [nfc-amiibo](https://github.com/crazyquark/nfc-amiibo), all credits go to the original creator, I only made some edits to have it work on Windows.
For Linux please use the original git as I have not tested whether the changes made still work on Linux.

## Hardware
1. You can probably use any `libnfc` supported NFC reader/writer(I used the always popular ACR122U)

2. `NTAG215` NFC tags  

## Software setup

### Install the Driver

The project requires the PC/SC driver for the specific NFC device to be installed. For the ACR122U that driver can be found [here](https://www.acs.com.hk/en/driver/3/acr122u-usb-nfc-reader/).

### Use existing release

Just download the latest binary from the [release page](https://github.com/Porr3/nfc-amiibo-win/releases/latest), it should work out of the box.

### Build from source

1. Install Visual Studio 2022 and CMake

2. Clone this repository with submodules

    `git clone --recurse-submodules https://github.com/Porr3/nfc-amiibo.git`

3. Compile sources

    start a `x64 Native Tools Command Prompt for VS 2022` (should be listed in the start menu Visual Studio 2022 folder)

    cd into the cloned git and run:
    ```
    cmake . -B build
    cmake --build build --config Release
    ```
    If everything worked the binary should be in `<git_folder>/bin`

## Getting the required files
After you have followed the above setup, you just need two more files to start making your own amiibo: an amiibo dump, and the key file.

### Amiibo Dump
Amiibo dumps are not hard to get. Amiibo are 540 bytes and usually stored in a .bin (binary) file. Assuming you are simply cloning your own legitimate amiibo, you can use any dumping tool to dump it to a .bin file. Otherwise, that's probably copyright infringement or something.

### Key file
This is the file containing Nintendo's key, which they use to encrypt/decrypt data on the amiibo. It is probably also copyrighted content, but it's a 160 byte .bin file which matches the MD5 `45fd53569f5765eef9c337bd5172f937`.

## Usage

Start the program:
`nfc-amiibo.exe path-to-key-file path-to-amiibo-file`

Once you see `***Scan tag***`, place and hold your blank NFC tag on the reader/writer. You should then see messages scrolling past with each data page as it begins writing them. ***Do not remove your tag until the write is finished.*** When you see `Finished writing tag`, it is safe to remove your tag and enjoy your new amiibo!

## Common Problems
    
* Failed to write a page
  ```
  Writing to 4: a5 b0 d1 00...Failed
  Failed to write to tag
  Write: RF Transmission Error
  ```
  This means your tag is already locked. The NTAG 21x spec declares locking bits which permanently prevent certain parts of a tag from being written to once they are set. Therefore once the locking bits are set, you cannot rewrite this tag to another amiibo. All amiibo are required to have certain locking bits sets, so you cannot change a tag once you've used it.

    If this happened anywhere other than page 4, it probably means that your device lost connection to the tag. Try again while keeping the tag closer to your device. Hopefully in the future I'll add a feature to check which of these problems occurred.
