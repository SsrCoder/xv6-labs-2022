#!/usr/bin/bash

apt-get update 
apt-get install -y git build-essential gdb-multiarch qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu

git remote add github $(git remote get-url origin)
git remote add mit git://g.csail.mit.edu/xv6-labs-2022
git remote set-url origin git://g.csail.mit.edu/xv6-labs-2022
