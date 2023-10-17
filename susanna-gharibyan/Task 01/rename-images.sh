for img in $(ls*.jpg); do
creation_date = $(stat "$img" -c "%y"| awk '{print $1}')
new_name="${creation_date}-${img}"
done
