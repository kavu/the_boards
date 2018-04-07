#!/usr/bin/env bash

set -e

docker build --rm -f Dockerfile -t qmk:latest .
