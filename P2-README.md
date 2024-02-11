// CST-315-WF900
// Author: Isaac Lund
// Date: 02/10-11/2024
This is my project 2 to run the project you need oracl VM virtualbox installed then create a virtual machine default values are fine. 
Then when you run it you need to go to the command prompt or terminal do these things
1. sudo apt-get update
2. sudo apt-get upgrade
3. sudo apt-get install build-essential
4. sudo apt-get install manpages-dev
4. gcc --version

Once all this is done you can now run the project file Project-2.c in terminal by doing:
1. checking if you have the project 2 file batch file and file all in the current directory
2. gcc -o filename Project-2.c
3. ./filename

You can now do any terminal command except changing directory example, cd
But there is a batch file you can run to go through a number of commands to do so you need to do:
1. chmod -x batch.sh
2. ./batch.sh

This will run through the commands in an interval of 2 seconds displaying what each command was.
You can exit the batch file at any time with ctrl+C, but doing so will exit the Project-2 file.
