echo "Compiling dat shiz"
APP_NAME="filedez"
FILES="filedez.c dezcrypt.c"

echo "gcc -o $APP_NAME $FILES"
gcc -o $APP_NAME $FILES
