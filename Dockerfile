FROM ubuntu:14.04
MAINTAINER Andrew Schwartzmeyer <andschwa@microsoft.com>

RUN apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF && \
    echo "deb http://download.mono-project.com/repo/debian wheezy main" | tee /etc/apt/sources.list.d/mono-xamarin.list && \
    apt-get update && apt-get install -y \
    mono-devel \
    ca-certificates-mono \
    nuget \
    libicu-dev \
    libunwind8 \
    gcc \
    g++ \
    make \
    cmake \
    wget && \
    apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

ENV LANG=en_US.UTF-8
RUN locale-gen en_US.UTF-8 && update-locale
COPY fakelogin /opt/
