#!/bin/bash

set -e

[ -z "${BAZEL_VERSION}" ] && export BAZEL_VERSION="0.24.0"

apt-get update 
apt-get install --no-install-recommends --no-install-suggests -y \
         wget \
         unzip \
         ca-certificates \
         openjdk-8-jdk
wget https://github.com/bazelbuild/bazel/releases/download/${BAZEL_VERSION}/bazel-${BAZEL_VERSION}-installer-linux-x86_64.sh
chmod +x bazel-${BAZEL_VERSION}-installer-linux-x86_64.sh
./bazel-${BAZEL_VERSION}-installer-linux-x86_64.sh
