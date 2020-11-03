echo '[*] running b2c!'
python3 ./b2c.py freenote
echo '[*] building wrapper'
gcc ./wrapper.c ./char.h -o wrapper -g -lpthread