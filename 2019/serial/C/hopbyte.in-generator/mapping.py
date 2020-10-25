#!/usr/bin/env python3
"""
Simple random mapping generator script
Writes a random mapping of processes to processors (actually, their are just pairs of numbers)
Usage:
- python3 mapping.py [number of processes] [number of processors] [random seed] [output file name]
- ./mapping.py [number of processes] [number of processors] [random seed] [output file name]
"""

import sys
import random

def main():
    """Computes the random mapping of processes to processors"""
    # The script expect 4 parameters + its name
    if len(sys.argv) != 5:
        print("Missing input parameters. Expected 4, got "+str(len(sys.argv)-1))
        sys.exit()

    # Parses inputs
    processes = int(sys.argv[1])
    processors = int(sys.argv[2])
    random.seed(int(sys.argv[3]))
    filename = sys.argv[4]

    # Starts output file
    with open(filename, 'w') as output:
        # Writes first line: number of processes and processors
        output.write(str(processes)+" "+str(processors)+"\n")

        # Generates mapping
        for process in range(processes):
            output.write(str(process)+" "+str(random.randrange(processors))+"\n")

if __name__ == '__main__':
    main()
