/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (c) 2025, Luxyd Technologies
 */

#ifndef _UAPI_LINUX_LUXYD_AI_IOCTL_H
#define _UAPI_LINUX_LUXYD_AI_IOCTL_H

#include <linux/ioctl.h>
#include <linux/types.h>

#define MAT_A_OFFSET	0x0000
#define MAT_B_OFFSET	0x2000
#define MAT_P_OFFSET	0x4000

struct matrix_info {
	int m;		/* Matrix A row size, matrix AB row size */
	int n;		/* Matrix A column size, matrix B row size */
	int p;		/* Matrix B column size, matrix AB column size */

	__u64 addr_a;	/* Address of Matrix A data in device mapped memory */
	__u64 addr_b;	/* Address of Matrix B data in device mapped memory */
	__u64 addr_p;	/* Address of Matrix P data in device mapped memory */
};

/* IOCTL commands */
#define LUXYD_AI_IOCTL_MAGIC		'L'
#define LUXYD_AI_STATUS_GET		_IOR(LUXYD_AI_IOCTL_MAGIC, 1, __u32)
#define LUXYD_AI_MODEL_LOAD		_IOW(LUXYD_AI_IOCTL_MAGIC, 2, __u32)
#define LUXYD_AI_INFERENCE_START	_IOWR(LUXYD_AI_IOCTL_MAGIC, 3, __u32)
#define LUXYD_AI_MATRIX_LOAD		_IOW(LUXYD_AI_IOCTL_MAGIC, 4, struct matrix_info)
#define LUXYD_AI_MATRIX_MULTIPLY	_IOR(LUXYD_AI_IOCTL_MAGIC, 5, struct matrix_info)

#ifdef __cplusplus
extern "C" {
#endif
int luxyd_dev_open(const char *devname);
void *luxyd_dev_init(int fd, int *mmap_size);
int luxyd_dev_matrix_load(int fd, void *mmap_ptr, struct matrix_info *matrix_info);
int luxyd_dev_matrix_multiply(int fd, void *mmap_ptr, struct matrix_info *matrix_info);
int luxyd_dev_close(int fd, void *mmap_ptr, int mmap_size);
#ifdef __cplusplus
}
#endif

#endif /* _UAPI_LINUX_LUXYD_AI_IOCTL_H */
