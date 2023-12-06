for file in *.jpg; do
    if [[ -f "$file" ]]; then
        if [[ $file =~ ^[0-9]{4}-[0-9]{2}-[0-9]{2}-.*\.jpg$ ]]; then
            echo "$file is already named correctly"
        else
            creation_date=$(stat -c %y "$file" | cut -d ' ' -f1)
            new_name="$creation_date-$file"

            mv "$file" "$new_name"
            echo "$file -> $new_name"
        fi
    fi
done
