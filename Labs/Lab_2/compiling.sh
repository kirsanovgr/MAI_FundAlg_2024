#!/bin/bash

echo "installing dependencies"
sudo apt-get update
sudo apt-get install -y subunit check make cmake

echo "creating executable files"
make

echo "launch tests"
make test
