#!/bin/bash

cd task3

rm -rf obj_dir/
rm -f sigdelay.vcd

echo "Compiling program..."

if verilator -Wall --cc --trace counter.sv ram.sv sigdelay.sv -exe sigdelay_tb.cpp \
    --top-module sigdelay \
    -CFLAGS "-I$(realpath ../include)"; then

        echo "Compilation successful"

        echo "Building program..."
        if make -j -C obj_dir/ -f Vsigdelay.mk Vsigdelay; then

            echo "Build successful"
            echo "Running program..."

            ~/Documents/iac/lab0-devtools/tools/attach_usb.sh
            obj_dir/Vsigdelay
            surfer "sigdelay.vcd"
        else
            echo "Build failed"
        fi 
else
    echo "Compilation failed"
fi 
