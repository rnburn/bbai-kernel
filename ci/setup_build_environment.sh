#!/bin/bash

set -e
export DEBIAN_FRONTEND="noninteractive"
apt-get update 
apt-get install --no-install-recommends --no-install-suggests -y \
                software-properties-common \
                build-essential \
                git \
                curl \
                wget
