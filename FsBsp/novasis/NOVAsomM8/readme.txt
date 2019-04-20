***************************
Novasis NOVAsomP board
***************************

This file documents the Buildroot support for the NOVAsomP board.

Please read the Quick Start Guide [1] for an introduction to the board.

Build
=====

Configure Buildroot for your i.MX6UL EVK board:

  make novasis_novasomp_defconfig

Build all components:

  make

You will find in ./output/images/ the following files:
  - rootfs.ext2
  - rootfs.tar
  - uInitrd

Enjoy!

References
==========
[1] http://www.novasis.it/NOVAsomP.html
