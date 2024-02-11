# CST-315-WF900A
# Author: Isaac Lund
# Date: 02/01-11/2024

# Directs scripts to the bourne-shell.
#! /bin/sh

#echo "ls command";
ls;
sleep 2;

#echo "mkdir command of folder 'Life'";
mkdir life; ls;
sleep 2;

#echo "rmdir command of folder 'Life'";
rmdir life; ls;
sleep 2;

#echo "ls -l command";
ls -l;
sleep 2;

#echo "touch command of 'file2'";
touch file2; ls -l;
sleep 2;

#echo "cp command on 'file' to 'file2'";
cp file file2;
sleep 2;

#echo "cat command on 'file2'";
cat file2;
sleep 2;

#echo "grep command on 'file2' for 'hello'";
grep hello file2;
sleep 2;

#echo "exit command"
