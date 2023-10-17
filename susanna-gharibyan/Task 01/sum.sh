sum.sh

sum=0
if[[S#!=1]]
then 
echo "argument should be passed";
exit 1;
fi
while[[$sum<$1]]
do
 read num;
 if[[$sum -ge limit]]
  then
  echo $sum
  exit 1
  fi
  sum=sum+num;
  done
  echo $sum
  exit 0
