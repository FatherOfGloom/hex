:: You need to have wsl installed in order to run this script
pushd .\src\
bash.exe -c "set -xe && gcc -o lin-exe main.c /mnt/c/Users/anton/dev/include/unholy.c hex.c -lgmp -I/mnt/c/Users/anton/dev/include && valgrind -s --track-origins=yes ./lin-exe 123123"
del .\lin-exe
del .\lin-exe.exe
popd