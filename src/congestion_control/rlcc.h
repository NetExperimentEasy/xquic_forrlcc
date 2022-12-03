/**
 * @copyright Copyright (c) 2022, jinyaoliu 
 */

#ifndef _RLCC_CC_H_INCLUDED_
#define _RLCC_CC_H_INCLUDED_

#include <xquic/xquic_typedef.h>
#include <xquic/xquic.h>
#include "src/transport/xqc_send_ctl.h"
#include "src/transport/xqc_packet_out.h"
#include <hiredis/hiredis.h>  

#define MSEC2SEC 1000000

typedef struct xqc_rlcc_s {
    uint32_t                cwnd;
    /* Current pacing rate */
    uint32_t                pacing_rate;
    redisContext*           redis_conn_listener;
    redisContext*           redis_conn_publisher;
    void*                   reply; // subscribe
    char*                   redis_host;
    uint32_t                redis_port;

    /* sample state */
    xqc_usec_t              timestamp;
    xqc_usec_t              rtt;
    uint32_t                rlcc_lost;   // on loss times
    uint64_t                last_lost;
    uint32_t                lost;       // sampler lost
    xqc_usec_t              srtt;
    uint32_t                throughput;
    uint32_t                delivered;
    uint32_t                delivered_interval;
    uint32_t                last_acked;
    uint64_t                inflight;
    uint32_t                prior_cwnd;
    uint32_t                prior_pacing_rate;
    xqc_usec_t              min_rtt;
    xqc_usec_t              min_rtt_timestamp;

    xqc_bool_t              in_recovery;
    xqc_bool_t              is_slow_start;

    uint32_t                rlcc_path_flag;
} xqc_rlcc_t;

extern const xqc_cong_ctrl_callback_t xqc_rlcc_cb;

#endif /* _XQC_RLCC_H_INCLUDED_ */