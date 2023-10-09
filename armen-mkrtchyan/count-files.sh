function f_count(){
    
cd $1 | ls -1 | wc -l

}

sum=$(f_count $1)

echo $sum
