# idsort
	a utility to sort and joint info from different files
	inspired by IBS DFSORT utility

## operation modes

-S, --sort 
	sort

-J, --Join

## required arguments

[-I#] [File]

-O, --output-file [File]

## flags

-f, --field=field[/field]...
	defauts to the whole line

-c, --condition=condition[&&condition]...
	            condition[||condition]... 
	

-i, --include=field[/field]...

--header=number-of-lines

--footer=number-of-lines

## option syntax

field		->		start:length:type:order			

condition	->		start:lenght:type:operator:value


	start		->	the number of column where the field begins, the first column is 1, if ommited defaults to 1

	lenght		->	the number of characters in the field, if ommited defaults to the end of the line

	type		->	N for numbers or S for strings, if omited defaults to string

	order		->	A for ascending or D for descending, if omited defaults to ascending

	operator	->	comparation operator <, >, <=, >=, =, !=, ~=(just for strings, equivalent to "contains") 

	value		->	the value to compare the field with, must be a number or a quoted string
