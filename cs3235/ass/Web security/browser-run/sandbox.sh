#!/bin/bash

# enable user namespace cloning

sudo sysctl -w kernel.unprivileged_userns_clone=1

