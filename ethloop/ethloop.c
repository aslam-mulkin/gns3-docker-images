/*
 * ethloop loops back all received frames.
 *
 * ethloop is the virtual equivalence of a RJ45 loopback plug.
 * It's main objective is to see, how a network behaves with a
 * loop in it's topology.
 *
 * This program is put into the public domain, use it as you like.
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pcap.h>

pcap_t *pcap = NULL;		/* pcap handle */

/* print pcap error/warning and exit on error */
void handle_pcap_err(char *prefix, int err) {
    char *msg = NULL;

    switch(err) {
        case 0:			/* no error */
            break;
        case PCAP_ERROR:
            fprintf(stderr, "%s: error: %s\n", prefix, pcap_geterr(pcap));
            break;
        case PCAP_ERROR_BREAK:
            msg = "pcap_loop terminated by pcap_break";
            break;
        case PCAP_ERROR_NOT_ACTIVATED:
            msg = "pcap not activated";
            break;
        case PCAP_ERROR_ACTIVATED:
            msg = "pcap is already activated";
            break;
        case PCAP_ERROR_NO_SUCH_DEVICE:
            msg = "no such device";
            break;
        case PCAP_ERROR_RFMON_NOTSUP:
            msg = "rfmon mode not supported";
            break;
        case PCAP_ERROR_NOT_RFMON:
            msg = "rfmon mode not activated";
            break;
        case PCAP_ERROR_PERM_DENIED:
            msg = "permission denied";
            break;
        case PCAP_ERROR_IFACE_NOT_UP:
            msg = "interface isn't up";
            break;
        case PCAP_ERROR_CANTSET_TSTAMP_TYPE:
            msg = "device can't set the time stamp type";
            break;
        case PCAP_ERROR_PROMISC_PERM_DENIED:
            msg = "no permission to capture in promiscuous mode";
            break;
        case PCAP_ERROR_TSTAMP_PRECISION_NOTSUP:
            msg = "requested time stamp precision not supported";
            break;
        case PCAP_WARNING:
            fprintf(stderr, "%s: warning: %s\n", prefix, pcap_geterr(pcap));
            break;
        case PCAP_WARNING_PROMISC_NOTSUP:
            msg = "warning: promiscuous mode not supported";
            break;
        case PCAP_WARNING_TSTAMP_TYPE_NOTSUP:
            msg = "warning: requested time stamp type not supported";
            break;
        default:
            if (err > 0)
                fprintf(stderr, "%s: unknown warning, err = %d\n", prefix, err);
            else
                fprintf(stderr, "%s: unknown error, err = %d\n", prefix, err);
            break;
    }

    if (msg != NULL)
        fprintf(stderr, "%s: %s\n", prefix, msg);
    if (err < 0)
        exit(1);
}

/* break pcap loop by a signal */
void break_pcap_loop(int signum) {
    if (pcap != NULL) pcap_breakloop(pcap);
}

/* print packet counter */
void print_counter(int counter) {
    printf("\r%6d", counter); fflush(stdout);
}

/* callback on received packet */
void echo_packet(u_char *user, const struct pcap_pkthdr *pkthdr,
                 const u_char *packet) {
    static int counter = 0;
    int ret;

    ret = pcap_inject(pcap, packet, pkthdr->len);
    if (ret < 0) {
        printf("\n");
        handle_pcap_err("pcap_inject", ret);
        }
    print_counter(++counter);
}

int main(int argc, char *argv[]) {
    char errbuf[PCAP_ERRBUF_SIZE];
    sig_t old_sighup, old_sigint, old_sigquit;
    char *device;
    int ret;

    /* first (and only) argument is device name */
    if (argc != 2 || argv[1][0] == '-') {
        fprintf(stderr, "ethloop loops back all received frames.\n\n"
                        "Usage: ethloop <network device>\n");
        exit(1);
    }
    device = argv[1];

    /* open capture device */
    if ((pcap = pcap_create(device, errbuf)) == NULL) {
        fprintf(stderr, "pcap_create: can't open network device: %s\n", errbuf);
        exit(1);
    }

    /* set capture options */
    handle_pcap_err("pcap_set_snaplen", pcap_set_snaplen(pcap, 65535));
    handle_pcap_err("pcap_set_promisc", pcap_set_promisc(pcap, 1));

    /* activate capture */
    handle_pcap_err("pcap_activate", pcap_activate(pcap));
    handle_pcap_err("pcap_setdirection", pcap_setdirection(pcap, PCAP_D_IN));

    /* receive packets until HUP, INT or QUIT signal */
    old_sighup  = signal(SIGHUP,  break_pcap_loop);
    old_sigint  = signal(SIGINT,  break_pcap_loop);
    old_sigquit = signal(SIGQUIT, break_pcap_loop);
    print_counter(0);
    ret = pcap_loop(pcap, -1, echo_packet, NULL);
    printf("\n");
    if (ret != PCAP_ERROR_BREAK)
        handle_pcap_err("pcap_loop", ret);
    signal(SIGHUP,  old_sighup);
    signal(SIGINT,  old_sigint);
    signal(SIGQUIT, old_sigquit);

    pcap_close(pcap);
    return 0;
}
