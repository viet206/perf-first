#!/bin/sh

OPT=$1

if [ -z $OPT ]; then
cat <<EOF

	Script builder

	-b : build
EOF
exit 1
fi

case $OPT in
	-b)
		cc -I../src ../src/*.c -O3 -o crm
		;;
	*)
		echo "Error"
		;;
esac
