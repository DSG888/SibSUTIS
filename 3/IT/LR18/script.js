var i;
var array1 = new Array(9); 

function Rand() {
	document.form1.reset();
	for (i = 1; i <= 9; i++) {
		array1[i-1] = Math.floor(Math.random() * (99 - 11)) + 10;
		document.form1.elements["textArr" + i].value = array1[i-1];
	}
}

function Sort() {
	for (i = 1; i <= 9; i++) {
		array1[i-1] = document.form1.elements["textArr" + i].value;}
	array1.sort(function(a,b){return a - b});
	for (i = 1; i <= 9; i++) {
		document.form1.elements["sortArr" + i].value = array1[i-1];
	}
}
