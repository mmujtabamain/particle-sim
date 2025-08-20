#!/bin/bash

set -e 

# DO NOT CALL; has been called once; given below for refernce only
# git submodule add https://github.com/microsoft/vcpkg.git external/vcpkg
# gets vcpkg from git to external/vcpkg; vcpkg is added as submodule
git submodule update --init --recursive
# bootstrap it to generate ./external/vcpkg/vcpkg 
./external/vcpkg/bootstrap-vcpkg.sh

# install sfml
./external/vcpkg/vcpkg install sfml
# Runs the file
./run