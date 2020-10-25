#!/bin/bash
python mapping.py 50000 40960 0 mapping.in
make
./graph_generator 50000 10000000 0 application.in
cat application.in > hopbyte.in
cat topology.in >> hopbyte.in
cat mapping.in >> hopbyte.in
rm mapping.in
rm application.in