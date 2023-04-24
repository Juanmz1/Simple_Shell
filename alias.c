include "shell.h"

declare - A aliases

print_aliases()
{
for alias_name in "${!aliases[@]}"; do
echo "$alias_name='${aliases[$alias_name]}'"
done
}

void print_alias()
{
for alias_name in "$@"; do
if ["${aliases[$alias_name]+defined}"]; then
echo "$alias_name='${aliases[$alias_name]}'"
else
echo "alias: $alias_name: not found"
return (1);
fi
done
}

define_alias()
{
for arg in "$@"; do

if [[$arg == *= *]]; then
alias_name = "${arg%%=*}"
alias_value = "${arg#*=}"
aliases[$alias_name] = "$alias_value"
else
echo "alias: $arg: not in the form 'name=value'"
return (1);
fi
done
}


if [$# -eq 0]; then
print_aliases
elif ["$1" = "-p"]; then
shift
print_alias "$@"
else
define_alias "$@"
fi
