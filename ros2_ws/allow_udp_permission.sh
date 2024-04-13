#!/bin/bash

# Allow UDP traffic from 192.168.0.180 to 192.168.0.64
sudo iptables -A INPUT -s 192.168.0.180 -d 192.168.0.64 -p udp -j ACCEPT
sudo iptables -A OUTPUT -s 192.168.0.64 -d 192.168.0.180 -p udp -j ACCEPT
