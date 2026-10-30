#!/bin/bash

cd task2

rm -rf obj_dir/
rm -f sinegen.vcd

echo "Compiling program..."

if verilator -Wall --cc --trace counter.sv rom.sv sinegen.sv -exe sinegen_tb.cpp \
    --top-module sinegen \
    -CFLAGS "-I$(realpath ../include)"; then

        echo "Compilation successful"

        echo "Building program..."
        if make -j -C obj_dir/ -f Vsinegen.mk Vsinegen; then

            echo "Build successful"
            echo "Running program..."

            ~/Documents/iac/lab0-devtools/tools/attach_usb.sh
            obj_dir/Vsinegen
            surfer "sinegen.vcd"
        else
            echo "Build failed"
        fi 
else
    echo "Compilation failed"
fi 
