#!/bin/bash

NUC_ADDR=10.139.1.143

scp build/ch.bin user-sau-nuc@$NUC_ADDR:/tmp
ssh user-sau-nuc@$NUC_ADDR 'st-flash write /tmp/ch.bin 0x8000000'
