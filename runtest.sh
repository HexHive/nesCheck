#!/bin/bash

TESTFILE=test

make || exit 1;

clang -O0 -g -emit-llvm neschecklib.c -c -o neschecklib.bc

cd test
rm -f $TESTFILE.bc $TESTFILE.ll $TESTFILE.opt.bc $TESTFILE.opt.ll $TESTFILE.s $TESTFILE.native $TESTFILE.nescheckout
clang -O0 -g -emit-llvm "$TESTFILE.c" -c -o "$TESTFILE.bc" || exit 1;
llvm-dis < "$TESTFILE.bc" > "$TESTFILE.ll"
llvm-link ../neschecklib.bc "$TESTFILE.bc" -o "$TESTFILE.linked.bc"
opt -o "$TESTFILE.opt.bc" -load ../../../../Debug+Asserts/lib/LLVMNesCheck.so -nescheck -stats -time-passes < "$TESTFILE.linked.bc" > "$TESTFILE.nescheckout" 2>&1  || exit 1;
llvm-dis < "$TESTFILE.opt.bc" > "$TESTFILE.opt.ll"
llc "$TESTFILE.opt.bc" -o "$TESTFILE.s"
gcc "$TESTFILE.s" -o "$TESTFILE.native"
chmod +x $TESTFILE.native
./$TESTFILE.native
