#!/bin/bash

# Générer un numéro de port aléatoire entre 1024 et 65535
random_port=$(shuf -i 1024-65535 -n 1)
random_pass=$(shuf -i 111-999 -n 1)

# Commande pour ouvrir un terminal et lancer webserve
gnome-terminal --tab --title="Webserve" -- bash -c "./webserve $random_port $random_pass; exec bash"

# Attendre quelques secondes pour laisser webserve démarrer
sleep 2

# Commande pour ouvrir un deuxième terminal et lancer IRSSI
gnome-terminal --tab --title="IRSSI" -- bash -c "irssi -c localhost --port=$random_port --password=$random_pass; exec bash"

# Attendre quelques secondes pour laisser IRSSI démarrer
sleep 2

WID=`xdotool search --name "IRSSI" `
xdotool windowfocus $WID

xdotool type --delay 100 "/join channel"
xdotool key "Return" 