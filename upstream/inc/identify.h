#ifndef IDENTIFY_H
#define IDENTIFY_H

#include <stdio.h>

#define NO_WRITING              0
#define AUTO_BR                 1
#define MBR_DOS                 2
#define FAT12_BR                3
#define FAT16_BR                4
#define FAT32_BR                5
#define FAT32NT5_BR             6
#define FAT32NT6_BR             7
#define EXFATNT6_BR             8
#define MBR_95B                 9
#define MBR_2000               10
#define MBR_VISTA              11
#define MBR_WIN7               12
#define MBR_SYSLINUX           13
#define MBR_ZERO               14
#define FAT16FD_BR             15
#define FAT32FD_BR             16
#define FAT32PE_BR             17
#define NTFS_BR                18
#define MBR_GPT_SYSLINUX       19
#define MBR_RUFUS              20
#define MBR_REACTOS            21
#define FAT16ROS_BR            22
#define FAT32ROS_BR            23
#define FAT32KOS_BR            24
#define MBR_GRUB4DOS           25
#define MBR_GRUB2              26
#define MBR_KOLIBRIOS          27
#define NUMBER_OF_RECORD_TYPES 28

/* Returns the number of sectors on disk before partition */
#ifdef __OpenBSD__
unsigned long partition_start_sector(FILE *fp, const char *szPath);
#else
unsigned long partition_start_sector(FILE *fp);
#endif

/* Returns the number of heads for the drive of a partition */
unsigned short partition_number_of_heads(FILE *fp);

/* Returns TRUE if writing a boot record of type iBr seems like a good idea,
   otherwise FALSE */
int sanity_check(FILE *fp, const char *szPath, int iBr, int bPrintMessages);

/* Prints some information about a device */
void diagnose(FILE *fp, const char *szPath);

/* Does a smart automatic selection of which boot record to write, returns
   the kind of boot record as defined above */
#ifdef __OpenBSD__
int smart_select(FILE *fp, const char *szPath);
#else
int smart_select(FILE *fp);
#endif

#endif
