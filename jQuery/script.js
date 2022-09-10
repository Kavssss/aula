function soma() {
	var a=10;
	var b=5;
	document.write(a + b);
}


function somar(a, b) {
	document.write(a + b);
}

//soma(13, 21);

function sum(a, b) {
	return(a + b);
}

//document.write(sum(20, 1));

function somaNumeros() {
	var val1 = parseInt(document.getElementById("num1").value);
	var val2 = parseInt(document.getElementById("num2").value);
	var soma = val1 + val2;
	//document.write(soma);
	document.getElementById("resultados").innerHTML = "<div class=\"resultado\">" + soma + "</div>";
}

function subNumeros() {
	var val1 = parseInt(document.getElementById("num1").value);
	var val2 = parseInt(document.getElementById("num2").value);
	var sub = val1 - val2;
	//document.write(sub);
	document.getElementById("resultados").innerHTML = "<div class=\"resultado\">" + sub + "</div>";
}

function multNumeros() {
	var val1 = parseInt(document.getElementById("num1").value);
	var val2 = parseInt(document.getElementById("num2").value);
	var mult = val1 * val2;
	//document.write(mult);
	document.getElementById("resultados").innerHTML = "<div class=\"resultado\">" + mult + "</div>";
}

function divNumeros() {
	var val1 = parseInt(document.getElementById("num1").value);
	var val2 = parseInt(document.getElementById("num2").value);
	var div = val1 / val2;
	//document.write(div);
	document.getElementById("resultados").innerHTML = "<div class=\"resultado\">" + div + "</div>";
}