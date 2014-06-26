BEGIN {	menor = 100000
	maior = 0
}

{
	if($1 < menor) {
		menor = $1
	}
	if($1 > maior) {
		maior = $1
	}
}
END {	print("menor: "menor".\nmaior: "maior)
}
			

