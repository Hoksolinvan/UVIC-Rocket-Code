#pragma once

#include <stdint.h>
#include <stdbool.h>

#define WRITE_ENABLE 0x06
#define VOLATILE_SR_WRITE_ENABLE 0x50
#define WRITE_DISABLE 0x04

#define RELEASE_POWER_DOWN 0xAB
#define DEVICE_ID 0x90
#define JEDEC_ID 0x9F
#define READ_UNIQUE_ID 0x4B

#define READ_DATA 0x03
#define FAST_READ 0x0B

#define PAGE_PROGRAM 0x02

#define SECTOR_ERASE 0x20
#define BLOCK_ERASE_32 0x52
#define BLOCK_ERASE_64 0xD8
#define CHIP_ERASE 0x60

#define READ_SREG_1 0x05
#define WRITE_SREG_1 0x01
#define READ_SREG_2 0x35
#define WRITE_SREG_2 0x31
#define READ_SREG_3 0x15
#define WRITE_SREG_3 0x11

#define READ_SFDP_REGISTER 0x5A
#define ERASE_SECURITY_REGISTER 0x44
#define PROGRAM_SECURITY_REGISTER 0x42
#define READ_SECURITY_REGISTER 0x48

#define GLOBAL_BLOCK_LOCK 0x7E
#define GLOBAL_BLOCK_UNLOCK 0x98
#define READ_BLOCK_LOCK 0x3D
#define INDIVIDUAL_BLOCK_LOCK 0x36
#define INDIVIDUAL_BLOCK_UNLOCK 0x39

#define PROGRAM_SUSPEND 0x75
#define PROGRAM_RESUME 0x7A
#define POWER_DOWN 0xB9

#define ENABLE_RESET 0x66
#define RESET_DEVICE 0x99




void send_write_enable(void);
void volatile_write_enable(void);
