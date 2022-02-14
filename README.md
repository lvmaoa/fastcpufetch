# Fake Arch Fetch

Fake Arch Fetch is a fast and light screenshot information tool that will display the "base" OS. E.g. a Manjaro system will display an Arch Linux Logo while BunsenLabs will display a Debian logo. Based on efetch, archfetch, and afetch.

It's primary purpose is to display the Arch Linux logo instead of the OS logo for users using Arch Linux based systems. It currently only has the Arch Logo but will support a larger variety of distribution logos in the future.

![alt text](https://github.com/aprilove/Fake-Arch-Fetch/blob/main/images/demo.png)


### Build
1. Install pthread dependency
2. clone the repo
`git clone https://github.com/aprilove/Fake-Arch-Fetch.git`
3. `cd` into the repo
`cd Fake-Arch-Fetch/`
4. make
`make`
5. Install
`sudo make install`

To uninstall `sudo make uninstall`

### Dependencies:
- pthreads

### To do:
- [ ] Implement pkg counter
