#!/usr/bin/env bash
#
# usage: bash -x ./run.sh
#

declare -r proj=GNet
declare -r dir_build=build
declare -r dir_scripts=scripts
declare -r client=${proj}_client.out
declare -r server=${proj}_server.out
declare -r unittest=${proj}_unittest.out
declare -r profiler=${proj}_profiler.out
declare -r workspace=ws-${proj}
declare -r is_running=`ps aux | grep tmux | grep -v grep`

rm -rf $dir_build; 

bash -x ./$dir_scripts/fmt.sh

mkdir $dir_build; 

cmake -B $dir_build .

make -C $dir_build; 

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
tmux split-window -h

# client task pane
tmux send-keys -t left 'clear' 'C-m'
tmux send-keys -t left "./$dir_build/$client" 'C-m'

# unittest task pane
tmux send-keys -t right 'clear; sleep 1' 'C-m'
tmux send-keys -t right "ls -al $dir_build/*.out" 'C-m'
tmux send-keys -t right "bat test/main.cpp" 'C-m'
tmux send-keys -t right "$dir_build/$unittest" 'C-m'

# resize the client pane
tmux select-pane -t left 
tmux resize-pane -R 5

# Set focus on the unittest pane
tmux select-pane -t right

# Set default window
tmux select-window -t $workspace:$USER

# Attach to session
tmux -2 attach-session -t $workspace
