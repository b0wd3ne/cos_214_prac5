# CampusGuard - COS 214 Practical 5
# Builds and runs the whole application inside Docker, matching what the
# team builds and demos locally. Includes gdb and valgrind so the same
# evidence used for the write-up can be reproduced live during the demo.

FROM ubuntu:22.04

RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential \
        gdb \
        valgrind \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /campusguard

# Copy source after installing packages so package layers are cached and
# only re-run when the Ubuntu base image changes, not on every code edit.
COPY . .

RUN make clean && make

CMD ["./campusguard"]
