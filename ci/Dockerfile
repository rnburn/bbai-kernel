FROM gcc:13

WORKDIR /third_party

ADD setup_build_environment.sh /third_party
ADD install_bazel.sh /third_party
ADD latest-glibc.conf /etc/ld.so.conf.d

RUN /third_party/setup_build_environment.sh \
 && /third_party/install_bazel.sh

EXPOSE 8888
