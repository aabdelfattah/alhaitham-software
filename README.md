# Al Haitham Project

The aim of this project is the proposal of a real time vision system for its application within visual interaction environments through hand gesture recognition using an FPGA and a camera.

## Features

- The project is based on the ALTERA DE2-115 FPGA kit and the TRDB-D5M camera.

- The current repository includes the software files only, hardware files can be found at [al-haitham hardware repo](https://github.com/aabdelfattah/alhaitham-hardware "alhaitham-hardware").

- There are 2 separate NIOS II eclipse software projects:
  - OpenCV ported to NIOS II processor with our tracker software.(more details about the porting in a readme inside the project)
  - USB firmware on another NIOS core for our DE2-115 kit to act as a HID device (mouse).

- Check pdf/project-doc.pdf for more technical details and block diagrams.

- The tracker detects :
  - pink colors and outputs their (x,y) locations , as a demo we used these locations to control the mouse pointer in Ubuntu .
  - pink + green as a left click.
  - green only as a right click.

- The results definitely need improvement (about ~0.5 fps) but it was basically a learning project and we wasted a lot of time messing with ALTERA glitchy tools, this project may act as a good base for others who want to quickly build up a working system and then start improving it.




## Install

Just clone the repo:

```
git clone https://github.com/aabdelfattah/alhaitham-software.git
```

1. Import the selected project from the repository to the local drive.

2. Import the projects to NIOS II software build tools , recreate the bsp projects from .sopc files if needed.

3. Build the projects.




That's it. Its ready to go.

## Run

Download the SOF to the DE2-115 , and run the software from NIOS II IDE .


## Contribute

- Fork project
- Add features
- Run tests
- Send pull request

## License

See LICENSE file for details