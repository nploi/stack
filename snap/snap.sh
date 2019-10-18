#!/usr/bin/env bash
cd ..
rm -rf CMakeCache.txt
echo 'Removed CMakeCache.txt'
snapcraft
snapcraft login
snapcraft push --release=edge stacker_*.snap