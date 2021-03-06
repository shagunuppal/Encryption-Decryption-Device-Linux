# Encryption-Decryption-Device-Linux

<b> Course Assignment for Operating Systems (CSE231) </b> <br>
<b> Instructor : Dr. Sambuddho Chakravarty </b>

The aim of this assignment was to create character devices for encryption as well as decryption of files. 

<b> The Encryption Device (encdev) : </b><br><br>
The device computes a simple block cipher (encryption) on a file (the input) and outputs the encrypted file.
For this, a kernel module based device driver for the encdev device needs to be written so as to use VFS data structures and define open(), read(), write() and close() functions for this device.
The device can be accesses via a call to open() system call, passing the device file path as an argument. The first call to write() internally initializes the shared random key (a random 128-bit number). 
Subsequent write()s would result in the bytes being encrypted and stored internally in the kernel in some data structure, e.g. some dynamically allocated location. 
The last block to be written is signaled through an EOF byte being written to the file, which is not encrypted.
Subsequent read()s result in reading off the encrypted blocks, until an EOF is encountered. Finally, upon calling close(), the initialized data structures are deallocated.
<br>
<center>
<img src = "encdevice.png">
</center>
<br>
<b> The Decryption Device (decdev) : </b><br><br>
Just like encdev, there is a decdev device file which is used to decrement an encrypted file. Similar to encdev, there are functions like open() and write() which helps in writing blocks of encrypted file to the device. The first block of 128-bits (16 bytes) happens to be the key (the same is one used for encryption
and decryption). The subsequent blocks written are the cipher blocks (encrypted previously via the encdev). Here again the last block is signaled via the EOF character. Each of these blocks is decrypted and stored in some internal data structure.
Thereafter, subsequent read() calls result in reading blocks of decrypted blocks. The final block is again signaled through reading off the previously written EOF character.
<br>
<center>
<img src = "decdevice.png">
</center>

## Commands to create the devices 
Following are the commands to first create the encryption and decryption devices on a Linux System : <br><br>
<b>
mknod /dev/encdev c 150 1 <br>
chmod a+r+w /dev/encdev <br>
cd enc <br>
make <br>
insmod encdev.ko <br>
<br>
mknod /dev/decdev c 160 1 <br>
chmod a+r+w /dev/decdev <br>
cd dec <br>
make <br>
insmod decdev.ko <br>
</b>

## Test Function
The test program can be used to check the functioning of the devices. Name of the file that is to be encrypted and decrypted must be passed as an argument on the comand line, for example some.txt here. <br>
<b>
gcc test.c <br>
./a.out some.txt <br>
</b>
