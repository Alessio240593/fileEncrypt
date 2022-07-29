#! /bin/bash

GREEN=$(tput setaf 2)

if [ ! -d "build" ]
then
	mkdir build
	printf "${GREEN} <build> directory create succesfully!\n${RESET}"
fi

cd build

cmake ..
printf "${GREEN} makefile create succesfully!\n${RESET}"

make
printf "${GREEN} application create succesfully!\n${RESET}"

make