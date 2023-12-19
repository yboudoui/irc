

a=":yee TOTO : dhsf sdkfjh\r\nPASS 555\r\nNICK yboudoui2\r\nUSER yboudoui yboudoui localhost :Youssouf BOUDOUIA\r\nJOIN #t\r\n"

#nc 127.0.0.1 8080 $a

echo -n $a | nc 127.0.0.1 8081
#PRIVMSG #t :f\r\n
#EOF

