#ifndef __wrdf__
#define __wrdf__

/* stackoverflow  */

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>

void myprintf(FILE *fp, char *fmt, ...)
{
    char buff[512];
    int rc,fd;
    va_list argh;
    va_start (argh, fmt);

    rc = vsnprintf(buff, sizeof buff, fmt, argh);
    if (rc < 0  || rc >= sizeof buff)
    {
        rc = sprintf(buff, "Argh!: %d:\n", rc);
    }

    if (!fp) fp = stderr;
    fd = fileno(fp);
    if (fd < 0) return;
    if (rc > 0)  write(fd, buff, rc);
    return;
}


/**
 * writefd() - A variant of write(2)
 *
 * This function returns 0 if the write was successful, and the nonzero
 * errno code otherwise, with errno itself kept unchanged.
 * This function is safe to use in a signal handler;
 * it is async-signal-safe, and keeps errno unchanged.
 *
 * Interrupts due to signal delivery are ignored.
 * This function does work with non-blocking sockets,
 * but it does a very inefficient busy-wait loop to do so.
*/
int writefd(const int descriptor, const void *const data, const size_t size)
{
    const char       *head = (const char *)data;
    const char *const tail = (const char *)data + size;
    ssize_t           bytes;
    int               saved_errno, retval;

    /* File descriptor -1 is always invalid. */
    if (descriptor == -1)
        return EINVAL;

    /* If there is nothing to write, return immediately. */
    if (size == 0)
        return 0;

    /* Save errno, so that it can be restored later on.
     * errno is a thread-local variable, meaning its value is
     * local to each thread, and is accessible only from the same thread.
     * If this function is called in an interrupt handler, this stores
     * the value of errno for the thread that was interrupted by the
     * signal delivery. If we restore the value before returning from
     * this function, all changes this function may do to errno
     * will be undetectable outside this function, due to thread-locality.
    */
    saved_errno = errno;

    while (head < tail) {

        bytes = write(descriptor, head, (size_t)(tail - head));

        if (bytes > (ssize_t)0) {
            head += bytes;

        } else
        if (bytes != (ssize_t)-1) {
            errno = saved_errno;
            return EIO;

        } else
        if (errno != EINTR && errno != EAGAIN && errno != EWOULDBLOCK) {
            /* EINTR, EAGAIN and EWOULDBLOCK cause the write to be
             * immediately retried. Everything else is an error. */
            retval = errno;
            errno = saved_errno;
            return retval;
        }
    }

    errno = saved_errno;
    return 0;
}

int wrout(const char *const string)
{
    if (string)
        return writefd(STDOUT_FILENO, string, strlen(string));
    else
        return 0;
}

#endif /* __wrdf__ */