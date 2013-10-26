./build.sh

echo "Woo, done building..."
echo

if [ -e filedez.c.dez ]; then
	echo "Removing filedez.c.dez"
	rm lol.txt.dez
fi

if [ -e filedez.c.dez.undez ]; then
	echo "Removing filedez.c.dez.undez"
fi

echo
echo "Testing: ./filedez filedez.c"
echo

./filedez filedez.c
clear

echo
echo "Testing: ./filedez -d filedez.c.dez"
echo

./filedez -d filedez.c.dez
clear

echo "Undezzed filedez.c:"
cat filedez.c.dez.undez