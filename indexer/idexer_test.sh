indexer > foo
var="$(grep -i count * | wc -w foo | awk '{print $1}')"
echo "Words in page: $var"

