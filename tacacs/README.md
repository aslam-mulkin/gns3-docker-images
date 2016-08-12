# TACACS+ appliance

Terminal Access Controller Access-Control System Plus (TACACS+) is a protocol
developed by Cisco and released as an open standard beginning in 1993.
Although derived from TACACS, TACACS+ is a separate protocol that handles
authentication, authorization, and accounting (AAA) services.

This `tac_plus` server is a major rewrite of the original Cisco source code.

For more information see http://www.shrubbery.net/tac_plus/,
a reference manual for the configuration file is available at
http://manpages.ubuntu.com/manpages/trusty/man5/tac_plus.conf.5.html .

An easier TACACS+ configuration can be done with `do_auth`, see
https://github.com/jathanism/do_auth .

The appliance includes `tac_passwd`, `tac_adduser` and `tac_deluser`
to manage the password file `/etc/tacacs+/passwd`.
