#! /vendor/bin/sh

# Setup cpu.shares to throttle background groups (bg ~ 5% sysbg ~ 5% dex2oat ~2.5%)
echo 1024 > /dev/cpuctl/background/cpu.shares
echo 1024 > /dev/cpuctl/system-background/cpu.shares
echo 512 > /dev/cpuctl/dex2oat/cpu.shares
echo 20480 > /dev/cpuctl/foreground/cpu.shares
echo 20480 > /dev/cpuctl/top-app/cpu.shares
echo 20480 > /dev/cpuctl/camera-daemon/cpu.shares
echo 20480 > /dev/cpuctl/system/cpu.shares
echo 20480 > /dev/cpuctl/nnapi-hal/cpu.shares
echo 20480 > /dev/cpuctl/rt/cpu.shares

pkill provider
