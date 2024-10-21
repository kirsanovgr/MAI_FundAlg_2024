#!/bin/bash

echo "installing dependencies"
apt-get update
apt-get install -y subunit check make cmake

echo "creating executable files"
make

echo "launch tests"
make test