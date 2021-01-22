logs="./dumps/log"
var=0

while true; do
	./debug nv ./dumps/imprint$var 2>$logs &
	sleep 600
	ps -ef | grep ./debug | grep -v grep | awk '{ print $2 }' | xargs kill -2
	((var=$var+1))
done
