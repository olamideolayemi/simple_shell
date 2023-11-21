#!/bin/bash
pid_max=$(cat /proc/sys/kernel/pid_max)
echo "MAXimum PID Val: $pid_max"
