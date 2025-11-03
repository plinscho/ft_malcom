#include "ft_malcom.h"

void    free_malcom(t_malcom *m){
    if (!m) return ;
    if (m->src_eth.hostname) free(m->src_eth.hostname);
    if (m->src_eth.mac_addr) free(m->src_eth.mac_addr);
    if (m->dst_eth.hostname) free(m->dst_eth.hostname);
    if (m->dst_eth.mac_addr) free(m->dst_eth.mac_addr);
    // Add more structs to free
    if (m->socketfd >= 0)     close(m->socketfd);
    free(m);
}