#include "f1_types.h"

#include <stdlib.h>

int f1_randomize_udp_dgram(f1_udp_datagram_t * dgram)
{
    int ret = EXIT_SUCCESS;
    size_t i = 0;
    uint8_t * dgram_raw_ptr = (uint8_t *)dgram;

    if (NULL == dgram_raw_ptr)
    {
        ret = EXIT_FAILURE;
        goto done;
    }

    /* Fill raw buffer with random bytes */
    for (i = 0; i < F1_UDP_DATAGRAM_SIZE; ++i)
    {
        dgram_raw_ptr[i] = rand() % 0xFF;
    }

done:
    return ret;
}
