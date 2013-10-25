./build.sh

echo "Woo, done building..."
echo

if [ ! -e lol.txt ]; then
	echo "No lol.txt, creating..."
	echo lolololololololololololololololololol > lol.txt
fi

if [ -e lol.txt.dez ]; then
	echo "Removing lol.txt.dez"
	rm lol.txt.dez
fi

echo


echo "Testing: ./filedez lol.txt"
echo

./filedez lol.txt