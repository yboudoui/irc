#!/bin/sh

random_port=$(shuf -i 1024-65535 -n 1)
random_pass=$(shuf -i 111-999 -n 1)

writeSpeed=5

#ctrl+V ctrl+M  retrun (\r\n)
# Commande pour ouvrir un terminal et lancer ircserv
gnome-terminal --geometry=140x100+0+0 --title="FT_IRC" -- bash -c "./ircserv $random_port $random_pass; exec bash"
sleep 0.5

gnome-terminal --geometry=140x34+1280+0  --title="IRSSI_TRISTAN" -- bash -c "nc 127.0.0.1 $random_port "
WID_TRISTAN=`xdotool search --name "IRSSI_TRISTAN" `

gnome-terminal --geometry=140x34+1280+720  --title="IRSSI_ISOLDE" -- bash -c "nc 127.0.0.1 $random_port "
WID_ISOLDE=`xdotool search --name "IRSSI_ISOLDE" `

xdotool windowfocus $WID_TRISTAN 
xdotool type --delay $writeSpeed "PASS $random_pass"
xdotool key --delay 10 ctrl+v && sleep 0.1 && xdotool key ctrl+m && xdotool key "Return" 
xdotool type --delay $writeSpeed "NICK tristan"
xdotool key --delay 10 ctrl+v && sleep 0.1 && xdotool key ctrl+m && xdotool key "Return" 
xdotool type --delay $writeSpeed "USER tristan tristan localhost :Tristan Wagner"
xdotool key --delay 10 ctrl+v && sleep 0.1 && xdotool key ctrl+m && xdotool key "Return" 


xdotool windowfocus $WID_ISOLDE
xdotool type --delay $writeSpeed "PASS $random_pass"
xdotool key --delay 10 ctrl+v && sleep 0.1 && xdotool key ctrl+m && xdotool key "Return" 
xdotool type --delay $writeSpeed "NICK isolde"
xdotool key --delay 10 ctrl+v && sleep 0.1 && xdotool key ctrl+m && xdotool key "Return" 
xdotool type --delay $writeSpeed "USER isolde isolde localhost :Isolde Wagner"
xdotool key --delay 10 ctrl+v && sleep 0.1 && xdotool key ctrl+m && xdotool key "Return" 


# Assurez-vous que le script est exécutable avec la commande suivante si nécessaire :
# chmod +x nom_du_script.sh

# Vérifie si un fichier est spécifié en argument
if [ $# -eq 0 ]; then
    echo "Usage: $0 <fichier>"
    exit 1
fi

# Récupère le nom du fichier à traiter
fichier=$1

# Vérifie si le fichier existe
if [ ! -f "$fichier" ]; then
    echo "Le fichier $fichier n'existe pas."
    exit 1
fi

# Lit le fichier ligne par ligne
while IFS= read -r ligne || [ -n "$ligne" ]; do
    # Utilise le caractère pipe "|" comme séparateur
    name=$(echo "$ligne" | cut -d ';' -f 1)
    cmd=$(echo "$ligne" | cut -d ';' -f 2)

    if [ "$name" = "TRISTAN" ]; then
        WID=$WID_TRISTAN;
        nick=tristan;
    else 
        WID=$WID_ISOLDE;
        nick=isolde;
    fi

    premierCaractere=$(echo "$cmd" | awk '{print substr($0, 1, 1)}')

    if [ $premierCaractere = "/" ]; then
        msg=":"$nick" "$(echo "$cmd" | awk '{print substr($0, 2)}')
    else
        msg=":"$nick" PRIVMSG #DerRing :"$cmd
    fi
    xdotool windowfocus $WID type --delay $writeSpeed  "$msg" && xdotool key "Return" 
    xdotool key --delay 10 ctrl+v && sleep 0.1 && xdotool key ctrl+m && xdotool key "Return" 

done < "$fichier"
