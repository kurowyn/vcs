#!/usr/bin/env bash

set -euo pipefail

bin=../bin/vcs.exe

make build
./$bin
