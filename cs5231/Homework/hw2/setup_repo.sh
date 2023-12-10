#!/bin/bash

DIR=~/A2/
cd $DIR

if [ ! -f "SID" ]; then
	echo "Please run ./gen_sid.sh to generate SID file first."
	exit
fi

read -p 'GitHub account username (user.name): ' GIT_USER
read -p 'GitHub account email address (user.email): ' GIT_MAIL

git config --global user.name $GIT_USER
git config --global user.email $GIT_MAIL

# unset repo
rm -rf .git

# init repo
git init && git add -A && git commit -m "init"
git branch -M main

# set remote repo
read -p 'SSH URL to your Github repo (git@...): ' repo_url
git remote add origin "$repo_url"
git push -u origin main

