#!/bin/bash
random_port=$(shuf -i 1024-65535 -n 1)
random_pass=$(shuf -i 111-999 -n 1)

writeSpeed=30

# Commande pour ouvrir un terminal et lancer webserve
gnome-terminal --geometry=140x100+0+0 --title="FT_IRC" -- bash -c "./webserve $random_port $random_pass; exec bash"
sleep 1

gnome-terminal --geometry=140x34+1280+0  --title="IRSSI_TRISTAN" -- bash -c "irssi -c localhost --port=$random_port --password=$random_pass; exec bash"
WID_TRISTAN=`xdotool search --name "IRSSI_TRISTAN" `

gnome-terminal --geometry=140x34+1280+720  --title="IRSSI_ISOLDE" -- bash -c "irssi -c localhost --port=$random_port --password=$random_pass; exec bash"
WID_ISOLDE=`xdotool search --name "IRSSI_ISOLDE" `

xdotool windowfocus $WID_TRISTAN type --delay $writeSpeed "/set nick tristan" && xdotool key "Return" 
xdotool windowfocus $WID_TRISTAN type --delay $writeSpeed "/connect localhost $random_port $random_pass" && xdotool key "Return" 
xdotool windowfocus $WID_ISOLDE type --delay $writeSpeed "/set nick isolde" && xdotool key "Return" 
xdotool windowfocus $WID_ISOLDE type --delay $writeSpeed "/connect localhost $random_port $random_pass" && xdotool key "Return" 


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
    else 
        WID=$WID_ISOLDE;
    fi

    xdotool windowfocus $WID type --delay $writeSpeed "$cmd" && xdotool key "Return" 
done < "$fichier"
