count-files.sh 

function Count() {
    files_list=$(ls -1 $1)
    count=$(echo "$files_list" | wc -l)

    echo "$1: $count"
}
if [ $# -ne 1 ]; then
    echo "something went wrong, please correct"
    echo  $0
    exit 1
fi

directory_to_count=$1
Count "$directory_to_count"

