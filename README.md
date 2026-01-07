This repository contains an experimental kernel x86_64, writed using assembly and C, loaded via GRUB 2 and tested on QEMU using SeaBIOS and OVMF.

WARNING
This kernel is not for real use. It's purpose is for learning and experimentation

LICENCE
This project is licensed under GNU General Public License v3.0.
You are free to use it, change it, and distribute this software, as far as you use the same Licence.

Check the archive LICENSE for more details.


FUNCIONALITIES:

Boot via GRUB 2 (multiboot2)
Execution in long mode (64-bit)
Kernel freestanding
Stack manual initialization
Direct Write in VGA text mode (0xB8000)
ISO bootable build
QEMU Execution

TREE:

.
├── build/ # Objects and final binary
│ └── kernel.bin
├── iso/ # ISO BOOTABLE structure
│ └── boot/
│ ├── grub/
│ │ └── grub.cfg
│ └── kernel.bin
├── src/ # Source code
│ ├── boot.s # Entry point (_start) + stack
│ └── kernel.c # Main
├── kernel.iso # grub-mkrescue generated ISO
├── OVMF_VARS_4M.fd . # UEFI variables for QEMU
└── README.md

GENERAL BOOT VISION

1. GRUB 2 load the kernel using multiboot2
2. The code in boot.s:
   - Starts the stack
   - Calls kernel_main() in C
3. The kernel writes text directly at the VGA memory
4. The CPU enters at safe loop using hlt


REQUIREMENTS
- gcc (x86_64)
- binutils
- grub2
- grub-mkrescue
- qemu-system-x86_64
- ovmf (for UEFI)

Ubuntu install:
  sudo apt install build-essential grub-pc-bin grub-efi-amd64-bin xorriso qemu-system ovmf

COMPILATION
  as -c src/kernel.c -o build/kernel.o \
    -ffreestanding -fno-pie -fno-stack-protector -O2
  ld -T linker.ld -o build/kernel.bin build/boot.o build/kernel.o

Copy kernel to ISO
  cp build/kernel.bin iso/boot

Generate the ISO
  grub-mkrescue -o kernel.iso iso/

QEMU EXECUTION (UEFI)
  qemu-system-x86_64 \
    -drive if=pflash,format=raw,readonly,file=/usr/share/OVMF/OVMF_CODE_4M.fd \
    -drive if=pflash,format=raw,file=OVMF_VARS_4M.fd \
    -cdrom kernel.iso \
    -m 512M \
    -net none

NEXT UPDATES
-keyboard driver
-cursor VGA management
-GDT/IDT
-Mem Alloc
-Bootloader

