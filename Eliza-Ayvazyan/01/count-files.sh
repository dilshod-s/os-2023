
#!/bin/bash

function count() {
 dir="$1"
 counter=0

 if [[ -d "$dir" ]]; 
 then
  counter=$(ls -1 "$dir" | wc -l)
 fi

 echo $counter
}

dir="$1"
count "$dir"


