#!/bin/zsh

# Load ROOT environment
source $(brew --prefix root)/bin/thisroot.sh

# Define GUNDAM paths
export GUNDAM_ROOT="$HOME/Research/gundam"
export GUNDAM_INSTALL="$HOME/Research/gundam/gundam-gcc_17.0.0-arm64-apple-darwin24.6.0"

# Add GUNDAM executable and libraries
export PATH="$GUNDAM_INSTALL/bin:$PATH"
export DYLD_LIBRARY_PATH="$GUNDAM_INSTALL/lib:$DYLD_LIBRARY_PATH"

# Go back to tutorial repo
cd "$HOME/Research/gundam-input-tutorial_new"

echo "ROOT: $(which root)"
echo "GUNDAM: $(which gundamFitter)"
echo "Current directory: $(pwd)"
