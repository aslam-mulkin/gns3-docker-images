# nicer alpine appliance

The alpine appliance has two major annoyances:
- It doesn't stop immediately
- It tries to use localhost for DNS lookup, when no resolver is defined

This appliance fixes that by using two programs:
- tini, see https://github.com/krallin/tini
- nodnsd, see https://github.com/ehlers/nodnsd
