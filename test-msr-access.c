
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static char msr_name[] = "/dev/cpu/0/msr";
static int msr_fd;
static uint32_t testreg = 0x186;

int check_msr()
{
    if (access(msr_name, R_OK|W_OK))
    {
        fprintf(stderr,"Unable to access MSR device %s: %s\n", msr_name, strerror(errno));
        return 1;
    }
    return 0;
}

int open_msr()
{
    msr_fd = open(msr_name, O_RDWR);
    if (msr_fd < 0)
    {
        fprintf(stderr,"Cannot open MSR device %s: %s\n", msr_name, strerror(errno));
        return 1;
    }
    return 0;
}

int close_msr()
{
    if (msr_fd > 0)
    {
        close(msr_fd);
    }
    return 0;
}

int read_msr()
{
    ssize_t ret;
    uint64_t data = 0;
    if (msr_fd > 0)
    {
        ret = lseek(msr_fd, testreg, SEEK_SET);
        if (ret < 0)
        {
            fprintf(stderr, "Cannot seek to register 0x%x\n", testreg);
            return 1;
        }
        ret = read(msr_fd, &data, sizeof(uint64_t));
        if (ret < 0)
        {
            fprintf(stderr, "Cannot read register 0x%x at MSR %s: %s\n", testreg, msr_name, strerror(errno));
            return 1;
        }
        else if (ret != sizeof(uint64_t))
        {
            fprintf(stderr, "Incomplete read on register 0x%x at MSR %s: %lu bytes\n", testreg, msr_name, ret);
            return 1;
        }
        return 0;
    }
    return 1;
}

int write_msr()
{
    ssize_t ret;
    uint64_t data = 0;
    if (msr_fd > 0)
    {
        ret = lseek(msr_fd, testreg, SEEK_SET);
        if (ret < 0)
        {
            fprintf(stderr, "Cannot seek to register 0x%x\n", testreg);
            return 1;
        }
        ret = write(msr_fd, &data, sizeof(uint64_t));
        if (ret < 0)
        {
            fprintf(stderr, "Cannot write register 0x%x at MSR %s: %s\n", testreg, msr_name, strerror(errno));
            return 1;
        }
        else if (ret != sizeof(uint64_t))
        {
            fprintf(stderr, "Incomplete read on register 0x%x at MSR %s: %lu bytes\n", testreg, msr_name, ret);
            return 1;
        }
        return 0;
    }
    return 1;
}

int main()
{
    int ret = 0;
    seteuid(0);
    setuid(0);
    if (check_msr()) return 1;
    if (open_msr()) return 1;
    if (read_msr()) return 1;
    if (write_msr()) return 1;
    if (close_msr()) return 1;
    printf("All OK!\n");
    return 0;
}
