#!/bin/bash

# JUDGE_TARGET_SITE_DIR and JUDGE_ATTACKER_SITE_DIR must be set

CUR_DIR=$(dirname $(readlink -f $0))
case_no=$1
flag_val=$2

create_folders_target=""
create_folders_attacker=""
copy_files_target=""
link_files_target=""
copy_files_attacker=""
link_files_attacker=""
extra_sed=""
db_schemas=""

$CUR_DIR/cleanup.sh > /dev/null 2>&1

case "$case_no" in
	"1")
		copy_files_target="case01.php"
		link_files_target="includes global-libs"
		db_schemas="setup.sql table1.sql"
		;;
	"2")
		copy_files_target="case02.php"
		link_files_target="includes global-libs"
		db_schemas="setup.sql table2.sql"

		voucher_id=$(python3 -c 'import random; print(random.randint(2, 10**9))')
		extra_sed='-e s/!!VOUCHER_ID!!/'$voucher_id'/g'
		;;
	"3")
		copy_files_target="case03.php"
		csrf_token=$(sha1sum <<< $USERNAME | awk '{ print $1 }')
		extra_sed='-e s/!!CSRF_TOKEN!!/'"$csrf_token"'/g'
		;;
	"4")
		create_folders_target="case04"
		copy_files_target="case04/login.php"
		link_files_target="case04/404.php"
		copy_files_attacker="cookie_thief.php"

		cookie_val=$(openssl rand --hex 20)
		extra_sed='-e s/!!COOKIE_VALUE!!/'"$cookie_val"'/g'
		;;
	"5")
		create_folders_target="case05"
		copy_files_target="case05/delete.php case05/login.php"
		link_files_target="case05/index.php"

		cookie_val=$(openssl rand --hex 20)
		csrf_token=$(sha1sum <<< $USERNAME | awk '{ print $1 }')
		extra_sed='-e s/!!COOKIE_VALUE!!/'"$cookie_val"'/g -e s/!!CSRF_TOKEN!!/'"$csrf_token"'/g'
		;;
	*)
		echo "There is no case $case_no!"
		exit 1
		;;
esac

for folder in $create_folders_target; do
	mkdir -p $JUDGE_TARGET_SITE_DIR/"$folder"
done

for file in $copy_files_target; do
	sed -e 's/!!FLAG_VALUE!!/'"$flag_val"'/g' \
		$extra_sed \
		$JUDGE_TARGET_SRC_DIR/"$file" > \
		$JUDGE_TARGET_SITE_DIR/"$file"
done

for file in $link_files_target; do
	ln -s $JUDGE_TARGET_SRC_DIR/"$file" $JUDGE_TARGET_SITE_DIR/"$file"
done

for folder in $create_folders_attacker; do
	mkdir -p $JUDGET_ATTACKER_SITE_DIR/"$folder"
done

for file in $copy_files_attacker; do
	sed -e 's/!!FLAG_VALUE!!/'"$flag_val"'/g' \
		$extra_sed \
	   	$JUDGE_ATTACKER_SRC_DIR/"$file" > \
		$JUDGE_ATTACKER_SITE_DIR/"$file"
done

for file in $link_files_attacker; do
	ln -s $JUDGE_ATTACKER_SRC_DIR/"$file" $JUDGE_ATTACKER_SITE_DIR/"$file"
done

for schema in $db_schemas; do
	sed -e 's/!!FLAG_VALUE!!/'$flag_val'/g' $CUR_DIR/$schema \
		$extra_sed | \
	   sudo mysql -u root -p'testpass' 
done


