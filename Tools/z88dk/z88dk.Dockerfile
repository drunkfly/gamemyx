# To create the image:
#   $ docker build -t z88dk -f z88dk.Dockerfile .
# To run the container:
#   $ docker run -v ${PWD}:/src/ -it z88dk <command>

FROM alpine:latest

LABEL Version="0.8" \
      Date="2018-Apr-10" \
      Docker_Version="18.03.0-ce-mac60 (23751)" \
      Maintainer="Garrafon Software (@garrafonsoft)" \
      Description="A basic Docker container to compile and use z88dk from GIT"

ENV Z88DK_PATH="/opt/z88dk" \
    SDCC_PATH="/tmp/sdcc"

RUN apk add --no-cache build-base libxml2 m4 \
    && apk add --no-cache -t .build_deps bison flex libxml2-dev git subversion boost-dev texinfo \
    && git clone --depth 1 --recursive https://github.com/z88dk/z88dk.git ${Z88DK_PATH}

# Add, edit or uncomment the following lines to customize the z88dk compilation
# COPY clib_const.m4 ${Z88DK_PATH}/libsrc/_DEVELOPMENT/target/
# COPY config_sp1.m4 ${Z88DK_PATH}/libsrc/_DEVELOPMENT/target/zx/config/

RUN cd ${Z88DK_PATH} \
    && chmod 777 build.sh \
    && ./build.sh \
    && rm -fR ${SDCC_PATH} \
    && apk del .build_deps

ENV PATH="${Z88DK_PATH}/bin:${PATH}" \
    ZCCCFG="${Z88DK_PATH}/lib/config/"

WORKDIR /src/
