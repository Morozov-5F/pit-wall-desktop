#include <stdio.h>
#include <uv.h>

#include "config.h"
#include "f1_types.h"

static uv_loop_t  gs_uv_loop;
static uv_udp_t   gs_udp_handle;
static uv_timer_t gs_send_timer;

/* Timer callback */
static void s_schedule_dgram_send(uv_timer_t * handle)
{
    f1_udp_datagram_t gs_sample_dgram;
    struct sockaddr_in send_addr;
    uv_buf_t msg;
    /* TODO: create send address sockaddr_in struc */
    /* TODO: randomize sample dgram */
    /* TODO: create a dgram buffer */
    /* TODO: send UDP packet */
}

static int libuv_init()
{
    int uv_ret = 0;
    struct sockaddr_in bind_addr;

    printf("Initialization...\n");

    /* Setup libUV loop */
    uv_ret = uv_loop_init(&gs_uv_loop);
    if (0 != uv_ret)
    {
        fprintf(stderr, "Unable to intialize LibUV loop: %d\n", uv_ret);
        goto done;
    }
    /* Setup UDP socket */
    uv_ret = uv_udp_init(&gs_uv_loop, &gs_udp_handle);
    if (0 != uv_ret)
    {
        fprintf(stderr, "Unable to intialize LibUV UDP handle: %d\n", uv_ret);
        goto done;
    }
    uv_ret = uv_ip4_addr(F1_SOCKET_BIND_ADDRESS, F1_SOCKET_BIND_PORT, &bind_addr);
    if (0 != uv_ret)
    {
        fprintf(stderr, "Unable to bind LibUV UDP : %d\n", uv_ret);
        goto done;
    }
    uv_ret = uv_udp_bind(&gs_udp_handle, (const struct sockaddr *)&bind_addr, 0);
    if (0 != uv_ret)
    {
        fprintf(stderr, "Unable to bind LibUV UDP handle to %s:%d: %d\n",
                F1_SOCKET_BIND_ADDRESS, F1_SOCKET_BIND_PORT, uv_ret);
        goto done;
    }
    /* Setup libUV send timer */
    uv_ret = uv_timer_init(&gs_uv_loop, &gs_send_timer);
    if (0 != uv_ret)
    {
        fprintf(stderr, "Unable to initialize libUV timer: %d\n", uv_ret);
        goto done;
    }
    uv_ret = uv_timer_start(&gs_send_timer, s_schedule_dgram_send,
                            F1_SEND_PERIOD_MS, F1_SEND_PERIOD_MS);
    if (0 != uv_ret)
    {
        fprintf(stderr, "Unable to start libUV timer: %d\n", uv_ret);
        goto done;
    }

    printf("Initialization complete\n");

done:
    return uv_ret;
}

int main(int argc, const char * argv [])
{
    int ret = libuv_init();

    return ret;
}
