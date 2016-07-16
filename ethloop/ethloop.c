/*
 * ethloop loops back all received frames.
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pcap.h>

pcap_t *pcap = NULL;

void print_pcap_err(char *prefix, int err) {
  switch(err) {
    case 0:
      break;
    case PCAP_ERROR:
      fprintf(stderr, "%s: pcap error %s\n", prefix, pcap_geterr(pcap));
      break;
    case PCAP_ERROR_BREAK:
      fprintf(stderr, "%s: pcap_loop terminated by pcap_break\n", prefix);
      break;
    case PCAP_ERROR_NOT_ACTIVATED:
      fprintf(stderr, "%s: pcap not activated\n", prefix);
      break;
    case PCAP_ERROR_ACTIVATED:
      fprintf(stderr, "%s: pcap is already activated\n", prefix);
      break;
    case PCAP_ERROR_NO_SUCH_DEVICE:
      fprintf(stderr, "%s: no such device\n", prefix);
      break;
    case PCAP_ERROR_RFMON_NOTSUP:
      fprintf(stderr, "%s: rfmon mode not supported\n", prefix);
      break;
    case PCAP_ERROR_NOT_RFMON:
      fprintf(stderr, "%s: rfmon mode not activated\n", prefix);
      break;
    case PCAP_ERROR_PERM_DENIED:
      fprintf(stderr, "%s: permission denied\n", prefix);
      break;
    case PCAP_ERROR_IFACE_NOT_UP:
      fprintf(stderr, "%s: interface isn't up\n", prefix);
      break;
    case PCAP_ERROR_CANTSET_TSTAMP_TYPE:
      fprintf(stderr, "%s: device can't set the time stamp type\n", prefix);
      break;
    case PCAP_ERROR_PROMISC_PERM_DENIED:
      fprintf(stderr, "%s: no permission to capture in promiscuous mode\n", prefix);
      break;
    case PCAP_ERROR_TSTAMP_PRECISION_NOTSUP:
      fprintf(stderr, "%s: requested time stamp precision not supported\n", prefix);
      break;
    case PCAP_WARNING:
      fprintf(stderr, "%s: pcap warning %s\n", prefix, pcap_geterr(pcap));
      break;
    case PCAP_WARNING_PROMISC_NOTSUP:
      fprintf(stderr, "%s: warning: promiscuous mode not supported\n", prefix);
      break;
    case PCAP_WARNING_TSTAMP_TYPE_NOTSUP:
      fprintf(stderr, "%s: warning: requested time stamp type not supported\n", prefix);
      break;
    default:
      if (err > 0)
        fprintf(stderr, "%s: unknown warning, err = %d\n", prefix, err);
      else
        fprintf(stderr, "%s: unknown error, err = %d\n", prefix, err);
      break;
  }

  if (err < 0) exit(1);
}

void terminate_pcap_loop(int signum) {
  if (pcap != NULL) pcap_breakloop(pcap);
}

void print_counter(int counter) {
  printf("\r%6d", counter); fflush(stdout);
}

void echo_packet(u_char *user, const struct pcap_pkthdr *pkthdr,
                 const u_char *packet) {
  static int counter = 0;
  int ret;

  ret = pcap_inject(pcap, packet, pkthdr->len);
  if (ret < 0) print_pcap_err("pcap_inject", ret);
  print_counter(++counter);
}

int main(int argc, char *argv[]) {
  char errbuf[PCAP_ERRBUF_SIZE];
  int ret;

  if (argc != 2) {
    fprintf(stderr, "ethloop loops back all received frames.\n\n"
                    "Usage: ethloop <network device>\n");
    exit(1);
  }

  if ((pcap = pcap_create(argv[1], errbuf)) == NULL) {
    fprintf(stderr, "pcap_create: can't open network device: %s\n", errbuf);
    exit(1);
  }

  print_pcap_err("pcap_set_snaplen", pcap_set_snaplen(pcap, 65535));
  print_pcap_err("pcap_set_promisc", pcap_set_promisc(pcap, 1));

  print_pcap_err("pcap_activate", pcap_activate(pcap));
  print_pcap_err("pcap_setdirection", pcap_setdirection(pcap, PCAP_D_IN));

  print_counter(0);
  signal(SIGHUP, terminate_pcap_loop);
  signal(SIGINT, terminate_pcap_loop);
  ret = pcap_loop(pcap, -1, echo_packet, NULL);
  if (ret != PCAP_ERROR_BREAK) print_pcap_err("pcap_loop", ret);
  signal(SIGHUP, SIG_DFL);
  signal(SIGINT, SIG_DFL);
  printf("\n");

  pcap_close(pcap);
  return 0;
}
