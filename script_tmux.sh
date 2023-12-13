#!/bin/bash

# Générer un numéro de port aléatoire entre 1024 et 8090
random_port=$(shuf -i 8000-8100 -n 1)
random_pass=$(shuf -i 111-999 -n 1)

# Démarrer tmux
tmux kill-session -t ma_session
tmux new-session -d -s ma_session

# Diviser la fenêtre en deux panneaux horizontaux
tmux split-window -h

tmux select-pane -t ma_session:0.1
# Lancer ./webserve dans le deuxième panneau avec le titre "WebServe"
tmux send-keys -t ma_session:0.1 './webserve ' $random_port ' ' $random_pass '' C-m
tmux select-pane -t ma_session:0.1
tmux rename-window "WebServe"

sleep 2

tmux select-pane -t ma_session:0.0
# Lancer irssi dans le premier panneau avec le titre "IRSSI"
tmux send-keys -t ma_session:0.0 'irssi -c localhost --port='$random_port' --password='$random_pass'' C-m
tmux select-pane -t ma_session:0.0
tmux rename-window "IRSSI"


# Exemple : Utiliser xdotool pour naviguer dans les panneaux et y écrire des commandes
# Naviguer vers le panneau "IRSSI" et envoyer la commande "/connect irc.freenode.net" dans irssi
tmux select-pane -t ma_session:0.0
tmux send-keys -t ma_session:0.0 '/join channel' ENTER
tmux send-keys -t ma_session:0.0 'Hello World !' ENTER

# Attacher à la session tmux
tmux attach-session -t ma_session