#!/usr/bin/env bash

declare -r dir_build=`pwd`/build
declare -r proj=GNet
declare -r workspace=ws-${proj}
declare -r is_running=`ps aux | grep tmux | grep -v grep`
declare -r client=${proj}_client.out
declare -r server=${proj}_server.out
declare -r unittest=${proj}_unittest.out
declare -r profiler=${proj}_profiler.out

# make sure the workspace is new one
if [ -z "$is_running" ]; then
  tmux has-session -t $workspace 2>/dev/null
  if [ $? == 0 ]; then  
    tmux kill-session -t $workspace
  fi
fi

# create new session
tmux -2 new-session -d -s $workspace -n $USER

# reset the pane
tmux kill-pane -a
tmux split-window -v
tmux select-pane -t 1
tmux split-window -h
tmux select-pane -t 1
tmux resize-pane -D 16

# server task pane
tmux send-keys -t 1 'clear' 'C-m'
tmux send-keys -t 1 "$dir_build/$server" 'C-m'

# client task pane
tmux send-keys -t right 'clear; sleep 1' 'C-m'
tmux send-keys -t right "$dir_build/$client" 'C-m'

# cmd control pane
tmux send-keys -t 3 'clear; sleep 2' 'C-m'
tmux send-keys -t 3 "ss -tulpn | grep $proj" 'C-m'

# Set focus on the cmd control pane
tmux select-pane -t 3

# Set default window
tmux select-window -t $workspace:$USER

# Attach to session
tmux -2 attach-session -t $workspace
