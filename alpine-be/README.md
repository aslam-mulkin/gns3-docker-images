# nicer alpine appliance

The alpine appliance has two major annoyances:
- It doesn't stop immediately
- It tries to use localhost for DNS lookup, when no resolver is defined

This appliance fixes that by using two programs:
- run-stop, see https://github.com/ehlers/run-stop
- nodnsd, see https://github.com/ehlers/nodnsd
