#!/bin/bash

set -e
export DEBIAN_FRONTEND="noninteractive"
apt-get update 
apt-get install --no-install-recommends --no-install-suggests -y \
                software-properties-common \
                build-essential \
                libperl-dev \
                libatlas-base-dev \
                gfortran \
                cmake \
                pkg-config \
                gettext-base \
                zip \
                git \
                ca-certificates \
                curl \
                automake \
                autogen \
                autoconf \
                libtool \
                gnupg2 \
                ssh \
                lcov \
                vim \
                gdb \
                wget \
                python
