echo -e "\nEnter your name: "
read name

echo -e "\nEnter phone number: "
read phone

echo -e "\nEnter city: "
read city

echo -e "\nEnter pin number: "
read pin

fname="records.txt"
echo -e "$name\t$phone\t$city\t$pin\t$state" >> "$fname"

if [ -s "$fname" ]; then
  echo -e "\nName\tPhone\tCity\tPin\tState\n"
  cat "$fname"
else
  echo -e "\nFile is Empty"
fi

echo -e "\nEnter name to modify record: "
read name_to_modify

if grep -q "$name_to_modify" "$fname"; then
  echo -e "\nEnter new phone number: "
  read new_phone

  # Using sed to replace the line with the updated information
  sed -i "s/^$name_to_modify\t[^\t]*/$name_to_modify\t$new_phone/" "$fname"
else
  echo -e "\nRecord not found"
fi